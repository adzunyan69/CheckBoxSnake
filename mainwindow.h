#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QCheckBox>
#include <QKeyEvent>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QLabel>
#include "snake.h"
#include"changefieldsizewindow.h"

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
    void spawnFood();
    void gameOver();


protected:
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::MainWindow *ui;

    QLabel *lvlLabel;

    Snake *snake;
    SnakeBody currSnakeBody;
    Field field;
    bool firstSetup = true;

    void startSnake();
    void connectObjects();
    void setupField();
    void setupSnake();
    void setupWindow();
    void clearField();

    QPoint fieldSize = QPoint(10, 10);

signals:

    void directionChanged(Snake::Direction direction);
    void foodSpawned(QPoint foodPoint);



private slots:
    void on_actionChangeFieldSize_triggered();
};
#endif // MAINWINDOW_H
