#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

class Teapot
{
public:
    double xp, yp, zp, size;
    Teapot(double xp, double yp, double zp, double size)
    {
        this->xp = xp;
        this->yp = yp;
        this->zp = zp;
        this->size = size;
    }
    void make()
    {
        glTranslatef(this->xp, this->yp, this->zp);
        glutSolidTeapot(this->size);
    }
};

double camX = 0.0, camY = 0.0, camZ = 5.0;

double yaw = 0.0;
double pitch = 0.0;

int lastMouseX = 450;
int lastMouseY = 450;

bool firstMouse = true;

double speed = 0.2;

double gspeed = 0;

void showInfo();
void gravity();

void computeCamera(double& dirX, double& dirY, double& dirZ)
{
    double radian_Yaw = yaw * 3.1415 / 180.0;
    double radian_Pitch = pitch * 3.1415 / 180.0;

    dirX = cos(radian_Pitch) * cos(radian_Yaw);
    dirY = sin(radian_Pitch);
    dirZ = cos(radian_Pitch) * sin(radian_Yaw);
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

    glColor3f(1, 0.4, 0.2);

    glutSolidTeapot(1.5);


    //showInfo();
    gravity();

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


    glutPostRedisplay();
}

void Keyboardf(unsigned char key, int xx, int yy)
{
    double dirX, dirY, dirZ;
    computeCamera(dirX, dirY, dirZ);

    double forwardX = dirX;
    double forwardZ = dirZ;


    double rightX = dirZ;
    double rightZ = -dirX;

    if (key == 'w')
    {
        camX += forwardX * speed;
        camZ += forwardZ * speed;
    }

    if (key == 's')
    {
        camX -= forwardX * speed;
        camZ -= forwardZ * speed;
    }

    if (key == 'a')
    {
        camX += rightX * speed;
        camZ += rightZ * speed;
    }

    if (key == 'd')
    {
        camX -= rightX * speed;
        camZ -= rightZ * speed;
    }

    if (key == 32) camY = 5;


    if (key == 27) exit(0);

    glutPostRedisplay();
}

void showInfo()
{
    cout << "----------------------------\n";
    //cout << "Position = (" << camX << " , " << camY << "," << camZ << ")\n";
    //cout << "Mouse Position = (" << lastMouseX << " , " << lastMouseY << ")\n";
    cout << "Angle = (X = " << yaw << ", Y = " << pitch << ")\n";
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


void lightshading()
{
    GLfloat light_position[] = { 5, 5, 5, 1 };
    GLfloat light_diffuse[] = { 1, 1, 1, 1 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
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
    glutCreateWindow("MyProject ver 1.0");

    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouseMotion);
    glutKeyboardFunc(Keyboardf);

    init();
    lightshading();

    glutMainLoop();
}
