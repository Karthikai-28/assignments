from typing import Generic, Optional, TypeVar
from utils import gen_primes

Key = TypeVar('Key')
Value = TypeVar('Value')


class HashMap(Generic[Key, Value]):
    __max_bucket_size = 2
    __storage: list[list[tuple[Key, Value]]]

    def __init__(self) -> None:
        self.__gen = gen_primes()
        self.__storage_size = next(self.__gen)
        self.__initialize_storage()
        self.size = 0
        self.__can_resize = True

    def put(self, key: Key, value: Value) -> None:
        """
        Inserts a key-value pair into the map or updates an existing key-value
        pair if it is already present
        """
        bucket = self.__get_bucket(key)
        # look for the key in the current bucket
        for (i, (k, _)) in enumerate(bucket):
            if k == key:
                bucket[i] = (key, value)
                break
        # if the key isn't found, we insert it into the bucket and increment
        # the size of the map
        else:
            bucket.append((key, value))
            if self.__can_resize:
                self.size += 1

        # if the length of the current bucket exceeds the maximum size, we
        # resize the map to accommodate the new size
        if len(bucket) > self.__max_bucket_size:
            self.__resize()

    def get(self, key: Key) -> Optional[Value]:
        """
        Retrieve a value from the map given a key or None if the key doesn't
        exist
        """
        for (bucket_key, value) in self.__get_bucket(key):
            if bucket_key == key:
                return value

        return None

    def __get_bucket(self, key: Key) -> list[tuple[Key, Value]]:
        index = hash(key) % self.__storage_size
        return self.__storage[index]

    def __initialize_storage(self) -> None:
        self.__storage = [[] for _ in range(self.__storage_size)]

    def __resize(self) -> None:
        if not self.__can_resize:
            return
        self.__can_resize = False

        self.__storage_size = next(self.__gen)
        old_storage = self.__storage
        self.__initialize_storage()
        for bucket in old_storage:
            for (key, value) in bucket:
                self.put(key, value)
        self.__can_resize = True

    def __contains__(self, key: Key):
        bucket = self.__get_bucket(key)
        for (k, _) in bucket:
            if k == key:
                return True

        return False

    def __iter__(self):
        for bucket in self.__storage:
            yield from bucket
