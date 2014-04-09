#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <vector>
#include "../utils/utils.h"
void drawCenterTexture(int texture_id, float alpha);
extern GLfloat  horizontal[3][3];
extern GLfloat  vertical[3][3];
extern GLfloat  laplacian[3][3];
extern GLfloat  sobel[3][3];

void process_img(wchar_t* file_name, wchar_t* save_name) {
 
  if (glConvolutionFilter2D == NULL)
    return;

  if (glConvolutionFilter2D != NULL) {
    glConvolutionFilter2D(GL_CONVOLUTION_2D, GL_LUMINANCE,
      3, 3, GL_LUMINANCE, GL_FLOAT, laplacian);
    glEnable(GL_CONVOLUTION_2D);
    glConvolutionFilter2D(GL_CONVOLUTION_2D, GL_LUMINANCE,
      3, 3, GL_LUMINANCE, GL_FLOAT, laplacian);
    glEnable(GL_CONVOLUTION_2D);
  }

  std::vector<unsigned char> buffer;
  dcodec_utils::BitmapData bitmap;

  dcodec_utils::load_file(file_name, buffer);

  if (!dcodec_utils::parse_bmp(buffer, bitmap))
    return;

   DWORD t = GetTickCount();

  // 生成并绑定一个FBO，也就是生成一个离屏渲染对像
  GLuint fb;
  glGenFramebuffersEXT(1,&fb); 
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fb);

  GLuint tex;
  glGenTextures(1, &tex);

  // 分配数据纹理的显存空间
  glBindTexture(GL_TEXTURE_RECTANGLE_ARB, tex);
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, 
    GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, 
    GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, 
    GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, 
    GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_COLOR,GL_DECAL);

  t = GetTickCount();
  glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA,
    bitmap.w, bitmap.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &bitmap.data[0]);

  glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, 
    GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_RECTANGLE_ARB, tex, 0);

  drawCenterTexture(tex, 1);

  glDisable(GL_CONVOLUTION_2D);

  GLint rect[4];
  glGetIntegerv(GL_VIEWPORT, rect);

  dcodec_utils::BitmapData b;
  b.w = bitmap.w;rect[2];
  b.h = bitmap.h;rect[3];
  b.pixel_bytes = 4;

  b.data.resize(b.w * b.h * b.pixel_bytes);

  glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
  glReadPixels(0, 0, b.w, b.h, GL_RGBA,GL_UNSIGNED_BYTE, &b.data[0]);

  t = GetTickCount() - t;

  glEnable(GL_CONVOLUTION_2D);
  // 释放显卡内存
  glDeleteFramebuffersEXT (1,&fb);
  glDeleteTextures (1,&tex);

  

  DWORD ts = GetTickCount();

  unsigned char * pp = &b.data[0];
  for(int i = 0; i < b.h; i ++) {
    for(int j = 0; j < b.w; j ++) {
      double fff = 0;
      for(int k = 0; k < 3; k ++) {
        for (int l = 0; l < 3; l ++) {
          fff +=laplacian[k][l]* pp[i*b.w + j];
          fff +=laplacian[k][l]* pp[i*b.w + j];
          fff +=laplacian[k][l]* pp[i*b.w + j];
        }
      }

      pp[i*b.w + j] = fff/8;
    }
  }

  ts = GetTickCount() - ts;
  dcodec_utils::save_bmp(b, buffer);
  dcodec_utils::save_file(save_name, buffer);
}