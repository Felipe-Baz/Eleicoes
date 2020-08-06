#include <stdio.h>
#include <stdlib.h>
 
void mergesort(int *v, int n)
{
    int *c = malloc(sizeof(int) * n);
    sort(v, c, 0, n - 1);
    free(c);
}
 
/*
  Dado um vetor de inteiros v e dois inteiros i e f, ordena o vetor v[i..f] em ordem crescente.
  O vetor c é utilizado internamente durante a ordenação.
*/
void sort(int *v, int *c, int i, int f)
{
    if (i >= f)
        return;
 
    int m = (i + f) / 2;
 
    sort(v, c, i, m);
    sort(v, c, m + 1, f);
 
    /* Se v[m] <= v[m + 1], então v[i..f] já está ordenado. */
    if (v[m] <= v[m + 1])
        return;
 
    merge(v, c, i, m, f);
}
 
/*
  Dado um vetor v e três inteiros i, m e f, sendo v[i..m] e v[m+1..f] vetores ordenados,
  coloca os elementos destes vetores, em ordem crescente, no vetor em v[i..f].
*/
void merge(int *v, int *c, int i, int m, int f)
{
    int z,
        iv = i, ic = m + 1;
 
    for (z = i; z <= f; z++)
        c[z] = v[z];
 
    z = i;
 
    while (iv <= m && ic <= f)
    {
        /* Invariante: v[i..z] possui os valores de v[iv..m] e v[ic..f] em ordem crescente. */
 
        if (c[iv] < c[ic])
            v[z++] = c[iv++];
        else /* if (c[iv] > c[ic]) */
            v[z++] = c[ic++];
    }
 
    while (iv <= m)
        v[z++] = c[iv++];
 
    while (ic <= f)
        v[z++] = c[ic++];
}
 
//retorna 0 se não houver empate, se houver retorna de quantas pessoas
int empate(int eleitores, int candidatos, int votos[eleitores], int verif[candidatos])
{
    int i, j, teste[candidatos], obs = 0;
    for (i = 0; i < candidatos; i++)
    {
        teste[i] = 0;
    }
 
    for (i = candidatos; i > 2; i--)
    {
 
        if (votos[i - 1] == votos[i - 2])
        {
            obs = 1;
            teste[i - 1] = 1;
            teste[i - 2] = 1;
        }
        else
        {
            return 0;
        }
    }
 
    if (obs == 0)
    {
        return 0;
    }
    else
    {
        /*considerando q como estão empatados, possuem o mesmo numero de votos e o candidato
         vencedor é aquele que possue o menor numero de cadastro então podemos usar o vetor de
         verificação percorrendo ele do inicio ao fim em ordem crescente em busca do 1 valor
         que possua a quantidade de votos que ocasionou o empate.
         */
        for (i = 0; i < candidatos - 1; i++)
        {
            for (j = candidatos - 1; j >= 0; j--)
            {
                if (verif[i] == teste[j])
                {
                    float a = (votos[candidatos - 1] * 100);
                    printf("%d %.2f\n", i + 1, a / eleitores);
                    return 1;
                }
            }
        }
    }
}
 
void segundoTurno(int eleitores, int candidatos, int eleicao[eleitores][3], int votos[eleitores], int verif[candidatos])
{
    int i, j, cand1, cand2, cand3, votacao[2] = {0, 0}, test=  0; 
    for (i = 0; i < candidatos; i++)
    {
        if (verif[i] == votos[candidatos - 1])
        {
            cand1 = i;
        }
    }
    for (i = 0; i < candidatos; i++)
    {
        if (verif[i] == votos[candidatos - 2])
        {
            cand2 = i;
        }
    }
    for (i = 0; i < candidatos; i++)
    {
        if (verif[i] == votos[candidatos - 3] && i != cand2)
        {
            cand3 = i;
        }
    }
    if(verif[cand3] == verif[cand2])
    {
        if(cand2 > cand3)
        {
            cand2 = cand3;
        }
    }
    

    //correct
    for (i = 0; i < eleitores; i++)
    {
        int conc = 0;
        for (j = 0; j < 3; j++)
        {
            
            if (eleicao[i][j] == cand1 + 1)
            {
                votacao[0]++;
                conc = 1;
                break;
            }
            else if (eleicao[i][j] == cand2 + 1)
            {
                votacao[1]++;
                conc=1;
                break;
            }
        }
        if(conc == 0)
         {
            test++;
        }
    }
    //empate
    if (votacao[0] == votacao[1])
    {
        if (cand1 > cand2)
        {
            //candidato 2 win
 
            float a = (votacao[1] * 100);
            printf("%d %.2f\n", cand2+1, a / (eleitores-test));
        }
        else
        {
            //candidato 1 win
            float a = (votacao[0] * 100);
            printf("%d %.2f\n", cand1+1, a / (eleitores-test));
        }
    }
    else
    {
        if (votacao[0] > votacao[1])
        {
            //candidato 1 win
            float a = (votacao[0] * 100);
            printf("%d %.2f\n", cand1+1, a / (eleitores-test));
        }
        else
        {
            //candidato 2 win
 
            float a = (votacao[1] * 100);
            printf("%d %.2f\n", cand2+1, a / (eleitores-test));
        }
    }
}
 
void primeiroTurno(int eleitores, int candidatos, int votos[eleitores][3])
{
    int porcent[candidatos], i, j, vet[candidatos], teste = 0, Empate = 0;
    float resp;
    //contabiliza a quantidade de votos em cada candidato.
    for (i = 0; i < candidatos; i++)
    {
        porcent[i] = 0;
    }
 
    for (i = 0; i < eleitores; i++)
    {
        if (votos[i][0] > candidatos || votos[i][0] <= 0)
        {
            teste++;
        }
    }
    if (teste == eleitores)
    {
        printf("0"); //caso erro por votos invalidos
        return;
    }
 
    for (j = 1; j <= candidatos; j++)
    {
        for (i = 0; i < eleitores; i++)
        {
            if (votos[i][0] == j && votos[i][0] <= candidatos && votos[i][0] > 0)
            {
                porcent[j - 1]++;
            }
        }
    }
 
    for (i = 0; i < candidatos; i++)
    {
        vet[i] = porcent[i];
    }
 
    mergesort(&porcent, candidatos);
 
    Empate = empate(eleitores, candidatos, porcent, vet);
 
    if (Empate == 0)
    {
        float a = porcent[candidatos - 1] * 100;
        int test = 0;
        for (i = 0; i < eleitores; i++)
        {
            if (votos[i][0] > candidatos || votos[i][0] <= 0)
            {
                test++;
            }
        }
 
        for (i = 0; i < candidatos; i++)
        {
            if (vet[i] == porcent[candidatos - 1])
            {
 
                printf("%d %.2f\n", i + 1, (a / (eleitores - test)));
                int z = a / (eleitores - test);
 
                if (z < 50)
                {
 
                    segundoTurno(eleitores, candidatos, votos, porcent, vet);
                }
            }
        }
    }
}
 
int main(int argc, char const *argv[])
{
    int eleitores, candidatos, i, j, resp, cand1, cand2;
    scanf("%d", &eleitores);
    scanf("%d", &candidatos);
    int votos[eleitores][3];
    //zera o matriz
    for (i = 0; i < eleitores; i++)
    {
        for (j = 0; j < candidatos; j++)
        {
            votos[i][j] = 0;
        }
    }
    //adciono os votos
    for (i = 0; i < eleitores; i++)
    {
        scanf("%d %d %d", &votos[i][0], &votos[i][1], &votos[i][2]);
    }
    primeiroTurno(eleitores, candidatos, votos);
    return 0;
}
