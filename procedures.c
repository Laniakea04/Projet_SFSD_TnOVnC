#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*-----------------Fonction de lecture d'un bloc----------------*/
void lireDir(Fichier *f,int N_Bloc,Tbloc *buffer)
{
    if(N_Bloc <= (f->entete).NbBloc) //Si le bloc existe
    {
        fseek(f->fichier, sizeof(Entete) + (N_Bloc-1) * sizeof(Tbloc),SEEK_SET); //On avance vers le bloc i
        fread(buffer, 1, sizeof(Tbloc), f->fichier); //On lit le bloc dans buffer
    }
}

/*-----------------Fonction d'�criture d'un bloc----------------*/
void ecrireDir(Fichier *f,int N_Bloc,Tbloc *buffer)
{
    if(N_Bloc <= (f->entete).NbBloc)
    {
        fseek(f->fichier, sizeof(Entete) + (N_Bloc-1) * sizeof(Tbloc),SEEK_SET);  //On avance vers la position i ou on veut ecrire
        fwrite(buffer, 1, sizeof(Tbloc), f->fichier);
    }
}


// Fonction pour ouvrir un fichier
Fichier* ouvrir(char* chemin, char mode) {
    // Allouer de la mémoire pour la structure Fichier
    Fichier* f = malloc(sizeof(Fichier));

    // Déterminer le mode d'ouverture du fichier
    char* s;
    if(mode == 'A' || mode == 'a') {
        s = "rb+"; // Mode lecture et écriture
    } else if(mode == 'N' || mode == 'n') {
        s = "wb+"; // Mode écriture
    } else {
        free(f);
        return NULL; // Mode non reconnu
    }

    // Ouvrir le fichier
    f->fichier = fopen(chemin, s);

    // Vérifier si l'ouverture du fichier a réussi
    if(f->fichier == NULL) {
        free(f);
        return NULL; // L'ouverture du fichier a échoué
    }

    // Retourner le pointeur vers la structure Fichier
    return f;
}

/*-----------------fonction fermer----------------------*/

void fermer(Fichier *f)
{
    //Sauvegarde de l'ent�te
    rewind(f->fichier);
    fwrite(&(f->entete), sizeof(Entete), 1, f->fichier);
    fclose(f->fichier); //Fermiture du fichier


}
// Fonction pour récupérer une chaîne de caractères à partir d'un bloc
void recuperer_chaine(int n, int* i, int* j, char* ch, Tbloc buffer) {
    // Parcourir les caractères de la chaîne
    for (int k = 0; k < n; k++) {
        // Vérifier si j est inférieur ou égal à la taille du bloc
        if (*j <= b) {
            // Copier le caractère du bloc dans la chaîne
            ch[k] = buffer.tab[*j];
            // Augmenter j
            (*j)++;
        }
    }
    // Ajouter le caractère de fin de chaîne
    ch[n] = '\0';
}

//procedure recherche


void Recherche(int c, char* nomfichier, bool* trouv, int* i, int* j) {
    FILE* f = ouvrir(nomfichier, 'r');
    *i = 1;
    *j = 1;
    *trouv = false;
    TBloc buffer;
    lireDir(f, *i, &buffer);

    while (!(*trouv) && (*i <= entete(f, 2) || (*i == entete(f, 2) && *j != entete(f, 3)))) {
        int longeur, efface, cle_rech;
        Recuperer_chaine(3, *i, *j, &longeur);
        Recuperer_chaine(1, *i, *j, &efface);
        Recuperer_chaine(20, *i, *j, &cle_rech);

        if (cle_rech == c && efface == 'F') {
            *trouv = true;
        } else {
            *j = *j + nombre(longeur) - 24;
            if (*j > b) {
                *j = 1;
                (*i)++;
                lireDir(f, *i, &buffer);
            }
        }
    }

    fermer(f);
}


// Assumons que les fonctions Ouvrir, Recherche et ecriredir sont déjà définies

void Suppression_logique(char* c, char* nomfichier) {
    bool trouv;
    int i, j;

    FILE* f = Ouvrir(nomfichier, 'A');
    Recherche(c, nomfichier, &trouv, &i, &j);

    if (trouv) {
        j = j + 3;
        buf.tab[j] = 'V';
        ecrireDir(f, i, j);
    } else {
        printf("L’élément n’existe pas !\n");
    }
}
void insertion(Fichier *f, Enregistrement nouvelElement) {
    // Variables pour suivre la position d'insertion
    int blocActuel = f->entete.premierBloc;
    int position = f->entete.premierePositionLibre;

    while (true) {
        Tbloc buffer;
        lireDir(f, blocActuel, &buffer);

        // Vérifier s'il y a de la place dans le bloc actuel pour l'enregistrement
        if (position + nouvelElement.taille + TAILLE_EN_TETE_ENREG <= TAILLE_BLOC) {
            // Insérer l'enregistrement dans le bloc actuel
            buffer.tab[position] = nouvelElement.taille;
            buffer.tab[position + 1] = nouvelElement.efface;
            snprintf(&buffer.tab[position + 2], sizeof(nouvelElement.cle), "%s", nouvelElement.cle);
            snprintf(&buffer.tab[position + 22], nouvelElement.taille - TAILLE_EN_TETE_ENREG, "%s", nouvelElement.info);

            // Mettre à jour l'en-tête du fichier
            f->entete.premierePositionLibre = position + nouvelElement.taille;
            ecrireDir(f, blocActuel, &buffer);
            fermer(f);
            return; // Insertion réussie, sortie de la fonction
        } else {
            // Le bloc actuel est plein, passer au bloc suivant s'il existe
            if (buffer.suivant != 0) {
                blocActuel = buffer.suivant;
                position = 0;
            } else {
                // Créer un nouveau bloc s'il n'y a pas de bloc suivant
                int nouveauBloc = allouerNouveauBloc(f);
                buffer.suivant = nouveauBloc;
                ecrireDir(f, blocActuel, &buffer);
                blocActuel = nouveauBloc;
                position = 0;
            }
        }
    }
}

// Fonction pour allouer un nouveau bloc et renvoyer son numéro
int allouerNouveauBloc(Fichier *f) {
    // ... (logique pour allouer un nouveau bloc, mise à jour des en-têtes)
}
