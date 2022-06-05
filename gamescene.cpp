#include "gamescene.h"
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QDir>

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
            if(m_game.dir != 2 && m_game.m_state == Game::State::Active)
            {
                m_game.dir = 1;
            }
        }
            break;
        case Qt::Key_Right:
        {
            if(m_game.dir != 1 && m_game.m_state == Game::State::Active)
            {
                m_game.dir = 2;
            }
        }
            break;
        case Qt::Key_Up:
        {
            if(m_game.dir != 0 && m_game.m_state == Game::State::Active)
            {
                m_game.dir = 3;
            }
        }
            break;
        case Qt::Key_Down:
        {
            if(m_game.dir != 3 && m_game.m_state == Game::State::Active)
            {
                m_game.dir = 0;
            }
        }
            break;
        case Qt::Key_P:
        {
            if(m_game.m_state == Game::State::Active)
            {
                m_game.m_state = Game::State::Pause;
            }
            else if(m_game.m_state == Game::State::Pause)
            {
                m_game.m_state = Game::State::Active;
            }
        }
            break;
        case Qt::Key_R:
        {
            if(m_game.m_state == Game::State::GameOver)
            {
              m_game.Reset();
            }
        }
            break;
        case Qt::Key_Z:
        {
            //renderScene(); //uncomment if want to make screenshots
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

    if(m_pauseBgPixmap.load(m_game.PATH_TO_PAUSE_BG_PIXMAP))
    {
        qDebug() << "PauseBgPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "PauseBgPixmap is not loaded successfully";
    }

    if(m_gameOverPixmap.load(m_game.PATH_TO_GAME_OVER_BG_PIXMAP))
    {
        qDebug() << "GameOverBgPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "GameOverBgPixmap is not loaded successfully";
    }
}

void GameScene::renderScene()
{
    static int index = 0;
    QString fileName = QDir::currentPath() + QDir::separator() + "screen" + QString::number(index++) + ".png";
    QRect rect = sceneRect().toAlignedRect();
    QImage image(rect.size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    render(&painter);
    image.save(fileName);
    qDebug() << "saved " << fileName;
}

void GameScene::update()
{
    clear();
    if(m_game.m_state == Game::State::Active)
    {
        m_game.m_deltaTime += m_game.ITERATION_VALUE;
        if(m_game.m_deltaTime > m_game.DELAY)
        {
            m_game.m_deltaTime = 0.0f;
            m_game.Tick();
        }
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

    QGraphicsPixmapItem *headItemPixmap = new QGraphicsPixmapItem(m_headPixmap.copy(m_game.dir * m_game.TILE_SIZE.width(), 0, m_game.TILE_SIZE.width(), m_game.TILE_SIZE.height()));
    headItemPixmap->setPos(m_game.s[0].x * m_game.size, m_game.s[0].y * m_game.size);
    addItem(headItemPixmap);

    for (int i = 1; i < m_game.num; i++)
    {
        QGraphicsPixmapItem *tailItemPixmap = new QGraphicsPixmapItem(m_tailPixmap);
        tailItemPixmap->setPos(m_game.s[i].x * m_game.size, m_game.s[i].y * m_game.size);
        addItem(tailItemPixmap);
    }

    QGraphicsPixmapItem *fruitPixmapItem = new QGraphicsPixmapItem(m_fruitPixmap);
    fruitPixmapItem->setPos(m_game.f.x, m_game.f.y);
    addItem(fruitPixmapItem);

    if(m_game.m_state == Game::State::Pause)
    {
        QGraphicsPixmapItem *pauseBgPixmapItem = new QGraphicsPixmapItem(m_pauseBgPixmap.scaled(m_game.RESOLUTION.width(), m_game.RESOLUTION.height()));
        addItem(pauseBgPixmapItem);
    }
    else if(m_game.m_state == Game::State::GameOver)
    {
        QGraphicsPixmapItem *headItemPixmap = new QGraphicsPixmapItem(m_headPixmap.copy(m_game.dir * m_game.TILE_SIZE.width(), 0, m_game.TILE_SIZE.width(), m_game.TILE_SIZE.height()));
        headItemPixmap->setPos(m_game.s[0].x * m_game.size, m_game.s[0].y * m_game.size);
        addItem(headItemPixmap);
        QGraphicsPixmapItem *gameOverBgPixmapItem = new QGraphicsPixmapItem(m_gameOverPixmap.scaled(m_game.RESOLUTION.width(), m_game.RESOLUTION.height()));
        addItem(gameOverBgPixmapItem);
    }
}
