#include <windows.h>
#include <GL\glew.h>
#include "gl_on_draw.h"
#include "draw_method.h"
#include <GL/wglew.h>
#include "MultiSample.h"
#include <atlbase.h>
#include <atlwin.h>
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

#if 1

  glMatrixMode(GL_PROJECTION);

  ::glViewport(0, 0, w, h);	
  ::gluOrtho2D(-1, 1, 1, -1);
  //::gluPerspective(0.0f, (GLfloat)w / (GLfloat)h, 0.1f,100.0f);

  glMatrixMode (GL_MODELVIEW);
#else
  int min_w = w < h ? w : h;
  ::glViewport((w - min_w)/2, (h - min_w)/2,  min_w, min_w);	

  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
// 
//   if (w <= h)
// 
//     glOrtho(0, 1.5, 0, 1.5 * (GLfloat)h/(GLfloat)w, -10.0, 10.0);
// 
//   else
// 
//     glOrtho(0, 1.5*(GLfloat)w/(GLfloat)h, 0, 1.5, -10.0, 10.0);
#endif
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
