import os
from typing import Any, Match
import re

dirs = {'north': 'N', 'south': 'S', 'east': 'E', 'west': 'W', '\n': ' '}


def __direction_to_letter(m: Match[str]) -> str:
    match = m.group(0)[0]
    return ' ' if match == '\n' else match.upper()


def normalize_address(address: str) -> str:
    """
    Normalizes an address so that it is uniformly displayed in both packages and
    places.
    """
    return re.sub(r'(?i)(north|south|east|west|\n)', __direction_to_letter, address.strip())


def minutes_to_clock(minutes: float) -> str:
    """
    Formats integer minutes to a clock format
    """
    return f'{int(minutes / 60)}:{(int(minutes) % 60):02}'


def clock_to_minutes(clock: str) -> int:
    """
    Converts a clock display to an integer amount of minutes
    """
    hours, minutes = list(map(int, clock.split(':')))
    if 0 <= hours < 24 and 0 <= minutes < 60:
        return hours * 60 + minutes

    raise Exception


def debug(*args) -> None:
    if 'DEBUG' in os.environ:
        print(*args)


class ANSICodes:
    CLEAR = '\033[0m'
    RED = '\033[91m'
    GREEN = '\033[92m'
    BLUE = '\033[94m'
    CYAN = '\033[96m'

    @staticmethod
    def green(line: Any) -> str:
        return f'{ANSICodes.GREEN}{line}{ANSICodes.CLEAR}'

    @staticmethod
    def cyan(line: Any) -> str:
        return f'{ANSICodes.CYAN}{line}{ANSICodes.CLEAR}'

    @staticmethod
    def blue(line: Any) -> str:
        return f'{ANSICodes.BLUE}{line}{ANSICodes.CLEAR}'

    @staticmethod
    def red(line: Any) -> str:
        return f'{ANSICodes.RED}{line}{ANSICodes.CLEAR}'


def gen_primes():
    primes = [2]
    while True:
        prime = primes[-1]
        yield prime

        while any(map(lambda p: prime % p == 0, primes)):
            prime += 1

        primes.append(prime)
