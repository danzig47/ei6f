/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
  See the LICENSE file for details.
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

int const TEMT6000_PIN = A1; //照度センサーの入力ピンをA1に設定
int incomingByte = 0;  // 受信データ用

unsigned long delayTime;

void setup() {
    Serial.begin(9600);

    if (! bme.begin(0x76, &Wire)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
    delayTime = 10000;

}

void loop() {
  // Only needed in forced mode! In normal mode, you can remove the next line.
  bme.takeForcedMeasurement(); // has no effect in normal mode

  //PC側から要求があったときだけ値を送信する
  if (Serial.available() > 0) { // 受信したデータが存在する
    incomingByte = Serial.read(); // 受信データを読み込む
    printValues();
  }
}

void printValues() {
    float t = bme.readTemperature(); //温度

    float h = bme.readHumidity();  //湿度

    //照度センサーから値取得（TEMT6000）
    float sensor_value = analogRead(TEMT6000_PIN); // Get raw sensor reading
    float lux = sensor_value * 0.9765625; //Lux換算式

    //不快指数（気象協会基準）
    float di = 0.81 * t + 0.01 * h * (0.99 * t - 14.3) + 46.3;
    
    Serial.print(t);
    Serial.print(",");

    Serial.print(bme.readPressure() / 100.0F);  //気圧
    Serial.print(",");

    Serial.print(h);
    Serial.print(",");

    Serial.print(lux);
    Serial.print(",");

    Serial.print(di);
    Serial.println();
}
