import sqlite3
import pandas as pd
import numpy as np
from datetime import datetime, timedelta
import time

# Conectar ao banco de dados SQLite e criar tabelas
conn = sqlite3.connect('ecommerce_data.db')
c = conn.cursor()

# Comandos SQL para criar tabelas
tables_creation_commands = [
    '''CREATE TABLE IF NOT EXISTS viewed_per_minute (Time TEXT, Viewed INTEGER)''',
    '''CREATE TABLE IF NOT EXISTS bought_per_minute (Time TEXT, Bought INTEGER)''',
    '''CREATE TABLE IF NOT EXISTS unique_users_per_product (Time TEXT, ProductID INTEGER, UniqueUsers INTEGER)''',
    '''CREATE TABLE IF NOT EXISTS most_bought_last_hour (ProductID INTEGER, BoughtCount INTEGER)''',
    '''CREATE TABLE IF NOT EXISTS most_viewed_last_hour (ProductID INTEGER, ViewCount INTEGER)''',
    '''CREATE TABLE IF NOT EXISTS avg_views_before_purchase (ProductID INTEGER, AvgViews INTEGER)''',
    '''CREATE TABLE IF NOT EXISTS sold_out (ProductID INTEGER, SoldOutCount INTEGER)'''
]

# Criar as tabelas se não existirem
for command in tables_creation_commands:
    c.execute(command)

# Fechar a conexão após criar tabelas
conn.close()

# Função para inserir dados
def insert_data(df, table_name):
    conn = sqlite3.connect('ecommerce_data.db')
    df.to_sql(table_name, conn, if_exists='append', index=False)
    conn.close()

# Inserir dados iniciais
time_range = pd.date_range(start="2023-04-21 09:00", end="2023-04-21 09:59", freq='T')

# Dicionário de DataFrames e nomes de tabelas
dfs_and_tables = {
    'viewed_per_minute': pd.DataFrame({
        'Time': time_range,
        'Viewed': np.random.randint(50, 100, size=len(time_range))
    }),
    'bought_per_minute': pd.DataFrame({
        'Time': time_range,
        'Bought': np.random.randint(10, 30, size=len(time_range))
    }),
    'unique_users_per_product': pd.DataFrame({
        'Time': time_range,
        'ProductID': np.random.randint(1, 21, size=len(time_range)),
        'UniqueUsers': np.random.randint(1, 50, size=len(time_range))
    }),
    'most_bought_last_hour': pd.DataFrame({
        'ProductID': np.random.randint(1, 21, size=10),
        'BoughtCount': np.random.randint(20, 50, size=10)
    }).sort_values(by='BoughtCount', ascending=False).reset_index(drop=True),
    'most_viewed_last_hour': pd.DataFrame({
        'ProductID': np.random.randint(1, 21, size=10),
        'ViewCount': np.random.randint(100, 200, size=10)
    }).sort_values(by='ViewCount', ascending=False).reset_index(drop=True),
    'avg_views_before_purchase': pd.DataFrame({
        'ProductID': np.random.randint(1, 21, size=10),
        'AvgViews': np.random.randint(5, 15, size=10)
    }),
    'sold_out': pd.DataFrame({
        'ProductID': np.random.randint(1, 21, size=20),
        'SoldOutCount': np.random.randint(1, 10, size=20)
    }).groupby('ProductID').sum().reset_index()
}

for table_name, df in dfs_and_tables.items():
    insert_data(df, table_name)

# Funções para atualizar o banco de dados
def insert_new_data(conn):
    new_time = datetime.now()
    new_viewed = np.random.randint(50, 100)
    new_bought = np.random.randint(10, 30)
    new_product_id = np.random.randint(1, 21)
    new_unique_users = np.random.randint(1, 50)
    new_bought_count = np.random.randint(20, 50)
    new_view_count = np.random.randint(100, 200)
    new_avg_views = np.random.randint(5, 15)
    new_sold_out_count = np.random.randint(1, 10)

    # Inserir novos dados
    c = conn.cursor()
    c.execute('INSERT INTO viewed_per_minute (Time, Viewed) VALUES (?, ?)', (new_time, new_viewed))
    c.execute('INSERT INTO bought_per_minute (Time, Bought) VALUES (?, ?)', (new_time, new_bought))
    c.execute('INSERT INTO unique_users_per_product (Time, ProductID, UniqueUsers) VALUES (?, ?, ?)', (new_time, new_product_id, new_unique_users))
    c.execute('INSERT INTO most_bought_last_hour (ProductID, BoughtCount) VALUES (?, ?)', (new_product_id, new_bought_count))
    c.execute('INSERT INTO most_viewed_last_hour (ProductID, ViewCount) VALUES (?, ?)', (new_product_id, new_view_count))
    c.execute('INSERT INTO avg_views_before_purchase (ProductID, AvgViews) VALUES (?, ?)', (new_product_id, new_avg_views))
    c.execute('INSERT INTO sold_out (ProductID, SoldOutCount) VALUES (?, ?)', (new_product_id, new_sold_out_count))
    conn.commit()

def remove_old_data(conn):
    cutoff_time = datetime.now() - timedelta(minutes=60)
    c = conn.cursor()
    c.execute('DELETE FROM viewed_per_minute WHERE Time < ?', (cutoff_time,))
    c.execute('DELETE FROM bought_per_minute WHERE Time < ?', (cutoff_time,))
    c.execute('DELETE FROM unique_users_per_product WHERE Time < ?', (cutoff_time,))
    conn.commit()

def update_database():
    conn = sqlite3.connect('ecommerce_data.db')
    insert_new_data(conn)
    remove_old_data(conn)
    conn.close()
    print("Database updated at", datetime.now().strftime("%Y-%m-%d %H:%M:%S"))

# Loop para atualizar os dados 10 vezes a cada 30 segundos
for _ in range(10):
    update_database()
    time.sleep(30)
