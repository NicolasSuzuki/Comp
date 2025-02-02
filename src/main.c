#include <stdio.h>
#include "analisador_lexico.h"
#include "analisador_sintatico.h"
#include "analisador_semantico.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }

    FILE *arquivo = fopen(argv[1], "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Chama o analisador sintático
    analisador_sintatico(arquivo);

    // Reinicia o arquivo para o início
    rewind(arquivo);

    // Chama o analisador semântico
    analisador_semantico(arquivo);

    fclose(arquivo);
    return 0;
}
