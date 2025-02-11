
# Algoritmo KMeans - LabProg 2024.2

O programa desenvolvido aplica o algoritmo KMeans em um dataset fornecido em `/db/` e disponibiliza os resultados em `/output/`.

O programa permite o usuário escolher o valor de `k` as ser usado no algoritmo.




## Como Usar e Exemplo

Clone esse repositorio para uma pasta em seu computador e descompacte o dataset na pasta `/db/`. Para compilar o codigo, abra um terminal e use o comando `make`. Use `./main.e <imagemEntrada.pgm> <imagemSaida.pgm> <k>` para executar o programa. 

`imagemEntrada.pgm` devera conter a o caminho inteiro desde o dataset ate a imagem, e.g. `pasta1/img1.pgm`. OBS: o programa considera a existencia da pasta com nome do dataset (`/dataset_Herlev_reduzido_PGM/`) ao executar, então tenha certeza da existencia dessa pasta em `/db/`.

`imagemSaida.pgm` é o nome do arquivo de saida do programa que será armazenado em `/output/`.

`k` é a quantidade de clusters que será usada pelo kmeans.
