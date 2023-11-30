/*  Programa: Gerenciador de reservas de livros por RA
        Autor: Ana Araujo
    Versao: 1.0 - 06/12/2022
*/

//Bibliotecas externas
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10

//Estrutura de dados
//criação da lista estática
struct info {
    int valor;
    int prox;
};
typedef struct info tipoInfo;

struct listaEE {
    int tamanhoLista;
    int primeiro;
    int ultimo;
    int ano_2011;
    int ano_2012;
    int ano_2013;
    int ano_2014;
    int ano_2015;
    int ano_2016;
    int ano_2017;
    int ano_2018;
    // 0 ocupado, 1 livre
    struct info elemento[MAX];
};
typedef struct listaEE tipoListaEE;

//inicia lista
void inicializaLista (tipoListaEE *listaAux){ 
    // Inicializa elementos da lista
    int i;
    listaAux->tamanhoLista =0;
    listaAux->primeiro=-1;
    listaAux->ultimo=-1;
    for (i=0; i<MAX; i++){
        listaAux->elemento[i].valor=0;
        listaAux->elemento[i].prox=-1;
    }
}

//insere no final
int insereElementoOrdenado (tipoListaEE *listaAux, int posicao){ 

    int digito, ano, cont = 0; //conta qtd de digitos do ra

    int j, i = 0;

    if(listaAux->tamanhoLista >= MAX){
        printf("lista cheia\n");
        return 0;
    }

    //compara valor e acha posição
    while(i < listaAux->tamanhoLista && listaAux->elemento[i].valor < posicao){
        i++;
    }

    //desloca elementos da lista
    for(j=listaAux->tamanhoLista-1; j >= i; j--){
        listaAux->elemento[j+1] = listaAux->elemento[j];
    }

    //adiciona elemento na lista
    listaAux->elemento[i].valor = posicao;
    //atualiza a quantidade
    listaAux->tamanhoLista++;
    
    //recebe total de  digitos de um numero
    digito = contaDigitos(posicao);
    ano = verificaAno(listaAux, posicao);
    
    return 1;
}
        
//verifica ano
int verificaAno(tipoListaEE *listaAux, int num){
    int inicio_ra;
    inicio_ra = num;
   
    while(inicio_ra >= 1000){
        inicio_ra = inicio_ra / 1000;
    }
    //2011
    if(inicio_ra == 66){
        listaAux->ano_2011++;
    }
    //2012
    else if(inicio_ra == 76){
        listaAux->ano_2012++;
    }
    //2013
    else if(inicio_ra == 86){
        listaAux->ano_2013++;
    }
    //2014
    else if(inicio_ra == 96){
        listaAux->ano_2014++;
    }
    //2015
    else if(inicio_ra == 106){
        listaAux->ano_2015++;
    }
    //2016
    else if(inicio_ra == 116){
        listaAux->ano_2016++;
    }
    //2017
    else if(inicio_ra == 126){
        listaAux->ano_2017++;
    }
    //2018
    else if(inicio_ra == 136){
        listaAux->ano_2018++;
    }  
}

//conta digitos
int contaDigitos(int n){
    int count = 0;

    while(n != 0) {
        count++;
        n /= 10;
    }
    return count;
}

//procura elemento
int buscaItem(tipoListaEE *listaAux, int num){
int i = 0;
//compara número com valores da lista
while(i < listaAux->tamanhoLista){
    //retorna posição do num caso o encontre
    if(num == listaAux->elemento[i].valor){
        return i;
    } else {
        i++;
    }
}

//retorna -1 caso não haja o número na lista
    return -1;
}

 //exclui elemento da lista
    bool excluiItem(tipoListaEE *listaAux, int num){
        int pos, j;

         //verifica se lista está vazia
        if(listaAux->tamanhoLista == 0){
            return false;
        }

        //verifica se lista foi inicializada
        if(listaAux == NULL){
            return false;
        }

        //verifica se num existe na lista
        pos = buscaItem(listaAux, num);

        //caso não exista retorna -1
        if(pos == -1) return false;

        //caso o num exista
        for(j = pos; j < listaAux->tamanhoLista-1; j++){
            listaAux->elemento[j].valor = listaAux->elemento[j+1].valor;
        }

        //diminui em um o tamanho da lista
        listaAux->tamanhoLista--;
        return true;
    }

//exibi lista
void exibirLista(tipoListaEE *listaAux){
    int i;
    for(i=0; i<listaAux->tamanhoLista; i++){
        printf("%d ", listaAux->elemento[i].valor);
    }
    printf("\n");
}

int main(){

    tipoListaEE minhaLista;
    
    inicializaLista(&minhaLista);

    minhaLista.ano_2011 = 0;
    minhaLista.ano_2012 = 0;
    minhaLista.ano_2013 = 0;
    minhaLista.ano_2014 = 0;
    minhaLista.ano_2015 = 0;
    minhaLista.ano_2016 = 0;
    minhaLista.ano_2017 = 0;
    minhaLista.ano_2018 = 0;

    int l,  //qtd de movimentações
        i = 1,  //iterador
        ra, //num de ra
        num, //ra a ser excluido
        op, //op = 1 - reserva e op = 2 - retirada
        pos; //posição livre

    scanf("%d", &l);

    for(i=0; i<l; i++){
        scanf("%d", &op);
        if(op == 1){
            //reserva
            scanf("%d", &pos);
            insereElementoOrdenado(&minhaLista, pos);
             exibirLista(&minhaLista);
        } else {
            //retira
            scanf("%d", &num);
            if(excluiItem(&minhaLista, num)){
                 exibirLista(&minhaLista);
            } else {
                printf("nao existe\n");
                 exibirLista(&minhaLista);
            }
        }
    }
   
    printf("\n2011: %d", minhaLista.ano_2011);
    printf("\n2012: %d", minhaLista.ano_2012);
    printf("\n2013: %d", minhaLista.ano_2013);
    printf("\n2014: %d", minhaLista.ano_2014);
    printf("\n2015: %d", minhaLista.ano_2015);
    printf("\n2016: %d", minhaLista.ano_2016);
    printf("\n2017: %d", minhaLista.ano_2017);
    printf("\n2018: %d", minhaLista.ano_2018);

    return 0;
}