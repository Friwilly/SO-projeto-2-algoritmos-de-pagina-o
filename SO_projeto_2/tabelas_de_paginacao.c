#include <stdio.h>

struct referencias{
    int fila[100];
    int tam;
};

int main()
{
    FILE *entrada = fopen("entrada.txt", "r");
    if (!entrada) {
        printf("Erro: Não foi possível abrir o arquivo.\n");
        return 1;
    }

    FILE *saida = fopen("saida.txt", "w");
    if (!saida) {
        printf("Erro: Não foi possível criar o arquivo.\n");
        fclose(entrada);
        return 1;
    }
    
    struct referencias paginas;
    paginas.tam = 0;
    int i = 0;
    
    int quadros;
    fscanf(entrada, "%d", &quadros);
    if(quadros <= 0){
        printf("Erro: Quantidade de quadros inválida");
        fclose(entrada);
        fclose(saida);
        return 1;
    }
    
    //inicia a tabela
    while(fscanf(entrada, "%d", &paginas.fila[i]) != EOF){
        paginas.tam++;
        
        i++;
        
        if(i > 99){
            break;
        }
    }
    fclose(entrada);
    
    if(paginas.tam == -1){
        printf("Erro: arquivo de entrada vazio");
        fclose(saida);
        return 1;
    }
    
    int fIFO[quadros];
    for(int k = 0; k < quadros; k++){
        fIFO[k] = -1;
    }
    int countFIFO = 0;
    
    int otimo[quadros];
    for(int k = 0; k < quadros; k++){
        otimo[k] = -1;
    }
    int countOtimo = 0;
    
    int lRU[quadros];
    for(int k = 0; k < quadros; k++){
        lRU[k] = -1;
    }
    int countLRU = 0;
    
    int verif = -1;
    
    //FIFO
    for(int j = 0; j < paginas.tam; j++){
        //verifica se a tabela de paginação contém a referencia
        for(int h = 0; h < quadros; h++){
            if (fIFO[h] == paginas.fila[j]){
                verif = 0;
                break;
            }
        }
        //se contém, passa para o proximo elemento
        if(verif == 0){
            verif = -1;
            continue;
        }
        //se não contém, shifta a tabela e insere a nova referencia
        for(int h = quadros; h > 0; h--){
            fIFO[h] = fIFO[h-1];
        }
        fIFO[0] = paginas.fila[j]; 
        countFIFO++;
    }
    
    verif = -1;
    
    //auxiliar para identificar 
    int aux[quadros];
    for(int k = 0; k < quadros; k++){
        aux[k] = 0;
    }
    int countAux = 0;
    
    //otimo
    for(int j = 0; j < paginas.tam; j++){
        //verifica se a tabela de paginação contém a referencia
        for(int h = 0; h < quadros; h++){
            if (otimo[h] == paginas.fila[j]){
                verif = 0;
                break;
            }
        }
        //se contém, passa para o proximo elemento
        if(verif == 0){
            verif = -1;
            continue;
        }
        //se não contém, busca as referencias futuras e registra no auxiliar aux
        for(int h = j; h < paginas.tam; h++){
            //verifica se a tabela de paginação contém a referencia futura
            for(int p = 0; p < quadros; p++){
                if(otimo[p] == paginas.fila[h]){
                    aux[p] = 1;
                    countAux++;
                    break;
                }
                
            }
            
            if(countAux >= quadros-1){
                break;
            }
        }
        
        
        for(int p = 0; p < quadros; p++){
            if(otimo[p] < 0){
                otimo[p] = paginas.fila[j];
                verif = 0;
                break;
            }
            
        }
        
        if(verif != 0){
            //busca o indice para substituicao e preenche
            for(int p = 0; p < quadros; p++){
                if(aux[p] == 0){
                    otimo[p] = paginas.fila[j];
                    break;
                }
                
            }
        }
        
        //redefinição das variaveis utilizadas pra proxima iteração
        for(int k = 0; k < quadros; k++){
        aux[k] = 0;
        }
        countAux = 0;
        
        verif = -1;
        
        countOtimo++;
    }
    
    //redefinição das variaveis utilizadas pro processo seguinte
    verif = -1;
    
    for(int k = 0; k < quadros; k++){
        aux[k] = 0;
    }
    countAux = 0;
    
    //LRU
    for(int j = 0; j < paginas.tam; j++){
        //verifica se a tabela de paginação contém a referencia
        for(int h = 0; h < quadros; h++){
            if (lRU[h] == paginas.fila[j]){
                verif = 0;
                break;
            }
        }
        //se contém, passa para o proximo elemento
        if(verif == 0){
            verif = -1;
            continue;
        }
        //se não contém, busca as referencias passadas e registra no auxiliar aux
        for(int h = j; h > 0; h--){
            //verifica se a tabela de paginação contém a referencia passada
            for(int p = 0; p < quadros; p++){
                if(lRU[p] == paginas.fila[h]){
                    aux[p] = 1;
                    countAux++;
                    break;
                }
                
            }
            
            if(countAux >= quadros-1){
                break;
            }
        }
        
        
        for(int p = 0; p < quadros; p++){
            if(lRU[p] < 0){
                lRU[p] = paginas.fila[j];
                verif = 0;
                break;
            }
            
        }
        
        if(verif != 0){
            //busca o indice para substituicao e preenche
            for(int p = 0; p < quadros; p++){
                if(aux[p] == 0){
                    lRU[p] = paginas.fila[j];
                    break;
                }
                
            }
        }
        
        //redefinição das variaveis utilizadas pra proxima iteração
        for(int k = 0; k < quadros; k++){
        aux[k] = 0;
        }
        countAux = 0;
        
        verif = -1;
        
        countLRU++;
    }
    
    fprintf(saida, "FIFO: %d\n", countFIFO);
    fprintf(saida, "OTM: %d\n", countOtimo);
    fprintf(saida, "LRU: %d\n", countLRU);


    fclose(saida);
    return 0;
}
