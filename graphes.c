/*
 * graphes.c
 *
 *  Created on: Apr 16, 2016
 *     Authors: Valentina Zelaya & Theo Hermann
 */

#include <stdlib.h>
#include <stdio.h>

#include "graphes.h"

Noeud* newNoeud(int aNum,char* aName,int aPoids,Noeud* aSuiv,int aStock){
	Noeud* unN=NULL;
	unN=(Noeud*)malloc(sizeof(Noeud));
	unN->num=aNum;
	unN->poids=aPoids;

	strcpy(unN->name,aName);
	unN->suiv=aSuiv;
	unN->stock=aStock;

	return unN;
}

Noeud* copyNoeud(Noeud* unN){
	Noeud* copie=NULL;
	copie=(Noeud*)malloc(sizeof(Noeud));
	copie->num=unN->num;
	copie->poids=unN->poids;
	strcpy(copie->name,unN->name);
	copie->stock=unN->stock;
	copie->suiv=NULL;
	return copie;
}

Graphe InitGraphe(int nsom){
	Graphe g;
	int i;
	g=(Graphe)malloc(2*nsom*sizeof(Noeud*));  //Le 2*nsom a été rajouté pour allouer assez de mémoire

	if (g == NULL)
	 {fprintf(stderr, "InitGraphe : malloc failed\n");
	   exit(0);
	   }
	for (i=1;i<=nsom;i++){
		g[i]=(Noeud*)malloc(nsom*nsom*sizeof(Noeud));
		if (g[i] == NULL){
			fprintf(stderr, "InitGraphe : malloc failed \n");
			exit(1);
		}
		g[i]->num=i;

		char name[MAX_NAME];
		name[0]='d';
		name[1]='e';
		name[2]='p';
		name[3]='o';
		name[4]='t';
		name[5]='_';
		char str[3];
		sprintf(str,"%d",i);
		name[6]=str[0];
		name[7]=str[1];
		name[8]=str[2];
		name[9]='\0';

		strcpy(g[i]->name,name);
		g[i]->stock=(-1);

	}

	return g;
}

void TermineGraphe(Graphe g,int nsom){
	int i;
	for(i=1;i<=nsom;i++){
		free(g[i]);
	}
	free(g);
}


Noeud* AjouteNoeudQueue(Noeud * listeN,Noeud* newN){
	newN->suiv=NULL;

	if(listeN==NULL){
		listeN=newN;
	}
	else{
		Noeud* t=listeN;
		while (t->suiv!=NULL){
			t=t->suiv;
		}
		t->suiv=newN;
	}

	return listeN;
}

int EstDansListe(Noeud* pList, int num){
	int bool=false;
	pList=pList->suiv;
	for(;pList!=NULL;pList=(pList->suiv)){
		if (pList->num==num)
			bool=true;
	}
	return bool;
}


int EstSuccesseur(Graphe g, int i, int s)
{
  return EstDansListe(g[i], s);
}

Noeud* getSucceseur(Graphe g,Noeud* pNi, int j){
	Noeud* succ;
	Noeud*p=pNi;

	succ=(Noeud*)malloc(sizeof(Noeud*));
	p=p->suiv;
	for (; p != NULL; p = p->suiv){
		if(p->num==j){
			succ=p;
		}
	}
	return succ;
}

int poidsDansListe(Noeud* pList,int num){
	int p;
	for(;pList!=NULL;pList=(pList->suiv)){
			if (pList->num==num)
				p=pList->poids;
	}
	return p;
}

int getPoids(Graphe g, int i,int j){
	return poidsDansListe(g[i],j);
}


int nbSuccesseurs(Noeud *p){
	int n=0;

	while(p->suiv){
		n++;
		p=p->suiv;
	}
	return n;
}


/***Renvoie un nb aléatoire de [a-b]  (m inclus)***/
int randInt(int a,int b){
  if(a<b)
    return rand()%(b-a)+a+1;
  else if (b==0)
    return 0;
  else if(a==b)
    return 1;
  else
	return 0;
}


Graphe GrapheAleatoire(int nsom){
	Graphe g;

	int i,k;
	int nbSucc;
	int randPoids;
	int randNum;
	int nmaxarc=(nsom-2)/2;
	char name[MAX_NAME];
	


	g=InitGraphe(nsom);

	//Graphe* pG;

	for(i=1;i<=nsom;i++){
		int aStock;
		//Chaque noeud a un nb de successeurs compris entre 0 et nsom(nsom-1)/2
		if ((nsom>1)&&(nsom<=5))
			nbSucc=randInt(1,1);
		//printf("\n %d successeurs pour %d; ",nbSucc,i);
		else if (nsom>=12)
			nbSucc=2;
		else
			nbSucc=randInt(1,nmaxarc-1);

		aStock=randInt(MIN_STOCK,MAX_STOCK);
		g[i]->stock=aStock;

		for(k=0;k<nbSucc;k++){
			int stockSucc;
			do{
				randNum=randInt(1,nsom);
				//printf(".%d. ",randNum);
			}while((i==randNum)||(EstSuccesseur(g,i,randNum))||(EstSuccesseur(g,randNum,i)));

			//On tire au sort un poids...
			randPoids=randInt(MIN_POIDS,MAX_POIDS);
			//Et un nb de marchandises stockees
			stockSucc=randInt(MIN_STOCK,MAX_STOCK);


			//... et on créé le noeud correspondant ... on l'ajoute

			name[0]='d';
			name[1]='e';
			name[2]='p';
			name[3]='o';
			name[4]='t';
			name[5]='_';
			char str[3];
			sprintf(str,"%d",randNum);
			name[6]=str[0];
			name[7]=str[1];
			name[8]=str[2];
			name[9]='\0';

			//Pour un graphe orienté
			g[i]=AjouteNoeudQueue(g[i],newNoeud(randNum,name,randPoids,NULL,stockSucc));


			//Lignes de code à ajouter si l'on veut avoir un graphe non-orienté
			//Pas utile pour la reprsentation avec Graphviz mais important pour la recherche du plus court chemin ?

			char str2[3];
			sprintf(str2,"%d",i);
			name[6]=str2[0];
			name[7]=str2[1];
			name[8]=str2[2];

			g[randNum]=AjouteNoeudQueue(g[randNum],newNoeud(i,name,randPoids,NULL,g[i]->stock));

		}
	}

	return g;
}



Graphe GrapheManuel(int nsom){
	Graphe g;
	int i,j,k,l;
	char** names=malloc(2*nsom*sizeof(char*));
	

	for (l=1;l<=nsom;l++){
		names[l]=(char*)malloc(2*MAX_NAME*sizeof(char));
	}

	g=InitGraphe(nsom);

	//Pour chaque sommet...
	for (i=1;i<=nsom;i++){
		int nbSucc;
		int aStock;
		//Si son nom est inconnu, le demander...
		if (strcmp(names[i],"")==0){
			printf("Veuillez saisir le nom du depot %d: \n",i);
			printf("%% ");
			scanf("%s",names[i]);
		}
		 //On enregistre sa qte de marchandises
		if (g[i]->stock==(-1)){
			printf("Veuillez saisir un stock pour le depot %d: \n",i);
			printf("%% ");
			scanf("%d",&aStock);
			g[i]->stock=aStock;
		}
		
			

		//On enregistre son nombre de successeurs...
		do{
			printf("Veuillez saisir le nombre de liens restants pour le noeud %d \n",i);
			printf("%% ");
			scanf("%d",&nbSucc);
			if (nbSucc>=nsom){
				printf("Un noeud ne peut pas avoir plus de %d successeurs pour ce graphe ! \n",nsom-1);
			}
		}while(nbSucc>=nsom);

		//... et pour chaque successeur...
		for (j=0;j<nbSucc;j++){
			int stockSucc;
			int aPoids;
			int num;

			char *nameSucc = (char*)malloc(MAX_NAME*sizeof(char));


			do{
				printf("Veuillez saisir le numero du %deme noeud successeur du noeud %d \n",j+1,i);
				printf("%% ");
				scanf("%d",&num);

				if(EstSuccesseur(g,i,num))
					printf("Ce noeud est déjà un successeur du noeud %d \n",i);

				if(i==num)
					puts("Un noeud ne peut pas avoir lui-même comme successeur !");

				if (num>nsom)
					printf("Il y seulement %d sommets dans ce graphe !\n",nsom);

			}while(EstSuccesseur(g,i,num)||(i==num)||(num>nsom));


			if (strcmp(names[num],"")!=0){
				printf("Le nom du depot %d a déjà été saisi précedemment: %s \n",num,names[num]);
				strcpy(nameSucc,names[num]);
				stockSucc=g[num]->stock;
			}
			else{
				printf("Le nom du %deme successeur n'est pas connu... \n",j+1);
				printf("Veuillez saisir le nom du %deme successeur \n",j+1);
				printf("%% ");
				scanf("%s",nameSucc);
				strcpy(names[num],nameSucc);
				printf("Veuillez saisir le stock du %deme successeur \n",j+1);
				printf("%% ");
				scanf("%d",&stockSucc);
			}

			puts("Quelle est la distance qui sépare ces deux noeuds (poids de l'arc)? ");
			printf("%% ");
			scanf("%d",&aPoids);


			g[i]=AjouteNoeudQueue(g[i],newNoeud(num,nameSucc,aPoids,NULL,stockSucc));


			g[num]=AjouteNoeudQueue(g[num],newNoeud(i,g[i]->name,aPoids,NULL,g[i]->stock));

			//On met à jour les stocks des noeuds concernés
			g[num]->stock=stockSucc;

			free(nameSucc);

		}
		strcpy(g[i]->name,names[i]);

	}
	puts(" ");
	puts("Vous avez fini de construire votre graphe manuellement !");
	free(names);
	return g;
}





