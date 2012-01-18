/*
 *  Tape.h
 *  Machine_Turing
 *
 *  Created by Lou on 17/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#ifndef TAPE_H
#define TAPE_H

#include <string>
#include <iostream>
#define DISPLAY_SIZE 22
#define TAPE_SIZE 10000

class Tape
{
public:
	Tape();
	void tape_copy(Tape*);	
    void tape_print();
	std::string getContent();
	int getHead();
	void setContent(std::string);
	void setHead(int);
	
	
private:
	
	std::string m_content;
	int head;
    
};

#endif