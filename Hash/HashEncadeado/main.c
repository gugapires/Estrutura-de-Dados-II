#include <stdio.h>
#include <stdlib.h>

typedef struct aluno {
	int mat;
	char nome;
	aluno *prox;
}Aluno;

typedef struct hash {
	int qtd, TABLE_SIZE;
	Aluno **itens; 
}Hash;


Hash* criaHash(int TABLE_SIZE) {
    Hash* ha = (Hash*)malloc(sizeof(Hash));
    int i;
    if (ha != NULL) {
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->itens = (int*)malloc(TABLE_SIZE * sizeof(int));

        if (ha->itens == NULL) {
            free(ha);
            return 0;
        }
        ha->qtd = 0;
        for (i = 0; i < ha->TABLE_SIZE; ++i){
            ha->itens[i] = NULL;
        }
    }
    return ha;
}

int chaveDivisao(int chave, int TABLE_SIZE) {
    return (chave % TABLE_SIZE);
}

int buscaHash(Hash* ha, int mat) {
    if (ha == NULL) {
        return 0;
    }
    int pos = chaveDivisao(mat, ha->TABLE_SIZE);
    if (ha->itens[pos] == NULL) {
        return 0;
    }
    Aluno aux;
    aux = ha->itens[pos];
    do {
        if (aux.mat == mat) {
                return 1;
        }
        aux = aux.prox;
    }while(aux != NULL);
    return 0;
}

int insereHash(Hash* ha, Aluno al) {
    if (ha == NULL) {
        return 0;
    }
    int pos = chaveDivisao(al.mat, ha->TABLE_SIZE);
    if (ha->itens != NULL) {

    }
    Aluno* novo;
    novo = (Aluno*)malloc(sizeof(Aluno));
    if (novo == NULL) {
        return 0;
    }
	novo->mat = al.mat;
	novo->nome = al.nome;
	novo->prox = NULL;
	Aluno aux = ha->itens[pos];
	do {
		if (aux == NULL) {
			ha->itens[pos] = novo;
			return 1;
		}
		aux = aux.prox;
	}while(aux != NULL);
	return 0;
}

void liberaHash (Hash* ha) {

}


void main(){
    
}