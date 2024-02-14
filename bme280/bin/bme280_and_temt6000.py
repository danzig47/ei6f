# -*- coding: utf-8 -*-

import serial
import time
import json
import datetime as dt
import pandas as pd

if __name__ == '__main__':

    adj_t = 0.0 #温度 補正値
    adj_h = 0.0 #湿度 補正値
    adj_l = 2.0 #照度 補正値

    ser = serial.Serial("COM7", 9600, timeout=1)
    time.sleep(2)
    #データ要求コマンド送信「.」
    ser.write(b".")
    mbit = ser.read(38).decode().strip()
    ser.close()

    t = mbit.split(',')[0]
    t = str(float(t) + adj_t)

    p = mbit.split(',')[1]

    h = mbit.split(',')[2]
    h = str(round(float(h) + adj_h,2))

    l = mbit.split(',')[3]
    l = str(round(float(l) * adj_l))

    #d = mbit.split(',')[4] #Arduno内で計算した不快指数（使わない）

    #不快指数（気象協会基準）
    d = str(round(0.81 * float(t) + 0.01 * float(h) * (0.99 * float(t) - 14.3) + 46.3, 2))

    json_src = {'Temp':t, 'Pressure':p, 'Humidity':h, 'Lux':l, 'DI':d}
    json_data = json.dumps(json_src, indent=2)
    print(json_data)
