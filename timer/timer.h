#pragma once
#include <windows.h>
#pragma comment(lib, "winmm")

class Timer {
public:
  Timer();
  ~Timer();
  void Start();
  void Stop();

  static void CALLBACK TimerProc(UINT, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR);

private:
  void OnTimer(UINT uTimerID);

private:
  UINT              timer_id_;

  DWORD             target_thread_id_;
  CRITICAL_SECTION  cs_;
public:
  static UINT       g_timer_msg;
};