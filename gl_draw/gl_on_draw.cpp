#include <windows.h>
#include <GL\gl.h>
#include "gl_on_draw.h"
#include "draw_method.h"

GLfloat kAngle = 0.0f;

//
DrawMethod* GetTestDrawMethod();

OpenGLDraw::~OpenGLDraw() {
  ::wglDeleteContext(h_rc);
}

void OpenGLDraw::OnInit(HWND hwnd) {
  PIXELFORMATDESCRIPTOR pfd;
  ZeroMemory( &pfd, sizeof(PIXELFORMATDESCRIPTOR) );
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR );
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 32;

  HDC dc = ::GetDC(hwnd);
  if(!SetPixelFormat(dc, ChoosePixelFormat(dc, &pfd ), &pfd ))
    ::DestroyWindow(hwnd);

  h_rc = ::wglCreateContext(dc);
  ::wglMakeCurrent(dc, h_rc);
  ::DeleteDC(dc);

  //ReleaseDC(hWnd, _hDC);
  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f); 
  // Useless ?
  glMatrixMode(GL_MODELVIEW);	
  glLoadIdentity();

  SetDrawEffect(GetTestDrawMethod());
}

void OpenGLDraw::OnTimer(HWND hwnd) {
  kAngle +=0.01f;
  InvalidateRect(hwnd, NULL, FALSE);
}

void OpenGLDraw::OnPaint(HDC dc) {

  ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  ::glRotatef(kAngle, 1, 1, 1);

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
  ::glLoadIdentity();	
  ::glOrtho(-1, 1.0, -1, 1.0, -1.0, 1.0);
  //::gluPerspective(45.0f,w / (GLfloat)h, 0.1f,100.0f);
}

void OpenGLDraw::SetDrawEffect(DrawMethod* method) {
  draw_.reset(method);
}