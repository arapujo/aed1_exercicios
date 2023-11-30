/*  Programa: Jogo de cartas que identifica triplas que somem 10
    Autor: Ana Araujo
    Versao: 1.0 - 14/11/2022
*/
#include <stdio.h>
#include <stdlib.h>
    
//lista duplamente encadeada
struct lista {
    int valor;
    struct lista *anterior;
    struct lista *proximo;
};  
typedef struct lista no;

//primeiro nó
no *primeiro = NULL;
//último nó
no *ultimo = NULL;
//tamanho da lista
int tam = 0;
    
//Funções

//insere no fim
int inserir_no_fim(int valor) {
    no *aux;
    aux = (no*)malloc(sizeof(no));
    
    //verifica alocação
    if(aux==NULL){
        return 0;
    
    } 
    //insere o valor na lista
    aux->valor = valor;
    
    aux->anterior = ultimo;
    aux->proximo = NULL;
    
    //lista só tem um elemento
    if(ultimo == NULL) {
        primeiro = aux;
    } else {
        ultimo->proximo = aux;
    }
    
    ultimo = aux;
    tam++;
    
    return 1;
}
    
//insere no ínicio
int insere_inicio(int valor){
    no *aux;
    aux = (no*)malloc(sizeof(no));

    //verifica alocação
    if(aux==NULL){
        return 0;
    
    } 
    //insere valor na lista
    aux->valor = valor;
    aux->anterior = NULL;
    aux->proximo = primeiro;
    
    //lista vazia
    if(primeiro == NULL) {
        ultimo = aux;
    } else {
        primeiro->anterior = aux;
    }
    
    primeiro = aux;
    tam++;
    return 1;
    
    
}
    
//insere em posição específica
int inserir_posicao(int valor, int posicao) {
    
    //insere no ínicio se posição igual a 0
    if(posicao==0){
        return insere_inicio(valor);
    }
    
    no *aux, *novo = (no*) malloc(sizeof(no));
    
    //verifica alocação
    if(novo==NULL){
        return 0;
    
    } 

    novo->valor = valor;
    aux = primeiro;
    
    int i = 0;
    
    //procura posição
    while((i < posicao-1) && aux->proximo!=NULL){
        aux = aux->proximo;
        i++;
    }
    
    novo->proximo = aux->proximo; 
    novo->anterior = aux; 
    
    if(aux->proximo!=NULL){
        aux->proximo->anterior = novo; 
    }
    
    aux->proximo = novo; 
    tam++;
    
    return 1;
    
}
    
//exclui nó especifico
int exclusao_posicao(int pos){
    no *aux = primeiro;
    no *anterior, *proximo;
    int i = 0;

    //lista vazia
    if(aux==NULL){
        return 0;
    }
    //percorre lista
    while(aux!=NULL){
        if(i==pos) break;
        i++;
        aux = aux->proximo;
    }
    if(i!=pos){
        return 0;
    }
    proximo = aux->proximo;
    anterior = aux->anterior;
    free(aux);

    if(anterior!=NULL){
        anterior->proximo = proximo;
    } else {
        primeiro = proximo;
    } 
    if(proximo!=NULL){
        proximo->anterior = anterior;
    } else {
        ultimo = anterior;
    }
    tam--;
    return 1;
    
}
    
//imprimi lista
void imprimir() {
    no *aux = primeiro;
    
    //verifica lista vazia
    if(tam==0){
        return;
    }
    
    do{
        printf("%d ", aux->valor);
        aux = aux->proximo;
    } while(aux != NULL);
    
    printf("\n");
    
}
    
//exlcui último nó
int exclui_ultimo(){
    no *aux;
    
    aux = ultimo;
    ultimo = ultimo->anterior;
    ultimo->proximo = NULL;
    free(aux); 
    tam--;
    return 1;
}
    
//exclui primeiro nó
int exclui_primeiro(){
    no *aux;
    
    aux = primeiro;
    primeiro = primeiro->proximo;
    primeiro->anterior = NULL;
    free(aux); 
    tam--;
    return 1;
}

//exclui valor específico
void exclui_num(int num) {
    no *aux = primeiro;
    
    int flag = 0;
    
    while(aux!=NULL){
        if(aux->valor == num){
            //primeiro elemento
            if(aux->anterior == NULL){
                primeiro = aux->proximo;
                primeiro->anterior = NULL;
            //ultimo elemento
            } else if (aux->proximo == NULL){
                ultimo = aux->anterior;
                ultimo->proximo = NULL;
            } else {
                aux->anterior->proximo = aux->proximo;
                aux->proximo->anterior = aux->anterior;
            }
            free(aux);
            flag = 1;
            break;
        }
        aux = aux->proximo;
    }
    if(flag == 0){
        return;
    }
    tam--;
}
    
//verifica triplas
int trio() {
    
    no *aux1 = primeiro;
    no *aux2, *aux3;
    int i = 0, ult = 0;
    
    if(tam<3){
        return 0;
    }
    
    //verifica primeira borda
    if(primeiro->valor + primeiro->proximo->valor + ultimo->valor == 10){
        exclui_num(primeiro->valor);
        exclui_num(primeiro->valor);
        exclui_ultimo();
        return 1;
    //verifica meio da lista
    } else{
        while(aux1!=NULL && i<tam-2){
        aux2 = aux1->proximo;
        aux3 = aux2->proximo;
        
        if(aux1->valor + aux2->valor + aux3->valor == 10){
            exclusao_posicao(i);
            exclusao_posicao(i);
            exclusao_posicao(i);
            return 1;
        }
    
        i++;
        aux1 = aux1->proximo;
        }
    }
    
    //verifica última borda
    if(primeiro->valor + ultimo->anterior->valor + ultimo->valor == 10){
        exclui_num(ultimo->anterior->valor);
        exclui_num(ultimo->valor);
        exclui_primeiro();
        return 1;
    }
    return 0;
}
    
//Programa principal
int main() {
    int jogada, posicao, valor, seq[10], i;
    
    //lê sequência
    for(i=0; i<10; i++){
        scanf("%d", &seq[i]);
        //verifica se num é válido
        if(seq[i] >= 0 && seq[i] < 10){
            inserir_no_fim(seq[i]);
        }
    }
    
    imprimir();
    //lê jogadas
    for(i=0; i<5; i++){
        scanf("%d %d", &jogada, &posicao);
        inserir_posicao(jogada, posicao);
        while(trio()==1){
            trio();
        }
        
        imprimir();
    }
    
    if(tam==0){
        printf("ganhou");
    } else {
        printf("perdeu");
    }
    
    return 0;
}