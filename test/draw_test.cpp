#include "draw_test.h"
#include <Windows.h>
#include <gl\glew.h>
#include <stdlib.h>
#include "..\utils\utils.h"

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
  float lightPosition[]={0.0f,0.0f,1.0f,0.0f}; //光源位置
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

void DrawCube::OnDraw() {
  // DrawCubess(0, 0, 0);return;;
   glColor3f (1.0, 1.0, 1.0);
  //glLoadIdentity ();             /* clear the matrix */
  /* viewing transformation  */
  // gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  // glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
  //::glPolygonMode(GL_FRONT, GL_LINE);
  // ::glPolygonMode(GL_BACK, GL_POINT);
  glLoadIdentity();     //复位旋转角度计数器
  glTranslatef(0.0f,0.0f,-3.0f);
  ::glRotatef(roate_angle_, 1, 0, 0);
  ::glRotatef(roate_angle_, 0, 1, 0);
  ::glRotatef(roate_angle_, 0, 0, 1);
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


DrawTexture::DrawTexture(DrawWays draw_ways) 
: draw_ways_(draw_ways), roate_angle_(0.0f) {
  texture_ = 0;
}

void DrawTexture::OnInit() {  
  glClearColor(1.0f,.0f,.0f,1.0f);
}

void DrawTexture::OnDraw() {

  // DrawCubess(0, 0, 0);return;;
  //glColor3f (1.0, 1.0, 1.0);
  //glLoadIdentity ();             /* clear the matrix */
  /* viewing transformation  */
  // gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   
  //::glPolygonMode(GL_FRONT, GL_LINE);
  // ::glPolygonMode(GL_BACK, GL_POINT);
  glLoadIdentity();     //复位旋转角度计数器
  //glTranslatef(0.0f,0.0f,-3.0f);
 
 // 
  GLint rect[4];
  glGetIntegerv(GL_VIEWPORT, rect);

  glScalef (1, rect[2] / (float)rect[3], 1.0);      /* modeling transformation */ 

  float w = 1.0f;
  float h = w * h_ / w_;
  float x = -w/2;
  float y = -h/2;

  float f = 0.0;

  float vectorCoords[][3] = {
    {x, y, f}, {x + w, y, f}, {x, y + h, f},
    {x + w, y + h, f},
    {-1, 0, f}, {1, 0, f},
    {0, -1, f}, {0, 1, f},
  };

  float l = 0;
  float t = 0;
  float r = 1;
  float b = 1;

  float texCoords[][2] = {
    {l, t}, {r, t}, {l, b}, {r, b}
  };

  glLineWidth(0.1);

  ::glPushMatrix();
  
  ::glRotatef(roate_angle_, 0, 0, 1);
  
 // ::glTranslatef(0.2, 0, -.4);
  
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
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

  glEnable(GL_POINT_SMOOTH);  
  glEnable(GL_LINE_SMOOTH);  
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points  
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines  

  if (texture_ == 0) {
    LoadGLTextures(L"texture_test.bmp", &texture_);
  }

  glEnable(GL_TEXTURE_2D);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vectorCoords);

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

  GLfloat fColor[][4] = { 
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 0.0},
    {1.0, 1.0, 1.0, 0.0},
    {1.0, 1.0, 1.0, 0.0},

    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.5, 0.0, 1.0},
  };
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(4, GL_FLOAT, 0, fColor);

  glBindTexture(GL_TEXTURE_2D, texture_);  

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glColor4f(0, 0.5, 0, 0.4);
  glDisable(GL_TEXTURE_2D);
  glDrawArrays(GL_LINES, 4, 4);
  glPopMatrix();
#if 1
  glColor4f(0, 0.5, 0, 0.4);
  glDisable(GL_TEXTURE_2D);
  glDrawArrays(GL_LINES, 4, 4);
#endif
}
void DrawTexture::OnTimer() {
  roate_angle_ += 0.5;
}

bool DrawTexture::LoadGLTextures(wchar_t* file_name, GLuint * texture) {
  std::vector<unsigned char> buffer;
  dcodec_utils::BitmapData bitmap;

  dcodec_utils::load_file(file_name, buffer);
  if (!dcodec_utils::parse_bmp(buffer, bitmap))
    return false;

  w_ = bitmap.w;
  h_ = bitmap.h;

  glGenTextures(1,texture);     // Create The Texture
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);  

  glBindTexture(GL_TEXTURE_2D, *texture);  
  // Bind To The Texture ID 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   
  // Linear Min Filter 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   
  // Linear Mag Filter 
  glTexImage2D(GL_TEXTURE_2D, 0, 3, bitmap.w, bitmap.h, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, &bitmap.data[0]); 

  return true;
}
