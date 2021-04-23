#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fieldSize = QPoint(25, 25);
    setupField();

    //field[3][2]->setChecked(true);
    snake.setFieldSize(fieldSize);

    connect(&snake, SIGNAL(snakeBodyChanged(const SnakeBody&)), this, SLOT(drawSnake(const SnakeBody&)));
    connect(this, SIGNAL(directionChanged(Snake::Direction)), &snake, SLOT(directionChange(Snake::Direction)));
    snake.start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupField()
{
    field = Field(fieldSize.x(), QVector<QCheckBox*>(fieldSize.y(), nullptr));
    for(int i = 0; i < fieldSize.x(); i++)
    {
        for(int j = 0; j < fieldSize.y(); j++)
        {
            field[i][j] = new QCheckBox(this);
            ui->gridLayout->addWidget(field[i][j], j, i, Qt::AlignCenter);
        }
    }
}

void MainWindow::drawSnake(const SnakeBody &snake)
{
    clearField();

    for(QPoint point: snake)
    {
        field[point.x()][point.y()]->setChecked(true);
    }
}

void MainWindow::clearField()
{
    for(int i = 0; i < fieldSize.x(); i++)
    {
        for(int j = 0; j < fieldSize.y(); j++)
        {
            field[i][j]->setChecked(false);
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
        emit directionChanged(Snake::UP);
    if(event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
        emit directionChanged(Snake::DOWN);
    if(event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
        emit directionChanged(Snake::LEFT);
    if(event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
        emit directionChanged(Snake::RIGHT);
}
