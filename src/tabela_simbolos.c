#include "tabela_simbolos.h"

void inicializar_tabela(TabelaSimbolos *tabela) {
    tabela->tamanho = 0;
}

// Função hash para mapear um nome a um índice na tabela
int hash(char *nome) {
    unsigned long hash = 5381;
    int c;
    while ((c = *nome++)) {
        hash = ((hash << 5) + hash) + c; 
    }
    return hash % TAMANHO_TABELA;
}

void inserir_tabela(TabelaSimbolos *tabela, char *nome_id, char *escopo, char *tipo_id, char *tipo_dado, int linha) {
    int indice = hash(nome_id);
    EntradaTabela *entrada = &tabela->entradas[indice];

    strcpy(entrada->nome_id, nome_id);
    strcpy(entrada->escopo, escopo);
    strcpy(entrada->tipo_id, tipo_id);
    strcpy(entrada->tipo_dado, tipo_dado);
    entrada->linhas[entrada->num_linhas++] = linha;
    tabela->tamanho++;
}

EntradaTabela* buscar_tabela(TabelaSimbolos *tabela, char *nome_id, char *escopo) {
    int indice = hash(nome_id);
    EntradaTabela *entrada = &tabela->entradas[indice];

    if (strcmp(entrada->nome_id, nome_id) == 0 && strcmp(entrada->escopo, escopo) == 0) {
        return entrada;
    }
    return NULL;
}

void imprimir_tabela(TabelaSimbolos *tabela) {
    printf("# TABELA DE SÍMBOLOS\n");
    printf("Nome_ID;Escopo;Tipo_ID;Tipo_dado;Linhas\n");
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        EntradaTabela *entrada = &tabela->entradas[i];
        if (entrada->nome_id[0] != '\0') {
            printf("%s;%s;%s;%s;", entrada->nome_id, entrada->escopo, entrada->tipo_id, entrada->tipo_dado);
            for (int j = 0; j < entrada->num_linhas; j++) {
                printf("%d", entrada->linhas[j]);
                if (j < entrada->num_linhas - 1) printf(",");
            }
            printf("\n");
        }
    }
}
