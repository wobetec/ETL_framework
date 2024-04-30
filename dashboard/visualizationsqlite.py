import sqlite3
import pandas as pd
from dash import Dash, dcc, html, Input, Output, callback
import plotly.graph_objs as go
import sys
import fcntl


def fetch_data_viewed_per_minute(conn):
    query = "SELECT datetime, count FROM T1 ORDER BY datetime DESC LIMIT 60"
    df = pd.read_sql_query(query, conn, parse_dates=["datetime"])
    return df

def fetch_data_bought_per_minute(conn):
    query = "SELECT datetime, count FROM T2 ORDER BY datetime DESC LIMIT 60"
    df = pd.read_sql_query(query, conn, parse_dates=["datetime"])
    return df

def fetch_data_unique_users_per_product(conn):
    query = "SELECT datetime, count FROM T3 ORDER BY datetime DESC LIMIT 60"
    df = pd.read_sql_query(query, conn, parse_dates=["datetime"])
    return df

def fetch_data_most_bought_last_hour(conn):
    query = "SELECT datetime, count FROM T4 ORDER BY count DESC LIMIT 10"
    df = pd.read_sql_query(query, conn)
    return df

def fetch_data_most_viewed_last_hour(conn):
    query = "SELECT datetime, count FROM T5 ORDER BY count DESC LIMIT 10"
    df = pd.read_sql_query(query, conn)
    return df


def fetch_data_avg_views_before_purchase(conn):
    query = "SELECT datetime, count FROM T6 ORDER BY datetime DESC LIMIT 60"
    df = pd.read_sql_query(query, conn)
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
app = Dash(__name__)

empty_figure = go.Figure()

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


@callback(
    [
        Output("graph-viewed-per-minute", "figure"),
        Output("graph-bought-per-minute", "figure"),
        Output("graph-unique-users-per-product", "figure"),
        Output("graph-most-bought-last-hour", "figure"),
        Output("graph-most-viewed-last-hour", "figure"),
        Output("graph-avg-views-before-purchase", "figure"),
    ],
    [Input("interval", "n_intervals")]
)
def update_from_sql(n):
    db_file = "../etl/new.db"
    with open(db_file, 'r') as f:
        # try:
            # fcntl.flock(f, fcntl.LOCK_SH)
        conn = sqlite3.connect(db_file)
        
        df_viewed_per_minute = fetch_data_viewed_per_minute(conn)
        df_bought_per_minute = fetch_data_bought_per_minute(conn)
        df_unique_users_per_product = fetch_data_unique_users_per_product(conn)
        df_most_bought_last_hour = fetch_data_most_bought_last_hour(conn)
        df_most_viewed_last_hour = fetch_data_most_viewed_last_hour(conn)
        df_avg_views_before_purchase = fetch_data_avg_views_before_purchase(conn)
        # finally:
        #     conn.close()
        # fcntl.flock(f, fcntl.LOCK_UN)

    if df_viewed_per_minute.empty:
        df_viewed_per_minute = pd.DataFrame(columns=["datetime", "count"])
    if df_bought_per_minute.empty:
        df_bought_per_minute = pd.DataFrame(columns=["datetime", "count"])
    if df_unique_users_per_product.empty:
        df_unique_users_per_product = pd.DataFrame(columns=["datetime", "count"])
    if df_most_bought_last_hour.empty:
        df_most_bought_last_hour = pd.DataFrame(columns=["datetime", "count"])
    if df_most_viewed_last_hour.empty:
        df_most_viewed_last_hour = pd.DataFrame(columns=["datetime", "count"])
    if df_avg_views_before_purchase.empty:
        df_avg_views_before_purchase = pd.DataFrame(columns=["datetime", "count"])
    
    fig_viewed_per_minute = go.Figure()
    fig_viewed_per_minute.add_trace(go.Scatter(x=df_viewed_per_minute["datetime"], y=df_viewed_per_minute["count"], mode="lines+markers", name="Viewed per Minute"))
    fig_viewed_per_minute.update_layout(
        title="Número de Produtos Visualizados por Minuto",
        xaxis=dict(type="date", tickformat="%H:%M", dtick=60000),
        yaxis=dict(title="Número de Visualizações")
    )

    fig_bought_per_minute = go.Figure()
    fig_bought_per_minute.add_trace(go.Scatter(x=df_bought_per_minute["datetime"], y=df_bought_per_minute["count"], mode="lines+markers", name="Bought per Minute"))
    fig_bought_per_minute.update_layout(
        title="Número de Produtos Comprados por Minuto",
        xaxis=dict(type="date", tickformat="%H:%M", dtick=60000),
        yaxis=dict(title="Número de Compras")
    )

    fig_unique_users_per_product = go.Figure()
    fig_unique_users_per_product.add_trace(go.Scatter(x=df_unique_users_per_product["datetime"], y=df_unique_users_per_product["count"], mode="lines+markers", name="Unique Users per Product"))
    fig_unique_users_per_product.update_layout(
        title="Número de Usuários Únicos por Produto",
        xaxis=dict(type="date", tickformat="%H:%M", dtick=60000),
        yaxis=dict(title="Número de Usuários Únicos")
    )

    fig_most_bought_last_hour = go.Figure()
    fig_most_bought_last_hour.add_trace(go.Bar(y=df_most_bought_last_hour["datetime"].astype(str), x=df_most_bought_last_hour["count"], orientation="h", name="Most Bought Last Hour"))
    fig_most_bought_last_hour.update_layout(
        title="Produtos Mais Comprados na Última Hora",
        xaxis=dict(title="Quantidade Comprada"),
        yaxis=dict(autorange="reversed", title="ID do Produto")
    )

    fig_most_viewed_last_hour = go.Figure()
    fig_most_viewed_last_hour.add_trace(go.Bar(y=df_most_viewed_last_hour["datetime"].astype(str), x=df_most_viewed_last_hour["count"], orientation="h", name="Most Viewed Last Hour"))
    fig_most_viewed_last_hour.update_layout(
        title="Produtos Mais Visualizados na Última Hora",
        xaxis=dict(title="Quantidade de Visualizações"),
        yaxis=dict(autorange="reversed", title="ID do Produto")
    )

    fig_avg_views_before_purchase = go.Figure()
    fig_avg_views_before_purchase.add_trace(go.Scatter(x=df_avg_views_before_purchase["datetime"].astype(str), y=df_avg_views_before_purchase["count"], mode="lines+markers", name="Average Views Before Purchase"))
    fig_avg_views_before_purchase.update_layout(
        title="Média de Visualizações Antes da Compra",
        xaxis=dict(title="ID do Produto"),
        yaxis=dict(title="Média de Visualizações")
    )

    return (
        fig_viewed_per_minute,
        fig_bought_per_minute,
        fig_unique_users_per_product,
        fig_most_bought_last_hour,
        fig_most_viewed_last_hour,
        fig_avg_views_before_purchase
    )


@callback(
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
