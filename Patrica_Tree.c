#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

#define bits_na_chave 32

typedef struct No{
    unsigned chave; //unsigned para garantir que o bit mais significativo seja sempre 0.
    int bit;
    struct No *esq, *dir;
} No;

unsigned bit(unsigned chave, int k){ //serve para retornar o k-ésimo bit da chave 
    return chave >> (bits_na_chave - 1 - k) & 1;
}

void inicializaNo(No **arvore){ //Criação de um Dummy
    *arvore = malloc(sizeof(No));
    (*arvore)->chave = UINT_MAX; //Serve para garantir que a chave seja maior que qualquer outra chave
    (*arvore)->esq = (*arvore)->dir = *arvore;
    (*arvore)->bit = -1;
}

int comprimento(char *palavra){
    int i = 0;
    while(palavra[i] != '\0'){
        i++;
    }
    return i;
}

No *InserirNo(No *arvore, unsigned chave, int w, No *pai){
    No *novo;
    if((arvore->bit >= w) || (arvore->bit <= pai->bit)){
        novo = malloc(sizeof(No));
        novo->chave = chave;
        novo->bit = w;
        if(bit(chave, novo->bit) == 1){
            novo->dir = novo;
            novo->esq = arvore;
        }else{
            novo->esq = novo;
            novo->dir = arvore;
        }
        return novo;
    }if(bit(chave, arvore->bit) == 0){
        arvore->esq = insere_rec(arvore->esq, chave, w, arvore);
    }else{
        arvore->dir = insere_rec(arvore->dir, chave, w, arvore);
    }
    return arvore;
}

void insere(No **arvore, unsigned chave){
    No *t = busca_rec((*arvore)->esq, chave, -1);
    if(chave == t->chave){
        return;
    }
    for(int i = 0; bit(chave, i) == bit(t->chave, i); i++){
        (*arvore)->esq = insere_rec((*arvore)->esq, chave, i, *arvore);
    }
}
