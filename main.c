/*
 * main.c
 *
 *  Created on: Apr 11, 2016
 *      Author: vz
 */

#include <stdio.h>
#include "graphes.h"

#define sep1 "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define sep2 "|||                                                            |||"

int main(){

	puts("  ");
	puts(sep1);
	puts(sep2);
	printf("||| Visualisation d'un réseau de distribution de marchandises  |||\n");
	puts(sep2);
	puts(sep1);
	puts("  ");

	puts(" Bonjour !");
	puts(" Sélectionnez une fonctionnalité: ");

	int choix=0;
	do{

		puts("--- Réseau Aléatoire --------------> Tappez 1 ");
		puts("--- Saisie manuelle ---------------> Tappez 2 ");
		puts("--- Lecture d'un fichier-----------> Tappez 3 ");
		printf("%%  ");

		//printf("--- A partir d´un fichier texte  ----> Tappez 3 ");
		//printf("--- A partir d´un fichier .dot  ----> Tappez 4 ");

		scanf("%d",&choix);
		getchar();

	}while(choix<=0||choix>3);

	int n;
	int depart;
	int arrivee;
	Graphe mainGraphe;
	char fileName[2*MAX_NAME];
	char fileNameTransport[2*MAX_NAME] = "transport";
	Noeud* path;
	int qteMarchandises;

	switch(choix){
		case 1: puts("");
			puts("Vous avez choisi le mode aléatoire !");
			puts("Veuillez saisir un nombre de sommets: ");
			printf("%%  ");
			scanf("%d",&n);
			srand(time(NULL));
			mainGraphe=GrapheAleatoire(n);
			break;

		case 2: puts("");
			puts("Vous avez choisi la saisie manuelle !");
			puts("Veuillez saisir un nombre de sommets: ");
			printf("%%  ");
			scanf("%d",&n);
			mainGraphe=GrapheManuel(n);
			break;
		case 3: puts("Vous avez choisi la lecture d'un fichier !");
			char fileToRead[MAX_NAME];
			puts("Veuillez saisir l'emplacement du fichier (au format results/myFile.dot): ");
			printf("%%  ");
			scanf("%s",&fileToRead);
			puts("Veuillez saisir le nombre de sommets du graphe ");
			printf("%%  ");
			scanf("%d",&n);
			mainGraphe = readGraphe(fileToRead,n);
			break;
	}
	PrintGraphe(mainGraphe,n);
	/*puts("Voulez-vous enregistrer ce graphe dans un fichier.dot ? [O/N]");
	//printf("%%  ");
	scanf("%c",&enregis);
	getchar();*/
	puts("\nVeuillez saisir le nom du fichier à créer (AVEC l'extension .dot) :");
	printf("%%");
	scanf("%s",fileName);
	writeGraphe(mainGraphe,n,fileName);
	//writeGraphe(mainGraphe,n);
	//puts("test ca continue....");
	puts("");
	puts("----- Recherche du plus court chemin ------");

	do{
		puts("");
		puts("\nVeuillez saisir le numero du depot de départ: ");
		printf("%%  ");
		scanf("%d",&depart);
		getchar();
		puts("");
		puts("Veuillez saisir le numero du depot d'arrivée: ");
		printf("%%  ");
		scanf("%d",&arrivee);
		getchar();

	}while(depart<=0||depart>n||arrivee<=0||arrivee>n);

	
	path=Dijkstra(mainGraphe,n,depart,arrivee);
	writePathOnFile(path,fileName);

	//Transport de la marchandise
	printf("\nVeuillez saisir la quantité de marchandises que vous souhaitez transporter du depot %d au depot %d: \n",depart,arrivee);
	printf("%%  ");
	scanf("%d",&qteMarchandises);
	strcat(fileNameTransport, fileName);
	transport(mainGraphe,n,depart,arrivee,qteMarchandises, fileNameTransport);
	TermineGraphe(mainGraphe,n);
	
	puts("-------------------- Exécution terminée -------------------");
	puts("-------------------- A bientôt ! --------------------------");

	return 0;
}
