
Para compilar o código e fazer testes, utilize `gcc -o main.e main.c pgm.c kmeans.c utils.c`.

Tambem é preferivel que a compilação seja feita em uma pasta separada, e.g. `/output/` para melhor organização. Nesse caso, utilize `cd <nome_da_pasta>` e depois `gcc -o main.e ../main.c ../pgm.c ../kmeans.c ../utils.c`

Esse comando de compilação é temporário e será usado somente durante o periodo de teste.

Após compilar, coloque a dataset fornecida no dropbox do projeto em uma pasta chamada `/database/` e descompacte. Lembre-se de sempre ajustar o caminho para os arquivos quando for fazer testes.

Sujeito a organização posterior.

