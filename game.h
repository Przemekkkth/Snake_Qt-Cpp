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
    void Reset();
    const int N, M;
    const int size;
    QSize RESOLUTION;
    Fruct f;
    Snake s[100];
    int dir,num;

    const QString PATH_TO_EMPTY_PIXMAP;
    const QString PATH_TO_TAIL_PIXMAP;
    const QString PATH_TO_HEAD_PIXMAP;
    const QString PATH_TO_FRUIT_PIXMAP;
    const QString PATH_TO_PAUSE_BG_PIXMAP;
    const QString PATH_TO_GAME_OVER_BG_PIXMAP;

    const float ITERATION_VALUE;
    float DELAY;
    const float ORIGINAL_DELAY;
    const QSize TILE_SIZE;
    float m_deltaTime;
    int m_score;

    enum class State
    {
        Active, Pause, GameOver
    };
    State m_state;
};

#endif // GAME_H
