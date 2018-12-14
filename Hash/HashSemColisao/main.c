#include <stdio.h>
#include <stdlib.h>

typedef struct hash{
    int qtd;
    int TABLE_SIZE;
    struct aluno **itens;
    
}Hash;

typedef struct aluno{
    int matricula;
}Aluno;


Hash* criaHash(int TABLE_SIZE){
    
    Hash* ha = (Hash*) malloc(sizeof(Hash));
    
    if(ha != NULL){
        int i;
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->itens = (struct aluno**) malloc (TABLE_SIZE * sizeof(struct aluno*));       
        
        if(ha->itens == NULL){
            free(ha);
            return 0;   
        }
        ha->qtd = 0;
        
        for(i=0; i < TABLE_SIZE; i++){
            ha->itens[i] = NULL;
        }
        return ha;
    }
}

int chaveDivisao(int chave, int TABLE_SIZE){
    return (chave & 0x7FFFFFFF) % TABLE_SIZE;
}


int insereHash(Hash* ha, struct aluno al){
    
    int chave = al.matricula;
    
    int pos = chaveDivisao(chave, ha->TABLE_SIZE);
    
    struct aluno* novo;
    
    novo = (struct aluno*) malloc(sizeof(struct aluno));
    
    if(ha == NULL)
        return 0;
    
    *novo = al;
    
    ha->itens[pos] = novo;
    ha->qtd++;
    return 1;
}

int buscaHash(Hash* ha, int mat, struct aluno *al){
    
    int pos = chaveDivisao(mat, ha->TABLE_SIZE);
    
    if(ha->itens[pos] == NULL){
        return 0;
    }
    
    *al = *(ha->itens[pos]);
    return 1;
}






int main(int argc, char** argv) {

    return (EXIT_SUCCESS);
}

