/*
   This file is part of max7219 driver for max7219 driver for WiringPi.

   max7219 driver for WiringPi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.

     max7219 driver for WiringPi is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with max7219 driver for WiringPi.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "max7219.h"
#include <wiringPiSPI.h>
#include <stdint.h>
#include <stdbool.h>

int g_max7219_channel;
int g_count;

int max7219_init(int channel, int speed, int count) {
  g_max7219_channel = channel;
  g_count = count;
  return wiringPiSPISetup(channel, speed);
}

int max7219_send_data_cascade(uint8_t *addresses, uint8_t *data, int l) {
  static unsigned char buff[4];
  int i;
  int ret;

  i = l;
  while(i--) {
    buff[2*i    ] = addresses[i];
    buff[2*i + 1] = data[i];
   }
  ret=wiringPiSPIDataRW(g_max7219_channel, buff, 2*l);
  return ret;
}

int max7219_send_data(int id, uint8_t address, uint8_t data) {
  static unsigned char buff[2*4];
  int i;

  //NOOP
  while(i < g_count) {
    buff[2*i    ] = REG_ADDR_NOOP;
    buff[2*i + 1] = 0x00;
    i++;
  }

  buff[2*id   ] = address;
  buff[2*id +1] = data;
  i++;

  return wiringPiSPIDataRW(g_max7219_channel, buff, 2*g_count);
}

int max7219_send_data_all(uint8_t address, uint8_t data) {
  static unsigned char buff[4];
  int i;
  int ret;

  i = 0;
  while(i < g_count) {
    buff[2*i    ] = address;
    buff[2*i + 1] = data;
    i++;
   }
  return wiringPiSPIDataRW(g_max7219_channel, buff, 2*g_count);
}

int max7219_set_shutdown(int id, uint8_t mode) {
  return max7219_send_data(id, REG_ADDR_SHUTDOWN, mode);
}

int max7219_set_shutdown_all(uint8_t mode) {
  return max7219_send_data_all(REG_ADDR_SHUTDOWN, mode);
}

int max7219_set_decode(int id, uint8_t mode) {
  return max7219_send_data(id, REG_ADDR_DECODE_MODE, mode);
}
int max7219_set_decode_all(uint8_t mode) {
  return max7219_send_data_all(REG_ADDR_DECODE_MODE, mode);
}

int max7219_test(int id) {
  return max7219_send_data(id, REG_ADDR_TEST, 0xFF);
}
int max7219_test_all(void) {
  return max7219_send_data_all(REG_ADDR_TEST, 0xFF);
}

int max7219_set_intensity(int id, uint8_t intensity) {
  return max7219_send_data(id, REG_ADDR_INTENSITY, intensity);
}
int max7219_set_intensity_all(uint8_t intensity) {
  return max7219_send_data_all(REG_ADDR_INTENSITY, intensity);
}
