#include <stdio.h>
#include <stdlib.h>

typedef struct hash{
    int qtd;
    int TABLE_SIZE;
    struct aluno **items;
}Hash;

typedef struct aluno{
    int matricula;
}Aluno;

/*                            Colocando Indice                           */

int chaveDivisao(int chave, int TABLE_SIZE){
    return (chave) % TABLE_SIZE;
}

int chaveMulti(int chave, int TABLE_SIZE){
    double A = 0.6180339887;
    double val = chave * A;
    val = val - (int)val;
    return (int)(TABLE_SIZE * val);
}

/* Falta Hashing Universal*/

Hash* criaHash(int TABLE_SIZE){
    
    Hash* ha = (Hash*) malloc (sizeof(Hash));
    
    if(ha != NULL){
        int i;
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->items = (struct aluno**) malloc(TABLE_SIZE * sizeof(struct aluno*));
        
        if(ha->items == NULL){
            free(ha);
            return NULL;
        }
        ha->qtd = 0;
        
        for(i = 0; i < ha->TABLE_SIZE; i++){
            ha->items[i] = NULL;
        }
        return ha;
    }
}

/* Tratamento da Colisao */
int hashingLinear(int pos, int i, int TABLE_SIZE){
    return ((pos + i) & 0x7FFFFFFF) % TABLE_SIZE;
}

int hashingQuadratico(int pos, int i, int TABLE_SIZE){
    pos = pos + 2*i + 5*i*i;
    return (pos) % TABLE_SIZE;
}

int hashingDuplo(int h1, int chave, int i, int TABLE_SIZE){
    int h2 = chaveDivisao(chave, TABLE_SIZE-1)+1;
    return ((h1+i*h2) & 0x7FFFFFFF) % TABLE_SIZE;
}
/* Fim tratamento de Colisao */

int inserehash(Hash* ha, struct aluno al){
    
    int chave = al.matricula;
    
    int i, pos, newpos;
    
    pos = chaveDivisao(chave, ha->TABLE_SIZE); //--> Pode substituir por outra função hashing: multi ou universal
    // Atenção --> Tem que trocar ela em todo o código (em remover, e em buscar para que se tenha acesso a ela)
    
    for(i = 0; i < ha->TABLE_SIZE; i++){
        
        newpos = hashingLinear(pos, i, ha->TABLE_SIZE);
        //newpos = hashingQuadratico(pos, i, ha->TABLE_SIZE); --> Só substituir os tratamentos
        
        if(ha->items[newpos] == NULL){
            struct aluno* novo;
            novo = (struct aluno*) malloc(sizeof(struct aluno));
            
            if(novo == NULL)
                return 0;
            
            *novo = al;
            
            ha->items[newpos] = novo;
            ha->qtd++;
            return 1;
        }
    }
    return 0;
}

int buscahash(Hash* ha, struct aluno *al, int mat){
    
    int i, pos, newpos;
    
    pos = chaveDivisao(mat, ha->TABLE_SIZE);
    
    for(i = 0; i < ha->TABLE_SIZE; i++){
        
        newpos = hashingLinear(pos, i, ha->TABLE_SIZE);
        
        if(ha->items[newpos] == NULL)
            return 0;
        
        if(ha->items[newpos]->matricula == mat){
            *al = *(ha->items[newpos]);            
            return 1;
        }
    }
    return 1;
}

void mostra(Hash* ha, struct aluno al){
    if(ha != NULL){
        
        int i;
        for(i = 0; i < ha->TABLE_SIZE; i++){
            if(ha->items[i] != NULL){ // Para os ponteiros que n tiverem nada faça a coisa abaixo
                
                printf("matriculas: %d \n", ha->items[i]->matricula);
            } else {
                //printf("%p \n", ha->items[i]); --> vai mostrar só as posições vazias
            }
        }   
    }    
}

int removerChave(Hash* ha, struct aluno al, int mat){
    
    int i, pos;
    
    pos = chaveDivisao(mat, ha->TABLE_SIZE);

    for(i = 0; i < ha->TABLE_SIZE; i++){    
        if(ha->items[pos]->matricula == mat){
            
            free(ha->items[pos]);
            //printf("remover %d \n", mat); --> Se quise ter certeza que foi deletado aqui vai mostrar o endereço de memoria
        }
        free(ha->items);
        free(ha);
    }
    return 1;
}

void main(){
    
    Hash* ha = criaHash(12);
    
    struct aluno al, nums[1] = {{10}};
    
    int i;
    
    for(i = 0; i < 1; i++){
        inserehash(ha, nums[i]);
    }
    //buscahash(ha, &al, 10); --> para usar esse aqui vc vai ter que colocar um print la no buscaHash pra ver se ele achou
       
    if (buscahash(ha, &al, 10) == 1)
        printf("matricula encontrada %d \n"); // ta funcionando mas ta indicando erro de sintaxe
    
    removerChave(ha, al, 10);

    /* vai varrer a tabela e mostrar o que tem la*/
    mostra(ha, al);
}

