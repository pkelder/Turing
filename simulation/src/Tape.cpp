/*
 *  Tape.cpp
 *  Turing
 *
 *  Created by Lou on 24/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#include "Tape.h"
#include <vector>

Tape::Tape(){
    cursor = 0;
    vector<char>* emptyContent = new vector<char>();
    content = *emptyContent;
    content.push_back('0');
    content.push_back('a');
}

Tape::Tape(vector<char> cont){
    cursor = CONTENT_OFFSET;
    for (int i = 0; i < CONTENT_OFFSET; i++) {
        content.push_back(' ');
    }
    for (char c : cont) {
        content.push_back(c);
    }
    for (int i = 0; i < CONTENT_ENDING; i++) {
        content.push_back(' ');
    }
    content = cont;
}

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
	cursor=cursor+mov;
	}

}



void Tape::setContent(vector<char> v){
	this->content=v;
	
}

	
int Tape::getCursor() const{
	return cursor;
}
	
	
vector<char> Tape::getContent() const{
	return content;
}
