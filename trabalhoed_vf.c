#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "trabalhoed_vf.h"

int comparacoesABP[1000];
int comparacoesAVL[1000];

ABP* insere_abp(ABP *a,info i)
{
    if (a == NULL)
    {
        a = (ABP*) malloc(sizeof(ABP));
        a->chave=i;
        a->esq = NULL;
        a->dir = NULL;

    }
    else if (strcmp(i.palavra,a->chave.palavra)<0)
    {

        a->esq = insere_abp(a->esq,i);
    }
    else
        a->dir = insere_abp(a->dir,i);
    return a;
}

void central(ABP *a)
{
    if (a!= NULL)
    {
        central(a->esq);
        printf("%s ",a->chave.palavra);
        printf("%d \n",a->chave.escore);
        central(a->dir);
    }
}

AVL * rotacao_esquerda(AVL *p)
{
    AVL *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;
    return p;
}



AVL* rotacao_direita(AVL* p)
{
    AVL *u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;
    return p;
}


AVL* rotacao_dupla_direita (AVL* p)
{
    AVL *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;
    if (v->FB == 1) p->FB = -1;
    else p->FB = 0;
    if (v->FB == -1) u->FB = 1;
    else u->FB = 0;
    p = v;
    return p;
}

AVL* rotacao_dupla_esquerda (AVL *p)
{
    AVL *z, *y;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;
    if (y->FB == -1) p->FB = 1;
    else p->FB = 0;
    if (y->FB == 1) z->FB = -1;
    else z->FB = 0;
    p = y;
    return p;
}

AVL* Caso1 (AVL*a, int *ok)
{
    AVL *z;
    z = a->esq;
    if (z->FB == 1)
        a = rotacao_direita(a);
    else
        a = rotacao_dupla_direita(a);
    a->FB = 0;
    *ok = 0;
    return a;
}

AVL* Caso2 (AVL *a, int *ok)
{
    AVL *z;
    z = a->dir;
    if (z->FB == -1)
        a = rotacao_esquerda(a);
    else
        a = rotacao_dupla_esquerda(a);
    a->FB = 0;
    *ok = 0;
    return a;
}

AVL* InsereAVL (AVL *a, info x, int *ok)
{
    /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
    x, a chave a ser inserida e h a altura da árvore */
    if (a == NULL)
    {
        a = (AVL*) malloc(sizeof(AVL));
        a->chave = x;
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    else if (strcmp (x.palavra,a->chave.palavra)<0)
    {
        a->esq = InsereAVL(a->esq,x,ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case -1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = 1;
                break;
            case 1:
                a=Caso1(a,ok);
                break;
            }
        }
    }
    else
    {
        a->dir = InsereAVL(a->dir,x,ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case 1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = -1;
                break;
            case -1:
                a = Caso2(a,ok);
                break;
            }
        }
    }
    return a;
}

int retorna_escore(ABP *a, char chave[100],int i)
{
    while (a!=NULL)
    {
        comparacoesABP[i]++;
        if (strcmp(chave,a->chave.palavra)==0)
        {
            comparacoesABP[i]++;
            return a->chave.escore;
        }

        else
        {
            comparacoesABP[i]++;
         if (strcmp(chave,a->chave.palavra)<0)
            a = a->esq;
        else
            a = a->dir;
        }
    }
    return 0; //não achou, retorna 0
}

int retorna_escoreAVL(AVL *a, char chave[100],int i)
{
    while (a!=NULL)
    {
        comparacoesAVL[i]++;
        if (strcmp(chave,a->chave.palavra)==0)
        {
            comparacoesAVL[i]++;
            return a->chave.escore;
        }

        else
        {
            comparacoesAVL[i]++;
         if (strcmp(chave,a->chave.palavra)<0)
            a = a->esq;
        else
            a = a->dir;
        }
    }
    return 0; //não achou, retorna 0
}




