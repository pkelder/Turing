#include "stateitem.h"
#include "mainwindow.h"



/**** Getters & Setters ****/

void StateItem::setStateNumber(int number){
    state_number=number;
}

void StateItem::setStateProperty(int b){
    state_property=b;
}


int StateItem::getStateProperty() const{
    return state_property;
}


int StateItem::getStateNumber() const{
    return state_number;
}


/***Methode de réponse à l'évènement clic ***/

void StateItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

  //  ((MainWindow *)this)->StateMoved(this);

}
