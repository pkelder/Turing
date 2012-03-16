#include "transitionitem.h"


/*** Methode de remplissage des attributs non graphiques de la transition ***/

void TransitionItem::FillTransition(int number, StateItem* src,StateItem* dest,QStringList curs, QStringList read, QStringList write){

    transition_number=number;
    cursor_move=curs;
    readings=read;
    writings=write;
    src_state=src;
    dest_state=dest;
}


/* Ajout d'un élément lu */

void TransitionItem::addReading(QString s){
    readings=s.split(",");

}

/* Ajout d'un élément à lire */

void TransitionItem::addWriting(QString s){
    writings=s.split(",");
}



/*** Getters & Setters ***/

void TransitionItem::setTransitionNumber(int a){
    transition_number=a;
}


int TransitionItem::getTransitionNumber() const{
    return transition_number;
}


void TransitionItem::setCursor(QString c){
    cursor_move=c.split(",");
}

QStringList TransitionItem::getCursor() const{
    return cursor_move;
}


QStringList TransitionItem::getReadings() const{
    return readings;
}

QStringList TransitionItem::getWritings() const{
    return writings;
}

StateItem* TransitionItem::getSrc() const{
    return src_state;
}

StateItem* TransitionItem::getDest() const{
    return dest_state;
}
