#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void preencherDecrescente(int v[], int n) {
	int i;
    for (i = 0; i < n; i++) {
        v[i] = n - i;
    }
}

void bubbleSort(int v[], int n, long long *comparacoes, long long *movimentacoes) {
    int trocou;

    do {
        trocou = 0;
        int i;
        for (i = 0; i < n - 1; i++) {
            (*comparacoes)++;

            if (v[i] > v[i + 1]) {
                int temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;

                (*movimentacoes)++;
                trocou = 1;
            }
        }
    } while (trocou);
}

void selectionSort(int v[], int n, long long *comparacoes, long long *movimentacoes) {
	int i;
    for (i = 0; i < n - 1; i++) {
        int min = i;
        
        int j;
        for (j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (v[j] < v[min]) {
                min = j;
            }
        }

        if (min != i) {
            int temp = v[i];
            v[i] = v[min];
            v[min] = temp;

            (*movimentacoes)++;
        }
    }
}

void testarAlgoritmo(int tamanho) {
    int *v = (int*) malloc(tamanho * sizeof(int));

    long long comparacoes = 0, movimentacoes = 0;
    clock_t inicio, fim;
    double tempo;

    preencherDecrescente(v, tamanho);

    inicio = clock();
    bubbleSort(v, tamanho, &comparacoes, &movimentacoes);
    fim = clock();

    tempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;

    printf("Bubble Sort\t%d\t%.2f ms\t%lld\t%lld\n",
           tamanho, tempo, comparacoes, movimentacoes);

    preencherDecrescente(v, tamanho);
    comparacoes = 0;
    movimentacoes = 0;

    inicio = clock();
    selectionSort(v, tamanho, &comparacoes, &movimentacoes);
    fim = clock();

    tempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;

    printf("Selection Sort\t%d\t%.2f ms\t%lld\t%lld\n",
           tamanho, tempo, comparacoes, movimentacoes);

    free(v);
}

int main() {
    printf("Algoritmo\tTamanho\tTempo\t\tComparacoes\tMovimentacoes\n");

    testarAlgoritmo(100);
    testarAlgoritmo(1000);
    testarAlgoritmo(10000);

    return 0;
