#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _polinom;
typedef struct _polinom* pozicija;
typedef struct _polinom
{
	int koef;
	int eks;
	pozicija next;
}polinom;

int CitanjeIzDatoteke(char*, pozicija);
int IspisPolinoma(char*, pozicija);
int Zbroj(pozicija, pozicija, pozicija);
int Umnozak(pozicija, pozicija, pozicija);


int main()
{
	pozicija Polinom1 = NULL;
	Polinom1 = (pozicija)malloc(sizeof(polinom));
	Polinom1->next = NULL;

	pozicija Polinom2 = NULL;
	Polinom2 = (pozicija)malloc(sizeof(polinom));
	Polinom2->next = NULL;

	pozicija suma = NULL;
	suma = (pozicija)malloc(sizeof(polinom));
	suma->next = NULL;

	pozicija umnozak = NULL;
	umnozak = (pozicija)malloc(sizeof(polinom));
	umnozak->next = NULL;

	CitanjeIzDatoteke("Polinom1.txt", Polinom1);
	CitanjeIzDatoteke("Polinom2.txt", Polinom2);

	printf("Ispis prvog polinoma:\n");
	IspisPolinoma("Polinom1.txt", Polinom1->next);
	printf("Ispis drugog polinoma:\n");
	IspisPolinoma("Polinom2.txt", Polinom2->next);

	printf("Zbroj polinoma:\n P(x) = ");
	Zbroj(Polinom1, Polinom2, suma);
	printf("Umnozak polinoma:\n P(x) = ");
	Umnozak(Polinom1, Polinom2, umnozak);

	return 0;

}

int CitanjeIzDatoteke(char* FileName, pozicija p)
{
	pozicija q = NULL;
	q = (pozicija)malloc(sizeof(polinom));
	pozicija tmp = NULL;

	if (q == NULL)
	{
		printf("Nema mjesta u memoriji\n");
		return -1;
	}

	FILE* fp = fopen(FileName, "r");
	if (fp == NULL)
	{
		printf("Greska pri otvaranju\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(FileName, "%d %d", &q->koef, &q->eks);
	}

	tmp = p;

	while (tmp->next != NULL && tmp->next->eks > q->eks)
		tmp = tmp->next;

	if (tmp->next != NULL && tmp->next->eks == q->eks)
	{
		tmp->next->koef += q->koef;
		free(q);

		if (tmp->next->koef == 0)
		{
			q = tmp->next;
			tmp->next = q->next;
			free(q);
		}
	}
	else
	{
		q->next = tmp->next;
		tmp->next = q;
	}

	fclose(fp);
	return 0;


}

int IspisPolinoma(char* FileName, pozicija p)
{
	FILE* fp = fopen(FileName, "r");
	if (fp == NULL)
	{
		printf("greska pri otvaranju\n");
		return -1;
	}

	while (p != NULL)
	{
		int i = 1;
		if (i)
		{
			printf("%d^%d", p->koef, p->eks);
			i = 0;
		}
		else
		{
			if (p->koef > 0)
			{
				printf(" + %d^%d", p->koef, p->eks);
			}
			else
				printf(" - %d^%d", p->koef, p->eks);
		}
		p = p->next;
	}

	return 0;


}

int Zbroj(pozicija p1, pozicija p2, pozicija r)
{
	pozicija q = NULL, tmp = NULL;
	q = (pozicija)malloc(sizeof(polinom));
	if (q == NULL)
	{
		printf("Nema slobodnog mjesta u memoriji!\n");
		return -1;
	}
	tmp = (pozicija)malloc(sizeof(polinom));
	if (tmp == NULL)
	{
		printf("Nema slobodnog mjesta u memoriji!\n");
		return -1;
	}

	while (p1 != NULL && p2 != NULL) {

		if (p1->eks < p2->eks) {
			q->eks = p2->eks;
			q->koef = p2->koef;
			p2 = p2->next;
		}

		else if (p1->eks > p2->eks) {
			q->eks = p1->eks;
			q->koef = p1->koef;
			p1 = p1->next;
		}

		else {
			q->eks = p1->eks;
			q->koef = p1->koef + p2->koef;
			p1 = p1->next;
			p2 = p2->next;
		}
		q->next = r->next;
		r->next = q;
		r = q;
	}

	if (p1 == NULL)
		tmp = p2;
	else tmp = p1;

	while (tmp != NULL) {

		q->eks = tmp->eks;
		q->koef = tmp->koef;

		q->next = r->next;
		r->next = q;
		r = q;
		tmp = tmp->next;
	}
	return 0;
}

int Umnozak(pozicija p1, pozicija p2, pozicija r)
{
	pozicija q = NULL, tmp = NULL;
	q = (pozicija)malloc(sizeof(polinom));
	if (q == NULL)
	{
		printf("Nema slobodnog mjesta u memoriji!\n");
		return -1;
	}
	tmp = (pozicija)malloc(sizeof(polinom));
	if (tmp == NULL)
	{
		printf("Greska u alokaciji!\n");
		return -1;
	}
	while (p1 != NULL)
	{
		while (p2 != NULL)
		{

			q->eks = p1->eks + p2->eks;
			q->koef = p1->koef * p2->koef;

			q = q->next;
		}
		p1 = p1->next;
		p2 = p2->next;
	}

	tmp = r;

	while (tmp->next != NULL && tmp->next->eks > q->eks)
		tmp = tmp->next;

	if (tmp->next != NULL && tmp->next->eks == q->eks)
	{
		tmp->next->koef += q->koef;
		free(q);

		if (tmp->next->koef == 0)
		{
			q = tmp->next;
			tmp->next = q->next;

			free(q);
		}
		else {
			q->next = tmp->next;
			tmp->next = q;
		}
	}

	return 0;
}



