/* 
 * File:   Simulation.h
 * Author: tom
 *
 * Created on January 24, 2012, 2:32 PM
 */

#ifndef SIMULATION_H
#define	SIMULATION_H

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
    void print(const int);
    void addTransition(const vector<char>, const vector<char>, const vector<int>, State, State);
    vector<MachineConfig> getConfigs() const;
    multimap<std::string,Transition> getTransitions() const;
    MachineConfig getActiveConfig() const;

private:
    vector<MachineConfig> configs;
    MachineConfig activeConfig;
    multimap<std::string,Transition> transitions;

};

#endif	/* SIMULATION_H */

