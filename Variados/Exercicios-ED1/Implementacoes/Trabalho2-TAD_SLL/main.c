#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaSL.h"

int main() {
    //declaracoes de funcoes a serem utilizadas
    Aluno * criarAluno(ListaSL *lista);
    void listarAlunos(ListaSL *lista);
    
    //variaveis do programa
    int tam, opcao, status, ID;
    Aluno *item;
    ListaSL *lista;
    
    //criando lista...
    lista = createListaSL();
    
    //loop principal
    while (1) {
        //menu de opcoes
        printf("\n1- Adicionar aluno (Pilha) \n2- Adicionar aluno (Fila) \n3- Remover aluno por ordem de insercao \n4- Remover aluno X \n5- Consultar aluno X \n6- Listar todos os alunos\n7- Tamanho da lista \n8- Sair \n-->");
        scanf("%d", &opcao);
        //executando opcoes
        if (opcao == 1) {
            item = criarAluno(lista);
            //se deu tudo certo na criação do aluno, entao...
            if (item != NULL) {
                //verificando inserção do item na lista
                status = insertSLStack(lista, item);
                if (status == 1) {
                    printf("\nO aluno de ID %d foi inserido na lista com sucesso!\n", item->ID);
                } else {
                    printf("\nErro ao adicionar o aluno de ID %d na lista...\n", item->ID);
                }
            } else {
                printf("\nErro ao criar aluno! Verifique os dados e tente novamente...\n");
            }
        } else if (opcao == 2) {
            item = criarAluno(lista);
            //se deu tudo certo na criação do aluno, entao...
            if (item != NULL) {
                //verificando inserção do item na lista
                status = insertSLQueue(lista, item);
                if (status == 1) {
                    printf("\nO aluno de ID %d foi inserido na lista com sucesso!\n", item->ID);
                } else {
                    printf("\nErro ao adicionar o aluno de ID %d na lista...\n", item->ID);
                }
            } else {
                printf("\nErro ao criar aluno! Verifique os dados e tente novamente...\n");
            }
        } else if (opcao == 3) {
            item = removeSL(lista);
            if (item != NULL) {
                printf("\nAluno de ID %d removido da lista com sucesso!\n", item->ID);
            } else {
                printf("\nErro ao remover aluno da lista...\n");
            }
        } else if (opcao == 4) {
            printf("\nInforme o ID do aluno: ");
            scanf("%d", &ID);
            item = removeStudent(lista, ID);
            if (item != NULL) {
                printf("\nAluno de ID %d removido da lista com sucesso!\n", item->ID);
            } else {
                printf("\nErro ao remover aluno da lista...\n");
            }
        } else if (opcao == 5) {
            printf("\nInforme o ID do aluno: ");
            scanf("%d", &ID);
            item = searchStudent(lista, ID);
            if (item != NULL) {
                printf("\nAluno encontrado com sucesso!\n");
                printf("Nome: %s", item->nome);
                printf("\nID: %d", item->ID);
                printf("\nMedia das notas: %f\n", item->media);
            } else {
                printf("\nAluno nao foi encontrado...\n");
            }
        } else if (opcao == 6) {
            //verificando se a lista tem elementos
            if (lista->primeiro != NULL) {
                listarAlunos(lista);
            } else {
                printf("\nLista de alunos vazia ou inexistente!\n");
            }
        } else if (opcao == 7) {
            tam = sizeListaSL(lista);
            printf("\nTamanho atual da lista: %d\n", tam);
        } else if (opcao == 8) {
            if (slDestroy(lista)) {
                printf("\nEncerrando programa...\n");
                break;
            } else {
               printf("\nVerifique se a lista esta vazia!\n"); 
            }
        } else {
            printf("\nSinto muito! Opcao invalida!!!\n");
        }
    }
    
    system("pause");
    return 0;
}
/*
    Função que irá criar uma struct do tipo aluno e preenche-la com dados
    Argumentos: nenhum
    Retorno: devolve um ponteiro para a estrutura criada e preenchida
*/
Aluno * criarAluno(ListaSL *lista) {
    //declaracao de funcao extra a ser utilizadas
    int existeID(ListaSL *lista, int ID);
    
    //verificando lista
    if (lista != NULL) {
        //criando aluno
        Aluno *item = (Aluno *) malloc(sizeof(Aluno));
        //preenchendo dados do aluno
        printf("\nNome do aluno: ");
        scanf("%s", item->nome);
        printf("\nID do aluno: ");
        scanf("%d", &item->ID);
        printf("\nMedia das notas do aluno: ");
        scanf("%f", &item->media);
        //devolvendo aluno com seus dados, se tiver ID válido (não repetido)
        if (!existeID(lista, item->ID)) {
            return item;
        }
    }
    return NULL;
}
/*
    Função que irá listar os elementos de uma lista na ordem de inserção (do ultimo ao mais antigo)
    Argumentos: uma lista qualquer (com elementos)
    Retorno: nenhum, apenas imprime na tela as informações
*/
void listarAlunos(ListaSL *lista) {
    NodeSL *nodeAtual = lista->primeiro;
    //percorrendo lista e imprimindo informacoes dos alunos
    printf("\n+++++ LISTA DE ALUNOS +++++\n");
    while (nodeAtual != NULL) {
        printf("\n------------------------------\n");
        printf("Nome do aluno: %s\n", nodeAtual->item->nome);
        printf("ID do aluno: %d\n", nodeAtual->item->ID);
        printf("Media do aluno: %f\n", nodeAtual->item->media);
        printf("------------------------------\n");
        //atualizando node da lista
        nodeAtual = nodeAtual->proximo;
    }   
}
/*
    Função que serve para verificar se o ID está ou não presente em algum item da lista
    Argumentos: uma lista qualquer e um inteiro representando o ID
    Retorno: devolve 1 (TRUE) se houver um ID igual na lista e 0 (FALSE) caso contrário
*/
int existeID(ListaSL *lista, int ID) {
    NodeSL *nodeAtual;
    //verificando se a lista é válida
    if (lista != NULL) {
        //verificando se lista não está vazia
        if (lista->primeiro != NULL) {
            //iniciando busca por aluno com o ID informado
            nodeAtual = lista->primeiro;
            while (nodeAtual != NULL) {
                if (nodeAtual->item->ID == ID) {
                    return 1; //TRUE, já existe um aluno com esse ID
                }
                nodeAtual = nodeAtual->proximo;
            }
        }
    }
    return 0; //FALSE, não existe um aluno com esse ID
}
