/* 
 * File:   Simulation.cpp
 * Author: tom
 * 
 * Created on January 24, 2012, 2:32 PM
 */

#include <iostream>
#include "Simulation.h"

Simulation::Simulation() {
    State* init = new State("init");
    State* accept = new State("accept");
    State* reject = new State("reject");
    states.push_back(init);
    states.push_back(accept);
    states.push_back(reject);
    //appel au lexer/parser et remplissage de la liste des states
    //appel au lexer/parser et remplissage de la liste des transitions
    vector<Tape*> tapes (1, new Tape());
    activeConfig = new MachineConfig(init, tapes);
    configs.push_back(activeConfig);
}

Simulation::Simulation(const Simulation& orig) {
}

Simulation::~Simulation() {
}

void Simulation::oneStep() {
    //Search for possible transitions by source state
    vector<Transition*> filteredTransitions;
    std::string activeState = activeConfig->getState()->getName();
    multimap<std::string,Transition*>::iterator it;
    pair<multimap<std::string,Transition*>::iterator,multimap<std::string,Transition*>::iterator> ret = transitions.equal_range(activeState);
    for (it=ret.first;it!=ret.second;++it) {
        filteredTransitions.push_back((*it).second);
    }
    
    //Search for possible transitions by read character (only one tape for now, folks)
//    vector<Transition*> possibleTransitions;
//    char readValue = activeConfig->getTape()[0]->getChar();
//    vector<Transition*>::iterator itt;
//    for (itt = filteredTransitions.begin(); itt < filteredTransitions.end(); itt++) {
//        if ((*itt)->getRead()[0] == readValue) {
//            possibleTransitions.push_back((*itt));
//        }
//    }
    
    //Let's go for the transition adventure
    int sizeft = filteredTransitions.size();
    const State* nextState;
    nextState = filteredTransitions[0]->getDestState();
    Tape actualTape = *activeConfig->getTape()[0];
    Tape* nextTape = new Tape(actualTape);
    nextTape->setChar(filteredTransitions[0]->getWrite()[0]);
    nextTape->move(filteredTransitions[0]->getMove()[0]);
    
    //Create the new config and store the old one
    vector<Tape*> nextTapes;
    nextTapes.push_back(nextTape);
    MachineConfig* nextConfig = new MachineConfig(nextState, nextTapes);
    configs.push_back(nextConfig);
    activeConfig = nextConfig;
}

void Simulation::wholeSimulation() {
    const State* currentState = activeConfig->getState();
    std::string stateName = currentState->getName();
    while(stateName != "accept" || stateName != "reject") {
        oneStep();
    }
    std::cout << "C'est fini : état " << stateName << std::endl;
}

void Simulation::print() {
    
}

void Simulation::addTransition(const vector<char> read, const vector<char> write, const vector<int> move, const State* sourceState, const State* destState) {
    Transition* tr = new Transition(read, write, move, sourceState, destState);
    transitions.insert(pair<std::string,Transition*>(sourceState->getName(), tr));
}

vector<MachineConfig*> Simulation::getConfigs() const {
    return configs;
}

vector<State*> Simulation::getStates() const {
    return states;
}

multimap<std::string,Transition*> Simulation::getTransitions() const {
    return transitions;
}

MachineConfig* Simulation::getActiveConfig() const {
    return activeConfig;
}