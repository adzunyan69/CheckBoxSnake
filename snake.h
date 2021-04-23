#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QPoint>

using SnakeBody = QVector<QPoint>;

class Snake : public QObject
{
    Q_OBJECT



    SnakeBody snakeBody;
    QTimer stepTimer;

    QPoint fieldSize;

public:
    enum Direction { UP, DOWN, LEFT, RIGHT } direction;

    explicit Snake(QObject *parent = nullptr);
    void start();
    void setFieldSize(QPoint _fieldSize) { fieldSize = _fieldSize; }
    void setFieldSize(unsigned x, unsigned y) { fieldSize.setX(x); fieldSize.setY(y); }

public slots:
    void directionChange(Snake::Direction _direction);
    void snakeLvlUp() { }
    void snakeStep();
signals:
    void snakeBodyChanged(const SnakeBody &snakeBody);
};

#endif // SNAKE_H
