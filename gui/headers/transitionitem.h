#ifndef TRANSITIONITEM_H
#define TRANSITIONITEM_H
#include "QGraphicsItem"
#include "stateitem.h"

class TransitionItem : public QGraphicsLineItem
{
public:
public:
    TransitionItem(int& x,int&y, int w,int h,QGraphicsItem * parent):
        QGraphicsLineItem(x,y,w, h,parent){
    }
    void FillTransition(int,StateItem*,StateItem*,QStringList,QStringList,QStringList);
    void setTransitionNumber(int);
    int getTransitionNumber();
    void setCursor(QString);
    QStringList getCursor();
    void addReading(QString);
    void addWriting(QString);


private:
    int transition_number;
    StateItem *src_state;
    StateItem *dest_state;
    QStringList cursor_move;
    QStringList readings;
    QStringList writings;
};

#endif // TRANSITIONITEM_H
