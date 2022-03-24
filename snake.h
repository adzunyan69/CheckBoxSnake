#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QPoint>
#include <QRandomGenerator>
#include <qmath.h>


class Snake : public QObject
{
    Q_OBJECT


public:
    using SnakeBody = QVector<QPoint>;

    enum class Direction { UP, DOWN, LEFT, RIGHT } direction;

    explicit Snake(QObject *parent = nullptr);
    void start();
    void setFieldSize(const QPoint &_fieldSize) { fieldSize = _fieldSize; }
    void setFieldSize(const unsigned &x, const unsigned &y) { fieldSize.setX(x); fieldSize.setY(y); }
    int getLvl() const { return lvl; }
    void pause() { stepTimer.stop(); }
    void resume() { stepTimer.start(); }

public slots:
    void directionChange(const Snake::Direction &_direction);
    void snakeLvlUp();
    void snakeStep();
    void foodSpawned(const QPoint &food) { qDebug() << "Spawn FOOD!!!" << food; currentFood = food; }
signals:
    void snakeBodyChanged(const SnakeBody &snakeBody);
    void foodEaten();
    void snakeNeedsFood();
    void gameOver();

private:
    void setStartSnakeBody();
    bool isEat() const;
    bool isCollision() const;

    SnakeBody snakeBody {};
    int lvl { 1 };
    QTimer stepTimer;
    QPoint fieldSize { 0, 0 };
    QPoint currentFood { 0, 0 };
};

#endif // SNAKE_H
