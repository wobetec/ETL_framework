import sqlite3
import pandas as pd
import numpy as np
from datetime import datetime, timedelta
import dash
from dash import dcc, html
from dash.dependencies import Input, Output
import plotly.graph_objs as go

# Conexão ao banco de dados SQLite
def connect_to_database():
    return sqlite3.connect("ecommerce_data.db")

def fetch_data_viewed_per_minute():
    conn = connect_to_database()
    query = "SELECT Time, Viewed FROM viewed_per_minute ORDER BY Time DESC LIMIT 60"
    df = pd.read_sql_query(query, conn, parse_dates=["Time"])
    conn.close()
    return df

def fetch_data_bought_per_minute():
    conn = connect_to_database()
    query = "SELECT Time, Bought FROM bought_per_minute ORDER BY Time DESC LIMIT 60"
    df = pd.read_sql_query(query, conn, parse_dates=["Time"])
    conn.close()
    return df

def fetch_data_unique_users_per_product():
    conn = connect_to_database()
    query = "SELECT Time, ProductID, UniqueUsers FROM unique_users_per_product ORDER BY Time DESC LIMIT 60"
    df = pd.read_sql_query(query, conn, parse_dates=["Time"])
    conn.close()
    return df

def fetch_data_most_bought_last_hour():
    conn = connect_to_database()
    query = "SELECT ProductID, SUM(BoughtCount) as BoughtCount FROM most_bought_last_hour GROUP BY ProductID ORDER BY BoughtCount DESC LIMIT 10"
    df = pd.read_sql_query(query, conn)
    conn.close()
    return df

def fetch_data_most_viewed_last_hour():
    conn = connect_to_database()
    query = "SELECT ProductID, SUM(ViewCount) as ViewCount FROM most_viewed_last_hour GROUP BY ProductID ORDER BY ViewCount DESC LIMIT 10"
    df = pd.read_sql_query(query, conn)
    conn.close()
    return df

# def fetch_data_sold_out():
#     conn = connect_to_database()
#     query = """
#     SELECT strftime("%Y-%m-%d %H:%M", Time) as Minute, SUM(SoldOutCount) as SoldOutCount
#     FROM sold_out
#     WHERE Time > DATETIME("now", "-60 minutes")
#     GROUP BY strftime("%Y-%m-%d %H:%M", Time)
#     ORDER BY Minute ASC
#     """
#     df = pd.read_sql_query(query, conn, parse_dates=["Minute"])
#     conn.close()
#     return df

# df_sold_out = fetch_data_sold_out()
# print(df_sold_out)



def fetch_data_avg_views_before_purchase():
    conn = connect_to_database()
    query = "SELECT ProductID, AVG(AvgViews) as AvgViews FROM avg_views_before_purchase GROUP BY ProductID LIMIT 10"
    df = pd.read_sql_query(query, conn)
    conn.close()
    return df

def ler_e_calcular_media(arquivo):
    try:
        df = pd.read_csv(arquivo, delim_whitespace=True, header=None, names=["Tratador", "Start", "End"])
        df["Duration"] = (df["End"] - df["Start"]) / 1000000
        medias = df.groupby("Tratador")["Duration"].mean().reset_index()
        medias["Duration"] = medias["Duration"].round(2)
        return medias
    except Exception as e:
        print(f"Erro ao ler ou processar o arquivo: {e}")
        return pd.DataFrame(columns=["Tratador", "Duration"])

# Aqui continua o restante do seu código de setup do Dash e callbacks
app = dash.Dash(__name__)

app.layout = html.Div([
    html.H1("Dashboard de Monitoramento em Tempo Real"),
    html.Div([
        dcc.Graph(id="graph-treatment-time"),
        dcc.Interval(id="interval-treatment-time", interval=10*1000, n_intervals=0)
    ]),
    html.Div([
        dcc.Graph(id="graph-viewed-per-minute"),
        dcc.Interval(id="interval-viewed-per-minute", interval=10*1000, n_intervals=0)
    ]),
    html.Div([
        dcc.Graph(id="graph-bought-per-minute"),
        dcc.Interval(id="interval-bought-per-minute", interval=10*1000, n_intervals=0)
    ]),
    html.Div([
        dcc.Graph(id="graph-unique-users-per-product"),
        dcc.Interval(id="interval-unique-users-per-product", interval=10*1000, n_intervals=0)
    ]),
    html.Div([
        dcc.Graph(id="graph-avg-views-before-purchase"),
        dcc.Interval(id="interval-avg-views-before-purchase", interval=10*1000, n_intervals=0)
    ]),
    html.Div([
        dcc.Graph(id="graph-most-bought-last-hour"),
        dcc.Interval(id="interval-most-bought-last-hour", interval=10*1000, n_intervals=0)
    ]),
    html.Div([
        dcc.Graph(id="graph-most-viewed-last-hour"),
        dcc.Interval(id="interval-most-viewed-last-hour", interval=10*1000, n_intervals=0)
    ]),
    # html.Div([
    #     dcc.Graph(id="graph-sold-out"),
    #     dcc.Interval(id="interval-sold-out", interval=10*1000, n_intervals=0)
    # ])
])

@app.callback(
    Output("graph-viewed-per-minute", "figure"),
    Input("interval-viewed-per-minute", "n_intervals"))
def update_graph_viewed_per_minute(n):
    df = fetch_data_viewed_per_minute()
    fig = go.Figure()
    fig.add_trace(go.Scatter(x=df["Time"], y=df["Viewed"], mode="lines+markers", name="Viewed per Minute"))
    fig.update_layout(
        title="Número de Produtos Visualizados por Minuto",
        xaxis=dict(type="date", tickformat="%H:%M", dtick=60000),
        yaxis=dict(title="Número de Visualizações")
    )
    return fig

@app.callback(
    Output("graph-bought-per-minute", "figure"),
    Input("interval-bought-per-minute", "n_intervals"))
def update_graph_bought_per_minute(n):
    df = fetch_data_bought_per_minute()
    fig = go.Figure()
    fig.add_trace(go.Scatter(x=df["Time"], y=df["Bought"], mode="lines+markers", name="Bought per Minute"))
    fig.update_layout(
        title="Número de Produtos Comprados por Minuto",
        xaxis=dict(type="date", tickformat="%H:%M", dtick=60000),
        yaxis=dict(title="Número de Compras")
    )
    return fig

@app.callback(
    Output("graph-unique-users-per-product", "figure"),
    Input("interval-unique-users-per-product", "n_intervals"))
def update_graph_unique_users_per_product(n):
    df = fetch_data_unique_users_per_product()
    fig = go.Figure()
    fig.add_trace(go.Scatter(x=df["Time"], y=df["UniqueUsers"], mode="lines+markers", name="Unique Users per Product"))
    fig.update_layout(
        title="Número de Usuários Únicos por Produto",
        xaxis=dict(type="date", tickformat="%H:%M", dtick=60000),
        yaxis=dict(title="Número de Usuários Únicos")
    )
    return fig

@app.callback(
    Output("graph-most-bought-last-hour", "figure"),
    Input("interval-most-bought-last-hour", "n_intervals"))
def update_graph_most_bought_last_hour(n):
    df = fetch_data_most_bought_last_hour()
    fig = go.Figure()
    fig.add_trace(go.Bar(y=df["ProductID"].astype(str), x=df["BoughtCount"], orientation="h", name="Most Bought Last Hour"))
    fig.update_layout(
        title="Produtos Mais Comprados na Última Hora",
        xaxis=dict(title="Quantidade Comprada"),
        yaxis=dict(autorange="reversed", title="ID do Produto")
    )
    return fig

@app.callback(
    Output("graph-most-viewed-last-hour", "figure"),
    Input("interval-most-viewed-last-hour", "n_intervals"))
def update_graph_most_viewed_last_hour(n):
    df = fetch_data_most_viewed_last_hour()
    fig = go.Figure()
    fig.add_trace(go.Bar(y=df["ProductID"].astype(str), x=df["ViewCount"], orientation="h", name="Most Viewed Last Hour"))
    fig.update_layout(
        title="Produtos Mais Visualizados na Última Hora",
        xaxis=dict(title="Quantidade de Visualizações"),
        yaxis=dict(autorange="reversed", title="ID do Produto")
    )
    return fig

@app.callback(
    Output("graph-avg-views-before-purchase", "figure"),
    Input("interval-avg-views-before-purchase", "n_intervals"))
def update_graph_avg_views_before_purchase(n):
    df = fetch_data_avg_views_before_purchase()
    fig = go.Figure()
    fig.add_trace(go.Scatter(x=df["ProductID"].astype(str), y=df["AvgViews"], mode="lines+markers", name="Average Views Before Purchase"))
    fig.update_layout(
        title="Média de Visualizações Antes da Compra",
        xaxis=dict(title="ID do Produto"),
        yaxis=dict(title="Média de Visualizações")
    )
    return fig

# @app.callback(
#     Output("graph-sold-out", "figure"),
#     Input("interval-sold-out", "n_intervals"))
# def update_graph_sold_out(n):
#     df_sold_out_aggregated = fetch_data_sold_out()

#     fig = go.Figure()
#     fig.add_trace(go.Scatter(x=df_sold_out_aggregated["Minute"], y=df_sold_out_aggregated["SoldOutCount"], mode="lines+markers", name="Sold Out Products"))
#     fig.update_layout(
#         title="Número de Produtos Vendidos Sem Estoque por Minuto",
#         xaxis=dict(
#             type="date",
#             tickformat="%H:%M",
#             dtick=60000  # isso define os intervalos de marcação do eixo X para cada minuto
#         ),
#         yaxis=dict(
#             title="Número de Produtos Vendidos Sem Estoque",
#         )
#     )
#     return fig

@app.callback(
    Output("graph-treatment-time", "figure"),
    Input("interval-treatment-time", "n_intervals"))
def update_graph_treatment_time(n):
    df_medias = ler_e_calcular_media("times.txt")
    fig = go.Figure()
    fig.add_trace(go.Bar(x=df_medias["Tratador"], y=df_medias["Duration"], name="Tempo Médio por Tratador"))
    fig.update_layout(
        title="Tempo Médio de Processamento por Tratador",
        xaxis=dict(title="Tratador"),
        yaxis=dict(title="Tempo Médio (segundos)")
    )
    return fig






if __name__ == "__main__":
    app.run_server(debug=True)
