#include <stdio.h>   // Biblioteca para entrada e saída de dados (printf, scanf)
#include <stdlib.h>  // Biblioteca para alocação dinâmica de memória (malloc, free)
#include <time.h>    // Biblioteca para medir tempo de execução (clock)

/*
    Função que preenche o vetor com valores em ordem decrescente.
    Isso gera o pior caso para os algoritmos de ordenação.
    Exemplo: 5 4 3 2 1
*/
void preencherDecrescente(int v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i] = n - i;
    }
}

/*
    Implementação do Bubble Sort.
    Compara elementos adjacentes e troca quando estão fora de ordem.
    Também contabiliza:
    - número de comparações
    - número de movimentações (trocas)
*/
void bubbleSort(int v[], int n, long long *comparacoes, long long *movimentacoes) {
    int trocou;  // variável de controle para otimizar o algoritmo

    do {
        trocou = 0;

        // Percorre o vetor comparando pares adjacentes
        for (int i = 0; i < n - 1; i++) {

            (*comparacoes)++;  // conta uma comparação

            if (v[i] > v[i + 1]) {
                // Realiza a troca dos valores
                int temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;

                (*movimentacoes)++; // conta uma movimentação
                trocou = 1;         // indica que houve troca
            }
        }

    } while (trocou); // se não houve troca, o vetor já está ordenado
}

/*
    Implementação do Selection Sort.
    Busca o menor elemento da parte não ordenada e coloca na posição correta.
    Também contabiliza:
    - número de comparações
    - número de movimentações
*/
void selectionSort(int v[], int n, long long *comparacoes, long long *movimentacoes) {

    for (int i = 0; i < n - 1; i++) {
        int min = i;  // assume que o menor elemento está na posição i

        // Procura o menor valor no restante do vetor
        for (int j = i + 1; j < n; j++) {

            (*comparacoes)++; // conta uma comparação

            if (v[j] < v[min]) {
                min = j;
            }
        }

        // Se encontrou um valor menor, faz a troca
        if (min != i) {
            int temp = v[i];
            v[i] = v[min];
            v[min] = temp;

            (*movimentacoes)++; // conta uma movimentação
        }
    }
}

/*
    Função que testa os dois algoritmos para um determinado tamanho.
    Mede tempo, comparações e movimentações.
*/
void testarAlgoritmo(int tamanho) {

    // Aloca dinamicamente o vetor
    int *v = (int*) malloc(tamanho * sizeof(int));

    long long comparacoes = 0, movimentacoes = 0;
    clock_t inicio, fim;
    double tempo;

    /* ------------------- BUBBLE SORT ------------------- */

    preencherDecrescente(v, tamanho);  // gera o pior caso

    inicio = clock();                  // marca o tempo inicial
    bubbleSort(v, tamanho, &comparacoes, &movimentacoes);
    fim = clock();                     // marca o tempo final

    // Calcula o tempo em milissegundos
    tempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;

    printf("Bubble Sort\t%d\t%.2f ms\t%lld\t%lld\n",
           tamanho, tempo, comparacoes, movimentacoes);

    /* ------------------- SELECTION SORT ------------------- */

    preencherDecrescente(v, tamanho);  // recria o vetor desordenado
    comparacoes = movimentacoes = 0;   // zera os contadores

    inicio = clock();
    selectionSort(v, tamanho, &comparacoes, &movimentacoes);
    fim = clock();

    tempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;

    printf("Selection Sort\t%d\t%.2f ms\t%lld\t%lld\n",
           tamanho, tempo, comparacoes, movimentacoes);

    free(v); // libera a memória alocada
}

/*
    Função principal.
    Executa os testes para vetores de:
    100, 1000 e 10000 elementos.
*/
int main() {

    printf("Algoritmo\tTamanho\tTempo\t\tComparacoes\tMovimentacoes\n");

    testarAlgoritmo(100);
    testarAlgoritmo(1000);
    testarAlgoritmo(10000);

    return 0;
}
