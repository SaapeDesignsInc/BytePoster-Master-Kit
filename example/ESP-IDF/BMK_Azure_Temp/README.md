SAAPE BMK DEMO CODE from ESP-IDF template
====================

This is a template application to be used with [Espressif IoT Development Framework](https://github.com/espressif/esp-idf).

Please check [ESP-IDF docs](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for getting started instructions.

- Make sure you have installed and configured the [ESP-IDF](https://github.com/espressif/esp-idf)
- Clone the "BMK_AzureTemp" project to your PC 
- Clone and configure [arduino-esp32](https://github.com/espressif/arduino-esp32) as componnent of your project. 
- Update the wifi credentials and Azure IoTHub Connection String credentials in main.cpp
- run "make menuconfig"   
- run "make flash" 

### Possible compilation errors:
#### 1. Error: ESP32MQTTClient.h - No such file found

   Solution: make sure that you enable AzureIoT module in Arduino Configuration in make menuconfig

#### 2. Error: 'mbedtls_ssl_conf_psk' was not declared in this scope

   Solution: In the terminal: 

```
make menuconfig
```

```
    Component Config -> mbedTLS -> TLS Key Exchange Methods -> 
    [*] Enable pre-shared-key ciphersuits
    [*] Enable PSK based ciphersuite modes
```

## Acknowledgments

* Hat tip to  K.Townsend (Adafruit Industries) for releasing the library of MCP9808 Arduino library. Amazing work! 
** 
* Inspiration
* etc
*Code in this repository is in the Public Domain (or CC0 licensed, at your option.)
Unless required by applicable law or agreed to in writing, this
software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied.*
