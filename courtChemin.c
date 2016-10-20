/*
 * plusCourtChemin.c
 *
 *  Created on: May 8, 2016
 *     Authors: Valentina Zelaya & Theo Hermann
 */

#include "graphes.h"


// Renvoie le plus grand element du tableau poids
// (servira aux comparaisons pour trouver le poids le plus petit)
int max(int nsom, int* poids){
	int indicePoidsMin=-1;
	int poidsMax=-1;

	int i;
	for (i=1; i<nsom+1; i++)
		if (poids[i]>poidsMax)
			poidsMax=poids[i];

	return poidsMax;
}

// Renvoie l'indice du noeud non parcouru le plus proche
int minNonParcourus(int nsom,int* noeudParcouru,int* poids){
	//printf("-----------------MinNonParcourus----------------\n");

		int indicePoidsMin=-1;
		int poidsMin=max(nsom,poids);

		int i;
		for (i=1; i<nsom+1; i++)
			//------------- Zone de test ----- Affichage des valeurs---------------------

			//printf("i=%d, Noeud Parcouru= %d, Poids=%d\n",i,noeudParcouru[i],poids[i]);

			/*if (noeudParcouru[i]==false)
				printf("np=f at %d\n",i);*/
			/*if ((poids[i]<poidsMin)&&(poids[i]!=-1)&&(noeudParcouru[i]==false))
				printf("p inf et diff -1 et npf at %d\n",i);
			/*if (poids[i]!=-1)
				printf("p diff -1 at %d\n",i);*/

			//----------- fin zone de test---------------------------------

			if ((poids[i]<=poidsMin)&&(poids[i]!=-1)&&(noeudParcouru[i]==false)){
				poidsMin=poids[i];
				indicePoidsMin=i;
				//printf("boucle ! | ");
			}
		//printf("test si minparcours marche: %d\n",indicePoidsMin);
		//printf("-----------------Fin MinNonParcourus----------------\n\n");

		return indicePoidsMin;
	}


//Fonction utilisée lors des tests pour Dijkstra... elle affiche sur la sortie standard les poids des chemins courants
void valeurs(int nsom,int* noeudParcouru,int* poids){
	printf("-----------------Valeurs----------------\n");

		int indicePoidsMin=-1;
		int poidsMin=99;

		int i;
		//printf("false = %d\n",false);
		for (i=1; i<nsom+1; i++)
			printf("i=%d, Noeud Parcouru= %d, Poids=%d\n",i,noeudParcouru[i],poids[i]);

		printf("-----------------Fin Valeurs----------------\n\n");
}

Noeud* Dijkstra(Graphe g,int nsom,int depart, int arrivee){
	
	printf("\n ------------ Recherche du chemin le plus court avec Dijkstra --------------\n");


	int poids[nsom+1];
	int noeudParcouru[nsom+1];
	int antecedents[nsom+1];

	int i;
	for (i=1; i<nsom+1; i++){
		poids[i]=-1;
		noeudParcouru[i]=false;
	}

	poids[depart]=0;

	while (minNonParcourus(nsom,noeudParcouru,poids)!=arrivee){
		int pere=0;
		//valeurs(nsom,noeudParcouru,poids);
		pere=minNonParcourus(nsom,noeudParcouru,poids);
		//printf("pere : %d \n",pere);
		int fils;
		for (fils=1; fils<=nsom; fils++){
			if (fils!=pere && EstDansListe(g[pere], fils)){
				if((noeudParcouru[fils]==false)&&(((poids[pere]+poidsDansListe(g[pere],fils))<poids[fils])||(poids[fils]==-1)))
					{
					int temp=poids[fils];
					poids[fils]=poids[pere]+poidsDansListe(g[pere],fils);
					antecedents[fils]=pere;
					//printf("Update poids de %d, fils de %d (%d => %d)\n",fils,pere, temp, poids[fils]);
					}

				}
			}


		noeudParcouru[pere]=true;
		//printf("%d parcouru\n",pere);

	}

	Noeud* plusCourtChemin=NULL;

	//printf("\n\n\n################################################\n");

	int tailleP=1;
	int ante=arrivee;
	printf("Parcours optimal :\n %d",ante);
	while (ante!=depart){
			tailleP++;
			ante=antecedents[ante];
			printf(" <= %d",ante);
	}
	//On stocke dans un tableau le chemin trouvé...
	i=tailleP;
	int* path[tailleP+1];
	int ante2=arrivee;
	path[i]=ante2;
	while (ante2!=depart){
		i--;
		ante2=antecedents[ante2];
		path[i]=ante2;
	}

	//.... et on le met dans une structure (Noeud* path)
	int k;
	int ind=path[1];
	int indP;
	plusCourtChemin=copyNoeud(g[ind]);
	for (k=2;k<=tailleP;k++){
		indP=path[k-1];
		ind=path[k];
		AjouteNoeudQueue(plusCourtChemin,getSucceseur(g,g[indP],ind));
		
	}
	PrintListeNoeuds(plusCourtChemin);
	//printf("\n################################################\n\n\n");
	printf("Recherche terminée\n");
	return plusCourtChemin;
}




void transport(Graphe g, int nsom, int depart, int arrivee, int qteMarchandises, char* fileName){
	if ((qteMarchandises>=0) && (g[depart]->stock >= qteMarchandises)){
		//maj du graphe
		g[arrivee]->stock = g[arrivee]->stock+qteMarchandises;
		g[depart]->stock = g[depart]->stock-qteMarchandises;
		printf("Transport réussi de %d unites de %s vers %s\n",qteMarchandises, g[depart]->name, g[arrivee]->name );
		
		//on enregistre un nouveau fichier dot
		writeGraphe(g,nsom,fileName);
	}else{
		puts("Transport des marchandises impossible, verifiez qu'il en reste suffisament dans le depot de départ\n");
	}
}
