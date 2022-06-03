#include "gamescene.h"
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsPixmapItem>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_game(), m_timer(new QTimer(this))
{
    setSceneRect(QRectF(0,0, m_game.RESOLUTION.width(), m_game.RESOLUTION.height()));
    loadPixmap();
    m_game.f.x = 0;
    m_game.f.y = 64;
    connect(m_timer, &QTimer::timeout, this, &GameScene::update);
    m_timer->start(m_game.ITERATION_VALUE);
}

void GameScene::keyPressEvent(QKeyEvent* event)
{
    if(!event->isAutoRepeat())
    {
        switch(event->key())
        {
        case Qt::Key_Left:
        {
            m_game.dir = 1;
        }
            break;
        case Qt::Key_Right:
        {
            m_game.dir = 2;
        }
            break;
        case Qt::Key_Up:
        {
            m_game.dir = 3;
        }
            break;
        case Qt::Key_Down:
        {
            m_game.dir = 0;
        }
            break;
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::loadPixmap()
{
    Q_ASSERT(m_greenPixmap.load(m_game.PATH_TO_GREEN_PIXMAP));
    Q_ASSERT(m_redPixmap.load(m_game.PATH_TO_RED_PIXMAP));
    Q_ASSERT(m_whitePixmap.load(m_game.PATH_TO_WHITE_PIXMAP));
}

void GameScene::update()
{

    clear();
    m_game.m_deltaTime += m_game.ITERATION_VALUE;
    if(m_game.m_deltaTime > m_game.DELAY)
    {
        m_game.m_deltaTime = 0.0f;
        m_game.Tick();
    }
    for (int i = 0; i < m_game.N; i++)
    {
        for (int j = 0; j < m_game.M; j++)
        {
            QGraphicsPixmapItem *whiteItemPixmap = new QGraphicsPixmapItem(m_whitePixmap);
            whiteItemPixmap->setPos(i*m_game.size, j*m_game.size);
            addItem(whiteItemPixmap);
        }
    }

    for (int i= 0; i < m_game.num; i++)
    {
        QGraphicsPixmapItem *redItemPixmap = new QGraphicsPixmapItem(m_redPixmap);
        redItemPixmap->setPos(m_game.s[i].x * m_game.size, m_game.s[i].y * m_game.size);
        addItem(redItemPixmap);
    }

    QGraphicsPixmapItem *greenPixmapItem = new QGraphicsPixmapItem(m_greenPixmap);
    greenPixmapItem->setPos(m_game.f.x, m_game.f.y);
    addItem(greenPixmapItem);
}
