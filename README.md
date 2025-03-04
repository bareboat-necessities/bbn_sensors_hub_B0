# bbn-sensors-hub-B0
NMEA 0183 XDR Sensors on esp32 m5stack atom-lite via GPIO

No soldering required. Connect sensors to i2c or specified GPIO pins. Load firmware to atom-lite.
(On Bareboat Necessites OS it's just copy-paste of a script, see below). Plug and play.

## Hardware

- m5stack atom-lite:  https://shop.m5stack.com/products/atom-lite-esp32-development-kit
- m5stack ATOMIC PortABC Extension Base: https://shop.m5stack.com/products/atomic-portabc-extension-base

### Accessories

- Grove to StemmaQT Cables for i2c, or StemmaQT to Dupont
- Grove T-Connector https://shop.m5stack.com/products/grove-t-connector-5pcs-a-pack
- Grove2Dupont Conversion Cable https://shop.m5stack.com/products/grove2dupont-conversion-cable-20cm-5pairs

(There are 3 kinds of connector different sensor could use: m5stack Grove, Adafruit Stemma QT, SparkFun Qwiic)

## Integration with SignalK

Integration with SignalK is done via NMEA XDR Parser SignalK plugin.

More: https://github.com/GaryWSmith/xdr-parser-plugin

Recommended config file for XDR Parser SignalK plugin:

https://github.com/bareboat-necessities/lysmarine_gen/blob/bookworm/install-scripts/4-server/files/xdrParser-plugin.json

## Supported Sensors

###  Ocean TDS CQRobot (Total Dissolved Solids) Meter Sensor to NMEA-0183

https://www.cqrobot.com/index.php?route=product/product&product_id=1122

M5Stack with Atom-Lite and Ocean TDS CQRobot (Total Dissolved Solids) Meter Sensor CQRSENTDS01 to NMEA-0183.

Connected to GPIO pin G7 as analog input.

Generates NMEA-0183 XDR sentences (USB Serial) like this:

Total Dissolved Solids in ppt (Parts per Thousand):

````
$BBXDR,X,0.3955,S,TDS*12
$BBXDR,X,0.3958,S,TDS*1F
$BBXDR,X,0.3952,S,TDS*15
$BBXDR,X,0.3955,S,TDS*12
````

ppm = ppt * 1000

The ideal TDS level for drinking water is 300–500 ppm, while 500 ppm
is the maximum recommended by the EPA. Water with a TDS level above 1,000 ppm
is not considered safe to drink, and levels above 2,000 ppm may
require a filtration system.


### Resistance sensor with M5Stack Atom-Lite

In order to measure the resistance you can measure voltage using ADC (analog) input esp32 pin on a voltage divider circuit.

Voltage divider circuit consists of:

- Resistor of a known resistance
- Sensor's resistor for which resistance is to be measured
- Known reference voltage (3.3v for esp32 case) applied to those two resistors connected in series

Voltage is measured on ADC (analog) input pin of esp32 connected in between those two resistors.

Ohm Law can be used to calculate unknown resistance from voltage drop (knowing reference voltage and reference resistor resistance)

There are two kinds of configurations for this circuit:

Either the variable resistor is close to GND (DOWNSTREAM) or it is closer to VCC (UPSTREAM).


![image](img/VoltageDivider.png)


$$
\begin{flalign}
\text{ Downstream: } \newline \newline
&  \large {V _{ref} \over {R _{ref} + R _{sensor}}} = {V _{meas} \over {R _{sensor}}} \text{ } \Rightarrow \text{ }
R _{sensor} = {R _{ref} {V _{meas} \over {V _{ref} - V _{meas}}}} &
\end{flalign}
$$



$$
\begin{flalign}
\text{ Upstream: } \newline \newline
&  \large {V _{ref} \over {R _{ref} + R _{sensor}}} = {V _{meas} \over {R _{ref}}} \text{ } \Rightarrow \text{ }
R _{sensor} = {R _{ref} {{V _{ref} - V _{meas}} \over V _{meas}}} &
\end{flalign}
$$


#### esp32 ADC

esp32 ADC is not the best:

- The ESP32 has two 12-bit ADCs
- Noisy (can be corrected by statistical sampling which will reduce sampling rate for accurate measurements)
- Non-linear (can be corrected by polynomial approximation)
- Almost ignores ranges < 0.14v and > 2.6v
- The ESP32 ADC can measure voltage levels between 0 V and 3.3 V. The measured voltage is assigned a value between 0 and 4095, with 0 V corresponding to 0 and 3.3 V corresponding to 4095
- ADCs in the esp32 have an attenuator stage at their inputs; the suggested range for 11Db attenuation is 2600mV at best (even though the ADC's range is 0-3.3v)
- However, the output can be made accurate to within 1% on input range of 0.14 to 2.6 volts


#### For precise measurements use external ADC

Examples:
- ADS1115  https://docs.m5stack.com/en/unit/vmeter
- INA219   https://www.adafruit.com/product/904

#### Resistive boat sensors

There are two types of commonly used resistance based sensors:
- European 0-190 ohms range (often 10-180 ohms working range)
- American Standard 240-33 ohms

Examples:

- Fuel level (10-180 Ohm or 0-190 Ohm range)
- Oil pressure
- Rudder position (10-180 Ohms)
- Trim
- Resistive Temperature Sensors

Constraints for selecting a reference resistor size for these types of sensors:

$$
\begin{flalign}
& V _{ref} = 3.3 \newline &
8 \lt  R _{sensor} \lt 240  \newline &
0.14 \lt  V _{meas} \lt 2.6 &
\end{flalign}
$$

Appropriate sizes are (in Ohms):

$$
\begin{flalign}
& \text{ Upstream: } \newline &
15  \lt  R _{ref} \lt 33 &
\end{flalign}
$$

$$
\begin{flalign}
& \text{ Downstream: } \newline &
68  \lt  R _{ref} \lt 220 &
\end{flalign}
$$

Pick up resistor with lower % tolerance.

#### NMEA 0183 XDR Sentences for resistance

NMEA 0183 is on USB serial with baud rate of 38400

Example sentences:

````
$BBXDR,G,135.4,O,Ohms_esp32*6A
$BBXDR,G,137.9,O,Ohms_esp32*65
$BBXDR,G,137.6,O,Ohms_esp32*6A
$BBXDR,G,137.6,O,Ohms_esp32*6A
$BBXDR,G,138.1,O,Ohms_esp32*62
$BBXDR,G,138.3,O,Ohms_esp32*60
````

#### Ready made voltage divider PCBs

There are numerous ready made voltage
divider PCBs. Look for

- Grove Voltage Divider with adjustable gain
- DFRobot DFR0051 Voltage Divider
- Phidgets 1121 Voltage Divider


### INA219 Voltage and Current sensors (up to four on secondary i2c bus)

Load and your sensor need to share common ground.

NMEA XDR Sentences:

````
$BBXDR,U,1.036,V,VOLT_INA219_2*28
$BBXDR,I,0.000,A,AMPS_INA219_2*29
$BBXDR,W,0.000,W,WATT_INA219_2*38
````

https://www.adafruit.com/product/904


### M5Stack 4-20mA current sensor to NMEA-0183 (on secondary i2c bus)

M5Stack Analog to I2C Unit (4-20mA Input) connected to M5Stack Atom-Lite via i2c

Can be used with many industrial 4-20 mAmps current sensors.

Ex:
- Tank level

Generates NMEA-0183 XDR sentences (USB Serial) like this:

````
$BBXDR,I,0.00480,A,AMPS*6B
$BBXDR,I,0.00481,A,AMPS*6A
````

Analog to I2C Unit 4-20mA Input (STM32G030)

https://shop.m5stack.com/products/ain4-20ma-unit

Would be useful for fluid level sensors like this one:

https://www.amazon.com/4-20mA-Liquid-Sensor-Throw-Sensors/dp/B07WDK2PRN
(Two wires from that sensor connect to IN+ and IN- on M5Stack Unit and on same terminal the current loop need to be powered from some DC power source)


### Voltmeter on m5stack Atom with ADS1115 M5Stack Voltmeter (on secondary i2c bus)


M5Stack Voltmeter unit connected to M5Stack Atom-Lite via i2c

Generates NMEA-0183 XDR sentences (USB Serial) like this:

````
$BBXDR,U,12.634,V,VOLT*50
$BBXDR,U,12.633,V,VOLT*57
````

The code is set up to measure 12 V circuits. You can easily modify it for other voltage ranges.

M5Stack Voltmeter unit:

https://shop.m5stack.com/products/voltmeter-unit-ads1115


### M5Stack DLight Illuminance sensor 

M5Stack DLight illuminance sensor connected to M5Stack Atom-Lite via i2c

Generates NMEA-0183 XDR sentences (USB Serial) like this:

````
$BBXDR,X,132.0,L,ILLU*68
$BBXDR,X,128.0,L,ILLU*63
````

M5Stack DLight illuminance sensor :

https://shop.m5stack.com/products/dlight-unit-ambient-light-sensor-bh1750fvi-tr


## NMEA XDR Output

on USB-C port with baud rate 38400

````
stty -F /dev/ttyUSB0 38400
socat stdio /dev/ttyUSB0
````

## Loading Firmware

### On Bareboat Necessities (BBN) OS (full)

````
# shutdown signalk
sudo systemctl disable signalk
sudo systemctl stop signalk

if [ -f bbn-flash-sensors-hub-B0.sh ]; then rm bbn-flash-sensors-hub-B0.sh; fi
wget https://raw.githubusercontent.com/bareboat-necessities/my-bareboat/refs/heads/master/m5stack-tools/bbn-flash-sensors-hub-B0.sh
chmod +x bbn-flash-sensors-hub-B0.sh
./bbn-flash-sensors-hub-B0.sh -p /dev/ttyUSB0
````

