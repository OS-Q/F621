
#include <Arduino.h>

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
  uint32_t init_time = micros();
  uint32_t curr_time = init_time;
  uint32_t max_time = init_time + timeout;
  int pin_state = 0;

  /* read GPIO info */
  pin_state = digitalRead(pin);

  // wait for any previous pulse to end
  while ((pin_state == state) && (curr_time < max_time))
  {
    curr_time = micros();
    pin_state = digitalRead(pin);
  }

  // wait for the pulse to start
  while ((pin_state != state) && (curr_time < max_time))
  {
    curr_time = micros();
    init_time = curr_time;
    pin_state = digitalRead(pin);
  }

  // wait for the pulse to stop
  while ((pin_state == state) && (curr_time < max_time))
  {
    curr_time = micros();
    pin_state = digitalRead(pin);
  }

  if (curr_time < max_time)
  {
    return (curr_time - init_time);
  }
  else
  {
    return 0;
  }
}
