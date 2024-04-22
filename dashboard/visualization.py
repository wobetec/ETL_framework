from dfs import df_avg_views_before_purchase
from dfs import df_bought_per_minute
from dfs import df_most_bought_last_hour
from dfs import df_most_viewed_last_hour
from dfs import df_sold_out
from dfs import df_unique_users_per_product
from dfs import df_viewed_per_minute

import pandas as pd
import numpy as np
from datetime import datetime, timedelta
import dash
from dash import dcc, html
from dash.dependencies import Input, Output
import plotly.graph_objs as go
from datetime import datetime


# Simulação de dados por minuto
def fetch_data_viewed_per_minute():
    new_time = datetime.now()
    new_viewed = np.random.randint(50, 100)
    return pd.DataFrame({"Time": [new_time], "Viewed": [new_viewed]})

def fetch_data_bought_per_minute():
    new_time = datetime.now()
    new_bought = np.random.randint(10, 30)
    return pd.DataFrame({"Time": [new_time], "Bought": [new_bought]})

def fetch_data_unique_users_per_product():
    new_time = datetime.now()
    new_product_id = np.random.randint(1, 21)
    new_unique_users = np.random.randint(1, 50)
    return pd.DataFrame({"Time": [new_time], "ProductID": [new_product_id], "UniqueUsers": [new_unique_users]})

def fetch_data_most_bought_last_hour():
    new_product_id = np.random.choice(range(1, 21), 10)
    new_bought_count = np.random.randint(20, 50, size=10)
    return pd.DataFrame({"ProductID": new_product_id, "BoughtCount": new_bought_count}).sort_values(by="BoughtCount", ascending=False)

def fetch_data_most_viewed_last_hour():
    new_product_id = np.random.choice(range(1, 21), 10)
    new_view_count = np.random.randint(100, 200, size=10)
    return pd.DataFrame({"ProductID": new_product_id, "ViewCount": new_view_count}).sort_values(by="ViewCount", ascending=False)

def fetch_data_sold_out():
    new_product_id = np.random.choice(range(1, 21), 5)
    new_sold_out_count = np.random.randint(1, 10, size=5)
    return pd.DataFrame({"ProductID": new_product_id, "SoldOutCount": new_sold_out_count})

def fetch_data_avg_views_before_purchase():
    new_product_id = np.random.choice(range(1, 21))
    new_avg_views = np.random.randint(5, 15)
    return pd.DataFrame({"ProductID": [new_product_id], "AvgViews": [new_avg_views]})

app = dash.Dash(__name__)

app.layout = html.Div([
    html.H1("Dashboard de Monitoramento em Tempo Real"),
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
    html.Div([
        dcc.Graph(id="graph-sold-out"),
        dcc.Interval(id="interval-sold-out", interval=10*1000, n_intervals=0)
    ])
])


@app.callback(Output("graph-viewed-per-minute", "figure"),
              Input("interval-viewed-per-minute", "n_intervals"))
def update_graph_viewed_per_minute(n):
    global df_viewed_per_minute
    new_data = fetch_data_viewed_per_minute()
    df_viewed_per_minute = pd.concat([df_viewed_per_minute, new_data])

    cutoff_time = datetime.now() - timedelta(minutes=10)
    df_viewed_per_minute = df_viewed_per_minute[df_viewed_per_minute["Time"] > cutoff_time]

    fig = go.Figure()
    fig.add_trace(go.Scatter(x=df_viewed_per_minute["Time"], y=df_viewed_per_minute["Viewed"], mode="lines+markers", name="Viewed per Minute"))
    fig.update_layout(
        title="Número de Produtos Visualizados por Minuto",
        xaxis=dict(
            type="date",
            tickformat="%H:%M",
            dtick=60000
        ),
        yaxis=dict(
            title="Número de Visualizações",
        )
        )

    return fig

@app.callback(Output("graph-bought-per-minute", "figure"),
              Input("interval-bought-per-minute", "n_intervals"))
def update_graph_bought_per_minute(n):
    global df_bought_per_minute
    new_data = fetch_data_bought_per_minute()
    df_bought_per_minute = pd.concat([df_bought_per_minute, new_data])
    cutoff_time = datetime.now() - timedelta(minutes=10)
    df_bought_per_minute = df_bought_per_minute[df_bought_per_minute["Time"] > cutoff_time]
    fig = go.Figure()
    fig.add_trace(go.Scatter(x=df_bought_per_minute["Time"], y=df_bought_per_minute["Bought"], mode="lines+markers", name="Bought per Minute"))
    fig.update_layout(
        title="Número de Produtos Comprados por Minuto",
        xaxis=dict(
            type="date",
            tickformat="%H:%M",
            dtick=60000
        ),
        yaxis=dict(
            title="Número de Compras",
        )
    )
    return fig

@app.callback(Output("graph-unique-users-per-product", "figure"),
              Input("interval-unique-users-per-product", "n_intervals"))
def update_graph_unique_users_per_product(n):
    global df_unique_users_per_product
    new_data = fetch_data_unique_users_per_product()
    df_unique_users_per_product = pd.concat([df_unique_users_per_product, new_data])
    cutoff_time = datetime.now() - timedelta(minutes=10)
    df_unique_users_per_product = df_unique_users_per_product[df_unique_users_per_product["Time"] > cutoff_time]
    fig = go.Figure()
    fig.add_trace(go.Scatter(x=df_unique_users_per_product["Time"], y=df_unique_users_per_product["UniqueUsers"], mode="lines+markers", name="Unique Users per Product"))
    fig.update_layout(
        title="Número de Usuários Únicos por Produto",
        xaxis=dict(
            type="date",
            tickformat="%H:%M",
            dtick=60000
        ),
        yaxis=dict(
            title="Número de Usuários Únicos",
        )
    )
    return fig

@app.callback(Output("graph-avg-views-before-purchase", "figure"),
              Input("interval-avg-views-before-purchase", "n_intervals"))
def update_graph_avg_views_before_purchase(n):
    global df_avg_views_before_purchase
    new_data = fetch_data_avg_views_before_purchase()
    new_data["Time"] = datetime.now()
    df_avg_views_before_purchase = pd.concat([df_avg_views_before_purchase, new_data])
    cutoff_time = datetime.now() - timedelta(minutes=10)
    df_avg_views_before_purchase = df_avg_views_before_purchase[df_avg_views_before_purchase["Time"] > cutoff_time]
    fig = go.Figure()
    fig.add_trace(go.Scatter(x=df_avg_views_before_purchase["Time"], y=df_avg_views_before_purchase["AvgViews"], mode="lines+markers", name="Average Views Before Purchase"))
    fig.update_layout(
        title="Média de Visualizações Antes da Compra",
        xaxis=dict(
            type="date",
            tickformat="%H:%M",
            dtick=60000
        ),
        yaxis=dict(
            title="Média de Visualizações",
        )
    )
    return fig

@app.callback(Output("graph-most-bought-last-hour", "figure"),
              Input("interval-most-bought-last-hour", "n_intervals"))
def update_graph_most_bought_last_hour(n):
    global df_most_bought_last_hour
    new_data = fetch_data_most_bought_last_hour()
    df_most_bought_last_hour = pd.concat([df_most_bought_last_hour, new_data])
    df_most_bought_last_hour = df_most_bought_last_hour.groupby('ProductID').sum().reset_index()
    df_most_bought_last_hour.sort_values(by='BoughtCount', ascending=False, inplace=True)
    df_most_bought_last_hour = df_most_bought_last_hour.head(10)

    fig = go.Figure()
    fig.add_trace(go.Bar(y=df_most_bought_last_hour["ProductID"].astype(str), x=df_most_bought_last_hour["BoughtCount"], orientation='h', name="Most Bought Last Hour"))
    fig.update_layout(
        title="Produtos Mais Comprados na Última Hora",
        xaxis=dict(title="Quantidade Comprada"),
        yaxis=dict(autorange="reversed", title="ID do Produto"),
    )
    return fig

@app.callback(Output("graph-most-viewed-last-hour", "figure"),
              Input("interval-most-viewed-last-hour", "n_intervals"))
def update_graph_most_viewed_last_hour(n):
    global df_most_viewed_last_hour
    new_data = fetch_data_most_viewed_last_hour()
    df_most_viewed_last_hour = pd.concat([df_most_viewed_last_hour, new_data])
    df_most_viewed_last_hour = df_most_viewed_last_hour.groupby('ProductID').sum().reset_index()
    df_most_viewed_last_hour.sort_values(by='ViewCount', ascending=False, inplace=True)
    df_most_viewed_last_hour = df_most_viewed_last_hour.head(10)

    fig = go.Figure()
    fig.add_trace(go.Bar(y=df_most_viewed_last_hour["ProductID"].astype(str), x=df_most_viewed_last_hour["ViewCount"], orientation='h', name="Most Viewed Last Hour"))
    fig.update_layout(
        title="Produtos Mais Visualizados na Última Hora",
        xaxis=dict(title="Quantidade de Visualizações"),
        yaxis=dict(autorange="reversed", title="ID do Produto")
    )
    return fig

@app.callback(Output("graph-sold-out", "figure"),
              Input("interval-sold-out", "n_intervals"))
def update_graph_sold_out(n):
    global df_sold_out
    new_data = fetch_data_sold_out()
    new_data["Time"] = datetime.now().replace(second=0, microsecond=0)

    df_sold_out = pd.concat([df_sold_out, new_data])
    
    df_sold_out_aggregated = df_sold_out.groupby('Time').agg({'SoldOutCount': 'sum'}).reset_index()

    cutoff_time = datetime.now() - timedelta(minutes=10)
    df_sold_out_aggregated = df_sold_out_aggregated[df_sold_out_aggregated["Time"] > cutoff_time]

    fig = go.Figure()
    fig.add_trace(go.Scatter(x=df_sold_out_aggregated["Time"], y=df_sold_out_aggregated["SoldOutCount"], mode="lines+markers", name="Sold Out Products"))
    fig.update_layout(
        title="Número de Produtos Vendidos Sem Estoque por Minuto",
        xaxis=dict(
            type="date",
            tickformat="%H:%M",
            dtick=60000
        ),
        yaxis=dict(
            title="Número de Produtos Vendidos Sem Estoque",
        )
    )
    return fig


if __name__ == "__main__":
    app.run_server(debug=True)