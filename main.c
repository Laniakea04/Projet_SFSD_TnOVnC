#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAILLE_BLOCS 1000

typedef struct {
    char bloc[TAILLE_BLOCS + 1]; // Tableau de caract�res avec une taille de TAILLE_BLOCS + 1
} Tbloc;

typedef struct {
    int NbBloc;      // Nombre de blocs dans le fichier
    int NbEng;   // Nombre total d'enregistrements dans le fichier
} Entete;
// Structure pour un enregistrement
typedef struct {
    int taille; // Taille de l'enregistrement
    int efface; // Indicateur d'effacement logique
    char cle[20]; // Cl� de l'enregistrement
    char info[N]; // Autres informations de l'enregistrement
} Enregistrement;

// Structure pour un bloc
typedef struct {
    char tab[B]; // Tableau de caract�res
    int NB; // Nombre d'enregistrements dans le bloc
    int suivant; // Num�ro du bloc suivant
} Bloc;

// Structure pour l'en-t�te du fichier
typedef struct {
    int premierBloc; // Num�ro du premier bloc
    int dernierBloc; // Num�ro du dernier bloc
    int premierePositionLibre; // Premi�re position libre dans le dernier bloc
    int caracteresPerdus; // Nombre de caract�res perdus suite aux suppressions logiques
    int NbBloc;      // Nombre de blocs dans le fichier
    int NbEng;   // Nombre total d'enregistrements dans le fichier
} Entete;

// Structure pour le fichier
typedef struct {
    FILE* f; // Pointeur vers le fichier
    Entete entete; // En-t�te du fichier
    Bloc buffer; // Tampon pour un bloc
} Fichier;
