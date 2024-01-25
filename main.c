#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAILLE_BLOCS 1000

typedef struct {
    char bloc[TAILLE_BLOCS + 1]; // Tableau de caractères avec une taille de TAILLE_BLOCS + 1
} Tbloc;

typedef struct {
    int NbBloc;      // Nombre de blocs dans le fichier
    int NbEng;   // Nombre total d'enregistrements dans le fichier
} Entete;
// Structure pour un enregistrement
typedef struct {
    int taille; // Taille de l'enregistrement
    int efface; // Indicateur d'effacement logique
    char cle[20]; // Clé de l'enregistrement
    char info[N]; // Autres informations de l'enregistrement
} Enregistrement;

// Structure pour un bloc
typedef struct {
    char tab[B]; // Tableau de caractères
    int NB; // Nombre d'enregistrements dans le bloc
    int suivant; // Numéro du bloc suivant
} Bloc;

// Structure pour l'en-tête du fichier
typedef struct {
    int premierBloc; // Numéro du premier bloc
    int dernierBloc; // Numéro du dernier bloc
    int premierePositionLibre; // Première position libre dans le dernier bloc
    int caracteresPerdus; // Nombre de caractères perdus suite aux suppressions logiques
    int NbBloc;      // Nombre de blocs dans le fichier
    int NbEng;   // Nombre total d'enregistrements dans le fichier
} Entete;

// Structure pour le fichier
typedef struct {
    FILE* f; // Pointeur vers le fichier
    Entete entete; // En-tête du fichier
    Bloc buffer; // Tampon pour un bloc
} Fichier;

int main() {
    // Créer un nouveau fichier (ou l'ouvrir s'il existe déjà)
    Fichier* f = ouvrir("monFichier.txt", 'A');
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    // Rechercher un enregistrement
    int cleRecherche = 123;
    bool trouve;
    int bloc, position;
    Recherche(cleRecherche, "monFichier.txt", &trouve, &bloc, &position);

    if (trouve) {
        printf("L'enregistrement avec la clé %d a été trouvé dans le bloc %d à la position %d.\n", cleRecherche, bloc, position);
    } else {
        printf("L'enregistrement avec la clé %d n'a pas été trouvé.\n", cleRecherche);
    }

    // Insérer un nouvel enregistrement
    Enregistrement nouvelElement;
    // Initialisez les champs de nouvelElement selon besoins
    insertion(f, nouvelElement);

    // Marquer un enregistrement comme supprimé
    Suppression_logique("123", "monFichier.txt");

    // Fermer le fichier
    fermer(f);

    return 0;
}
