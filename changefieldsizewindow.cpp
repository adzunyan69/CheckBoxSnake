#include "changefieldsizewindow.h"
#include "ui_changefieldsizewindow.h"

changeFieldSizeWindow::changeFieldSizeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeFieldSizeWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Изменение размеров окна");

    QIntValidator *fieldSizeValidator = new QIntValidator(3, 35, this);
    ui->lineEdit_x->setValidator(fieldSizeValidator);
    ui->lineEdit_y->setValidator(fieldSizeValidator);
}

changeFieldSizeWindow::~changeFieldSizeWindow()
{
    delete ui;
}

void changeFieldSizeWindow::setFieldSize(QPoint &_fieldSize)
{
    ui->lineEdit_x->setText(QString::number(_fieldSize.x()));
    ui->lineEdit_y->setText(QString::number(_fieldSize.y()));

    fieldSize = _fieldSize;
}

QPoint changeFieldSizeWindow::getFieldSize()
{
    return fieldSize;
}

void changeFieldSizeWindow::on_lineEdit_x_textEdited(const QString &newX)
{
    if(ui->lineEdit_x->hasAcceptableInput())
        fieldSize.setX(newX.toInt());
}

void changeFieldSizeWindow::on_lineEdit_y_textEdited(const QString &newY)
{
    if(ui->lineEdit_y->hasAcceptableInput())
        fieldSize.setY(newY.toInt());
}
