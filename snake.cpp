#include "snake.h"

Snake::Snake(QObject *parent) : QObject(parent)
{
    direction = Direction::RIGHT;
}

void Snake::setStartSnakeBody()
{
    snakeBody = { QPoint(QRandomGenerator::global()->bounded(0, fieldSize.x() - 1),
                  QRandomGenerator::global()->bounded(0, fieldSize.y() - 1)) };
}

void Snake::start()
{
    setStartSnakeBody();
    stepTimer.setInterval(1000);
    bool isConnect = connect(&stepTimer, &QTimer::timeout,
                             this, &Snake::snakeStep) &&
                     connect(this, &Snake::foodEaten,
                             this, &Snake::snakeLvlUp);
    if(isConnect == false)
    {
        qDebug() << "Connect signal and slots error.";
        return;
    }
    stepTimer.start();
    emit snakeBodyChanged(snakeBody);
}

void Snake::directionChange(const Snake::Direction &_direction)
{
    qDebug() << "Direction changed";
    if(snakeBody.size() == 1)
    {
        direction = _direction;
        return;
    }

    switch(_direction)
    {
    case Direction::UP:
        if(snakeBody.last().y() == (snakeBody.at(snakeBody.size() - 2).y() + 1))
            return;
        break;
    case Direction::DOWN:
        if(snakeBody.last().y() == (snakeBody.at(snakeBody.size() - 2).y() - 1))
            return;
        break;
    case Direction::LEFT:
        if(snakeBody.last().x() == (snakeBody.at(snakeBody.size() - 2).x() + 1))
            return;
        break;
    case Direction::RIGHT:
        if(snakeBody.last().x() == (snakeBody.at(snakeBody.size() - 2).x() - 1))
            return;
        break;

    default:
        qDebug() << "Error: unknown direction.";
        return;

    }

    direction = _direction;
}

void Snake::snakeLvlUp()
{
    snakeBody.resize(snakeBody.size() + 1);
    snakeBody.last() = currentFood;
    stepTimer.setInterval(1000/(std::log2(++lvl)));
    emit snakeBodyChanged(snakeBody);
    emit snakeNeedsFood();
}

void Snake::snakeStep()
{
    if(isEat())
    {
        qDebug() << "Snake has eaten food";
        emit foodEaten();
        return;
    }

    for(SnakeBody::iterator it = snakeBody.begin();  it != snakeBody.end() - 1; ++it)
        *it = *(it + 1);

    QPoint &head = snakeBody.last();
    switch(direction)
    {
    case Direction::UP:
        if(head.y() == 0)
            head.setY((fieldSize.y() - 1));
        else
        head.setY((head.y() - 1)%fieldSize.y());

        break;
    case Direction::DOWN:
        head.setY((head.y() + 1)%fieldSize.y());
        break;
    case Direction::LEFT:
        if(head.x() == 0)
            head.setX((fieldSize.x() - 1));
        else
            head.setX((head.x() - 1)%fieldSize.x());
        break;
    case Direction::RIGHT:
        head.setX((head.x() + 1)%fieldSize.x());
        break;

    default:
        qDebug() << "Error: unknown direction.";
        return;
    }

    emit snakeBodyChanged(snakeBody);
    qDebug() << "NewPosition: " << snakeBody;

    if(isCollision())
        emit gameOver();
}

bool Snake::isEat() const
{
    qDebug() << "currenFood: " << currentFood;
    switch (direction)
    {
    case Direction::UP:
        if((snakeBody.last().y() - 1) == currentFood.y() && snakeBody.last().x() == currentFood.x())
            return true;
        break;
    case Direction::DOWN:
        if((snakeBody.last().y() + 1) == currentFood.y() && snakeBody.last().x() == currentFood.x())
            return true;
        break;
    case Direction::LEFT:
        if((snakeBody.last().x() - 1) == currentFood.x() && snakeBody.last().y() == currentFood.y())
            return true;
        break;
    case Direction::RIGHT:
        if((snakeBody.last().x() + 1) == currentFood.x() && snakeBody.last().y() == currentFood.y())
            return true;
        break;
    }

    return false;
}

bool Snake::isCollision() const
{
    const QPoint &head = snakeBody.last();
    for(int i = 0; i < snakeBody.size() - 1; i++)
    {
        if(snakeBody.at(i).x() == head.x() && snakeBody.at(i).y() == head.y())
            return true;
    }
    return false;
}


