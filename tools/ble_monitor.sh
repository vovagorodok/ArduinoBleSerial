#!/bin/bash

SCRIPT_DIR=$( cd $( dirname $0 ) && pwd )
SCRIPT_PATH=$SCRIPT_DIR/ble_monitor.py
BLE_SERIAL_UUID=6e400001-b5a3-f393-e0a9-e50e24dcca9e

python3 $SCRIPT_PATH $BLE_SERIAL_UUID