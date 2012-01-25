/*
 *  State.h
 *  Turing
 *
 *  Created by Lou on 24/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#ifndef DEF_STATE
#define DEF_STATE

#include <string>

class State{
	
public:
	State();
	void setName(std::string);
	std::string getName() const;
	
	
private:
	std::string name;

};

#endif