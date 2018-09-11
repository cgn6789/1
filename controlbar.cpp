#include "controlbar.h"

int g_PointValue[100];

ControlBar::ControlBar(QWidget *parent)
    : QWidget(parent)
{
    initVariables();
    initUI();
}

void ControlBar::initVariables()
{
    m_circleRadius        = 400;   //默认设置进度条所在圆的直径
    m_circlelefttoppointX = 50;
    m_circlelefttoppointY = -50;
    m_circleAngle         = 0.0;
    m_leftindicatorX      = 0.0;
    m_leftindicatorY      = 0.0;
    m_LeftPressed         = false;
    m_LeftValid           = false;
    m_LeftFirstRun        = true;
    m_RightPressed        = false;
    m_RightValid          = false;
    m_RightFirstRun       = true;
    m_BottomPressed       = false;
    m_BottomValid         = false;
    m_BottomFirstRun      = true;
    m_angle               = 0;
    m_CurrentValue        = 31;

    int i = 0;
    int j = 31;
    for(i; i < 32; i++)
    {
        g_PointValue[i] = j;
        j = j - 1;
    }
    int m = i;
    int n = 119;
    for(m; m < 63; m++)
    {
        g_PointValue[m] = n;
        n = n - 1;
    }
}

void ControlBar::initUI()
{
    Qt::WindowFlags flags = Qt::Dialog | Qt::FramelessWindowHint;
    this->setWindowFlags(flags);

    //set mainmenu size
    this->setGeometry(QRect(MAIN_WINDOW_X, MAIN_WINDOW_Y, MAIN_WINDOW_W, MAIN_WINDOW_H));
    qreal m_circleX = MAIN_WINDOW_X + MAIN_WINDOW_W/2;
    qreal m_circleY = MAIN_WINDOW_Y + MAIN_WINDOW_H/2;
    m_circleCentrePoint.setX(m_circleX);
    m_circleCentrePoint.setY(m_circleY);
    //set background color
    this->setStyleSheet("background-color: #000;");

}

void ControlBar::paintEvent(QPaintEvent *)
{
    painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing,true);
    drawBackground(painter);
    drawLeftBar(painter);
    drawLeftIndicator(painter);
    drawRightBar(painter);
    drawRightIndicator(painter);
    drawBottomBar(painter);
    drawBottomIndicator(painter);
    drawBottomFilledRegion(painter);
    drawProgressIndicator(painter);
}

void ControlBar::drawBackground(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::gray);
    painter->setPen(QPen(QBrush(Qt::gray), 1));
    painter->drawEllipse(m_circlelefttoppointX,m_circlelefttoppointY,m_circleRadius,m_circleRadius);
    painter->drawEllipse(m_circlelefttoppointX + 70,m_circlelefttoppointY + 70,m_circleRadius-140,m_circleRadius-140);
    painter->restore();
}
void ControlBar::drawLeftBar(QPainter *painter)
{
    qreal m_barAngle = 140*16;    //弧形进度条开始位置
    qreal m_barAlen  = 70*16;     //弧形进度条弧长

    painter->save();
    QPen thickPen(Qt::white);
    thickPen.setWidth(5);
    painter->setPen(thickPen);
    painter->setBrush(Qt::white);

    m_leftbarBegin.setX(m_circleCentrePoint.x() - m_circleRadius/2 - MAIN_WINDOW_X + (m_circleRadius/2)*(1 - cos(PI*40.0/180.0)));
    m_leftbarBegin.setY(m_circleCentrePoint.y() - MAIN_WINDOW_Y - (m_circleRadius/2)*sin(PI*40.0/180.0));
    m_leftbarEnd.setX(m_circleCentrePoint.x() - m_circleRadius/2-MAIN_WINDOW_X + (m_circleRadius/2)*(1 - cos(PI*30.0/180.0)));
    m_leftbarEnd.setY(m_circleCentrePoint.y() - MAIN_WINDOW_Y + (m_circleRadius/2)*sin(PI*30.0/180.0));

    painter->drawArc(m_circlelefttoppointX,m_circlelefttoppointY, m_circleRadius,m_circleRadius, m_barAngle, m_barAlen);
    //painter->drawEllipse((250-200*cos(PI*40.0/180.0)-2.5*cos(PI*45.0/180.0)),(150-200*sin(PI*40.0/180.0))-2.5*sin(PI*45.0/180.0),qRound(5/2)+1,qRound(5/2)+1);
    painter->restore();
}

void ControlBar::drawLeftIndicator(QPainter *painter)
{
    qreal INDICATOR_RADIUS = 10;    //滑块半径

    painter->save();
    QPen thickPen(Qt::white);
    thickPen.setWidth(1);
    painter->setPen(thickPen);
    painter->setBrush(Qt::white);

    if(m_LeftFirstRun)
    {
         m_leftindicatorX = m_circleCentrePoint.x()-m_circleRadius/2-MAIN_WINDOW_X;
         m_leftindicatorY = m_circleCentrePoint.y()-MAIN_WINDOW_Y;
         QPointF leftindicatorCenter(m_leftindicatorX,m_leftindicatorY);
         m_leftmovePot = leftindicatorCenter;
         m_LeftFirstRun = false;
    }
    m_leftmovePot.setX(m_leftindicatorX + ((m_circleRadius/2) - sqrt((m_circleRadius/2)*(m_circleRadius/2) - (m_leftindicatorY - m_leftmovePot.y())*(m_leftindicatorY - m_leftmovePot.y()))));
    QPointF indicatorTopLeftPot(m_leftmovePot.x()-INDICATOR_RADIUS,m_leftmovePot.y()-INDICATOR_RADIUS);
    QPointF indicatorBottomRightPot(m_leftmovePot.x()+INDICATOR_RADIUS,m_leftmovePot.y()+INDICATOR_RADIUS);
    QRectF indicatorRect(indicatorTopLeftPot,indicatorBottomRightPot);
    m_leftindicatorRect=indicatorRect;

    painter->drawEllipse(indicatorTopLeftPot.x(),indicatorTopLeftPot.y(),INDICATOR_RADIUS*2,INDICATOR_RADIUS*2);
    painter->restore();
}

void ControlBar::drawRightBar(QPainter *painter)
{
    qreal m_barAngle = -30*16;    //弧形进度条开始位置
    qreal m_barAlen  = 70*16;     //弧形进度条弧长

    painter->save();
    QPen thickPen(Qt::white);
    thickPen.setWidth(5);
    painter->setPen(thickPen);
    painter->setBrush(Qt::white);

    m_rightbarBegin.setX(m_circleCentrePoint.x() + m_circleRadius/2 - MAIN_WINDOW_X - (m_circleRadius/2)*(1 - cos(PI*40.0/180.0)));
    m_rightbarBegin.setY(m_circleCentrePoint.y() - MAIN_WINDOW_Y - (m_circleRadius/2)*sin(PI*40.0/180.0));
    m_rightbarEnd.setX(m_circleCentrePoint.x() + m_circleRadius/2-MAIN_WINDOW_X - (m_circleRadius/2)*(1 - cos(PI*30.0/180.0)));
    m_rightbarEnd.setY(m_circleCentrePoint.y() - MAIN_WINDOW_Y + (m_circleRadius/2)*sin(PI*30.0/180.0));

    painter->drawArc(m_circlelefttoppointX,m_circlelefttoppointY, m_circleRadius,m_circleRadius, m_barAngle, m_barAlen);
    //painter->drawEllipse((250-200*cos(PI*40.0/180.0)-2.5*cos(PI*45.0/180.0)),(150-200*sin(PI*40.0/180.0))-2.5*sin(PI*45.0/180.0),qRound(5/2)+1,qRound(5/2)+1);
    painter->restore();
}

void ControlBar::drawRightIndicator(QPainter *painter)
{
    qreal INDICATOR_RADIUS = 10;    //滑块半径

    painter->save();
    QPen thickPen(Qt::white);
    thickPen.setWidth(1);
    painter->setPen(thickPen);
    painter->setBrush(Qt::white);

    if(m_RightFirstRun)
    {
         m_rightindicatorX = m_circleCentrePoint.x()+m_circleRadius/2-MAIN_WINDOW_X;
         m_rightindicatorY = m_circleCentrePoint.y()-MAIN_WINDOW_Y;
         QPointF rightindicatorCenter(m_rightindicatorX,m_rightindicatorY);
         m_rightmovePot = rightindicatorCenter;
         m_RightFirstRun=false;

    }
    m_rightmovePot.setX(m_circleCentrePoint.x() - MAIN_WINDOW_X + sqrt((m_circleRadius/2)*(m_circleRadius/2) - (m_rightindicatorY - m_rightmovePot.y())*(m_rightindicatorY - m_rightmovePot.y())));
    QPointF indicatorTopLeftPot(m_rightmovePot.x()-INDICATOR_RADIUS,m_rightmovePot.y()-INDICATOR_RADIUS);
    QPointF indicatorBottomRightPot(m_rightmovePot.x()+INDICATOR_RADIUS,m_rightmovePot.y()+INDICATOR_RADIUS);
    QRectF indicatorRect(indicatorTopLeftPot,indicatorBottomRightPot);
    m_rightindicatorRect=indicatorRect;

    painter->drawEllipse(indicatorTopLeftPot.x(),indicatorTopLeftPot.y(),INDICATOR_RADIUS*2,INDICATOR_RADIUS*2);
    painter->restore();
}

void ControlBar::drawBottomBar(QPainter *painter)
{
    qreal m_barAngle = -140*16;    //弧形进度条开始位置
    qreal m_barAlen  = 100*16;      //弧形进度条弧长

    painter->save();
    QPen thickPen(Qt::white);
    thickPen.setWidth(5);
    painter->setPen(thickPen);
    painter->setBrush(Qt::white);

    m_bottombarBegin.setX(m_circleCentrePoint.x() - MAIN_WINDOW_X - (m_circleRadius/2-70)*sin(PI*50.0/180.0));
    m_bottombarBegin.setY(m_circleCentrePoint.y() - MAIN_WINDOW_Y + (m_circleRadius/2-70)*cos(PI*50.0/180.0));
    m_bottombarEnd.setX(m_circleCentrePoint.x() - MAIN_WINDOW_X + (m_circleRadius/2-70)*sin(PI*50.0/180.0));
    m_bottombarEnd.setY(m_circleCentrePoint.y() - MAIN_WINDOW_Y + (m_circleRadius/2-70)*cos(PI*50.0/180.0));

    painter->drawEllipse(m_bottombarBegin.x()-5,m_bottombarBegin.y()-5,6,6);
    painter->drawArc(m_circlelefttoppointX + 70,m_circlelefttoppointY + 70,m_circleRadius-140,m_circleRadius-140, m_barAngle, m_barAlen);
    painter->restore();
}

void ControlBar::drawBottomIndicator(QPainter *painter)
{
    qreal INDICATOR_RADIUS = 10;    //滑块半径

    painter->save();
    QPen thickPen(Qt::white);
    thickPen.setWidth(1);
    painter->setPen(thickPen);
    painter->setBrush(Qt::white);

    if(m_BottomFirstRun)
    {
         m_bottomindicatorX = m_circleCentrePoint.x()-MAIN_WINDOW_X;
         m_bottomindicatorY = m_circleCentrePoint.y()+m_circleRadius/2-MAIN_WINDOW_Y - 70;
         QPointF bottomindicatorCenter(m_bottomindicatorX,m_bottomindicatorY);
         m_bottommovePot = bottomindicatorCenter;
         m_BottomFirstRun=false;

    }
    m_bottommovePot.setY(m_circleCentrePoint.y() - MAIN_WINDOW_Y + sqrt((m_circleRadius/2-70)*(m_circleRadius/2-70) - (m_bottomindicatorX - m_bottommovePot.x())*(m_bottomindicatorX - m_bottommovePot.x())));
    QPointF indicatorTopLeftPot(m_bottommovePot.x()-INDICATOR_RADIUS,m_bottommovePot.y()-INDICATOR_RADIUS);
    QPointF indicatorBottomBottomPot(m_bottommovePot.x()+INDICATOR_RADIUS,m_bottommovePot.y()+INDICATOR_RADIUS);
    QRectF indicatorRect(indicatorTopLeftPot,indicatorBottomBottomPot);
    m_bottomindicatorRect=indicatorRect;

    painter->drawEllipse(indicatorTopLeftPot.x(),indicatorTopLeftPot.y(),INDICATOR_RADIUS*2,INDICATOR_RADIUS*2);
    painter->restore();
}

void ControlBar::drawBottomFilledRegion(QPainter *painter)
{
    qreal m_barAngle    = -140*16; //弧形进度条开始位置
    qreal m_barAlen     = 0.0;     //弧形进度条弧长
    qreal m_chrodLength = 0.0;     //圆上两点间弦长的一半

    if(m_bottommovePot.x()-m_bottomindicatorRect.x()<=5)
    {
        return ;
    }
    painter->save();
    QPen thickPen(Qt::white);
    thickPen.setWidth(11);
    painter->setPen(thickPen);
    painter->setBrush(Qt::white);

    m_chrodLength = sqrt((m_bottommovePot.x() - m_bottombarBegin.x())*(m_bottommovePot.x() - m_bottombarBegin.x()) + (m_bottommovePot.y() - m_bottombarBegin.y())*(m_bottommovePot.y() - m_bottombarBegin.y()))/2;
    m_barAlen = asin(m_chrodLength/(m_circleRadius/2-70)) * 2 * 16 * 16 *3.5;
    painter->drawArc(m_circlelefttoppointX + 70,m_circlelefttoppointY + 70,m_circleRadius-140,m_circleRadius-140, m_barAngle, m_barAlen);
    painter->restore();
}

void ControlBar::drawProgressIndicator(QPainter *painter)
{
    int width         = m_circleRadius-140;
    int outerRadius   = width*0.5*1.09;
    int innerRadius   = width*0.5*0.91;
    int otherRadius   = width*0.5*0.83;
    int capsuleHeight = outerRadius - innerRadius;
    int otherHeight   = outerRadius - otherRadius;
    int capsuleWidth  = (width > 32 ) ? capsuleHeight *.1 : capsuleHeight *.35;
    int otherWidth    = (width > 32 ) ? otherHeight *.1 : otherHeight *.35;

    QColor color = m_color;
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);

    for (int i = 0; i < 32; i++)
    {
        color.setAlphaF(1.0f - (i/120.0f));
        painter->save();
        painter->translate(rect().center());
        painter->rotate(m_angle - i*3.0f);
        painter->drawRect(-capsuleWidth*0.5, -(innerRadius+capsuleHeight), capsuleWidth, capsuleHeight);
        painter->restore();
    }

    for (int i = 89; i < 120; i++)
    {
        color.setAlphaF(1.0f - (i/120.0f));
        painter->save();
        painter->translate(rect().center());
        painter->rotate(m_angle - i*3.0f);
        painter->drawRect(-capsuleWidth*0.5, -(innerRadius+capsuleHeight), capsuleWidth, capsuleHeight);
        painter->restore();
    }

    painter->save();
    color.setAlphaF(1.0f);
    painter->translate(rect().center());
    painter->rotate(-(g_PointValue[m_CurrentValue]*3.0f));
    painter->drawRect(-otherWidth*0.5, -(otherRadius+otherHeight), otherWidth, otherHeight);
    painter->restore();
}

void ControlBar::mousePressEvent(QMouseEvent *e)
{
    if(e->button())
    {
        if(m_leftindicatorRect.contains(e->pos()))
        {
            m_LeftValid = true;
            QPen thickPen(Qt::white);
            thickPen.setWidth(5);
            painter->setPen(thickPen);
            painter->setBrush(Qt::blue);
            qDebug()<<"Left mousePressEvent!";
        }
        if(m_rightindicatorRect.contains(e->pos()))
        {
            m_RightValid = true;
            painter->setBrush(Qt::blue);
            qDebug()<<"Right mousePressEvent!";
        }
        if(m_bottomindicatorRect.contains(e->pos()))
        {
            m_BottomValid = true;
            painter->setBrush(Qt::blue);
            qDebug()<<"Bottom mousePressEvent!";
        }
        update();
    }
}

void ControlBar::mouseMoveEvent(QMouseEvent *e)
{
    if(m_LeftValid)
    {
        QPointF curPos = e->pos();
        if(curPos.y() < m_leftbarBegin.y()||curPos.y() > m_leftbarEnd.y())
        {
            return ;
        }
        if(curPos.x() > m_leftmovePot.x())
        {
            m_leftmovePot = QPointF(e->pos().x(), e->pos().y());
            update();
        }

        if(curPos.x() < m_leftmovePot.x())
        {
            m_leftmovePot = QPointF(e->pos().x(), e->pos().y());
            update();
        }
        qDebug()<<"left mouseMoveEvent!";
    }
    if(m_RightValid)
    {
        QPointF curPos = e->pos();
        if(curPos.y() < m_rightbarBegin.y()||curPos.y() > m_rightbarEnd.y())
        {
            return ;
        }
        if(curPos.x() > m_rightmovePot.x())
        {
            m_rightmovePot = QPointF(e->pos().x(), e->pos().y());
            update();
        }

        if(curPos.x() < m_rightmovePot.x())
        {
            m_rightmovePot = QPointF(e->pos().x(), e->pos().y());
            update();
        }
        qDebug()<<"right mouseMoveEvent!";
    }
    if(m_BottomValid)
    {
        QPointF curPos = e->pos();
        if(curPos.x() < m_bottombarBegin.x()||curPos.x() > m_bottombarEnd.x())
        {
            return ;
        }
        if(curPos.y() > m_bottommovePot.y())
        {
            m_bottommovePot = QPointF(e->pos().x(),e->pos().y());
            m_CurrentValue  = (curPos.x()-m_bottombarBegin.x())*(63/(m_bottombarEnd.x()-m_bottombarBegin.x()));
            update();
        }

        if(curPos.y()<m_bottommovePot.y())
        {
            m_bottommovePot = QPointF(e->pos().x(),e->pos().y());
            m_CurrentValue  = (curPos.x()-m_bottombarBegin.x())*(63/(m_bottombarEnd.x()-m_bottombarBegin.x()));
            update();
        }
        qDebug()<<"bottom mouseMoveEvent!";
    }
    update();
}

void ControlBar::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button())
    {
        m_LeftPressed   = false;
        m_LeftValid     = false;
        m_RightPressed  = false;
        m_RightValid    = false;
        m_BottomPressed = false;
        m_BottomValid   = false;
        painter->setBrush(Qt::white);
        update();
    }
    qDebug()<<"mouseReleaseEvent!";
}

void ControlBar::resizeEvent(QResizeEvent *)
{
    update();
    qDebug()<<"resizeEvent!";
}

ControlBar::~ControlBar()
{
    delete(painter);
}
