#include "glwidget.h"
#include <iostream>

GLWidget::GLWidget(QWidget* parent):QGLWidget(parent)
{
    resize(300,300);

    rect = Rectangle(0.5, 0.3, 0.3, 0.3, 0.3, 0, 0.5, 0);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveRectangle()));
    timer->setInterval(1);
    timer->start();


}

void GLWidget::initializeGL() {
    qglClearColor(Qt::white);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0,0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void GLWidget::drawCoordinateSystem() {
    qglColor(Qt::black);

    glBegin(GL_LINES);
        glVertex3f(X_BEGIN, 0, 0);
        glVertex3f(X_END, 0, 0);
        glVertex3f(0, Y_END, 0);
        glVertex3f(0, Y_BEGIN, 0);

        //draw direction
        glVertex3f(X_BEGIN, 0, 0);
        glVertex3f(X_BEGIN+0.05, 0.015, 0);

        glVertex3f(X_BEGIN, 0, 0);
        glVertex3f(X_BEGIN+0.05, -0.015, 0);


        glVertex3f(0, Y_END, 0);
        glVertex3f(0.015, Y_END-0.05, 0);

        glVertex3f(0, Y_END, 0);
        glVertex3f(-0.015, Y_END-0.05, 0);


        int j = 1;
        for (float i=-10; i<10; i+=0.1) {
            if (j % 10 == 0) {

                //std::cout << i << std::endl;
                Point p = transofrmCoordinate(*(new Point(i, 0)));
                glVertex3f(p.x, 0.01, 0);
                glVertex3f(p.x, -0.01, 0);

                p = transofrmCoordinate(*(new Point(0, i)));
                glVertex3f(0.01, p.y, 0);
                glVertex3f(-0.01, p.y, 0);
            }
            j+=1;

        }
    glEnd();



    QFont *f = new QFont("Helevetica", 7);
    for (int i=-10; i<=10; i++) {
        Point p(i, 0);
        Point currentP = transofrmCoordinate(p);
        renderText(currentP.x, -0.05, 0, QString::number(i), *f);
    }

    for (int i=-10; i<=10; i++) {
        Point p(0, i);
        Point currentP = transofrmCoordinate(p);
        renderText(-0.05, currentP.y, 0, QString::number(i), *f);
    }

}

void GLWidget::drawFunction() {
    float xBegin = -PI;
    float xEnd = 3*PI;

    glPointSize(1);
    glBegin(GL_POINTS);
        while (xBegin <= xEnd) {
            float y = fabs(cos(xBegin));
            glColor3f(y+0.1, y-0.1, y+0.2);
            Point p(xBegin, cos(xBegin));
            Point currentP = transofrmCoordinate(p);
            glVertex3f(currentP.x, currentP.y, 0);
            xBegin += 0.0001;
        }
    glEnd();
}

void GLWidget::paintGL() {

    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    qglColor(Qt::black);
    //glTranslatef(rect.p1.x, rect.p1.y, 0);

glTranslatef(xOffset,yOffset,0);
    glTranslatef(rect.p1.x, rect.p1.y,0);
    glRotatef(rotateAngle, rect.p1.x, rect.p1.y,1);
    glTranslatef(-rect.p1.x, -rect.p1.y,0);

   // glRotatef(-rotateAngle, rect.p1.x, rect.p1.y,1);








    drawRectangle(0.0, 0.0, 0.0);
    glPopMatrix();




}

GLWidget::Point GLWidget::transofrmCoordinate(Point p) {
    Point result;
    result.x = p.x * (DEFAULT_LINE_LEN/BIG_LINE_LEN);
    result.y = p.y * (DEFAULT_LINE_LEN/BIG_LINE_LEN);
    return result;
}


void GLWidget::moveRectangle() {

    rotateAngle += 1;
    if (xOffset<=1 && yOffset+rect.p2.y <=1 && moveTop) {
        xOffset += 0.001;
        yOffset = moveCoeficient*xOffset;
    } else {

//        xOffset -= 0.001;
//        yOffset = 2*xOffset;
        moveTop = false;
    }

    if (!moveTop && xOffset >=-1 && yOffset >= -1) {
        xOffset -= 0.001;
        yOffset = moveCoeficient*xOffset;
    } else {
        moveTop = true;
    }
    this->repaint();
}


GLWidget::~GLWidget()
{

}

