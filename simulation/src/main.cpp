#include <iostream>
#include "Simulation.h"

int main (int argc, char * const argv[]) {
    
    Simulation* simulemoi = new Simulation();
    vector<char> entree (1,'1');
    vector<char> entreeFoireuse (1,'0');
    vector<char> sortie (1,'1');
    vector<int> mouvement (1, 1);
    State* init = simulemoi->getStates()[0];
    State* accept = simulemoi->getStates()[1];
    State* reject = simulemoi->getStates()[2];
    simulemoi->addTransition(entreeFoireuse,sortie,mouvement,init,reject);
    simulemoi->addTransition(entree,sortie,mouvement,init,accept);
    simulemoi->wholeSimulation();
    return 0;
}
