/* 
 * File:   Simulation.h
 * Author: tom
 *
 * Created on January 24, 2012, 2:32 PM
 */

#ifndef SIMULATION_H
#define	SIMULATION_H

#define MAX_ITERATIONS 5000

#include <vector>
#include <map>
#include <string>
#include "MachineConfig.h"
#include "Transition.h"
#include "State.h"

class Simulation {
public:
    Simulation();
    Simulation(const Simulation& orig);
    virtual ~Simulation();
    void oneStep();
    void wholeSimulation();
    void print();
    void addTransition(const vector<char>, const vector<char>, const vector<int>, const State*, const State*);
    void addState(State*);
    vector<MachineConfig*> getConfigs() const;
    vector<State*> getStates() const;
    multimap<std::string,Transition*> getTransitions() const;
    MachineConfig* getActiveConfig() const;

private:
    vector<MachineConfig*> configs;
    vector<State*> states;
    MachineConfig* activeConfig;
    multimap<std::string,Transition*> transitions;

};

#endif	/* SIMULATION_H */

