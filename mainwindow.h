#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QCheckBox>
#include <QKeyEvent>
#include "snake.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    using Field = QVector<QVector<QCheckBox*>>;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void drawSnake(const SnakeBody &snake);


protected:
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::MainWindow *ui;

    Snake snake;
    Field field;

    void setupField();
    void clearField();

    QPoint fieldSize;

signals:

    void directionChanged(Snake::Direction direction);



};
#endif // MAINWINDOW_H
