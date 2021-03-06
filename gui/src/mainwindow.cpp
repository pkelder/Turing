#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QGraphicsScene"
#include <iostream>
#include "QList"
#include <string>
#include "stateitem.h"
#include "transitionitem.h"
#include "QMessageBox"
#include <sstream>
#include "newtransitionwindow.h"
#include "typeinfo"

using namespace std;
int state_compteur=1;
int transition_compteur=1;

//Note: les états accepteurs seront dessinés en vert, les etats reject en rouge, le reste en noir
//au niveau du code, on distingue un état accepteur/neutre/rejecteur par un entier state_property
//qui sera à 0 pour un etat classique, -1 pour reject, 1 pour accept et 2 pour un état init



/*** Creation de la fenêtre ***/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //initialisation de la scene
    scene= new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    //initialisation de la liste des tapes
    ui->listWidget->setEnabled(true);
    QListWidgetItem *lwi = new QListWidgetItem("cliquez sur modifier pour modifier le contenu de la tape");
    ui->listWidget->addItem(lwi);
    ui->graphicsView->setMouseTracking(true);
    state_list.empty();
    transition_list.empty();

}


/*** Suppression de la fenêtre ***/

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bouton_clicked()
{
    //méthode principale qui lance la simulation
    //pour l'instant, on affiche la traduction du graphique en mode textuel compris
    // C'est ici que tu dois travailler Toto!

    QString text; //text contiendra l'ensemble de la machine de Turing version textuelle

    //test sur la vue choisie par l'utilisateur

    if (ui->tabWidget->currentIndex()==1){ //on est dans la vue TextView

        text=ui->textViewEdit->toPlainText();

    }

    else{       //on est dans la vue GraphicView


    //parcours de l'ensemble des transitions créées
    QList<const TransitionItem *>::Iterator iter;


    for(iter = transition_list.begin(); iter!=transition_list.end(); ++iter)
    {
        TransitionItem * currentTransition=(TransitionItem *) *iter;

        //on veut quelque chose du genre: init -- {1,0},",+ -> init

        //on récupère les éléments de la transition qui nous intéressent
        QStringList cursormv=currentTransition->getCursor();
        QStringList readings=currentTransition->getReadings();
        QStringList writings=currentTransition->getWritings();
        QString s,d;
        switch (currentTransition->getSrc()->getStateProperty()){
        case -1:
            s=*new QString("reject");
            break;
        case 0:
            s = QString::number(currentTransition->getSrc()->getStateNumber());
          break;
        case 1:
            s=*new QString("accept");
            break;
        case 2:
            s=*new QString("init");
            break;
        }

        switch (currentTransition->getDest()->getStateProperty()){
        case -1:
            d=*new QString("reject");
            break;
        case 0:
            d = QString::number(currentTransition->getDest()->getStateNumber());
          break;
        case 1:
            d=*new QString("accept");
            break;
        case 2:
            d=*new QString("init");
            break;
        }

        //on complète notre QString selon la bonne syntaxe
        text.append(s);
        text.append("-- {");
        text.append(readings.at(0));
        text.append("} , {");
        text.append(writings.at(0));
        text.append("} , {");
        text.append(cursormv.at(0));
        text.append("} ->");
        text.append(d);
        text.append("\n");

}
    }

    //Défaut à améliorer: on considère ici que les tapes prises en arguments sont toujours celles de la vue graphicsView.
    //Pour améliorer: retirer la partie Tapes de la vue et la placer dans la fenêtre globale

        //récupération des tapes on en fait une QStringList ou vector<std::string>
        vector<std::string> *tape_list=new vector<std::string>();
        int max=ui->listWidget->count();
        for(int i=0;i<max;i++){
            QString current_tape=ui->listWidget->item(i)->text();
            tape_list->push_back(current_tape.toStdString());
        }


        //transformer le QString en string
        std::string mon_string= text.toStdString();


    ui->console->setText(text);
    //pour l'instant, text est affiché sur la console: à envoyer dans le simulateur


}







/*** Méthodes limitant la sélection à un seul bouton d'édition à la fois ***/

void MainWindow::on_InitStateButton_clicked()
{

    //la selection d'un bouton entraine la deselection de tous les autres boutons
    if (ui->InitStateButton->isChecked()){
        ui->StateButton->setChecked(false);
        ui->EditButton->setChecked(false);
        ui->AcceptButton->setChecked(false);
        ui->RejectButton->setChecked(false);
        ui->TransitionButton->setChecked(false);
    }

}

void MainWindow::on_StateButton_clicked()
{

    //la selection d'un bouton entraine la deselection de tous les autres boutons
    if (ui->StateButton->isChecked()){
        ui->InitStateButton->setChecked(false);
        ui->EditButton->setChecked(false);
        ui->AcceptButton->setChecked(false);
        ui->RejectButton->setChecked(false);
        ui->TransitionButton->setChecked(false);
    }

}

void MainWindow::on_EditButton_clicked()
{

    //la selection d'un bouton entraine la deselection de tous les autres boutons
    if (ui->EditButton->isChecked()){
        ui->InitStateButton->setChecked(false);
        ui->StateButton->setChecked(false);
        ui->AcceptButton->setChecked(false);
        ui->RejectButton->setChecked(false);
        ui->TransitionButton->setChecked(false);
    }
}

void MainWindow::on_AcceptButton_clicked()
{

    //la selection d'un bouton entraine la deselection de tous les autres boutons
    if (ui->AcceptButton->isChecked()){
        ui->InitStateButton->setChecked(false);
        ui->EditButton->setChecked(false);
        ui->StateButton->setChecked(false);
        ui->RejectButton->setChecked(false);
        ui->TransitionButton->setChecked(false);
    }
}

void MainWindow::on_RejectButton_clicked()
{

    //la selection d'un bouton entraine la deselection de tous les autres boutons
    if (ui->RejectButton->isChecked()){
        ui->InitStateButton->setChecked(false);
        ui->EditButton->setChecked(false);
        ui->AcceptButton->setChecked(false);
        ui->StateButton->setChecked(false);
        ui->TransitionButton->setChecked(false);
    }
}



/*** Ouverture d'une fenêtre de création de Transition ***/


void MainWindow::on_TransitionButton_clicked()
{
    NewTransitionWindow *transition_window=new NewTransitionWindow(this);
    transition_window->show();

}




/*** Creation de la transition ***/


void MainWindow::CreateTransition(NewTransitionWindow *w){

    //on récupère les valeurs entrées par l'utilisateur dans la NewTransitionWindow
    QString dest=w->getDest();
    QString src=w->getSrc();
    QString cursor=w->getCursorMv();
    QString readString=w->getRead();
    QString writString=w->getWrite();

    //test si les etats src et dest existent (redondant, à voir si on l'enlève)

    QList<StateItem *> listSrcDest;
    QList<StateItem *>::Iterator iter;
    int existing_state=0;
    for(iter = state_list.begin(); iter!=state_list.end(); ++iter)
    {
        StateItem *currentItem=*iter;
        char currentStateNumber[256];
        sprintf(currentStateNumber,"%d",currentItem->getStateNumber());

        if ((currentStateNumber==src)||(currentStateNumber==dest)){
            existing_state++;
            listSrcDest.append(currentItem);
        }
    }

    //si non: message d'erreur
    if (existing_state!=2){
        QMessageBox::warning(this, "Les deux etats n'existent pas","Un des deux etats au moins n'existe pas: creation de la transition impossible");
    }

    //si oui, creation de la transition, et dessin de celle-ci

    else{

        //on empêche tout d'abord les états de bouger
        listSrcDest.at(0)->group()->setFlag(QGraphicsItem::ItemIsMovable,false);
        listSrcDest.at(1)->group()->setFlag(QGraphicsItem::ItemIsMovable,false);



        //recuperation des positions des etats src et dest
        QPointF beginpoint=listSrcDest.at(0)->scenePos();
        QPointF endpoint=listSrcDest.at(1)->scenePos();

        //repositionnement pour le dessin
        QList<QPointF> liste=setBestPosition(beginpoint,endpoint);
        beginpoint=liste.at(0);
        endpoint=liste.at(1);

        // creation des deux éléments: la transition (transition) et son numero (text)

        TransitionItem *transition = new TransitionItem((int&)beginpoint.rx(),(int&)beginpoint.ry(),endpoint.rx()-beginpoint.rx(),endpoint.ry()-beginpoint.ry(),0);
        transition->FillTransition(transition_compteur,listSrcDest.at(0),listSrcDest.at(1),cursor.split(","),readString.split(","),writString.split(","));


        QString text;
        text.append("(");text.append(readString);text.append(")");
        text.append(";");
        text.append("(");text.append(writString);text.append(")");
        text.append(";");
        text.append("(");text.append(cursor);text.append(")");

        QGraphicsTextItem *transID=new QGraphicsTextItem(text,0,scene);

        //placement du texte au centre de la transition
        int Xmoyen=(endpoint.rx()-beginpoint.rx())/2;
        int Ymoyen=(endpoint.ry()-beginpoint.ry())/2;
        transID->setPos(Xmoyen,Ymoyen);

        //lien entre les deux elements: creation d'un groupe, avec les propriete selectionnable et movable

        QGraphicsItemGroup *group=new QGraphicsItemGroup(0,scene);
        group->addToGroup(transition);
        group->addToGroup(transID);
        group->setFlag(QGraphicsItem::ItemIsSelectable);

        //positionnement du groupe
        group->setPos(beginpoint.rx(),beginpoint.ry());

        // incrementation du compteur de transition de 1
        transition_compteur++;

        //ajout d'une transition à la liste
        transition_list.append(transition);


    }
}



//ajustement de la position pour le tracés de la transition

QList<QPointF> MainWindow::setBestPosition(QPointF beginpoint, QPointF endpoint){

    //on divise l'ecran en 4 quarts
    if ((beginpoint.rx()>=endpoint.rx())&&(beginpoint.ry()>=endpoint.ry())){
        //2 en haut à gauche de 1
        beginpoint.setX(beginpoint.rx()+4);
        beginpoint.setY(beginpoint.ry()+4);
        endpoint.setX(endpoint.rx()+34);
        endpoint.setY(endpoint.ry()+34);
    }
    if ((beginpoint.rx()>=endpoint.rx())&&(beginpoint.ry()<=endpoint.ry())){
        //2 en bas à gauche de 1

        beginpoint.setY(beginpoint.ry()+17);
        endpoint.setX(endpoint.rx()+17);

    }
    if ((beginpoint.rx()<=endpoint.rx())&&(beginpoint.ry()>=endpoint.ry())){
        //2 en haut à droite de 1
        beginpoint.setX(beginpoint.rx()+17);
        endpoint.setY(endpoint.ry()+17);
    }
    if ((beginpoint.rx()<=endpoint.rx())&&(beginpoint.ry()<=endpoint.ry())){
        //2 en bas à droite de 1
        beginpoint.setX(beginpoint.rx()+34);
        beginpoint.setY(beginpoint.ry()+34);
        endpoint.setX(endpoint.rx()+4);
        endpoint.setY(endpoint.ry()+4);

    }

    QList<QPointF> result;
    result.append(beginpoint);result.append(endpoint);
    return result;

}




/* Methode de suppression d'un élément */

void MainWindow::on_DeleteButton_clicked()
{
    QList<QGraphicsItem *> items=ui->graphicsView->items();
    QList<QGraphicsItem *>::Iterator iter;
    for(iter = items.begin(); iter!=items.end(); ++iter)
    {
        QGraphicsItem *currentItem=*iter;

        if (currentItem->isSelected()){
            //suppression de l'élément graphique
            scene->removeItem(currentItem);

            //suppresion de l'élément dans le tableau
            if (typeid(currentItem)==typeid(StateItem))
                state_list.removeOne((StateItem *)currentItem);

            else{
                transition_list.removeOne((TransitionItem *)currentItem);

            }

        }
    }


}



/*** Debut Méthodes sur Tape ***/

/*modification du contenu de la tape (erreur dans le nom de la methode, sorry) */

void MainWindow::on_EditTransitionButton_clicked(){

    bool ok=false;
    //nouvelle valeur
    QString currentTape = QInputDialog::getText(this, "Tapel", "Entrez la valeur de la tape voulue", QLineEdit::Normal, QString(), &ok);

    //trouver la ligne sélectionnée
    int i=0;
    if (ui->listWidget->selectedItems().size()!=0){
        i=ui->listWidget->row(ui->listWidget->selectedItems().at(0));
    }

    //modifier la valeur
    ui->listWidget->item(i)->setText(currentTape);


}


/*ajout d'une tape */

void MainWindow::on_AddTapeButton_clicked(){

    QListWidgetItem *lwi = new QListWidgetItem("cliquez sur modifier pour modifier le contenu de la tape");
    ui->listWidget->addItem(lwi);

}

/*Suppression d'une tape */

void MainWindow::on_DeleteTapeButton_clicked(){

    //trouver la ligne sélectionnée
    int i=ui->listWidget->count()-1;
    if (ui->listWidget->selectedItems().size()!=0){
        i=ui->listWidget->row(ui->listWidget->selectedItems().at(0));
    }

    //on supprime l'élément voulu
    ui->listWidget->takeItem(i);


}

/*** Fin Méthodes sur Tape ***/





/*** Debut Méthodes Graphiques ***/

void MainWindow::mousePressEvent(QMouseEvent * e)
{

    if (ui->EditButton->isChecked()){}

    else{
        //partie commune à la création des etats
        // creation des deux éléments: l'ellipse etat (item) et son numero (text)
        StateItem *item = new StateItem(0,0,40,40,0,scene );

        item->setStateNumber(state_compteur);
        item->setAcceptTouchEvents(true);
        item->setAcceptsHoverEvents(true);
        item->setFlag(QGraphicsItem::ItemIsSelectable,true);
        item->setFlag(QGraphicsItem::ItemIsMovable,true);

        char text[50];
        sprintf(text,"%d",item->getStateNumber());
        QGraphicsTextItem *state=new QGraphicsTextItem(text,0,scene);

        //reglage tres sale de la position, voir si on ne peut pas faire mieux
        state->setPos(10,10);

        // incrementation du compteur d'etat de 1
        state_compteur++;


        //lien entre les deux elements: creation d'un groupe, avec les propriete selectionnable et movable
        QGraphicsItemGroup *group=new QGraphicsItemGroup(0);
        item->setParentItem(group);
        group->addToGroup(item);
        group->addToGroup(state);
        group->setFlag(QGraphicsItem::ItemIsMovable,true);
        group->setFlag(QGraphicsItem::ItemIsSelectable,true);
        group->setHandlesChildEvents(false);


        //ajout de l'element a la liste des transitions
        state_list.append(item);

        //ajout du groupe a la scene
        scene->addItem(group);
        group->setPos(e->x(),e->y());

        if (ui->StateButton->isChecked()){//le stylo est noir par défaut
            item->setStateProperty(0);
        }

        else{

            if (ui->AcceptButton->isChecked())
            {

                //identification de l'état accepteur
                item->setStateProperty(1);
                //creation du crayon vert
                QPen greenpen(Qt::green);
                item->setPen(greenpen);
            }
            else
            {
                if (ui->RejectButton->isChecked())
                {
                    //identification de l'état rejecteur
                    item->setStateProperty(-1);
                    //creation du crayon rouge
                    QPen redpen(Qt::red);
                    item->setPen(redpen);

                }
                else{
                    if (ui->InitStateButton->isChecked()){
                        //identification de l'état rejecteur
                        item->setStateProperty(2);
                        //creation du crayon rouge
                        QPen bluepen(Qt::blue);
                        item->setPen(bluepen);

                    }
                }

            }

        }

    }

}





/*** Suppression d'un element par clic sur la touche suppr ***/

void MainWindow::keyPressEvent ( QKeyEvent * event )
{
    if (event->key()==Qt::Key_Delete){
        QList<QGraphicsItem *> items=ui->graphicsView->items();
        QList<QGraphicsItem *>::Iterator iter;
        for(iter = items.begin(); iter!=items.end(); ++iter)
        {
            QGraphicsItem *currentItem=*iter;

            if (currentItem->isSelected()){
                //suppression de l'élément graphique
                scene->removeItem(currentItem);

                //suppresion de l'élément dans le tableau
                if (typeid(currentItem)==typeid(StateItem))
                    state_list.removeOne((StateItem *)currentItem);

                else{
                    transition_list.removeOne((TransitionItem *)currentItem);
                }


            }
        }

    }

}




/*** Déplacement d'un état: repositionnement des transitions ***/
/*** en cours d'écriture ***/


void MainWindow::StateMoved(StateItem * state){


    const TransitionItem * t=transition_list.first();

}



/*** Fin Méthodes Graphiques ***/



/*** Accesseur ***/
int MainWindow::getStateNumber() const {
    return state_list.size();
}

QList<const TransitionItem *> MainWindow::getTransitionList(){
return transition_list;
}
