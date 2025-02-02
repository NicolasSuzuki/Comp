#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 100

// Estrutura para representar uma entrada na tabela de símbolos
typedef struct {
    char nome_id[50];      // Nome do identificador
    char escopo[50];       // Escopo do identificador
    char tipo_id[10];      // Tipo do identificador (ex: int, float)
    char tipo_dado[10];    // Tipo de dado (variável ou função)
    int linhas[100];       // Linhas onde o identificador foi usado
    int num_linhas;        // Número de linhas
} EntradaTabela;

// Estrutura para a tabela de símbolos
typedef struct {
    EntradaTabela entradas[TAMANHO_TABELA];
    int tamanho;
} TabelaSimbolos;

// Funções para manipular a tabela de símbolos
void inicializar_tabela(TabelaSimbolos *tabela);
int hash(char *nome);
void inserir_tabela(TabelaSimbolos *tabela, char *nome_id, char *escopo, char *tipo_id, char *tipo_dado, int linha);
EntradaTabela* buscar_tabela(TabelaSimbolos *tabela, char *nome_id, char *escopo);
void imprimir_tabela(TabelaSimbolos *tabela);

#endif
