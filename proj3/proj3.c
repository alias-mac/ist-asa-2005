
#include <stdio.h>
#include <stdlib.h>

/* Estrutura dos Pontos */
typedef struct ponto_s {
  int x;
  int y;
} ponto_t;

/* Estrutura da lista de Pontos */
typedef struct lista_s {
  ponto_t *p;
  struct lista_s *prev;
  struct lista_s *next;
} lista_t;

typedef struct stack_s {
  int p;
  struct stack_s *next;
} stack_t;

int n;              /* Número de Pontos em C */
ponto_t **apo;      /* Array ordenado de apontadores para Pontos */
lista_t *lpo;       /* O topo da lista de Pontos ordenada! */

void cria_lpo(void)
{
  int i;
  ponto_t *np;
  lista_t *temp = NULL;
  lista_t *nlpo;
  
  for (i = 0; i < n; i++)
  {
    /* cria novo ponto */
    np = (ponto_t *) calloc(1, sizeof(ponto_t));
    scanf("%d %d", &(np->x), &(np->y));
    /* cria espaço pa ele na lista */
    nlpo = (lista_t *) calloc(1, sizeof(lista_t));
    nlpo->p = np;
    /* Não existem pontos então é criado o 1º */
    if (temp == NULL)
    {
      lpo = nlpo;
      temp = nlpo;
      continue;
    }
    /* Encontra o lugar na lista */
    while (np->x > temp->p->x)
      temp = temp->next;    /* anda pa frente em x */
    while (np->x < temp->p->x)
      temp = temp->prev;    /* anda pa trás em x */
    while (np->x == temp->p->x && np->y > temp->p->y)
      temp = temp->next;    /* anda pa frente em y */
    while (np->x == temp->p->x && np->y < temp->p->y)
      temp = temp->prev;    /* anda pa trás em y */
    /* coloca ordenado na lista de Pontos */
    nlpo->prev = temp;
    nlpo->next = temp->next;
    nlpo->next->prev = nlpo;
    temp->next = nlpo;
  }
}

void toArray(void)
{
  int i;
  
  apo = (ponto_t **) calloc(n, sizeof(ponto_t *));
  for (i = 0; i < n; i++)
  {
    apo[i] = (lpo+i)->p;
  }
}

void print_array(void)
{
  int i;
  for (i = 0; i < n; i++)
  {
    printf("Ponto %d: %d\t%d\n", i, apo[i]->x, apo[i]->y);
  }
}

int main(void)
{
  lista_t *old;

  /* lê o número de pontos */
  scanf("%d", &n);
  
  /* Cria a lista de pontos ordenados */
  cria_lpo();
  
  /* Coloca lista de pontos ordenados num array */
  toArray();
  
  print_array();
  
  /* free da lista de pontos */
  while(lpo != NULL)
  {
    old = lpo;
    lpo = lpo->next;
    free(old);
  }
  free(lpo);
  
  return 0;
}
