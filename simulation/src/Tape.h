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

#define CONTENT_OFFSET 1
#define CONTENT_ENDING 1

#include <vector>
using namespace std;

class Tape{
	
public:
	Tape();
        Tape(vector<char>);
	void setChar(char);
	char getChar() const;
	void move(int);
	int getCursor() const;
	vector<char> getContent() const;
	
	
private:
	vector<char> content;
	int cursor;
};

#endif
