#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

typedef struct No{
    char chave; //Mais facil de verificar se a chave é igual outra pelos bits
    int bit;
    struct No *esq, *dir;
} No;

void inicializaNo(No **arvore){ //Criação de um Dummy
    *arvore = malloc(sizeof(No));
    (*arvore)->chave = CHAR_MAX; //Serve para garantir que a chave inicial seja um valor muito alto, que provavelmente não será usado em operações normais com a árvore.
    (*arvore)->esq = (*arvore)->dir = *arvore;
    (*arvore)->bit = -1;
}

No *busca_rec(No *arvore, unsigned chave, int w){
    if(arvore->bit <= w){
        return arvore;
    }if(bit(chave, arvore->bit) == 0){
        return busca_rec(arvore->esq, chave, arvore->bit);
    }else{
        return busca_rec(arvore->dir, chave, arvore->bit);
    }
}

No *busca(No *arvore, unsigned chave){
    No *t = busca_rec(arvore, chave, -1);
    return t->chave == chave ? t : NULL;
}

int comprimento(char *palavra){
    int i = 0;
    while(palavra[i] != '\0'){
        i++;
    }
    return i;
}

