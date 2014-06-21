#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QJsonObject>
#include "../Global/globaldef.h"

class DragLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DragLabel(QWidget *parent = 0);
     QJsonObject exportJsonObject();
     void setImage(QString file);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
signals:
    void sendTouchingLabel(DragLabel*);
    void sendTouchEnd();
    void sendDeleteLabel(DragLabel*);
public slots:
    void removeFromParent();
    void bringToTop();
private:
    QPoint previousPos;
    bool bIsTouching;
    QString _imageName;

    QAction * Act_Delete;
public:
    std::string m_strImageName;
};

#endif // DRAGLABEL_H
