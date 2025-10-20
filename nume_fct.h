/*TĂNASE Lorena - 311 CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* declararea structurilor */
/* declararea structurii de satelit */
struct satelit;
typedef struct satelit* TSat;

typedef struct satelit {
  int frecv;
  char *nume;
  TSat st, dr;
} *TSat;

/* structura de heap - luata din laboratorul 6 */
typedef int (*TFCmp)(TSat, TSat);

typedef struct Heap {
    int nrMax, nrElem;
    TSat *v;
    TFCmp comp;
} THeap;

/* structura de coada - luata din laboratorul 3 */
typedef struct celula
{ 
  TSat info;
  struct celula *urm, *pre;
} TCelula, *TLista;

typedef struct coada
{ 
  TLista inc;       /* adresa primei celule */
} TCoada;


/* functii pt heap-uri */
int RelMinHeap(TSat a, TSat b);
THeap* AlocaHeap(int nrMax, TFCmp comp);
void insertHeap(THeap *h, TSat val);
TSat extrHeap(THeap *h);
void AfisareHeap(THeap* h, int pos);
void DistrugeHeap(THeap **h);

/* functii pt coada */
TCoada* InitQ ();
int IntrQ(TCoada *c, TSat x);
TSat ExtrQ(TCoada *c);
void DistrQ(TCoada **c);
void AfisareQ(TCoada *c);

/* functii pt sateliti */
TSat initializare_satelit(int frecv_noua, char *nume_nou);
void distruge_satelit(TSat *aux);
void distruge(TSat r);
void DistrSat(TSat *a);

/* fct auxiliare */
int task_nr(char *str);
void afisare_galaxie(TSat sat, FILE *fout);
char *trimming_if_fun(char *str);
int *constr_drum(TSat r, char *str, int *c, int *i);

/* task-uri */
TSat task1(char **matrix_of_elem, int nr_of_sat);
void task2 ( char** codif, int nr_de_codif, TSat galaxie, FILE *fout);
void task3(char **vect_de_sat, int nr_of_sat, int nr_de_sat_de_gasit, TSat galaxie, FILE *fout);
TSat task4(char **vect_de_sat, int nr_de_sat_de_gasit, TSat aux);