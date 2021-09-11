import sys
from wgups.truck import Truck
from wgups.package import Package
from datastructures.hashmap import HashMap
from utils import clock_to_minutes

instructions = '''
Please select an option from the list:
    1. Get info on a specific package
    2. Get info on all packages
    3. Get one-liner info on all packages
    4. Get info on truck travel distance
'''


def get_input(prompt: str) -> str:
    """
    Adds a prompt to the input and captures any EOF error and quits the app
    """
    try:
        return input(f'{prompt}\n> ')
    except EOFError:
        sys.exit(0)


def get_int_input(prompt: str) -> int:
    """
    Adds a prompt to the input and captures any EOF error and quits the app
    """
    while True:
        try:
            return int(get_input(prompt))
        except ValueError:
            print('Please enter an integer value')


def print_package(package: Package, time: int) -> None:
    print(f'Package ID: {package.id}')
    print(f'Current status: {package.status(time)}')
    print(f'Package due by: {package.formatted_deadline()}')
    print(f'Package weight: {package.mass}')
    print('Delivery address:')
    print(package.street_address)
    print(f'{package.city}, {package.state} {package.zipcode}')
    print()


def start_app(packages: HashMap[int, Package], trucks: list[Truck]) -> None:
    """
    Starts the command-line app for retrieving information between
    """
    print('Welcome to WGUPS Package Tracking.')
    while True:
        selection = get_input(instructions)

        if selection == 'quit':
            break

        time = 0
        if selection != '4':
            while time == 0:
                try:
                    string = get_input(
                        'Please enter a time in the format of HH:MM')
                    time = clock_to_minutes(string)
                except Exception:
                    continue

        if selection == '1':
            while not (pkg_num := get_int_input('Please enter a valid package ID')) in packages:
                print(f'Package with ID "{pkg_num}" was not found')

            print_package(packages.get(pkg_num), time)

        elif selection == '2':
            for (_, package) in packages:
                print_package(package, time)

        elif selection == '3':
            package_list = [package for (_, package) in packages]
            package_list.sort(key=lambda p: p.id)
            for package in package_list:
                print(package.info(time))

        elif selection == '4':
            for truck in trucks:
                print(
                    f'Truck {truck.number} traveled {round(truck.miles_traveled, 1)} miles')
