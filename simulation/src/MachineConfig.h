/*
 *  MachineConfig.h
 *  Turing
 *
 *  Created by Lou on 24/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#ifndef DEF_MACHINECONFIG
#define DEF_MACHINECONFIG

#include <vector>
#include "State.h"
#include "Tape.h"
using namespace std;

class MachineConfig{
	
public:
	MachineConfig();
	void setTape(vector<Tape>);
	void setState(State);
	State getState();
	vector<Tape> getTape();
	
	
private:
	vector<Tape> tapes;
	State state;
	
};

#endif