#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _student;
typedef struct _student* pozicija;
typedef struct _student {
    char ime[50];
    char prezime[50];
    int godRodenja;
    pozicija next;
}student;

int PrintMenu();
pozicija Inicijalizacija(pozicija p);
int DodajNaPocetak(pozicija p);
int Ispis(pozicija p);
int DodajNaKraj(pozicija p);
int TraziPoPrezimenu(pozicija p);
pozicija PronadiPrethodni(pozicija p, char* prezime);
int Izbrisi(pozicija p);

int main()
{
    pozicija head = NULL;
    int odabir=0, uvjet=1;

    while(uvjet)
    {
        PrintMenu();
        scanf("%d", &odabir);

        switch(odabir)
        {
        case 1:
            DodajNaPocetak(head);
            break;

        case 2:
            Ispis(head);
            break;

        case 3:
            DodajNaKraj(head);

        case 4:
            TraziPoPrezimenu(head);
            break;

        case 5:
            Izbrisi(head);
            break;

        case 6:
            uvjet = 0;
            break;
        }

    }

    OslobodiMemoriju(head);


    return 0;
    }

int PrintMenu()
{
    printf("1. Unesi studenta na pocetak.\n");
	printf("2. Ispisi listu.\n");
	printf("3. Unesi studenta na kraj.\n");
	printf("4. Pronadji preko prezimena.\n");
	printf("5. Izbrisi preko prezimena.\n");
	printf("6. Izadi iz programa.\n");


	printf("\nUnesite izbor : ");

	return 0;
}

pozicija Inicijalizacija(pozicija p)
    {
        p = (pozicija)malloc(sizeof(student));

        if(p==NULL)
        {
            printf("Greska u inicijalizaciji\n");
            return NULL;
        }

        strcpy(p->ime, "");
        strcpy(p->prezime, "");
        p->godRodenja = 0;
        p->next = NULL;

        return p;
    }

int DodajNaPocetak(pozicija p)
    {
        pozicija q = NULL;
        q  = Inicijalizacija(q);
        if(q==NULL)
        {
            printf("Greska u inicijalizaciji\n");
            return -1;
        }

        printf("Ime:");
        scanf("%s", q->ime);
        printf("Prezime:");
        scanf("%s", q->prezime);
        printf("Godina Rodenja:");
        scanf("%d", &q->godRodenja);

        q->next = p->next;
        p->next = q;

        return 0;
    }

int Ispis(pozicija p)
{
    p = p->next;

    if(p==NULL)
    {
        printf("Prazna lista\n");
        return -1;
    }

    while(p!=NULL)
    {

        printf("%s %s %d\n", p->ime, p->prezime, p->godRodenja);
        p = p->next;
    }

    return 0;
}

int DodajNaKraj(pozicija p)
{
    pozicija q = NULL;
    q = Inicijalizacija(q);

    if(q==NULL)
    {
        printf("Greska u inicijalizaciji\n");
        return -1;
    }

        while(p->next != NULL)
        {
            p = p->next;
        }

         printf("Ime:");
        scanf("%s", q->ime);
        printf("Prezime:");
        scanf("%s", q->prezime);
        printf("Godina Rodenja:");
        scanf("%d", &q->godRodenja);

        q->next = p->next;
        p->next = q;

        return 0;
}

int TraziPoPrezimenu(pozicija p)
{
    p = p->next;
    char prez[50] = {0};

    printf("Unesite prezime koje trazite\n");
    scanf("%s", prez);

    while(p != NULL && strcmp(p->prezime, prez) != 0)
    {
        p = p->next;
    }

    if(p==NULL)
    {
        printf("Osoba s tim prezimenom ne postoji\n");
    }
    else
    {
        printf("Trazena osoba je %p\n", p);
    }

    return 0;

}

pozicija PronadiPrethodni(pozicija p, char* prezime)
{
   pozicija prethodni = NULL;
   pozicija trenutni = NULL;

	prethodni = p;
	trenutni = p->next;

	while (trenutni != NULL && strcmp(trenutni->prezime, prezime) != 0)
	{
		prethodni = trenutni;
		trenutni = prethodni->next;
	}

	if (trenutni == NULL)
	{
		return NULL;
	}

	else
		return prethodni;
}

int Izbrisi(pozicija p)
{
	pozicija temp = NULL;
	char prezimeZaObr[50] = { 0 };

	printf("Unesi prezime koje zelis izbrisati: ");
	scanf(" %s", prezimeZaObr);

	p = PronadiPrethodni(p, prezimeZaObr);
	if (p == NULL)
	{
		printf("Osoba s tim prezimenom ne postoji!\n");
		return -1;
	}

	temp = p->next;
	if(temp != NULL)
    {
        p->next = temp->next;
        free(temp);
    }

	return 0;
}

int OslobodiMemoriju(pozicija p)
{
    pozicija temp = NULL;

    while(p->next !=NULL)
    {
        temp = p->next;
        p->next = temp->next;
        free(temp);
    }

   return 0;

}


