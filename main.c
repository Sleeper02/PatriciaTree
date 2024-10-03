#include <stdio.h>
#include <stdlib.h>
#include "Patricia_Tree.c"

int main(){

    No *arvore;
    
    inicializaNo(&arvore);

    //Inserção de algumas chaves binárias para teste
    printf("Inserindo algumas chaves\n");
    insere(&arvore, "1010");  
    insere(&arvore, "11001");
    insere(&arvore, "1000");
    insere(&arvore, "11110");

    //Impressão da árvore após as inserções
    printf("Após as inserções:\n");
    imprime_arvore(arvore);

    //Testando a busca de chaves binárias
    const char *chave_para_buscar = "11001";
    printf("\nBuscando a chave binária %s na árvore\n", chave_para_buscar);
    unsigned chave_binaria_convertida = converte_binario_para_int(chave_para_buscar); // Converte a chave
    No *resultado = busca(arvore, chave_binaria_convertida);
    if (resultado != NULL) {
        printf("Chave %u encontrada!\n", resultado->chave);
    } else {
        printf("Chave binária %s não encontrada!\n", chave_para_buscar);
    }

    //Removendo uma chave binária
    const char *chave_para_remover = "1010";
    printf("\nRemovendo a chave binária %s da árvore\n", chave_para_remover);
    unsigned chave_para_remover_convertida = converte_binario_para_int(chave_para_remover); // Converte a chave
    remover(&arvore, chave_para_remover_convertida);

    //Impressão da árvore após a remoção
    printf("Árvore após remoção da chave binária %s:\n", chave_para_remover);
    imprime_arvore(arvore);

    return 0;
}