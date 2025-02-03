#include <stdio.h>
#include <string.h>
#include "analisador_lexico.h"
#include "analisador_sintatico.h"
#include "analisador_semantico.h"
#include "tokens.h"

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        printf("Uso: %s [-l|-p|-s] <arquivo_de_entrada>\n", argv[0]);
        printf("  -l: Executa apenas o analisador léxico.\n");
        printf("  -p: Executa o analisador sintático.\n");
        printf("  -s: Executa o analisador semântico.\n");
        return 1;
    }

    int flag_lexico = 0, flag_sintatico = 0, flag_semantico = 0;
    char *arquivo_entrada;

    if (argc == 3) {
        if (strcmp(argv[1], "-l") == 0) {
            flag_lexico = 1;
        } else if (strcmp(argv[1], "-p") == 0) {
            flag_sintatico = 1;
        } else if (strcmp(argv[1], "-s") == 0) {
            flag_semantico = 1;
        } else {
            printf("Flag inválida: %s\n", argv[1]);
            return 1;
        }
        arquivo_entrada = argv[2];
    } else {
        arquivo_entrada = argv[1];
    }

    FILE *arquivo = fopen(arquivo_entrada, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    if (flag_lexico) {
        inicializar_lexico(arquivo);
        int token_atual;
        char lexema[100];
        int linha, coluna;

        while ((token_atual = obter_token(lexema, &linha, &coluna)) != TOKEN_EOF) {
            printf("<TOKEN> \"%s\" [linha: %d, coluna: %d]\n", lexema, linha, coluna);
        }
    } else if (flag_sintatico) {
        analisador_sintatico(arquivo);
    } else if (flag_semantico) {
        analisador_semantico(arquivo);
    } else {
        analisador_sintatico(arquivo);
        rewind(arquivo); // Reinicia o arquivo para o início
        analisador_semantico(arquivo);
    }

    fclose(arquivo);
    return 0;
}