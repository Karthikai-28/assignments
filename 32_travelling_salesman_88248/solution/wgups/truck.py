from __future__ import annotations
from typing import TYPE_CHECKING, Union
from utils import debug, minutes_to_clock
if TYPE_CHECKING:
    from wgups.place import Place
    from wgups.package import Package
    from datastructures.graph import Graph


class Truck:
    __number = 0

    @staticmethod
    def __get_number() -> int:
        Truck.__number += 1
        return Truck.__number

    @staticmethod
    def __calc_time(time: float) -> float:
        return (8 * 60) + (time / 18 * 60)

    miles_traveled: float = 0
    packages: list[Package]
    number: int
    deliveries_performed = 0

    def __init__(self) -> None:
        self.number = self.__get_number()
        self.packages = []

    def load_package(self, package: Package) -> None:
        if self.full():
            raise Exception

        package.set_en_route(self)
        self.packages.append(package)

    def capacity(self) -> int:
        return 16 - len(self.packages)

    def get_time(self) -> float:
        return self.__calc_time(self.miles_traveled)

    def empty(self) -> bool:
        return len(self.packages) == 0

    def full(self) -> bool:
        return len(self.packages) == 16

    def location(self) -> str:
        return 'HUB' if self.empty() else self.packages[-1].address

    def run_delivery(self, graph: Graph[Union[Place, str]]) -> None:
        """
        Calculates the distance traveled while delivering all the packages on
        the truck. Iterates over every package, calculating the distance from
        the current location to the next location, and returns to the hub at
        the end
        """
        self.deliveries_performed += 1
        previous: str = ''
        current: str = 'HUB'
        for pkg in self.packages:
            previous = current
            current = pkg.address
            self.miles_traveled += graph.distance_between(previous, current)
            pkg.set_delivered(self)
            info = f'truck {self.number}'
            info += f' delivered package {pkg.id}'
            info += f' at {minutes_to_clock(pkg.delivered_at)}'
            info += f' to address {pkg.address}'
            info += f' after {round(self.miles_traveled, 1)} miles'
            debug(info)

        self.packages.clear()
        self.miles_traveled += graph.distance_between(current, 'HUB')
        debug(
            f'returned to HUB with {round(self.miles_traveled, 1)} miles on the odo')
