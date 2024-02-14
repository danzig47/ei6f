# -*- coding: utf-8 -*-

import time
import json
import datetime as dt
import pandas as pd
import sqlite3

#相対パス
r_path="../"

#DB挿入関数
def ins_db(temp, press, humi, lux, di,co2):
    # dbを作成する
    # すでに存在していれば、それにアスセスする。
    db_name = '../env_ei6f.db'
    conn = sqlite3.connect(db_name)
    # sqliteを操作するカーソルオブジェクトを作成
    cur = conn.cursor()

    #日付と時刻を生成
    today = dt.datetime.now().strftime('%Y-%m-%d')
    now_time = dt.datetime.now().strftime('%H:%M:%S')

    # テーブル構造を取得するため1件だけ取得してみる
    df = pd.read_sql_query(sql="SELECT * FROM env LIMIT 1", con=conn)
    df_ins = pd.DataFrame([
        [today, now_time, temp, press, humi, lux, di, co2]],columns=df.columns)

    df2 = pd.read_sql_query(sql="SELECT * FROM env6f LIMIT 1", con=conn)
    df2_ins = pd.DataFrame([
        [today, now_time, temp, press, humi, lux, di, co2]],columns=df2.columns)

    try:
        df_ins.to_sql('env',conn, if_exists='append', index=None)
        df2_ins.to_sql('env6f',conn, if_exists='append', index=None)
    except sqlite3.Error as e:
        print(e)
    # データベースへのコネクションを閉じる。
    conn.close()

#Main
if __name__ == '__main__':

    #気温等データ読み込み
    jsonfile = open('../bme280.json', 'r')
    bme280 = json.load(jsonfile)
    #print(bme280)

    #co2データ読み込み
    jsonfile = open('../co2.json', 'r')
    scd30 = json.load(jsonfile)
    #print(scd30['CO2'])

    t=bme280['Temp']
    p=bme280['Pressure']
    h=bme280['Humidity']
    l=bme280['Lux']
    d=bme280['DI']
    co2=scd30['CO2']
#    co2='0'

    #DBに挿入
    ins_db(t,p,h,l,d,co2)
