#define _CRT_SECURE_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct _student;
typedef struct _student* pozicija;
typedef struct _student
{
    char ime[50];
    char prezime[50];
    int godRodenja;
    pozicija next;
}student;

int PrintMenu();
pozicija Inicijalizacija(pozicija p);
int DodajNaPocetak(pozicija p);
int UnesiPodatke(pozicija p);
int Ispis(pozicija p);
int DodajNaKraj(pozicija p);
int TraziPoPrezimenu(pozicija p);
pozicija PronadiPrethodni(pozicija p, char* prezime);
int Izbrisi(pozicija p);
int OslobodiMemoriju(pozicija p);

int DodajNakon(pozicija p);
int DodajIspred(pozicija p);
int SortListu(pozicija p);
int UpisiUDatoteku(pozicija p, char* datoteka);
int ProcitajIzDatoteke(pozicija p, char* datoteka);

int main()
{
    pozicija head = NULL;
    int odabir=0, uvjet=1;
    char datoteka[50] = {0};
    char datoteka2[50] = {0};
    head = Inicijalizacija(head);


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

        case 7:
            DodajNakon(head);
            break;

        case 8:
            DodajIspred(head);
            break;

        case 9:
            SortListu(head);
            break;

        case 10:
            printf("ime datoteke:\n");
            scanf(" %s", datoteka);
            UpisiUDatoteku(head->next, datoteka);
            break;

        case 11:
            printf("ime datoteke:\n");
            scanf(" %s", datoteka2);
            ProcitajIzDatoteke(head, datoteka2);
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
	printf("7. Unesi studenta nakon odredenog.\n");
	printf("8. Unesi studenta prije odredenog.\n");
	printf("9. Sortiraj listu.\n");
	printf("10. Unesi u datoteku.\n");
	printf("11. Procitaj iz datoteke.\n");




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

        UnesiPodatke(q);

        q->next = p->next;
        p->next = q;

        return 0;
    }

int UnesiPodatke(pozicija p)
{
        printf("Ime:");
        scanf("%s", p->ime);
        printf("Prezime:");
        scanf("%s", p->prezime);
        printf("Godina Rodenja:");
        scanf("%d", &p->godRodenja);

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

        UnesiPodatke(q);

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

int DodajNakon(pozicija p)
{
    pozicija q = NULL;
    char prezime[50] = {0};

    printf("unesi prezime osobe iza koje zelis dodati novu:\n");
    scanf(" %s", prezime);

    q = Inicijalizacija(q);

    while(p->next != NULL && strcmp(p->prezime, prezime)!=0)
    {
        p = p->next;
    }

    if(p != NULL)
    {

        UnesiPodatke(q);
        q->next = p->next;
        p->next = q;
    }

    return 0;
}

int DodajIspred(pozicija p)
{
    char prez[50] = {0};
    pozicija q = NULL;

    printf("Unesi prezime ispred kojeg zelite dodati novi:\n");
    scanf(" %s", prez);

    while (p->next != NULL && strcmp(p->next->prezime, prez) != 0)
	{
		p = p->next;
	}

	if (p->next != NULL)
	{
		q = Inicijalizacija(q);
		UnesiPodatke(q);
		q->next = p->next;
		p->next = q;
	}

	return 0;

}

int SortListu(pozicija p)
{
    pozicija a = NULL, b = NULL;
    pozicija prethodni = NULL, kraj = NULL;
    pozicija temp = NULL;

    for(a = p; a->next != kraj;)
    {
        prethodni = a;

        for(b = a->next; b->next != kraj; b = b->next)
        {
            if(strcmp(b->prezime, p->next->prezime)>0)
            {
                temp = b->next;
                temp->next = temp;
                b->next = temp->next;
                temp->next = b;
                b = temp;
            }
            prethodni = b;
        }
        kraj = b;
    }
    return 0;
}

int UpisiUDatoteku(pozicija p, char* datoteka)
{
   FILE* fp = NULL;

   fp = fopen(datoteka, "w");

   if(!fp)
   {
       printf("greska pri ucitavanju\n");
       return -1;
   }

   while(p!=NULL)
   {
       fprintf(fp, " %s %s %d", p->ime, p->prezime, p->godRodenja);
       p = p->next;
   }

   fclose(fp);

   return 0;
}

int ProcitajIzDatoteke(pozicija p, char* datoteka)
{
    pozicija q = NULL;
    FILE* fp = NULL;
    fp = fopen(datoteka, "r");

    if(!fp)
    {
        printf("greska pri ucitavanju\n");
        return -1;
    }

    while(!feof(fp))
    {
        q = Inicijalizacija(q);

        fscanf(fp, " %s %s %s", p->ime, p->prezime, p->godRodenja);
        q->next = p->next;
        p->next = q;
    }

    fclose(fp);

    return 0;
}
