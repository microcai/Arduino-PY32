/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"
#include "PinConfigured.h"

#ifdef __cplusplus
extern "C" {
#endif

void pinMode(uint32_t ulPin, uint32_t ulMode)
{
  PinName p = digitalPinToPinName(ulPin);

  if (p != NC) {
    switch (ulMode) {
      case INPUT: /* INPUT_FLOATING */
        pin_function(p, PY32_PIN_DATA(PY32_MODE_INPUT, GPIO_NOPULL, 0));
        break;
      case INPUT_PULLUP:
        pin_function(p, PY32_PIN_DATA(PY32_MODE_INPUT, GPIO_PULLUP, 0));
        break;
      case INPUT_PULLDOWN:
        pin_function(p, PY32_PIN_DATA(PY32_MODE_INPUT, GPIO_PULLDOWN, 0));
        break;
      case INPUT_ANALOG:
        pin_function(p, PY32_PIN_DATA(PY32_MODE_ANALOG, GPIO_NOPULL, 0));
        break;
      case OUTPUT:
        pin_function(p, PY32_PIN_DATA(PY32_MODE_OUTPUT_PP, GPIO_NOPULL, 0));
        break;
      case OUTPUT_OPEN_DRAIN:
        pin_function(p, PY32_PIN_DATA(PY32_MODE_OUTPUT_OD, GPIO_NOPULL, 0));
        break;
      default:
        Error_Handler();
        break;
    }
  }
}

void digitalWrite(uint32_t ulPin, uint32_t ulVal)
{
  digitalWriteFast(digitalPinToPinName(ulPin), ulVal);
}

int digitalRead(uint32_t ulPin)
{
  return digitalReadFast(digitalPinToPinName(ulPin));
}

void digitalToggle(uint32_t ulPin)
{
  digitalToggleFast(digitalPinToPinName(ulPin));
}

#ifdef __cplusplus
}
#endif
