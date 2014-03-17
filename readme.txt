Esse projeto possuí 3 módulos que trabalham com uma matriz 9x9 representando um tabuleiro de Sudoku.

No primeiro módulo foi implementado um verificador que diz se a matriz está valida ou se possui erros e nesse caso, apontando os mesmos. Assim criamos 3 funções que analisam 
independentemente as linhas, colunas e submatrizes da matriz principal, verificando se a regra do jogo está válida. Visto que as 3 funções fazem uma análise independente,
concluímos que elas poderiam ser executadas separadamente. Criamos 9 threads para executar cada função. Dessa forma a validação da 
Linha 1, Coluna1 e submatriz 1 são executadas paralelamente em threads diferentes, em uma próxima interação já é começada a verificação da Linha2, Coluna2 e submatriz2
mesmo ainda não tendo necessariamente terminada a validação do grupo 1. Assim, no total executamos 27 threads paralelizando as validações.
Essa é uma abordagem interessante pois podemos validar diversas partes da matriz que dependem de diferentes regras de validação de forma concorrente, sem utilizar um número
absurdo de threads e agilizando o processamento.

O segundo módulo foi implementado para, dado um tabuleiro de Sudoku 9x9 com X's, disponibilizar as opções válidas para cada campo contendo um X. Uma função foi criada para detectar essas opções, chamada "findClues". Como o objetivo é analisar cada célula da matriz, executamos 81 threads paralelizando as buscas pelas opções. A função verifica se existe um X, e caso exista, preenche a saída com todas as opções, iterando nas linhas, colunas e submatrizes de modo a retirar opções invalidas substituindo pelo caracter N. Na impressão, removemos todas as referências do caracter N, restando apenas as opções válidas para cada uma das células. A escolha das 81 threads teve como objetivo otimizar a identificação das opções em cada uma das células da matriz completa em paralelo, sem que haja problemas de concorrência. Considerando que as células que não estão marcadas com X tem seu processamento bem rápido, isso ameniza o fato de termos uma alta quantidade de threads simultâneas.

O terceiro módulo não foi terminado, apesar de boa parte do código estar feita. O objetivo do modulo sudoku.c é, a partir de uma entrada com alguns números faltantes de um
tabuleiro 9x9 de Sudoku (representados pelo caracter 'X'), ele retornar para o usuário o Sudoku resolvido. O algoritmo pensado foi utilizar o segundo módulo para encontrar
todas as possíveis dicas e, para cada elemento faltante que só tivesse uma dica, considerar que esse elemento é o certo. Para avaliar quais elementos já estão certos, uma
matriz 9x9 foi feita e caso o elemento daquela posição esteja com valor 0, ainda não está correto, caso esteja com 1, já está correto. Enquanto os 81 elementos não estiverem
corretos, o programa rodaria novamente o algoritmo do segundo módulo e, cada vez retornaria menos possibilidades, já que no passo anterior assumimos que os que só tem uma
dica estão corretos e marcamos isso na matriz de valores corretos do Sudoku. Isso aconteceria até que todos os valores estivessem corretos. É possível talvez que o Sudoku 
não tenha solução e, nesse caso, em algum momento o número de dicas seria nulo, nos mostrando que o Sudoku não pode ser resolvido. As threads a princípio rodariam em paralelo
como no segundo módulo, fazendo com que o programa calcule de maneira mais rápida as dicas.
