# ETL_framework

ETL micro-framwork para disciplina de computação escalável 2024.1.

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
make main
```

## Simulador
O simulador é responsável por gerar dados de entrada para o ETL. Para executar o simulador, no diretório `.\simulator\`, basta executar:
```
python3 data_generator.py
```

## Execução
Para executar o projeto, com o simulador em execução e os arquivos compilados, basta executar o arqivo no diretório `.\etl\`:
```
./main.out
```

## Proto3

    pip install grpcio-tools

    python3 -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. simulation.proto


## sqlite3

    sudo apt-get update
    sudo apt-get install libsqlite3-dev



## Dashboard Dash/Plotly
Primeiro é necessário instalar as dependências do projeto. Cada aplicação (Dashboard e Simulador) possuiem suas dependências de forma separada.
```
pip install -r requirements.txt
```

Para executar o dashboard, basta executar o comando:
```
python3 ./visualizationsqlite.py
```

## Alunos
- Cleyton Santos
- Esdras Cavalcanti
- Marcelo Ângelo
- Ramyro Aquines
- Zuilho Segundo