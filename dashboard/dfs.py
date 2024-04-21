import pandas as pd
import numpy as np

# Data and time range simulation
time_range = pd.date_range(start="2023-04-21 09:00", end="2023-04-21 09:59", freq='T')

# 1. Number of products viewed per minute
df_viewed_per_minute = pd.DataFrame({
    'Time': time_range,
    'Viewed': np.random.randint(50, 100, size=len(time_range))
})

# 2. Number of products bought per minute
df_bought_per_minute = pd.DataFrame({
    'Time': time_range,
    'Bought': np.random.randint(10, 30, size=len(time_range))
})

# 3. Number of unique users viewing each product per minute
df_unique_users_per_product = pd.DataFrame({
    'Time': time_range,
    'ProductID': np.random.randint(1, 21, size=len(time_range)),
    'UniqueUsers': np.random.randint(1, 50, size=len(time_range))
})

# 4. Ranking of products most bought in the last hour
df_most_bought_last_hour = pd.DataFrame({
    'ProductID': np.random.randint(1, 21, size=10),
    'BoughtCount': np.random.randint(20, 50, size=10)
}).sort_values(by='BoughtCount', ascending=False).reset_index(drop=True)

# 5. Ranking of products most viewed in the last hour
df_most_viewed_last_hour = pd.DataFrame({
    'ProductID': np.random.randint(1, 21, size=10),
    'ViewCount': np.random.randint(100, 200, size=10)
}).sort_values(by='ViewCount', ascending=False).reset_index(drop=True)

# 6. Average number of views before a purchase
df_avg_views_before_purchase = pd.DataFrame({
    'ProductID': np.random.randint(1, 21, size=10),
    'AvgViews': np.random.randint(5, 15, size=10)
})

# 7. Number of products sold without stock
sold_out_data = {
    'ProductID': np.random.randint(1, 21, size=20),
    'SoldOutCount': np.random.randint(1, 10, size=20)
}
df_sold_out_temp = pd.DataFrame(sold_out_data)
df_sold_out = df_sold_out_temp.groupby('ProductID').sum().reset_index()

# Displaying the created DataFrames
dfs = {
    "Products Viewed per Minute": df_viewed_per_minute,
    "Products Bought per Minute": df_bought_per_minute,
    "Unique Users Viewing Each Product": df_unique_users_per_product,
    "Ranking of Most Bought Products (Last Hour)": df_most_bought_last_hour,
    "Ranking of Most Viewed Products (Last Hour)": df_most_viewed_last_hour,
    "Average Views Before Purchase": df_avg_views_before_purchase,
    "Sold Out Products Count": df_sold_out
}