/* 
 * File:   Simulation.cpp
 * Author: tom
 * 
 * Created on January 24, 2012, 2:32 PM
 */

#include "Simulation.h"

Simulation::Simulation() {
}

Simulation::Simulation(const Simulation& orig) {
}

Simulation::~Simulation() {
}

void Simulation::oneStep() {

}

void Simulation::wholeSimulation() {
    std::string state = activeConfig.getState().getName();
    while(state != "accept") {
        oneStep();
    }
}

void Simulation::print(const int level) {

}

void Simulation::addTransition(const vector<char> read, const vector<char> write, const vector<int> move, const State sourceState, const State destState) {
    Transition* tr = new Transition(read, write, move, sourceState, destState);
    transitions.insert(pair<std::string,Transition>(sourceState.getName()&, tr&));
}

vector<MachineConfig> Simulation::getConfigs() const {
    return configs;
}

multimap<std::string,Transition> Simulation::getTransitions() const {
    return transitions;
}

MachineConfig Simulation::getActiveConfig() const {
    return activeConfig;
}