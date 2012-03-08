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

/* note: les états accepteurs seront dessinés en vert, les etats reject en rouge, le reste en noir
 au niveau du code, on distingue un état accepteur/neutre/rejecteur par un entier state_property qui sera à 0 pour un etat classique, -1 pour reject et 1 pour accept*/




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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bouton_clicked()
{

    //méthode principale qui lance la simulation

    //pour l'instant, on affiche la traduction du graphique en mode textuel compris

    //initialisation du string qui va contenir le text
    QString text;

    //parcours de l'ensemble des transitions créées

   // QList<QGraphicsItem *> items=ui->graphicsView->items();
    QList<const TransitionItem *>::Iterator iter;


    for(iter = transition_list.begin(); iter!=transition_list.end(); ++iter)
    {
      TransitionItem * currentTransition=(TransitionItem *) *iter;

      //on veut quelque chose du genre: init -- {1,0},",+ -> init

      //on récupère les éléments de la transition qui nous intéressent
      QStringList cursormv=currentTransition->getCursor();
      QStringList readings=currentTransition->getReadings();
      QStringList writings=currentTransition->getWritings();
      QString s = QString::number(currentTransition->getSrc()->getStateNumber());
      QString d= QString::number(currentTransition->getDest()->getStateNumber());

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


      //récupération des tapes on en fait une QStringList ou vector<std::string>

      //transformer le QString en string

    }

    //ui->console->setText("Ici sera affiche le resultat de la simulation.\nEn attendant, une petite blague: comment rendre un belge fou?\nReponse: Le mettre dans une piece ronde et lui dire qu'il y a une frite dans l'un des coins!");
    ui->console->setText(text);






}

int MainWindow::getStateNumber(){
    return state_list.size();
}

/* méthodes limitant la sélection à un seul bouton d'édition à la fois */

void MainWindow::on_StateButton_clicked()
{

    //la selection d'un bouton entraine la deselection de tous les autres boutons
    if (ui->StateButton->isChecked()){
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
        ui->EditButton->setChecked(false);
        ui->AcceptButton->setChecked(false);
        ui->StateButton->setChecked(false);
        ui->TransitionButton->setChecked(false);
    }
}

void MainWindow::on_TransitionButton_clicked()
{
    NewTransitionWindow *transition_window=new NewTransitionWindow(this);
    transition_window->show();

}


void MainWindow::CreateTransition(NewTransitionWindow *w){

    //on récupère les valeurs entrées par l'utilisateur
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
        char * currentStateNumber;
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


      /*  char text[50];
        sprintf(text,"%d",transition->getTransitionNumber());
        QGraphicsTextItem *transID=new QGraphicsTextItem(text,0,scene); */

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
                //transition_list.removeOne((TransitionItem *)currentItem);
            }


        }
    }


}

/*modification du contenu de la tape (erreur dans le nom de la methode, a modifier) */

void MainWindow::on_EditTransitionButton_clicked(){

    bool ok=false;
    //nouvelle valeur
    QString currentTape = QInputDialog::getText(this, "Tapel", "Entrez la valeur de la tape voulue", QLineEdit::Normal, QString(), &ok);

    //trouver la ligne sélectionnée
    int i=ui->listWidget->row(ui->listWidget->selectedItems().at(0));

    //modifier la valeur
    ui->listWidget->item(i)->setText(currentTape);


}


/* ajout ou suppression d'une tape */

void MainWindow::on_spinBox_valueChanged ( int i)
{

    //test sur l'ajout ou la suppression d'un element au tableau listWidget
    if (i>ui->listWidget->count()){
        QListWidgetItem *lwi = new QListWidgetItem("cliquez sur modifier pour modifier le contenu de la tape");
        ui->listWidget->addItem(lwi);
    }
    else{
        ui->listWidget->takeItem(ui->listWidget->count()-1);

    }

}



/* méthode de réalisation du graphique */

void MainWindow::mousePressEvent(QMouseEvent * e)
{

    //QPoint position= e->globalPos();

    if (ui->EditButton->isChecked()){}

    else{
        //partie commune à la création des etats
        // creation des deux éléments: l'ellipse etat (item) et son numero (text)
        StateItem *item = new StateItem(0,0,40,40,0,scene );

        item->setStateNumber(state_compteur);
        item->setAcceptTouchEvents(true);
        item->setAcceptsHoverEvents(true);

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
            }

        }

    }

}



