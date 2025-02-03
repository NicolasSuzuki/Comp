#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "analisador_sintatico.h"
#include "analisador_lexico.h"
#include "tokens.h"

int token_atual;
char lexema[100];
int linha, coluna;

void declaracao();
void declaracao_funcao();
void corpo();
void expressao();
void parametros();
void comando_return();
void termo();
void fator();
void tipo();
void identificador();

void proximo_token() {
    token_atual = obter_token(lexema, &linha, &coluna);
}

void imprimir_no(const char *nome, int nivel) {
    for (int i = 0; i < nivel; i++) printf("  ");
    printf("%s (\n", nome);
}

void programa() {
    imprimir_no("Programa", 0);
    while (token_atual != TOKEN_EOF) {
        declaracao();
    }
    printf(")\n");
}

void declaracao() {
    imprimir_no("Declaracao", 1);
    tipo();
    identificador();
    if (token_atual == '=') { 
        printf("  =\n");
        proximo_token();
        expressao(); 
    } 
    if (token_atual == '(') { 
        declaracao_funcao();
    } else if (token_atual == ';') {
        printf("  ;\n");
        proximo_token();
    } else {
        printf("ERRO SINTATICO: “%c” INVALIDO [linha: %d, coluna: %d]\n", token_atual, linha, coluna);
        exit(1);
    }
    printf(")\n");
}

void declaracao_funcao() {
    imprimir_no("DeclaracaoFuncao", 2);
    proximo_token();
    
    parametros();

    if (token_atual == ')') {
        printf("  )\n");
        proximo_token();
    } else {
        printf("ERRO SINTATICO: Esperado ')' [linha: %d, coluna: %d]\n", linha, coluna);
        exit(1);
    }

    if (token_atual == '{') {
        printf("  {\n");
        proximo_token();
        corpo();
        if (token_atual == '}') {
            printf("  }\n");
            proximo_token();
        } else {
            printf("ERRO SINTATICO: Esperado '}' [linha: %d, coluna: %d]\n", linha, coluna);
            exit(1);
        }
    } else {
        printf("ERRO SINTATICO: Esperado '{' [linha: %d, coluna: %d]\n", linha, coluna);
        exit(1);
    }
    printf(")\n");
}

void parametros() {
    imprimir_no("Parametros", 3);
    if (token_atual == TOKEN_INT || token_atual == TOKEN_FLOAT) {
        tipo();
        identificador();
        while (token_atual == ',') {
            printf("  ,\n");
            proximo_token();
            tipo();
            identificador();
        }
    }
    printf(")\n");
}

void corpo() {
    imprimir_no("Corpo", 3);
    while (token_atual != '}') {
        if (token_atual == TOKEN_RETURN) { 
            comando_return();
        } else if (token_atual == TOKEN_INT || token_atual == TOKEN_FLOAT) {
            declaracao();
        } else {
            expressao();
        }
    }
    printf(")\n");
}

void comando_return() {
    imprimir_no("ComandoReturn", 4);
    printf("  return\n");
    proximo_token();
    expressao();

    if (token_atual == ';') {
        printf("  ;\n");
        proximo_token();
    } else {
        printf("ERRO SINTATICO: Esperado ';' após return [linha: %d, coluna: %d]\n", linha, coluna);
        exit(1);
    }
    printf(")\n");
}

void expressao() {
    imprimir_no("Expressao", 4);
    termo();
    while (token_atual == '+' || token_atual == '-' || token_atual == '*' || token_atual == '/') {
        printf("  %c\n", token_atual);
        proximo_token();
        termo();
    }
    printf(")\n");
}

void termo() {
    imprimir_no("Termo", 5);
    fator();
    while (token_atual == '*' || token_atual == '/') {
        printf("  %c\n", token_atual);
        proximo_token();
        fator();
    }
    printf(")\n");
}

void fator() {
    imprimir_no("Fator", 6);
    if (token_atual == TOKEN_IDENTIFICADOR || token_atual == TOKEN_NUMERO) {
        printf("  %s\n", lexema);
        proximo_token();
    } else if (token_atual == '(') {
        printf("  (\n");
        proximo_token();
        expressao();
        if (token_atual == ')') {
            printf("  )\n");
            proximo_token();
        } else {
            printf("ERRO SINTATICO: Esperado ')' [linha: %d, coluna: %d]\n", linha, coluna);
            exit(1);
        }
    } else {
        printf("ERRO SINTATICO: “%s” INVALIDO [linha: %d, coluna: %d]\n", lexema, linha, coluna);
        exit(1);
    }
    printf(")\n");
}

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

void analisador_sintatico(FILE *arquivo) {
    
    inicializar_lexico(arquivo);
    proximo_token();

    programa();
}
