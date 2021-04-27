#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    startSnake();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startSnake()
{
    snake = new Snake(this);
    connectObjects();
    setupField();
    setupSnake();
    setupWindow();

    firstSetup = false;

    snake->start();
}

void MainWindow::connectObjects()
{
    connect(snake, SIGNAL(snakeBodyChanged(const SnakeBody&)), this, SLOT(drawSnake(const SnakeBody&)));
    connect(snake, SIGNAL(gameOver()), this, SLOT(gameOver()));
    connect(snake, SIGNAL(snakeNeedsFood()), this, SLOT(spawnFood()));
    connect(this, SIGNAL(directionChanged(Snake::Direction)), snake, SLOT(directionChange(Snake::Direction)));
    connect(this, SIGNAL(foodSpawned(QPoint)), snake, SLOT(foodSpawned(QPoint)));
}

void MainWindow::setupField()
{

    field.clear();

    field = Field(fieldSize.x(), QVector<QCheckBox*>(fieldSize.y(), nullptr));

    for(int i = 0; i < fieldSize.x(); i++)
    {
        for(int j = 0; j < fieldSize.y(); j++)
        {
            field[i][j] = new QCheckBox(this);
            field[i][j]->setAttribute(Qt::WA_TransparentForMouseEvents);
            field[i][j]->setFocusPolicy(Qt::NoFocus);
            ui->gridLayout->addWidget(field[i][j], j, i, Qt::AlignCenter);
        }
    }

    spawnFood();
}

void MainWindow::setupSnake()
{
    snake->setFieldSize(fieldSize);
}

void MainWindow::setupWindow()
{
    this->setWindowTitle("CheckBoxSnake");
    this->setFixedSize(fieldSize.x()*25, fieldSize.y()*25);
    if(firstSetup)
    {
        lvlLabel = new QLabel(this);
        ui->statusbar->insertWidget(0, lvlLabel);
    }
    lvlLabel->setText("Score: " + QString::number(snake->getLvl()));
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

    lvlLabel->setText("Score: " + QString::number(snake->getLvl()));
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
    qDebug() << "keyPress: " << event->nativeScanCode();
    if(event->text() == "w" || event->text() == "ц")
        emit directionChanged(Snake::UP);
    if(event->text() == "s" || event->text() == "ы")
        emit directionChanged(Snake::DOWN);
    if(event->text() == "a" || event->text() == "ф")
        emit directionChanged(Snake::LEFT);
    if(event->text() == "d" || event->text() == "в")
        emit directionChanged(Snake::RIGHT);
}

void MainWindow::gameOver()
{
    QMessageBox::information(this, "Game Over", "Поиграли и хватит. Количество очков: " + QString::number(snake->getLvl()));
    qApp->exit();
}

void MainWindow::on_actionChangeFieldSize_triggered()
{
    changeFieldSizeWindow changeFieldSize;
    changeFieldSize.setFieldSize(fieldSize);
    snake->pause();
    qDebug() << "ChangeFieldSize";
    if(changeFieldSize.exec() == QDialog::Accepted)
    {
        qDebug() << "Accepted";

        fieldSize = changeFieldSize.getFieldSize();
        qDebug() << fieldSize;

        startSnake();
    }
    else
        snake->resume();
}
