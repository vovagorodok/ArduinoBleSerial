from typing import NamedTuple

from ble_serial import uuids


class Service(NamedTuple):
    uuid: str

    @classmethod
    def parse(cls, argv: list[str]):
        return cls(argv[1] if len(argv) > 1 else uuids.BLE_SERIAL_SERVICE_UUID)
