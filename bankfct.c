#include <stdio.h>
#include <stdlib.h>

#include "bankfct.h"

#define TAILLE_MAX 1024

void vide_buffer(void)
{
    int c;
    do{c = getchar();} while (c!='\n' && c != EOF);
}

int read_clifile(void)
{
    FILE *clifile = NULL;
    char prb[1];

    clifile = fopen("clifile.csv", "r");
    if (clifile == NULL)
    {
        printf("\n\t\t****** Impossible d'ouvrir le fichier client clifile ******\n");
        printf("Le programme va s'arreter, appuyer sur une touche, puis 'entrer'");
        scanf("%c", &prb);
        exit(0);
    }

    char buffer[TAILLE_MAX] = "";

    int row = 0;
    int column = 0;

    printf("\n\t\t****** Affichage du fichier client ******\n\n");
    while(fgets(buffer, TAILLE_MAX, clifile) != NULL)
    {
        /*if (row == 0)
            continue;*/
        char* value = strtok(buffer, ",");
        while (value)
        {
            switch(column)
            {
            case 0:
                printf("Account ID: %s\t", value);
                break;
            case 1:
                printf("Owner: %s\t", value);
                break;
            case 2:
                printf("Amount: %s\t", value);
                break;
            }
            value = strtok(NULL, ",");
            column++;
        }
        printf("\n");
        row++;
        column = 0;
    }

    fclose(clifile);

    return 0;
}

int nb_client(void)
{
    FILE *clifile = NULL;
    char buffer[TAILLE_MAX] = "";
    int i = 0;

    clifile = fopen("clifile.csv", "r");
    if (clifile == NULL)
        return EOF; //erreur

    while (fgets(buffer, TAILLE_MAX, clifile) != NULL)
        i++;

    fclose(clifile);

    return i;
}

int add_client(void)
{
    int next_idacc = 0;
    int *pnext_idacc = &next_idacc;
    char cliname[16] = "";
    char *pcliname = &cliname;
    float solde = 0.0;
    float *psolde = &solde;
    FILE *clifile = NULL;

    char opecli[25] = "";
    FILE *opefile = NULL;
    char prb[1]; //placebo pour affichage message exit(0)

    printf("\n\t\t****** Ouverture d un compte client ******\n\n");
    if (nb_client() == EOF){printf("Erreur a l ouverture du fichier client\n"); printf("Le programme va s'arreter, appuyer sur une touche, puis 'entrer'"); scanf("%c", &prb); exit(0);}

    printf("entrer le nom du client: (pas de caractere espace) ");
    scanf("%s", pcliname);
    vide_buffer;
    printf("entrer le solde a l ouverture du compte: ");
    scanf("%f", psolde);
    vide_buffer;

    *pnext_idacc = 4000 + (nb_client() + 1); //on a choisit un id avec un pattern '4000', on incremente en fonction


    printf("\nClient %s cree avec succes, recapitulatif:\n", cliname);
    printf("account ID: %d \towner: %s \tamount: %f\n\n", *pnext_idacc, cliname, solde);

    //ecrire dans le csv
    clifile = fopen("clifile.csv", "r+");
    if (clifile == NULL){printf("Erreur a l ouverture du fichier client\n"); printf("Le programme va s'arreter, appuyer sur une touche, puis 'entrer'"); scanf("%c", &prb);exit(0);}

    fseek(clifile, 0, SEEK_END);
    fprintf(clifile, "\n%d, %s, %f", next_idacc, cliname, solde);
    printf("Instance client ajoute au fichier client\n");

    fclose(clifile);

    //creer un fichier d operation (credit debit)
    sprintf(opecli, "operations_compte%d.csv", next_idacc);
    opefile = fopen(opecli, "a");
    if (opefile == NULL) {printf("Erreur a la creation du fichier d operation client\n"); printf("Le programme va s'arreter, appuyer sur une touche, puis 'entrer'"); scanf("%c", &prb);exit(0);}

    fprintf(opefile, "solde_depart, %f", solde);
    printf("Le fichier d historique des operations '%s' a ete cree pour le compte %d\n", opecli, next_idacc);

    fclose(opefile);

    return 0;
}

int sold_client(void)
{
    FILE *opefile = NULL;
    //FILE *clifile = NULL;
    char* tabope = NULL;
    char opecli[25]= "";
    int idacc;
    char prb[1];

    printf("\n\t\t****** Affichage du solde ******\n\n");

    printf("Entrez le numero de compte a consulter: ");
    scanf("%d", &idacc);
    sprintf(opecli, "operations_compte%d.csv", idacc); //concatener un char & un int

    opefile = fopen(opecli, "r");

    if (opefile == NULL)
    {
        printf("\n\t\t****** Impossible d'ouvrir le fichier d historique des operations ******\n\n");
        printf("Le compte %d ne semble pas etre ouvert chez Bankpho\n\n", idacc);
        printf("Le programme va s'arreter, appuyer sur une touche, puis 'entrer'");
        scanf("%c", &prb);
        exit(0);
    }

    char buffer[TAILLE_MAX] = "";
    char *pvalue = NULL;
    int row = 0;
    int column = 0;
    int nbl=0;
    //float curmont, cursold;


    //nb ligne
    while(fgets(buffer, TAILLE_MAX, opefile) != NULL)
        nbl +=1;

    tabope = malloc(nbl * 100/*sizeof(char)*/);
        if (tabope == NULL)
        {
            printf("Echec allocation de memoire, relancez le programme\n");
            printf("Le programme va s'arreter, appuyer sur une touche, puis 'entrer'");
            scanf("%c", &prb);
            exit(0);
        }


    fseek(opefile, 0, SEEK_SET); //revenir au debut du fichier

    while(fgets(buffer, TAILLE_MAX, opefile) != NULL)
    {
        pvalue = strtok(buffer, ",");
        while (pvalue)
        {
            switch(column)
            {
            case 0:
                //libelle insignifiant
                break;
            case 1:
                printf("Montant: %s\n", pvalue);
                //tabope[row] = *pvalue;
                //printf("%s", tabope[row]);
                break;
            }
            pvalue = strtok(NULL, ",");
            column++;
        }
        row++;
        column = 0;
    }

    //for (int j = 0 ; j < nbl ; j++)
        //printf("case %d: %s\n", j, tabope[j]);

    fclose(opefile);
    free(tabope);

    printf("\n\t\t******Work in Progress******\n\n");
    printf("Calcul du solde indisponible\n\n");
    printf("Il reste a enregistrer les operations dans un tableau\n\
et caster les chaines de caractere en float\n\n");
    printf("referez vous au code source pour voir le debut de solution\n");


    return 0;
}

int read_opefile(void)
{
    FILE *opefile = NULL;
    char opecli[25] = "";
    int idacc;
    char prb[1];

    printf("Entrez le numero de compte a consulter: ");
    scanf("%d", &idacc);
    sprintf(opecli, "operations_compte%d.csv", idacc); //concatener un char & un int

    opefile = fopen(opecli, "r");
    if (opefile == NULL)
    {
        printf("\n\t\t****** Impossible d'ouvrir le fichier d historique des operations ******\n\n");
        printf("Le compte %d ne semble pas etre ouvert chez Bankpho\n\n", idacc);
        printf("Le programme va s'arreter, appuyer sur une touche, puis 'entrer'");
        scanf("%c", &prb);
        exit(0);
    }

    char buffer[TAILLE_MAX] = "";
    int row = 0;
    int column = 0;

    printf("\n\t\t****** Affichage des operations ******\n\n");
    while(fgets(buffer, TAILLE_MAX, opefile) != NULL)
    {
        /*if (row == 0)
            printf("libelle_operation\tmontant_operation\n");*/

        char* value = strtok(buffer, ",");
        while (value)
        {
            switch(column)
            {
            case 0:
                printf("Libelle: %s\t", value);
                break;
            case 1:
                printf("Montant: %s", value);
                break;
            }
            value = strtok(NULL, ",");
            column++;
        }
        //printf("\n");
        row++;
        column = 0;
    }
    printf("\n");

    fclose(opefile);

    return 0;
}

int cred_client(void)
{

    FILE *opefile = NULL;
    char opecli[25] = "";
    char opelib[100] = "default";
    int idacc;
    float opecred = 0;
    char prb[1];

    printf("Entrez le numero de compte a crediter: ");
    scanf("%d", &idacc);
    sprintf(opecli, "operations_compte%d.csv", idacc); //concatener un char & un int

    opefile = fopen(opecli, "r+");
    if (opefile == NULL)
    {
        printf("\n\t\t****** Impossible d'ouvrir le fichier d historique des operations ******\n\n");
        printf("Le compte %d ne semble pas etre ouvert chez Bankpho\n\n", idacc);
        printf("Le programme va s'arreter, appuyer sur une touche, puis 'entrer'");
        scanf("%c", &prb);
        exit(0);
    }

    printf("\n\t\t****** Crediter le compte client %d ******\n\n", idacc);
    printf("Entrez le libelle de l'operation: ");
    scanf("%s", &opelib);
    vide_buffer();
    printf("\nEntrez le montant a crediter: ");
    scanf("%f", &opecred);
    vide_buffer();

    printf("\nCompte %d credite avec succes, recapitulatif:\n", idacc);
    printf("Libelle: %s \tmontant: %f\n\n", opelib, opecred);

    //ecrire dans le csv
    fseek(opefile, 0, SEEK_END);
    fprintf(opefile, "\n%s, %f", opelib, opecred);
    printf("Operation de credit ajoute au fichier 'operations_compte%d'\n", idacc);

    fclose(opefile);

    return 0;
}

int deb_client(void)
{
    FILE *opefile = NULL;
    char opecli[25] = "";
    char opelib[100] = "default";
    int idacc;
    float opedeb = 0;
    //float *popedeb = &opedeb;
    char prb[1];

    printf("Entrez le numero de compte a debiter: ");
    scanf("%d", &idacc);
    sprintf(opecli, "operations_compte%d.csv", idacc); //concatener un char & un int

    opefile = fopen(opecli, "r+");
    if (opefile == NULL)
    {
        printf("\n\t\t****** Impossible d'ouvrir le fichier d historique des operations ******\n\n");
        printf("Le compte %d ne semble pas etre ouvert chez Bankpho\n\n", idacc);
        printf("Le programme va s'arreter, appuyer sur une touche, puis 'entrer'");
        scanf("%c", &prb);
        exit(0);
    }

    printf("\n\t\t****** Debiter le compte client %d ******\n\n", idacc);
    printf("Entrez le libelle de l'operation: ");
    scanf("%s", &opelib);
    vide_buffer();
    printf("\nEntrez le montant a crediter: ");
    scanf("%f", &opedeb);
    vide_buffer();

    printf("\nCompte %d debite avec succes, recapitulatif:\n", idacc);
    printf("Libelle: %s \tmontant: %f\n\n", opelib, opedeb);
    opedeb *= -1; //passer le montant en negatif

    //ecrire dans le csv
    fseek(opefile, 0, SEEK_END);
    fprintf(opefile, "\n%s, %f", opelib, opedeb);
    printf("Operation de debit ajoute au fichier 'operations_compte%d'\n", idacc);

    fclose(opefile);

    return 0;
}

int bankpho_99(void)
{
    //printf("\nrien en attente, la derniere amelioration est passee en production\n\n");
    FILE *opefile = NULL;
    //FILE *clifile = NULL;
    char* tabope = NULL;
    char opecli[25]= "";
    int idacc;
    char prb[1];

    printf("\n\t\t****** Affichage du solde ******\n\n");

    printf("Entrez le numero de compte a consulter: ");
    scanf("%d", &idacc);
    sprintf(opecli, "operations_compte%d.csv", idacc); //concatener un char & un int

    opefile = fopen(opecli, "r");

    if (opefile == NULL)
    {
        printf("\n\t\t****** Impossible d'ouvrir le fichier d historique des operations ******\n\n");
        printf("Le compte %d ne semble pas etre ouvert chez Bankpho\n\n", idacc);
        printf("Le programme va s'arreter, appuyer sur une touche, puis 'entrer'");
        scanf("%c", &prb);
        exit(0);
    }

    char buffer[TAILLE_MAX] = "";
    char *pvalue = NULL;
    int row = 0;
    int column = 0;
    int nbl=0;
    //float curmont, cursold;


    //nb ligne
    while(fgets(buffer, TAILLE_MAX, opefile) != NULL)
        nbl +=1;

    tabope = malloc(nbl * 100/*sizeof(char)*/);
        if (tabope == NULL)
        {
            printf("Echec allocation de memoire, relancez le programme\n");
            printf("Le programme va s'arreter, appuyer sur une touche, puis 'entrer'");
            scanf("%c", &prb);
            exit(0);
        }


    fseek(opefile, 0, SEEK_SET); //revenir au debut du fichier

    while(fgets(buffer, TAILLE_MAX, opefile) != NULL)
    {
        pvalue = strtok(buffer, ",");
        while (pvalue)
        {
            switch(column)
            {
            case 0:
                //libelle insignifiant
                break;
            case 1:
                printf("Montant: %s\n", pvalue);
                //tabope[row] = *pvalue;
                //printf("%s", tabope[row]);
                break;
            }
            pvalue = strtok(NULL, ",");
            column++;
        }
        row++;
        column = 0;
    }

    //for (int j = 0 ; j < nbl ; j++)
        //printf("case %d: %s\n", j, tabope[j]);

    fclose(opefile);
    free(tabope);

    printf("\n\t\t******Work in Progress******\n\n");
    printf("Calcul du solde indisponible\n\n");
    printf("Il reste a enregistrer les operation dans un tableau\n\
et caster les chaines de caractere en float\n\n");
    printf("referez vous au code source pour voir le debut de solution\n");

    return 0;
}
