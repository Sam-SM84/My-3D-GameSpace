#include <GL/glut.h>
#include <cmath>
#include "Color.h"
#include "Object.h"
#include "Teapot.h"
#include "Cube.h"
#include "Sphere.h"
#include "WallX.h"
#include "WallZ.h"

using namespace std;

double camX = 0.0, camY = 0.0, camZ = 5.0;

double yaw = 0.0;
double pitch = 0.0;

int lastMouseX = 450;
int lastMouseY = 450;

bool firstMouse = true;

double speed = 0.01;

double gspeed = 0;

bool keys[256] = {false};

double t1 = 0,t2 = 0;

void computeCamera(double& dirX, double& dirY, double& dirZ)
{
    double radian_Yaw = yaw * 3.1415 / 180.0;
    double radian_Pitch = pitch * 3.1415 / 180.0;

    dirX = cos(radian_Pitch) * cos(radian_Yaw);
    dirY = sin(radian_Pitch);
    dirZ = cos(radian_Pitch) * sin(radian_Yaw);
}

double getRealTime(double& t1, double& t2)
{
    t2 = glutGet(GLUT_ELAPSED_TIME);
    double delta = (t2 - t1);
    t1 = t2;
    return delta;
}


void moveCamera(double dt)
{
    double dirX, dirY, dirZ;
    computeCamera(dirX, dirY, dirZ);

    double forwardX = dirX;
    double forwardZ = dirZ;


    double rightX = dirZ;
    double rightZ = -dirX;

    double realSpeed = dt * speed;

    if (keys['w'])
    {
        camX += forwardX * realSpeed;
        camZ += forwardZ * realSpeed;
    }

    if (keys['s'])
    {
        camX -= forwardX * realSpeed;
        camZ -= forwardZ * realSpeed;
    }

    if (keys['a'])
    {
        camX += rightX * realSpeed;
        camZ += rightZ * realSpeed;
    }

    if (keys['d'])
    {
        camX -= rightX * realSpeed;
        camZ -= rightZ * realSpeed;
    }

    if (keys[32]) camY = 5;
    if (keys[27]) exit(0);
   
}

void gravity()
{
    gspeed += 0.0005;
    if (camY > 0)
    {
        camY -= gspeed;
    }
    else if (camY < 0)
    {
        camY = 0;
        gspeed = 0;
    };
}

void makeGround(double sx, double sz, double ex, double ez)
{
    for (int i = 0; i < ex - sx; i++)
    {
        for (int j = 0; j < ez - sz; j++)
        {
            glPushMatrix();
            glTranslatef(i, -1.5, j);
            glColor3f(0, 0.75, 0);
            glutSolidCube(1);
            glPopMatrix();
        }
    }

}

void add_objects(double dt)
{

    Cube c = Cube(50, 0, -20, 5, { 0,0,1 });
    c.make();
    c.makeWireCube();

    Sphere s = Sphere(100, 0, -50, 4, { 0,1,0 });
    Position p = s.getDim();
    s.moveObject = [&]()
    {
        s.xp += 2.0  * cos(glutGet(GLUT_ELAPSED_TIME) * 0.005);
    };
    s.moveObject();
    s.make();

    WallX w = WallX(0, 20, 0, 5, { 1,0,0 });
    w.moveObject = [&]()
    {
        w.startingX += cos(glutGet(GLUT_ELAPSED_TIME) * 0.001);
        w.endingX += cos(glutGet(GLUT_ELAPSED_TIME) * 0.001) ;
    };
    w.moveObject();
    w.make();

    WallZ wx = WallZ(-20, 20, -20, 3, { 1,0.25,0 });
    wx.make();

    makeGround(-10, -10, 100, 100);

}


void update(double dt)
{
    moveCamera(dt);
    add_objects(dt);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    double dirX, dirY, dirZ;
    computeCamera(dirX, dirY, dirZ);

    gluLookAt(
        camX, camY, camZ,
        camX + dirX, camY + dirY, camZ + dirZ,
        0, 1, 0
    );

    double dt = getRealTime(t1, t2);
    update(dt);

    gravity();

    glutPostRedisplay();
    glutSwapBuffers();

}


void mouseMotion(int x, int y)
{
    int dx = x - (lastMouseX);
    int dy = y - (lastMouseY);

    double sensitivity = 0.15;


    yaw += dx * sensitivity;
    pitch -= dy * sensitivity;

    glutWarpPointer(lastMouseX, lastMouseY);

    if (pitch > 90.0) pitch = 90.0;
    if (pitch < -90.0) pitch = -90.0;

    if (yaw > 360) yaw -= 360;
    if (yaw < 0) yaw += 360;


    //glutPostRedisplay();
}

void KeyboardDownf(unsigned char key, int xx, int yy)
{
    keys[key] = true;
}

void KeyboardUpf(unsigned char key, int xx, int yy)
{
    keys[key] = false;
}

void lightshading()
{
    GLfloat light_position[] = { 5, 5, 5, 1 };
    GLfloat light_diffuse[] = { 1, 1, 1, 1 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.8, 0.8, 0.8, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);

    glutWarpPointer(lastMouseX, lastMouseY);
    glutSetCursor(GLUT_CURSOR_NONE);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(360, 30);
    glutCreateWindow("MyProject ver 1.2");

    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouseMotion);
    glutKeyboardFunc(KeyboardDownf);
    glutKeyboardUpFunc(KeyboardUpf);

    init();
    lightshading();

    glutMainLoop();
}
