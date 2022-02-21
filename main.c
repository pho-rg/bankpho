#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>

#include "bankfct.h"

#define TAILLE_MAX 1024

int main(void)
{
    //initier les listes chainees du jeu de depart

    //------------------------------------------------------------------|
    //travaux sur les listes chainees pas assez fiable pour deploiement |
    //cf fichiers bankfct.h et listechainee.c                           |
    //------------------------------------------------------------------|
    /*
    List *plistclient = emptyList();  //initaliser notre liste chainee client
    List *plistope = emptyList();  //initaliser notre liste chainee operation (credit debit)
    */


    //boucle de choix utilisateur
    int choix;
    int sortie = 0;
    char prb[1];

    _nvlsaisie:
    printf("\n\t\t****** Royal Evasion Bankpho ****** \n\n\
Quelle action souhaitez-vous faire\n\
           1 Lister les comptes clients et leur solde\n\
           2 Ouvrir un compte chez Bankpho\n\
           3 Afficher le solde d'un compte client\n\
           4 Lister les operations d'un compte client\n\
           5 Crediter un compte client\n\
           6 Debiter un compte client\n\n\
           9 Quitter l'espace de consultation de la Royal Evasion Bankpho\n\n\
votre choix: ");
    scanf("%d", &choix);
    vide_buffer();
    switch(choix)
    {
    case 1:
        read_clifile();
        break;
    case 2:
        add_client();
        break;
    case 3:
        sold_client(); //idacc clifile.csv
        break;
    case 4:
        read_opefile(); //idacc opefile.csv
        break;
    case 5:
        cred_client(); //idacc montant opefile.csv
        break;
    case 6:
        deb_client(); //idacc montant opefile.csv
        break;
    case 9:
        printf("Vous avez choisit de finir les tests de l'exercice 4 'bankpho'\n\
tout le code est documente dans le rapport 'rapport_dm1langc_pierrehenry_dorglandes.pdf'\n\
vous avez teste tous les exercices du dossier 'dm1_langc_pierrehenry_dorglandes'\n\n");
        printf("Le programme va s'arreter, appuyer sur une touche, puis 'entrer'");
        scanf("%c", &prb);
        sortie = 1;
        break;
    case 99: //test amelioration programme
        bankpho_99();
        break;
    default:
        printf("Saisie invalide, le choix est entre 1 et 6\n\n");
        goto _nvlsaisie;
        break;
    }
    if (sortie != 1)
        goto _nvlsaisie;

    return 0;

}
