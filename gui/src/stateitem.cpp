#include "stateitem.h"
#include "mainwindow.h"


void StateItem::setStateNumber(int number){
    state_number=number;
}

int StateItem::getStateNumber(){
    return state_number;
}


void StateItem::setStateProperty(int b){
    state_property=b;
}


int StateItem::getStateProperty(){
    return state_property;
}
