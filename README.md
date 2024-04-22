# ETL_framework
ETL micro-framwork para disciplina de computação escalável

## Estrutura de diretórios
```
ETL_framework
├── src
├── etl
├── simulator
├── README.md
```

## Compilação usando o Makefile
Para compilar o projeto, basta executar o comando:
```
make test 
```

## Simulador
O simulador é responsável por gerar dados de entrada para o ETL. Para executar o simulador, basta executar o comando:
```
python3 simulator/data_generator.py
```

## Execução
Para executar o projeto, com o simulador em execução e os arquivos compilados, basta executar o comando:
```
./test.out
```


## Dashboard Flask
Primeiro é necessário instalar as dependências do projeto:
```
pip install -r requirements.txt
```

Para executar o dashboard, basta executar o comando:
```
python3 dashboard/visualizationsqlite.py
```