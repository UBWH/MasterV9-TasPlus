/*
  tasmota_version.h - Version header file for Tasmota

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

#ifndef _TASMOTA_VERSION_H_
#define _TASMOTA_VERSION_H_

const uint32_t VERSION = 0x09020000
                             + 0x01        //Migrate TasPlus V8->V9
                             + 0x01        //Add SG-RANGE
                             + 0x01        //ADD SG-TEMP-AC  (Sonoff TH10)
                                           //Add Configure Temp for SG-TEMP/SG-TEMP-AC (Relay on/off)
                                           //Add MqttKeepAlive
                             + 0x01        //BUG: Watchdogs now work if WiFi down
                             
                        ;
#endif  // _TASMOTA_VERSION_H_
