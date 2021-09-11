from __future__ import annotations
from typing import Union
import utils


class Place:
    def __init__(self, name: str, address: str) -> None:
        self.name = name
        self.address = utils.normalize_address(address)

    def __str__(self) -> str:
        return self.address

    def __repr__(self) -> str:
        return self.address

    def __eq__(self, o: Union[str, Place]) -> bool:
        return hash(self) == hash(o)

    def __hash__(self) -> int:
        return hash(self.address)
