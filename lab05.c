/*  Programa: Fila de tarefas utilizando fila estática circular
    Autor: Ana Araujo
    Versao: 1.0 - 17/11/2022
*/

//bibliotecas externas
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

//estrutura fila estática circular
struct filaCircular{
    int primeiro;
    int ultimo;
    int tamanhoFila;
    int elementos[MAX];
}; typedef struct filaCircular tipoFC;

//funções
//inicializa fila
void inicializaFila(tipoFC *filaAux){
    int i;
    filaAux->primeiro = -1;
    filaAux->ultimo = -1;
    filaAux->tamanhoFila = 0;
    for(i=0;i<MAX;i++){
        filaAux->elementos[i]=0;
    }
}

//verifica se está fila vazia
int filaVazia(tipoFC *filaAux){
    if((filaAux->primeiro==filaAux->ultimo) && (filaAux->ultimo==-1)){
        //fila vazia
        return 1;
    } else {
        return 0; //fila não vazia
    }        
}

//insere elemento
int insereElemento (tipoFC *filaAux, int info){ 
  
    //fila cheia
    if(filaAux->tamanhoFila >= MAX) {
        return 0;
    }

    // se a fila estiver vazia insere o primeiro elemento
    if (filaVazia(filaAux)==1){
        filaAux->primeiro = 0;
        filaAux->ultimo = 0;
        filaAux->elementos[0]=info;
        filaAux->tamanhoFila++;
        return 1;
    } 
    else { 
    // se a fila não estiver cheia
        int posicao = ((filaAux->ultimo + 1) % MAX);
        filaAux->elementos[posicao] = info;
        filaAux->ultimo = posicao;
        filaAux->tamanhoFila++;
        return 1;
    }  
}

int removeElemento(tipoFC *filaAux){
    int i;

    if (filaAux->tamanhoFila == 0){
        printf("vazia\n");
        return 0;
    } else {
        //remove primeiro elemento e ajusta espaço
        int primeiro = filaAux->primeiro;
        filaAux->elementos[(primeiro) % MAX] = 0;
        filaAux->tamanhoFila--;
        //desloca elementos
        for(i=filaAux->primeiro; i<filaAux->ultimo; i++){
            filaAux->elementos[i] = filaAux->elementos[i+1];
        }

        //atualiza último e ajusta espaço
        int ultimo = filaAux->ultimo;
        filaAux->elementos[(ultimo) % MAX] = 0;
        filaAux->ultimo--;
    }
 
}

//desloca primeiro elemento para o final
int trocarPosicao(tipoFC *filaAux){

    //lista vazia
    if(filaAux->tamanhoFila == 0){
        printf("vazia\n");
        return 0;
    } else {
        //encontra o primeiro
        int primeiro = filaAux->primeiro;
        //encontra o último
        int ultimo = filaAux->ultimo;
        int temp = filaAux->elementos[(primeiro) % MAX];
        filaAux->elementos[filaAux->primeiro] = 0;
        filaAux->primeiro = ((primeiro + 1) % MAX);
        filaAux->ultimo = ((ultimo + 1) % MAX);
        filaAux->elementos[filaAux->ultimo] = temp;
        return 1;
    }
}

int exibirFila(tipoFC *filaAux){
    int i = 1;
    int aux = filaAux->primeiro;
    //fila vazia
    if (filaAux->tamanhoFila == 0){
        return 0;
    } else {
        for (i=filaAux->ultimo; i!=filaAux->primeiro; i--){
        printf("%d ", filaAux->elementos[i]);
    }
    //exibie o primeiro elemento pois o loop termina antes
    printf("%d", filaAux->elementos[(aux) % MAX]);
    printf("\n");
    }
}

//programa principal
int main() {

    //declara fila
    tipoFC minhaFila;

    inicializaFila(&minhaFila);

    int id, //id da tarefa
        i,  //iterador
        qtd, //qtd de operações
        op; //op=1 - insere, op=2 - remove e op=3 - troca

    scanf("%d", &qtd);

    for(i=0; i<qtd; i++){
        scanf("%d", &op);
        if(op==1){
            scanf("%d", &id);
            insereElemento(&minhaFila, id);
        } else if(op==2){
            removeElemento(&minhaFila);
        } else{
            trocarPosicao(&minhaFila);
        }
    }
   
    exibirFila(&minhaFila);
    
    return 0;
}