#include <bits/stdc++.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

bool gameover;
const int width=40;
const int height=20;
int x,y,fruitX, fruitY, score;
int tailX[200], tailY[200];
int tailsize;
enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void setup()
{
    gameover=false;
    dir=STOP;
    x=width/2;
    y=height/2;
    fruitX=rand()%width;
    fruitY=rand()%height;
    score=0;
}

void draw()
{
    system("cls");

    for (int i=0; i<width+2; i++)
    {
        cout<<"#";
    }
    cout<<endl;

    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width+1; j++)
            {
                if (j==0 or j==width)
                    cout<<"#";

                if (i==y && j==x)
                {
                    cout<<"O";
                }
                else if (i==fruitY && j==fruitX)
                {
                    cout<<"F";
                }
                else
                {
                    bool printed=false;
                    for (int k=0; k<tailsize; k++)
                    {
                        if (tailX[k]==j && tailY[k]==i)
                        {
                            cout<<"o";
                            printed=true;
                        }
                    }
                    if (printed==false)
                            cout<<" ";
                }
            }
            cout<<endl;
    }

    for (int i=0; i<width+2; i++)
    {
        cout<<"#";
    }
    cout<<endl;
    cout<<"score: "<<score<<endl;
}

void input()
{
    if (_kbhit())
    {
        switch(_getch())
        {
        case 'a':
            dir=LEFT;
            break;
        case 'w':
            dir=UP;
            break;
        case 's':
            dir=DOWN;
            break;
        case 'd':
            dir=RIGHT;
            break;
        case 'g':
            gameover=true;
            break;
        }
    }
}

void logic()
{
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X, prev2Y;
    tailX[0]=x;
    tailY[0]=y;

    for (int i=1; i<tailsize; i++)
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }

    switch(dir)
    {
        case LEFT:
            x--;
            Sleep(25);
            break;
        case DOWN:
            y++;
            Sleep(70);
            break;
        case UP:
            y--;
            Sleep(70);
            break;
        case RIGHT:
            x++;
            Sleep(25);
            break;
        default:
            break;
    }
    if (x>width-1)
    {
        x=0;
    }
    if (x<0)
    {
        x=width-1;
    }
    if (y>height-1)
    {
        y=0;
    }
    if (y<0)
    {
        y=height-1;
    }

    for (int i=0; i<tailsize; i++)
    {
        if (tailX[i]==x && tailY[i]==y)
            gameover=true;
    }

    if (x==fruitX && y==fruitY)
    {
        tailsize++;
        score++;
        fruitX=rand()%width;
        fruitY=rand()%height;
    }
}

int main()
{
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursoInfo;
    CursoInfo.dwSize=1;
    CursoInfo.bVisible=false;
    SetConsoleCursorInfo(hConsole, &CursoInfo);

    setup();
    while(!gameover)
    {
        draw();
        input();
        logic();
    }
    return 0;
}
