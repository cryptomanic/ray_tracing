#include <GL/glut.h>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

#define pi 3.141592654

struct point{
  float x, y;
};

void DRAW ();
point ray(point A, float phi);
void DrawCircle(point C, float r);
int circle_check(point A, point C, float r);


int main (int argc, char* argv[]) {
  glutInit (&argc, argv);  // used to initialize the GLUT library
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);  // sets the initial display mode
  glutInitWindowSize (512, 512);
  glutInitWindowPosition (0, 0);
  glutCreateWindow ("Ray Tracing");

  // Initialize OpenGL
  glClearColor (1, 1, 1, 0);
  glMatrixMode (GL_PROJECTION);
  gluOrtho2D (0, 300, 0, 300);

  glutDisplayFunc (DRAW);

  glutMainLoop ();
}

void DRAW () {
  point A;
  A.x = 100;
  A.y = 300;
  float phi = 276;
  point C;
  C.x = 100;
  C.y = 100;
  float r = 30;
  point C2;
  C2.x = 200;
  C2.y = 150;
  float r2 = 50;
  point C3;
  C3.x = 150;
  C3.y = 75;
  float r3 = 15;

  glClear(GL_COLOR_BUFFER_BIT);
  glPointSize (1.0);

  glColor3f (0, 1, 0);
  DrawCircle(C, r);
  DrawCircle(C2, r2);
  DrawCircle(C3, r3);
  
  glColor3f (1, 0, 0);
  glBegin(GL_POINTS);   
  for (int i = 0; i < 300; i++) {
    A = ray(A, phi);
    glVertex2i (int(A.x), int(A.y));
    // cout<<"pixel: "<<int(A.x)<<" "<<int(A.y)<<"\n";
    if (circle_check(A, C, r) <= 0) {
      float rho = atan(-(A.x-C.x)/(A.y-C.y))*(180/pi);
      phi = 2*rho-phi;
    }
    else if (circle_check(A, C2, r2) <= 0) {
      float rho = atan(-(A.x-C2.x)/(A.y-C2.y))*(180/pi);
      phi = 2*rho-phi;
    }
    else if (circle_check(A, C3, r3) <= 0) {
      float rho = atan(-(A.x-C3.x)/(A.y-C3.y))*(180/pi);
      phi = 2*rho-phi;
    }
  }
  glEnd();
  glFlush();
}
  
point ray(point A, float phi) {
  float psi = phi*pi/180;
  point temp;
  float dx, dy;
  if(phi >= 0 && phi <= 45) {
    dx = 1;
    dy = tan(psi);
  }
  else if(phi > 45 && phi < 90) {
    dy = 1;
    dx = 1/tan(psi);
  }
  else if(phi == 90) {
    dy = 1;
    dx = 0;
  }
  else if(phi > 90 && phi <= 135) {
    dy = 1;
    dx = 1/tan(psi);
  }
  else if(phi > 135 && phi <= 180) {
    dx = -1;
    dy = -tan(psi);
  }
  else if(phi > 180 && phi <= 225) {
    dx = -1;
    dy = -tan(psi);
  }
  else if(phi > 225 && phi < 270) {
    dy = -1;
    dx = -1/tan(psi);
  }
  else if(phi == 270) {
    dy = -1;
    dx = 0;
  }
  else if(phi > 270 && phi <= 315) {
    dy = -1;
    dx = -1/tan(psi);
  }
  else if(phi > 315 && phi < 360) {
    dx = 1;
    dy = tan(psi);
  }
  else if(phi < 0) {
    phi += 360;
    return ray(A, phi);
  }
  else if(phi > 360) {
    phi -= 360;
    return ray(A, phi);
  }
  else {
    dx = 0;
    dy = 0;
  }
  temp.x = A.x + dx;
  temp.y = A.y + dy;
  return temp;
}

void DrawCircle(point C, float r) {
  int num_segments = 360;
  float cx = C.x;
  float cy = C.y;
  glBegin(GL_LINE_LOOP);
  glLineWidth (4.0);
  // cout<<"CIRLCE\n\n";
  for(int ii = 0; ii < num_segments; ii++) { 
    float theta = 2.0f * pi * float(ii) / float(num_segments);
    //get the current angle 
    float x = r * cosf(theta);//calculate the x component 
    float y = r * sinf(theta);//calculate the y component
    // cout<<int(x+cx)<<" "<<int(y+cy)<<"\n";
    glVertex2i(x + cx, y + cy);//output vertex 
  }
  // cout<<"_________________________________\n";
  glEnd(); 
}

int circle_check(point A, point C, float r) {
  float x = (A.x-C.x);
  float y = (A.y-C.y);
  float cond = x*x+y*y-r*r;
  if (cond < 0)
    return -1;
  else if (cond == 0)
    return 0;
  else
    return 1;
}
