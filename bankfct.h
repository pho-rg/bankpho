//fichier header bankpho
#ifndef __LIST_H__
#define __LIST_H__


//------STRUCTURES------

typedef struct Cell_t {         //struct d un maillon de la liste chainee
    int accnum;                  //donnee numero de compte (liste client)
    float data;                 //donnee solde (liste client) montant (liste operation)
    char label[25];           //donnee nom client (liste client) libelle (liste operation)
    struct Cell_t*next;       //pointeur vers cellule suivante
} List, Cell;                   //on donne deux noms à la struct ; List as ensemble de cellule

//------PROTOTYPE DU FICHIER bankfct.c------

void vide_buffer(void); //vider la memoire temporaire
int read_clifile(void); //affiche le fichier client
int nb_client(void); //renvoi le nombre de client ayant un compte chez bankpho
int add_client(void); //procedure d ajout d un client
int sold_client(void); //consulter le solde d'uun compte client
int read_opefile(void); //consulter les operations (debit - credit) d'un compte client
int cred_client(void); //crediter un compte client
int deb_client(void); //debiter un compte client
int bankpho_99(void); //test amelioration avant deploiement

//------PROTOTYPE DU FICHIER listechainee.c------

//------------------------------------------------------------------|
//travaux sur les listes chainees pas assez fiable pour deploiement |
//cf fichier listechainee.c                                         |
//------------------------------------------------------------------|
/*
List *emptyList(void);          //liste vide de départ
int isEmptyList(List*);         //fonction detectant la liste vide (1 si oui ; 0 sinon)
long lenList(List*);            //fonction de calcul taille de la liste
List *addAt(List*, int, int);   //fonction ajout d'un element a une position donnee (
int getAt(List*, int);          //fonction recuperation d'un element a une position donnee
void setAt(List*, int, int);    //fonction modification d'un element a une position donnee
List *freeAt(List *, int);      //fonction effacement d'un element a une position donnee
List *freeList(List *);         //fonction effacer toute la liste
void printList(List *;)         //fonction affichage contenu de la liste
*/

#endif // __LIST_H__
