#include "transitionitem.h"

void TransitionItem::setTransitionNumber(int a){
    transition_number=a;
}


int TransitionItem::getTransitionNumber(){
    return transition_number;
}


void TransitionItem::setCursor(QString c){
    cursor_move=c.split(",");
}

QStringList TransitionItem::getCursor(){
    return cursor_move;
}

void TransitionItem::addReading(QString s){
    readings=s.split(",");

}

void TransitionItem::addWriting(QString s){
    writings=s.split(",");
}

void TransitionItem::FillTransition(int number, StateItem* src,StateItem* dest,QStringList curs, QStringList read, QStringList write){

    transition_number=number;
    cursor_move=curs;
    readings=read;
    writings=write;
    src_state=src;
    dest_state=dest;
}


QStringList TransitionItem::getReadings(){
    return readings;
}

QStringList TransitionItem::getWritings(){
    return writings;
}

StateItem* TransitionItem::getSrc(){
    return src_state;
}

StateItem* TransitionItem::getDest(){
    return dest_state;
}
