#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // Para isspace, isalpha, isalnum, isdigit
#include <string.h> // Para strcmp
#include "analisador_sintatico.h"
#include "analisador_lexico.h"
#include "tokens.h"

// Variáveis globais para armazenar o token atual e o lexema
int token_atual;
char lexema[100];
int linha, coluna;

// Protótipos das funções
void declaracao();
void tipo();
void identificador();

// Função para obter o próximo token do analisador léxico
void proximo_token() {
    token_atual = obter_token(lexema, &linha, &coluna);
}

// Função para imprimir a árvore sintática
void imprimir_no(const char *nome, int nivel) {
    for (int i = 0; i < nivel; i++) printf("  ");
    printf("%s (\n", nome);
}

// Função para o não terminal "Programa"
void programa() {
    imprimir_no("Programa", 0);
    while (token_atual != TOKEN_EOF) {
        declaracao();
    }
    printf(")\n");
}

// Função para o não terminal "Declaração"
void declaracao() {
    imprimir_no("Declaracao", 1);
    tipo();
    identificador();
    if (token_atual == ';') {
        printf("  ;\n");
        proximo_token();
    } else {
        printf("ERRO SINTATICO: “;” INVALIDO [linha: %d, coluna: %d]\n", linha, coluna);
        exit(1);
    }
    printf(")\n");
}

// Função para o não terminal "Tipo"
void tipo() {
    imprimir_no("Tipo", 2);
    if (token_atual == TOKEN_INT || token_atual == TOKEN_FLOAT) {
        printf("  %s\n", lexema);
        proximo_token();
    } else {
        printf("ERRO SINTATICO: “%s” INVALIDO [linha: %d, coluna: %d]\n", lexema, linha, coluna);
        exit(1);
    }
    printf(")\n");
}

// Função para o não terminal "Identificador"
void identificador() {
    imprimir_no("Identificador", 2);
    if (token_atual == TOKEN_IDENTIFICADOR) {
        printf("  %s\n", lexema);
        proximo_token();
    } else {
        printf("ERRO SINTATICO: “%s” INVALIDO [linha: %d, coluna: %d]\n", lexema, linha, coluna);
        exit(1);
    }
    printf(")\n");
}

// Função principal do analisador sintático
void analisador_sintatico(FILE *arquivo) {
    // Inicializa o analisador léxico
    inicializar_lexico(arquivo);
    proximo_token();

    // Inicia a análise sintática
    programa();
}
