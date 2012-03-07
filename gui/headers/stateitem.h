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
    int getStateNumber();
    void setStateProperty(int);
    int getStateProperty();

private:
    int state_number;
    int state_property;

};

#endif // STATEITEM_H
