# -*- coding: utf-8 -*-

import serial
import datetime
import time
import json
import sys
from collections import OrderedDict

ser = serial.Serial("COM9", 115200,  timeout=10)
while True:
    time.sleep(5)
    #データ要求コマンド送信「.」
    ser.write(b".")
    co2 = ser.readline().decode().strip()
    if len(co2) > 0:
      break
ser.close()

json_src ={'CO2':co2}

json_data = json.dumps(json_src, indent=2)
print(json_data)
