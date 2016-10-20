/*
 * plusCourtChemin.c
 *
 *  Created on: May 8, 2016
 *     Authors: Valentina Zelaya & Theo Hermann
 */

#include "graphes.h"
#include <stdlib.h>
#include <stdio.h>

void PrintListeNoeuds(Noeud* p){
	p=p->suiv;
	for (; p != NULL; p = p->suiv){
		printf("..le %s, ",p->name);

		printf("à une distance de %d ",p->poids);

		puts(" ");
	}
}


void PrintGraphe(Graphe g,int nsom){
	int i;
	for (i=1;i<=nsom;i++){
		printf("Le noeud %d a %d successeurs... \n", g[i]->num, nbSuccesseurs(g[i]));
		PrintListeNoeuds(g[i]);
	}
	printf("\n");
}


void writeListeNoeuds(FILE* f,Noeud* p){
	int numNoeud=p->num;
	p=p->suiv;
	for (; p != NULL; p = p->suiv){
		if (!(p->num>numNoeud)){
			fprintf(f,"A%d -- ",numNoeud);
			fprintf(f,"A%d [label=\"%d\",arrowsize=%d];\n",p->num,p->poids,p->poids/(MAX_POIDS-MIN_POIDS));
		}
	}

}

void writeGraphe(Graphe g,int nsom,char* fileName){
	FILE* file=NULL;
	int i,k,j;
	char fileChemin[2*MAX_NAME];
	strcpy(fileChemin,"results/");

	strcat(fileChemin,fileName);
	file=fopen(fileChemin,"w");
	puts(".......writeGraphe.......");

	fprintf(file,"graph G{ \n");
	fprintf(file,"node[shape=Mrecord] \n");
	fprintf(file,"rankdir=LR \n");


	for(i=1;i<=nsom;i++){
		fprintf(file,"A%d [label=\"<f0>(%d) %s | <f1> stock: %d\"];\n",i,g[i]->num,g[i]->name,g[i]->stock);
	}

	writeListeNoeuds(file,g[1]);

	for(k=2;k<=nsom;k++){
		writeListeNoeuds(file,g[k]);
	}

	fprintf(file,"}");
	fclose(file);

	char* picName;
	char* command2;
	char* command1;

	command1=malloc(3*MAX_NAME*sizeof(char));
	command2=malloc(3*MAX_NAME*sizeof(char));
	picName=malloc(2*MAX_NAME*sizeof(char));

	strncpy(picName,fileName,(strlen(fileName)-4));
	picName[strlen(fileName)-4]='\0';
	strcat(picName,".jpg");
	//printf("%s \n",picName);
	strcpy(command1,"cd results && dot -Tjpg -o ");
	strcat(command1,picName);
	strcat(command1," ");
	strcat(command1,fileName);
	//printf("%s \n",command1);

	strcpy(command2,"cd results && eog ");
	strcat(command2,picName);

	//printf("%s \n",command2);
	system(command1);


	system(command2);

	free(picName);
	free(command1);
	free(command2);
}


void writePathOnFile(Noeud* path,char* fileName){
	FILE* file=NULL;
	int i,k,j;
	char fileChemin[2*MAX_NAME];
	strcpy(fileChemin,"results/");

	strcat(fileChemin,fileName);
	file=fopen(fileChemin,"r+");

	puts(".......writePathOnFile.......");

	char* command1;
	char* command2;
	char* command3;

	command1=malloc(3*MAX_NAME*sizeof(char));
	command2=malloc(3*MAX_NAME*sizeof(char));
	command3=malloc(3*MAX_NAME*sizeof(char));

	strcpy(command1,"");
	strcpy(command2,"");
	strcpy(command3,"");


	Noeud* p=path;

	//command1 : sed -i 's/^A3\ \[/A3\ \[color=purple,/1' d3.dot

	int taillePath=nbSuccesseurs(path)+1;
	for (i=0;i<taillePath;i++){
		strcpy(command1,"cd results && sed -i \'s/^A");
		char str1[3];
		sprintf(str1,"%d",p->num);
		strcat(command1,str1);
		strcat(command1,"\\ \\\[/A");
		strcat(command1,str1);
		strcat(command1,"\\ \\\[color=thistle1,style=filled,penwidth=3, /\' ");
		strcat(command1,fileName);
		system(command1);
		p=p->suiv;
	}
	p=path;
	Noeud* pSuiv;

	for(k=0;k<(taillePath-1);k++){

		//sed -i 's/^A7\ \-\-\ A1\ \[/A7\ \-\-\ A1\ \[color=purple,\ /' test3.dot
		strcpy(command2,"cd results && sed -i \'s/^A");
		char str1[3];
		sprintf(str1,"%d",p->num);
		strcat(command2,str1);
		strcat(command2,"\\ \\\-\\\-\\ A");
		char str2[3];
		pSuiv=p->suiv;
		sprintf(str2,"%d",pSuiv->num);
		strcat(command2,str2);
		strcat(command2,"\\ \\\[/A");

		strcat(command2,str1);
		strcat(command2,"\\ \\-\\-\\ A");
		sprintf(str2,"%d",pSuiv->num);
		strcat(command2,str2);

		strcat(command2,"\\ \\\[color=purple,penwidth=2,\\ /\' ");
		strcat(command2,fileName);
		system(command2);


		//sed -i 's/^A1\ \-\-\ A7\ \[/A1\ \-\-\ A7\ \[color=purple,\ /' test3.dot
		strcpy(command3,"cd results && sed -i \'s/^A");
		strcat(command3,str2);
		strcat(command3,"\\ \\\-\\\-\\ A");
		strcat(command3,str1);
		strcat(command3,"\\ \\\[/A");

		strcat(command3,str2);
		strcat(command3,"\\ \\-\\-\\ A");
		strcat(command3,str1);

		strcat(command3,"\\ \\\[color=purple,penwidth=2,\\ /\' ");
		strcat(command3,fileName);
		system(command3);


		p=p->suiv;

	}
	char picNameSol[3*MAX_NAME];
	char picName[3*MAX_NAME];

	strcpy(picNameSol,"");
	strncpy(picName,fileName,(strlen(fileName)-4));
	picName[strlen(fileName)-3]='\0';
	strcat(picName,"solution");
	strcat(picName,".jpg");
	strcat(picNameSol,picName);

	char cm[3*MAX_NAME];
	char cm2[3*MAX_NAME];
	strcpy(cm2,"cd results && dot -Tjpg -o ");
	strcat(cm2,picNameSol);
	strcat(cm2," ");
	strcat(cm2,fileName);
	//puts(cm2);
	system(cm2);

	strcpy(cm,"cd results && eog ");
	strcat(cm,picNameSol);
	//strcat(cm," &");
	//puts(cm);
	system(cm);

	free(command1);
	free(command2);
	free(command3);
}

//-----Fonctions auxiliaires de readGraphe(..) -----/


//Trouve le nom du noeud dans la ligne
char* findLabel(char* ligne){
	int i = 0;
	while (ligne[i] != 'l' || ligne[i+1] != 'a' || ligne[i+2] != 'b' || ligne[i+3] != 'e' || ligne[i+4] != 'l' || ligne[i+5] != '=' )
	{
		if(ligne[i+5] == '\0') return "LABEL NON TROUVE";
		i++;
	}
	int k=i; 
	while (ligne[k]!=')'){
		k++;
	}
	k=k+2;
	char* label;
	label = malloc(MAX_NAME*sizeof(char));
	int j = 0;
	while(ligne[k] != ' ')
	{	
		label[j] = ligne[k];
		k++; j++;
	}
	label[j] = '\0';
	return label;
}


//Trouve le stock d'un noeud sur la ligne
int findStock(char* ligne){
	int i = 0;
	while (ligne[i] != 's' || ligne[i+1] != 't' || ligne[i+2] != 'o' || ligne[i+3] != 'c' || ligne[i+4] != 'k' || ligne[i+5]!=':')
	{
		if(ligne[i] == '\0') return -1;
		i++;
	}
	i+=7;//i est maintenant au debut du stock
	int stock;
	int j = i;
	char str[5];
	
	while(ligne[j] != '\"'){
		str[j-i]=ligne[j];
		j++; 
	}
	str[4]='\0';	
	stock = atoi(str);
	printf("res findStock: %d \n",stock);
	return stock;
}

//Trouve le poids d'un noeud sur la ligne
int findPoids(char* ligne){
	int i = 0;
	while (ligne[i] != 'l' || ligne[i+1] != 'a' || ligne[i+2] != 'b' || ligne[i+3] != 'e' || ligne[i+4] != 'l' )
	{
		if(ligne[i] == '\0') return -1;
		i++;
	}
	i+=7;//i est maintenant au debut du poids
	int poids;
	int j = i;
	char str[5];
	
	while(ligne[j] != '\"'){
		str[j-i]=ligne[j];
		j++; 
	}
	str[4]='\0';	
	poids = atoi(str);

	return poids;
}

Graphe readGraphe(char* fileName,int nsom){
	Graphe g;
	FILE *dotFile;
	dotFile = fopen(fileName,"r");
	if (dotFile == NULL)
	{
		fprintf(stderr,"ERREUR : Impossible d'ouvrir le fichier\n");
	}else
	{
		puts("Ouverture du fichier réussie");

		
		g = InitGraphe(nsom);

		//Lecture du fichier, ligne par ligne (k nb de sommets trouvés, i_ligne l'indice dans la ligne en cours)
		char ligne[LG_MAX_LIGNE_FICHIER_DOT];
		int i_ligne;
		
		puts("AvantBoucle ");
		
		while(!feof(dotFile)  && (ligne[0]!= '}'))
		{	
			//puts("Lecture de la ligne ");
			i_ligne = 0;
			ligne[i_ligne] = (char)fgetc(dotFile);
			//printf("%c\n",ligne[i_ligne]);
			
			while((ligne[i_ligne] != '\n') && (ligne[i_ligne]!= '}')&& (ligne[i_ligne]!= 'EOF'))
			{
				i_ligne++;
				ligne[i_ligne] = (char)fgetc(dotFile);
			}
			i_ligne++;
			ligne[i_ligne] = '\0';
			//printf("%s\n",ligne);
			if(ligne[0]=='A' && (ligne[3] == '[' || ligne[4] == '['))
			{
				int k = 1;
				int num;
				char chiffres[MAX_CHIFFRES];
				
				while (ligne[k]!='['){
					chiffres[k-1]=ligne[k];
					k++;
				}
				chiffres[k]='\0';
				
				num = atoi(chiffres);
				
				char* label=findLabel(ligne);
				
				strcpy(g[num]->name,label);
				printf("g[num]->name: %s \n",g[num]->name);							
				g[num]->stock = findStock(ligne);
				printf("g[num] -> stock: %d \n",g[num]->stock);
				
				
			}else if(ligne[0]=='A' && (ligne[3] == '-' || ligne[4] == '-'))
			{
				//2 entiers composés de 1 ou 2 chiffres => 4 cas (mal écris...)
				int num1;
				int num2;
				char chiffres1[MAX_CHIFFRES];
				char chiffres2[MAX_CHIFFRES];
				if(ligne[3] == '-')
				{
					chiffres1[0] = ligne[1];
					
					if(ligne[9] == '[')
					{
						chiffres2[0] = ligne[7];
						chiffres2[1] = '\0';
					}else
					{
						chiffres2[0] = ligne[7];
						chiffres2[1] = ligne[8];
					}
					

				}else
				{
					chiffres1[0] = ligne[1];
					chiffres1[1] = ligne[2];
					if(ligne[10] == '[')
					{
						chiffres2[0] = ligne[8];
						chiffres2[1] = '\0';
					}else
					{
						chiffres2[0] = ligne[8];
						chiffres2[1] = ligne[9];
					}
				}
				num1 = atoi(chiffres1);
				num2 = atoi(chiffres2);

				int poids = findPoids(ligne);
				printf("poids %d\n",poids);
				//g[i]=AjouteNoeudQueue(g[i],newNoeud(randNum,name,randPoids,NULL,stockSucc));
				//g[num1]=AjouteNoeudQueue(g[num1],newNoeud(num2,g[num2]->name,poids,NULL,g[num2]->stock));
				printf("num1 %d, num2 %d \n",num1,num2);
				char* name2 = g[num2]->name;
				int stock2 = g[num2]->stock;
				char* name1 = g[num1]->name;
				int stock1 = g[num1]->stock;
				printf("stock1 %d, stock2 %d \n",stock1,stock2);
				g[num1]=AjouteNoeudQueue(g[num1],newNoeud(num2,name2,poids,NULL,stock2));
				g[num2]=AjouteNoeudQueue(g[num2],newNoeud(num1,name1,poids,NULL,stock1));


			}
		}
		puts("Fin de la lecture du graphe !");
		fclose(dotFile);
	}
	return g;
}







