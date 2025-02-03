#ifndef ANALISADOR_SEMANTICO_H
#define ANALISADOR_SEMANTICO_H

#include <stdio.h>
#include "tabela_simbolos.h"

extern TabelaSimbolos tabela;

void verificar_declaracao(char *nome_id, char *escopo, char *tipo_id, int linha);
void analisador_semantico();

#endif // ANALISADOR_SEMANTICO_H

