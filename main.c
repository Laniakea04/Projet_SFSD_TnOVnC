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
    char nomFichier[] = "monFichier.txt";

    // Créer un nouveau fichier
    Fichier* f = ouvrir(nomFichier, 'N');
    if (f == NULL) {
        printf("Erreur lors de la création du fichier.\n");
        return 1;
    }

    // Exemple de structure d'enregistrement à insérer
    Enregistrement nouvelElement;
    nouvelElement.taille = 15; // Taille de la chaîne d'informations
    nouvelElement.efface = 'F'; // Marqueur de suppression logique
    snprintf(nouvelElement.cle, sizeof(nouvelElement.cle), "%s", "nouvelleCle");
    snprintf(nouvelElement.info, sizeof(nouvelElement.info), "%s", "NouvellesInfos123");

    // Appel de la fonction d'insertion
    insertion(f, nouvelElement);

    // Fermer le fichier
    fermer(f);

    return 0;
}
