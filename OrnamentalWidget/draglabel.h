#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>
#include <QMouseEvent>

class DragLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DragLabel(QWidget *parent = 0);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
signals:

public slots:
   // void removeFromParent();
    void bringToTop();
private:
    QPoint previousPos;
    bool bIsTouching;

    QAction * Act_Delete;
public:
    std::string m_strImageName;
};

#endif // DRAGLABEL_H
