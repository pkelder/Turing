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
#include <vector>
#include <string>

using namespace std;


Transition::Transition(vector<char> rd,vector<char> wt,vector<int> mv, const State* src, const State* dest){

	read=rd;
	write=wt;
	move=mv;
	sourceState=src;
	destState=dest;
}

vector<char> Transition::getRead() const {
    return read;
}

vector<char> Transition::getWrite() const {
    return write;
}

vector<int> Transition::getMove() const {
    return move;
}

const State* Transition::getDestState() const {
    return destState;
}