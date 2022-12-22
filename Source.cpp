#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <time.h>
#include <string>

#define PI 3.14

GLfloat mX = 0;

typedef struct Point
{
    float x, y;
    Point(float _x, float _y) : x(_x), y(_y) {}
} Point;

struct def
{
    GLfloat g, x, y;
    def() {}
    def(GLfloat _x, GLfloat _y, GLfloat _g) : x(_x), y(_y), g(_g) {}
};
struct enemy
{
    GLfloat x, y;
    int type;
    enemy() {}
    enemy(GLfloat _x, GLfloat _y, int _type) : x(_x), y(_y), type(_type) {}
};

struct missel
{
    float x, y;
    bool moving;
};

bool gameOver;
bool flash = false;
bool forward = true;
int score = 0, lives = 3;

std::vector<struct missel> missels;
std::vector<struct enemy> droids;
std::vector<struct enemy> shots;
std::vector<struct def> defence;
std::vector<Point> explode;

void start()
{
    struct def d;
    struct missel m;
    srand(time(NULL));
    for (int i = 0, k = -13.5; i < 4; i++, k += 8)
    {
        d = def(k, 2, 1.0f);
        defence.push_back(d);
        d.y = 3;
        defence.push_back(d);
        d.x = k + 1;
        defence.push_back(d);
        d.x = k + 2;
        defence.push_back(d);
        d.y = 2;
        defence.push_back(d);
    }
    for (int i = 0; i < 5; i++)
    {
        for (float j = 0, k = -13; j < 10; j++, k += 3)
        {
            droids.push_back(enemy(k, 25.5 - i * 2.5, i + 1));
        }
    }
    for (int i = 0; i < 2; i++)
    {

        m.moving = false;
        m.y = -1;
        m.x = mX - 1 + 2 * i;
        missels.push_back(m);
    }
}

void moveShip(bool *forward)
{
    bool overflow = false;
    float step = 0.01;

    for (int i = 0; i < droids.size(); i++)
    {
        if (droids[i].y < 2)
        {
            gameOver = true;
            return;
        }

        if (droids[i].x + step > 18 && *forward == true)
        {
            overflow = true;
            break;
        }
        if (droids[i].x - step < -20 && *forward == false)
        {
            overflow = true;
            break;
        }
    }
    if (overflow)
    {
        *forward = !*forward;
        for (int i = 0; i < droids.size(); i++)
        {
            droids[i].y -= 0.5;
        }
    }
    step = (*forward == true) ? step : -step;

    for (int i = 0; i < droids.size(); i++)
    {
        droids[i].x += step;
    }
}

void drawText(const char *text, int length, float x, float y, float size, float r, float g, float b)
{
    glPushMatrix();
    glColor3f(r, g, b);
    glTranslatef(x, y, 0.0f);
    glScalef(size, size, 1.0f);
    for (int i = 0; i < length; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, (int)text[i]);
    }
    glPopMatrix();
}

void move_tiro()
{
    for (int i = 0; i < shots.size(); i++)
        shots[i].y -= (1.0) / 10;
}

void moveBullet()
{
    for (int i = 0; i < missels.size(); i++)
        if (missels[i].moving == true)
            missels[i].y += (1.5) / 10;
}

void shipDraw()
{
    glPushMatrix();
    glTranslatef(mX, 0, 0);
    glColor3f(1.0f, 0.92f, 0.80f);
    glLineWidth(2);
    glBegin(GL_TRIANGLES);
        glVertex2f(-1.0f, -1.0f); 
        glVertex2f(1.0f, -1.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.1f);
        glVertex2f(-0.5f, -0.1f);
        glVertex2f(0.0f, 1.0f); 
        glVertex2f(0.2f, 0.5f);
        glVertex2f(-0.2f, 0.5f);
        glVertex2f(0.0f, -1.4f); 
        glVertex2f(0.2f, -1.0f);
        glVertex2f(-0.2f, -1.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.1f, -1.5f);
        glVertex2f(-0.1f, -1.5f);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex2f(0.0f, -1.9f); 
    glEnd();

    glColor3f(0.5f, 0.6f, 0.86f);
    glBegin(GL_QUADS);
        glVertex2f(0.2f, -0.2f);
        glVertex2f(0.2f, 0.5f);
        glVertex2f(-0.2f, 0.5f);
        glVertex2f(-0.2f, -0.2f);
        glVertex2f(0.1f, -1.4f);
        glVertex2f(0.1f, -1.3f);
        glVertex2f(-0.1f, -1.4f);
        glVertex2f(-0.1f, -1.3f);
    glEnd();
    glPopMatrix();
}

void android3()
{
    glColor3ub(199,21,133);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(0, 2);
        glVertex2f(2, 2);
        glVertex2f(2, 0);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0, 1.2);
        glVertex2f(0, 2);
        glVertex2f(1, 2);
        glVertex2f(2, 1.2);
        glVertex2f(2, 2);
        glVertex2f(1, 2);
        glVertex2f(0, 1); 
        glVertex2f(0, 0);
        glVertex2f(0.8, 1);
        glVertex2f(2, 1);
        glVertex2f(2, 0);
        glVertex2f(1.2, 1);
        glVertex2f(0, 0);
        glVertex2f(2, 0);
        glVertex2f(1, 0.9);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(0.5, 0.5);
        glVertex2f(1.5, 0.5);
        glVertex2f(1, 0.1);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS); 
        glVertex2f(0.5, 1.3);
        glVertex2f(0.5, 1.5);
        glVertex2f(0.7, 1.5);
        glVertex2f(0.7, 1.3);
        glVertex2f(1.3, 1.3);
        glVertex2f(1.3, 1.5);
        glVertex2f(1.5, 1.5);
        glVertex2f(1.5, 1.3);
    glEnd();
}

void android2()
{
    glColor3ub(176,196,222);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(0, 2);
        glVertex2f(2, 2);
        glVertex2f(2, 0);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0 - 0.2, 2); 
        glVertex2f(2.2, 2);
        glVertex2f(1, 1.4);
        glVertex2f(0, 0.9);
        glVertex2f(0, 1.7);
        glVertex2f(0.6, 1.4);
        glVertex2f(2, 0.9); 
        glVertex2f(2, 1.7);
        glVertex2f(1.4, 1.4);
        glVertex2f(0.2, 0);
        glVertex2f(0.2, 0.7);
        glVertex2f(0.6, 0);
        glVertex2f(1.8, 0);
        glVertex2f(1.8, 0.7);
        glVertex2f(1.4, 0);
        glVertex2f(0.5, 0.5); 
        glVertex2f(1.4, 0.5);
        glVertex2f(1, 0 - 0.3);
    glEnd();
    glBegin(GL_QUADS); 
        glVertex2f(0.5, 0.7);
        glVertex2f(0.5, 0.9);
        glVertex2f(0.7, 0.9);
        glVertex2f(0.7, 0.7);
        glVertex2f(1.3, 0.7);
        glVertex2f(1.3, 0.9);
        glVertex2f(1.5, 0.9);
        glVertex2f(1.5, 0.7);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(0.9, 0.3);
        glVertex2f(0.9, 0.5);
        glVertex2f(1.1, 0.5);
        glVertex2f(1.1, 0.3);
    glEnd();
}

void android1()
{
    glColor3ub(255,69,0);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(0, 2);
        glVertex2f(2, 2);
        glVertex2f(2, 0);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0, 0);
        glVertex2f(2, 0);
        glVertex2f(1, 0.9);
        glVertex2f(0, 1.5);
        glVertex2f(0, 2);
        glVertex2f(0.6, 2);
        glVertex2f(2, 1.5);
        glVertex2f(2, 2);
        glVertex2f(1.4, 2);
        glVertex2f(0, 1);
        glVertex2f(0, 0.2);
        glVertex2f(0.8, 1);
        glVertex2f(2, 1);
        glVertex2f(2, 0.2);
        glVertex2f(1.2, 1);
    glEnd();
    glBegin(GL_QUADS); 
        glVertex2f(0.5, 1.3); 
        glVertex2f(0.5, 1.5);
        glVertex2f(0.8, 1.5);
        glVertex2f(0.8, 1.3);
        glVertex2f(1.2, 1.3);
        glVertex2f(1.2, 1.5);
        glVertex2f(1.5, 1.5);
        glVertex2f(1.5, 1.3);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(0.8, 0.4);
        glVertex2f(0.8, 0.6);
        glVertex2f(1.2, 0.6);
        glVertex2f(1.2, 0.4);
    glEnd();
}

void Draw(struct enemy inv)
{
    glPushMatrix();
    glTranslatef(inv.x, inv.y, 0);
    if (inv.type >= 4)
    {
        android1();
    }
    else if (inv.type >= 2)
    {
        android2();
    }
    else
    {
        android3();
    }
    glPopMatrix();
}

void DrawDef(struct def defence)
{
    glPushMatrix();
    glTranslatef(defence.x, defence.y, 0);
    glColor3ub(173,255,47);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(0, 1);
        glVertex2f(1, 1);
        glVertex2f(1, 0);
    glEnd();
    glPopMatrix();
}

void DrawExplode(GLfloat x, GLfloat y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glLineWidth(1);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);
    glColor3f(1.0f, 1.0f, 0.0f);
    for (int i = 0; i <= 20; i++)
    {
        glVertex2f((cos(i * 2.0f * PI / 20)), sin(i * 2.0f * PI / 20));
    }
    glEnd();
    glPopMatrix();
}

void flushScreen()
{
    glClearColor(0.6, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);
}

void drawBullet(GLfloat x, GLfloat y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(1.0f, 0.0f, 0.1f);
    glLineWidth(2);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, -0.2f);
        glVertex2f(0.1f, -0.2f);
        glVertex2f(0.1f, 0.2f);
        glVertex2f(-0.1f, 0.2f);
    glEnd();
    glPopMatrix();
}

void DrawMissel(float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2);
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, -0.2f);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(0.1f, 0.1f);
        glVertex2f(0.1f, -0.2f);
    glEnd();
    glPopMatrix();
}
void bulletReset(int m)
{
    missels[m].y = -1;
    missels[m].moving = false;
    missels[m].x = mX - 1 + 2 * m;
}
void shoot(int alien)
{
    shots.push_back(droids[alien]);
}

void Alien(int step)
{
    if (droids.size() < shots.size())
        return;
    int alien = rand() % droids.size();
    shoot(alien);

    glutTimerFunc((4000 - step > 1000 ? 4000 - step : 1000), Alien, step * 1.3);
}

bool checkBoundingBox(Point p0, Point p1, float size)
{
    return !(p0.x < p1.x || p0.x > (p1.x + size) || p0.y < p1.y || p0.y > (p1.y + size));
}

void Collision(int step)
{
    for (int i = 0; i < shots.size(); i++)
    {
        if (shots[i].y <= 4)
        {
            for (int j = 0; j < defence.size(); j++)
            {
                if (checkBoundingBox(Point(shots[i].x, shots[i].y), Point(defence[j].x, defence[j].y), 1))
                {
                    explode.push_back(Point(shots[i].x, shots[i].y));
                    shots.erase(shots.begin() + i);
                    defence[j].g -= 0.25f;
                    if (defence[i].g <= 0)
                    {
                        defence.erase(defence.begin() + i);
                    }
                    break;
                }
            }
        }
        if (checkBoundingBox(Point(shots[i].x, shots[i].y), Point(mX - 1, -1), 2))
        {
            lives--;
            flash = true;
            explode.push_back(Point(shots[i].x, shots[i].y));

            gameOver = (lives > 0) ? false : true;
            shots.erase(shots.begin() + i);
        }
        if (shots[i].y <= -2)
        {
            shots.erase(shots.begin() + i);
        }
    }
    for (int j = 0; j < missels.size(); j++)
    {
        if (missels[j].y > 30)
        {
            bulletReset(j);
        }
        for (int i = 0; i < defence.size(); i++)
        {
            if (checkBoundingBox(Point(missels[j].x, missels[j].y), Point(defence[i].x, defence[i].y), 1))
            {
                defence[i].g -= 0.25f;
                explode.push_back(Point(missels[j].x, missels[j].y));
                bulletReset(j);

                if (defence[i].g <= 0)
                {
                    defence.erase(defence.begin() + i);
                }
            }
        }
        for (int i = 0; i < droids.size(); i++)
        {
            if (checkBoundingBox(Point(missels[j].x, missels[j].y), Point(droids[i].x, droids[i].y), 2))
            {
                explode.push_back(Point(missels[j].x, missels[j].y));
                bulletReset(j);
                score += droids[i].type > 3 ? 10 : (droids[i].type > 1 ? 20 : 40);
                droids.erase(droids.begin() + i);
            }
        }
    }
    glutTimerFunc(step, Collision, step);
}

void MoveAll(int step)
{
    moveShip(&forward);
    move_tiro();
    moveBullet();
    glutPostRedisplay();
    Collision(0);
    glutTimerFunc(step, MoveAll, step);
}

void display(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    std::string pts = ("Score ");
    pts += std::to_string(score);
    drawText(pts.c_str(), pts.length(), -19, 29.5, 0.008, 1, 1, 1);
    pts = ("HP ");
    pts += std::to_string(lives);
    drawText(pts.c_str(), pts.length(), -19, 28, 0.008, 0.7, 0.7, 1);
    for (int i = 0; i < defence.size(); i++)
        DrawDef(defence[i]);
    for (int i = 0; i < droids.size(); i++)
        Draw(droids[i]);
    for (int i = 0; i < shots.size(); i++)
        drawBullet(shots[i].x, shots[i].y);
    for (int i = 0; i < missels.size(); i++)
        DrawMissel(missels[i].x, missels[i].y);
    if (flash)
    {
        flushScreen();
        flash = false;
    }
    for (int i = 0; i < explode.size(); i++)
        DrawExplode(explode[i].x, explode[i].y);
    explode.clear();

    if (gameOver)
        drawText("Game Over", 9, -10, 15, 0.025, 1, 0, 0);
    if (droids.size() == 0)
    {
        drawText("You Win", 7, -10, 15, 0.025, 1, 1, 1);
    }

    shipDraw();
    glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
    GLsizei widht, height;

    if (h == 0)
        h = 1;

    widht = w;
    height = h;

    glViewport(0, 0, widht, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (widht <= height)
    {
        gluOrtho2D(-20.0f, 20.0f, -3.0f * height / widht, 31.0f * height / widht);
    }
    else
    {
        gluOrtho2D(-20.0f * widht / height, 20.0f * widht / height, -3.0f, 31.0f);
    }
}

void specFunc(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT && !gameOver)
    {
        mX -= 0.5f;
        if (mX < -19)
            mX = -19;
    }
    if (key == GLUT_KEY_RIGHT && !gameOver)
    {
        mX += 0.5f;
        if (mX > 19)
            mX = 19;
    }
    if (key == GLUT_KEY_UP && missels[0].moving != true)
        missels[0].moving = true;
    if (key == GLUT_KEY_DOWN && missels[1].moving != true)
        missels[1].moving = true;
    for (int i = 0; i < missels.size(); i++)
        if (missels[i].moving == false)
            missels[i].x = mX - 1 + 2 * i;

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
    case 'p':
        gameOver = !gameOver;
        break;
    }
}

void init(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(-20, 20, -3, 31);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glutInitWindowPosition(512, 192);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Space Invaders");
    start();
    glutTimerFunc(0, MoveAll, 5);
    glutTimerFunc(0, Alien, 100);
    glutDisplayFunc(display);
    glMatrixMode(GL_PROJECTION);
    glutSpecialFunc(specFunc);
    glutKeyboardFunc(keyboard);
    init();
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}