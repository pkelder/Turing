#ifndef TRANSITIONITEM_H
#define TRANSITIONITEM_H
#include "QGraphicsItem"
#include "stateitem.h"


//Note: on ne définit pas ici les attributs comme const car on
//envisage une évolution du projet dans laquelle on peut éditer
//une transition et en modifier les attributs (setters à implémenter
//alors)

class TransitionItem : public QGraphicsLineItem
{

public:
    TransitionItem(int& x,int&y, int w,int h,QGraphicsItem * parent):
        QGraphicsLineItem(x,y,w, h,parent){
    }
    void FillTransition(int,StateItem*,StateItem*,QStringList,QStringList,QStringList);
    void setTransitionNumber(int);
    int getTransitionNumber() const;
    void setCursor(QString);
    QStringList getCursor() const;
    void addReading(QString);
    void addWriting(QString);
    QStringList getReadings() const;
    QStringList getWritings() const;
    StateItem *getSrc() const;
    StateItem *getDest() const;


private:
    int transition_number;
    StateItem* src_state;
    StateItem* dest_state;
    QStringList cursor_move;
    QStringList readings;
    QStringList writings;

};

#endif // TRANSITIONITEM_H
