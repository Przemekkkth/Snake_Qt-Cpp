#ifndef GAME_H
#define GAME_H
#include <QSize>

struct Snake
{ int x,y;};

struct Fruct
{ int x,y;};

class Game
{
public:
    Game();
    void Tick();
    const int N, M;
    const int size;
    QSize RESOLUTION;
    Fruct f;
    Snake s[100];
    int dir,num;
    const QString PATH_TO_GREEN_PIXMAP;
    const QString PATH_TO_RED_PIXMAP;
    const QString PATH_TO_WHITE_PIXMAP;
    const float ITERATION_VALUE;
    const float DELAY;
    float m_deltaTime;
};

#endif // GAME_H
