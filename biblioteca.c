    /*  Programa: Gerenciador de reservas de bibliotecas
        Autor: Ana Araujo
        Versao: 1.0 - 08/10/2022
    */
     
    //Bibliotecas externas
    #include <stdio.h>
    #include <stdlib.h>
    #include<stdbool.h>
    #define MAX 10
     
    //Lista estática sequencial
     struct lista {
        int ultimo;
        int reservas;
        int tamanhoLista;
        int lista[MAX];
    };
    typedef struct lista tipolistaBiblioteca;
     
    //Funções
    //inicia a lista
    void iniciaLista(tipolistaBiblioteca *listaAux){
        int i;
        //zera a lista
        listaAux->tamanhoLista = 0;
        for(i=0; i<MAX; i++){
            listaAux->lista[i] = 0 ;
            //inicializa o último
        }
        listaAux->ultimo = 0;
        listaAux->reservas = 0; 
    }
     
    //insere elemento no final da lista
    void insereFinal(tipolistaBiblioteca *listaAux, int num_livro){
        int i;
        //atualiza a lista
            listaAux->tamanhoLista++;
     
        //se a lista não estiver cheia
        if(listaAux->tamanhoLista <= MAX){
            //atualiza qtd de reservas
            listaAux->reservas++;
            //insere elemento ao final da lista
            listaAux->lista[listaAux->tamanhoLista-1] = num_livro;
            //atualiza o último
            listaAux->ultimo = listaAux->tamanhoLista-1;
            printf("Sua reserva foi realizada\n");
        } else {
            //lista cheia
            printf("Lista de reserva cheia\n");
        }
    }
     
    //procura elemento na lista
    int buscaItem(tipolistaBiblioteca *listaAux, int num){
        int i = 0;
        //compara número com valores da lista
        while(i < listaAux->tamanhoLista){
            //retorna posição do num caso o encontre
            if(num == listaAux->lista[i]){
                return i;
            } else{
                i++;
            }
        }
        //retorna -1 caso não haja o número na lista
        return -1;
    }
     
    //exclui elemento da lista
    bool excluiItem(tipolistaBiblioteca *listaAux, int num){

        //lista  vazia
        if(listaAux == NULL || listaAux->tamanhoLista == 0){
            return false;
        }
        int pos, j;
        //verifica se num existe na lista
        pos = buscaItem(listaAux, num);
        //caso não exista retorna -1
        if(pos == -1) return false;
        //caso o num exista
        for(j = pos; j < listaAux->tamanhoLista-1; j++){
            listaAux->lista[j] = listaAux->lista[j+1];
        }
        //diminui em um o tamanho da lista
        listaAux->tamanhoLista--;
        return true;
    }
     
    //retorna tamanho da lista
    int tamanho_lista(tipolistaBiblioteca *listaAux){
        return listaAux->tamanhoLista;
    }

    int imprime(tipolistaBiblioteca *listaAux){
        int i;

        for(i=0; i < listaAux->tamanhoLista; i++){
            printf("%d ", listaAux->lista[i]);
        }
        printf("\n");
    }
     
    //Principal
    int main(){
     
        tipolistaBiblioteca minhaLista;
     
        int i,    //iterador
            l,    //número de reservas
            num_livro, //num do livro
            op,   //op = 1 : reserva e op = 2 retirada
            reservas = 0, //qtd de reservas
            retiradas = 0; //qtd de retiradas
     
        iniciaLista(&minhaLista);
     
        //lê número de reservas que o usuário deseja
        scanf("%d", &l);
            for(i=0; i<l; i++){
                scanf("%d %d", &op, &num_livro);
                //opção de rerserva
                if(op == 1){
                    insereFinal(&minhaLista,  num_livro);
                //opção de retirada
                } else {
                    if(excluiItem(&minhaLista, num_livro)){
                        //reserva sucedida
                        printf("O livro foi retirado com sucesso\n");
                        retiradas++;
                        //reserva não sucedida
                    } else {
                        printf("Voce nao possui reserva desse livro\n");
                    }
                }
            }
            imprime(&minhaLista);
            printf("Voce realizou %d reservas e %d retiradas\n", minhaLista.reservas, retiradas);

        return 0;
    }