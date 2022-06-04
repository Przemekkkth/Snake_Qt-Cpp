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
    m_game.Tick();
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
            if(m_game.dir != 2)
            {
                m_game.dir = 1;
            }
        }
            break;
        case Qt::Key_Right:
        {
            if(m_game.dir != 1)
            {
                m_game.dir = 2;
            }
        }
            break;
        case Qt::Key_Up:
        {
            if(m_game.dir != 0)
            {
                m_game.dir = 3;
            }
        }
            break;
        case Qt::Key_Down:
        {
            if(m_game.dir != 3)
            {
                m_game.dir = 0;
            }
        }
            break;
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::loadPixmap()
{

    if(m_headPixmap.load(m_game.PATH_TO_HEAD_PIXMAP))
    {
        qDebug() << "HeadPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "HeadPixmap is not loaded successfully";
    }

    if(m_tailPixmap.load(m_game.PATH_TO_TAIL_PIXMAP))
    {
        qDebug() << "TailPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "TailPixmap is not loaded successfully";
    }

    if(m_emptyPixmap.load(m_game.PATH_TO_EMPTY_PIXMAP))
    {
        qDebug() << "EmptyPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "EmptyPixmap is not loaded successfully";
    }

    if(m_fruitPixmap.load(m_game.PATH_TO_FRUIT_PIXMAP))
    {
        qDebug() << "FruitPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "FruitPixmap is not loaded successfully";
    }
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
            QGraphicsPixmapItem *emptyItemPixmap = new QGraphicsPixmapItem(m_emptyPixmap);
            emptyItemPixmap->setPos(i*m_game.size, j*m_game.size);
            addItem(emptyItemPixmap);
        }
    }

    for (int i = 0; i < m_game.num; i++)
    {
        QGraphicsPixmapItem *tailItemPixmap = new QGraphicsPixmapItem(m_tailPixmap);
        tailItemPixmap->setPos(m_game.s[i].x * m_game.size, m_game.s[i].y * m_game.size);
        addItem(tailItemPixmap);
    }

    QGraphicsPixmapItem *fruitPixmapItem = new QGraphicsPixmapItem(m_fruitPixmap);
    fruitPixmapItem->setPos(m_game.f.x, m_game.f.y);
    addItem(fruitPixmapItem);
}
