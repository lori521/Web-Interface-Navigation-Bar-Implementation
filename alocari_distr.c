/*TĂNASE Lorena - 311 CB*/
#include "nume_fct.h"

/* functii pt HEAP-uri*/
/* functie de alocare a unui heap*/
THeap *AlocaHeap(int nrMax, TFCmp comp)
{
    THeap *h = (THeap *)malloc(sizeof(struct Heap));
    if (!h)
    {
        return NULL;
    }

    h->v = (TSat *)malloc(nrMax * sizeof(TSat));
    if (!h->v)
    {
        free(h);
        return NULL;
    }

    h->nrMax = nrMax;
    h->nrElem = 0;
    h->comp = comp;

    return h;
}

/* functia de comparatie pt min-heap */
int RelMinHeap(TSat a, TSat b)
{
    if (a->frecv == b->frecv)
        return strcmp(a->nume, b->nume) > 0;
    else
        return a->frecv > b->frecv;
}

/* functia de comparatie pt min-heap */
int RelMaxHeap(TSat a, TSat b)
{
    if (a->frecv == b->frecv)
        return strcmp(a->nume, b->nume) < 0;
    else
        return a->frecv < b->frecv;
}

/* functia de distrugere pt heap */
void DistrugeHeap(THeap **h)
{
    for (int i = 0; i < (*h)->nrElem; i++)
    {
        free((*h)->v[i]->nume);
        free((*h)->v[i]);
    }
    free((*h)->v);
    free(*h);
    *h = NULL;
}

/* functia de inserare in heap */
void insertHeap(THeap *h, TSat val)
{
    if (h->nrElem >= h->nrMax || h == NULL)
        return;

    int i = h->nrElem;
    h->v[i] = val;
    h->nrElem++;

    while (i > 0 && h->comp(h->v[(i - 1) / 2], h->v[i]))
    {
        // swap
        TSat temp = h->v[i];
        h->v[i] = h->v[(i - 1) / 2];
        h->v[(i - 1) / 2] = temp;

        i = (i - 1) / 2;
    }
}

/* functia de extragere din heap */
TSat extrHeap(THeap *h)
{
    if (!h || h->nrElem == 0)
    {
        return 0;
    }

    TSat extr_value = h->v[0];

    h->v[0] = h->v[h->nrElem - 1];
    h->nrElem--;

    int poz = 0;
    int s = 2 * poz + 1;
    while (s < h->nrElem)
    {
        if (s + 1 < h->nrElem && h->comp(h->v[s], h->v[s + 1]))
        {
            s = s + 1;
        }

        if (!h->comp(h->v[poz], h->v[s]))
        {
            break;
        }

        TSat temp = h->v[poz];
        h->v[poz] = h->v[s];
        h->v[s] = temp;

        poz = s;
        s = 2 * poz + 1;
    }

    return extr_value;
}

/* functia de afisare pt heap */
void AfisareHeap(THeap *h, int pos)
{
    if (pos >= h->nrElem)
    {
        return;
    }

    printf("%d %s ", h->v[pos]->frecv, h->v[pos]->nume);

    AfisareHeap(h, 2 * pos + 1);

    AfisareHeap(h, 2 * pos + 2);
}

/* functii pt COADA*/
/* functia de alocare a unei cozi */
TCoada *InitQ() /* creeaza coada vida */
{
    TCoada *c;
    c = (TCoada *)malloc(sizeof(TCoada));
    if (!c)
        return NULL;

    c->inc = NULL;
    return c;
}

/* functia de inserare intr-o coada */
int IntrQ(TCoada *c, TSat x)
{
    TLista aux = (TLista)malloc(sizeof(TCelula)); /* 1 */
    if (!aux)
        return 0;

    aux->info = x;

    aux->urm = NULL;
    aux->pre = NULL;

    if (c->inc == NULL)
    {
        aux->urm = aux;
        aux->pre = aux;
        c->inc = aux;
    }
    else
    {
        aux->urm = c->inc;
        aux->pre = c->inc->pre;
        c->inc->pre->urm = aux;
        c->inc->pre = aux;
    }
    return 1;
}

/* functia de extragere dintr-o coada */
TSat ExtrQ(TCoada *c)
{
    if (!c || !c->inc)
        return NULL;
    TLista aux = c->inc;
    TSat x = aux->info;
    if (!x)
    {
        return NULL;
    }

    if (c->inc == c->inc->urm)
    {
        c->inc = NULL;
    }
    else
    {
        TLista ultim = c->inc;
        c->inc = c->inc->urm;
        c->inc->pre = ultim->pre;
        ultim->pre->urm = c->inc;
    }
    free(aux);
    return x;
}

/* functia de distrugere a unei coada */
void DistrQ(TCoada **c)
{
    if (*c)
    {
        TLista aux;
        while ((*c)->inc)
        {
            aux = (*c)->inc;
            (*c)->inc = aux->urm;
            free(aux->info->nume);
            free(aux->info);
            free(aux);
        }
        free(*c);
        *c = NULL;
    }
}

/* functia de afisare a unei coada */
void AfisareQ(TCoada *c)
{
    if (!c || !c->inc)
    {
        printf("coada goala.\n");
        return;
    }
    printf("Coada: [");
    TLista aux = c->inc;

    while (aux)
    {
        printf("%d-%s", aux->info->frecv, aux->info->nume);

        if (aux->urm == c->inc)
            break;
        aux = aux->urm;
    }
    printf("]\n");
}

/* functii pt SATELITI */
/* functia de initializare pt un satelit */
TSat initializare_satelit(int frecv_noua, char *nume_nou)
{
    TSat aux = (TSat)malloc(sizeof(struct satelit));
    if (!aux)
    {
        return NULL;
    }
    aux->frecv = frecv_noua;
    aux->nume = (char *)malloc((strlen(nume_nou) + 1) * sizeof(char));
    if (!aux->nume)
    {
        free(aux);
        return NULL;
    }
    strcpy(aux->nume, nume_nou);
    aux->dr = NULL;
    aux->st = NULL;
    return aux;
}

/* functia de distrugere a unui satelit */
void distruge_satelit(TSat *aux)
{
    if (!aux || !*aux)
        return;
    free((*aux)->nume);
    free(*aux);
    *aux = NULL;
}

/* functie auxiliara - distruge toate nodurile */
void distruge(TSat r)
{
    if (!r)
        return;
    distruge(r->st);      /* distruge subarborele stang */
    distruge(r->dr);      /* distruge subarborele drept */
    distruge_satelit(&r); /* distruge nodul radacina */
}

/* functie care distruge toate nodurile arborelui de la adresa a */
void DistrSat(TSat *a)
{
    if (!(*a))
        return;   /* arbore deja vid */
    distruge(*a); /* distruge toate nodurile */
    *a = NULL;
}
