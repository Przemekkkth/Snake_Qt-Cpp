#include "game.h"
#include <QDebug>
Game::Game() :
    N(30), M(20),
    size(16), RESOLUTION(QSize(size*N, size*M)), dir(0), num(4),
    PATH_TO_EMPTY_PIXMAP(":/images/empty.png"),
    PATH_TO_TAIL_PIXMAP(":/images/tail.png"),
    PATH_TO_HEAD_PIXMAP(":/images/head.png"),
    PATH_TO_FRUIT_PIXMAP(":/images/fruit.png"),
    PATH_TO_PAUSE_BG_PIXMAP(":/images/bg_pause.png"),
    PATH_TO_GAME_OVER_BG_PIXMAP(":/images/bg_gameover.png"),
    ITERATION_VALUE(1000.0f/60.0f), DELAY(200.0f), ORIGINAL_DELAY(200.0f),
    TILE_SIZE(QSize(16,16)),
    m_deltaTime(0.0f),
    m_score(0),
    m_state(State::Active)
{
    srand(time(0));
    for(int i = 0; i < 100; ++i)
    {
        s[i].x = 0;
        s[i].y = 0;
    }
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

    if ((s[0].x==(f.x/size)) && (s[0].y == (f.y/size)))
    {
        num++;
        f.x=rand() % N * size;
        f.y=rand() % M * size;
        m_score += 2;
        DELAY -= 2;
    }

    if (s[0].x>N)
    {
        s[0].x=0;
    }
    if (s[0].x<0)
    {
        s[0].x=N;
    }
    if (s[0].y>M)
    {
        s[0].y=0;
    }
    if (s[0].y<0)
    {
        s[0].y=M;
    }

    for (int i=1;i<num;i++)
    {
        if (s[0].x == s[i].x && s[0].y == s[i].y)
        {
            qDebug() << "Game Over";
            num=i;
        }
    }

}
