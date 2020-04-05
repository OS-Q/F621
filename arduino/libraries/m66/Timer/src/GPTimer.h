#ifndef __TIMER_H__
#define __TIMER_H__

#include <Arduino.h>

typedef enum
{
  TIMER_FAST = 0x100, /* Fast Timer*/
  /* Normal Timers */
  TIMER_1,
  TIMER_2,
  TIMER_3,
  TIMER_4,
  TIMER_5,
  TIMER_6,
  TIMER_7,
  TIMER_8,
  TIMER_9,
  TIMER_END
} TimerID;

typedef enum
{
  TIMER_ONESHOT_MODE = 0,
  TIMER_REPEAT_MODE
} TimerMode;

class GPTimer
{
public:
  GPTimer(TimerID id);
  bool begin() { return m_id; }
  bool end() { return 1; }
  bool start(uint32_t interval, bool mode, Callback_Timer_OnTimer callbackFunc, void *user = NULL);
  bool stop();
  //TODO RTC ALARM
private:
  uint32_t m_id;
};

#endif
