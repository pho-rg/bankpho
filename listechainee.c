#include <stdio.h>
#include <stdlib.h>

#include "bankfct.h"

//------------------------------------------------------------------|
//travaux sur les listes chainees pas assez fiable pour deploiement |
//------------------------------------------------------------------|

/*
static Cell *createCellope(char label[25], float data) //fonction creation cellule propre a ce fichier (static) reprennant la struct List<>Cell avec parametre(donnee, pointeur)
 {
    Cell *cell = malloc(sizeof(Cell)); //allocation zone mem var *cell de type pointer et de struct Cell<>List de la taille d'une cellule de struct Cell<>List

    cell->label = label;
    cell->data = data; //la valeur de cell (qui correspond a la donnee 'data' de la struct Cell<>List) est egale au parametre data de la fonction createCell
    cell->next = NULL; //la valer de cell (qui correspond au pointeur 'next' de la struct Cell<>List) est egale a NULL puisque cette cellule juste cree est la derniere de notre liste

    return cell; //on a notre cellule de crée
}

static Cell *createCellclient(int accnum, char label[25], float data) //fonction creation cellule propre a ce fichier pour la liste client
 {
    Cell *cell = malloc(sizeof(Cell)); //allocation zone mem var *cell de type pointer et de struct Cell<>List de la taille d'une cellule de struct Cell<>List

    cell->accnum = accnum;
    cell->label = label;
    cell->data = data; //la valeur de cell (qui correspond a la donnee 'data' de la struct Cell<>List) est egale au parametre data de la fonction createCell
    cell->next = NULL; //la valer de cell (qui correspond au pointeur 'next' de la struct Cell<>List) est egale a NULL puisque cette cellule juste cree est la derniere de notre liste

    return cell; //on a notre cellule de crée
}

////functions
//garder en tête que *L pointe vers le premier element de la liste
List *emptyList(void)
{
    return NULL;
}

int isEmptyList(List *L)
{
    return L == NULL;           //si valeur de la zone mem du parametre *L est nulle -> renvoi 1 ; sinon 0
}

long lenList(List *L)
{
    long len = 0;
    while (!isEmptyList(L)) //on parcours la liste
    {
        len++;
        L = L->next //L (soit le pointeur du premier element de la liste) devient le pointeur de la cellule suivante
    }
    return len;
}

List *addAt(List *L, int data, int pos)
{
    //pour ajouter un element il faut creer la cellule first -> cf fct createCell
    List *pprec = L; //pprec est un pointeur qui pointe sur la valeur de la cellule précédente
    List *pcur = L; //pcur est un pointeur qui pointe la valeur de la cellule actuelle
    int i;

    Cell *cell = createCell(data); //on cree une nouvelle cellule avec le parametre voulut dans addAt
    //gerer le cas de la liste vide ; il faut mettre la cellule en premiere position
    if(isEmptyList(L))
    {
        return cell; //notre liste est egale a notre liste allouee soit la cellule jsute cree
    }
    //gerer le cas ou la pos dder est 0 mais la liste n est pas vide
    if(pos==0)
    {
        cell->next = L; //la cellule alloue va pointer cers le reste de la liste ; soit le pointeur 'next' de la cellule juste cree pointe sur L
        return cell;    //on retourne la cellule juste cree puisqu'elle devient pointeur de tete (pos 0) ; plist pointe desormais sur 'data' de cellule juste cree
    }
    //gerer le cas pos dder est entre pos 0 et pos -1 via une boucle
    i = 0;
    while(i<pos)
    {
        i++;
        pprec = pcur; //pointeur precedent(i-1) vaut la cellule courante(i) ; but de garder en memoire pour inserer cellule juste cree
        pcur = pcur->next; //la cellule courante(i) vaut la cellule d'apres(i+1) ; tjs pour inserer sans perdre l'info
    }
    pprec->next = cell; //chainage ; pointeur prec(i-1) pointe sur valeur de cellule juste cree
    cell->next = pcur; //cellule juste cree pointe sur la valeur de cellule curent (i), qui devient la cellule d'apres(i+1)

    return L;

}

int getAt(List *L, int pos)
{
    int i = 0;
    //gerer le cas de la liste vide
    if (isEmptyList(L))
    {
        printf("liste vide\n");
        return -1; //donner une valeur par defaut
    }
    //trouver la pos dde
    while (i < pos)
    {
        i++;
        L = L->next; //passer a la cellule suivante jusque trouver le bon element (i=pos)
    }
    return L->data; //on donne la valeur de l'element pour L=i
}

void setAt(List *L, int newdata, int pos)
{
    i = 0;
    if(isEmptyList(L))
    {
        printf("la liste est vide\n");
        return //ne retourne rien
    }
    while(!isEmptyList(L))
    {
        i++;
        L = L->next;
    }
    L->data = newdata; //modification de la donnee pour la cellulle pos i
}

List *freeAt(List *L, int pos) //meme base que addAt()
{
    List *pprec = L;
    List *pcur = L;
    int i;

    //gerer cas liste vide
    if(isEmptyList(L))
    {
        return NULL;
    }
    //cas pos = 0
    if (pos==0)
    {
        L = L->next; //on pointe le debut de la liste sur adr cellule suivante
        free(pcur);
        return L;
    }
    //tt les autres cas
    while (i < pos) //parcourir jusque i en chopant l'info adr des cellules i-1 ; i et i+1
    {
        i++;
        pprec = pcur; //cellule i-1 pointe sur cellule i
        pcur = pcur->next; //cellule i pointe sur cellule i+1
    }
    prec->next = cur->next; //cellule i-1 pointe sur cellule i+1 ; passover cellule i
    free(cur); //effacement cellule i

    return L;
}

List *freeList(List *L)
{
    List *pprov = NULL; //creation var provisoire qui est un pointeur de type List
    while (!isEmptyList(L))
    {
        pprov = L->next; //on met adr cellule i+1 dans pprov qui est un buffer
        free(L); //on libere l'adr de la cellule i
        L = pprov; //L (pointeur du premier element de notre liste) prend la valeur de cellule i+1 (devenu i avec le free de la cellule i)
    }
    return L;
}

void printList(List *L)
{
    while(!isEmptyList(L)) //tant que la liste n'est pas vide
    {
        printf("%d ", L->data); //afficher la valeur de la cellule de la liste
        L = L->next;    //la cellule courante devient egale a la cellule d'apres jusqu'à tomber sur NULL, la derniere cellule
    }
    printf("\n");
}
*/
