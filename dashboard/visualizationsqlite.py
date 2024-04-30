import sqlite3
import pandas as pd
import dash
from dash import dcc, html
from dash.dependencies import Input, Output
import plotly.graph_objs as go
import sys

# Conexão ao banco de dados SQLite
def connect_to_database():
    return sqlite3.connect("../etl/new.db")

def fetch_data_viewed_per_minute():
    conn = connect_to_database()
    query = "SELECT datetime, count FROM T1 ORDER BY datetime DESC LIMIT 60"
    df = pd.read_sql_query(query, conn, parse_dates=["datetime"])
    conn.close()
    return df

def fetch_data_bought_per_minute():
    conn = connect_to_database()
    query = "SELECT datetime, count FROM T2 ORDER BY datetime DESC LIMIT 60"
    df = pd.read_sql_query(query, conn, parse_dates=["datetime"])
    conn.close()
    return df

def fetch_data_unique_users_per_product():
    conn = connect_to_database()
    query = "SELECT datetime, count FROM T3 ORDER BY datetime DESC LIMIT 60"
    df = pd.read_sql_query(query, conn, parse_dates=["datetime"])
    conn.close()
    return df

def fetch_data_most_bought_last_hour():
    conn = connect_to_database()
    query = "SELECT datetime, count FROM T4 ORDER BY count DESC LIMIT 10"
    df = pd.read_sql_query(query, conn)
    conn.close()
    return df

def fetch_data_most_viewed_last_hour():
    conn = connect_to_database()
    query = "SELECT datetime, count FROM T5 ORDER BY count DESC LIMIT 10"
    df = pd.read_sql_query(query, conn)
    conn.close()
    return df


def fetch_data_avg_views_before_purchase():
    conn = connect_to_database()
    query = "SELECT datetime, count FROM T6 ORDER BY datetime DESC LIMIT 60"
    df = pd.read_sql_query(query, conn)
    conn.close()
    return df

def ler_e_calcular_media(arquivo):
    try:
        df = pd.read_csv(arquivo, sep=' ', header=None, names=["Tratador", "Start", "End"])
        df["Duration"] = (df["End"] - df["Start"]) / 1e9
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
    dcc.Interval(id="interval", interval=500, n_intervals=0),
    html.Div([
        dcc.Graph(id="graph-treatment-time"),
    ]),
    html.Div([
        dcc.Graph(id="graph-viewed-per-minute"),
    ]),
    html.Div([
        dcc.Graph(id="graph-bought-per-minute"),
    ]),
    html.Div([
        dcc.Graph(id="graph-unique-users-per-product"),
    ]),
    html.Div([
        dcc.Graph(id="graph-avg-views-before-purchase"),
    ]),
    html.Div([
        dcc.Graph(id="graph-most-bought-last-hour"),
    ]),
    html.Div([
        dcc.Graph(id="graph-most-viewed-last-hour"),
    ]),
])

@app.callback(
    Output("graph-viewed-per-minute", "figure"),
    Input("interval", "n_intervals"))
def update_graph_viewed_per_minute(n):
    df = fetch_data_viewed_per_minute()
    fig = go.Figure()
    if df.empty:
        return fig
    fig.add_trace(go.Scatter(x=df["datetime"], y=df["count"], mode="lines+markers", name="Viewed per Minute"))
    fig.update_layout(
        title="Número de Produtos Visualizados por Minuto",
        xaxis=dict(type="date", tickformat="%H:%M", dtick=60000),
        yaxis=dict(title="Número de Visualizações")
    )
    return fig

@app.callback(
    Output("graph-bought-per-minute", "figure"),
    Input("interval", "n_intervals"))
def update_graph_bought_per_minute(n):
    df = fetch_data_bought_per_minute()
    fig = go.Figure()
    if df.empty:
        return fig
    fig.add_trace(go.Scatter(x=df["datetime"], y=df["count"], mode="lines+markers", name="Bought per Minute"))
    fig.update_layout(
        title="Número de Produtos Comprados por Minuto",
        xaxis=dict(type="date", tickformat="%H:%M", dtick=60000),
        yaxis=dict(title="Número de Compras")
    )
    return fig

@app.callback(
    Output("graph-unique-users-per-product", "figure"),
    Input("interval", "n_intervals"))
def update_graph_unique_users_per_product(n):
    df = fetch_data_unique_users_per_product()
    fig = go.Figure()
    if df.empty:
        return fig
    fig.add_trace(go.Scatter(x=df["datetime"], y=df["count"], mode="lines+markers", name="Unique Users per Product"))
    fig.update_layout(
        title="Número de Usuários Únicos por Produto",
        xaxis=dict(type="date", tickformat="%H:%M", dtick=60000),
        yaxis=dict(title="Número de Usuários Únicos")
    )
    return fig

@app.callback(
    Output("graph-most-bought-last-hour", "figure"),
    Input("interval", "n_intervals"))
def update_graph_most_bought_last_hour(n):
    df = fetch_data_most_bought_last_hour()
    fig = go.Figure()
    if df.empty:
        return fig
    fig.add_trace(go.Bar(y=df["datetime"].astype(str), x=df["count"], orientation="h", name="Most Bought Last Hour"))
    fig.update_layout(
        title="Produtos Mais Comprados na Última Hora",
        xaxis=dict(title="Quantidade Comprada"),
        yaxis=dict(autorange="reversed", title="ID do Produto")
    )
    return fig

@app.callback(
    Output("graph-most-viewed-last-hour", "figure"),
    Input("interval", "n_intervals"))
def update_graph_most_viewed_last_hour(n):
    df = fetch_data_most_viewed_last_hour()
    fig = go.Figure()
    if df.empty:
        return fig
    fig.add_trace(go.Bar(y=df["datetime"].astype(str), x=df["count"], orientation="h", name="Most Viewed Last Hour"))
    fig.update_layout(
        title="Produtos Mais Visualizados na Última Hora",
        xaxis=dict(title="Quantidade de Visualizações"),
        yaxis=dict(autorange="reversed", title="ID do Produto")
    )
    return fig

@app.callback(
    Output("graph-avg-views-before-purchase", "figure"),
    Input("interval", "n_intervals"))
def update_graph_avg_views_before_purchase(n):
    df = fetch_data_avg_views_before_purchase()
    fig = go.Figure()
    if df.empty:
        return fig
    fig.add_trace(go.Scatter(x=df["datetime"].astype(str), y=df["count"], mode="lines+markers", name="Average Views Before Purchase"))
    fig.update_layout(
        title="Média de Visualizações Antes da Compra",
        xaxis=dict(title="ID do Produto"),
        yaxis=dict(title="Média de Visualizações")
    )
    return fig


@app.callback(
    Output("graph-treatment-time", "figure"),
    Input("interval", "n_intervals"))
def update_graph_treatment_time(n):
    df_medias = ler_e_calcular_media("../etl/times.txt")
    fig = go.Figure()
    if df_medias.empty:
        return fig
    fig.add_trace(go.Bar(x=df_medias["Tratador"], y=df_medias["Duration"], name="Tempo Médio por Tratador"))
    fig.update_layout(
        title="Tempo Médio de Processamento por Tratador",
        xaxis=dict(title="Tratador"),
        yaxis=dict(title="Tempo Médio (segundos)")
    )
    return fig

if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "debug":
        app.run_server(debug=True)
    else:
        app.run_server(debug=False)
