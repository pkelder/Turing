/*
 *  Tape.cpp
 *  Machine_Turing
 *
 *  Created by Lou on 17/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#include "Tape.h"


Tape::Tape()
{
	int i;
	
    for (i=0; i < TAPE_SIZE; ++i)
        this->m_content[i] = ' ';

}



void Tape::tape_copy(Tape* t)
{
	int i;
	
    for (i=0; i < TAPE_SIZE; ++i)
        this->m_content[i] = t->m_content[i];
	
}


void Tape::tape_print()
{
	int i;
    for (i=0; i < DISPLAY_SIZE; ++i)
        printf("----");
    printf("-\n");
    for (i=0; i < DISPLAY_SIZE; ++i)
        printf("| %c ", this->m_content[TAPE_SIZE/2-DISPLAY_SIZE/2+i]); 
    printf("|\n");
	
    for (i=0; i < DISPLAY_SIZE; ++i)
        printf("----");
    printf("-\n");
}

std::string Tape::getContent()
{
	return m_content;
}

int Tape::getHead()
{
	return head;
}

void Tape::setContent(std::string s)
{
	int i;
	for (i=0; i < TAPE_SIZE; ++i)
        this->m_content[i] = s[i];
}

void Tape::setHead(int i)
{
	head=i;
}
