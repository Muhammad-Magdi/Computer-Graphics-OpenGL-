#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <complex>
#include <iostream>

using namespace std;

const double PI = acos(-1);
typedef complex<double> point;
#define X real()
#define Y imag()
#define vec(a, b)							((b)-(a))
#define rotate(p, t)  ((p)*(exp(point(0, t))))
#define rotateA(p, t, about) 	(rotate(vec(about,p),t)+about)
#define translate(v, p) ((v)+(p))
#define rad(t)  ((t)*PI/180)

inline double rotationDegree(int sides){
  return rad((180-(((sides-2)*180.0)/sides)));
}

int sides;

/*
  Shape     sides, rotation degree
  Triangle  3, 2*PI/3
  Square    4, PI/2
  Pentagon  5, 2*PI/5
  Hexagon   6, PI/3
  Heptagon  7, ...
  N-agon    n, 180-((n-2)*180/n)
*/
void display() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
  glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
  glBegin(GL_POLYGON);{
   glColor3f(0.0f, 1.0f, 1.0f);         // Cyan
   point p1(0, 0), p2(3.0/sides, 0), t;
   glVertex2f(p1.X, p1.Y);
   for(int i = 0 ; i < sides-1 ; ++i){
     glVertex2f(p2.X, p2.Y);
     t = translate(p2, vec(p1, p2));
     t = rotateA(t, rotationDegree(sides), p2);
     p1 = p2;
     p2 = t;
   }}glEnd();
  glFlush();  // Render now
}

int main(int argc, char** argv) {
  sides = 1;
  glutInit(&argc, argv);                 // Initialize GLUT
  glutCreateWindow("Having Fun With Polygons"); // Create a window with the given title
  glutDisplayFunc(display); // Register display callback handler for window re-paint
  cout << "Enter The Number of Sides [< 1 to exit]: ";
  cin >> sides;
  while(sides > 0){
    display();
    cout << "Enter The Number of Sides [< 1 to exit]: ";
    cin >> sides;
  }
  glutMainLoop();           // Enter the infinitely event-processing loop
  return 0;
}
