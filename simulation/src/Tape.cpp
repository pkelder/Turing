/*
 *  Tape.cpp
 *  Turing
 *
 *  Created by Lou on 24/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#include "Tape.h"

Tape::Tape(){}

void Tape::setChar(char c){
	content[cursor]=c;

}


char Tape::getChar() const{
	
return content[cursor];

}


/* on choisit une convention:
 i=1 : on avance de 1
 i=-1: on recule de 1;
 i=0: on reste sur place
 on considère des Machines de Turing avec des Tapes semi-infinies
*/

void Tape::move(const int mov){
	
	if (!(cursor==0&&mov==-1)){
	this->cursor=this->cursor+mov;
	}

}



void Tape::setContent(vector<char> v){
	this->content=v;
	
}

void Tape::setCursor(int i){
	cursor=i;
	
}
	
	
int Tape::getCursor() const{
	return cursor;
}
	
	
vector<char> Tape::getContent() const{
	return content;
}