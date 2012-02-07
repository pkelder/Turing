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

/*
 * Méthode qui simule un tour de la machine de Turing.
 * Elle produit une liste de transitions possibles par filtrage par état source.
 * Elle refiltre ensuite cette liste en fonction des caractères lus sur les bandes.
 * Une fois une transition choisie (de manière pas forcément déterministe), elle va
 * l'appliquer. En découle une nouvelle configuration, l'ancienne étant sauvegardée.
 */
void Simulation::oneStep() {
    //Search for possible transitions by source state
    vector<Transition*> filteredTransitions;
    std::string activeState = activeConfig->getState()->getName();
    auto ret = transitions.equal_range(activeState);
    for (auto it=ret.first;it!=ret.second;++it) {
        filteredTransitions.push_back((*it).second);
    }
    
    //Search for possible transitions by read character (only one tape for now, folks)
    vector<Transition*> possibleTransitions;
    char readValue = activeConfig->getTape()[0]->getChar();
    for (Transition* tr : filteredTransitions ) {
        if (tr->getRead()[0] == readValue) {
            possibleTransitions.push_back(tr);
        }
    }
    
    //Let's go for the transition adventure
    const State* nextState = possibleTransitions[0]->getDestState();
    Tape actualTape = *(activeConfig->getTape()[0]);
    Tape* nextTape = new Tape(actualTape);
    nextTape->setChar(possibleTransitions[0]->getWrite()[0]);
    nextTape->move(possibleTransitions[0]->getMove()[0]);
    
    //Create the new config and store the old one
    vector<Tape*> nextTapes;
    nextTapes.push_back(nextTape);
    MachineConfig* nextConfig = new MachineConfig(nextState, nextTapes);
    configs.push_back(nextConfig);
    activeConfig = nextConfig;
}

/*
 * Lance toute la simulation. Les conditions d'arrêt actuellement
 * sont l'arrivée à l'état accept ou reject. Il faudrait trouver un
 * moyen d'arrêter la simulation si la machine ne peut pas se terminer
 * ou si elle s'arrête pour une raison particulière.
 */
void Simulation::wholeSimulation() {
    const State* currentState = activeConfig->getState();
    std::string stateName = currentState->getName();
    while(stateName != "accept" && stateName != "reject") {
        oneStep();
        currentState = activeConfig->getState();
        stateName = currentState->getName();
    }
    std::cout << "C'est fini : état " << stateName << std::endl;
}

/*
 * Méthode permettant un affichage "verbose" de la simulation en
 * console. Fait appel aux méthodes print des objets plus profonds.
 */
void Simulation::print() {
    
}

/*
 * Méthode permettant l'ajout d'une transition. Il lui faut :
 * - un vector<char> de caractères à lire
 * - un vector<char> de caractères à écrire
 * - un vector<char> de mouvements de curseur à effectuer
 * - un State de départ
 * - un State d'arrivée
 * Cette méthode doit être appelée par un parser ou par l'interface graphique.
 */
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
