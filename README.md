# bbn_esp32_sensors_hub
NMEA 0183 XDR Sensors on esp32 m5stack atomS3-lite

## Hardware

- m5stack atomS3-lite:  https://shop.m5stack.com/products/atoms3-lite-esp32s3-dev-kit
- m5stack ATOMIC PortABC Extension Base: https://shop.m5stack.com/products/atomic-portabc-extension-base

## Supported Sensors

### AS3935 Lightning Detector sensor to NMEA-0183

AS3935 Lightning Detector connected to M5Stack AtomS3-Lite via i2c and one additional digital GPIO pin (G7) (interrupt)

Generates NMEA-0183 XDR sentences (USB Serial) like this:

````
$BBXDR,D,1000,M,LIGHTNING_RANGE*16
$BBXDR,X,410415,,LIGHTNING_LEVEL*4A
````

DFRobot Gravity AS3935 Lightning Detector:

https://www.dfrobot.com/product-1828.html

### Multiple Dallas Temperature 1-Wire Sensors


DS18B20 with GikFun plugin terminal board (includes required pull-up resistor for 1-wire bus)

DS18B20 data is connected to pin G8 on m5stack AtomS3-lite

Can be used for

- Engine temperature
- Exhaust temperature
- Fridge temperature
- Engine coolant temperature
- Batteries bank temperature
- MPPT controller temperature
- etc

Supports multiple 1-wire Dallas Temperature sensors.

Generates NMEA 0183 XDR and TXT sentences on USB serial 

````
$BBTXT,01,01,01,TEMPERATURE sensors found=1*0A
$BBTXT,01,01,02,TEMPERATURE found sensor address=28478546D4523ABF*1A
$BBXDR,C,23.94,C,TEMP_28478546D4523ABF*38
$BBXDR,C,23.94,C,TEMP_28478546D4523ABF*38
$BBXDR,C,23.94,C,TEMP_28478546D4523ABF*38
$BBXDR,C,23.94,C,TEMP_28478546D4523ABF*38
$BBXDR,C,24.00,C,TEMP_28478546D4523ABF*32
$BBXDR,C,24.00,C,TEMP_28478546D4523ABF*32
````

Waterproof Digital Temperature Sensor DS18B20 with GikFun plugin terminal board

https://www.amazon.com/Gikfun-DS18B20-Waterproof-Digital-Temperature/dp/B08V93CTM2

### INA219 Voltage and Current

Load and your sensor need to share common ground.

NMEA XDR Sentences:

````
$BBXDR,U,1.036,V,VOLT_INA219_2*28
$BBXDR,I,0.000,A,AMPS_INA219_2*29
$BBXDR,W,0.000,W,WATT_INA219_2*38
````

###  SGP30 Air Quality and TVOC sensor connected to M5Stack AtomS3-Lite via i2c

Generates NMEA-0183 XDR sentences (USB Serial) like this:

````
$BBXDR,X,5,,TVOC*2D
$BBXDR,X,415,,eCO2*7D
$BBXDR,X,13507,,rawH2*38
$BBXDR,X,18875,,rawEthanol*14
$BBXDR,X,7,,TVOC*2F
$BBXDR,X,416,,eCO2*7E
$BBXDR,X,13501,,rawH2*3E
$BBXDR,X,18864,,rawEthanol*14
````

Here are some TVOC levels and their associated health effects:

- 0 ppb: Good
- 220 ppb: Moderate, may cause some symptoms
- 660 ppb: Unhealthy if sensitive, more likely to cause symptoms
- 2200 ppb: Unhealthy
- 3300 ppb: Very unhealthy
- 4400 ppb: Hazardous

SGP30 Air Quality and TVOC sensor :

[M5Stack SGP30 Air Quality and TVOC sensor](https://shop.m5stack.com/products/tvoc-eco2-gas-unit-sgp30)



### Time-of-Flight Distance Ranging Sensor Unit (VL53L0X) 

Time-of-Flight Distance Ranging Sensor Unit (VL53L0X) sensor connected to M5Stack AtomS3-Lite via i2c

Generates NMEA-0183 XDR sentences (USB Serial) like this:

````
$BBXDR,D,0.2410,M,RANGE_VL53L0X*66
$BBXDR,D,0.2430,M,RANGE_VL53L0X*64

````

Time-of-Flight Distance Ranging Sensor Unit (VL53L0X) sensor :

https://shop.m5stack.com/products/tof-sensor-unit


## NMEA XDR Output

on USB-C port with baud rate 115200

````
socat stdio /dev/ttyACM1
````

## Loading Firmware

### On Bareboat Necessities (BBN) OS (full)

````
if [ -f bbn-flash-m5-hub.sh ]; then rm bbn-flash-m5-hub.sh; fi
wget https://raw.githubusercontent.com/bareboat-necessities/my-bareboat/refs/heads/master/m5stack-tools/bbn-flash-m5-hub.sh
chmod +x bbn-flash-m5-hub.sh 
./bbn-flash-m5-hub.sh -p /dev/ttyACM1
````

