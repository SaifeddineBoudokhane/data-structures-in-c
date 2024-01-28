#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//Fonction et procedure supplementaire
	//fonction qui renvoie 1 si la chaîne est purement un entier
int is_digit(const char* str){
	int i;
    if (str == NULL)
    {
    	return 0;
    }
    for ( i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }

    return 1;
}
	//une fonction qui renvoie votre choix entre deux entiers
int selection(int j,int i){
	char select[100];int select_d;
	while(1){
			printf("->");scanf("%s",select);
			if(is_digit(select)){
				select_d=atoi(select);
				if(select_d>=j && select_d<=i){
					break;
				}
				else{
				printf("Entre invalide\n");
				}
			}
			else{
				printf("Entre invalide\n");
			}
		}
	return select_d;
}
//structure pour liste SC
typedef struct cellule_sc{
	char nom[51];
	float prix;
	struct cellule_sc *suiv;
}cellule_sc;
typedef struct{
	cellule_sc *debut;
}list_sc;
//structure pour liste DC
typedef struct cellule_dc{
	char nom[51];
	float prix;
	struct cellule_dc *suiv;
	struct cellule_dc *prec;
}cellule_dc;
typedef struct{
	cellule_dc *debut;
	cellule_dc *fin;
}list_dc;
//structure pour file
typedef struct cellule_file{
	char nom[51];
	float prix;
	struct cellule_file *suiv;
	struct cellule_file *prec;
}cellule_file;
typedef struct{
	cellule_file *debut;
	cellule_file *fin;
}list_file;
//structure pour pile
typedef struct cellule_pile{
	char nom[51];
	float prix;
	struct cellule_pile *suiv;
}cellule_pile;
typedef struct{
	cellule_pile *debut;
}list_pile;

//Liste SC
	//affichage des produit
void aff_sc(list_sc l){
	cellule_sc *p;int i=1;
	if (l.debut==NULL){
		printf("Pas de produits !\n");
	}
	else{
		p=l.debut;
		while(p!=NULL){
			printf("%d. %s\t\t%.3fdt\n",i,p->nom,p->prix);
			p=p->suiv;
			i++;
		}
	}
}
	//ajout liste sc
void ajout_sc(list_sc *l){
	cellule_sc *p,*q;
	q=(cellule_sc*)malloc(sizeof(cellule_sc));
	printf("Nom du produit :\n");
	scanf("%s",&(q->nom));
	printf("Prix du produit :\n");
	scanf("%f",&(q->prix));
	q->suiv=NULL;
	if (l->debut==NULL){
		l->debut=q;
	}
	else{
		p=l->debut;
		while(p->suiv!=NULL){
			p=p->suiv;
		}
		p->suiv=q;
	}
	printf("produit ajoute avec succes!\n");
}
	//suppression d'un produit
void suppsc(list_sc *l,int n){
	cellule_sc *p,*pre;int i;
	if(l->debut==NULL){
		printf("list est vide\n");
	}
	else{
		p=l->debut;
		for(i=1;i<n;i++){
			pre=p;
			p=p->suiv;
			if(p==NULL){
				break;
			}
		}
		if(p==NULL){
			printf("Produit n'existe pas!\n");
		}
		else{
			if(l->debut==p){
				l->debut=p->suiv;
				free(p);
			}
			else{
				pre->suiv=p->suiv;
				free(p);
			}
			printf("produit supprime avec succes!\n");
		}
	}
}
	//menu liste SC
int listsc(list_sc *lsc){
	int n,choix,repeate=1;
	while(repeate!=0){
		printf("========= Liste SC =========\n");
		printf("1-Affichage des produits\n");
		printf("2-Ajout d'un produit\n");
		printf("3-Suppression d'un produit\n");
		printf("4-Retour au menu\n");
		printf("5-Quitter\n");
		printf("============================\n");
		choix=selection(1,5);
		switch(choix){
			case 1:
				aff_sc(*lsc);
				break;
			case 2:
				ajout_sc(lsc);
				break;
			case 3:
				printf("Numero du produit :\n");n=selection(1,99999);
				suppsc(lsc,n);
				break;
			case 4:
				repeate=0;
				return 1;
				break;
			case 5:
				repeate=0;
				return 0;
				break;
		}
	}
}
//Liste DC
	//affichage des produit
void aff_dc(list_dc l){
	cellule_dc *p;int i=1;
	if (l.debut==NULL){
		printf("Pas de produits !\n");
	}
	else{
		p=l.debut;
		while(p!=NULL){
			printf("%d. %s\t\t%.3fdt\n",i,p->nom,p->prix);
			p=p->suiv;
			i++;
		}
	}
}
	//ajout d'un produit
void ajout_dc(list_dc *l){
	cellule_dc *q;
	q=(cellule_dc*)malloc(sizeof(cellule_dc));
	printf("Nom du produit :\n");
	scanf("%s",&(q->nom));
	printf("Prix du produit :\n");
	scanf("%f",&(q->prix));
	q->suiv=NULL;
	q->prec=l->fin;
	if (l->debut==NULL){
		l->debut=q;
		l->fin=q;
	}
	else{
		(l->fin)->suiv=q;
		l->fin=q;
	}
	printf("produit ajoute avec succes!\n");
}
	//suppression d'un produit
void suppdc(list_dc *l,int n){
	cellule_dc *p;int i;
	if(l->debut==NULL){
		printf("list est vide\n");
	}
	else{
		p=l->debut;
		for(i=1;i<n;i++){
			p=p->suiv;
			if(p==NULL){
				break;
			}
		}
		if(p==NULL){
			printf("Produit n'existe pas!\n");
		}
		else{
			if(p==l->debut){
				l->debut=p->suiv;
				if(l->fin==p){
					l->fin=NULL;
				}
				else{
					(p->suiv)->prec=NULL;
				}
				free(p);
			}
			else{
				if(l->fin==p){
					l->fin=p->prec;
					(p->prec)->suiv=NULL;
					free(p);
				}
				else{
					(p->prec)->suiv=p->suiv;
					(p->suiv)->prec=p->prec;
					free(p);
				}
					
			}
			printf("produit supprime avec succes!\n");
		}
	}
}
	//menu Dc
int listdc(list_dc *ldc){
	int n,choix,repeate=1;
	while(repeate!=0){
		printf("========= Liste DC =========\n");
		printf("1-Affichage des produits\n");
		printf("2-Ajout d'un produit\n");
		printf("3-Suppression d'un produit\n");
		printf("4-Retour au menu\n");
		printf("5-Quitter\n");
		printf("============================\n");
		choix=selection(1,5);
		switch(choix){
			case 1:
				aff_dc(*ldc);
				break;
			case 2:
				ajout_dc(ldc);
				break;
			case 3:
				printf("Numero du produit :\n");n=selection(1,99999);
				suppdc(ldc,n);
				break;
			case 4:
				repeate=0;
				return 1;
				break;
			case 5:
				repeate=0;
				return 0;
				break;
		}
	}
}
//Pile
	//affichage des produit
void aff_pile(list_pile l){
	cellule_pile *p;int i=1;
	if (l.debut==NULL){
		printf("Pas de produits !\n");
	}
	else{
		p=l.debut;
		while(p!=NULL){
			printf("%d. %s\t\t%.3fdt\n",i,p->nom,p->prix);
			p=p->suiv;
			i++;
		}
	}
}
	//ajout d'un produit
void empile(list_pile *l){
	cellule_pile *p;
	p=(cellule_pile*)malloc(sizeof(cellule_pile));
	printf("Nom du produit :\n");
	scanf("%s",&(p->nom));
	printf("Prix du produit :\n");
	scanf("%f",&(p->prix));
	p->suiv=l->debut;
	l->debut=p;
	printf("produit ajoute avec succes!\n");
}
	//suppression d'un produit
void depiler(list_pile *l){
	cellule_pile *p;
	if(l->debut==NULL){
		printf("Pile est vide\n");
	}
	else{
		p=l->debut;
		l->debut=p->suiv;
		free(p);
		printf("produit supprime avec succes!\n");
	}
}
	//menu pile
int pile(list_pile *lpile){
	int choix,repeate=1;
	while(repeate!=0){
		printf("=========== Pile ===========\n");
		printf("1-Affichage des produits\n");
		printf("2-Ajout d'un produit\n");
		printf("3-Suppression d'un produit\n");
		printf("4-Retour au menu\n");
		printf("5-Quitter\n");
		printf("============================\n");
		choix=selection(1,5);
		switch(choix){
			case 1:
				aff_pile(*lpile);
				break;
			case 2:
				empile(lpile);
				break;
			case 3:
				depiler(lpile);
				break;
			case 4:
				repeate=0;
				return 1;
				break;
			case 5:
				repeate=0;
				return 0;
				break;
		}
	}
}
//File
	//affichage des produit
void aff_file(list_file l){
	cellule_file *p;int i=1;
	if (l.debut==NULL){
		printf("Pas de produits !\n");
	}
	else{
		p=l.debut;
		while(p!=NULL){
			printf("%d. %s\t\t%.3fdt\n",i,p->nom,p->prix);
			p=p->suiv;
			i++;
		}
	}
}
	//ajout d'un produit
void enfiler(list_file *l){
	cellule_file *q;
	q=(cellule_file*)malloc(sizeof(cellule_file));
	printf("Nom du produit :\n");
	scanf("%s",&(q->nom));
	printf("Prix du produit :\n");
	scanf("%f",&(q->prix));
	q->suiv=NULL;
	q->prec=l->fin;
	if (l->debut==NULL){
		l->debut=q;
		l->fin=q;
	}
	else{
		(l->fin)->suiv=q;
		l->fin=q;
	}
	printf("produit ajoute avec succes!\n");
}
	//suppression d'un produit
void defiler(list_file *l){
	cellule_file *p;
	if(l->debut==NULL){
		printf("file est vide\n");
	}
	else{
		p=l->debut;
		l->debut=p->suiv;
		if(l->fin==p){
			l->fin=NULL;
		}
		else{
			(p->suiv)->prec=NULL;
		}
		free(p);
		printf("produit supprime avec succes!\n");
	}
}
	//menu file
int file(list_file *lfile){
	int choix,repeate=1;
	while(repeate!=0){
		printf("=========== File ===========\n");
		printf("1-Affichage des produits\n");
		printf("2-Ajout d'un produit\n");
		printf("3-Suppression d'un produit\n");
		printf("4-Retour au menu\n");
		printf("5-Quitter\n");
		printf("============================\n");
		choix=selection(1,5);
		switch(choix){
			case 1:
				aff_file(*lfile);
				break;
			case 2:
				enfiler(lfile);
				break;
			case 3:
				defiler(lfile);
				break;
			case 4:
				repeate=0;
				return 1;
				break;
			case 5:
				repeate=0;
				return 0;
				break;
		}
	}
}
int main(){
	int choix,repeate=1;
	list_sc lsc;list_dc ldc;list_file lfile;list_pile lpile;
	lsc.debut=NULL;
	ldc.debut=NULL;ldc.fin=NULL;
	lfile.debut=NULL;lfile.fin=NULL;
	lpile.debut=NULL;
	while (repeate!=0){
		printf("=========== Menu ===========\n");
		printf("1-Liste SC\n");
		printf("2-Liste DC\n");
		printf("3-Pile\n");
		printf("4-File\n");
		printf("5-Quitter\n");
		printf("============================\n");
		choix=selection(1,5);
		switch(choix){
			case 1:
				repeate=listsc(&lsc);
				break;
			case 2:
				repeate=listdc(&ldc);
				break;
			case 3:
				repeate=pile(&lpile);
				break;
			case 4:
				repeate=file(&lfile);
				break;
			case 5:
				repeate=0;
				break;
		}
	}
	return 0;
}
