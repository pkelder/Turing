#ifndef STATEITEM_H
#define STATEITEM_H
#include "QGraphicsItem"
#include <QtCore>
#include <QtGui>

class StateItem : public QGraphicsEllipseItem
{
public:
    StateItem(int x,int y, int w,int h,QGraphicsItem * parent,QGraphicsScene * graphic):
        QGraphicsEllipseItem(x,y,w, h,parent, graphic){
    }
    void setStateNumber(int);
    void setStateProperty(int);
    int getStateNumber() const;
    int getStateProperty() const;


private:
    int state_number;
    int state_property;

private slots:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);


};

#endif // STATEITEM_H
