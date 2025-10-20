/*TĂNASE Lorena - 311 CB*/
#include <stdlib.h>

#include "nume_fct.h"

int main(int argc, char *argv[])
{
    printf("%d\n", argc);
    for(int i = 0; i < argc; i++){
        printf("pe pos %d ai %s\n",i, argv[i]);
    }
    /* variabila care preia nr cerintei din linia de comanda */
    int nr_of_task = task_nr(argv[1]);

    /* fisierele de intrare si iesire */
    FILE *fin = fopen(argv[2], "r");
    FILE *fout = fopen(argv[3], "w");

    /* radacina arborelui de sateliti */
    TSat galaxie;

    /* linia cu ajutorul careia se citeste input-ul */
    char *line = (char *)malloc(1000 * sizeof(char));
    if (!line)
    {
        return 1;
    }

    /* nr de linii citite de la tastatura */
    fgets(line, 25, fin);
    int nr_of_sat = atoi(line);

    /* structura in care pastrez prima parte dintre elementele din input alocata dinamic*/
    char **matrix_of_elem = malloc(2 * nr_of_sat * sizeof(char *));
    for (int i = 0; i < 2 * nr_of_sat; i++)
    {
        matrix_of_elem[i] = malloc(25 * sizeof(char));
    }

    int k = 0;
    /* structura are doua linii prima - pentru frecventa si a doua - pentru
     * numele satelitului */
    while ((fgets(line, 1000, fin) && (k != nr_of_sat)))
    {
        char *token = strtok(line, " \n");
        strcpy(matrix_of_elem[k], token);
        token = strtok(NULL, " \n");
        strcpy(matrix_of_elem[nr_of_sat + k], token);
        k++;
    }

    /* formarea arborelui pe baza caruia sunt implementate task-urile */
    galaxie = task1(matrix_of_elem, nr_of_sat);

    /* switch case in functie de numarul cerintei*/
    switch (nr_of_task)
    {
    case 1:
    {
        /*functia de afisare a arborelui pe nivel */
        afisare_galaxie(galaxie, fout);

        break;
    }
    case 2:
    {
        /* numarul de codificari citite de la tastatura */
        int nr_de_codif = atoi(line);

        /* structura in care pastrez elementele din input alocata dinamic*/
        char **codif = malloc(nr_de_codif * sizeof(char *));
        for (int i = 0; i < nr_de_codif; i++)
        {
            codif[i] = malloc(1000 * sizeof(char));
        }

        int k = 0;
        /* inserarea codificarilor in structura de mai sus */
        while ((fgets(line, 1000, fin) && (k != nr_de_codif)))
        {
            strcpy(codif[k], line);
            k++;
        }

        /* apelul functiei care rezolva a doua cerinta */
        task2(codif, nr_de_codif, galaxie, fout);

        /* eliberarea memoriei ocupate de sturctura */
        for (int i = 0; i < nr_de_codif; i++)
        {
            free(codif[i]);
        }
        free(codif);
        break;
    }
    case 3:
    {
        /* numarul de sateliti care trebuie gasiti in arbore */
        int nr_de_sat_de_gasit = atoi(line);

        /* structura in care pastrez elementele din input alocata dinamic*/
        char **vect_de_sat_task3 = malloc(nr_de_sat_de_gasit * sizeof(char *));
        for (int i = 0; i < nr_de_sat_de_gasit; i++)
        {
            vect_de_sat_task3[i] = malloc(15 * sizeof(char));
        }

        int k = 0;
        /* inserarea numelor satelitilor in structura de mai sus */
        while ((fgets(line, 1000, fin) && (k != nr_de_sat_de_gasit)))
        {
            strcpy(vect_de_sat_task3[k], line);
            k++;
        }

        /* apelul functiei care rezolva a treia cerinta */
        task3(vect_de_sat_task3, nr_of_sat, nr_de_sat_de_gasit, galaxie, fout);

        /* eliberarea memoriei ocupate de sturctura */
        for (int i = 0; i < nr_de_sat_de_gasit; i++)
        {
            free(vect_de_sat_task3[i]);
        }
        free(vect_de_sat_task3);

        break;
    }
    case 4:
    {
        int nr_de_sat_de_gasit = atoi(line);

        /* structura in care pastrez elementele din input alocata dinamic*/
        char **vect_de_sat_task4 = malloc(nr_de_sat_de_gasit * sizeof(char *));
        for (int i = 0; i < nr_de_sat_de_gasit; i++)
        {
            vect_de_sat_task4[i] = malloc(15 * sizeof(char));
        }

        int k = 0;
        /* inserarea numelor satelitilor in structura de mai sus */
        while ((k < nr_de_sat_de_gasit) && fgets(line, 1000, fin))
        {
            strcpy(vect_de_sat_task4[k], line);
            /* eliminarea spatiilor */
            vect_de_sat_task4[k] = trimming_if_fun(vect_de_sat_task4[k]);
            k++;
        }

        /* apelul functiei care rezolva a doua cerinta */
        TSat result = task4(vect_de_sat_task4, nr_de_sat_de_gasit, galaxie);
        fprintf(fout, "%s", result->nume);

        /* eliberarea memoriei ocupate de sturctura */
        for (int i = 0; i < nr_de_sat_de_gasit; i++)
        {
            free(vect_de_sat_task4[i]);
        }
        free(vect_de_sat_task4);

        break;
    }
    case 5:
    {
        printf("cerinta 5\n");
        break;
    }
    default:
    {
        printf("nu exista aceasta cerinta\n");
        break;
    }
    }

    /* eliberarea memoriei pentru structura care retine numele si frecventa satelitilor care formeaza min-heap-ul */
    for (int i = 0; i < 2 * nr_of_sat; i++)
    {
        free(matrix_of_elem[i]);
    }
    free(matrix_of_elem);

    /* eliberarea memoriei pentru restul structurilor folosite */
    free(line);
    DistrSat(&galaxie);

    /* inchiderea fisierelor utilizate */
    fclose(fin);
    fclose(fout);
    return 0;
}