/*TĂNASE Lorena - 311 CB*/
#include "nume_fct.h"

/* functie care returneaza numarul cerintei */
int task_nr(char *str) {
    if(strchr(str, '1')){
        return 1;
    } else if(strchr(str, '2')){
        return 2;
    } else if(strchr(str, '3')){
        return 3;
    } else if(strchr(str, '4')){
        return 4;
    } else if(strchr(str, '5')){
        return 5;
    }
    return 0;
}

/* functie care elimina spatiile */
char *trimming_if_fun(char *str) {
    int length = strlen(str);
    char *copy = (char*)malloc((length + 1)* sizeof(char));
    strncpy(copy, str, (length - 1));
    copy[length-1] = '\0';
    free(str);
    return copy;
}

/* functie recursiva care retine drumul catre un anumit satelit intr-un vector */
int *constr_drum(TSat r, char *str, int *c, int *i)
{
    if (r == NULL)
        return 0;
    if (strcmp(r->nume, str) == 0)
    {
        return c;
    }

    if (constr_drum(r->st, str, c, i)) {
        c[(*i)] = 0;
        (*i)++;
        return c;
    }
    
    if (constr_drum(r->dr, str, c, i)) {
        c[(*i)] = 1;
        (*i)++;
        return c;
    }
    return NULL;
}

/* pseudocodul de afisare pe nivel din curs */
void afisare_galaxie(TSat sat, FILE *fout)
{
    if (sat == NULL)
        return;

    TCoada *c = InitQ();
    IntrQ(c, sat);

    int sat_pe_niv_curent = 1;
    int sat_pe_niv_urm = 0;

    while (c->inc != NULL)
    {
        TSat aux = ExtrQ(c);
        fprintf(fout, "%d-%s ", aux->frecv, aux->nume);
        sat_pe_niv_curent--;

        if (aux->st != NULL)
        {
            IntrQ(c, aux->st);
            sat_pe_niv_urm++;
        }
        if (aux->dr != NULL)
        {
            IntrQ(c, aux->dr);
            sat_pe_niv_urm++;
        }

        if (sat_pe_niv_curent == 0)
        {
            fprintf(fout, "\n");
            sat_pe_niv_curent = sat_pe_niv_urm;
            sat_pe_niv_urm = 0;
        }
    }
    DistrQ(&c);
}
