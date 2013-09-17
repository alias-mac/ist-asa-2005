
#include <stdio.h>
#include <stdlib.h>

/* Estrutura da Listas de Arcos */
typedef struct arcos_s {
  int orig;
  int dest;
  int cap;
  int fluxo;
  struct arcos_s *next;
} arcos_t;

typedef struct lista_s {
  arcos_t *first;
  arcos_t *last;
} lista_t;

typedef struct fifo_s {
  int vert;
  struct fifo_s *next;
} fifo_t;

int narcos;         /* Numero de arcos do grafo */
int nvert;          /* Numero de vertices do grafo */
lista_t **grafo;    /* O topo da lista do grafo */

void grafo_cap(void)
{
  int i;
  int no1, no2;
  arcos_t *na;
  
  grafo = (lista_t **) calloc(nvert, sizeof(lista_t *));
  for (i = 0; i < narcos; i++)
  {
    /* cria novo arco */
    na = (arcos_t *) calloc(1, sizeof(arcos_t));
    scanf("%d %d %d", &no1, &no2, &(na->cap));
    na->orig = no1-1;
    na->dest = no2-1;
    /* coloca no grafo_cap */
    if (grafo[no1-1] == NULL)
    {   /* mete no 1º */
      grafo[no1-1] = (lista_t *) calloc(1, sizeof(lista_t));
      grafo[no1-1]->first = na;
    }
    else
    {
      /* mete no fim */
      grafo[no1-1]->last->next = na;
    }
    grafo[no1-1]->last = na;
  }
}

void grafo_fluxo(void)
{
  int i;
  int no1, no2, temp;
  arcos_t *lg;
  
  for (i = 0; i < narcos; i++)
  {
    scanf("%d %d %d", &no1, &no2, &temp);
    
    /* Percorre a lista de arcos à procura do que queremos */
    for (lg = grafo[no1-1]->first; lg != NULL; lg = lg->next)
    {
      /* Verifica se é o mesmo arco */
      if (lg->dest == no2-1)
        lg->fluxo = temp;
    }
  }
}

void grafo_alt(void)
{
  int i, n;
  int no1, no2, temp;
  arcos_t *lg;
  
  /* número de arcos a alterar */
  scanf("%d", &n);
  for (i = 0; i < n; i++)
  {
    scanf("%d %d %d", &no1, &no2, &temp);
    
    /* Percorre a lista de arcos à procura do que queremos */
    for (lg = grafo[no1-1]->first; lg != NULL; lg = lg->next)
    {
      /* Verifica se é o mesmo arco */
      if (lg->dest == no2-1)
        lg->cap = temp;
    }
  }
}

arcos_t **bfs(void)
{
  int res;
  int *color = (int *) calloc(nvert, sizeof(int));
  arcos_t *temp;
  fifo_t *fifo = (fifo_t *) calloc(1, sizeof(fifo_t));
  fifo_t *last = fifo;
  fifo_t *aux; /* para o free */
  arcos_t **pi = (arcos_t **) calloc(nvert, sizeof(arcos_t *));
  
  /* Marca vertice gray */
  color[0] = 1;
  fifo->vert = 0; /*já tá a 0*/
  while (fifo != NULL)
  {
    for (temp = grafo[fifo->vert]->first; temp != NULL; temp = temp->next)
    {
      res = temp->cap - temp->fluxo;
      if (res == 0) /* saturado */
        continue;
      if (color[temp->dest] == 0) /* ainda n foi visitado */
      {
        color[temp->dest] = 1;
        /* Coloca o predecessor de temp->dest */
        pi[temp->dest] = temp;
        /* Enqueue */
        last->next = (fifo_t *) calloc(1,sizeof(fifo_t));
        last->next->vert = temp->dest;
        last = last->next;
      }
      if (temp->dest == 1) /* Chegámos à sink */
      {
        /* free da fifo */
        for (aux = fifo; aux != NULL; aux = fifo)
        {
          fifo = fifo->next;
          free(aux);
        }
        free(color);
        return pi;
      }
    }
    /* Marca vertice black */
    color[fifo->vert] = 2;
    /* Dequeue */
    aux = fifo, fifo = fifo->next;
    free(aux);
  }
  /* free do vector de cores da BFS */
  free(color);
  /* free do vector de precedencias */
  free(pi);
  /* já não é possivel chegar aumentar fluxo */
  return NULL;
}

void fluxo_aum(arcos_t *pi[])
{
  int i, j, min, res;
  
  /* Procuramos o residual minimo pelo caminho p */
  min = pi[1]->cap - pi[1]->fluxo;
  for (j = 1, i = j; i != 0; j = i, i = pi[j]->orig)
  {
    res = pi[i]->cap - pi[i]->fluxo;
    if (res < min)
      min = res;
  }
  /* Aumentamos o fluxo pelo caminho p min unidades */
  for (j = 1, i = j; i != 0; j = i, i = pi[j]->orig)
    pi[i]->fluxo += min;
}

int fluxo_cal(void)
{
  int res = 0;
  arcos_t *temp;
  arcos_t **pi;
  
  /* Começa-se em 1 e verifica-se se é possivel chegar a 2 */
  while ((pi = bfs()) != NULL)
  {
    /* Aumenta-se o fluxo por esse caminho */
    fluxo_aum(pi);
    /* free do vector de precedencias */
    free(pi);
  }
  
  /* Calcula fluxo final máximo */
  for (temp = grafo[0]->first; temp != NULL; temp = temp->next)
    res += temp->fluxo;
  
  return res;
}

int main(void)
{
  int i;
  int no1, no2, f;
  char dummy;       /* Para divisão de informação */
  arcos_t *lg, *temp;

  /* lê nvertices e narcos */
  scanf("%d %d", &nvert, &narcos);
  
  /* Cria o grafo e preenche com as capacidades */
  grafo_cap();
  
  /* Verifica a divisão de info */
  dummy = getchar(); /* o '\n' ou ' ' que vem a seguir ao grafo */
  if ((dummy != '\n' && dummy != ' ') || getchar() != '#')
    exit(-1);
  
  /* Bypass dos fluxos */
  for (i = 0; i < narcos; i++)
    scanf("%d %d %d", &no1, &no2, &f);
  
  /* Verifica a divisão de info */
  dummy = getchar(); /* o '\n' ou ' ' que vem a seguir ao grafo */
  if ((dummy != '\n' && dummy != ' ') || getchar() != '#')
    exit(-1);
  
  /* Coloca as alterações */
  grafo_alt();
  
  /* Calcula o fluxo máximo do grafo */
  printf("%d\n", fluxo_cal());
  
  /* free do grafo */
  for (i = 0; i < nvert; i++)
  {
    if (grafo[i] == NULL)
      continue;
    for (lg = grafo[i]->first; lg != NULL; lg = temp)
    {
      temp = lg->next;
      free(lg);
    }
    free(grafo[i]);
  }
  free(grafo);
  
  return 0;
}
