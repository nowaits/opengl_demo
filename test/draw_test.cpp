#include "draw_test.h"
#include <Windows.h>
#include <gl\glew.h>
#define BUFFER_OFFSET(offset) ((const GLubyte *)NULL + (offset))

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
typedef struct _Point {
  GLfloat position[3];
  GLfloat color[3];
  int     id;
} Point;

typedef struct _Normal {
  GLfloat normal_pointer[3];
} Normal;

// ��������İ˸����㱣�浽һ����������
Point vertex_list[] = {
  -0.5f, -0.5f, -0.5f, 0, 0, 1, 0,
  0.5f, -0.5f, -0.5f, 0, 1, 1, 1,
  -0.5f,  0.5f, -0.5f, 1, 0, 1, 2,
  0.5f,  0.5f, -0.5f, 1, 1, 1, 3,

  -0.5f, -0.5f,  0.5f, 0.5, 0, 1, 4,
  0.5f, -0.5f,  0.5f, 0, 1, 0.5, 5,
  -0.5f,  0.5f,  0.5f, 0, 0.5, 1, 6,
  0.5f,  0.5f,  0.5f, 0, 0, 0.5, 7,
};

GLfloat vertex_listss[][3] = {
  -0.5f, -0.5f, -0.5f,
  0.5f, -0.5f, -0.5f, 
  -0.5f,  0.5f, -0.5f, 
  0.5f,  0.5f, -0.5f, 

  -0.5f, -0.5f,  0.5f, 
  0.5f, -0.5f,  0.5f, 
  -0.5f,  0.5f,  0.5f, 
  0.5f,  0.5f,  0.5f,
};

GLfloat normalize[][3] = {
  0, 0, -1.0f,
  -1.0f, 0, 0,
   0, -1.0f,  0,
   0, 0, 1.0f,
   1.0f, 0, 0,
   0, 1.0f, 0,
};

// ��Ҫʹ�õĶ������ű��浽һ����������
static const GLint index_list[][4] = {
  0, 2, 3, 1, 
  0, 4, 6, 2,
  0, 1, 5, 4,
  4, 5, 7, 6,
  1, 3, 7, 5,
  2, 6, 7, 3,
};

DrawCube::DrawCube() 
: user_vertex_obj_(false) {

}
void DrawCube::OnInit() {
  if (user_vertex_obj_) {
    GLuint vertex_buffer;
    GLuint normalize_buffer;
    GLuint index_buffer;

    // ����һ����������������������ָ��������
    glGenBuffersARB(1, &vertex_buffer);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertex_buffer);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB,
      sizeof(vertex_list), vertex_list, GL_STATIC_DRAW_ARB);
  // 
  //   // ����һ���������������������ָ��������
  //   glGenBuffersARB(1, &index_buffer);
  //   glBindBufferARB(GL_ARRAY_BUFFER_ARB, index_buffer);
  //   glBufferDataARB(GL_ARRAY_BUFFER_ARB,
  //     sizeof(normalize), normalize, GL_STATIC_DRAW_ARB);


    // ����һ���������������������ָ��������
    glGenBuffersARB(1, &index_buffer);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, index_buffer);
    glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,
      sizeof(index_list), index_list, GL_STATIC_DRAW_ARB);
  }



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

}

//���Ƶ�λ������
void DrawCubess(float xPos,float yPos,float zPos)
{
  // glPushMatrix();
  //glTranslatef(xPos,yPos,zPos);
  glBegin(GL_QUADS);    //����
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(0.5f,0.5f,0.5f);
  glVertex3f(0.5f,0.5f,-0.5f);
  glVertex3f(-0.5f,0.5f,-0.5f);
  glVertex3f(-0.5f,0.5f,0.5f);
  glEnd();
  glBegin(GL_QUADS);    //����
  glNormal3f(0.0f,-1.0f,0.0f);
  glVertex3f(0.5f,-0.5f,0.5f);
  glVertex3f(-0.5f,-0.5f,0.5f);
  glVertex3f(-0.5f,-0.5f,-0.5f);
  glVertex3f(0.5f,-0.5f,-0.5f);
  glEnd();
  glBegin(GL_QUADS);    //ǰ��
  glNormal3f(0.0f,0.0f,1.0f);
  glVertex3f(0.5f,0.5f,0.5f);
  glVertex3f(-0.5f,0.5f,0.5f);
  glVertex3f(-0.5f,-0.5f,0.5f);
  glVertex3f(0.5f,-0.5f,0.5f);
  glEnd();
  glBegin(GL_QUADS);    //����
  glNormal3f(0.0f,0.0f,-1.0f);
  glVertex3f(0.5f,0.5f,-0.5f);
  glVertex3f(0.5f,-0.5f,-0.5f);
  glVertex3f(-0.5f,-0.5f,-0.5f);
  glVertex3f(-0.5f,0.5f,-0.5f);
  glEnd();
  glBegin(GL_QUADS);    //����
  glNormal3f(-1.0f,0.0f,0.0f);
  glVertex3f(-0.5f,0.5f,0.5f);
  glVertex3f(-0.5f,0.5f,-0.5f);
  glVertex3f(-0.5f,-0.5f,-0.5f);
  glVertex3f(-0.5f,-0.5f,0.5f);
  glEnd();
  glBegin(GL_QUADS);    //����
  glNormal3f(1.0f,0.0f,0.0f);
  glVertex3f(0.5f,0.5f,0.5f);
  glVertex3f(0.5f,-0.5f,0.5f);
  glVertex3f(0.5f,-0.5f,-0.5f);
  glVertex3f(0.5f,0.5f,-0.5f);
  glEnd();
  // glPopMatrix();
}

void DrawCube::OnDraw() {
 // DrawCubess(0, 0, 0);return;;
 // glColor3f (1.0, 1.0, 1.0);
  //glLoadIdentity ();             /* clear the matrix */
  /* viewing transformation  */
  // gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  // glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
 //::glPolygonMode(GL_FRONT, GL_LINE);
 // ::glPolygonMode(GL_BACK, GL_POINT);
   glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  
  if (user_vertex_obj_) {
    // ʵ��ʹ��ʱ�붥������ǳ����ƣ�ֻ����ָ������ʱ����ָ��ʵ�ʵ����飬��Ϊָ��NULL����
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
   
    glVertexPointer(3, GL_FLOAT, sizeof(Point), NULL);
    glColorPointer(3, GL_FLOAT, sizeof(Point), BUFFER_OFFSET(3*sizeof(GLfloat)));
    glDrawElements(GL_QUADS, sizeof(index_list)/sizeof(**index_list), GL_UNSIGNED_INT, NULL);
  }
  else {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
 //   glEnableClientState(GL_COLOR_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normalize);
   // glColorPointer(3, GL_FLOAT, sizeof(Point), (const GLubyte *)(&vertex_list + 3*sizeof(GLfloat)));
    glVertexPointer(3, GL_FLOAT, 0, vertex_listss);
    

    glDrawElements(GL_QUADS, sizeof(index_list)/sizeof(**index_list), GL_UNSIGNED_INT, index_list);
  }
}