/*
 *  Tape.cpp
 *  Turing
 *
 *  Created by Lou on 24/01/12.
 *  Copyright 2012 Centrale Nantes. All rights reserved.
 *
 */

#include "Tape.h"
#include <iostream>
#include <vector>

/*
 * Constructeur par défaut selon la même structure que le constructeur
 * par contenu. Il considère que le contenu est un espace vide unique.
 */
Tape::Tape(){
    cursor = CONTENT_OFFSET;
    for (int i = 0; i < CONTENT_OFFSET; i++) {
        content.push_back(' ');
    }
    content.push_back(' ');
    for (int i = 0; i < CONTENT_ENDING; i++) {
        content.push_back(' ');
    }
}

/*
 * Constructeur de Tape qui prend le contenu en argument.
 * S'occupe d'ajouter un nombre prédéfini de vides avant et après
 * le contenu, pour permettre à un grand nombre de machines simples
 * de fonctionner.
 */
Tape::Tape(vector<char> cont){
    //Placer le curseur au début du contenu
    cursor = CONTENT_OFFSET;
    //Ajout d'un vide de départ
    for (int i = 0; i < CONTENT_OFFSET; i++) {
        content.push_back(' ');
    }
    //Ajout du contenu en lui-même
    for (char c : cont) {
        content.push_back(c);
    }
    //Ajout d'un vide après le contenu
    for (int i = 0; i < CONTENT_ENDING; i++) {
        content.push_back(' ');
    }
}

/*
 * Méthode qui écrit le caractère donné là où le curseur est actuellement.
 * Si jamais le curseur est en fin de bande et qu'il y écrit, alors la
 * méthode s'occupe automatiquement de rallonger la bande avec un espace vide.
 */
void Tape::setChar(char c){
    content[cursor] = c;
    if (cursor == content.size()-1) {
        content.push_back(' ');
    }
}


char Tape::getChar() const{
    return content[cursor];
}


/* Méthode qui s'occupe de bouger le curseur.
 * On choisit une convention:
 * i= 1 : on avance de 1
 * i=-1 : on recule de 1
 * i= 0 : on reste sur place
 * On considère des Machines de Turing avec des Tapes semi-infinies.
 */
void Tape::move(const int mov){
    if (mov < -1 || mov > 1) {
        std::cerr << "La machine a demandé un mouvement non autorisé" << std::endl;
        std::cerr << "Mouvement demandé : " << mov << std::endl;
    } else if (cursor == 0 && mov == -1) {
        std::cerr << "La machine a tenté d'aller trop à gauche" << std::endl;
        std::cerr << "L'offset autorisé est de " << CONTENT_OFFSET << std::endl;
    } else if (cursor == content.size()-1 && mov == 1) {
        std::cerr << "La machine a tenté d'aller trop à droite" << std::endl;
        std::cerr << "L'offset autorisé est de " << CONTENT_ENDING << std::endl;
    } else {
        cursor += mov;
    }
}
	
int Tape::getCursor() const{
    return cursor;
}
	
vector<char> Tape::getContent() const{
    return content;
}
