#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour une commande
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
