/*
 *  Transition.cpp
 *  Turing
 *
 *  Created by Lou on 24/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#include "Transition.h"
#include "State.h"
#include<vector>
#include<string>

using namespace std;


Transition::Transition(vector<char> rd,vector<char> wt,vector<int> mv,State src,State dest){

	read=rd;
	write=wt;
	move=mv;
	this->sourceState=src;
	this->destState=dest;
}
