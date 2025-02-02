#include <stdio.h>
#include <ctype.h>  // Para isspace, isalpha, isalnum, isdigit
#include <string.h> // Para strcmp
#include "analisador_lexico.h"
#include "tokens.h"

// Variável global para o arquivo de entrada
FILE *arquivo;

// Função para obter o próximo token
int obter_token(char *lexema, int *linha, int *coluna) {
    char caractere;
    int i = 0;

    // Ignorar espaços em branco
    while ((caractere = fgetc(arquivo)) != EOF && isspace(caractere)) {
        if (caractere == '\n') {
            (*linha)++;
            *coluna = 1;
        } else {
            (*coluna)++;
        }
    }

    if (caractere == EOF) {
        return TOKEN_EOF;
    }

    // Identificadores ou palavras-chave
    if (isalpha(caractere)) {
        lexema[i++] = caractere;
        while (isalnum(caractere = fgetc(arquivo))) {
            lexema[i++] = caractere;
        }
        lexema[i] = '\0';
        ungetc(caractere, arquivo); // Devolve o último caractere lido

        // Verificar se é uma palavra-chave
        if (strcmp(lexema, "int") == 0) return TOKEN_INT;
        if (strcmp(lexema, "float") == 0) return TOKEN_FLOAT;
        return TOKEN_IDENTIFICADOR;
    }

    // Números
    if (isdigit(caractere)) {
        lexema[i++] = caractere;
        while (isdigit(caractere = fgetc(arquivo)) || caractere == '.') {
            lexema[i++] = caractere;
        }
        lexema[i] = '\0';
        ungetc(caractere, arquivo);
        return TOKEN_NUMERO;
    }

    // Operadores e delimitadores
    lexema[0] = caractere;
    lexema[1] = '\0';
    return caractere; // Retorna o próprio caractere como token
}

// Função para inicializar o analisador léxico
void inicializar_lexico(FILE *arquivo_entrada) {
    arquivo = arquivo_entrada;
}
