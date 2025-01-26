#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Commande
{
    int id;
    char client[50];
    char description[100];
    char statut[20];
    char date[20];
    struct Commande* suivant;
} Commande;

typedef struct
{
    Commande* tete;
    Commande* queue;
    int taille;
} FileCommande;

void initFile(FileCommande* file)
{
    file->tete = NULL;
    file->queue = NULL;
    file->taille = 0;
}

void ajouterCommande(FileCommande* file, int id, const char* client, const char* description, const char* statut, const char* date)
{
    Commande* nouvCommande = (Commande*)malloc(sizeof(Commande));

    nouvCommande->id = id;
    strcpy(nouvCommande->client, client);
    strcpy(nouvCommande->description, description);
    strcpy(nouvCommande->statut, statut);
    strcpy(nouvCommande->date, date);
    nouvCommande->suivant = NULL;

    if (file->queue == NULL) // Si la file est vide
    {
        file->tete = nouvCommande;
        file->queue = nouvCommande;
    }
    else
    {
        file->queue->suivant = nouvCommande;
        file->queue = nouvCommande;
    }

    file->taille++;
    printf("Commande ajoutee avec succes !\n");
}

void annulerCommande(FileCommande* file)
{
    if (file->tete == NULL)
    {
        printf("Aucune commande en attente.\n");
        return;
    }

    Commande* commandeAnnulee = file->tete;
    file->tete = file->tete->suivant;

    if (file->tete == NULL)  // Si la file est maintenant vide
    {
        file->queue = NULL;
    }

    printf("Commande ID %d annulee avec succes.\n", commandeAnnulee->id);
    free(commandeAnnulee);
    file->taille--;
}
Commande* rechercherCommande(FileCommande* file, int id)
{
    Commande* courant = file->tete;

    while (courant != NULL)
    {
        if (courant->id == id)
        {
            return courant; 
        }

        courant = courant->suivant;
    }

    return NULL; 
}

void afficherHistorique(FileCommande* file)
{
    if (file->tete == NULL)
    {
        printf("Aucune commande a afficher.\n");
        return;
    }

    Commande* courant = file->tete;

    printf("Historique des commandes :\n");

    while (courant != NULL)
    {
        printf("ID: %d | Client: %s | Description: %s | Statut: %s | Date: %s\n",
        courant->id, courant->client, courant->description, courant->statut, courant->date);

        courant = courant->suivant;
    }
}
void afficherCommandesEnAttente(FileCommande* file)
{
    if (file->tete == NULL)
    {
        printf("Aucune commande en attente.\n");
        return;
    }

    Commande* courant = file->tete;

    printf("Commandes en attente :\n");

    while (courant != NULL)
    {
        if (strcmp(courant->statut, "En attente") == 0)
        {
            printf("ID: %d | Client: %s | Description: %s | Date: %s\n",
            courant->id, courant->client, courant->description, courant->date);
        }

        courant = courant->suivant;
    }
}
