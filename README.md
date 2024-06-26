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
├── extras/
│ ├── lr_0_parser_completo.c
│ └── lr_0_parser.excalidraw
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
Digite a cadeia de entrada: abc
```

O programa exibirá a saída, mostrando o processo de análise sintática:

```vbnet
Saida: x
Cadeia: x$
----------- LOOP 0 -----------
Stack: [0, $]

> S3
----------- LOOP 1 -----------
Stack: [0, $] [3, x]

> R3: S -> x
----------- LOOP 2 -----------
Stack: [0, $] [0, S]

aceitacao
----------- LOOP 3 -----------
Stack: [0, $] [0, S] [1, $]
```
 
 ## **Extras** 
 
 Arquivo [lr_0_parser.excalidraw](https://github.com/GabrielaSchmitt/LR-0-parser/blob/main/extras/lr_0_parser.excalidraw) anexado é o caderno de anotações utilizado durante a execução do algoritmo, contém referencias, desenhos que utilizamos. Para abrir faça a importação no site [excalidraw](https://excalidraw.com/).

 Caso queira executar o código online, sugiro o site [onlinegdb](https://www.onlinegdb.com/), utilize o arquivo que contem o código completo [lr_0_completo_completo.c](https://github.com/GabrielaSchmitt/LR-0-parser/blob/main/extras/lr_0_completo_completo.c).

 ✨ Obrigada pela atenção! ✨


