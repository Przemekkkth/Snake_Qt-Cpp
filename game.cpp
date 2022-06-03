#include "game.h"
#include <QDebug>
Game::Game() :
    N(30), M(20),
    size(16), RESOLUTION(QSize(size*N, size*M)), dir(0), num(4),
    PATH_TO_GREEN_PIXMAP(":/images/green.png"), PATH_TO_RED_PIXMAP(":/images/red.png"),
    PATH_TO_WHITE_PIXMAP(":/images/white.png"), ITERATION_VALUE(1000.0f/60.0f), DELAY(200.0f),
    m_deltaTime(0.0f)
{
    srand(time(0));
}

void Game::Tick()
{

    for (int i=num;i>0;--i)
    {
        s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
    }

    if (dir==0) s[0].y+=1;
    if (dir==1) s[0].x-=1;
    if (dir==2) s[0].x+=1;
    if (dir==3) s[0].y-=1;

    qDebug() << "s[0].x " << s[0].x << " s[0].y " << s[0].y;
    if ((s[0].x==(f.x/size)) && (s[0].y == (f.y/size)))
    {
        num++;
        f.x=rand() % N * size;
        f.y=rand() % M * size;
    }

    if (s[0].x>N) s[0].x=0;  if (s[0].x<0) s[0].x=N;
    if (s[0].y>M) s[0].y=0;  if (s[0].y<0) s[0].y=M;

    for (int i=1;i<num;i++)
        if (s[0].x==s[i].x && s[0].y==s[i].y)  num=i;
}
