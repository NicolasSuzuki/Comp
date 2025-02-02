#include <stdio.h>
#include "analisador_semantico.h"
#include "tabela_simbolos.h"
#include "analisador_lexico.h"
#include "tokens.h"

// Variável global para a tabela de símbolos
TabelaSimbolos tabela;

// Função para verificar declarações de variáveis
void verificar_declaracao(char *nome_id, char *escopo, char *tipo_id, int linha) {
    EntradaTabela *entrada = buscar_tabela(&tabela, nome_id, escopo);
    if (entrada != NULL) {
        printf("ERRO SEMÂNTICO: Variável '%s' já declarada no escopo '%s' LINHA: %d\n", nome_id, escopo, linha);
    } else {
        inserir_tabela(&tabela, nome_id, escopo, tipo_id, "variavel", linha);
    }
}

// Função principal do analisador semântico
void analisador_semantico(FILE *arquivo) {
    inicializar_tabela(&tabela);

    // Inicializa o analisador léxico
    inicializar_lexico(arquivo);

    int token_atual;
    char lexema[100];
    int linha, coluna;

    // Exemplo de uso: percorrer o código-fonte e verificar declarações
    while ((token_atual = obter_token(lexema, &linha, &coluna)) != TOKEN_EOF) {
        // Verifica se o token é uma declaração de variável
        if (token_atual == TOKEN_INT || token_atual == TOKEN_FLOAT) {
            char tipo_id[10];
            strcpy(tipo_id, lexema);

            // Obtém o próximo token (nome da variável)
            token_atual = obter_token(lexema, &linha, &coluna);
            if (token_atual == TOKEN_IDENTIFICADOR) {
                verificar_declaracao(lexema, "global", tipo_id, linha);
            }
        }
    }

    // Imprimir a tabela de símbolos
    imprimir_tabela(&tabela);
}
