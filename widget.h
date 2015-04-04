#ifndef WIDGET_H
#define WIDGET_H
#include "glwidget.h"
#include <QWidget>
#include <QPushButton>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:

    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    QPushButton* paintButton;
    QPushButton* clearButton;
    GLWidget* glWidget;
    Ui::Widget *ui;
};

#endif // WIDGET_H
