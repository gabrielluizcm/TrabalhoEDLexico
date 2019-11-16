typedef struct info
{
    char palavra[100];
    int escore;
} info;

typedef struct AVL
{
    info chave;
    int FB;
    struct AVL *dir;
    struct AVL *esq;
} AVL;

typedef struct ABP
{
    info chave;
    struct ABP *dir;
    struct ABP *esq;
} ABP;

ABP* cria_abp(void);
AVL* cria_avl(void);
ABP* insere_abp(ABP *a,info i);
void central(ABP *a);
AVL* rotacao_esquerda(AVL *p);
AVL* rotacao_direita(AVL* p);
AVL* rotacao_dupla_direita (AVL* p);
AVL* rotacao_dupla_esquerda (AVL *p);
AVL* Caso1 (AVL*a, int *ok);
AVL* Caso2 (AVL *a, int *ok);
AVL* InsereAVL (AVL *a, info x, int *ok);
int retorna_escore(ABP *a, char chave[100],int i);
int retorna_escoreAVL(AVL *a, char chave[100],int i);






