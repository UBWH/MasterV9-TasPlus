/*
  user_config_override.h - user configuration overrides my_user_config.h for Tasmota

  Copyright (C) 2020  Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

// force the compiler to show a warning to confirm that this file is included
#warning **** user_config_override.h: Using Settings from this File ****

/*****************************************************************************************************\
 * USAGE:
 *   To modify the stock configuration without changing the my_user_config.h file:
 *   (1) copy this file to "user_config_override.h" (It will be ignored by Git)
 *   (2) define your own settings below
 *
 ******************************************************************************************************
 * ATTENTION:
 *   - Changes to SECTION1 PARAMETER defines will only override flash settings if you change define CFG_HOLDER.
 *   - Expect compiler warnings when no ifdef/undef/endif sequence is used.
 *   - You still need to update my_user_config.h for major define USE_MQTT_TLS.
 *   - All parameters can be persistent changed online using commands via MQTT, WebConsole or Serial.
\*****************************************************************************************************/

/*
Examples :

// -- Master parameter control --------------------
#undef  CFG_HOLDER
#define CFG_HOLDER        4617                   // [Reset 1] Change this value to load SECTION1 configuration parameters to flash

// -- Setup your own Wifi settings  ---------------
#undef  STA_SSID1
#define STA_SSID1         "YourSSID"             // [Ssid1] Wifi SSID

#undef  STA_PASS1
#define STA_PASS1         "YourWifiPassword"     // [Password1] Wifi password

// -- Setup your own MQTT settings  ---------------
#undef  MQTT_HOST
#define MQTT_HOST         "your-mqtt-server.com" // [MqttHost]

#undef  MQTT_PORT
#define MQTT_PORT         1883                   // [MqttPort] MQTT port (10123 on CloudMQTT)

#undef  MQTT_USER
#define MQTT_USER         "YourMqttUser"         // [MqttUser] Optional user

#undef  MQTT_PASS
#define MQTT_PASS         "YourMqttPass"         // [MqttPassword] Optional password

// You might even pass some parameters from the command line ----------------------------
// Ie:  export PLATFORMIO_BUILD_FLAGS='-DUSE_CONFIG_OVERRIDE -DMY_IP="192.168.1.99" -DMY_GW="192.168.1.1" -DMY_DNS="192.168.1.1"'

#ifdef MY_IP
#undef  WIFI_IP_ADDRESS
#define WIFI_IP_ADDRESS   MY_IP                  // Set to 0.0.0.0 for using DHCP or enter a static IP address
#endif

#ifdef MY_GW
#undef  WIFI_GATEWAY
#define WIFI_GATEWAY      MY_GW                  // if not using DHCP set Gateway IP address
#endif

#ifdef MY_DNS
#undef  WIFI_DNS
#define WIFI_DNS          MY_DNS                 // If not using DHCP set DNS IP address (might be equal to WIFI_GATEWAY)
#endif

*/
#ifdef  FRIENDLY_NAME
#undef  FRIENDLY_NAME
#endif
#define FRIENDLY_NAME         "Tasmota-Plus"

#ifdef MODULE
#undef MODULE
#endif

//Product 
// Only ONE of the following should be enabled.
//This is set in platformio_tasmota_env.ini

#ifdef SP_STRIP
#define PRODUCT_NAME    "SP-Strip" 
#define MODULE          WEMOS          //Module 18
#endif

#ifdef  SP_PLUG
#define PRODUCT_NAME    "SP-Plug"
#define MODULE          WEMOS          //Module 18
#endif

#ifdef  SS_4CHPRO
#define PRODUCT_NAME    "SS-4CHPro"
#define MODULE          SONOFF_4CHPRO  //Module 23
#endif

#ifdef  SS_SHELLY1
#define MODULE          SHELLY1       //Module 45

#ifdef  SG_TEMP
#define PRODUCT_NAME    "SG-TEMP"
#elif defined(SG_DHT)
#define PRODUCT_NAME    "SG-DHT"
#else
#define PRODUCT_NAME    "SS-1CHPro"
#endif

#endif

#ifdef  SG_RANGE
#define PRODUCT_NAME    "SG-RANGE"
#define MODULE          SONOFF_SV       
#endif

#ifdef  SG_TEMP_AC
#define PRODUCT_NAME    "SG-TEMP-AC"
#define MODULE          SONOFF_TH       
#endif


#ifndef PRODUCT_NAME
#define PRODUCT_NAME    "tasmota"
#endif

#ifdef  SG_RANGE
#define MAX_CALCULATIONS          4     //Up to 4 calculation points
#define STRING_CALCULATION_UNITS  7     //e.g. 'litres'  (6 chars plus zero)
#else
#define MAX_WATCHDOGS    4      // Allow up to 4 watchdog timers
#endif

#ifdef  OTA_URL
#undef  OTA_URL
#endif

#define OTA_URL       "http://ubwh.com.au/tasmota/Tasmota-Plus/tasmota-" PRODUCT_NAME ".bin.gz"  // [OtaUrl]

#ifndef  USE_PING
#define USE_PING                //Include Ping
#endif
// Remove unnecessary modules
#undef USE_SHELLY_DIMMER
#undef USE_SONOFF_RF
#undef ROTARY_V1
#undef USE_RF_FLASH
#undef USE_SONOFF_SC
#undef USE_ARMTRONIX_DIMMERS
#undef USE_PS_16_DZ
#undef USE_SONOFF_IFAN
#undef USE_BUZZER
#undef USE_ARILUX_RF
#undef USE_SHUTTER
#undef USE_DEEPSLEEP
#undef USE_EXS_DIMMER
#undef USE_MY92X1
#undef USE_SM16716                              // Add support for SM16716 RGB LED controller (+0k7 code)
#undef USE_SM2135                               // Add support for SM2135 RGBCW led control as used in Action LSC (+0k6 code)
#undef USE_SONOFF_L1                            // Add support for Sonoff L1 led control
#undef USE_ELECTRIQ_MOODL                       // Add support for ElectriQ iQ-wifiMOODL RGBW LED controller (+0k3 code)
#undef USE_LIGHT_PALETTE                        // Add support for color palette (+0k7 code)
#undef USE_DGR_LIGHT_SEQUENCE                   // Add support for device group light sequencing (requires USE_DEVICE_GROUPS) (+0k2 code)
#undef USE_COUNTER                              // Enable inputs as counter (+0k8 code)
//#undef USE_DS18x20                              // Add support for DS18x20 sensors with id sort, single scan and read retry (+2k6 code)
#undef USE_I2C                                  // I2C using library wire (+10k code, 0k2 mem, 124 iram)
#undef USE_IR_REMOTE                            // Send IR remote commands using library IRremoteESP8266 and ArduinoJson (+4k3 code, 0k3 mem, 48 iram)

#endif  // _USER_CONFIG_OVERRIDE_H_
