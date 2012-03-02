/* 
 * File:   Simulation.cpp
 * Author: tom
 * 
 * Created on January 24, 2012, 2:32 PM
 */

#include <iostream>
#include "Simulation.h"
#include "TmParser.h"
#include <time.h>
#include <stdlib.h>

Simulation::Simulation(std::string machine, vector<std::string> stringTapes) {
    states.push_back("init");
    states.push_back("accept");
    states.push_back("reject");
    parseTuring(machine,this);
    vector<Tape*> tapes;
    for (std::string st : stringTapes) {
        std::vector<char> vectorCopy(st.size() + 1);
        std::copy(st.begin(), st.end(), vectorCopy.begin());
        tapes.push_back(new Tape(vectorCopy));
    }
    activeConfig = new MachineConfig("init", tapes);
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
    std::string activeState = activeConfig->getState();
    auto ret = transitions.equal_range(activeState);
    for (auto it=ret.first;it!=ret.second;++it) {
        filteredTransitions.push_back((*it).second);
    }

    if (filteredTransitions.empty()) {
        std::cerr << "[ERR] Pas de transition possible, la machine est bloquée." << std::endl;
        std::cerr << "[ERR] Problème : Pas de transition trouvée avec l'état source actuel." << std::endl;
        std::cerr << "[ERR] Etat final : " << activeState << std::endl;
        exit(0);
    }
    
    //Search for possible transitions by read character
    vector<Transition*> possibleTransitions;
    vector<char> readValue;
    for (Tape* t : activeConfig->getTape()) {
        readValue.push_back(t->getChar());
    }
    for (Transition* tr : filteredTransitions ) {
        if (tr->getRead() == readValue) {
            possibleTransitions.push_back(tr);
        }
    }

    if (possibleTransitions.empty()) {
        std::cerr << "[ERR] Pas de transition possible, la machine est bloquée." << std::endl;
        std::cerr << "[ERR] Problème : Pas de transition trouvée compatible avec les caractères lus." << std::endl;
        std::cerr << "[ERR] Etat final : " << activeState << std::endl;
        exit(0);
    }
    
    //Let's go for the transition adventure
    srand(time(NULL));
    int n = rand() % possibleTransitions.size(); //Random number for transition selection
    Transition* select = possibleTransitions[n];
    std::string nextState = select->getDestState();
    vector<Tape*> actualTapes = activeConfig->getTape();
    vector<Tape*> nextTapes; //We need a real copy, nextTapes = actualTapes won't work as they contain pointers
    for (Tape* t : actualTapes) {
        nextTapes.push_back(new Tape(*t));
    }
    for (int i = 0; i < nextTapes.size(); i++) {
        char toWrite = select->getWrite()[i];  //Must declare in advance or does not compile
        nextTapes[i]->setChar(toWrite);
        nextTapes[i]->move(select->getMove()[i]);
    }
    
    //Create the new config and store the old one
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
    std::string stateName = activeConfig->getState();
    int steps = 0;
    while(stateName != "accept" && stateName != "reject") {
        oneStep();
        steps++;
        stateName = activeConfig->getState();
        if (steps > MAX_ITERATIONS) {
            std::cout << "Trop d'itérations, le programme tourne peut-être en boucle !" << std::endl;
            exit(1);
        }
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
 * - un vector<int> de mouvements de curseur à effectuer
 * - un State de départ
 * - un State d'arrivée
 * Cette méthode doit être appelée par un parser ou par l'interface graphique.
 */
void Simulation::addTransition(const vector<char> read, const vector<char> write, const vector<int> move, const std::string sourceState, const std::string destState) {
    Transition* tr = new Transition(read, write, move, sourceState, destState);
    transitions.insert(pair<std::string,Transition*>(sourceState, tr));
}

void Simulation::addState(std::string st) {
    for (std::string s : states) {
        if (s == st) { return; }
    }
    states.push_back(st);
}

vector<MachineConfig*> Simulation::getConfigs() const {
    return configs;
}

vector<std::string> Simulation::getStates() const {
    return states;
}

multimap<std::string,Transition*> Simulation::getTransitions() const {
    return transitions;
}

MachineConfig* Simulation::getActiveConfig() const {
    return activeConfig;
}
