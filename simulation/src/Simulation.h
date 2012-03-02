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

class Simulation {
public:
    Simulation(std::string, vector<std::string>);
    Simulation(const Simulation& orig);
    virtual ~Simulation();
    void oneStep();
    void wholeSimulation();
    void print();
    void addTransition(const vector<char>, const vector<char>, const vector<int>, const std::string, const std::string);
    void addState(std::string);
    vector<MachineConfig*> getConfigs() const;
    vector<std::string> getStates() const;
    multimap<std::string,Transition*> getTransitions() const;
    MachineConfig* getActiveConfig() const;

private:
    vector<MachineConfig*> configs;
    vector<std::string> states;
    MachineConfig* activeConfig;
    multimap<std::string,Transition*> transitions;

};

#endif	/* SIMULATION_H */

