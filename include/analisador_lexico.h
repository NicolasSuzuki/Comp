#ifndef ANALISADOR_LEXICO_H
#define ANALISADOR_LEXICO_H

#include <stdio.h>

int obter_token(char *lexema, int *linha, int *coluna);
void inicializar_lexico(FILE *arquivo);

#endif
