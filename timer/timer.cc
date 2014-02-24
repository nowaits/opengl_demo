#include <iostream>
#include <cassert>
#include "timer.h"

#define FPS 25

UINT  Timer::g_timer_msg = 0;

Timer::Timer() : 
timer_id_(0), target_thread_id_(::GetCurrentThreadId()) {
  if (g_timer_msg == 0) {
    const wchar_t msg_str[] = L"timer_call_back";
    g_timer_msg = ::RegisterWindowMessageW(msg_str);
  }

  const int spin_count = 10;
  ::InitializeCriticalSectionAndSpinCount(&cs_, spin_count);
}

Timer::~Timer() {
  Stop();
  ::DeleteCriticalSection(&cs_);
}

void Timer::Start() {
  if (timer_id_ != 0)
    return;

  TIMECAPS tc;
  //获得定时器分辨率
  if (::timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) {
    return;
  }
  UINT nResolution = min(max(tc.wPeriodMin, 1), tc.wPeriodMax);
  UINT nInterval = 1000/FPS;
  if (nInterval < nResolution)
  {
    nInterval = nResolution;
  }
  //设置定时最小分辨率
  ::timeBeginPeriod(nResolution);

  timer_id_ = ::timeSetEvent(nInterval, nResolution, 
    Timer::TimerProc, 
    (DWORD)this, TIME_PERIODIC);
}


void Timer::Stop() {
  if (timer_id_ != 0) {
    ::timeKillEvent(timer_id_);
    timer_id_ = 0;
  }
}

void Timer::OnTimer(UINT uTimerID) {

  if (::TryEnterCriticalSection(&cs_) == TRUE) {
    assert(uTimerID == timer_id_);
    ::PostThreadMessage(target_thread_id_, Timer::g_timer_msg, NULL, (LPARAM)(this));
    ::LeaveCriticalSection(&cs_);
  }
  else {
    std::cout<<"miss one frame"<<std::endl;
  }
}

void CALLBACK Timer::TimerProc(UINT uTimerID, UINT, DWORD_PTR dwUser, DWORD_PTR, DWORD_PTR) {
  Timer* timer = (Timer*)dwUser;

  if(timer)
    timer->OnTimer(uTimerID);
};