#include "draw_method.h"
#include <GL\gl.h>

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
  glTranslatef(0.64f,0.0f,-10.0f);
  glColor4f(0.18f,0.18f,0.2f,1.0f);
  glBegin(GL_TRIANGLES);
  glVertex3f( 0.0f, 1.0f, 0.0f);	// Top
  glVertex3f(-1.0f,-1.0f, 0.0f);	// Bottom Left
  glVertex3f( 1.0f,-1.0f, 0.0f);	// Bottom Right
  glEnd();
  glPopMatrix();
}

// 二十四面体
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