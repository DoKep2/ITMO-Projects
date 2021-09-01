#include <windows.h>
#include <gl/gl.h>
#include <math.h>
#include <mmsystem.h>
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
using namespace std;
float vertex[] = {1,1,0, 1,-1,0, -1,-1,0, -1,1,0};


const double M_PI = acos(-1);
float xAlpha = 0;
float yAlpha = 0;
float zAlpha = 0;

HWND hwnd;
HDC hDC;
POINTFLOAT pos = {0, 0};

void ShowPlane(float x1, float y1, float z1,
               float x2, float y2, float z2,
               float x3, float y3, float z3,
               float x4, float y4, float z4)
{
    glBegin(GL_TRIANGLES);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x3, y3, z3);
    glVertex3f(x2, y2, z2);
    glVertex3f(x3, y3, z3);
    glVertex3f(x4, y4, z4);
    glEnd();
    glLineWidth(10);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x4, y4, z4);
    glVertex3f(x3, y3, z3);
    glEnd();

}

typedef struct rgb
{
    float r;
    float g;
    float b;
    bool operator ==(const rgb& other)
    {
        return (r == other.r && g == other.g && b == other.b);
    }
} rgb;

typedef struct Point
{
    float x;
    float y;
    float z;
} Point;

Point PointRotateX(float x, float y, float z, float oy, float oz, float angle)
{
    Point point;
    point.x = x;
    point.y = (y - oy) * cos(angle) - (z - oz) * sin(angle) + oy;
    point.z = (y - oy) * sin(angle) + (z - oz) * cos(angle) + oz;
    return point;
}

Point PointRotateY(float x, float y, float z, float ox, float oz, float angle)
{
    Point point;
    point.x = (x - ox) * cos(angle) - (z - oz) * sin(angle) + ox;
    point.y = y;
    point.z = (x - ox) * sin(angle) + (z - oz) * cos(angle) + oz;
    return point;
}

Point PointRotateZ(float x, float y, float z, float ox, float oy, float angle)
{
    Point point;
    point.x = (x - ox) * cos(angle) - (y - oy) * sin(angle) + ox;
    point.y = (x - ox) * sin(angle) + (y - oy) * cos(angle) + oy;
    point.z = z;
    return point;
}



void ShowWorld()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &vertex);
    for(int i = -15; i < 15; i++)
    {
        for(int j = -15; j < 15; j++)
        {
            glPushMatrix();
            glTranslatef(i * 2, j * 2, 0);
            if((i + j) % 2)
            {
                glColor3f(0, 0, 0);
            }
            else
                glColor3f(1, 1, 1);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            glPopMatrix();
        }
    }
    glDisableClientState(GL_VERTEX_ARRAY);
}

class Camera
{
private:
    double x, y, z;
    double xRot, zRot;
public:
    Camera(double x_, double y_, double z_, double xRot_, double zRot_):
        x(x_),
        y(y_),
        z(z_),
        xRot(xRot_),
        zRot(zRot_)
    {}
    void Apply()
    {
        glRotatef(-xRot, 1, 0, 0);
        glRotatef(-zRot, 0, 0, 1);
        glTranslatef(-x, -y, -z);
    }
    void Rotation(float xAngle, float zAngle)
    {
        xRot += xAngle;
        zRot += zAngle;
    }
    void Move()
    {
        if(GetForegroundWindow() != hwnd)
            return;
        float angle = -zRot / 180 * M_PI;
        float speed = 0;
        if(GetKeyState('W') < 0)
        {
            speed = 0.3;
        }
        if(GetKeyState('S') < 0)
        {
            speed = -0.3;
        }
        if(GetKeyState('A') < 0)
        {
            speed = 0.3;
            angle -= M_PI/2;
        }
        if(GetKeyState('D') < 0)
        {
            speed = 0.3;
            angle += M_PI/2;
        }

        if(speed)
        {
            x += sin(angle) * speed;
            y += cos(angle) * speed;
        }
        if(GetKeyState(VK_SPACE) < 0)
        {
            z += 0.5;
        }
        if(GetKeyState(VK_SHIFT) < 0)
        {
            z -= 0.5;
        }
        POINT cur;
        POINT base = {400, 300};
        GetCursorPos(&cur);
        Rotation((base.y - cur.y) / 7.0, (base.x - cur.x) / 7.0);
        SetCursorPos(base.x, base.y);
    }
};

Camera camera(0, 0, 5, 70, -40);


class LR
{
public:
    double x;
    double y;
    double z;
    double a;
public:
    LR(double x_, double y_, double z_, double a_ = 0):
        x(x_),
        y(y_),
        z(z_),
        a(a_)
    {}
    void Rotate()
    {
        glTranslatef(x, y, z);
        if(x != 1.5)
            glRotatef(a, 1, 0, 0);
        if(y != 1.5)
            glRotatef(a, 0, 1, 0);
        if(z != 1.5)
            glRotatef(a, 0, 0, 1);
        glTranslatef(-x, -y, -z);
    }
    LR& operator = (const LR& other)
    {
        if(this == &other)
        {
            return *this;
        }
        x = other.x;
        y = other.y;
        z = other.z;
        a = other.a;
    }
};

vector<LR> arr;

struct NumPlanes
{
    int l = 0, r = 1, f = 2, b = 3, d = 4, u = 5;
} Planes;

void fillArr()
{
    arr.push_back(LR(0, 1.5, 1.5)); /// LEFT
    arr.push_back(LR(2, 1.5, 1.5)); /// RIGHT
    arr.push_back(LR(1.5, 0, 1.5)); /// FRONT
    arr.push_back(LR(1.5, 2, 1.5)); /// BACK
    arr.push_back(LR(1.5, 1.5, 0)); /// DOWN
    arr.push_back(LR(1.5, 1.5, 2)); /// UP
}
void changeX(int x);
void changeY(int y);
void changeZ(int z);

class Cube
{
public:
    rgb ArrColor[3][3][3][6];
    rgb NewColor[3][3][3][6];
public:
    void Draw(int x, int y, int z)
    {
        glColor3f(ArrColor[x][y][z][0].r, ArrColor[x][y][z][0].g, ArrColor[x][y][z][0].b);
        ShowPlane(0,0,0, 1,0,0, 0,1,0, 1,1,0); /// down
        glColor3f(ArrColor[x][y][z][1].r, ArrColor[x][y][z][1].g, ArrColor[x][y][z][1].b);
        ShowPlane(0,0,0, 0,0,1, 1,0,0, 1,0,1); /// front
        glColor3f(ArrColor[x][y][z][2].r, ArrColor[x][y][z][2].g, ArrColor[x][y][z][2].b);
        ShowPlane(0,0,0, 0,0,1, 0,1,0, 0,1,1); /// left
        glColor3f(ArrColor[x][y][z][3].r, ArrColor[x][y][z][3].g, ArrColor[x][y][z][3].b);
        ShowPlane(0,1,0, 0,1,1, 1,1,0, 1,1,1); /// back
        glColor3f(ArrColor[x][y][z][4].r, ArrColor[x][y][z][4].g, ArrColor[x][y][z][4].b);
        ShowPlane(1,0,0, 1,0,1, 1,1,0, 1,1,1); /// right
        glColor3f(ArrColor[x][y][z][5].r, ArrColor[x][y][z][5].g, ArrColor[x][y][z][5].b);
        ShowPlane(0,0,1, 0,1,1, 1,0,1, 1,1,1); /// up
    }
    void update()
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    for(int t = 0; t < 6; t++)
                    {
                        ArrColor[i][j][k][t] = NewColor[i][j][k][t];
                    }
                }
            }
        }
    }
    void clear_()
    {
        for(int i = 0; i < 6; i++)
        {
            arr[i].a = 0;
        }
    }
    void repeat(double angle, int isX, int isY, int isZ)
    {
        glClearColor(0.8f, 0.0f, 0.52f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        camera.Apply();
        camera.Move();
        ShowWorld();
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    glPushMatrix();
                    glTranslatef(0, 0, 10);
                    glTranslatef(1.5, 1.5, 1.5);
                    glRotatef(angle, isX, isY, isZ);
                    glTranslatef(-1.5, -1.5, -1.5);
                    glTranslatef(i, j, k);
                    Draw(i, j, k);
                    glPopMatrix();
                }
            }
        }
        glPopMatrix();
        SwapBuffers(hDC);
    }
    void AllCube(int axis)
    {
        double angle = 0;
        for(int i = 0; i < 9; i++)
        {
            angle += 10;
            if(axis == 1)
                repeat(angle, 1, 0, 0);
            else if(axis == 2)
                repeat(angle, 0, 1, 0);
            else
                repeat(angle, 0, 0, 1);
        }
        if(axis == 1)
        {
            changeX(0);
            update();
            changeX(1);
            update();
            changeX(2);
            update();
        }
        if(axis == 2)
        {
            changeY(0);
            update();
            changeY(1);
            update();
            changeY(2);
            update();
        }
        if(axis == 3)
        {
            changeZ(0);
            update();
            changeZ(1);
            update();
            changeZ(2);
            update();
        }
    }
    void ZCube(int cnt)
    {
        /// L -> B -> R -> F
        for(int i = 0; i < cnt; i++)
        {
            int cp = Planes.l;
            Planes.l = Planes.b;
            Planes.b = Planes.r;
            Planes.r = Planes.f;
            Planes.f = cp;
        }
    }
    void XCube(int cnt)
    {
        /// F -> D -> B -> U
        for(int i = 0; i < cnt; i++)
        {
            int cp = Planes.f;
            Planes.f = Planes.d;
            Planes.d = Planes.b;
            Planes.b = Planes.u;
            Planes.u = cp;
        }
    }

    void Rotate(int x, int y, int z)
    {
        glPushMatrix();
        if(!x)
            arr[0].Rotate();
        if(x == 2)
            arr[1].Rotate();
        if(!y)
            arr[2].Rotate();
        if(y == 2)
            arr[3].Rotate();
        if(!z)
            arr[4].Rotate();
        if(z == 2)
            arr[5].Rotate();

        glTranslatef(x, y, z);
        Draw(x, y, z);
        glPopMatrix();
    }
    void Show()
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    glPushMatrix();
                    glTranslatef(0, 0, 10);
                    Rotate(i, j, k);
                    glPopMatrix();
                }
            }
        }
    }

};
Cube cube;

void changeX(int x)
{
    for(int y = 0; y < 3; y++)
    {
        for(int z = 0; z < 3; z++)
        {
            rgb cp = cube.ArrColor[x][y][z][3];
            cube.ArrColor[x][y][z][3] = cube.ArrColor[x][y][z][0];
            cube.ArrColor[x][y][z][0] = cube.ArrColor[x][y][z][1];
            cube.ArrColor[x][y][z][1] = cube.ArrColor[x][y][z][5];
            cube.ArrColor[x][y][z][5] = cp;
            Point tmp = PointRotateX(x, y, z, 1, 1, M_PI/2);
            for(int t = 0; t < 6; t++)
            {
                cube.NewColor[(int)round(tmp.x)][(int)round(tmp.y)][(int)round(tmp.z)][t] = (rgb)cube.ArrColor[x][y][z][t];
            }
        }
    }
}

void changeY(int y)
{
    for(int x = 0; x < 3; x++)
    {
        for(int z = 0; z < 3; z++)
        {
            rgb cp = cube.ArrColor[x][y][z][0];
            cube.ArrColor[x][y][z][0] = cube.ArrColor[x][y][z][4];
            cube.ArrColor[x][y][z][4] = cube.ArrColor[x][y][z][5];
            cube.ArrColor[x][y][z][5] = cube.ArrColor[x][y][z][2];
            cube.ArrColor[x][y][z][2] = cp;
            Point tmp = PointRotateY(x, y, z, 1, 1, -M_PI/2);
            for(int t = 0; t < 6; t++)
            {
                cube.NewColor[(int)round(tmp.x)][(int)round(tmp.y)][(int)round(tmp.z)][t] = (rgb)cube.ArrColor[x][y][z][t];
            }
        }
    }
}

void changeZ(int z)
{
    for(int x = 0; x < 3; x++)
    {
        for(int y = 0; y < 3; y++)
        {
            rgb cp = cube.ArrColor[x][y][z][2];
            cube.ArrColor[x][y][z][2] = cube.ArrColor[x][y][z][3];
            cube.ArrColor[x][y][z][3] = cube.ArrColor[x][y][z][4];
            cube.ArrColor[x][y][z][4] = cube.ArrColor[x][y][z][1];
            cube.ArrColor[x][y][z][1] = cp;
            Point tmp = PointRotateZ(x, y, z, 1, 1, M_PI/2);
            for(int t = 0; t < 6; t++)
            {
                cube.NewColor[(int)round(tmp.x)][(int)round(tmp.y)][(int)round(tmp.z)][t] = (rgb)cube.ArrColor[x][y][z][t];
            }
        }
    }
}


void cmain()
{
    glClearColor(0.8f, 0.0f, 0.52f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    camera.Apply();
    camera.Move();
    ShowWorld();
    cube.Show();
    glPopMatrix();
    SwapBuffers(hDC);
}

BOOL CheckColor(int x, int y, int z, int p, float r, float g, float b)
{
    return (cube.ArrColor[x][y][z][p].r == r && cube.ArrColor[x][y][z][p].g == g &&
            cube.ArrColor[x][y][z][p].b == b);
}

void L(int cnt, int direct)
{
    for(int c = 0; c < cnt; c++)
    {
        for(int t = 0; t < 9; t++)
        {
            arr[direct].a += 10;
            cmain();
        }
        if(arr[direct].x != 1.5)
            changeX(arr[direct].x);
        if(arr[direct].y != 1.5)
            changeY(arr[direct].y);
        if(arr[direct].z != 1.5)
            changeZ(arr[direct].z);
        cube.update();
        cube.clear_();
    }
}

void CrossF()
{
    int j = 4;
    while(j--)
    {
        int i = 4;
        while(i--)
        {
            int cnt = 0;
            while((CheckColor(1, 0, 2, 5, 1, 1, 1) || CheckColor(1, 0, 2, 1, 1, 1, 1)) && cnt <= 4)
            {
                L(1, 5);
                cnt++;
            }
            if(cnt == 5)
            {
                break;
            }
            L(1, 2);
        }
        cube.ZCube(1);
        cube.AllCube(3);
    }
}

void MakeFront()
{
    int i = 4;
    while(i--)
    {
        while(1)
        {
            if(CheckColor(1, 0, 2, 5, cube.ArrColor[1][0][1][1].r, cube.ArrColor[1][0][1][1].g, cube.ArrColor[1][0][1][1].b)
                    && CheckColor(1, 0, 2, 1, 1, 1, 1))
            {
                L(1, 5);
                L(1, 1);
                L(1, 2);
                L(3, 1);
                break;
            }
            else if(CheckColor(1, 0, 2, 1, cube.ArrColor[1][0][1][1].r, cube.ArrColor[1][0][1][1].g, cube.ArrColor[1][0][1][1].b)
                    && CheckColor(1, 0, 2, 5, 1, 1, 1))
            {
                L(2, 2);
                break;
            }
            L(1, 5);
        }
        cube.ZCube(1);
        cube.AllCube(3);
    }
}

void Pif_Paf(int cnt)
{
    for(int i = 0; i < cnt; i++)
    {
        L(3, 1);
        L(3, 5);
        L(1, 1);
        L(1, 5);
    }
}

void MakeAngles()
{
    int i = 4;
    while(i--)
    {
        int cnt = 0;
        while(CheckColor(2, 0, 2, 1, 1, 1, 1) || CheckColor(2, 0, 2, 5, 1, 1, 1) || CheckColor(2, 0, 2, 4, 1, 1, 1))
        {
            L(1, 5);
            cnt++;
            if(cnt > 4)
            {
                break;
            }
        }
        if(CheckColor(2, 0, 0, 1, 1, 1, 1) || CheckColor(2, 0, 0, 0, 1, 1, 1) || CheckColor(2, 0, 0, 4, 1, 1, 1))
        {
            Pif_Paf(1);
        }
        cube.ZCube(1);
        cube.AllCube(3);
    }
    i = 4;
    while(i--)
    {
        int cnt = 0;
        double r1 = cube.ArrColor[1][0][0][1].r;
        double g1 = cube.ArrColor[1][0][0][1].g;
        double b1 = cube.ArrColor[1][0][0][1].b;
        double r2 = cube.ArrColor[2][1][0][4].r;
        double g2 = cube.ArrColor[2][1][0][4].g;
        double b2 = cube.ArrColor[2][1][0][4].b;
        while(1)
        {
            if(CheckColor(2, 0, 2, 1, 1, 1, 1))
            {
                if((CheckColor(2, 0, 2, 5, r1, g1, b1) && CheckColor(2, 0, 2, 4, r2, g2, b2))
                        || (CheckColor(2, 0, 2, 5, r2, g2, b2) && CheckColor(2, 0, 2, 4, r1, g1, b1)))
                {
                    Pif_Paf(5);
                    break;
                }
            }
            else if(CheckColor(2, 0, 2, 5, 1, 1, 1))
            {
                if((CheckColor(2, 0, 2, 1, r1, g1, b1) && CheckColor(2, 0, 2, 4, r2, g2, b2))
                        || (CheckColor(2, 0, 2, 1, r2, g2, b2) && CheckColor(2, 0, 2, 4, r1, g1, b1)))
                {
                    Pif_Paf(3);
                    break;
                }
            }
            else if(CheckColor(2, 0, 2, 4, 1, 1, 1))
            {
                if((CheckColor(2, 0, 2, 1, r1, g1, b1) && CheckColor(2, 0, 2, 5, r2, g2, b2))
                        || (CheckColor(2, 0, 2, 1, r2, g2, b2) && CheckColor(2, 0, 2, 5, r1, g1, b1)))
                {
                    Pif_Paf(1);
                    break;
                }
            }
            L(1, 5);
            cnt++;
            if(cnt > 4)
                break;
        }
        cube.ZCube(1);
        cube.AllCube(3);
    }
}

void SecondRight()
{
    L(3, 5);
    L(3, 1);
    L(1, 5);
    L(1, 1);
    L(1, 2);
    L(1, 1);
    L(3, 2);
    L(3, 1);
}
void SecondLeft()
{
    L(1, 5);
    L(3, 0);
    L(3, 5);
    L(1, 0);
    L(3, 2);
    L(1, 0);
    L(1, 2);
    L(3, 0);
}

void SecondLayer()
{
    int i = 4;
    while(i--)
    {
        if(!CheckColor(2, 0, 1, 1, 1, 1, 0) && !CheckColor(2, 0, 1, 4, 1, 1, 0))
        {
            while(!CheckColor(1, 0, 2, 5, 1, 1, 0) && !CheckColor(1, 0, 2, 1, 1, 1, 0))
            {
                L(1, 5);
            }
            SecondRight();
        }
        if(!CheckColor(0, 0, 1, 1, 1, 1, 0) && !CheckColor(0, 0, 1, 2, 1, 1, 0))
        {
            while(!CheckColor(1, 0, 2, 5, 1, 1, 0) && !CheckColor(1, 0, 2, 1, 1, 1, 0))
            {
                L(1, 5);
            }
            SecondLeft();
        }
        cube.ZCube(1);
        cube.AllCube(3);
    }
    i = 5;
    while(i--)
    {
        double r = cube.ArrColor[1][0][1][1].r;
        double g = cube.ArrColor[1][0][1][1].g;
        double b = cube.ArrColor[1][0][1][1].b;
        int cnt = 0;
        while((!CheckColor(1, 0, 2, 1, r, g, b) || CheckColor(1, 0, 2, 5, 1, 1, 0)) && cnt <= 4)
        {
            cnt++;
            L(1, 5);
        }
        if(CheckColor(1, 0, 2, 1, r, g, b) && !CheckColor(1, 0, 2, 5, 1, 1, 0))
        {
            if(CheckColor(1, 0, 2, 5, cube.ArrColor[0][0][0][2].r, cube.ArrColor[0][0][0][2].g, cube.ArrColor[0][0][0][2].b))
            {
                SecondLeft();
            }
            else if(CheckColor(1, 0, 2, 5, cube.ArrColor[2][0][0][4].r, cube.ArrColor[2][0][0][4].g, cube.ArrColor[2][0][0][4].b))
            {
                SecondRight();
            }
        }
        cnt = 0;
        while((!CheckColor(1, 0, 2, 1, r, g, b) || CheckColor(1, 0, 2, 5, 1, 1, 0)) && cnt <= 4)
        {
            cnt++;
            L(1, 5);
        }
        if(CheckColor(1, 0, 2, 1, r, g, b) && !CheckColor(1, 0, 2, 5, 1, 1, 0))
        {
            if(CheckColor(1, 0, 2, 5, cube.ArrColor[0][0][0][2].r, cube.ArrColor[0][0][0][2].g, cube.ArrColor[0][0][0][2].b))
            {
                SecondLeft();
            }
            else if(CheckColor(1, 0, 2, 5, cube.ArrColor[2][0][0][4].r, cube.ArrColor[2][0][0][4].g, cube.ArrColor[2][0][0][4].b))
            {
                SecondRight();
            }
        }
        cube.ZCube(1);
        cube.AllCube(3);
    }
}
void kek()
{
    L(1, 2);
    L(3, 5);
    L(3, 1);
    L(1, 5);
    L(1, 1);
    L(3, 2);
}

void beside()
{
    while(!CheckColor(1, 2, 2, 3, cube.ArrColor[1][2][1][3].r, cube.ArrColor[1][2][1][3].g, cube.ArrColor[1][2][1][3].b)
            || !CheckColor(2, 1, 2, 4, cube.ArrColor[2][1][1][4].r, cube.ArrColor[2][1][1][4].g, cube.ArrColor[2][1][1][4].b))
    {
        cube.ZCube(1);
        cube.AllCube(3);
    }
    L(3, 1);
    L(3, 5);
    L(1, 1);
    L(3, 5);
    L(3, 1);
    L(2, 5);
    L(1, 1);
    L(3, 5);
}
void opposite()
{
    while(!CheckColor(1, 2, 2, 3, cube.ArrColor[1][2][1][3].r, cube.ArrColor[1][2][1][3].g, cube.ArrColor[1][2][1][3].b)
            || !CheckColor(1, 0, 2, 1, cube.ArrColor[1][0][2][1].r, cube.ArrColor[1][0][2][1].g, cube.ArrColor[1][0][2][1].b))
    {
        cube.ZCube(1);
        cube.AllCube(3);
    }
    L(3, 1);
    L(3, 5);
    L(1, 1);
    L(3, 5);
    L(3, 1);
    L(2, 5);
    L(1, 1);
    beside();
}

void UpLayer()
{
    int i = 4;
    while(i--)
    {
        if(CheckColor(0, 1, 2, 5, 1, 1, 0) && CheckColor(1, 1, 2, 5, 1, 1, 0) && CheckColor(1, 2, 2, 5, 1, 1, 0) &&
                CheckColor(1, 0, 2, 5, 1, 1, 0) && CheckColor(2, 1, 2, 5, 1, 1, 0))
        {
            break;
        }
        if(CheckColor(0, 1, 2, 5, 1, 1, 0) && CheckColor(1, 1, 2, 5, 1, 1, 0) && CheckColor(1, 2, 2, 5, 1, 1, 0) &&
                !CheckColor(1, 0, 2, 5, 1, 1, 0) && !CheckColor(2, 1, 2, 5, 1, 1, 0))
        {
            L(1, 2);
            L(3, 5);
            L(3, 1);
            L(1, 5);
            L(1, 1);
            L(3, 2);
            break;
        }
        if(CheckColor(0, 1, 2, 5, 1, 1, 0) && CheckColor(1, 1, 2, 5, 1, 1, 0) && CheckColor(2, 1, 2, 5, 1, 1, 0))
        {
            L(1, 2);
            Pif_Paf(1);
            L(3, 2);
            break;
        }
        L(1, 2);
        Pif_Paf(1);
        L(3, 2);
        i++;
        cube.ZCube(1);
        cube.AllCube(3);
    }
    i = 4;

    while(i--)
    {
        int cnt = 0;
        vector<int> pos;
        for(int j = 0; j < 4; j++)
        {
            if(CheckColor(1, 0, 2, 1, cube.ArrColor[1][0][1][1].r, cube.ArrColor[1][0][1][1].g, cube.ArrColor[1][0][1][1].b))
            {
                cnt++;
                pos.push_back(j);
            }
            cube.ZCube(1);
            cube.AllCube(3);
        }
        if(cnt == 4)
        {
            return;
        }
        if(cnt == 2)
        {
            if(pos[1] - pos[0] == 2)
            {
                opposite();
            }
            else
            {
                beside();
            }
        }
        L(1, 5);
    }
}

void UpCorners()
{
    int i = 4;
    int cnt = 0;
    vector<int> index = {1, 4, 5};
    while(i--)
    {
        int c = 0;
        double r1 = cube.ArrColor[2][0][0][1].r;
        double g1 = cube.ArrColor[2][0][0][1].g;
        double b1 = cube.ArrColor[2][0][0][1].b;
        double r2 = cube.ArrColor[2][0][0][4].r;
        double g2 = cube.ArrColor[2][0][0][4].g;
        double b2 = cube.ArrColor[2][0][0][4].b;
        vector<rgb> s;
        for(int j = 0; j < 3; j++)
        {
            s.push_back(cube.ArrColor[2][0][2][index[j]]);
        }
        for(int j = 0; j < 3; j++)
        {
            if(s[j] == rgb{r1, g1, b1} || s[j] == rgb{r2, g2, b2})
            {
                c++;
            }
        }
        if(c == 2)
        {
            cnt++;
        }
        cube.ZCube(1);
        cube.AllCube(3);
    }
    if(!cnt)
    {
        L(3, 1);
        L(1, 5);
        L(3, 0);
        L(3, 5);
        L(1, 1);
        L(1, 5);
        L(1, 0);
        L(3, 5);
    }
    int it = 0;
    while(1)
    {
        it++;
        double r1 = cube.ArrColor[0][2][0][2].r;
        double g1 = cube.ArrColor[0][2][0][2].g;
        double b1 = cube.ArrColor[0][2][0][2].b;
        double r2 = cube.ArrColor[0][2][0][3].r;
        double g2 = cube.ArrColor[0][2][0][3].g;
        double b2 = cube.ArrColor[0][2][0][3].b;
        vector<rgb> corner;
        index = {2, 3, 5};
        for(int i = 0; i < 3; i++)
        {
            corner.push_back(cube.ArrColor[0][2][2][index[i]]);
        }
        int c = 0;
        for(int i = 0; i < 3; i++)
        {
            if(corner[i] == rgb{r1, g1, b1} || corner[i] == rgb{r2, g2, b2})
            {
                c++;
            }
        }
        if(c == 2)
        {
            break;
        }
        cube.ZCube(1);
        cube.AllCube(3);
    }

    double r1 = cube.ArrColor[0][0][0][2].r;
    double g1 = cube.ArrColor[0][0][0][2].g;
    double b1 = cube.ArrColor[0][0][0][2].b;
    double r2 = cube.ArrColor[0][0][0][1].r;
    double g2 = cube.ArrColor[0][0][0][1].g;
    double b2 = cube.ArrColor[0][0][0][1].b;

    while(1)
    {
        vector<rgb> corner;
        index = {1, 2,5};
        for(int i = 0; i < 3; i++)
        {
            corner.push_back(cube.ArrColor[0][0][2][index[i]]);
        }
        int c = 0;
        for(int i = 0; i < 3; i++)
        {
            if(corner[i] == rgb{r1, g1, b1} || corner[i] == rgb{r2, g2, b2})
            {
                c++;
            }
        }
        if(c == 2)
        {
            break;
        }
        L(1, 1);
        L(3, 5);
        L(1, 0);
        L(1, 5);
        L(3, 1);
        L(3, 5);
        L(3, 0);
        L(1, 5);
    }
    cube.XCube(1);
    cube.AllCube(1);
    cube.XCube(1);
    cube.AllCube(1);
    i = 4;
    while(i--)
    {
        if(CheckColor(2, 0, 0, 1, 1, 1, 0))
        {
            Pif_Paf(4);
        }
        else if(CheckColor(2, 0, 0, 4, 1, 1, 0))
        {
            Pif_Paf(2);
        }
        L(1, 4);
    }
}
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;

    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          600,
                          600,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);
    glEnable(GL_DEPTH_TEST);
    glFrustum(-1, 1, -1, 1, 2, 80);
    glTranslatef(0, 0, -4);
    fillArr();
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                cube.ArrColor[i][j][k][0] = (rgb)
                {
                    1, 1, 1
                }; /// red
                cube.ArrColor[i][j][k][1] = (rgb)
                {
                    0, 0, 1
                }; /// green
                cube.ArrColor[i][j][k][2] = (rgb)
                {
                    1, 0.6, 0
                }; /// blue
                cube.ArrColor[i][j][k][3] = (rgb)
                {
                    0, 1, 0
                }; /// yellow
                cube.ArrColor[i][j][k][4] = (rgb)
                {
                    1, 0, 0
                }; /// orange
                cube.ArrColor[i][j][k][5] = (rgb)
                {
                    1, 1, 0
                }; /// white
                for(int t = 0; t < 6; t++)
                {
                    cube.NewColor[i][j][k][t] = (rgb)cube.ArrColor[i][j][k][t];
                }
            }
        }
    }
    cube.clear_();
    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */
            glClearColor(0.8f, 0.0f, 0.52f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            if(GetKeyState('J') < 0)
            {
                PlaySound("rubiks_cube.wav", NULL, SND_ASYNC);
                L(1, Planes.l);
            }
            if(GetKeyState('L') < 0)
            {
                PlaySound("rubiks_cube.wav", NULL, SND_ASYNC);
                L(1, Planes.r);
            }

            if(GetKeyState('I') < 0)
            {
                PlaySound("rubiks_cube.wav", NULL, SND_ASYNC);
                L(1, Planes.b);
            }

            if(GetKeyState('K') < 0)
            {
                PlaySound("rubiks_cube.wav", NULL, SND_ASYNC);
                L(1, Planes.f);
            }

            if(GetKeyState('N') < 0)
            {
                PlaySound("rubiks_cube.wav", NULL, SND_ASYNC);
                L(1, Planes.d);
            }
            if(GetKeyState('M') < 0)
            {
                PlaySound("rubiks_cube.wav", NULL, SND_ASYNC);
                L(1, Planes.u);
            }
            glPushMatrix();
            camera.Apply();
            camera.Move();
            ShowWorld();
            cube.Show();
            glPopMatrix();
            SwapBuffers(hDC);
            if(GetKeyState('Q') < 0)
            {
                CrossF();
                MakeFront();
                MakeAngles();
                SecondLayer();
                UpLayer();
                UpCorners();
            }
            Sleep (1);
        }

    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    case WM_DESTROY:
        return 0;

    case WM_SETCURSOR:
        ShowCursor(FALSE);
        break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
    }
    break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

