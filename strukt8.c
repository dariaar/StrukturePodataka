#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _CvorStabla;
typedef struct _CvorStabla *Stablo;
typedef struct _CvorStabla {
	int broj;
	Stablo lijevo;
	Stablo desno;
} CvorStabla;

Stablo StvoriStablo(int);
Stablo Unos(Stablo, int);
int InOrderPrint(Stablo);
int PostOrderPrint(Stablo);
int PreOrderPrint(Stablo);
Stablo IzbrisiCvor(int, Stablo);
Stablo NadiMin(Stablo);
Stablo NadiCvor(int, Stablo);



struct _StogElement;
typedef struct _StogElement *Pozicija;
typedef struct _StogElement{
	Pozicija sljedeci;
	Stablo cvor;
} StogElement;

int Push(Stablo, Pozicija);
int Pop(Pozicija);
Pozicija StvoriStogElement();
Stablo NadiZadnjiNaStogu(Pozicija);
int LevelOrderPrint(Stablo, Pozicija);

int main(){
	char ch = '0';
	int isActive = 1, broj = 0;
	Pozicija stogHead = NULL;
	Stablo korijen = NULL, temp = NULL;

	stogHead = StvoriStogElement();


	while(isActive){
		printf("\nOdaberi operaciju binarnog stabla:\n");
		printf("1 - unos novog elementa u stablo\n");
		printf("2 - ispis inorder stabla\n");
		printf("3 - ispis postorder stabla\n");
		printf("4 - ispis preorder stabla\n");
		printf("5 - ispis levelorder stabla\n");
		printf("6 - trazenje elementa stabla\n");
		printf("7 - brisanje elementa iz stabla\n");
		printf("8 - kraj\n");
		scanf(" %c", &ch);
		switch(ch){
			case '1':
				printf("\nUnesite broj koji zelite unijeti");
				scanf("%d", &broj);
				korijen = Unos(korijen, broj);
				break;
			case '2':
				printf("\nInOrder: \n");
				InOrderPrint(korijen);
				break;
			case '3':
				printf("\nPostOrder: \n");
				PostOrderPrint(korijen);
				break;
			case '4':
				printf("\nPreOrder: \n");
				PreOrderPrint(korijen);
				break;
			case '5':
				printf("\nLevelOrder: \n");
				LevelOrderPrint(korijen, stogHead);
				break;
			case '6':
				printf("\nUnesi koji broj zelis naci u stablu: ");
				scanf("%d", &broj);
				temp = NadiCvor(broj, korijen);
				if(temp){
					printf("\nCvor %d se nalazi na adres %d\n", temp->broj, temp);
				}
				break;
			case '7':
				printf("\nUnesi element koji brises iz stabla: \n");
				scanf("%d", &broj);
				korijen = IzbrisiCvor(broj, korijen);
				break;
			case '8':
				printf("\nZavrsetak programa");
				isActive = 0;
				break;
			default:
				printf("\nKrivi unos probajte ponovno");
				break;
		}
	}
	return EXIT_SUCCESS;
}

int Push(Stablo cvor, Pozicija stogHead){
	Pozicija q = StvoriStogElement();
	q->cvor = cvor;

	q->sljedeci = stogHead->sljedeci;
	stogHead->sljedeci = q;
}

int Pop(Pozicija stogHead){
	Pozicija prev, curr = NULL;
	prev = StvoriStogElement();
	curr = StvoriStogElement();

	prev = stogHead;
	curr = prev->sljedeci;

	while (curr->sljedeci != NULL) {
		prev = curr;
		curr = curr->sljedeci;
	}

	prev->sljedeci = curr->sljedeci;
	printf("%d\n", curr->cvor->broj);
	free(curr);
}

Pozicija StvoriStogElement(){
	Pozicija q = malloc(sizeof(StogElement));
	if(!q){
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	q->sljedeci = NULL;
	q->cvor = NULL;
	return q;
}

int LevelOrderPrint(Stablo korijen, Pozicija stogHead){
	Stablo trenutni = NULL;
	if(korijen == NULL){
		return EXIT_SUCCESS;
	}
	Push(korijen, stogHead);
	while(stogHead->sljedeci != NULL){
		trenutni = NadiZadnjiNaStogu(stogHead);
		if(trenutni->lijevo != NULL){
			Push(trenutni->lijevo, stogHead);
		}
		if(trenutni->desno != NULL){
			Push(trenutni->desno, stogHead);
		}
		Pop(stogHead);
	}
}

Stablo NadiZadnjiNaStogu(Pozicija stogHead){
	while (stogHead->sljedeci != NULL) {
		stogHead = stogHead->sljedeci;
	}
	return stogHead->cvor;
}

Stablo IzbrisiCvor(int broj, Stablo korijen){
	Stablo tmp = NULL;
	if(!korijen){
		return korijen;
	}
	else if(broj < korijen->broj){
		korijen->lijevo = IzbrisiCvor(broj, korijen->lijevo);
	}
	else if(broj > korijen->broj){
		korijen->desno = IzbrisiCvor(broj, korijen->desno);
	}
	else{
		if(korijen->lijevo && korijen->desno){
			tmp = NadiMin(korijen->desno);
			korijen->broj = tmp->broj;
			korijen->desno = IzbrisiCvor(tmp->broj, korijen->desno);
		}
		else{
			tmp = korijen;
			if(!korijen->lijevo){
				korijen = korijen->desno;
			}
			else if(!korijen->desno){
				korijen = korijen->lijevo;
			}
			free(tmp);
		}
	}
	return korijen;
};
Stablo NadiMin(Stablo korijen){
	while(korijen->lijevo){
		korijen = korijen->lijevo;
	}
	return korijen;
};
Stablo NadiCvor(int broj, Stablo korijen){
	if(!korijen){
		return korijen;
	}
	else if(broj < korijen->broj){
		return NadiCvor(broj, korijen->lijevo);
	}
	else if(broj > korijen->broj){
		return NadiCvor(broj, korijen->desno);
	}
	else{
		return korijen;
	}
};

Stablo StvoriStablo(int broj){
	Stablo q = malloc(sizeof(CvorStabla));
	if(!q){
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	q->broj = broj;
	q->lijevo = NULL;
	q->desno = NULL;
	return q;
}

Stablo Unos(Stablo p, int broj){
	if(p == NULL){
		p = StvoriStablo(broj);
	}
	else{
		if(broj > p->broj){
			p->desno = Unos(p->desno, broj);
		}
		if(broj < p->broj){
			p->lijevo = Unos(p->lijevo, broj);
		}
	}
	return p;
}

int InOrderPrint(Stablo korijen){
	if(korijen == NULL){
		return EXIT_SUCCESS;
	}
	else{

		InOrderPrint(korijen->lijevo);
		printf("%d\n", korijen->broj);
		InOrderPrint(korijen->desno);
	}
	return EXIT_SUCCESS;
}

int PostOrderPrint(Stablo korijen){
	if(korijen == NULL){
		return EXIT_SUCCESS;
	}
	else{

		PostOrderPrint(korijen->lijevo);
		PostOrderPrint(korijen->desno);
		printf("%d\n", korijen->broj);
	}
	return EXIT_SUCCESS;
}

int PreOrderPrint(Stablo korijen){
	if(korijen == NULL){
		return EXIT_SUCCESS;
	}
	else{

		printf("%d\n", korijen->broj);
		PreOrderPrint(korijen->lijevo);
		PreOrderPrint(korijen->desno);
	}
	return EXIT_SUCCESS;
}
