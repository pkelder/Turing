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
#include "Tape.h"
using namespace std;

class MachineConfig{
	
public:
        MachineConfig(const std::string, vector<Tape*>);
        const std::string getState() const;
	vector<Tape*> getTape() const;
	
	
private:
	vector<Tape*> tapes;
        std::string state;
	
};

#endif
