#!/usr/bin/env python3
import asyncio
import sys

from bleak import BleakClient, BleakScanner

from ble_serial import uuids
from ble_serial.utils import is_linux, is_fedora
from ble_serial.service import Service


async def scan_serial_devices(service: Service, timeout=5.0):
    devices_dict = await BleakScanner.discover(timeout=timeout, return_adv=True)

    for dev, adv in devices_dict.values():
        if service.uuid.lower() in adv.service_uuids:
            yield dev


async def acquire_mtu(client: BleakClient):
    if not is_linux():
        return

    # issue: https://github.com/hbldh/bleak/issues/1471
    if is_fedora():
        return

    from bleak.backends.bluezdbus.client import BleakClientBlueZDBus
    if type(client._backend) is not BleakClientBlueZDBus:
        return
    
    # in Linux acquire mtu should be called in order to have more than 23
    await client._backend._acquire_mtu()


async def connect(dev):
    client = BleakClient(dev)

    print(f"Connecting to {dev.name}")
    await client.connect()
    if not client.is_connected:
        print("Connection fail")
        return

    await acquire_mtu(client)

    service = client.services.get_service(uuids.BLE_SERIAL_SERVICE_UUID)
    tx_char = service.get_characteristic(uuids.BLE_SERIAL_CHARACTERISTIC_UUID_TX)
    rx_char = service.get_characteristic(uuids.BLE_SERIAL_CHARACTERISTIC_UUID_RX)

    return client, tx_char, rx_char


async def monitor(client: BleakClient, tx_char, rx_char):
    print("Monitoring...")

    # issue: https://github.com/hbldh/bleak/issues/1501
    async def callback(char, array):
        print(str(array, 'utf-8'), end='', flush=True)
    await client.start_notify(rx_char, callback)

    while True:
        await asyncio.sleep(0.01)


async def connect_and_monitor(dev):
    res = await connect(dev)
    if not res:
        return
    client, tx_char, rx_char = res

    await monitor(client, tx_char, rx_char)
    await client.disconnect()


async def scan_and_monitor(service: Service):
    devices = list()

    print("Devices:")
    async for device in scan_serial_devices(service):
        print(f"{len(devices)}. [{device.address}] {device.name}")
        devices.append(device)

    if not len(devices):
        print("Device not found.")
        exit()

    user_input = input("Chose device [0]: ")

    try:
        device_num = int(user_input)
        if device_num >= len(devices) or device_num < 0:
            print("Incorrect device number.")
            exit()
    except ValueError:
        device_num = 0
        if len(user_input):
            print("Incorrect input.")
            exit()

    await connect_and_monitor(devices[device_num])


def try_scan_and_monitor(service: Service):
    try:
        asyncio.run(scan_and_monitor(service))
    except KeyboardInterrupt:
        print("User interrupt.")
    except Exception as e:
        print(e)


if __name__ == '__main__':
    try_scan_and_monitor(Service.parse(sys.argv))
