#ifndef CHANGEFIELDSIZEWINDOW_H
#define CHANGEFIELDSIZEWINDOW_H

#include <QDialog>
#include <QValidator>

namespace Ui {
class changeFieldSizeWindow;
}

class changeFieldSizeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit changeFieldSizeWindow(QWidget *parent = nullptr);
    ~changeFieldSizeWindow();

    void setFieldSize(const QPoint &_fieldSize);
    QPoint getFieldSize();

private slots:
    void on_lineEdit_x_textEdited(const QString &arg1);

    void on_lineEdit_y_textEdited(const QString &arg1);

private:
    QPoint fieldSize;

    Ui::changeFieldSizeWindow *ui;
};

#endif // CHANGEFIELDSIZEWINDOW_H
