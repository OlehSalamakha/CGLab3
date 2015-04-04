#include "widget.h"
#include "ui_widget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    glWidget = new GLWidget(this);

    ui->setupUi(this);
    paintButton = new QPushButton("Paint", this);

    clearButton = new QPushButton("Clear", this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QVBoxLayout *leftLayout = new QVBoxLayout();
    QVBoxLayout *rightLayout = new QVBoxLayout();



    rightLayout->addWidget(paintButton);
    rightLayout->addWidget(clearButton);
    leftLayout->addWidget(glWidget);
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    this->setLayout(mainLayout);

    connect(paintButton, SIGNAL(clicked()), glWidget, SLOT(drawGrapchic()));
    connect(clearButton, SIGNAL(clicked()), glWidget, SLOT(clearGraphic()));





}

Widget::~Widget()
{
    delete ui;
}
