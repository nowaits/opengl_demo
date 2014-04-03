#pragma once

#include <Windows.h>
#include <memory>
class DrawMethod;

class OpenGLDraw {
public:
  OpenGLDraw();
  ~OpenGLDraw();
  void OnInit(HWND hwnd);

  void InitMSAA();

  void OnTimer(HWND hwnd);
  void OnPaint(HDC dc);
  void OnSize(int w, int h);

  void SetDrawEffect(DrawMethod* method);

private:
  HGLRC                       h_rc;
  std::auto_ptr<DrawMethod>   draw_;

  unsigned int                PixelFormat;
};