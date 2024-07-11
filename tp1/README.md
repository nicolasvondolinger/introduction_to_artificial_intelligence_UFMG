Resolução de Sudoku usando Algoritmos de Busca

Este projeto implementa vários algoritmos de busca para resolver o jogo Sudoku. O Sudoku é um quebra-cabeça numérico em que o objetivo é preencher uma grade 9x9 com dígitos de 1 a 9, de forma que cada coluna, linha e sub-grade 3x3 contenha todos os dígitos de 1 a 9 sem repetição.

Como Rodar

    Compilar o código: Abra um terminal na pasta do projeto e compile o código usando o compilador g++ com o seguinte comando:

        g++ -o bin/TP1.exe main.cpp

Executar o programa: Após compilar com sucesso, execute o programa com o seguinte comando, onde o primeiro argumento é o algoritmo escolhido (A, I, U, D, G ou B) e o segundo argumento é a string representando o tabuleiro do Sudoku, onde os espaços vazios são representados por 0:

bin/TP1.exe A "107006450 025340008 060001070 053000029 610009800 000602007 001093200 008000000 040078591"

    O primeiro argumento define o algoritmo a ser usado:
        A: A* search
        I: Iterative deepening search
        U: Uniform-cost search
        D: Depth-first search
        G: Greedy best-first search
        B: Breadth-first search

    O segundo argumento é uma string representando o tabuleiro do Sudoku, onde cada número é um dígito do tabuleiro na posição correspondente, e os espaços vazios são representados por 0.

Por exemplo, a saída esperada do comando acima é a seguinte:

46 0
137986452 925347168 864521973 753814629 612739845 489652317 571493286 298165734 346278591 

Onde o primeiro número representa a quantidade de estados que foram explorados, o segundo número o tempo em milisegundos que o resultado demorou para ser encontrado e por último o tabuleiro resolvido.