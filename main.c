#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "trabalhoed_vf.h"

//Para chamar, digite "exemplo léxico.txt entrada.txt saida.txt" */

int comparacoesABP[1000];   //variáveis globais para contagem do número de comparações de cada árvore
int comparacoesAVL[1000];


int main(int argc, char *argv[]) //argc conta o número de parâmetros e argv armazena as strings correspondentes aos parâmentros digitados
{

    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados


    FILE *lexico;
    FILE *sentencas;

    FILE *saida;
    int i,ok,*escore;
    int total[1000];
    info inf;
    char *palavra, linha[1000]; // linhas a serem lidas do arquivo
    char separador[]= {" ,.&*%\?!;/'@\"$#=><()][}{:\t"}; //possíveis caracteres separadores para tokenização
    ABP* palavras_abp;
    AVL* palavras_avl;
    palavras_abp=NULL;
    palavras_avl=NULL;


    if (argc!=4)  //o numero de parametros esperado é 4: nome do programa (argv[0]), nome do arquivo léxico(argy[1]), nome do arq de entrada de frases(argv[2]), nome do arq de saida(argv[3])
    {
        printf ("Número incorreto de parâmetros.\n Para chamar o programa digite: exemplo <arq_lexico> <arq_entrada> <arq_saida>\n");
        return 1;
    }
    else
    {

        lexico = fopen (argv[1], "r"); // abre o arquivo para leitura -- argv[1] é o primeiro parâmetro após o nome do arquivo.
        if (lexico == NULL) //se não conseguiu abrir o arquivo
        {
            printf ("Erro ao abrir o arquivo %s",argv[1]);
            return 1;
        }
        sentencas = fopen (argv[2], "r"); // abre o arquivo para leitura -- argv[2] é o segundo parâmetro após o nome do arquivo.
        if (sentencas == NULL) //se não conseguiu abrir o arquivo
        {
            printf ("Erro ao abrir o arquivo %s",argv[2]);
            return 1;
        }
        else // arquivo de entrada OK

        {
            saida = fopen (argv[3], "w"); // abre o arquivo para saida -- argv[3] é o terceiro parâmetro após o nome do arquivo.


            rewind (lexico);
            rewind (sentencas);

            while (fgets(linha,1000,lexico))                     //percorre todo o arquivo do lexico de palavras,lendo linha por linha
            {
                palavra=strtok(linha,separador);
                strcpy (inf.palavra,palavra);                   //copia palavra lida para estrutura
                palavra = strtok (NULL, separador);
                escore = atoi(palavra);
                inf.escore=escore;                              //copia pontuacao da palavra lida para estrutura
                palavras_abp=insere_abp(palavras_abp,inf);      //insere estrutura com palavra e seu escore na ABP
                palavras_avl=InsereAVL(palavras_avl,inf,&ok);   //insere estrutura com palavra e seu escore na AVL
            }

            i=0;

            while (fgets(linha,1000,sentencas))                       //percorre todo arquivo de sentencas, lendo linha por linha
            {
                total[i]=0;                                           //inicializa escore total da linha
                comparacoesABP[i] = 0;

                palavra=strtok(linha,separador);
                while(palavra!=NULL)                                   //percorre toda linha
                {
                    total[i]=total[i]+retorna_escore(palavras_abp, palavra, i); //soma escore da palavra ao escore total da frase
                    palavra = strtok (NULL, separador);
                }
                i++;                                                        //incrementa indice da linha no vetor.
            }

            i=0;                                                            //inicializa indice da linha

            rewind(sentencas);

            while (fgets(linha,1000,sentencas))                       //percorre todo arquivo de sentencas, lendo linha por linha
            {
                total[i]=0;                                           //inicializa escore total da linha
                comparacoesAVL[i] = 0;

                palavra=strtok(linha,separador);
                while(palavra!=NULL)                                   //percorre toda linha
                {

                    total[i]=total[i]+retorna_escoreAVL(palavras_avl, palavra, i); //soma escore da palavra ao escore total da frase
                    palavra = strtok (NULL, separador);

                }
                i++;                                                        //incrementa indice da linha no vetor.
            }

            i=0;                                                            //inicializa indice da linha

            rewind (sentencas);
            while (fgets(linha,1000,sentencas))                             //percorre arquivo de sentencas linha por linha
            {
                //escreve no arquivo a frase e sua pontuação
                fprintf(saida,"Frase: %sEscore: %d\nComparações ABP: %d\nComparações AVL: %d\n\n",linha,total[i],comparacoesABP[i],comparacoesAVL[i]);
                i++;    //incrementa indice da linha
            }

            printf("\nArquivo %s gerado com sucesso.\n",argv[3]);
        }
        fclose (lexico); //fecha os arquivos
        fclose (sentencas);
        fclose (saida);
        return 0;
    }
}
