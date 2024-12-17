# bbn_esp32_sensors_hub
NMEA 0183 XDR Sensors on esp32 m5stack atomS3-lite

## Hardware

- m5stack atomS3-lite:  https://shop.m5stack.com/products/atoms3-lite-esp32s3-dev-kit
- m5stack ATOMIC PortABC Extension Base: https://shop.m5stack.com/products/atomic-portabc-extension-base

## Supported Sensors

### AS3935 Lightning Detector sensor to NMEA-0183

AS3935 Lightning Detector connected to M5Stack AtomS3-Lite via i2c and one additional digital GPIO pin (interrupt)

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

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

Generates NMEA 0183 XDR and TXT sentences on USB serial with 4800 baud rate

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

