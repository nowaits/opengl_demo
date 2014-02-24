#include "draw_test.h"
#include <Windows.h>
#include <gl\glew.h>
#include <stdlib.h>

DrawMethod* GetTestDrawMethod() {
  return new DrawCube;
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

// ��ʮ������
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
  // ������
  GLint points[4];
  // ������
  GLfloat normal[3];
  int     id;
};

// ��������İ˸����㱣�浽һ����������
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
  glClearColor(0.0f,0.0f,0.0f,0.0f);   //������ɫΪ��ɫ
  glShadeModel(GL_SMOOTH);     //ʹ��ƽ����������
  glEnable(GL_DEPTH_TEST);     //�޳�������
  glEnable(GL_CULL_FACE);      //���������α���
  glFrontFace(GL_CCW);      //�������ʱ�뷽��Ϊ����
  glEnable(GL_LIGHTING);      //���ù���

  float legAngle[2]={0.0f,0.0f};
  float armAngle[2]={0.0f,0.0f};
  float ambientLight[]={0.3f,0.5f,0.8f,1.0f};  //������
  float diffuseLight[]={0.25f,0.25f,0.25f,1.0f}; //ɢ���
  float lightPosition[]={0.0f,0.0f,1.0f,0.0f}; //��Դλ��
  //���ʱ���
  float matAmbient[]={1.0f,1.0f,1.0f,1.0f};
  float matDiff[]={1.0f,1.0f,1.0f,1.0f};

  //ΪLIGHT0��������
  glMaterialfv(GL_FRONT,GL_AMBIENT,matAmbient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,matDiff);
  //���ڿ�ʼ��ЭLIGHT0
  glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight); //���û��������
  glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight); //����ɢ������
  glLightfv(GL_LIGHT0,GL_POSITION,lightPosition); //���ù�Դ�ڳ����е�λ��
  //���ù�
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

    // ����һ����������������������ָ��������
    glGenBuffersARB(1, &vertex_buffer);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertex_buffer);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB,
      sizeof(g_points), g_points, GL_STATIC_DRAW_ARB);

    // ����һ���������������������ָ��������
    glGenBuffersARB(1, &index_buffer);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, index_buffer);
    glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,
      sizeof(g_index_list), g_index_list, GL_STATIC_DRAW_ARB);


    // ָ����������
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
  glLoadIdentity();     //��λ��ת�Ƕȼ�����
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