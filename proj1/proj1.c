
#include <stdio.h>
#include <stdlib.h>

/* Estrutura da Listas de Arcos */
typedef struct arcos_s {
    int dest;
    int peso;
    struct arcos_s *next;
} arcos_t;

typedef struct lista_s {
    arcos_t *first;
    arcos_t *last;
} lista_t;

int nvert;              /* Numero de vertices do grafo e da mst */
int pmst;               /* Peso da mst */
lista_t **grafo;        /* Array de listas de arcos do grafo */
lista_t **mst;          /* Array de listas de arcos do mst */

int *vector;            /* Array de vertices visitados */
int *pesos;             /* Array de pesos máximos */

void dfs(int v1,int peso)
{
    arcos_t *l;

    vector[v1] = 1;     /* marca como visitado */
    if(mst[v1] == NULL)
        return;
    /* Percorre a lista de arcos */
    for(l = mst[v1]->first; l != NULL; l = l->next)
    {
        if(vector[l->dest] == 0)
        {
            /* ainda não visitamos */
            if (peso > l->peso)
                pesos[l->dest] = peso;
            else
                pesos[l->dest] = l->peso;
            dfs(l->dest,pesos[l->dest]);
        }
    }
}

int main(void)
{
    int i, n, min = -1;
    int no1, no2, peso;
    char dummy;
    arcos_t *na, *lg, *lm, *temp;

    /* lê nvertices */
    scanf("%d %d", &nvert, &n);
    /* lê grafo */
    grafo = (lista_t **) calloc(nvert, sizeof(lista_t *));
    for (i = 0; i < n; i++)
    {
        /* cria novo arco */
        na = (arcos_t *) malloc(sizeof(arcos_t));
        scanf("%d %d %d", &no1, &no2, &(na->peso));
        na->dest = no2-1;
        na->next = NULL;
        if (grafo[no1-1] == NULL)
        {   /* mete no 1º */
            grafo[no1-1] = (lista_t *) malloc(sizeof(lista_t));
            grafo[no1-1]->first = na;
        }
        else
        {
            /* mete no fim */
            grafo[no1-1]->last->next = na;
        }
        grafo[no1-1]->last = na;
    }

    /* Verifica a divisão de info */
    dummy = getchar(); /* o '\n' ou ' ' que vem a seguir ao grafo */
    if ((dummy != '\n' && dummy != ' ') || getchar() != '#')
        exit(-1);

    mst = (lista_t **) calloc(nvert, sizeof(lista_t *));
    /* lê mst */
    for (i = 0; i < nvert-1; i++)
    {
        /* 1º arco */
        na = (arcos_t *) malloc(sizeof(arcos_t));
        scanf("%d %d %d", &no1, &no2, &peso);
        /*actualiza peso da mst*/
        pmst += peso;
        na->dest = no2-1;
        na->peso = peso;
        na->next = NULL;
        if (mst[no1-1] == NULL)
        {   /* mete no 1º */
            mst[no1-1] = (lista_t *) malloc(sizeof(lista_t));
            mst[no1-1]->first = na;
        }
        else
        {
            /* mete no fim */
            mst[no1-1]->last->next = na;
        }
        mst[no1-1]->last = na;
        /* 2º arco */
        na = (arcos_t *) malloc(sizeof(arcos_t));
        na->dest = no1-1;
        na->peso = peso;
        na->next = NULL;
        if (mst[no2-1] == NULL)
        {   /* mete no 1º */
            mst[no2-1] = (lista_t *) malloc(sizeof(lista_t));
            mst[no2-1]->first = na;
        }
        else
        {
            /* mete no fim */
            mst[no2-1]->last->next = na;
        }
        mst[no2-1]->last = na;
    }
    /* procura arcos a mais */
    for (i = 0; i < nvert; i++)
    {
        if (grafo[i] == NULL)
            continue;
        vector = (int *) calloc(nvert, sizeof(int));
        pesos = (int *) calloc(nvert, sizeof(int));
        dfs(i, 0);
        /* Para cada vértice do grafo */
        for (lg = grafo[i]->first; lg != NULL; lg = temp)
        {
            lm = NULL;
            if (mst[i] != NULL)
            {
                /* Verifica se existe o arco na mst */
                for (lm = mst[i]->first; lm != NULL; lm = lm->next)
                {
                    /* Vê se os arcos são iguais */
                    if (lg->dest == lm->dest)
                        break;
                }
            }
            /* Se existem diferentes */
            if (lm == NULL)
            {
                n = (lg->peso) - pesos[lg->dest];
                if (n < min || min == -1)
                    min = n;
            }
            /* free do grafo */
            temp = lg->next;
            free(lg);
        }
        free(grafo[i]);
        free(pesos);
        free(vector);
    }
    free(grafo);
    printf("%d\n",min+pmst);
    /* free da mst */
    for (i = 0; i < nvert; i++)
    {
        if (mst[i] == NULL)
            continue;
        for (lm = mst[i]->first; lm != NULL; lm = temp)
        {
            temp = lm->next;
            free(lm);
        }
        free(mst[i]);
    }
    free(mst);

    return 0;
}
