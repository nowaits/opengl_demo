#include <windows.h>
#include <GL\glew.h>
#include "gl_on_draw.h"
#include "draw_method.h"
#include <GL/wglew.h>
#include "MultiSample.h"
#include <atlbase.h>
#include <atlwin.h>
#include <math.h>
//
DrawMethod* GetTestDrawMethod();

OpenGLDraw::OpenGLDraw() {
  SetDrawEffect(GetTestDrawMethod());
  PixelFormat = 0;
}

OpenGLDraw::~OpenGLDraw() {
  ::wglDeleteContext(h_rc);
}

void OpenGLDraw::OnInit(HWND hwnd) {
  PIXELFORMATDESCRIPTOR pfd = {0};
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR );
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 32;

  HDC dc = ::GetDC(hwnd);

  if (PixelFormat == 0)
     PixelFormat = ChoosePixelFormat(dc, &pfd );
  if(!SetPixelFormat(dc, PixelFormat, &pfd ))
    ::DestroyWindow(hwnd);

  h_rc = ::wglCreateContext(dc);
  ::wglMakeCurrent(dc, h_rc);
  ::DeleteDC(dc);

  ::glClearColor( 0.0f, 0.0f, 0.0f, 1.0f); 
  // Useless ?
  ::glMatrixMode(GL_MODELVIEW);	
  ::glLoadIdentity();
  ::glewInit();

  if (draw_.get())
    draw_->OnInit();
}

void OpenGLDraw::OnTimer(HWND hwnd) {
  if (draw_.get())
    draw_->OnTimer();

  InvalidateRect(hwnd, NULL, FALSE);
}

void OpenGLDraw::OnPaint(HDC dc) {

  ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (draw_.get())
    draw_->OnDraw();

  ::glFinish();
  ::SwapBuffers(dc) ; 
}

void OpenGLDraw::OnSize(int w, int h) {
  if (h == 0)
    h = 1;

  ::glViewport(0, 0, w, h);	
  ::glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  double width = 1;
  double height = width;

  double depth_near = 3.0;

  double depth_far = depth_near + 30;

#if 0
 glFrustum(-width, width, -height, height, depth_near, depth_far);
#else
  float angle = atan(width /depth_near) * 180 / 3.1415926 * 2;

  ::gluPerspective(angle, 1, depth_near, depth_far);
#endif
  gluLookAt (0.0, 0.0, depth_near+1, .0, 0.0, 0.0, 0.0, 1.0, 0.0);

  double or_w = 0.5;

  ::glOrtho(-or_w, or_w, -or_w, or_w, 0, 0.5);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
}

void OpenGLDraw::SetDrawEffect(DrawMethod* method) {
  draw_.reset(method);
}

void OpenGLDraw::InitMSAA() {
  PIXELFORMATDESCRIPTOR pfd = {0};
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR );
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 32;
  CWindow tmp_wnd;RegisterClass;
  tmp_wnd.Create(L"OpenGL demo", NULL);    

  HDC tmp_dc = ::GetDC(tmp_wnd.m_hWnd);
  if(!SetPixelFormat(tmp_dc, ChoosePixelFormat(tmp_dc, &pfd ), &pfd ))
    ::DestroyWindow(tmp_wnd.m_hWnd);

  HGLRC gl_tmp_rc = ::wglCreateContext(tmp_dc);
  ::wglMakeCurrent(tmp_dc, gl_tmp_rc);
  ::DeleteDC(tmp_dc);

  MultiSample  sample;
  sample.SetMultiSample(4);
  
  if (sample.InitMultiSample(tmp_wnd.m_hWnd)) {
    PixelFormat = sample.GetMultiSampleFormat();
  } else {
    PixelFormat = ChoosePixelFormat(tmp_dc, &pfd );
  }

  ::wglDeleteContext(gl_tmp_rc);
  tmp_wnd.DestroyWindow();

  MSG Msg;
  while (GetMessage (&Msg, NULL, 0, 0)) {
    TranslateMessage (&Msg) ;
    DispatchMessage (&Msg) ;
  }
}
