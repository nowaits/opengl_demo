#include <windows.h>
#include "gl_draw\gl_on_draw.h"
#include "gl_draw\draw_method.h"
#include "timer\timer.h"

const wchar_t*  title   = L"OpenGL demo";
const wchar_t*  caption = L"OpenGL demo";
static HWND     g_hwnd  = NULL;
Timer           g_timer;

std::auto_ptr<OpenGLDraw> gl_draw(new OpenGLDraw);

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
  case WM_PAINT: 
    {
      PAINTSTRUCT ps;
      HDC dc = BeginPaint(hwnd, &ps);
      gl_draw->OnPaint(dc);
      EndPaint(hwnd, &ps);
    }
    break;
  case WM_SIZE: 
    {
      gl_draw->OnSize(LOWORD(lParam), HIWORD(lParam));
      break;
    }
  case WM_DESTROY:
    PostQuitMessage (0) ;
    return 0 ;
  default:
    break;
  }
  return DefWindowProc (hwnd, message, wParam, lParam) ;
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
  HWND         hwnd ;
  MSG          msg ;
  WNDCLASS     wndclass ;

  wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
  wndclass.lpfnWndProc   = WndProc ;
  wndclass.cbClsExtra    = 0 ;
  wndclass.cbWndExtra    = 0 ;
  wndclass.hInstance     = hInstance ;
  wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
  wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
  wndclass.hbrBackground = (HBRUSH) GetStockObject (GRAY_BRUSH ) ;
  wndclass.lpszMenuName  = NULL ;
  wndclass.lpszClassName = title ;

  if (!RegisterClass (&wndclass)) {
    return 0 ;
  }

  hwnd = CreateWindow (title,                  // window class name
    caption, // window caption
    WS_OVERLAPPEDWINDOW,        // window style
    CW_USEDEFAULT,              // initial x position
    CW_USEDEFAULT,              // initial y position
    CW_USEDEFAULT,              // initial x size
    CW_USEDEFAULT,              // initial y size
    NULL,                       // parent window handle
    NULL,                       // window menu handle
    hInstance,                  // program instance handle
    NULL) ;                     // creation parameters

  gl_draw->OnInit(hwnd);
  ShowWindow (hwnd, iCmdShow) ;
  UpdateWindow (hwnd) ;
  g_hwnd = hwnd;
  g_timer.Start();

  while (GetMessage (&msg, NULL, 0, 0)) {
    if (msg.message == Timer::g_timer_msg) {
      gl_draw->OnTimer(hwnd);
    }
    TranslateMessage (&msg) ;
    DispatchMessage (&msg) ;
  }
  return (int)msg.wParam ;
}
