/*
 *  Tape.h
 *  Turing
 *
 *  Created by Lou on 24/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#ifndef DEF_TAPE
#define DEF_TAPE

#include <vector>
using namespace std;

class Tape{
	
public:
	Tape();
	void setChar(char);
	char getChar();
	void move(int);
	void setContent(vector<char>);
	void setCursor(int);
	int getCursor();
	vector<char> getContent();
	
	
private:
	vector<char> content;
	int cursor;
	
};

#endif