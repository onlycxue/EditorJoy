#include "draglabel.h"
#include <iostream>
#include <QMenu>
#include <QDebug>
//#include "mainwindow.h"


DragLabel::DragLabel(QWidget *parent) :
    QLabel(parent)
{
    m_strImageName = "";
    Act_Delete = new QAction("Delete", this);
    connect(Act_Delete, SIGNAL(triggered()), this, SLOT(removeFromParent()));
    //
}


void DragLabel::mouseMoveEvent(QMouseEvent *event)
{

    if( bIsTouching ){
        QPoint moveOffset = QPoint( event->x() - previousPos.x(),event->y() -previousPos.y() );

        QRect labelGeometry = this->geometry();
        int imgWidth = labelGeometry.width();
        int imageHeight = labelGeometry.height();
        labelGeometry.setX(labelGeometry.x() + moveOffset.x());
        labelGeometry.setY(labelGeometry.y() + moveOffset.y());
        labelGeometry.setWidth(imgWidth);
        labelGeometry.setHeight(imageHeight);
        this->setGeometry(labelGeometry);
        qDebug() << "x :" << this->x() << "  " << "y: " << this->y();
    }
}

void DragLabel::mousePressEvent(QMouseEvent *event)
{
    bIsTouching = true;
    previousPos = QPoint(event->x(),event->y());
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->raise();
    emit sendTouchingLabel(this);
}

void DragLabel::mouseReleaseEvent(QMouseEvent *event)
{
    bIsTouching = false;
    emit sendTouchEnd();
}

void DragLabel::contextMenuEvent(QContextMenuEvent *event) //右键菜单项编辑
{
    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);
    menu->addAction(Act_Delete); //添加菜单项1
    menu->exec(cur.pos()); //关联到光标
}

void DragLabel::removeFromParent()
{
    this->hide();

    emit sendDeleteLabel(this);
    //delete this;
}

void DragLabel::bringToTop(){
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->raise();
}
