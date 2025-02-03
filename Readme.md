# Projeto de Compiladores - Linguagem C-

Este projeto consiste na implementação de um compilador para a linguagem **C-**, desenvolvido como parte da disciplina de Compiladores. O compilador é composto por três módulos principais: **analisador léxico**, **analisador sintático**, e **analisador semântico**.

---

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

```
/projeto_compilador
│
├── /src                  # Pasta com o código-fonte
│   ├── main.c            # Ponto de entrada do programa
│   ├── analisador_lexico.c  # Implementação do analisador léxico
│   ├── analisador_sintatico.c  # Implementação do analisador sintático
│   ├── analisador_semantico.c  # Implementação do analisador semântico
│   └── tabela_simbolos.c  # Implementação da tabela de símbolos
│
├── /include              # Pasta com os cabeçalhos (.h)
│   ├── analisador_lexico.h
│   ├── analisador_sintatico.h
│   ├── analisador_semantico.h
│   ├── tabela_simbolos.h
│   └── tokens.h          # Definição dos tokens e constantes
│
├── /testes               # Pasta com arquivos de teste
│   ├── teste1.cminus     # Exemplo de código em C-
│   ├── teste2.cminus
│   └── teste3.cminus
│
├── Makefile              # Arquivo para automatizar a compilação
└── README.md             # Descrição geral do projeto
```

---

## Como Compilar o Projeto

Para compilar o projeto, siga os passos abaixo:

### **Pré-requisitos**
- **GCC**: O compilador C (GNU Compiler Collection) deve estar instalado no seu sistema.
- **Make**: A ferramenta `make` deve estar disponível para automatizar a compilação.

### **Passos para Compilar**

1. **Clone o repositório** (se aplicável):
   ```bash
   git clone <url_do_repositorio>
   cd projeto_compilador
   ```

2. **Compile o projeto**:
   Execute o comando `make` para compilar o projeto:
   ```bash
   make
   ```

   Isso irá gerar o executável `compilador`.

3. **Limpe os arquivos temporários** (opcional):
   Para remover os arquivos objeto e o executável, use:
   ```bash
   make clean
   ```

---

## Como Executar o Compilador

Após compilar o projeto, você pode executar o compilador com um arquivo de entrada em C-. O compilador suporta as seguintes flags:

- **`-l` ou `-L`**: Executa apenas o analisador léxico e imprime os tokens.
- **`-p` ou `-P`**: Executa o analisador sintático e imprime a árvore de análise sintática.
- **`-s` ou `-S`**: Executa o analisador semântico e imprime a tabela de símbolos.

### **Exemplos de Uso**

1. **Analisar um arquivo de entrada**:
   ```bash
   ./compilador testes/teste1.cminus
   ```

2. **Executar apenas o analisador léxico**:
   ```bash
   ./compilador -l testes/teste1.cminus
   ```

3. **Executar o analisador sintático**:
   ```bash
   ./compilador -p testes/teste1.cminus
   ```

4. **Executar o analisador semântico**:
   ```bash
   ./compilador -s testes/teste1.cminus
   ```

---

## Testes

A pasta `/testes` contém exemplos de código em C- para testar o compilador. Você pode usar esses arquivos ou criar novos para verificar o funcionamento do compilador.

### **Exemplo de Arquivo de Teste**

#### **`testes/teste1.cminus`**
```c
int x;
float y;
int x; // Declaração duplicada (deve gerar um erro semântico)
```

### **Executando os Testes**

Para testar o compilador com um arquivo de teste, use:
```bash
./compilador testes/teste1.cminus
```

---

## Funcionalidades Implementadas

### **Analisador Léxico**
- Reconhece tokens como palavras-chave (`int`, `float`), identificadores, números, operadores e delimitadores.
- Trata erros léxicos e imprime os tokens no formato especificado.

### **Analisador Sintático**
- Implementado como um **parser descendente recursivo**.
- Verifica a estrutura do código-fonte com base na gramática da linguagem C-.
- Constrói a árvore sintática (opcional).

### **Analisador Semântico**
- Usa uma **tabela de símbolos** para verificar regras semânticas.
- Verifica declarações de variáveis, tipos, escopo, e unicidade.
- Detecta e reporta erros semânticos.
- Imprime a tabela de símbolos quando solicitado.

### **Tabela de Símbolos**
- Implementada usando uma tabela hash.
- Armazena informações sobre identificadores (variáveis, funções, etc.).
- Suporta inserção, busca e impressão de entradas.

---

## Próximos Passos

1. **Expandir a Gramática**:
   - Adicionar suporte para expressões aritméticas, estruturas de controle (`if`, `while`), e funções.

2. **Melhorar o Tratamento de Erros**:
   - Adicionar mensagens de erro mais descritivas e recuperação de erros.

3. **Testar com Casos Reais**:
   - Usar arquivos de teste mais complexos para verificar se o compilador está funcionando corretamente.

---

## Autor

- Nicolas Alves Suzuki
