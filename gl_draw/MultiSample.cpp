
#include "MultiSample.h"

#include <gl\glew.h>
#include <GL\wglew.h>
#include <string>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MultiSample::MultiSample() : Multisample(16), multisampleSupportted(false), 
MultiSampleFormat(0), numofFormats(0){
  memset(pixelformat,0, 20*sizeof(int));
}

MultiSample::~MultiSample(){}

//NEHE #46
// WGLisExtensionSupported: This Is A Form Of The Extension For WGL
bool MultiSample::WGLisExtensionSupported(const char *extension) {
  const size_t extlen = strlen(extension);

  // Try To Use wglGetExtensionStringARB On Current DC, If Possible
  PROC wglGetExtString = wglGetProcAddress("wglGetExtensionsStringARB");

  std::string supported;

  if (wglGetExtString) {
    char* str = ((char*(__stdcall*)(HDC))wglGetExtString)(wglGetCurrentDC());
    if (str)
      supported = str;
  }

  // If That Failed, Try Standard Opengl Extensions String
  if (supported.empty())
    supported = (char*)glGetString(GL_EXTENSIONS);

  size_t pos = supported.find(extension);

  return supported.find(extension) != std::string::npos;
}

bool MultiSample::InitMultiSample(HWND hwnd){
  multisampleSupportted = WGLisExtensionSupported("WGL_ARB_multisample");

  if(!multisampleSupportted)
  {
    multisampleSupportted =multisampleSupportted;
    //  return false;
  }

  PFNWGLCHOOSEPIXELFORMATARBPROC wglewChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");

  HDC hdc = ::GetDC(hwnd);

  float	fAttributes[] = {0,0};
  int iAtributes[] = 
#if 1
  {
    WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
      WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
      WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
      WGL_COLOR_BITS_ARB, 24,
      WGL_ALPHA_BITS_ARB, 8,
      WGL_DEPTH_BITS_ARB, 16,
      WGL_STENCIL_BITS_ARB, 0,
      WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
      WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
      WGL_SAMPLES_ARB, Multisample,   //1< <=2  - 16F(20-64),// 2< <=4  - 12F, // 4< <=8  - 8F, 8< <=16 -4F, 
      0,0
  };
#else
  {  
    WGL_SUPPORT_OPENGL_ARB, 1, // Must support OGL rendering  
      WGL_DRAW_TO_WINDOW_ARB, 1, // pf that can run a window  
      WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB, // must be HW accelerated  
      WGL_COLOR_BITS_ARB,     32, // 8 bits of each R, G and B  
      WGL_DEPTH_BITS_ARB,     24, // 24 bits of depth precision for window, 典型情况下深度缓冲区都是24位的,试了几台机器都不支持32位深度缓冲区  
      WGL_DOUBLE_BUFFER_ARB,GL_TRUE, // Double buffered context  
      WGL_PIXEL_TYPE_ARB,      WGL_TYPE_RGBA_ARB, // pf should be RGBA type  
      WGL_STENCIL_BITS_ARB, 8,//开启模板缓冲区,模板缓冲区位数=8  
      WGL_SAMPLE_BUFFERS_ARB, GL_TRUE, // MSAA on,开启多重采样  
      WGL_SAMPLES_ARB,        Multisample, // 4x MSAA ,多重采样样本数量为4  
      0, 0
  }; // NULL termination  
#endif

  if(!wglewChoosePixelFormatARB(hdc, iAtributes, fAttributes, 20*2 , pixelformat, &numofFormats)) {
    multisampleSupportted = false;
    return false;
  }
  if(numofFormats <= 0)
    return false;

  MultiSampleFormat = pixelformat[0];
  return true;
}