// reservation.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservation.h"

#define FILE_RESERVATION "reservation.txt"
#define FILE_ID "id.txt"
/*
enum 
{
	EID;
	EDATE;
	ENOM;
	EPRENOM;
	ENOM_PARKING ;
	COLUMNS ;
};*/
int ajouter_reservation(char *file, reservation r) {
    FILE *f = fopen(file, "a");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }
    fprintf(f, "%s %s %s %s %s %d %d %d %d\n",
            r.client_info.nom, r.client_info.prenom, r.client_info.cin, r.nom_parking,
            r.client_info.num_telephone, r.id, r.date_reservation.jour,
            r.date_reservation.mois, r.date_reservation.annee);
    fclose(f);
    return 1;
}
/*
int modifier_reservation(int id1, reservation nouv) {
    int tr = 0;
    reservation r;
    FILE *f = fopen(FICHIER_RESERVATION, "r");
    FILE *f2 = fopen("nouv.txt", "w");

    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "nom client :%s prenom client %s cin :%s nom parking : %s telephone %s id reservation :%d date de reservation : %d %s %d\n",
                       r.client_info.nom, r.client_info.prenom, r.client_info.cin,
                       r.nom_parking.nom, r.client_info.num_telephone, &r.id,
                       &r.date_reservation.jour, r.date_reservation.mois,
                       &r.date_reservation.annee) != EOF) {
            if (r.id == id1) {
                fprintf(f2, "nom client :%s prenom client %s cin :%s nom parking : %s telephone %s id reservation :%d date de reservation : %d %s %d\n",
                        nouv.client_info.nom, nouv.client_info.prenom, nouv.client_info.cin,
                        nouv.nom_parking.nom, nouv.client_info.num_telephone, nouv.id,
                        nouv.date_reservation.jour, nouv.date_reservation.mois,
                        nouv.date_reservation.annee);
                tr = 1;
            } else {
                fprintf(f2, "nom client :%s prenom client %s cin :%s nom parking : %s telephone %s id reservation :%d date de reservation : %d %s %d\n",
                        r.client_info.nom, r.client_info.prenom, r.client_info.cin,
                        r.nom_parking.nom, r.client_info.num_telephone, r.id,
                        r.date_reservation.jour, r.date_reservation.mois,
                        r.date_reservation.annee);
            }
        }
    }
    fclose(f);
    fclose(f2);
    remove(FICHIER_RESERVATION);
    rename("nouv.txt", FICHIER_RESERVATION);
    return tr;
}
*/
int supprimer_reservation(char *file, int id) {
    FILE *f = fopen(file, "r");
    FILE *f2 = fopen("temp.txt", "w");  // Créer un fichier temporaire pour sauvegarder les autres réservations
    int result = 0;  // Variable pour vérifier si une réservation a été supprimée

    if (f != NULL && f2 != NULL) {
        reservation r;
        // Utilisation du format approprié pour lire les champs
        while (fscanf(f, "%s %s %s %s %s %d %d %d %d\n",
                       r.client_info.nom, r.client_info.prenom, r.client_info.cin,
                       r.nom_parking, r.client_info.num_telephone, &r.id,
                       &r.date_reservation.jour, &r.date_reservation.mois,
                       &r.date_reservation.annee) != EOF) {
            if (r.id != id) {
                // Si l'ID ne correspond pas, on garde la réservation dans le fichier temporaire
                fprintf(f2, "%s %s %s %s %s %d %d %d %d\n",
                        r.client_info.nom, r.client_info.prenom, r.client_info.cin,
                        r.nom_parking, r.client_info.num_telephone, r.id,
                        r.date_reservation.jour, r.date_reservation.mois,
                        r.date_reservation.annee);
            } else {
                result = 1;  // Réservation trouvée et supprimée
            }
        }
        fclose(f);
        fclose(f2);

        if (result) {
            remove(FILE_RESERVATION);  
            rename("temp.txt", FILE_RESERVATION); 
        } else {
            remove("temp.txt"); // Supprime le fichier temporaire si aucune réservation n'a été supprimée
        }

        return result;
    } else {
        if (f != NULL) fclose(f);
        if (f2 != NULL) fclose(f2);
        return 0; 
    }
}
reservation chercher_for_modif(char*file ,int id) {
    reservation r;
    FILE *f = fopen(file, "r");

    if (f != NULL) {
        while (fscanf(f, "%s %s %s %s %s %d %d %d %d\n",
                       r.client_info.nom, r.client_info.prenom, r.client_info.cin,
                       r.nom_parking, r.client_info.num_telephone, &r.id,
                       &r.date_reservation.jour, &r.date_reservation.mois,
                       &r.date_reservation.annee) != EOF) {
            if (r.id == id) {
                fclose(f);
                return r;
            }
        }
        fclose(f);
    }

    r.id = -1;  // Retourne une réservation avec un ID invalide si non trouvé
    return r;
}

int modifier_reservation(char*file ,int id1, reservation nouv) {
    int tr = 0;
    reservation r;
    FILE *f = fopen(file, "r");
    FILE *f2 = fopen("nouv.txt", "w");

    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%s %s %s %s %s %d %d %d %d\n",
                       r.client_info.nom, r.client_info.prenom, r.client_info.cin,
                       r.nom_parking, r.client_info.num_telephone, &r.id,
                       &r.date_reservation.jour, &r.date_reservation.mois,
                       &r.date_reservation.annee) != EOF) {
            if (r.id == id1) {
                fprintf(f2, "%s %s %s %s %s %d %d %d %d\n",
                        nouv.client_info.nom, nouv.client_info.prenom, nouv.client_info.cin,
                        nouv.nom_parking, nouv.client_info.num_telephone, nouv.id,
                        nouv.date_reservation.jour, nouv.date_reservation.mois,
                        nouv.date_reservation.annee);
                tr = 1;
            } else {
                fprintf(f2, "%s %s %s %s %s %d %d %d %d\n",
                        r.client_info.nom, r.client_info.prenom, r.client_info.cin,
                        r.nom_parking, r.client_info.num_telephone, r.id,
                        r.date_reservation.jour, r.date_reservation.mois,
                        r.date_reservation.annee);
            }
        }
        fclose(f);
        fclose(f2);
        remove(FILE_RESERVATION);
        rename("nouv.txt", FILE_RESERVATION);
    }
    return tr;
}




/*
void afficher_reservation (GtkWidget *liste );
{
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtklistStore *store;
int id;
char nom[50];
char prenom[50];
char nom_parking[100];
date_reservation_t date_reservation;
store=NULL;	
store = gtk_tree_view_get_model(liste);
	if (store != NULL) {
	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("id", renderer, "text", EID, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("date_reservation", EDATE, "text", TYPE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", ENOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text", EPRENOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("nom_parking", renderer, "text", ENOM_PARKING, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	}
        store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);
reservation r;
FILE *f = fopen(file, "r");
    if (f = NULL) {
        return ; 
        while (fscanf(f, "%s %s %s %s %d %d %d %s %d\n",
                       r.client_info.nom, r.client_info.prenom, r.client_info.cin,
                       r.nom_parking, &r.client_info.num_telephone, &r.id,
                       &r.date_reservation.jour, r.date_reservation.mois,
                       &r.date_reservation.annee) != EOF) 
{
	 gtk_list_store_append(store, &iter);
         gtk_list_store_set(store,&iter,EID,id,ENOM,nom,EPRENOM,prenom,EDATE,date,ENOM_PARKING,nom_parking,-1);
        fclose(f);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }
}

reservation chercher_for_modif(int id) {
    reservation r;
    FILE *f = fopen(FICHIER_RESERVATION, "r");

    if (f != NULL) {
        while (fscanf(f, "%s %s %s %s %d %d %d %d %d\n",
                       r.client_info.nom, r.client_info.prenom, r.client_info.cin,
                       r.nom_parking, &r.client_info.num_telephone, &r.id,
                       &r.date_reservation.jour, &r.date_reservation.mois,
                       &r.date_reservation.annee) != EOF) {
            if (r.id == id) {
                fclose(f);
                return r;
            }
        }
        fclose(f);
    }

    r.id = -1;  // Retourne une réservation avec un ID invalide si non trouvé
    return r;
}

int modifier_reservation(int id1, reservation nouv) {
    int tr = 0;
    reservation r;
    FILE *f = fopen(FICHIER_RESERVATION, "r");
    FILE *f2 = fopen("nouv.txt", "w");

    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%s %s %s %s %d %d %d %d %d\n",
                       r.client_info.nom, r.client_info.prenom, r.client_info.cin,
                       r.nom_parking, &r.client_info.num_telephone, &r.id,
                       &r.date_reservation.jour, &r.date_reservation.mois,
                       &r.date_reservation.annee) != EOF) {
            if (r.id == id1) {
                fprintf(f2, "%s %s %s %s %d %d %d %d %d\n",
                        nouv.client_info.nom, nouv.client_info.prenom, nouv.client_info.cin,
                        nouv.nom_parking, nouv.client_info.num_telephone, nouv.id,
                        nouv.date_reservation.jour, nouv.date_reservation.mois,
                        nouv.date_reservation.annee);
                tr = 1;
            } else {
                fprintf(f2, "%s %s %s %s %d %d %d %d %d\n",
                        r.client_info.nom, r.client_info.prenom, r.client_info.cin,
                        r.nom_parking, r.client_info.num_telephone, r.id,
                        r.date_reservation.jour, r.date_reservation.mois,
                        r.date_reservation.annee);
            }
        }
        fclose(f);
        fclose(f2);
        remove(FICHIER_RESERVATION);
        rename("nouv.txt", FICHIER_RESERVATION);
    }
    return tr;
}

*/
