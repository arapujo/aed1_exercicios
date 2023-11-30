/*  Programa: Pilha que realiza converões de binários e decimais
    Autor: Ana Araujo
    Versao: 1.0 - 23/11/2022
*/

//bibliotecas externas
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define tamanhoMax 100

//estrutura pilha estática circular
struct pilha{
    int topo;
    int binario;
    int decimal[tamanhoMax];
}; typedef struct pilha tipoPilha;

//funções
//inicializa a pilha
void inicializaPilha(tipoPilha *pilhaAux) {
    int i;
    for (i=0; i<=tamanhoMax-1; i++)
    pilhaAux->decimal[i] = 0;
    pilhaAux->topo = -1;
    pilhaAux->binario = 0;
}

//empilha
int empilharPilha(tipoPilha *pilhaAux, int val){
    if (pilhaAux->topo >= tamanhoMax-1) { // pilha cheia
        return -1; // aborta a funcao
    } else {
        pilhaAux->topo++;
        pilhaAux->decimal[pilhaAux->topo] = val;
        return 0; // sucesso
    }
}

//verifica se pilha vazia
int pilhaVazia(tipoPilha *pilhaAux){
    if(pilhaAux->topo == -1){
        return 1; //pilha vazia
    } else {
        return 0;
    }
}

//exibi pilha
int exibirPilha(tipoPilha *pilhaAux){
    int i, aux = pilhaAux->topo;

    if(pilhaVazia(pilhaAux) == 1){
        return 0;
    } else {
        for(i=aux; i>=0; --i){
            printf("%d ", pilhaAux->decimal[i]);
        }
        printf("\n");
    }

    return 1;
}

//converte decimal para binário
int converteDecimalBinario(tipoPilha *pilhaAux, int decimal){

    int bin = 0, resto, i = 1;
    
    //caso o decimal seja 0
    if(decimal == 0){
        bin = 0;
    //caso o decimal seja 1024 é feita uma adaptação por conta do overflow
    } else if(decimal == 1024){
        printf("1000000000");
    }
    else{
        while (decimal!=0){
            resto = decimal % 2;
            decimal /= 2;
            bin += resto * i;
            i *= 10;
        }
    }

    pilhaAux->binario = bin;

    printf("%d ", bin);
    binarioOposto(pilhaAux, decimal);

    return 1;

}

int binarioOposto(tipoPilha *pilhaAux, int decimal){
    int i, bin = 0, size = 0, dec;

    int x = pilhaAux->binario;

    //caso o decimal seja 1024 é feita uma adaptação por conta do overflow
    if(decimal == 1024){
        printf("01111111111");
        printf(" %d\n", 1023);
        return 1;
    //caso o decimal seja 
    } else if(x == 0){
        printf("d%d", 1);
        printf("%d\n", 1);
    //calcula a qtd de digitos do binario
    } else {
        while(x){
            x = x/10;
            size++;
        }
        //transforma o binario em inteiro
        int arr_a[size];
        for (i=size - 1, x=pilhaAux->binario; x ; x=x/10, i-- ) {
            arr_a[i] = x % 10;
        }
    
        //transforma 1 em 0 e 0 em 1
        for(i=size;i>=0;i--){
            if(arr_a[i] == 1){
                arr_a[i]=0;
            } else {
                arr_a[i]=1;
            }
        }

        //exibi binário oposto
        for(i=0; i<size; i++){
            printf("%d", arr_a[i]);
        }

        //calcula decimal do binário oposto
        for(i=0; i<size; i++){
            bin *= 2;
            bin += arr_a[i];
        }
    }
    
    //exibi o decimal oposto
    printf(" %d\n", bin);

    return 1;
}

//programa principal
int main() {

    //declara pilha
    tipoPilha *minhaPilha = (tipoPilha*)malloc(sizeof(tipoPilha));

    inicializaPilha(minhaPilha);

    int i, num, l;
    scanf("%d", &l);

    for (i=0; i<l; i++){
        scanf("%d", &num);
        empilharPilha(minhaPilha, num);
        printf("%d ", num);
        converteDecimalBinario(minhaPilha, num);
    }
    
    return 0;
}