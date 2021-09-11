from typing import Iterable, Union, cast
from wgups.truck import Truck
from wgups.place import Place
from wgups.package import Package
from datastructures import Graph, HashMap
import csv

HUB = 'HUB'
base_time = 8 * 60

__ALL_TRUCKS__: list[Truck]
__ALL_PACKAGES__: HashMap[int, Package]
__GRAPH__: Graph[Union[Place, str]]


def __find_closest(pkgs: Iterable[Package], loc: Union[str, Place]) -> Package:
    """
    Time complexity: O(n)
    Space complexity: O(1)
    """
    shortest_dist = float('inf')
    closest = None
    for p in pkgs:
        dist = __GRAPH__.distance_between(p.address, loc)
        if dist < shortest_dist:
            shortest_dist = dist
            closest = p

    return cast(Package, closest)


wrong_address_packages = None


def __dispatch_trucks() -> int:
    """
    Goes over the list of all trucks and calls the delivery method, additionally
    it checks to see if enough time has passed for any packages with a wrong
    address to have their corrected address available and updates them if so

    Time complexity: O(m * n) -> O(2 * n) -> O(n)
    Space complexity: O(1)
    Space complexity: O(1)
    """
    global wrong_address_packages
    if wrong_address_packages is None:
        wrong_address_packages = [
            p[1] for p in __ALL_PACKAGES__ if p[1].wrong_address]

    packages_delivered = 0

    for truck in __ALL_TRUCKS__:
        packages_delivered += len(truck.packages)
        truck.run_delivery(__GRAPH__)

        if len(wrong_address_packages) != 0:
            for p in wrong_address_packages:
                if p.correct_address_available(truck.get_time()):
                    p.update_address()
                    wrong_address_packages.remove(p)

    return packages_delivered


def __distribute_packages(packages: Iterable[Package]):
    """
    Attempts to distribute packages between the trucks to create the shortest
    possible route for the given packages and trucks

    Time complexity: O(m * n) -> O(2 * n) -> O(n)
    Space complexity: O(1)
    """
    count = float('inf')
    while count > 2:
        count = 0
        for truck in __ALL_TRUCKS__:
            if truck.full():
                continue
            shortest = float('inf')
            closest = None
            for p in packages:
                if p.available_for(truck):
                    count += 1
                    dist = __GRAPH__.distance_between(
                        truck.location(), p.address)
                    if dist < shortest:
                        shortest = dist
                        closest = p

            if closest is not None:
                truck.load_package(closest)


def __deliver_priority_packages(destination_package_map: HashMap[str, list[Package]]):
    """
    Time complexity: O(n)
    Space complexity: O(n)
    """
    priority_packages = set([p[1] for p in __ALL_PACKAGES__ if any([p[1].priority(
        t.get_time()) and p[1].available_for(t) for t in __ALL_TRUCKS__])])
    # load the trucks that have the fewest miles traveled first
    __ALL_TRUCKS__.sort(key=lambda t: t.miles_traveled)
    for truck in __ALL_TRUCKS__:
        # load the truck until it's full or there are no more packages remaining
        while not truck.full() and len(priority_packages) != 0:
            # find the package whose destination is closest to the trucks
            # current location
            closest = __find_closest(priority_packages, truck.location())
            # get all dependencies of that package
            deps = closest.dependencies
            for dep in deps:
                deps = deps.union(cast(set[Package], dep.dependencies))
            deps.add(closest)
            # ensure we have capacity the package and its dependencies
            if truck.capacity() >= len(deps):
                while len(deps) != 0:
                    # find the closest package of the dependencies, for most
                    # packages this will be the original closes package
                    pkg = __find_closest(deps, truck.location())
                    deps.discard(pkg)
                    # make sure this wasn't processed already
                    if not pkg.at_hub():
                        continue
                    # add the package and remove it from the priority packages
                    # to ensure it's not loaded twice
                    priority_packages.discard(pkg)
                    truck.load_package(pkg)
                    # while we still have space, load any packages that are
                    # being delivered to the same address as the previously-
                    # loaded package
                    for p in (destination_package_map.get(pkg.address) or []):
                        if not truck.full() and p.available_for(truck):
                            priority_packages.discard(p)
                            truck.load_package(p)


def __deliver_remaining_packages() -> int:
    """
    Time complexity: O(n) + O(n) + O(n) -> O(n)
    Space complexity: O(n)
    """
    remaining_packages = [p[1] for p in __ALL_PACKAGES__ if p[1].at_hub()]
    __distribute_packages(remaining_packages)
    return __dispatch_trucks()


def __parse_packages() -> tuple[HashMap[int, Package], HashMap[str, list[Package]]]:
    """
    parses the packages from the .csv into a list of package objects and a map
    containing the all the packages for a destination, this is used later to
    load as many packages as possible that have the same destination

    Time complexity: O(n)
    Space complexity: O(n)
    """
    packages = HashMap[int, Package]()
    destination_package_map = HashMap[str, list[Package]]()
    dependency_map = HashMap[int, set[Package]]()
    with open('packages.csv') as f:
        for row in csv.reader(f, delimiter=';'):
            new_package = Package(*row)
            packages.put(new_package.id, new_package)
            if (package_list := destination_package_map.get(new_package.address)) is None:
                package_list: list[Package] = []
                destination_package_map.put(new_package.address, package_list)
            package_list.append(new_package)
            for dep in new_package.dependent_packages:
                if (dep_set := dependency_map.get(dep)) is None:
                    dep_set = set()
                    dependency_map.put(dep, dep_set)
                dep_set.add(new_package)
            for pkg in dependency_map.get(new_package.id) or []:
                pkg.dependencies.add(new_package)
                new_package.dependencies.add(pkg)

    return packages, destination_package_map


def __parse_distances() -> Graph[Union[Place, str]]:
    """
    we parse the the distances csv into a place objects. we use the the street
    address and zip code to build a unique identifier for each place. this id
    is used to look it up in the graph so we can use a string or the place
    object itself for that lookup

    Time complexity: O(n * (n/2)) = O(n^2) as it is essentially a summation
    Space complexity: O(n^2)
    """
    graph = Graph[Union[Place, str]]()
    with open('distances.csv') as f:
        places: list[Place] = []

        for name, address, *dists in csv.reader(f, delimiter=';', quotechar='"'):
            place = Place(name, address)
            graph.add_vertex(place)
            places.append(place)
            for (i, dist) in enumerate(dists):
                graph.add_edge(place, places[i], float(dist))

    return graph


def schedule_delivery() -> tuple[HashMap[int, Package], list[Truck]]:
    """
    The method responsible for figuring out how to best deliver the packages.

    n = number of packages
    m = number of places
    Time complexity: O(m^2) + O(n)
    Space complexity: O(m^2) + O(n)
    """
    global __ALL_TRUCKS__
    global __ALL_PACKAGES__
    global __GRAPH__
    __ALL_TRUCKS__ = [Truck(), Truck()]
    __ALL_PACKAGES__, destination_package_map = __parse_packages()  # O(n)
    __GRAPH__ = __parse_distances()  # O(m^2)

    # m is number of places, n is number of packages
    # complexity to here -> O(m^2) + O(n)

    # make sure all priority packages are fully delivered
    priority_remaining = True
    # time complexity of while block: O(n) + O(n) -> O(n)
    while priority_remaining:
        __deliver_priority_packages(destination_package_map)
        if priority_remaining := any([not truck.empty() for truck in __ALL_TRUCKS__]):
            __deliver_remaining_packages()

    # continue delivering packages until none remain
    remaining_package_count = sum(
        map(lambda p: 0 if p[1].is_delivered() else 1, __ALL_PACKAGES__))
    # time complexity of while block: O(n)
    while remaining_package_count != 0:
        remaining_package_count -= __deliver_remaining_packages()

    return __ALL_PACKAGES__, __ALL_TRUCKS__
