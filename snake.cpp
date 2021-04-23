#include "snake.h"

Snake::Snake(QObject *parent) : QObject(parent)
{
    snakeBody = {QPoint(0, 0), QPoint(1, 0), QPoint(1, 1)};
    direction = RIGHT;
}

void Snake::start()
{
    stepTimer.setInterval(500);
    connect(&stepTimer, SIGNAL(timeout()), this, SLOT(snakeStep()));
    stepTimer.start();
    emit snakeBodyChanged(snakeBody);
}

void Snake::directionChange(Snake::Direction _direction)
{
    qDebug() << "Direction change";
    if(snakeBody.size() == 1)
    {
        direction = _direction;
        return;
    }

    switch(_direction)
    {
    case UP:
        if(snakeBody.last().y() == (snakeBody.at(snakeBody.size() - 2).y() + 1))
            return;
        break;
    case DOWN:
        if(snakeBody.last().y() == (snakeBody.at(snakeBody.size() - 2).y() - 1))
            return;
        break;
    case LEFT:
        if(snakeBody.last().x() == (snakeBody.at(snakeBody.size() - 2).x() + 1))
            return;
        break;
    case RIGHT:
        if(snakeBody.last().x() == (snakeBody.at(snakeBody.size() - 2).x() - 1))
            return;
        break;

    default:
        qDebug() << "Error: unknown direction.";
        return;

    }

    direction = _direction;
}

void Snake::snakeStep()
{
    for(SnakeBody::iterator it = snakeBody.begin();  it != snakeBody.end() - 1; ++it)
        *it = *(it + 1);

    QPoint &head = snakeBody.last();
    switch(direction)
    {
    case UP:
        if(head.y() == 0)
            head.setY((fieldSize.y() - 1));
        else
        head.setY((head.y() - 1)%fieldSize.y());

        break;
    case DOWN:
        head.setY((head.y() + 1)%fieldSize.y());
        break;
    case LEFT:
        if(head.x() == 0)
            head.setX((fieldSize.x() - 1));
        else
            head.setX((head.x() - 1)%fieldSize.x());
        break;
    case RIGHT:
        head.setX((head.x() + 1)%fieldSize.x());
        break;

    default:
        qDebug() << "Error: unknown direction.";
        return;
    }

    emit snakeBodyChanged(snakeBody);
    qDebug() << "NewPosition: " << snakeBody;
}


