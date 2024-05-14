import time
import numpy as np
import pandas as pd
from datetime import timedelta
from datetime import datetime
import os
import fcntl
import shutil

from users import UserGenerator
from products import ProductGenerator


def save(df, file_path, sep=';'):
    with open(file_path, 'w') as f:
        try:
            fcntl.flock(f, fcntl.LOCK_EX)
            df.to_csv(f, index=False, sep=sep, header=True, mode='w')
        finally:
            fcntl.flock(f, fcntl.LOCK_UN)


class Simulation:

    main_folder = 'data'

    subfolders = ['datacat', 'cadeanalytics', 'contaverde']

    subsubfolders = ['audit', 'behavior', 'failings']


    def __init__(self, user_min=0, user_max=1000, product_min=0, product_max=1000):
        # First load of data
        self.user_generator = UserGenerator()
        self.users = pd.DataFrame([self.user_generator.generate_user(i) for i in range(user_min, user_max)])

        self.product_generator = ProductGenerator()
        self.products = pd.DataFrame([self.product_generator.generate_product(i) for i in range(product_min, product_max)])
        
        self.stock = self.products[['product_id']].copy()
        self.stock['available_quantity'] = np.random.randint(100, 1000, len(self.stock))

        self.orders = pd.DataFrame(columns=['user_id', 'product_id', 'order_quantity', 'order_creation_date', 'order_payment_date', 'order_deliver_date'])
    
    
    def create_folders(self):
        for folder in self.subfolders:
            folder_path = os.path.join(self.main_folder, folder)
            os.makedirs(folder_path, exist_ok=True)

        for folder in self.subsubfolders:
            folder_path = os.path.join(self.main_folder, 'datacat', folder)
            os.makedirs(folder_path, exist_ok=True)


    def delete_folders(self):
        try:
            shutil.rmtree(self.main_folder)
        except:
            pass


    def clear_old_logs(self, waiting_time):
        current_time = time.time()
        for root, dirs, files in os.walk(os.path.join(self.main_folder, 'datacat')):
            for file in files:
                file_path = os.path.join(root, file)
                creation_time = os.path.getctime(file_path)
                if current_time - creation_time > waiting_time:
                    os.remove(file_path)


    def get_stimulus(self):
        stimuli = ['Click', 'Hover', 'Type', 'Scroll', 'Swipe', 'Visualization']
        return stimuli[np.random.randint(0, len(stimuli))]
    

    def get_target_component(self):
        components = ['Button', 'Menu', 'Form', 'Image', 'Link']
        return components[np.random.randint(0, len(components))]
    

    def get_behavior_message(self, stimulus, name, target_component):
        product_id = None
        
        if stimulus == 'Click':
            phrases = f"{name} clicked on {target_component} component"
        elif stimulus == 'Type':
            phrases = f"{name} searched for {target_component}"
        elif stimulus == 'Hover':
            phrases = f"{name} hovered over {target_component}"
        elif stimulus == 'Scroll':
            phrases = f"{name} scrolled over {target_component}"
        elif stimulus == 'Swipe':
            phrases = f"{name} swiped {target_component}"
        elif stimulus == 'Visualization':
            product_id = self.products.sample(1)['product_id'].values[0]
            phrases = f"User {name} visualized {product_id}"
        else:
            phrases = f"No behavior captured from {name} after 15 seconds"
            
        return phrases, product_id


    def gen_datacat(self, num_events):

        num_log_behavior = num_events

        # Behavior
        df_behavior = []
        visualized_products = []
        for i in range(num_log_behavior):
            event_type = 'behavior'
            notification_date = datetime.now()
            user_id = self.users['user_id'].iloc[np.random.randint(0, self.users.shape[0])]
            stimulus = self.get_stimulus()
            target_component = self.get_target_component()
            message, product_id = self.get_behavior_message(stimulus, user_id, target_component)
            if product_id is not None:
                visualized_products.append({
                    'user_id': user_id,
                    'product_id': product_id
                })
            df_behavior.append({
                'notification_date': notification_date,
                'event_type': event_type,
                'message': message,
                'user_id': user_id,
                'stimulus': stimulus,
                'target_component': target_component
            })
        end_date = datetime.now()
        file_name = f"log_behavior_{end_date.strftime('%Y-%m-%d_%H-%M-%S')}.txt"
        csv_path = os.path.join('data', 'datacat', 'behavior', file_name)
        df_behavior = pd.DataFrame(df_behavior)
        save(df_behavior, csv_path, sep=';')
            
        return pd.DataFrame(visualized_products)


    def gen_cadeanalytics(self, num_events):

        df_cadeanalytics = []
        visualized_products = []
        for i in range(num_events):
            event_type = 'cadeanalytics'
            notification_date = datetime.now()
            user_id = self.users.sample(1)['user_id'].values[0]
            stimulus = self.get_stimulus()
            if stimulus == 'Visualization':
                product_id = self.products.sample(1)['product_id'].values[0]
                visualized_products.append({
                    'user_id': user_id,
                    'product_id': product_id
                })
                stimulus = f'{stimulus} {product_id}'
            target_component = self.get_target_component()
            df_cadeanalytics.append({
                'notification_date': notification_date,
                'event_type': event_type,
                'user_id': user_id,
                'stimulus': stimulus,
                'target_component': target_component
            })
        csv_path = os.path.join('data', 'cadeanalytics', "cade_analytics.txt")
        df_cadeanalytics = pd.DataFrame(df_cadeanalytics)
        save(df_cadeanalytics, csv_path, sep=';')

        return pd.DataFrame(visualized_products)
    

    def update_orders(self, visualized_products):
        new_orders = []
        n_orders = np.random.randint(0, np.round(np.sqrt(visualized_products.shape[0])))
        visualized_products = visualized_products.sample(n_orders)
        for index, row in visualized_products.iterrows():
            user_id = row['user_id']
            product_id = row['product_id']
            quantity = np.random.randint(1, 8)
            creation_date = datetime.now()
            payment_date = datetime.now() + timedelta(hours= np.random.randint(1, 24 * 3))
            deliver_date = payment_date + timedelta(hours= np.random.randint(1, 24 * 4))
            new_orders.append({
                'user_id': user_id,
                'product_id': product_id,
                'order_quantity': quantity,
                'order_creation_date': creation_date,
                'order_payment_date': payment_date,
                'order_deliver_date': deliver_date
            })
        new_orders = pd.DataFrame(new_orders)
        if self.orders.shape[0] == 0:
            self.orders = new_orders
        else:
            self.orders = pd.concat([self.orders, new_orders], ignore_index=True)
        file_name = 'orders.txt'
        csv_path = os.path.join('data', 'contaverde', file_name)
        save(new_orders, csv_path, sep=',')
        return new_orders


    def update_stock(self, new_orders):
        # Add random
        for i in range(np.random.randint(0, 1+np.round(np.sqrt(new_orders.shape[0])))):
            product_id = self.products.sample(1)['product_id'].values[0]
            quantity = np.random.randint(1, 10)
            stock_index = self.stock[self.stock['product_id'] == product_id].index[0]
            self.stock.loc[stock_index, 'available_quantity'] += quantity

        # Remove
        for index, order in new_orders.iterrows():
            product_id = order['product_id']
            quantity = order['order_quantity']
            stock_index = self.stock[self.stock['product_id'] == product_id].index[0]
            self.stock.loc[stock_index, 'available_quantity'] -= quantity


    def save_contaverde(self):
        contaverde_path = os.path.join('data', 'contaverde')

        save(self.users, os.path.join(contaverde_path, 'users.txt'), sep=',')
        save(self.products, os.path.join(contaverde_path, 'products.txt'), sep=',')
        save(self.stock, os.path.join(contaverde_path, 'stock.txt'), sep=',')
        save(self.orders, os.path.join(contaverde_path, 'orders.txt'), sep=',')


    def run(self, num_events):
        # Generate events
        start_time = time.perf_counter()
        vis_datacat = self.gen_datacat(num_events//2)
        print(f"\tDatacat time: {time.perf_counter() - start_time}")
        start_time = time.perf_counter()
        vis_cadeanalytics = self.gen_cadeanalytics(num_events//2)
        print(f"\tCadeanalytics time: {time.perf_counter() - start_time}")

        # Generate purchase orders based on visualizations events
        start_time = time.perf_counter()
        new_orders = self.update_orders(pd.concat([vis_datacat, vis_cadeanalytics], ignore_index=True))
        print(f"\tOrders time: {time.perf_counter() - start_time}")
        start_time = time.perf_counter()
        self.update_stock(new_orders)
        print(f"\tStock time: {time.perf_counter() - start_time}")

        # Save data
        self.save_contaverde()


if __name__ == '__main__':
    start_time = time.perf_counter()
    simulation = Simulation()
    simulation.delete_folders()
    simulation.create_folders()
    print(f"Initialization time: {time.perf_counter() - start_time}")

    # Main loop
    while True:
        start_time = time.perf_counter()
        num_events = np.random.randint(1000, 10000)
        simulation.run(num_events)
        simulation.clear_old_logs(120)
        print(f"Execution step time: {time.perf_counter() - start_time}")
