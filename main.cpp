#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>
#include "include/BmpLoader.h"


double windowHeight=800, windowWidth=800;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0, fan_rot=360.0, f_x=0.0, f_y = 0.0 ;
GLboolean bRotate = false, uRotate = false, fanRotate = false;
GLfloat  eye_x = 2, eye_y = 3, eye_z = 11, look_x=2, look_y=0;
GLboolean AL = true, DL = false, SL = false, L0=false, L1 = false, L2 = false;
unsigned int TID[10] = {1, 2, 3, 4, 5, 6, 7, 8, 6, 10};

static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0},  //point index 0
    {2.0, 0.0, 0.0},  //point index 1
    {2.0, 0.0, 2.0},  //point index 2
    {0.0, 0.0, 2.0},  //point index 3
    {0.0, 2.0, 0.0},  //point index 4
    {2.0, 2.0, 0.0},  //point index 5
    {2.0, 2.0, 2.0},  //point index 6
    {0.0, 2.0, 2.0}   //point index 7
};

static GLubyte quadIndices[6][4] =
{
    {0, 1, 5, 4}, // indices for drawing the triangle plane 1
    {1, 2, 6, 5}, // indices for drawing the triangle plane 2
    {2, 3, 7, 6}, // indices for drawing the triangle plane 3
    {3, 0, 4, 7},  // indices for drawing the triangle plane 4
    {0, 1, 2, 3}, // indices for drawing the triangle plane 5
    {4, 5, 6, 7}  // indices for drawing the triangle plane 6
};

/*static GLfloat colors[6][3] =
{
    {0.0, 0.0, 1.0},  //color for point index 0
    {0.5, 0.0, 1.0},  //color for point index 1
    {0.0, 1.0, 0.0},  //color for point index 2
    {0.0, 1.0, 1.0},  //color for point index 3
    {0.8, 0.0, 0.0},  //color for point index 4
    {0.5, 1.0, 0.5}  //color for point index 5
};
*/
static void getNormal3p(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void solid(float col_a,float col_b,float col_c)
{

    GLfloat mat_ambient[] = { col_a*0.5, col_b*0.5, col_c*0.5, 1.0 };
    GLfloat mat_diffuse[] = {  col_a, col_b, col_c, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glutSolidSphere (3.0, 20, 16);

}


void drawCube(float col_a,float col_b,float col_c)
{

    GLfloat mat_ambient[] = { col_a*0.5, col_b*0.5, col_c*0.5, 1.0 };
    GLfloat mat_diffuse[] = {  col_a, col_b, col_c, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

   // glColor3f(col_a,col_b,col_c);
    glBegin(GL_QUADS);

    for (GLint i = 0; i <6; i++)
    {
                //glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);

        glVertex3fv(&v_cube[quadIndices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);glTexCoord2f(0,1);
    }
    glEnd();
    //glutSolidSphere (3.0, 20, 16);

}

/*void ownTranslatef(GLfloat dx, GLfloat dy, GLfloat dz)
{

    GLfloat m[16];

    m[0] = 1;
    m[4] = 0;
    m[8] = 0;
    m[12] = dx;
    m[1] = 0;
    m[5] = 1;
    m[9] = 0;
    m[13] = dy;
    m[2] = 0;
    m[6] = 0;
    m[10] = 1;
    m[14] = dz;
    m[3] = 0;
    m[7] = 0;
    m[11] = 0;
    m[15] = 1;

    glMatrixMode(GL_MODELVIEW);
    glMultMatrixf(m);
}
*/

void light()
{
    //1st light(Spotlight)---RED
    GLfloat no_light[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat light_ambient[]  = {1.0, 0.0, 0.0, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = {0.0, 80.0, -2.0, 1.0 };

    if(AL)
        glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    else
        glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);

    if(DL)
        glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    else
        glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);

    if(SL)
        glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    else
        glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);

    glLightfv( GL_LIGHT0, GL_POSITION, light_position);


    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);

    //......................2nd light.........................GREEN
    GLfloat light_ambient2[]  = {0.0, 1.0, 0.0, 1.0};
    GLfloat light_diffuse2[]  = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat light_position2[] = { -15, -5.0, -5.0, 1.0 };

    if(AL)
        glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient2);
    else
        glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);

    if(DL)
        glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
    else
        glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);

    if(SL)
        glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    else
        glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);

    glLightfv( GL_LIGHT1, GL_POSITION, light_position2);

    //......................2nd light.........................BLUE
    GLfloat light_ambient3[]  = {0.0, 0.0, 1.0, 1.0};
    GLfloat light_diffuse3[]  = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat light_position3[] = { 15, -5.0, -5.0, 1.0 };

    if(AL)
        glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient3);
    else
        glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);

    if(DL)
        glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse3);
    else
        glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);

    if(SL)
        glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
    else
        glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);

    glLightfv( GL_LIGHT2, GL_POSITION, light_position3);

}


void wall_sets()
{
    glViewport(0, 0, windowHeight, windowWidth);

    glPushMatrix(); //....................................begin of walls.................................

    //standing floor
    glPushMatrix();
    glTranslatef(-8,-3,-10);
    glScalef(7.5,0.3,2);
    drawCube(1.0, 0.5, 1.0);
    glPopMatrix();

    //floor
    glPushMatrix();
    glTranslatef(-8,-3.1,-10);
    glScalef(7.8,0.05,10);
    drawCube(0.902, 0.902, 0.980);
    glPopMatrix();

    //ceil
    glPushMatrix();
    glTranslatef(-8,6,-10);
    glScalef(7.8,0.02,10);
    drawCube(0.0,0.9,0.9);
    glPopMatrix();

    // left wall
    glPushMatrix();
    glTranslatef(-8,-3,-10);
    glScalef(0.25,4.5,10);
    drawCube(0.847, 0.749, 0.847);
    glPopMatrix();


    // right wall
    glPushMatrix();
    glTranslatef(7,-3,-10);
    glScalef(0.25,4.5,10);
    drawCube(0.847, 0.749, 0.847);
    glPopMatrix();


    //back wall
    glPushMatrix();
    glTranslatef(-8,-3,-10);
    glScalef(7.5,4.5,0.25);
    drawCube(0.878, 1.000, 1.000);
    glPopMatrix();

    //black board
    glPushMatrix();
    glTranslatef(-6,0,-9.5);
    glScalef(6,2.5,0.25);
    drawCube(0.000, 0.000, 0.000);
    glPopMatrix();

    glPopMatrix(); //..............end of walls................

}

void almirah()
{
    glViewport(0, 0, windowHeight, windowWidth);
    glPushMatrix(); //....................................begin of almirah.................................
//almirah
    glPushMatrix();
    glTranslatef(-7.3,-2.8,-1.5);
    glScalef(0.5,3,1.5);
    drawCube(0.4, 0.1, 1.0);
    glPopMatrix();

    //almirah row1
    glPushMatrix();
    glTranslatef(-6.3,-2.8,-1.5);
    glScalef(0.05,0.05,1.5);
    drawCube(0.4, 0.0, 0.0);
    glPopMatrix();

    //almirah row2
    glPushMatrix();
    glTranslatef(-6.3,3.1,-1.5);
    glScalef(0.05,0.05,1.5);
    drawCube(0.4, 0.0, 0.0);
    glPopMatrix();

    //almirah col1
    glPushMatrix();
    glTranslatef(-6.3,-2.8,-1.5);
    glScalef(0.05,3,0.05);
    drawCube( 0.4, 0.0, 0.0);
    glPopMatrix();
    //almirah col2
    glPushMatrix();
    glTranslatef(-6.3,-2.8,-0.2);
    glScalef(0.05,3,0.05);
    drawCube( 0.4, 0.0, 0.0);
    glPopMatrix();
    //almirah handle1
    glPushMatrix();
    glTranslatef(-6.2,0,-0.3);
    glScalef(0.05,0.5,0.05);
    drawCube( 1.0, 1.0, 1.0);
    glPopMatrix();
    //almirah handle2
    glPushMatrix();
    glTranslatef(-6.2,0,0.1);
    glScalef(0.05,0.5,0.05);
    drawCube( 1.0, 1.0, 1.0);
    glPopMatrix();

    //almirah col3
    glPushMatrix();
    glTranslatef(-6.3,-2.8,0);
    glScalef(0.05,3,0.05);
    drawCube( 0.4, 0.0, 0.1);
    glPopMatrix();

    //almirah col4
    glPushMatrix();
    glTranslatef(-6.3,-2.8,1.4);
    glScalef(0.05,3,0.05);
    drawCube( 0.4, 0.0, 0.0);
    glPopMatrix();
    glPopMatrix();
}

void windows()
{
    glViewport(0, 0, windowHeight, windowWidth);
    glPushMatrix(); //....................................begin of window.................................
//left window
    glPushMatrix();
    glTranslatef(-7.5,0,2);
    glScalef(0.05,2,2);
    drawCube( 1.000, 1.000, 0.941);
    glPopMatrix();

/*    //left window row1
    glPushMatrix();
    glTranslatef(-7.4,0,2);
    glScalef(0.05,0.05,2);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();

    //left window row2
    glPushMatrix();
    glTranslatef(-7.4,2,2);
    glScalef(0.05,0.05,2);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();
    //left window row3
    glPushMatrix();
    glTranslatef(-7.4,4,2);
    glScalef(0.05,0.05,2);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();

    //left window col1
    glPushMatrix();
    glTranslatef(-7.4,0,2);
    glScalef(0.05,2,0.05);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();
    //left window col2
    glPushMatrix();
    glTranslatef(-7.4,0,4);
    glScalef(0.05,2,0.05);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();
    //left window col3
    glPushMatrix();
    glTranslatef(-7.4,0,6);
    glScalef(0.05,2,0.05);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();
    */

    // 1st right window
    glPushMatrix();
    glTranslatef(6.5,0,-4);
    glScalef(0.05,2,2);
    drawCube(1.000, 1.000, 0.941);
    glPopMatrix();

  /*  //1st right window row1
    glPushMatrix();
    glTranslatef(6.3,0,-4);
    glScalef(0.05,0.05,2);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();

    //1st right window row2
    glPushMatrix();
    glTranslatef(6.3,2,-4);
    glScalef(0.05,0.05,2);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();

    //1st right window row3
    glPushMatrix();
    glTranslatef(6.3,4,-4);
    glScalef(0.05,0.05,2);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();

    //1st right window col1
    glPushMatrix();
    glTranslatef(6.3,0,-4);
    glScalef(0.05,2,0.05);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();

    //1st right window col2
    glPushMatrix();
    glTranslatef(6.3,0,-2);
    glScalef(0.05,2,0.05);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();

    //1st right window col3
    glPushMatrix();
    glTranslatef(6.3,0,0);
    glScalef(0.05,2,0.05);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();*/

    //2nd right window
    glPushMatrix();
    glTranslatef(6.5,0,2);
    glScalef(0.05,2,2);
    drawCube( 1.000, 1.000, 0.941);
    glPopMatrix();
/*
    //2nd right window row1
    glPushMatrix();
    glTranslatef(6.3,0,2);
    glScalef(0.05,0.05,2);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();

    //2nd right window row2
    glPushMatrix();
    glTranslatef(6.3,2,2);
    glScalef(0.05,0.05,2);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();

    //2nd right window row3
    glPushMatrix();
    glTranslatef(6.3,4,2);
    glScalef(0.05,0.05,2);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();

    //2nd right window col1
    glPushMatrix();
    glTranslatef(6.3,0,2);
    glScalef(0.05,2,0.05);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();
    //2nd right window col2
    glPushMatrix();
    glTranslatef(6.3,0,4);
    glScalef(0.05,2,0.05);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();
    //2nd right window col3
    glPushMatrix();
    glTranslatef(6.3,0,6);
    glScalef(0.05,2,0.05);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();*/

    glPopMatrix();
}

void door()
{
    glViewport(0, 0, windowHeight, windowWidth);
    glPushMatrix(); //....................................begin of door.................................
    // door
    glPushMatrix();
    glTranslatef(-7.5,-2.8,-6);
    glScalef(0.08,4,2);
    drawCube(1.000, 1.000, 0.5);
    glPopMatrix();
    /*
    //door row1
    glPushMatrix();
    glTranslatef(-7.4,-2.8,-6);
    glScalef(0.05,0.05,2);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();
    //door row2
    glPushMatrix();
    glTranslatef(-7.4,5.2,-6);
    glScalef(0.05,0.05,2);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();
    //door col1
    glPushMatrix();
    glTranslatef(-7.4,-2.8,-6);
    glScalef(0.05,4,0.05);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();
    //door col2
    glPushMatrix();
    glTranslatef(-7.4,-2.8,-4);
    glScalef(0.05,4,0.05);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();
    //door col3
    glPushMatrix();
    glTranslatef(-7.4,-2.8,-2);
    glScalef(0.05,4,0.05);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();*/

    //door handle1
    glPushMatrix();
    glTranslatef(-7.2,1.5,-2.4);
    glScalef(0.05,0.5,0.1);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();
    glPopMatrix();
}

void celling_fan()
{
    glViewport(0, 0, windowHeight, windowWidth);

    glPushMatrix();    //............begin of celling fan................

    //middle rod
    glPushMatrix();
    glTranslatef(-0.3, 0.2, -0.3);
    glScalef(0.3,0.5,0.3);
    drawCube(0.3,0.5,0.8);
    glPopMatrix();

//middle bar
    glPushMatrix();
    glRotatef( fan_rot, f_x, f_y, 0.0 );
    glTranslatef(-1, -0.2, -1);
    glScalef(1,0.2,1);
    drawCube(0.5, 0.2, 1.0);
    glPopMatrix();


    //left-right wing
    glPushMatrix();
    glRotatef( fan_rot, f_x, f_y, 0.0 );
    glTranslatef(-5.5, 0, -0.5);
    glScalef(6,0.05,0.5);
    drawCube(0.5, 0.5, 0.8);
    glPopMatrix();

    //front-back wing
    glPushMatrix();
    glRotatef( fan_rot, f_x, f_y, 0.0 );
    glTranslatef(-0.5, 0, -5.5);
    glScalef(0.5,0.05,6);
    drawCube(0.5, 0.5, 0.8);
    glPopMatrix();

    glPopMatrix(); //............end of celling fan................


}

void table_chair()
{
    glViewport(0, 0, windowHeight, windowWidth);

    glPushMatrix();    //.......begin of table.......

    //FLAT
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    glRotatef(90,1,0,0);
    glScalef(4.2,2.2,0.05);
    drawCube(0.737, 0.561, 0.561);
    glPopMatrix();

    //back left leg
    glPushMatrix();
    glRotatef(180,1,0,0);
    glScalef(0.2,2.5,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();

    //back right leg
    glPushMatrix();
    glTranslatef(8,0,0);
    glRotatef(180,1,0,0);
    glScalef(0.2,2.5,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();

    //front left leg
    glPushMatrix();
    glTranslatef(0,0,4);
    glRotatef(180,1,0,0);
    glScalef(0.2,2.5,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();

    //front right leg
    glPushMatrix();
    glTranslatef(8,0,4);
    glRotatef(180,1,0,0);
    glScalef(0.2,2.5,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();

    //left leg connector
    glPushMatrix();
    glTranslatef(0,-4,0);
    glRotatef(90,1,0,0);
    glScalef(0.2,2,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();

    //right leg connector
    glPushMatrix();
    glTranslatef(8,-4,0);
    glRotatef(90,1,0,0);
    glScalef(0.2,2,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();

    //connect connector
    glPushMatrix();
    glTranslatef(0,-4,2);
    glScalef(4,0.2,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();

    glPopMatrix();      //......end of table

    glPushMatrix(); //........begin of chair .......
    glTranslated(2,0,1);
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    //glRotatef( alpha, axis_x, axis_y, 0.0 );

    //bottom FLAT
    glPushMatrix();
    glTranslatef(0,-1,-0.5);
    glRotatef(90,1,0,0);
    glScalef(2.5,2.3,0.05);
    drawCube(0.8, 0.2, 0.0);
    glPopMatrix();

    //side FLAT
    glPushMatrix();
    glTranslatef(0,-1,4);
    glScalef(2.5,2.2,0.05);
    drawCube(0.545, 0.271, 0.075);
    glPopMatrix();

    //back left leg
    glPushMatrix();
    glTranslatef(0,-1,0);
    glRotatef(180,1,0,0);
    glScalef(0.2,2.5,0.2);
    drawCube(0.5, 0.4, 0.2);
    glPopMatrix();

    //back right leg
    glPushMatrix();
    glTranslatef(4.5,-1,0);
    glRotatef(180,1,0,0);
    glScalef(0.2,2.5,0.2);
    drawCube(0.5, 0.4, 0.2);
    glPopMatrix();

    //front left leg
    glPushMatrix();
    glTranslatef(0,-1,4);
    glRotatef(180,1,0,0);
    glScalef(0.2,2.5,0.2);
    drawCube(0.5, 0.4, 0.2);
    glPopMatrix();

    //front right leg
    glPushMatrix();
    glTranslatef(4.5,-1,4);
    glRotatef(180,1,0,0);
    glScalef(0.2,2.5,0.2);
    drawCube(0.5, 0.4, 0.2);
    glPopMatrix();

    glPopMatrix(); //..........end of chair........
}

void call_table_chair()
{
    glPushMatrix();
    glScalef(0.5,0.5,0.5);
    glTranslatef(0,0,10);

    glPushMatrix();
    glTranslated(-8,0,-20);
    table_chair();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2,0,-20);
    table_chair();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-8,0,-12);
    table_chair();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2,0,-12);
    table_chair();
    glPopMatrix();


    glPushMatrix();
    glTranslated(-8,0,-4);
    table_chair();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2,0,-4);
    table_chair();
    glPopMatrix();

    glPopMatrix();

}

void LoadTexture(const char*filename, unsigned int ID)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glFrustum(-5,5,-5,5, 4, 100);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    // eye, look at, head up vector
    //gluLookAt(2,3,10,2,0,0, 0,1,0);
    gluLookAt(eye_x, eye_y, eye_z, look_x, look_y, 0, 0, 1, 0);
    glViewport(0, 0, windowHeight, windowWidth);

    //visualizing lighting effect
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TID[3]);
    glPushMatrix();
    glRotatef( theta, axis_x, axis_y, 0.0 );
    glRotatef( alpha, axis_x, axis_y, 0.0 );
    glTranslatef(-6.4, 4, 0);
    glScalef(0.25, 0.25, 0.25);
    solid(1,0,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //fan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TID[0]);
    glPushMatrix();
    glRotatef( theta, axis_x, axis_y, 0.0 );
    glRotatef( alpha, axis_x, axis_y, 0.0 );
    glTranslatef(0,4.8,0);
    celling_fan();
    glPopMatrix();
     glDisable(GL_TEXTURE_2D);

    //almirah
            glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, TID[5]);
    glPushMatrix();
    glRotatef( theta, axis_x, axis_y, 0.0 );
    glRotatef( alpha, axis_x, axis_y, 0.0 );
    almirah();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //windows
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TID[3]);
    glPushMatrix();
    glRotatef( theta, axis_x, axis_y, 0.0 );
    glRotatef( alpha, axis_x, axis_y, 0.0 );
    windows();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //door
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TID[1]);
    glPushMatrix();
    glRotatef( theta, axis_x, axis_y, 0.0 );
    glRotatef( alpha, axis_x, axis_y, 0.0 );
    door();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //wall sets
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TID[2]);
    glPushMatrix();
    glRotatef( theta, axis_x, axis_y, 0.0 );
    glRotatef( alpha, axis_x, axis_y, 0.0 );
    wall_sets();
    glPopMatrix();
     glDisable(GL_TEXTURE_2D);


      //........table chair sets........
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TID[4]);
    glPushMatrix();
    glRotatef( theta, axis_x, axis_y, 0.0 );
    glRotatef( alpha, axis_x, axis_y, 0.0 );
    call_table_chair();
    glPopMatrix();
     glDisable(GL_TEXTURE_2D);


    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    //movement (front, back, left, right, up, down)
    case 'w':
    case 'W':
        eye_z-=0.5;
//        if(eye_z<1)
//            eye_z = 10;
        break;
    case 's':
    case 'S':
        eye_z+=0.5;
//        if(eye_z>20)
//            eye_z = 10;
        break;
    case 'a':
    case 'A':
        eye_x-=0.5;
//        if(eye_x<-12)
//            eye_x = 2;
        break;

    case 'd':
    case 'D':
        eye_x+=0.5;
//        if(eye_x>10)
//            eye_x = 2;
        break;

    case 'u':
    case 'U':
        eye_y+=0.5;
//        if(eye_y>8)
//            eye_y = 2;
        break;

    case 'b':
    case 'B':
        eye_y-=0.5;
//        if(eye_y<-2)
//            eye_y = 2;
        break;

    //look(up, down, left, right)
    case 'i':
    case 'I':
        look_y+=0.5;
//        if(look_y>5)
//            look_y = 0;
        break;
    case 'k':
    case 'K':
        look_y-=0.5;
//        if(look_y<-3)
//            look_y = 0;
        break;

    case 'j':
    case 'J':
        look_x-=0.5;
//        if(look_x<-20)
//            look_x = 2;
        break;

    case 'l':
    case 'L':
        look_x+=0.5;
//        if(look_x>20)
//            look_x = 2;
        break;

    case 'f':
    case 'F':
        fanRotate = !fanRotate;
        uRotate = false;
        //bRotate = false;
        f_x=0.0;
        f_y=1.0;
        break;

    case 'h':
    case 'H':
        bRotate = !bRotate;
        uRotate = false;
        //fanRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'v':
    case 'V':
        uRotate = !uRotate;
        bRotate = false;
        fanRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        break;

    case '4':
        AL = !AL;
        light();
        break;
    case '5':
        DL = !DL;
        light();
        break;
    case '6':
        SL = !SL;
        light();
        break;

    case '1':
        L0 = !L0;
        if(L0)
            glEnable(GL_LIGHT0);
        else
            glDisable(GL_LIGHT0);
        break;

    case '2':
        L1 = !L1;
        if(L1)
            glEnable(GL_LIGHT1);
        else
            glDisable(GL_LIGHT1);
        break;

    case '3':
        L2 = !L2;
        if(L2)
            glEnable(GL_LIGHT2);
        else
            glDisable(GL_LIGHT2);
        break;


    case 27:	// Escape key
        exit(1);
    }
}

void animate()
{
    if (fanRotate == true)
    {
        //right rotation
//        fan_rot += 0.8;
//        if(fan_rot > 360.0)
//            fan_rot = 0.0; //*floor(fan_rot/360.0);

        //left rotation
        fan_rot -= 1;
        if(fan_rot <= 0.0)
            fan_rot  = 360.0;
    }

    if (bRotate == true)
    {
        theta += 0.1;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.1;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    glutPostRedisplay();

}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("1607100_Classroom_Assignment");

    glClearColor(0,0,0,1);

    printf("Enter below key for controlling....");
    printf("\n f/F fan  rotation\n h/H horizontal rotation\n v/V vertical rotation");
    printf("\n 1  light1(SpotLight) RED\n 2 light2(LEFT) GREEN\n 3 light3(RIGHT) BLUE");
    printf("\n 4  ambient\n 5 diffuse\n 6 specular\n");

    printf("\nEnter below key for controlling movement....");
    printf("\n w/W  front\t s/S back");
    printf("\n a/A  left\t d/D right");
    printf("\n u/U  up\t b/B down");

    printf("\n\nEnter below key for controlling look....");
    printf("\n i/I up\t\t k/K down");
    printf("\n j/J  left\t l/L right");
    printf("\n\nEnter Esc for quit\n");

    LoadTexture("E:\\4rth year 2nd semester\\graphics LAB\\GLUT projects\\ClassroomAssignment\\fan.bmp", TID[0]);
    LoadTexture("E:\\4rth year 2nd semester\\graphics LAB\\GLUT projects\\ClassroomAssignment\\door.bmp", TID[1]);
    LoadTexture("E:\\4rth year 2nd semester\\graphics LAB\\GLUT projects\\ClassroomAssignment\\black.bmp", TID[2]);
    LoadTexture("E:\\4rth year 2nd semester\\graphics LAB\\GLUT projects\\ClassroomAssignment\\windows.bmp", TID[3]);
    LoadTexture("E:\\4rth year 2nd semester\\graphics LAB\\GLUT projects\\ClassroomAssignment\\chair.bmp", TID[4]);
    LoadTexture("E:\\4rth year 2nd semester\\graphics LAB\\GLUT projects\\ClassroomAssignment\\almirah.bmp", TID[5]);

        glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    //glEnable(GL_LIGHTING);
    //light();

    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);

       glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);

    glutMainLoop();

    return 0;
}




