cd C:\xampp\htdocs\bme280\bin

:シリアルポート
::set COM_BME280=COM8
::set COM_SCD30=COM9

:センサー値をJSON形式で出力
::python co2_read.py > ../co2.json
python scd41.py > ../co2.json
python bme280_and_temt6000.py > ../bme280.json

:DB更新
python ins_db.py >> ../db_err.log
