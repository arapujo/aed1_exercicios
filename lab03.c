/*  Programa: Gerenciador de produtos de mercado
        Autor: Ana Araujo
    Versao: 1.0 - 05/11/2022
*/

//Bibliotecas externas
#include <stdio.h>
#include <stdlib.h>
        
//Estrutura de dados
//criação da lista encadeada
typedef struct no{
    int id; //produto;
    float preco;
    float lucro;
    int qtd_compra;
    int qtd;
    struct no *proximo; //ponteiro para o nó seguinte
}No;

int tamanhoLista = 0;

//Funções 
//inserir em ordem decrescente
void insere_ordenado(No **lista, int id, int qtd, float preco){
    No *aux, *novo = malloc(sizeof(No));
        
    //verifica se a alocação ocorreu certo
    if(novo){
        //insere dados na lista
        novo->id = id;
        novo->preco = preco;
        novo->qtd = qtd;
        novo->qtd_compra = 0;
        // a lista está vazia?
        if(*lista == NULL){
            novo->proximo = NULL;
            *lista = novo;
        } //preço é o maior?
        else if(novo->preco > (*lista)->preco){
            novo->proximo = *lista;
            *lista = novo;
        }
        else{
            aux = *lista;
            //preco do 1º no nao e maior que o id a ser inserido
            while(aux->proximo && novo->preco < aux->proximo->preco)
            aux = aux->proximo;
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }

        tamanhoLista++;
    }
        
}
        
//verifica se produto existe
No* busca_produto(No **lista, int num){
    No *aux, *no = NULL;
        
    aux = *lista;
        
    //percorre lista
    while(aux && aux->id != num){
        aux = aux->proximo;
    }

    if(aux != NULL){
        no = aux;
    }
        
    return no;
}
            
//remove produto
No* remove_produto(No **lista, int num){
    No *aux, *remove_produto = NULL;

    if(*lista != NULL){
    //no a ser removido é o 1º da lista
        if((*lista)->id == num){
            remove_produto = *lista;
            *lista = remove_produto->proximo;
        } 
        else{
            aux = *lista;
            while(aux->proximo && aux->proximo->id != num){
                aux = aux->proximo;
            }
            //id do proximo é o id a ser removido
            if(aux->proximo){// 
                remove_produto = aux->proximo;
                aux->proximo = remove_produto->proximo;
            }
        }
    }
        
    tamanhoLista--;
    return remove_produto;
}
        
//atualiza quantidade
void atualiza_quantidade(No **lista, int id, int qtd){
    No *novo = malloc(sizeof(No));
        
    No *aux, *no = NULL;
        
    aux = *lista;
        
    int qtd_aux;
        
    //percorre lista
    while(aux != NULL){
        if(id == aux->id){
            //adiciona qtd
            qtd_aux = aux->qtd += qtd; 
            novo->qtd = qtd_aux;   
        }
        aux = aux->proximo;   
    }     
}
        
//verifica se qtd é igual a 0
int verifica_qtd(No **lista, int id){
    No *aux, *no = NULL;

    aux = *lista;
        
    if(id == aux->id && aux->qtd == 0){
        return 0; 
    } else {
        return 1;
    }
        
}
        
//realiza a compra
int realiza_compra(No **lista, int id){
    No *novo = malloc(sizeof(No));
        
    No *aux, *no = NULL;
        
    aux = *lista;
        
    int qtdCompra_aux, compra_aux;
            
    while(aux!=NULL){
        if(id == aux->id){
            //incrementa qtd
            qtdCompra_aux = aux->qtd_compra++; 
            //adiciona qtd de compra na lista
            novo->qtd_compra = qtdCompra_aux;
            //qtd de produto - qtd de compra
            compra_aux = aux->qtd - aux->qtd_compra;
            aux->qtd = compra_aux + 1;
            novo->qtd = compra_aux;   
        }
            
        aux = aux->proximo;   
    }     
        
}
        
//calcula o lucro
int lucro_produto(No **lista, int id){
    No *novo = malloc(sizeof(No));
        
    No *aux, *no = NULL;
        
    aux = *lista;
            
    while(aux != NULL){
        if(id == aux->id){
            aux->lucro = aux->preco * aux->qtd_compra;
            novo->lucro = aux->lucro;    
        }
        aux = aux->proximo;   
    }     
        
}
        
//verifica se há lucro
int verifica_lucro(No **lista){
    No *novo = malloc(sizeof(No));
        
    No *aux, *no = NULL;
        
    aux = *lista;
        
    float lucro_aux;
    
    while(aux!=NULL){
        //se qtd de compra for 0 então lucro igual a 0
        if(aux->qtd_compra == 0){
            aux->lucro = 0;
            novo->lucro = aux->lucro;
        }
        aux = aux->proximo;   
    }     
}
        
//imprimi lista
void imprimi_lista(No *no){
    while(no != NULL){
        printf("%d %f\n", no->id, no->lucro);
        no = no->proximo;
    }
}
        
//libera lista
void libera_lista(No **lista){
    No *temp;

    while(*lista != NULL){
        temp = *lista;
        (*lista) = (*lista)->proximo;
        free(temp);
    }
}

//Programa principal
int main(){
        
    int l, //qtd de movimentações
        i, //iterador
        op, //opção escolhida
        id, //id do produto
        qtd_nova, //qtd nova do produto
        qtd_verificada, //qtd verificada
        qtd; //qtd do produto
                
    float preco; //valor do produto
        
    //inicia lista e nós auxiliares
    No *buscado, *removido, *lista = NULL;
        
    //printf("Insira a qtd de movimentacoes: ");
    scanf("%d", &l);
        
    if(l >= 1 && l <= 100){
        for(i=0; i<l; i++){
            scanf("%d", &op);
            //insercao
            if(op == 1){
                scanf("%d %d %f", &id, &qtd, &preco);
                //verifica se produto já existe
                buscado = busca_produto(&lista, id);
                if(buscado){
                    printf("ja existe\n");
                } else {
                    insere_ordenado(&lista, id, qtd, preco);
                }
                //atualiza_quantidade qtd
            } else if(op == 2){
                scanf("%d %d", &id, &qtd_nova);
                //verifica se produto existe
                buscado = busca_produto(&lista, id);
                if(buscado){
                    atualiza_quantidade(&lista, id, qtd_nova);
                } else {
                    printf("nao existe\n");
                }
            } 
            //compra
            else if(op == 3){
                scanf("%d", &id);
                buscado = busca_produto(&lista, id);
                qtd_verificada = verifica_qtd(&lista, id);
                //verifica se produto existe e se qtd é igual a 0
                if(buscado && qtd_verificada){
                //atualiza_quantidade a qtd de compra
                realiza_compra(&lista, id); 
                    //calcula o lucro
                    lucro_produto(&lista, id);
                } else {
                    printf("nao existe\n");
                }
            }   
            //remoção
            else if(op == 4 ) {
                scanf("%d", &id);
                //verifica se produto existe
                buscado = busca_produto(&lista, id);
                if(buscado){ 
                    remove_produto(&lista, id);
                    free(removido);
                } else {
                    printf("nao existe\n");
                } 
                
            }   
        
        }
    }
        
    //altera lucro se qtd for igual a o
    verifica_lucro(&lista);
    //exibi lista
    imprimi_lista(lista);
    //libera lista
    libera_lista(&lista);
    return 0;
}