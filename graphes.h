/*
 * graphes.c
 *
 *  Created on: Apr 16, 2016
 *     Authors: Valentina Zelaya & Theo Hermann
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define true 1
#define false 0
#define MAX_NAME 60
#define MAX_POIDS 100
#define MIN_POIDS 25
#define MAX_STOCK 80
#define MIN_STOCK 0
#define LG_MAX_LIGNE_FICHIER_DOT 300
#define MAX_CHIFFRES 5



/*** Definition des structures utilisées ***/

typedef int boolean;

typedef struct noeud{
	int num;                /*numéro de noeud*/
	char name[MAX_NAME];	/*étiquette du noeud*/
	int poids;	 	/* poids de l'arc qui relie ce noeud 
					avec son prédécesseur*/
	int stock;		/*qte de marchandises dans le dépôt*/
	struct Noeud* suiv;	/*tab de pointeurs vers les arcs du noeud*/
}Noeud;

typedef Noeud** Graphe;



/*** graphes.c ***/


/*
 * Constructeur
 */
Noeud* newNoeud(int aNum,char* aName,int aPoids,Noeud* aSuiv,int aStock);


/*
 * Constructeur par copie
 */
Noeud* copyNoeud(Noeud* unN);


/* nsom : nombre de sommets.
   nmaxarc : nombre maximum d'arcs.
   Alloue la memoire necessaire pour representer un graphe a 'nsom' sommets,
   possedant au maximum 'nmaxarc' arcs.
   Retourne un pointeur sur la structure allouee. */
Graphe InitGraphe(int nsom);


/*g : un graphe.
  Libere la memoire occupee par le graphe g. */
void TermineGraphe(Graphe g,int nsom);


/*listeN: le noeud de la liste chainee auquel on ajoutera le nouveau noeud
 * newN: le nouveau noeud à ajouter
 * Ajoute un noeud à la liste chainee de listeN
 * */
Noeud* AjouteNoeudQueue(Noeud * listeN,Noeud* newN);



/*pList: pointeur vers une liste chainee de noeuds
 * num: numéro du noeud dont on veut tester l'appartenance à pList
 * Renvoie vrai (1) si le noeud de numero num appartient à pList
 */
int EstDansListe(Noeud* pList, int num);


/* g: un graphe
 * i: le numero du sommet origine
 * s: le numero du noeud potentiellement successeur
 * Renvoie vrai (1) si le noeud de numero s est dans la liste chainee du noeud numero i
 *
 */
int EstSuccesseur(Graphe g, int i, int s);


/* g: un graphe
 * pNi: pointeur vers le noeud dont on souhaite avoir le successeur 
 * j: numero du successeur que l'on veut récupérer
 * 
 * Renvoie le successeur du noeud pointe par pNi
 */
Noeud* getSucceseur(Graphe g,Noeud* pNi, int j);


/* pList: pointeur vers un debut de chemin
 * num: numero du noeud lié à pList
 *
 * Renvoie le poids de la liaison entre un noeud et un de ses successeurs
 */
int poidsDansListe(Noeud* pList,int num);


/* i: num du noeud pere
 * j: numero d'un noeud fils
 *
 * Renvoie le poids de la liaison entre un noeud et un de ses successeurs
 */
int getPoids(Graphe g, int i,int j);


/* p: pointeur vers un noeud
 *
 * Renvoie le nombre de successeurs d'un noeud donné (nb d'élts de la liste chainee d'un noeud)
 */
int nbSuccesseurs(Noeud *p);



/* nsom : nombre de sommets.
   Retourne un graphe aleatoire a 'nsom' sommets et 'narc' arcs.
   Le nombre d'arcs doit etre <= nsom (nsom - 1) / 2*/
Graphe GrapheAleatoire(int nsom);


/* nsom: nombre de sommets
   Retourne un graphe aleatoire a 'nsom' sommets et 'narc' arcs.
   Le nombre d'arcs doit etre <= nsom (nsom - 1) / 2*/
Graphe GrapheManuel(int nsom);



/***** printGraph.c *****/


/*pListeNoeuds: pointeur vers un noeud de la liste chainee
 * Affiche tous le noeuds de la liste chainee d'un noeud
 */
void PrintListeNoeuds(Noeud* pListeNoeuds);


/*g: un graphe
 * nsom: nombre de sommets du graphe
 * Affiche un graphe
 */

void PrintGraphe(Graphe g,int nsom);


/* f: un fichier
 * pListe: un graphe
 *
 * Ecrit les successeurs d'un noeud passé en paramètre au format du fichier dot
 */

void writeListeNoeuds(FILE* f,Noeud* p);


/*g: un graphe
 * nsom: nombre de sommets du graphe
 * Écrit un graphe au format du fichier dot
 */

void writeGraphe(Graphe g,int nsom,char* fileName);



/* fileName: un chemin de la forme "results/myFile.dot"
 * nsom: nombre de sommets du graphe
 * Lit un graphe au format du fichier .dot et le stocke dans une structure
 */

Graphe readGraphe(char* fileName,int nsom);


/* path: pointeur vers le premier noeud du plus court chemin trouvé par Dijikstra
 * fileName: nom du fichier dans lequel reécrire ce chemin
 *
 * Reécrit un chemin dans un fichier .dot
 */

void writePathOnFile(Noeud* path,char* fileName);




/*** courtChemin.c ***/



/*
 * nsom: nombre de sommets du graphe
 * depart: numero du depot de départ
 * arrivee: numero du depot d'arrivée;
 * Trouve le plus court chemin entre un depôt de départ et un depôt d'arrivée
 */

Noeud* Dijkstra(Graphe g,int nsom,int depart, int arrivee);


/*
* nsom: nombre de sommets du graphe
* depart: numero du depot de départ
* arrivee: numero du depot d'arrivée;
* qteMarchandise: quantite de marchandise a transporter du depot 
* Si possible, transporte une quantite de marchandises entre un depot de depart et un depot d'arrivee
* C'est possible lorsqu'il reste assez de marchandises en stock dans le depot de depart
*/
void transport(Graphe g, int nsom, int depart, int arrivee, int qteMarchandises, char* fileName); 

