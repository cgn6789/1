#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include <QtGui>
#include <QtWidgets>
#include <QObject>
#include <cmath>
#include <iostream>
#include <string.h>
#include <qcolor.h>
#include <qpainter.h>
//#include <qframe.h>
#include <qdebug.h>

#define MAIN_WINDOW_X 500
#define MAIN_WINDOW_Y 300
#define MAIN_WINDOW_W 500
#define MAIN_WINDOW_H 300

const qreal PI = 3.1415926535898;

class ControlBar : public QWidget
{
    Q_OBJECT

public:
    ControlBar(QWidget *parent = 0);
    void initVariables();
    void initUI();

    ~ControlBar();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
private:
    /*进度条所在圆的直径，中心点，角度，右上角点位置*/
    QPointF m_circleCentrePoint;
    qreal   m_circleRadius;
    qreal   m_circleAngle;
    qreal   m_circlelefttoppointX;
    qreal   m_circlelefttoppointY;

    /*左边进度条滑块的信息*/
    qreal   m_leftindicatorY;
    qreal   m_leftindicatorX;
    QRectF  m_leftindicatorRect;
    QPointF m_leftmovePot;
    QPointF m_leftbarBegin;
    QPointF m_leftbarEnd;
    bool    m_LeftPressed;
    bool    m_LeftValid;
    bool    m_LeftFirstRun;

    /*右边进度条滑块的信息*/
    qreal   m_rightindicatorY;
    qreal   m_rightindicatorX;
    QRectF  m_rightindicatorRect;
    QPointF m_rightmovePot;
    QPointF m_rightbarBegin;
    QPointF m_rightbarEnd;
    bool    m_RightPressed;
    bool    m_RightValid;
    bool    m_RightFirstRun;

    /*底部进度条滑块的信息*/
    qreal   m_bottomindicatorY;
    qreal   m_bottomindicatorX;
    QRectF  m_bottomindicatorRect;
    QPointF m_bottommovePot;
    QPointF m_bottombarBegin;
    QPointF m_bottombarEnd;
    bool    m_BottomPressed;
    bool    m_BottomValid;
    bool    m_BottomFirstRun;

    /*环形进度条属性*/
    int     m_CurrentValue;
    int     m_angle;
    QColor  m_color;

    QPainter *painter;

    void drawBackground(QPainter* painter);
    void drawLeftBar(QPainter* painter);
    void drawLeftIndicator(QPainter* painter);
    void drawRightBar(QPainter* painter);
    void drawRightIndicator(QPainter* painter);
    void drawBottomBar(QPainter* painter);
    void drawBottomIndicator(QPainter* painter);
    void drawBottomFilledRegion(QPainter* painter);
    void drawProgressIndicator(QPainter* painter);
};

#endif // CONTROLBAR_H
