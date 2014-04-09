#include "draw_test.h"
#include <Windows.h>
#include <gl\glew.h>
#include <stdlib.h>
#include "..\utils\utils.h"
#include <GL/glut.h>
DrawMethod* GetTestDrawMethod() {
  return new DrawTexture;
}

void DrawSample::OnInit() {
}

void DrawSample::OnDraw() {
  glPushMatrix();
  glLoadIdentity();
  glColor4f(1.0f,1.0f,0.0f,1.0f);
  glBegin(GL_LINE_LOOP);	
  glVertex3f(-0.7f,-0.7f,0.0f);
  glVertex3f(0.1f,-0.7f,0.0f);
  glVertex3f(0.1f,0.7f,0.0f);
  glVertex3f(-0.7f,0.7f,0.0f);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  // glTranslatef(0.64f,0.0f,-10.0f);
  glColor4f(0.18f,0.18f,0.2f,1.0f);
  glBegin(GL_TRIANGLES);
  glVertex3f( 0.0f, 1.0f, 0.0f);	// Top
  glVertex3f(-1.0f,-1.0f, 0.0f);	// Bottom Left
  glVertex3f( 1.0f,-1.0f, 0.0f);	// Bottom Right
  glEnd();
  glPopMatrix();
}

// 二十四面体
void DrawIcosahedrons::OnInit()  {

}

void DrawIcosahedrons::OnDraw() {
  const float X =  .525731112119133606f;
  const float Z = .850650808352039932f;  
  static GLfloat vdata [12][3] ={  
    {-X,0.0,Z},{X,0.0,Z},{-X,0.0,-Z},{X,0.0,-Z},  
    {0.0,Z,X},{0.0,Z,-X},{0.0,-Z,X},{0.0,-Z,-X},  
    {Z,X,0.0},{-Z,X,0.0},{Z,-X,0.0},{-Z,-X,0.0}  
  };  
  static GLuint tindices [20][3] ={  
    {1,4,0},{4,9,0},{4,5,9},{8,5,4},{1,8,4},  
    {1,10,8},{10,3,8},{8,3,5},{3,2,5},{3,7,2},  
    {3,10,7},{10,6,7},{6,11,7},{6,0,11},{6,1,0},  
    {10,1,6},{11,0,9},{2,11,9},{5,2,9},{11,2,7}  
  };

  ::glPolygonMode(GL_FRONT, GL_LINE);
  ::glPolygonMode(GL_BACK, GL_LINE);
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  //gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glPushMatrix();
  // glTranslatef(0.64f,0.0f,-10.0f);
  glColor4f(0.18f,0.18f,0.2f,1.0f);
  glBegin(GL_POLYGON);
  for (int i =0;i <20;i++){  
    /*color information here */ 
    glColor3f(1.0, 0, 0);
    //glColor3f((rand()%1000)/1000.0,(rand()%1000)/1000.0, (rand()%1000)/1000.0, (rand()%1000)/1000.0);

    glNormal3fv(&vdata [tindices [i][0]][0]);
    glVertex3fv(&vdata [tindices [i][0]][0]); 
    // glColor3f((rand()%1000)/1000.0,(rand()%1000)/1000.0, (rand()%1000)/1000.0, (rand()%1000)/1000.0);
    glColor3f(0.0, 1.0, 0);
    glNormal3fv(&vdata [tindices [i][0]][0]);
    glVertex3fv(&vdata [tindices [i][1]][0]); 
    //   glColor3f((rand()%1000)/1000.0,(rand()%1000)/1000.0, (rand()%1000)/1000.0, (rand()%1000)/1000.0);
    glColor3f(0.0, 0, 1.0);
    glNormal3fv(&vdata [tindices [i][0]][0]);
    glVertex3fv(&vdata [tindices [i][2]][0]);  
  }  
  glEnd(); 
  glPopMatrix();
}



// cube
struct Point {
  GLfloat position[3];
  GLfloat color[3];
  int     id;
};

struct Face {
  // 点索引
  GLint points[4];
  // 法向量
  GLfloat normal[3];
  int     id;
};

// 将立方体的八个顶点保存到一个数组里面
Point vertexs[] = {
  -0.5f, -0.5f, -0.5f,  0, 0, 1,    0,
  0.5f, -0.5f, -0.5f,   0, 1, 1,    1,
  -0.5f,  0.5f, -0.5f,  1, 0, 1,    2,
  0.5f,  0.5f, -0.5f,   1, 1, 1,    3,

  -0.5f, -0.5f, 0.5f,   0.5, 0, 1,  4,
  0.5f, -0.5f,  0.5f,   0, 1, 0.5,  5,
  -0.5f,  0.5f,  0.5f,  0, 0.5, 1,  6,
  0.5f,  0.5f,  0.5f,   0, 0, 0.5,  7,
};

Face faces[] = {
  0, 2, 3, 1,   0, 0, -1.0f,    0,
  0, 4, 6, 2,   -1.0f, 0, 0,    1,
  0, 1, 5, 4,   0, -1.0f, 0,    2,
  4, 5, 7, 6,   0, 0, 1.0f,     3,
  1, 3, 7, 5,   1.0f, 0, 0,     4,
  2, 6, 7, 3,   0, 1.0f, 0,     5,
};

struct PointData {
  GLfloat vector[3];
  GLfloat normal[3];
  GLfloat color[3];
};

PointData g_points[24];
GLint g_index_list[24];

DrawCube::DrawCube(DrawWays draw_ways) 
: draw_ways_(draw_ways), roate_angle_(0.0f) {
  for(int i = 0 ; i < _countof(faces); i ++) {
    for(int j = 0; j < 4; j ++) {
      int index = faces[i].points[j];

      int offset = 4 * i + j;

      g_index_list[offset] = offset;
      g_points[offset].vector[0] = vertexs[index].position[0];
      g_points[offset].vector[1] = vertexs[index].position[1];
      g_points[offset].vector[2] = vertexs[index].position[2];

      g_points[offset].normal[0] = faces[i].normal[0];
      g_points[offset].normal[1] = faces[i].normal[1];
      g_points[offset].normal[2] = faces[i].normal[2];

      g_points[offset].color[0] = vertexs[index].color[0];
      g_points[offset].color[1] = vertexs[index].color[1];
      g_points[offset].color[2] = vertexs[index].color[2];
    }
  }
}

void DrawCube::OnInit() {
  glClearColor(0.0f,0.0f,0.0f,0.0f);   //清理颜色为黑色
  glShadeModel(GL_SMOOTH);     //使用平滑明暗处理
  glEnable(GL_DEPTH_TEST);     //剔除隐藏面
  glEnable(GL_CULL_FACE);      //不计算多边形背面
  glFrontFace(GL_CCW);      //多边形逆时针方向为正面
  glEnable(GL_LIGHTING);      //启用光照

  float legAngle[2]={0.0f,0.0f};
  float armAngle[2]={0.0f,0.0f};
  float ambientLight[]={0.3f,0.5f,0.8f,1.0f};  //环境光
  float diffuseLight[]={0.25f,0.25f,0.25f,1.0f}; //散射光
  float lightPosition[]={0.0f,1.0f,1.0f,0.0f}; //光源位置
  //材质变量
  float matAmbient[]={1.0f,1.0f,1.0f,1.0f};
  float matDiff[]={1.0f,1.0f,1.0f,1.0f};

  //为LIGHT0设置析质
  glMaterialfv(GL_FRONT,GL_AMBIENT,matAmbient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,matDiff);
  //现在开始调协LIGHT0
  glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight); //设置环境光分量
  glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight); //设置散射光分量
  glLightfv(GL_LIGHT0,GL_POSITION,lightPosition); //设置光源在场景中的位置
  //启用光
  glEnable(GL_LIGHT0);

  if (draw_ways_ == DRAW_ARRAYS) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(PointData), g_points);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(PointData), (const GLubyte *)(g_points) + sizeof(GLfloat)*3);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, sizeof(PointData), (const GLubyte *)(sizeof(GLfloat)*3 *2));
  }
  else if (draw_ways_ == VBO) {
    GLuint vertex_buffer;
    GLuint index_buffer;

    // 分配一个缓冲区，并将顶点数据指定到其中
    glGenBuffersARB(1, &vertex_buffer);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertex_buffer);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB,
      sizeof(g_points), g_points, GL_STATIC_DRAW_ARB);

    // 分配一个缓冲区，并将序号数据指定到其中
    glGenBuffersARB(1, &index_buffer);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, index_buffer);
    glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,
      sizeof(g_index_list), g_index_list, GL_STATIC_DRAW_ARB);


    // 指定顶点数据
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(PointData), (const GLubyte *)0);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(PointData), (const GLubyte *)(sizeof(GLfloat)*3));

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, sizeof(PointData), (const GLubyte *)(sizeof(GLfloat)*3 *2));
  }
}

void drawCube(float w) {

  w /= 2;
  // 将立方体的八个顶点保存到一个数组里面
  Point vertexs[] = {
    -w, -w, -w,   0, 0, 1,    0,
    w,  -w, -w,   0, 1, 1,    1,
    -w,  w, -w,   1, 0, 1,    2,
    w,   w, -w,   1, 1, 1,    3,

    -w, -w,  w,   0.5, 0, 1,  4,
     w, -w,  w,   0, 1, 0.5,  5,
    -w,  w,  w,   0, 0.5, 1,  6,
     w,  w,  w,   0, 0, 0.5,  7,
  };

  Face faces[] = {
    0, 2, 3, 1,   0, 0, -1.0f,    0,
    0, 4, 6, 2,   -1.0f, 0, 0,    1,
    0, 1, 5, 4,   0, -1.0f, 0,    2,
    4, 5, 7, 6,   0, 0, 1.0f,     3,
    1, 3, 7, 5,   1.0f, 0, 0,     4,
    2, 6, 7, 3,   0, 1.0f, 0,     5,
  };

  PointData points[24];
  GLint index_list[24];

  float current_color[4];
  ::glGetFloatv(GL_CURRENT_COLOR, current_color);

  for(int i = 0 ; i < _countof(faces); i ++) {
    for(int j = 0; j < 4; j ++) {
      int index = faces[i].points[j];

      int offset = 4 * i + j;

      index_list[offset] = offset;
      points[offset].vector[0] = vertexs[index].position[0];
      points[offset].vector[1] = vertexs[index].position[1];
      points[offset].vector[2] = vertexs[index].position[2];

      points[offset].normal[0] = faces[i].normal[0];
      points[offset].normal[1] = faces[i].normal[1];
      points[offset].normal[2] = faces[i].normal[2];
#if 0
      points[offset].color[0] = vertexs[index].color[0];
      points[offset].color[1] = vertexs[index].color[1];
      points[offset].color[2] = vertexs[index].color[2];
#else
      points[offset].color[0] = current_color[0];
      points[offset].color[1] = current_color[1];
      points[offset].color[2] = current_color[2];
#endif
    }
  }
  GLuint vertex_buffer;
  GLuint index_buffer;

  // 指定顶点数据
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, sizeof(PointData), (const GLubyte *)(points));

  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, sizeof(PointData), (const GLubyte *)((const GLubyte *)(points) + sizeof(GLfloat)*3));

  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3, GL_FLOAT, sizeof(PointData), (const GLubyte *)((const GLubyte *)(points) + sizeof(GLfloat)*3 *2));

   glShadeModel(GL_SMOOTH);     //使用平滑明暗处理
   glEnable(GL_DEPTH_TEST);     //剔除隐藏面
   glEnable(GL_CULL_FACE);      //不计算多边形背面
   glFrontFace(GL_CCW);      //多边形逆时针方向为正面

  GLint g[2];
  ::glGetIntegerv(GL_POLYGON_MODE, g);

  ::glPolygonMode(GL_FRONT, GL_LINE);
  ::glPolygonMode(GL_BACK, GL_LINE);

  glDrawElements(GL_QUADS,
    sizeof(index_list)/sizeof(index_list[0]), GL_UNSIGNED_INT, index_list);
  ::glPolygonMode(GL_FRONT, g[0]);
  ::glPolygonMode(GL_BACK, g[1]);
}

void DrawCube::OnDraw() {
  // DrawCubess(0, 0, 0);return;;
   glColor3f (1.0, 1.0, 1.0);
  //glLoadIdentity ();             /* clear the matrix */
  /* viewing transformation  */
  // gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  // glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
  ::glPolygonMode(GL_FRONT, GL_LINE);
   ::glPolygonMode(GL_BACK, GL_POINT);
  glLoadIdentity();     //复位旋转角度计数器

  ::glRotatef(roate_angle_, 1, 1, 1);
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);

  DrawInner();
}
void DrawCube::OnTimer() {
  roate_angle_ += 3;
}

void DrawCube::DrawInner() {
  switch (draw_ways_) {
case VERTEXS:
  {
    for(int i = 0 ; i < sizeof(g_index_list)/sizeof(g_index_list[0]); i += 4) {
      glBegin(GL_QUADS);
      for(int j = i; j < i + 4; j ++) {
        int index = g_index_list[j];       
        glNormal3f(
          g_points[index].normal[0], 
          g_points[index].normal[1], 
          g_points[index].normal[2]);

        glVertex3f(
          g_points[index].vector[0], 
          g_points[index].vector[1], 
          g_points[index].vector[2]);
      }
      glEnd();
    }
  }
  break;
case DRAW_ARRAYS:
  {
    glDrawElements(GL_QUADS,
      sizeof(g_index_list)/sizeof(g_index_list[0]), 
      GL_UNSIGNED_INT, g_index_list);
  }
  break;
case VBO:
  {
    glDrawElements(GL_QUADS, sizeof(g_index_list)/sizeof(g_index_list[0]), GL_UNSIGNED_INT, NULL);
  }
  break;
default:
  break;
  }
}

//////////////////////////////////////////////////////////////////////////

GLfloat  horizontal[3][3] = 
{
  { 0, -1, 0 },
  { 0,  1, 0 },
  { 0,  0, 0 }
};

GLfloat  vertical[3][3] =
{
  {  0, 0, 0 },
  { -1, 1, 0 },
  {  0, 0, 0 }
};

GLfloat  laplacian[3][3] = {
  { -0.125, -0.125, -0.125 },
  { -0.125,  1.0  , -0.125 },
  { -0.125, -0.125, -0.125 },
};

GLfloat  sobel[3][3] =
{
  { -1, -2, -1 },
  { 0, 0, 0 },
  {  1, 2, 1 }
};

DrawTexture::DrawTexture(DrawWays draw_ways) 
: draw_ways_(draw_ways), roate_angle_(0.0f) {
}

void DrawTexture::OnInit() {  
  glClearColor (0.0, 0.0, 0.0, 0.0);

  glConvolutionFilter2D(GL_CONVOLUTION_2D, GL_LUMINANCE,
    3, 3, GL_LUMINANCE, GL_FLOAT, sobel);
  glEnable(GL_CONVOLUTION_2D);
}

void drawTexture(int texture_id, float rc[4], float alpha) {
  float f = - 0;
  float vectorCoords[][2] = {
    {rc[0], rc[1]}, 
    {rc[2], rc[1]}, 
    {rc[2], rc[3]},
    {rc[0], rc[3]},
  };

  int index[_countof(vectorCoords)] = {0};

  for(int i = 0; i < _countof(vectorCoords); i ++)
    index[i] = i;

  float normal[][3] = {
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
  };

  float l = 0;
  float t = 0;
  float r = 1;
  float b = 1;

  float texCoords[][2] = {
    {l, t}, {r, t}, {r, b}, {l, b},
  };

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_TEXTURE_2D);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, vectorCoords);

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

  GLfloat fColor[][4] = { 
    {1.0, 1.0, 1.0, alpha},
    {1.0, 1.0, 1.0, alpha},
    {1.0, 1.0, 1.0, alpha},
    {1.0, 1.0, 1.0, alpha},
  };

  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, 0, normal);

  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(4, GL_FLOAT, 0, fColor);

  glDrawElements(GL_TRIANGLE_FAN, _countof(index), GL_UNSIGNED_INT, index);
}

void drawCenterTexture(int texture_id, float alpha) {
  GLint rect[4];
  glGetIntegerv(GL_VIEWPORT, rect);

  glBindTexture(GL_TEXTURE_2D, texture_id);

  float ww, hh;

  glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &ww);
  glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &hh);

  float w = 2.0 * ww/rect[2];
  float h = w * hh / ww;
  float x = -w/2;
  float y = -h/2;

  float rc[] = {x, y, x + w, y + h};
  ::glPushMatrix();
  ::glRotatef(alpha*90, 0, 0, 1);
  ::drawTexture(texture_id, rc, alpha);
  ::glPopMatrix();
}

void DrawTexture::OnDraw() {
  POINT pt = {0, 0};

  if (textures_.empty()) {
    std::vector<std::wstring> file_names;
    file_names.push_back(L"texture_test.bmp");
    file_names.push_back(L"texture_test2.bmp");
    LoadGLTextures(file_names);
  }

  drawCenterTexture(textures_[0], roate_angle_/3);
  if (roate_angle_/3 > 1)
    roate_angle_ = 0;

#if 0
  glClear(GL_COLOR_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glColor4f(1, 0, 0, 0.5);
  glRectf(-0.5, -0.5, 0.25, 0.25);
  

  float al = 0.3;
  glColor4f(1, 0, 0, al);


  glRectf(-0.25, -0.25, 0.5, 0.5);
#endif
  glPushMatrix();
  glEnable(GL_DEPTH_TEST);

  GLint rect[4];
  glGetIntegerv(GL_VIEWPORT, rect);

  float w = 2.0 * w_/rect[2];
  float h = w * h_ / w_;
  float x = -w/2;
  float y = -h/2;

  float f = 0.3;

  float ww = 0.2 * w_/rect[2];
  float hh = ww * h_ / w_;
  float xx = -ww/2;
  float yy = -hh/2;

  float ff = 0.2;
  float vectorCoords[][3] = {
    {x, y, f}, 
    {x + w, y, f}, 
     {x + w, y + h, f},
    {x, y + h, f},
   

    {xx, yy, ff}, 
    {xx + ww, yy, ff}, 
     {xx + ww, yy + hh, ff},
    {xx, yy + hh, ff},
   
  };

  int index[_countof(vectorCoords)] = {0};

  for(int i = 0; i < _countof(vectorCoords); i ++)
    index[i] = i;

  float dl = 0.2;

  float axisCoords[][3] = {
    {-1000, 0, dl}, {1000, 0, dl},
    {0, -1000, dl}, {0, 1000, dl},
  };

  float normal[][3] = {
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},

    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
  };

  float l = 0;
  float t = 0;
  float r = 1;
  float b = 1;

  float texCoords[][2] = {
    {l, t}, {r, t}, {r, b}, {l, b},
    {l, t}, {r, t},  {r, b},{l, b},
  };
  
  ::glLineWidth(0.1);
  ::glPushMatrix();
 
#if 1
  ::glPushMatrix();
  ::glRotatef(roate_angle_*10, 0, 1, 0);
  //::glEnable (GL_LIGHTING);
  //::glEnable(GL_LIGHT0);
  GLfloat position[] = { 0.0, .0, 1.0, 0.0 };

  float spot_direct[] = {0, 0, -1};

  float ambientLight[]={1, 1, 1, 1.0f};  //环境光

  ::glLightfv(GL_LIGHT0,GL_AMBIENT, ambientLight);
  ::glLightfv (GL_LIGHT0, GL_POSITION, position);
  ::glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 1);
  ::glLightfv (GL_LIGHT0, GL_SPOT_DIRECTION, spot_direct);
  
  if (true){
    ::glPushMatrix();
   // glDisable (GL_LIGHTING);
    glTranslatef(position[0], position[1], position[2]);
    glColor3f (1.0, 0.0, 0.0);
    drawCube (0.1);
  //  glEnable (GL_LIGHTING);
    ::glPopMatrix();
  }
  ::glPopMatrix();

  if (false) {
    GLfloat earth_mat_ambient[]   = {0, 0, 0, 1.0f};
    GLfloat earth_mat_diffuse[]   = {0.0f, 0.0f, 1, 1.0f};
    GLfloat earth_mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat earth_mat_emission[] = {0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat earth_mat_shininess   = 1.0f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,    earth_mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,    earth_mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,   earth_mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,   earth_mat_emission);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS,  earth_mat_shininess);
  }
#else
  ::glEnable (GL_LIGHTING);
  ::glEnable(GL_LIGHT0);
#endif
#if 0
  GLdouble eqn[4] = {0.0, -1.0, 0.0, 0};
  glClipPlane (GL_CLIP_PLANE0, eqn);
  glEnable (GL_CLIP_PLANE0);

  GLdouble eqn1[4] = {-1,0, 0, 0};
  glClipPlane (GL_CLIP_PLANE5, eqn1);
  glEnable (GL_CLIP_PLANE5);

  GLdouble eqn2[4] = {1,1, 0, 0.3};
  glClipPlane (GL_CLIP_PLANE3, eqn2);
  glEnable (GL_CLIP_PLANE3);
#endif
  glEnable(GL_LINE_SMOOTH);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_POINT_SMOOTH);  
  glEnable(GL_LINE_SMOOTH);  
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points  
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines  

  glEnable(GL_TEXTURE_2D);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vectorCoords);

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

  GLfloat fColor[][4] = { 
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},

    {1.0, 0.0, 0.0, 1.0},
    {1.0, 0.0, 0.0, 1.0},
    {1.0, 0.0, 0.0, 1.0},
    {1.0, 0.0, 0.0, 1.0},
  };

  float al = 0.6;
  for(int i = 0; i < _countof(fColor); i ++) {
    fColor[i][3] = al;
  }
  float ws = 100;
 
  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, 0, normal);

  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(4, GL_FLOAT, 0, fColor);

  // glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  // glTexCoordPointer();

  glBindTexture(GL_TEXTURE_2D, textures_[1]);  
  glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &ws);
  glDrawElements(GL_TRIANGLE_FAN, _countof(index)/2, GL_UNSIGNED_INT, index);

  glDrawArrays(GL_LINES, 4, 4);
  glPopMatrix();

  glPopMatrix();
}
void DrawTexture::OnTimer() {
  roate_angle_ += 0.1;
}

bool DrawTexture::LoadGLTextures(const std::vector<std::wstring>& files) {  
  textures_.resize(files.size());

  glGenTextures(textures_.size(), &textures_[0]);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);  

  for(size_t i = 0; i < files.size(); i ++) {
    std::vector<unsigned char> buffer;
    dcodec_utils::BitmapData bitmap;

    dcodec_utils::load_file(files[i].c_str(), buffer);

    if (!dcodec_utils::parse_bmp(buffer, bitmap))
      continue;

    w_ = bitmap.w;
    h_ = bitmap.h;

    glBindTexture(GL_TEXTURE_2D, textures_[i]);  
    // Bind To The Texture ID 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   
    // Linear Min Filter 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   
    // Linear Mag Filter 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.w, bitmap.h, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, &bitmap.data[0]); 

    

  }

  return true;
}
