//IMPLEMENTAÇÃO DE UMA ÁRVORE PATRICIA
//TRABALHO REALIZADO EM DUPLA POR:
//PAULO CELSO DOS SANTOS JÚNIOR
//NICOLAS DOS SANTOS FERNANDES
//DISCIPLINA: ESTRUTURA DE DADOS II
//PROFESSOR: DANILLO ROBERTO PEREIRA

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

#define bits_na_chave 32

//ESTRUTURA BÁSICA DO NÓ DA ÁRVORE PATRICIA
typedef struct No{
    unsigned chave; //unsigned para garantir que o bit mais significativo seja sempre 0.
    int bit;
    struct No *esq, *dir;
} No;

//IDENTIFICAÇÃO DO K-ÉSIMO BIT PARA COMPARAÇÕES E DECISÃO DE DIREÇÕES DA ÁRVORE
unsigned bit(unsigned chave, int k){ //serve para retornar o k-ésimo bit da chave, da esqueda para a direita
    return chave >> (bits_na_chave - 1 - k) & 1;
}

//INICIALIZA A ÁRVORE COM UM NÓ DUMMY, UTILIZAMOS UINT_MAX PARA EVITAR COMPARAÇÕES INCORRETAS NO COMEÇO
void inicializaNo(No **arvore){ //Criação de um Dummy
    *arvore = malloc(sizeof(No));
    (*arvore)->chave = UINT_MAX; //Serve para garantir que a chave seja maior que qualquer outra chave
    (*arvore)->esq = (*arvore)->dir = *arvore;
    (*arvore)->bit = -1;
}

///////////////////////////////////////////////////////////////////
//A PARTIR DAQUI TEMOS AS FUNÇÕES DE BUSCA UTILIZADAS NO TRABALHO//
///////////////////////////////////////////////////////////////////

//FUNÇÃO QUE BUSCA UMA CHAVE NA ÁRVORE, UTILIADA DE FORMA RECURSIVA
//PECORRE A ÁRVORE COMPARANDO OS BITS DA CHAVE ATÉ ENCONTRAR O NÓ CORRESPONDETE OU NÓ COM BIT MENOR QUE W
No *busca_rec(No *arvore, unsigned chave, int w){
    if(arvore->bit <= w){
        return arvore;
    }if(bit(chave, arvore->bit) == 0){
        return busca_rec(arvore->esq, chave, arvore->bit);
    }else{
        return busca_rec(arvore->dir, chave, arvore->bit);
    }
}

//FUNÇÃO QUE UTILIZA DE FORMA ADEQUADA A "BUSCA_REC" PARA ENCONTRAR O NÓ COM A CHAVE PROCURADA
No *busca(No *arvore, unsigned chave){
    No *t = busca_rec(arvore, chave, -1);
    return t->chave == chave ? t : NULL; //Se a chave não for encontrada retorna NULL
}

//FUNÇÃO PARA MEDIR O COMPRIMENTO DA CHAVE INDICADA, É UMA FUNÇÃO AUXILIAR QUE AINDA NÃO DECIDIMOS COMO UTILIZAR AO CERTO
//POR ENQUANTO FICA AQUI EM STAND-BY
int comprimento(char *palavra){
    int i = 0;
    while(palavra[i] != '\0'){
        i++;
    }
    return i;
}
//////////////////////////////////////////////////////////////////////
//A PARTIR DAQUI TEMOS AS FUNÇÕES DE INSERÇÃO UTILIZADAS NO TRABALHO//
//////////////////////////////////////////////////////////////////////

//FUNÇÃO PARA INSERIR UMA NOVA CHAVE NA ÁRVORE, CRIA UM NOVO NÓ QUANDO NECESSÁRIO
//ELA INSERE A CHAVE NA ÁRVORE QUANDO ENCONTRA O BIT CORRETO ONDE DIVERGE DE OUTRAS CHAVES
//É A FUNÇÃO COM A LÓGICA PRINCIPAL PARA REALIZAR A INSERÇÃO
No *insere_rec(No *arvore, unsigned chave, int w, No *pai){
    No *novo;
    if ((arvore->bit >= w) || (arvore->bit <= pai->bit)){
        novo = malloc(sizeof(No));
        novo->chave = chave;
        novo->bit = w;
        if(bit(chave, novo->bit) == 1){
            novo->esq = arvore;
            novo->dir = novo;
        }else{
            novo->esq = novo;
            novo->dir = arvore;
        }
        return novo;
    }
    
    if(bit(chave, arvore->bit) == 0)
        arvore->esq = insere_rec(arvore->esq, chave, w, arvore);
    else
        arvore->dir = insere_rec(arvore->dir, chave, w, arvore);
    return arvore;
}

//FUNÇÃO PARA CHAMAR E UTILIZAR DE FORMA CORRETA A "INSERE_REC"
//UTILIZAMOS UM LOOP DE FOR PARA ENCONTRAR O PRIMEIRO BIT QUE A CHAVE DIFERE DE T E EM SEGUIDA UTILIZAMOS A INSERE_REC
void insere(No **arvore, unsigned chave){
    No *t = busca_rec((*arvore)->esq, chave, -1);
    if(chave == t->chave){
        return;
    }
    for(int i = 0; bit(chave, i) == bit(t->chave, i); i++){
        (*arvore)->esq = insere_rec((*arvore)->esq, chave, i, *arvore);
    }
}

/////////////////////////////////////////////////////////////////////
//A PARTIR DAQUI TEMOS AS FUNÇÕES DE REMOÇÃO UTILIZADAS NO TRABALHO//
/////////////////////////////////////////////////////////////////////

//FUNÇÃO QUE ENCONTRA O NÓ PAI E O NÓ A SER REMOVIDO PARA AJUSTAR CORRETAMENTE OS APONTAMENTOS
//É UMA FUNÇÃO AUXILIAR PARA REALIZAR A REMOÇÃO DEFINITIVA
No* busca_pai_rec(No* arvore, unsigned chave, No* pai, int w) {
    if (arvore->bit <= w) {
        return pai; //Retorna o nó pai
    }
    if (bit(chave, arvore->bit) == 0) {
        return busca_pai_rec(arvore->esq, chave, arvore, arvore->bit);
    } else {
        return busca_pai_rec(arvore->dir, chave, arvore, arvore->bit);
    }
}

//FUNÇÃO QUE LIDA COM A REMOÇÃO DA CHAVE DE FORMA A AJUSTAR A ÁVORE DE ACORDO COM O NECESSÁRIO
//É A FUNÇÃO COM A LÓGICA PRINCIPAL PARA REALIZAR A REMOÇÃO
No* remove_rec(No* arvore, unsigned chave, No* pai) {
    //Se chegarmos/voltarmos ao nó Dummy a função para
    if (arvore == pai || arvore->chave == UINT_MAX) {
        return NULL;
    }

    //Se por acaso o nó encontrado não corresponde à chave
    if (arvore->chave != chave) {
        return arvore;  //A chave não está na árvore então retornamos a árvore como está
    }

    //Removendo a chave e ajustando a árvore
    if (arvore == arvore->esq && arvore == arvore->dir) {
        free(arvore); //Se o Nó é folha, pode ser removido diretamente  
        return NULL;
    }

    //Substituir o nó removido
    if (arvore->esq == arvore) {
        return arvore->dir; //Retorna o filho direito
    } else {
        return arvore->esq; //Retorna o filho esquerdo
    }
}

//FUNÇÃO QUE REALMENTE REALIZA A REMOÇÃO UTILIZANDO AS DUAS ULTIMAS FUNÇÕES AUXILIARES
void remover(No** arvore, unsigned chave) {
    No* pai = busca_pai_rec(*arvore, chave, NULL, -1);
    if (pai == NULL) {
        printf("Chave %u não encontrada.\n", chave);
        return;
    }
    
    No* removido = remove_rec(*arvore, chave, pai);
    if (removido != NULL) {
        if (pai->esq == removido) {
            pai->esq = removido;
        } else {
            pai->dir = removido;
        }
    } else {
        printf("Chave %u removida com sucesso.\n", chave);
    }
}

///////////////////////////////////////////////////////////////////////
//A PARTIR DAQUI TEMOS AS FUNÇÕES DE IMPRESSÃO UTILIZADAS NO TRABALHO//
///////////////////////////////////////////////////////////////////////

//FUNÇÃO DE IDENTAÇÃO, UTILIZADA PARA ORGANIZAR A ÁRVORE DE MANEIRA HIERÁRQUICA NA TELA
void imprime_espacos(int nivel) {
    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }
}

//FUNÇÃO RECURSIVA QUE PERCORRE A ÁRVORE. IMPRIME A CHAVE E O BIT ATUAL DO NÓ FAZENDO CHAMADAS RECURSIVAS. "NIVEL" É UTILIZADO PARA CONTROLAR IDENTAÇÃO
void imprime_rec(No *arvore, int nivel) {
    //Caso de um nó nulo | árvore ou subárvore vazia
    if (arvore == NULL || arvore->chave == UINT_MAX) {
        return;
    }

    imprime_espacos(nivel); //Imprime espaços com base no nível da árvore
    printf("Nó: Chave = %u, Bit = %d\n", arvore->chave, arvore->bit); //Imprime a chave e o bit do nó

    //Recursão para os filhos
    imprime_espacos(nivel);
    printf("Esquerda:\n");
    imprime_rec(arvore->esq, nivel + 1);

    imprime_espacos(nivel);
    printf("Direita:\n");
    imprime_rec(arvore->dir, nivel + 1);
}

//FUNÇÃO DE IMPRESSÃO PRINCIPAL
void imprime_arvore(No *arvore) {
    printf("Imprimindo a árvore Patricia:\n");
    imprime_rec(arvore, 0);  //Começa a impressão no nível 0
}