# bbn_esp32_sensors_hub
NMEA 0183 XDR Sensors on esp32 m5stack atomS3-lite

## Hardware

- m5stack atomS3-lite:  https://shop.m5stack.com/products/atoms3-lite-esp32s3-dev-kit
- m5stack ATOMIC PortABC Extension Base: https://shop.m5stack.com/products/atomic-portabc-extension-base

## Loading Firmware

````
wget https://raw.githubusercontent.com/bareboat-necessities/my-bareboat/refs/heads/master/m5stack-tools/bbn-flash-m5-hub.sh
chmod +x bbn-flash-m5-hub.sh 
./bbn-flash-m5-hub.sh -p /dev/ttyACM1
````

