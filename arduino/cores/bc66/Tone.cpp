/*
  Tone.cpp
  BC66
    Created on: 15.12.2019
    Author: Redferne Bellini

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"

#define DEBUG_TONE 
//DBG

void tone(uint8_t _pin, unsigned int frequency, unsigned long duration) {

  if (frequency == 0) {
    noTone(_pin);
    return;
  }
  uint32_t period = 32000 / frequency; // (pwmSrcClk/pwmDiv)
  uint32_t high = period / 2;
  uint32_t low = period - high;

  switch (_pin)
  {
    case PWM0:
    case PWM1:
    case PWM2:
    {
      // Frequency = (pwmSrcClk/pwmDiv) / (lowPulseNum+highPulseNum)
      int res = Ql_GPIO_Uninit((Enum_PinName) _pin);
      if (res)
          DEBUG_TONE("[TONE] Ql_GPIO_Uninit: %d\n\r", res);

      res = Ql_PWM_Init( (Enum_PinName) _pin, PWMSOURCE_32K, PWMSOURCE_DIV2, low, high);
      if (res)
          DEBUG_TONE("[TONE] Ql_PWM_Init: %d\n\r", res);
      res = Ql_PWM_Output((Enum_PinName) _pin, true);
      if (res)
          DEBUG_TONE("[TONE] Ql_PWM_Output: %d\n\r", res);
    }
    break;
  }
}

void noTone(uint8_t _pin) {
  switch (_pin)
  {
    case PWM0:
    case PWM1:
    case PWM2:
    {
      Ql_PWM_Uninit((Enum_PinName) _pin);
    }
  }
}
