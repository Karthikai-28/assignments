from __future__ import annotations
from enum import Enum, auto
import re
from typing import Optional, TYPE_CHECKING, cast
from utils import minutes_to_clock, normalize_address, ANSICodes

if TYPE_CHECKING:
    from wgups.truck import Truck

EOD = 24 * 60


class Package:
    class Status(Enum):
        AT_HUB = auto()
        EN_ROUTE = auto()
        DELIVERED = auto()

    @staticmethod
    def parse_time(time: str) -> int:
        if time == 'EOD':
            return EOD

        hours, minutes, meridiem = re.search(
            r'(?i)(\d?\d):(\d\d) ([ap]m)', time).groups()
        offset = 0 if meridiem.lower() == 'am' else 12
        return ((int(hours) + offset) * 60) + int(minutes)

    __required_truck: Optional[int] = None
    __loaded_at: Optional[float] = None
    __delivered_by: Optional[int] = None
    delivered_at: Optional[float] = None
    wrong_address = False
    __available_at = 0.0
    dependencies: set[Package]
    dependent_packages: set[int]
    __delivery_number = 0

    def __init__(self, id: str, address: str, city: str, state: str, zipcode: str, deadline: str, mass: str, notes: str):
        self.dependent_packages = set[int]()
        self.dependencies = set[Package]()
        self.id = int(id)
        self.street_address = address
        self.city = city
        self.state = state
        self.zipcode = zipcode
        self.deadline = self.parse_time(deadline)
        self.mass = int(mass)
        self.__status = self.Status.AT_HUB
        self.__parse_note(notes)
        self.address = normalize_address(
            f'{self.street_address} ({self.zipcode})')

    def __str__(self) -> str:
        deadline = minutes_to_clock(self.deadline)
        info = [f'id: {self.id}', f'address: {self.address}',
                f'status: {self.__status}', f'deadline: {deadline}']
        if self.delivered_at is not None:
            info.append(
                f'delivered at: {minutes_to_clock(self.delivered_at)}')
            on_time = self.delivered_at < self.deadline
            colored = ANSICodes.green(
                on_time) if on_time else ANSICodes.red(on_time)
            info.append(f'delivered on time: {colored}')

        return str.join(', ', info)

    def priority(self, time: float) -> bool:
        return self.at_hub() and self.deadline < EOD and self.__available_at <= time

    def available_for(self, truck: Truck, exclude: set[Package] = set()) -> bool:
        """
        Determines if this package (and recursively its dependencies) is
        available for delivery by the current truck
        """
        if self.wrong_address:
            return False

        if self.__available_at > truck.get_time():
            return False

        if not self.at_hub():
            return False

        if self.__required_truck is not None and self.__required_truck != truck.number:
            return False

        deps_available = True
        exclude.add(self)
        for deps in [d for d in self.dependencies if not d in exclude]:
            deps_available = deps.available_for(truck, exclude)

        return deps_available

    def __parse_note(self, notes: str) -> None:
        """
        Parses the note included with the package for special information
        """
        if len(notes) == 0:
            pass
        elif match := re.search(r'\d?\d:\d\d [ap]m', notes):
            self.__available_at = self.parse_time(match.group(0))
        elif match := re.search(r'truck (\d)', notes):
            self.__required_truck = int(match.group(1))
        elif 'delivered with' in notes:
            self.dependent_packages = set[int](
                map(int, re.findall(r'\d+', notes)))
        else:
            self.address = ''
            self.__available_at = self.parse_time('10:20 am')
            self.wrong_address = True

    def set_en_route(self, truck: Truck) -> None:
        if self.__status == self.Status.EN_ROUTE:
            raise Exception
        if (self.__required_truck or truck.number) != truck.number:
            raise Exception
        self.__delivered_by = truck.number
        self.__loaded_at = truck.get_time()
        self.__status = self.Status.EN_ROUTE

    def set_delivered(self, truck: Truck) -> None:
        if self.__status == self.Status.DELIVERED:
            raise Exception
        self.__status = self.Status.DELIVERED
        self.delivered_at = truck.get_time()
        self.__delivery_number = truck.deliveries_performed

    def is_delivered(self) -> bool:
        return self.__status == self.Status.DELIVERED

    def at_hub(self) -> bool:
        return self.__status == self.Status.AT_HUB

    def correct_address_available(self, time: float):
        return self.wrong_address and self.__available_at <= time

    def update_address(self):
        self.wrong_address = False
        self.address = '410 S State St (84111)'
        self.street_address = '410 S State St'
        self.zipcode = '84111'

    def status(self, time: int) -> str:
        """
        Gets the delivery status of the package at the given time

        @param time The time to retrieve that status at
        """
        if self.__available_at > time:
            return f'Delayed, package available at {minutes_to_clock(self.__available_at)}'

        loaded_at = cast(float, self.__loaded_at)
        if time < loaded_at:
            return f'At hub, expected load time {minutes_to_clock(loaded_at)}'

        delivered_at = cast(float, self.delivered_at)
        delivered_by = cast(int, self.__delivered_by)
        if time < delivered_at:
            return f'On truck {delivered_by}, loaded at {minutes_to_clock(loaded_at)}, expected delivery time {minutes_to_clock(delivered_at)} '

        return f'Delivered at {minutes_to_clock(delivered_at)} by truck {delivered_by}'

    def formatted_deadline(self) -> str:
        """
        Formats the deadline in a human-friendly format
        """
        if self.deadline == EOD:
            return 'EOD'

        return minutes_to_clock(self.deadline)

    def info(self, time: int) -> str:
        """
        Returns a string of tab-delimited info on the package for the given time

        @param time The time at which to get package status
        """
        info = [f'id: {self.id}', f'address: {self.address}']
        if (self.delivered_at or float('inf')) <= time:
            info.append(ANSICodes.green(self.Status.DELIVERED))
        elif (self.__loaded_at or float('inf')) <= time:
            info.append(ANSICodes.cyan(self.Status.EN_ROUTE))
        else:
            info.append(ANSICodes.blue(self.Status.AT_HUB))

        info.append(f'deadline: {self.formatted_deadline()}')

        if (self.__loaded_at or float('inf')) <= time:
            info.append(
                f'loaded at: {minutes_to_clock(self.__loaded_at)}')
            info.append(
                f'onto truck {self.__delivered_by} in delivery number {self.__delivery_number}')

        if (self.delivered_at or float('inf')) <= time:
            info.append(
                f'delivered at: {minutes_to_clock(self.delivered_at)}')
            on_time = self.delivered_at < self.deadline
            colored = ANSICodes.green(
                on_time) if on_time else ANSICodes.red(on_time)
            info.append(f'delivered on time: {colored}')

        return str.join('\t', info)

    def __hash__(self) -> int:
        return hash(self.id)
