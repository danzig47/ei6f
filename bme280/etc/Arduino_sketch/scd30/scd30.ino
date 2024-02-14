/*
  Reading CO2, humidity and temperature from the SCD30
  By: Nathan Seidle
  SparkFun Electronics
  Date: May 22nd, 2018
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  Feel like supporting open source hardware?
  Buy a board from SparkFun! https://www.sparkfun.com/products/15112

  This example prints the current CO2 level, relative humidity, and temperature in C.

  Hardware Connections:
  Attach RedBoard to computer using a USB cable.
  Connect SCD30 to RedBoard using Qwiic cable.
  Open Serial Monitor at 115200 baud.
*/

//The SCD30 has data ready every two seconds

#include <Wire.h>
#include "SparkFun_SCD30_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_SCD30

SCD30 airSensor;

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  if (airSensor.begin() == false)
  {
    //Serial.println("Air sensor not detected. Please check wiring. Freezing...");
    while (1)
      ;
  }

  //オートキャリブレーションをオン
  airSensor.setAutoSelfCalibration(true);
}

void loop()
{
  if (airSensor.dataAvailable()) {
    if (Serial.available() > 0) { // PCからデータ送信要求があるか？
      Serial.println(airSensor.getCO2());
    }
  }
}
