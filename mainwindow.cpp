#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connectObjects();
    setupField();
    setupSnake();
    setupWindow();

    snake.start();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectObjects()
{
    connect(&snake, SIGNAL(snakeBodyChanged(const SnakeBody&)), this, SLOT(drawSnake(const SnakeBody&)));
    connect(&snake, SIGNAL(gameOver()), this, SLOT(gameOver()));
    connect(&snake, SIGNAL(snakeNeedsFood()), this, SLOT(spawnFood()));
    connect(this, SIGNAL(directionChanged(Snake::Direction)), &snake, SLOT(directionChange(Snake::Direction)));
    connect(this, SIGNAL(foodSpawned(QPoint)), &snake, SLOT(foodSpawned(QPoint)));
}

void MainWindow::setupField()
{
    fieldSize = QPoint(10, 10);

    field = Field(fieldSize.x(), QVector<QCheckBox*>(fieldSize.y(), nullptr));
    for(int i = 0; i < fieldSize.x(); i++)
    {
        for(int j = 0; j < fieldSize.y(); j++)
        {
            field[i][j] = new QCheckBox(this);
            ui->gridLayout->addWidget(field[i][j], j, i, Qt::AlignCenter);
        }
    }

    spawnFood();
}

void MainWindow::setupSnake()
{
    snake.setFieldSize(fieldSize);
}

void MainWindow::setupWindow()
{
    this->setWindowTitle("CheckBoxSnake");
    this->setFixedSize(fieldSize.x()*25, fieldSize.y()*25);
    lvlLabel = new QLabel(this);
    ui->statusbar->addWidget(lvlLabel);
}

void MainWindow::drawSnake(const SnakeBody &snakeBody)
{
    clearField();

    for(QPoint point: snakeBody)
    {
        QCheckBox *cb = field[point.x()][point.y()];
        cb->setCheckState(Qt::CheckState::PartiallyChecked);
        currSnakeBody = snakeBody;
    }

    lvlLabel->setText("Score: " + QString::number(snake.getLvl()));
}

void MainWindow::spawnFood()
{
    int x = QRandomGenerator::global()->bounded(0, fieldSize.x() - 1);
    int y = QRandomGenerator::global()->bounded(0, fieldSize.y() - 1);
    if(field[x][y]->isChecked())
        spawnFood();
    else
    {
        field[x][y]->setChecked(true);
        emit foodSpawned(QPoint(x, y));
        qDebug() << "Food spawned at " << x << " " << y;
    }

}

void MainWindow::clearField()
{
    for(const QPoint &point: currSnakeBody)
        field[point.x()][point.y()]->setChecked(false);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "keyPress: " << event->key();
    if(event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
        emit directionChanged(Snake::UP);
    if(event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
        emit directionChanged(Snake::DOWN);
    if(event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
        emit directionChanged(Snake::LEFT);
    if(event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
        emit directionChanged(Snake::RIGHT);
}

void MainWindow::gameOver()
{
    QMessageBox::information(this, "Game Over", "Поигали и хватит. Количество очков: " + QString::number(snake.getLvl()));
    qApp->exit();
}
