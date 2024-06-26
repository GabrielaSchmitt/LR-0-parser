# LR(0) Parser

Este projeto implementa um analisador sintático LR(0) em C. Ele é composto por várias funções que trabalham em conjunto para analisar uma cadeia de entrada e determinar se ela pertence à linguagem especificada.

## Introdução ao LR(0)

LR(0) é um tipo de analisador ascendente que analisa linguagens determinísticas livres de contexto em tempo linear. Um método para analisar a estrutura sintática de uma cadeia de símbolos com base em uma gramática utilizando conjuntos de itens e uma tabela de parsing para decidir deslocamentos e reduções.

Este algoritmo é principalmente usado na construção de compiladores para transformar código-fonte em representações internas adequadas para execução ou otimização.

Visualmente, o funcionamento do algoritmo pode ser representado pelo seguinte esquema:

![parser_theory](https://github.com/GabrielaSchmitt/LR-0-parser/assets/86369677/5241c7c4-8acc-405e-92f4-bee2ed4e33e3)

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

```
lr_0_parser/
├── include/
│ ├── parser.h
│ ├── stack.h
│ └── transducer.h
├── src/
│ ├── parser.c
│ ├── stack.c
│ └── transducer.c
├── main.c
├── Makefile
└── Read.me
```


## Gramática utilizada

O projeto segue a gramática:

```
S → (E) | x
E → S | E+S
```
## DFA

![dfa](https://github.com/GabrielaSchmitt/LR-0-parser/assets/86369677/6a2ebbe4-88b3-4d7c-8827-8a4b468c1d0e)

## Parsing Table 

![parsing_table](https://github.com/GabrielaSchmitt/LR-0-parser/assets/86369677/7f6bc59d-f91c-4c2d-b667-37162e39e37e)


### Arquivos

- **main.c**: Contém a função principal que inicializa o analisador e processa a cadeia de entrada.
- **src/transducer.c**: Implementa a função transducer, que transforma a cadeia de entrada.
- **src/stack.c**: Implementa a pilha usada pelo analisador.
- **src/parser.c**: Implementa a tabela de análise sintática.
- **include/**: Contém os arquivos de cabeçalho para as funções declaradas nos arquivos de código-fonte.

## Compilação e Execução

### Compilar com GCC

Para compilar o projeto utilizando o `gcc`, execute os seguintes comandos no seu terminal:

```sh
gcc -Iinclude -c src/transducer.c -o src/transducer.o
gcc -Iinclude -c src/stack.c -o src/stack.o
gcc -Iinclude -c src/parser.c -o src/parser.o
gcc -Iinclude -c main.c -o main.o
gcc src/transducer.o src/stack.o src/parser.o main.o -o algoritmo_lr_parser
```

### Usar Makefile


Se você tiver make instalado, pode compilar o projeto com o comando:

```sh
make
```

Para limpar os arquivos objeto e o executável, use:

```sh
make clean
```

### Executando o Programa

Depois de compilar, você pode executar o programa resultante (neste caso, algoritmo_lr_parser):

```sh
./algoritmo_lr_parser
```

O programa solicitará que você insira uma cadeia de entrada. Ele então processará a cadeia e exibirá a saída correspondente.

## Exemplo de Uso

Aqui está um exemplo de como usar o programa:

1. Execute o programa:

```sh
./algoritmo_lr_parser
```

2. Digite a cadeia de entrada quando solicitado:

```css
Digite a cadeia de entrada: (abc+((j+klmnopq))))
```

O programa exibirá a saída, mostrando o processo de análise sintática:

```vbnet
Saida: (x+((x+x))))
Cadeia: (x+((x+x))))$
----------- LOOP 0 -----------
Stack: [0, $]

> S2
----------- LOOP 1 -----------
Stack: [0, $] [2, (]

> S3
----------- LOOP 2 -----------
Stack: [0, $] [2, (] [3, x]

> R3: S -> x

> G5
----------- LOOP 3 -----------
Stack: [0, $] [2, (] [5, S]

> R4: E -> S
----------- LOOP 4 -----------
Stack: [0, $] [2, (] [4, E]

> S7
----------- LOOP 5 -----------
Stack: [0, $] [2, (] [4, E] [7, +]

> S2
----------- LOOP 6 -----------
Stack: [0, $] [2, (] [4, E] [7, +] [2, (]

> S2
----------- LOOP 7 -----------
Stack: [0, $] [2, (] [4, E] [7, +] [2, (] [2, (]

> S3
----------- LOOP 8 -----------
Stack: [0, $] [2, (] [4, E] [7, +] [2, (] [2, (] [3, x]

> R3: S -> x

> G5
----------- LOOP 9 -----------
Stack: [0, $] [2, (] [4, E] [7, +] [2, (] [2, (] [5, S]

> R4: E -> S
----------- LOOP 10 -----------
Stack: [0, $] [2, (] [4, E] [7, +] [2, (] [2, (] [4, E] 

> S7
----------- LOOP 11 -----------
Stack: [0, $] [2, (] [4, E] [7, +] [2, (] [2, (] [4, E] [7, +]

> S3
----------- LOOP 12 -----------
Stack: [0, $] [2, (] [4, E] [7, +] [2, (] [2, (] [4, E] [7, +] [3, x]

> R3: S -> x

> G8
----------- LOOP 13 -----------
Stack: [0, $] [2, (] [4, E] [7, +] [2, (] [2, (] [4, E] [7, +] [8, S]

> R5: E -> E + S
----------- LOOP 14 -----------
Stack: [0, $] [2, (] [4, E] [7, +] [2, (] [2, (] [4, E]

> S6
----------- LOOP 15 -----------
Stack: [0, $] [2, (] [4, E] [7, +] [2, (] [2, (] [4, E] [6, )]

> R2: S -> ( E )

> G5
----------- LOOP 16 -----------
Stack: [0, $] [2, (] [4, E] [7, +] [2, (] [5, S]

> R4: E -> S
----------- LOOP 17 -----------
Stack: [0, $] [2, (] [4, E] [7, +] [2, (] [4, E]

> S6
----------- LOOP 18 -----------
Stack: [0, $] [2, (] [4, E] [7, +] [2, (] [4, E] [6, )]

> R2: S -> ( E )

> R5: E -> E + S
----------- LOOP 19 -----------
Stack: [0, $] [2, (] [4, E]

> S6
----------- LOOP 20 -----------
Stack: [0, $] [2, (] [4, E] [6, )]

> R2: S -> ( E )

> G5
----------- LOOP 21 -----------
Stack: [0, $] [5, S]

> R4: E -> S
----------- LOOP 22 -----------
Stack: [0, $] [4, E]

> S6
----------- LOOP 23 -----------
Stack: [0, $] [4, E] [6, )]

> R2: S -> ( E )
----------- LOOP 24 -----------
Stack: [2, S]

aceitacao
----------- LOOP 25 -----------
Stack: [2, S] [1, $]
```



