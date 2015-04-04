#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QPoint>
#include <cmath>
#include <QTimer>
class GLWidget:public QGLWidget
{
    Q_OBJECT
public:

    struct Point {
        float x;
        float y;
        Point() {

        }
        Point (float xp, float yp) {
            x = xp;
            y = yp;
        }
    };

    struct Rectangle {
        Point p1;
        Point p2;
        Point p3;
        Point p4;

        Rectangle() {

        }

        Rectangle(Point p1, Point p2, Point p3, Point p4) {
            this->p1 = p1;
            this->p2 = p2;
            this->p3 = p3;
            this->p4 = p4;

        }

        Rectangle(float x1, float y1, float x2, float y2, float x3, float y3,
                  float x4, float y4) {
            p1 = Point(x1, y1);
            p2 = Point(x2, y2);
            p3 = Point(x3, y3);
            p4 = Point(x4, y4);

        }
    };

    GLWidget(QWidget* parent = 0);
    const float X_BEGIN = -0.9;
    const float X_END = 0.9;
    const float Y_BEGIN = -0.9;
    const float Y_END = 0.9;
    const float DEFAULT_LINE_LEN = fabs(X_BEGIN) + fabs(X_END);
    const float BIG_LINE_LEN = 20;
    const float PI = 3.14;

    ~GLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void drawCoordinateSystem();
    void drawFunction();
    Point transofrmCoordinate(Point p);


    void drawRectangle(float r, float g, float b) {
       // glColor3f(r, g, b);

//        glPointSize(3);
//        glBegin(GL_POINTS);
//            glVertex2f(xOffset, yOffset);
//        glEnd();

        glBegin(GL_QUADS);
            glVertex2f(rect.p1.x, rect.p1.y);
            glVertex2f(rect.p2.x, rect.p2.y);
            glVertex2f(rect.p3.x, rect.p3.y);
            glVertex2f(rect.p4.x, rect.p4.y);
        glEnd();
    }

public slots:
    void drawGrapchic() { isDrawGraphic = true; this->repaint();}
    void clearGraphic() { isDrawGraphic = false; this->repaint();}
    void moveRectangle();

private:
    bool isDrawGraphic = false;
    Rectangle rect;
    QTimer *timer;
    float xOffset = 0;
    float yOffset = 0;
    float rotateAngle = 1;
    float moveCoeficient = 2;
    bool moveTop = true;


};

#endif // GLWIDGET_H
