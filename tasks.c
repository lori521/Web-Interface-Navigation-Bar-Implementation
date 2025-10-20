/*TĂNASE Lorena - 311 CB*/
#include "nume_fct.h"

TSat task1(char **matrix_of_elem, int nr_of_sat)
{
    /* aloc heap cu nr max de elem nr_of_sat elemente */
    THeap *sat_network = AlocaHeap(nr_of_sat, RelMinHeap);
    if (!sat_network)
        return NULL;

    /* parcurgerea pentru formarea heap-ului */
    for (int i = 0; i < nr_of_sat; i++)
    {
        /* initializarea satelitului cu informatiile din input */
        int frecv = atoi(matrix_of_elem[i]);
        char *nume = matrix_of_elem[nr_of_sat + i];

        TSat aux = initializare_satelit(frecv, nume);
        if (!aux)
        {
            DistrugeHeap(&sat_network);
            return NULL;
        }
        /* inserarea in min-heap */
        insertHeap(sat_network, aux);
    }

    /* formarea satelitilor de legatura si a legaturilor*/
    while (sat_network->nrElem > 1)
    {
        TSat sat_1 = extrHeap(sat_network);
        TSat sat_2 = extrHeap(sat_network);

        /* formarea informatiilor pentru satelitul de legatura */
        int frecv_noua = sat_1->frecv + sat_2->frecv;
        char *nume_nou = (char *)malloc((strlen(sat_1->nume) + strlen(sat_2->nume) + 1) * sizeof(char));
        if (!nume_nou)
        {
            distruge_satelit(&sat_1);
            distruge_satelit(&sat_2);
            DistrugeHeap(&sat_network);
            return NULL;
        }
        strcpy(nume_nou, sat_1->nume);
        strcat(nume_nou, sat_2->nume);
        /* initializarea satelitului de legatura cu informatiile de mai sus */
        TSat sat_nou = initializare_satelit(frecv_noua, nume_nou);
        free(nume_nou);
        if (!sat_nou)
        {
            distruge_satelit(&sat_1);
            distruge_satelit(&sat_2);
            DistrugeHeap(&sat_network);
            return NULL;
        }
        /* legaturile intre satelitul de legatura si satelitii cu care a fost format */
        sat_nou->st = sat_1;
        sat_nou->dr = sat_2;
        insertHeap(sat_network, sat_nou);
    }
    /* extragerea nodului care contine arborele final */
    TSat galaxie = extrHeap(sat_network);
    DistrugeHeap(&sat_network);
    return galaxie;
}

void task2(char **codif, int nr_de_codif, TSat galaxie, FILE *fout)
{
    /* parcurgerea vectorului cu string-uri */
    for (int i = 0; i < nr_de_codif; i++)
    {
        TSat inc = galaxie;
        int length = strlen(codif[i]);
        /* parcurgerea fiecarui string */
        for (int j = 0; j < length; j++)
        {
            /* trecerea in subarborele stang daca valoarea caracterului e 0 */
            if (codif[i][j] == '0')
            {
                if (inc->st)
                    inc = inc->st;
            }
            /* trecerea in subarborele drept daca valoarea caracterului e 1 */
            else if (codif[i][j] == '1')
            {
                if (inc->dr)
                    inc = inc->dr;
            }
            /* daca nu exista niciun fiu arborele se parcurge de la inceput */
            if (inc->st == NULL && inc->dr == NULL)
            {
                fprintf(fout, "%s ", inc->nume);
                inc = galaxie;
            }
        }
        fprintf(fout, "\n");
    }
}

void task3(char **vect_de_sat, int nr_of_sat, int nr_de_sat_de_gasit, TSat galaxie, FILE *fout)
{
    int k = 0;
    /* alocarea vectorului care retine drumul */
    int *c = (int *)malloc(nr_of_sat * sizeof(int));
    for (int j = 0; j < nr_of_sat; j++)
    {
        c[j] = 7;
    }

    for (int i = 0; i < nr_de_sat_de_gasit; i++)
    {
        k = 0;
        /* eliminarea spatiilor */
        vect_de_sat[i] = trimming_if_fun(vect_de_sat[i]);
        /* formarea drumului */
        c = constr_drum(galaxie, vect_de_sat[i], c, &k);
        /* afisarea inversa pana cand gasesc o valoare de 7*/
        for (int j = k - 1; j >= 0; j--)
        {
            if (c[j] != 7)
                fprintf(fout, "%d", c[j]);
            c[j] = 7;
        }
    }
    free(c);
}

TSat task4(char **vect_de_sat, int nr_de_sat_de_gasit, TSat aux)
{
    /* iesire din recursivitate */
    if (aux == NULL)
        return NULL;

    int i = 0;
    int toate_str_sunt_in_nume = 1;
    /* verificare daca numele satelitului contine toate string-urile din input */
    while (i < nr_de_sat_de_gasit)
    {
        if (strstr(aux->nume, vect_de_sat[i]) == NULL)
        {
            toate_str_sunt_in_nume = 0;
        }
        i++;
    }

    /* apelarea functiei pe subarbori */
    if (task4(vect_de_sat, nr_de_sat_de_gasit, aux->st))
        return task4(vect_de_sat, nr_de_sat_de_gasit, aux->st);
    if (task4(vect_de_sat, nr_de_sat_de_gasit, aux->dr))
        return task4(vect_de_sat, nr_de_sat_de_gasit, aux->dr);
    /* daca exista se da return la ultimul satelit gasit*/
    if (toate_str_sunt_in_nume)
        return aux;
}
