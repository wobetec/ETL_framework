import random
import time
import numpy as np
import pandas as pd
from names_generator import generate_name
from random_address import real_random_address
from random import randrange
from datetime import timedelta
from datetime import datetime
import os

main_folder = 'data'

subfolders = ['datacat', 'datacat', 'datacat', 'cadeanalytics', 'contaverde']

subsubfolders = ['audit', 'behaviour', 'failings']

if not os.path.exists(main_folder):
    os.mkdir(main_folder)

for folder in subfolders:
    folder_path = os.path.join(main_folder, folder)
    if not os.path.exists(folder_path):
        os.mkdir(folder_path)

for folder in subsubfolders:
    folder_path = os.path.join(main_folder, 'datacat', folder)
    if not os.path.exists(folder_path):
        os.mkdir(folder_path)
        
def delete_old_files(folder_path, waiting_time):
    current_time = time.time()
    for root, dirs, files in os.walk(folder_path):
        for file in files:
            file_path = os.path.join(root, file)
            creation_time = os.path.getctime(file_path)
            if current_time - creation_time > waiting_time:
                os.remove(file_path)

id_names = {f'{i}': generate_name(style='capital')  for i in range(1000, 6000)}
list_ids = list(id_names.keys())

product = {
    1001: "Laptop",
    1002: "Smartphone",
    1003: "Headphones",
    1004: "Tablet",
    1005: "Smartwatch",
    1006: "Camera",
    1007: "Printer",
    1008: "External Hard Drive",
    1009: "Wireless Mouse",
    1010: "Keyboard",
    1011: "Monitor",
    1012: "Gaming Console",
    1013: "Fitness Tracker",
    1014: "Bluetooth Speaker",
    1015: "Power Bank",
    1016: "Drone",
    1017: "Virtual Reality Headset",
    1018: "Digital Camera",
    1019: "Soundbar",
    1020: "Router",
    1021: "External SSD",
    1022: "Action Camera",
    1023: "Gaming Mouse",
    1024: "Gaming Keyboard",
    1025: "Graphics Card",
    1026: "Fitness Watch",
    1027: "Bluetooth Earbuds",
    1028: "Wireless Headphones",
    1029: "Smart Home Speaker",
    1030: "Portable Projector",
    1031: "Computer Case",
    1032: "Gaming Chair",
    1033: "Mechanical Keyboard",
    1034: "Gaming Monitor",
    1035: "Gaming Laptop",
    1036: "SSD Drive",
    1037: "Wireless Router",
    1038: "Fitness Band",
    1039: "Gaming Headset",
    1040: "Portable SSD"
}

products = list(product.values())

def genEventType():
    eventType = ['audit', 'behavior', 'failings']
    return random.choice(eventType)

def genAction():
    actions = ['Login', 'Logout', 'Update', 'Delete', 'Add', 'Search', 'Purchase']
    return random.choice(actions)

def genLineCode():
    return random.randint(1000, 9999)

def genStimulus():
    stimuli = ['Visualization', 'Click', 'Hover', 'Type', 'Scroll', 'Swipe']
    return random.choice(stimuli)

def genSeverity():
    severities = ['Low', 'Medium', 'High', 'Critical']
    return random.choice(severities)

def genTargetComp():
    components = ['Button', 'Menu', 'Form', 'Image', 'Link']
    return random.choice(components)

def genRandDate(start, end):
    delta = end - start
    int_delta = (delta.days * 24 * 60 * 60) + delta.seconds
    random_second = randrange(int_delta)
    return start + timedelta(seconds=random_second)

def genErrorMsg():
    errors = [
        "Database connection lost",
        "Invalid input data",
        "Server timeout",
        "File not found",
        "Access denied"
    ]
    return random.choice(errors)

def genAuditMessage(action, name, prod): 
    phrases = None

    if action == 'Login': 
        phrases = "User {username} logged in."
        #name = random.choice(id_names.values())
        return phrases.format(username = name)
    elif action == 'Logout':
        phrases = "User {username} logged out."
        #name = random.choice(id_names.values())
        return phrases.format(username = name)
        
    elif action == 'Update':
        phrases = "User {username} updated settings."
        #name = random.choice(id_names.values())
        return phrases.format(username = name)
    elif action == 'Delete':
        phrases = "User {username} deleted a product from the cart."
        #name = random.choice(id_names.values())
        return phrases.format(username = name)
    elif action == 'Add':
        phrases = "User {username} added a product to the cart."
        #name = random.choice(id_names.values())
        return phrases.format(username = name)
    elif action == 'Search':
        phrases = "User {username} searched for a product."
        #name = random.choice(id_names.values())
        return phrases.format(username = name)
    elif action == 'Purchase':
        phrases = "User {username} purchased {Product}."
        return phrases.format(username=name, Product=prod)
    #elif action == 'Visualization':
    #    phrases = "User {username} visualized {Product}."
    #    return phrases.format(username=name, Product=prod)
    else:
        phrases = "User {username} did not make any action after 15 seconds."
        #name = random.choice(id_names.values())
        return phrases.format(username = name)
            
def genFailureMsessage(message):

    if message=='Database connection lost':
        phrases = "Error: {error_message} occurred in {target} module."
        return phrases.format(error_message='Database connection lost',target=genTargetComp())
    elif message=='Invalid input data':
        phrases = "Error: {error_message} occurred in {target} module."
        return phrases.format(error_message='Invalid input data',target=genTargetComp())
    elif message=='Server timeout':
        phrases = "Error: {error_message} occurred in {target} module."
        return phrases.format(error_message='Server timeout',target=genTargetComp())
    elif message=='File not found':
        phrases = "Error: {error_message} occurred in {target} module."
        return phrases.format(error_message='File not found',target=genTargetComp())
    elif message=='Access denied':
        phrases = "Error: {error_message} occurred in {target} module."
        return phrases.format(error_message='Access denied',target=genTargetComp())
    else:
        return "No imediate failings found. Please, try again."
        
def genBehaviorMessage(stimulus, name):
    if stimulus == 'Click':
        phrases = "{username} clicked on {target} component."
        return phrases.format(username =  name, target = genTargetComp())
    elif stimulus == 'Type':
        phrases = "{username} searched for {target}."
        return phrases.format(username = name, target = genTargetComp())
    elif stimulus == 'Hover':
        phrases = "{username} hovered over {target}."
        return phrases.format(username = name, target = genTargetComp())
    elif stimulus == 'Scroll':
        phrases = "{username} scrolled over {target}."
        return phrases.format(username = name, target = genTargetComp())
    elif stimulus == 'Swipe':
        phrases = "{username} swiped {target}."
        return phrases.format(username = name, target = genTargetComp())
    elif stimulus == 'Visualization':
        phrases = "User {username} visualized {prod}."
        return phrases.format(username=name, prod= random.choice(list(product.keys())))
    #else:
    #    phrases = "No behavior captured from {username} after 15 seconds."
    #    return phrases.format(username = name)


def gen_logaudit(num_events, interval_minutes=30):
    start_date = datetime.now()
    end_date = start_date+timedelta(seconds=interval_minutes)
    interval_start = start_date
    interval_end = start_date + timedelta(seconds=interval_minutes)
    
    simulated_data = []
    for k in range(num_events):
        event_type = 'audit'
        notification_date = datetime.now()
        user_id = random.choice(list_ids) #audit, behavior
        action = genAction() #audit
        product = random.choice(products)
        message = genAuditMessage(action, id_names[user_id], product)
        
        event_data = {'notification_date': notification_date.strftime('%Y-%m-%d %H:%M:%S'), 'event_type': event_type, 'message': message,  'user_id': user_id, 'action': action}
        
        simulated_data.append(event_data)
        df = pd.DataFrame(data = simulated_data, columns = event_data.keys())
        df['notification_date'] = sorted(df['notification_date'])
        time = datetime.now()
        if time > interval_end:
            file_name = f"log_{event_type}_{start_date.strftime('%Y-%m-%d_%H-%M-%S')}.txt"
            csv_path = os.path.join('data', 'datacat/audit', file_name)
            df.to_csv(csv_path, index=False, sep=';')
            return df
        elif k==num_events-1: 
            file_name = f"log_{event_type}_{start_date.strftime('%Y-%m-%d_%H-%M-%S')}.txt"
            csv_path = os.path.join('data', 'datacat/audit', file_name)
            df.to_csv(csv_path, index=False, sep=';')
            return df

def gen_logbehavior(num_events, interval_minutes=30):
    start_date = datetime.now()
    end_date = start_date+timedelta(seconds=interval_minutes)
    interval_start = start_date
    interval_end = start_date + timedelta(seconds=interval_minutes)
    #print(interval_end)
    
    simulated_data = []
    for k in range(num_events):
        event_type = 'behavior'
        notification_date = datetime.now()
        user_id = random.choice(list_ids) #audit, behavior
        stimulus = genStimulus() #behavior
        target_component = genTargetComp() #behavior, failings
        #product = random.choice(products)
        message = genBehaviorMessage(stimulus, id_names[user_id])
        
        event_data = {'notification_date': notification_date.strftime('%Y-%m-%d %H:%M:%S'), 'event_type': event_type, 'message': message, 'user_id': user_id, 'stimulus': stimulus, 'target_component': target_component}
        
        simulated_data.append(event_data)
        df = pd.DataFrame(data = simulated_data, columns = event_data.keys())
        df['notification_date'] = sorted(df['notification_date'])
        time = datetime.now()
        if time > interval_end:
            file_name = f"log_{event_type}_{start_date.strftime('%Y-%m-%d_%H-%M-%S')}.txt"
            csv_path = os.path.join('data', 'datacat/behaviour', file_name)
            df.to_csv(csv_path, index=False, sep=';')
            return df
        elif k==num_events-1: 
            file_name = f"log_{event_type}_{start_date.strftime('%Y-%m-%d_%H-%M-%S')}.txt"
            csv_path = os.path.join('data', 'datacat/behaviour', file_name)
            df.to_csv(csv_path, index=False, sep=';')
    return df

def gen_logfailings(num_events, interval_minutes=30):
    start_date = datetime.now()
    end_date = start_date+timedelta(seconds=interval_minutes)
    interval_start = start_date
    interval_end = start_date + timedelta(seconds=interval_minutes)
    
    simulated_data = []
    for k in range(num_events):
        event_type = 'failure'
        notification_date = datetime.now()
        target_component = genTargetComp() #behavior, failings
        linecode = genLineCode() #failings
        severity = genSeverity() #failings
        err = genErrorMsg()
        message = genFailureMsessage(err)
        
        event_data = {'notification_date': notification_date.strftime('%Y-%m-%d %H:%M:%S'), 'event_type': event_type, 'message': message, 'target_component': target_component, 'linecode': linecode, 'severity': severity}
        
        simulated_data.append(event_data.values())

        df = pd.DataFrame(data = simulated_data, columns = event_data.keys())
        df['notification_date'] = sorted(df['notification_date'])

        time = datetime.now()
        if time > interval_end:
            file_name = f"log_{event_type}_{start_date.strftime('%Y-%m-%d_%H-%M-%S')}.txt"
            csv_path = os.path.join('data', 'datacat/failings', file_name)
            df.to_csv(csv_path, index=False, sep=';')
            return df
        elif k==num_events-1: 
            file_name = f"log_{event_type}_{start_date.strftime('%Y-%m-%d_%H-%M-%S')}.txt"
            csv_path = os.path.join('data', 'datacat/failings', file_name)
            df.to_csv(csv_path, index=False, sep=';')
    return df

def gen_randomlog(num_events):
    p = np.random.uniform(0,1/3)
    q = np.random.uniform(0,1-p)
    r = 1-p-q
    gen_logfailings(int(num_events*p))
    gen_logbehavior(int(num_events*q))
    gen_logaudit(int(num_events*r))

#CADEANALYTICS
def genStimulus():
    stimuli = ['Click', 'Hover', 'Type', 'Scroll', 'Swipe', 'Visualization']
    return random.choice(stimuli)

def genTargetComp():
    components = ['Button', 'Menu', 'Form', 'Image', 'Link']
    return random.choice(components)

def gen_cadeanalytics(num_events):
    start_date = datetime(2020, 1, 1)
    end_date = datetime(2024, 4, 22)
    
    simulated_data = []
    for _ in range(num_events):
        notification_date = datetime.now()
        user_id = random.choice(list_ids)
        stimulus = genStimulus()
        if stimulus=='Visualization':
            stimulus = 'Visualized {product}. '
            stimulus = stimulus.format(product=random.choice(list(product.keys())))
        target_component = genTargetComp()
        
        event_data = {'notification_date': notification_date.strftime('%Y-%m-%d %H:%M:%S'), 'user_id': user_id, 'stimulus': stimulus, 'target_component': target_component}
        
        simulated_data.append(event_data.values())
        df = pd.DataFrame(data = simulated_data, columns = event_data.keys())
        date = datetime.now()
        file_name = "cade_analytics.txt"
        csv_path = os.path.join('data', 'cadeanalytics', file_name)
        df.to_csv(csv_path, index=False, sep=';')


#CONTAVERDE        
product = {
    1001: "Laptop",
    1002: "Smartphone",
    1003: "Headphones",
    1004: "Tablet",
    1005: "Smartwatch",
    1006: "Camera",
    1007: "Printer",
    1008: "External Hard Drive",
    1009: "Wireless Mouse",
    1010: "Keyboard",
    1011: "Monitor",
    1012: "Gaming Console",
    1013: "Fitness Tracker",
    1014: "Bluetooth Speaker",
    1015: "Power Bank",
    1016: "Drone",
    1017: "Virtual Reality Headset",
    1018: "Digital Camera",
    1019: "Soundbar",
    1020: "Router",
    1021: "External SSD",
    1022: "Action Camera",
    1023: "Gaming Mouse",
    1024: "Gaming Keyboard",
    1025: "Graphics Card",
    1026: "Fitness Watch",
    1027: "Bluetooth Earbuds",
    1028: "Wireless Headphones",
    1029: "Smart Home Speaker",
    1030: "Portable Projector",
    1031: "Computer Case",
    1032: "Gaming Chair",
    1033: "Mechanical Keyboard",
    1034: "Gaming Monitor",
    1035: "Gaming Laptop",
    1036: "SSD Drive",
    1037: "Wireless Router",
    1038: "Fitness Band",
    1039: "Gaming Headset",
    1040: "Portable SSD"
}

product_stock = [
    5000,  # Laptop
    10000,  # Smartphone
    20000,  # Headphones
    15000,  # Tablet
    12000,  # Smartwatch
    8000,  # Camera
    1000,  # Printer
    1500,  # External Hard Drive
    20000,  # Wireless Mouse
    18000,  # Keyboard
    9000,  # Monitor
    6000,  # Gaming Console
    1500,  # Fitness Tracker
    2000,  # Bluetooth Speaker
    3000,  # Power Bank
    700,  # Drone
    800,  # Virtual Reality Headset
    1000,  # Digital Camera
    1500,  # Soundbar
    2000,  # Router
    15000,  # External SSD
    7000,  # Action Camera
    2000,  # Gaming Mouse
    1800,  # Gaming Keyboard
    800,  # Graphics Card
    1500,  # Fitness Watch
    2000,  # Bluetooth Earbuds
    1200,  # Wireless Headphones
    1500,  # Smart Home Speaker
    5000,  # Portable Projector
    2000,  # Computer Case
    6000,  # Gaming Chair
    1800,  # Mechanical Keyboard
    9000,  # Gaming Monitor
    4000,  # Gaming Laptop
    15000,  # SSD Drive
    1800,  # Wireless Router
    2000,  # Fitness Band
    1500,  # Gaming Headset
    1000  # Portable SSD
]

product_dict = dict(zip(list(product.values()), product_stock))

def gen_contaverde_users(num_events):
    df_audit = gen_logaudit(num_events)
    df_behavior = gen_logbehavior(num_events)
    user_id = pd.concat((df_audit['user_id'], df_behavior['user_id']))
    names = []
    last_names = []
    address = []
    start_date1 = datetime(2015, 1, 1)
    end_date1 = datetime(2024, 4, 22)
    start_date2 = datetime(1960, 1, 1)
    end_date2 = datetime(2000, 1, 1)
    register_day = []
    birth_day = []
    for i in range(2*num_events):
        full_name = random.choice(list(id_names.values()))
        name, last_name = full_name.split()
        names.append(name)
        last_names.append(last_name)
        addresses_dict = real_random_address()
        addresses = [addresses_dict['address1']]
        address.append(random.choice(addresses))
        register_day.append(datetime.now())
        birth_day.append(datetime.now())
        
    users = pd.DataFrame({'user_id': user_id, 'name': names, 'last_name': last_names, 'address': address, 'registar_day': register_day, 'birth_day': birth_day})
    file_name = 'users.txt'
    csv_path = os.path.join('data', 'contaverde', file_name)
    users.to_csv(csv_path, index=False, sep=',')

def gen_contaverde_products(num_events, prod=product):

    products_jpg = [
    "Laptop.jpg",
    "Smartphone.jpg",
    "Headphones.jpg",
    "Tablet.jpg",
    "Smartwatch.jpg",
    "Camera.jpg",
    "Printer.jpg",
    "External Hard Drive.jpg",
    "Wireless Mouse.jpg",
    "Keyboard.jpg",
    "Monitor.jpg",
    "Gaming Console.jpg",
    "Fitness Tracker.jpg",
    "Bluetooth Speaker.jpg",
    "Power Bank.jpg",
    "Drone.jpg",
    "Virtual Reality Headset.jpg",
    "Digital Camera.jpg",
    "Soundbar.jpg",
    "Router.jpg",
    "External SSD.jpg",
    "Action Camera.jpg",
    "Gaming Mouse.jpg",
    "Gaming Keyboard.jpg",
    "Graphics Card.jpg",
    "Fitness Watch.jpg",
    "Bluetooth Earbuds.jpg",
    "Wireless Headphones.jpg",
    "Smart Home Speaker.jpg",
    "Portable Projector.jpg",
    "Computer Case.jpg",
    "Gaming Chair.jpg",
    "Mechanical Keyboard.jpg",
    "Gaming Monitor.jpg",
    "Gaming Laptop.jpg",
    "SSD Drive.jpg",
    "Wireless Router.jpg",
    "Fitness Band.jpg",
    "Gaming Headset.jpg",
    "Portable SSD.jpg"
]
    product_description = [ "minha_descricao" for i in range(len(products_jpg))]
    # [
    # "Unleash your productivity with cutting-edge performance and sleek design.",  # Laptop
    # "Stay connected and stylish with the latest technology at your fingertips.",  # Smartphone
    # "Immerse yourself in crystal-clear sound and unparalleled comfort.",  # Headphones
    # "Experience the power of portability with stunning visuals and versatility.",  # Tablet
    # "Elevate your fitness and productivity with intelligent tracking and seamless connectivity.",  # Smartwatch
    # "Capture life's moments in stunning detail with professional-grade imaging.",  # Camera
    # "Print, scan, and copy with ease for vibrant documents and photos.",  # Printer
    # "Expand your storage and safeguard your data with reliable performance.",  # External Hard Drive
    # "Navigate with precision and freedom for seamless workflow.",  # Wireless Mouse
    # "Enhance your typing experience with ergonomic design and customizable keys.",  # Keyboard
    # "Immerse yourself in vibrant visuals and unparalleled clarity for work and play.",  # Monitor
    # "Embark on epic gaming adventures with powerful graphics and immersive gameplay.",  # Gaming Console
    # "Achieve your fitness goals with real-time tracking and personalized insights.",  # Fitness Tracker
    # "Bring your music to life with rich, immersive sound and portable convenience.",  # Bluetooth Speaker
    # "Stay charged on-the-go with reliable power for your devices.",  # Power Bank
    # "Capture breathtaking aerial footage and explore new perspectives.",  # Drone
    # "Step into immersive worlds and experience entertainment like never before.",  # Virtual Reality Headset
    # "Capture memories in stunning detail with advanced imaging technology.",  # Digital Camera
    # "Elevate your audio experience with rich, room-filling sound and sleek design.",  # Soundbar
    # "Stay connected with fast, reliable Wi-Fi coverage for your home or office.",  # Router
    # "Experience lightning-fast storage and transfer speeds for your data.",  # External SSD
    # "Capture your adventures in stunning 4K resolution with rugged durability.",  # Action Camera
    # "Dominate the game with precision control and customizable features.",  # Gaming Mouse
    # "Level up your gaming experience with responsive keys and customizable RGB lighting.",  # Gaming Keyboard
    # "Unleash the power of lifelike visuals and smooth gaming performance.",  # Graphics Card
    # "Stay motivated and track your progress with smart fitness features.",  # Fitness Watch
    # "Enjoy wireless freedom and immersive sound for music and calls.",  # Bluetooth Earbuds
    # "Escape into your music with comfort and superior sound quality.",  # Wireless Headphones
    # "Control your home and enjoy immersive audio with voice commands.",  # Smart Home Speaker
    # "Transform any space into a theater with portable, high-quality projection.",  # Portable Projector
    # "Protect and showcase your system with style and functionality.",  # Computer Case
    # "Stay comfortable and focused during intense gaming sessions with ergonomic support.",  # Gaming Chair
    # "Experience tactile precision and durability for gaming and typing.",  # Mechanical Keyboard
    # "Immerse yourself in smooth, lag-free gaming visuals with high refresh rates.",  # Gaming Monitor
    # "Take gaming on-the-go with powerful performance and stunning displays.",  # Gaming Laptop
    # "Experience blazing-fast speeds and reliable storage for your data.",  # SSD Drive
    # "Enjoy seamless connectivity and fast Wi-Fi speeds for your network.",  # Wireless Router
    # "Stay active and connected with smart fitness tracking and sleek design.",  # Fitness Band
    # "Experience immersive gaming audio and clear communication with teammates.",  # Gaming Headset
    # "Carry your data securely and access it quickly with ultra-portable SSD technology."  # Portable SSD
# ]
    product_price = [
    1000,  # Laptop
    800,  # Smartphone
    200,  # Headphones
    500,  # Tablet
    300,  # Smartwatch
    1000,  # Camera
    300,  # Printer
    200,  # External Hard Drive
    80,  # Wireless Mouse
    100,  # Keyboard
    500,  # Monitor
    400,  # Gaming Console
    200,  # Fitness Tracker
    100,  # Bluetooth Speaker
    30,  # Power Bank
    1000,  # Drone
    800,  # Virtual Reality Headset
    500,  # Digital Camera
    200,  # Soundbar
    100,  # Router
    200,  # External SSD
    400,  # Action Camera
    80,  # Gaming Mouse
    100,  # Gaming Keyboard
    800,  # Graphics Card
    200,  # Fitness Watch
    100,  # Bluetooth Earbuds
    300,  # Wireless Headphones
    200,  # Smart Home Speaker
    800,  # Portable Projector
    80,  # Computer Case
    400,  # Gaming Chair
    100,  # Mechanical Keyboard
    500,  # Gaming Monitor
    2000,  # Gaming Laptop
    200,  # SSD Drive
    100,  # Wireless Router
    100,  # Fitness Band
    200,  # Gaming Headset
    200  # Portable SSD
]


    product_id=[]
    product_name=[]
    product_picture=[]
    description=[]
    price=[]
    for i in range(num_events):
        id = random.choice(list(prod.keys()))
        product_id.append(id)
        names = list(prod.values())
        name = names[id-1001]
        product_name.append(name)
        product_picture.append(products_jpg[id-1001])      
        description.append(product_description[id-1001]) 
        price.append(product_price[id-1001])
        
    product_pd = pd.DataFrame({'product_id': product_id, 'name': product_name, 'picture': product_picture, 'discription': description, 'price': price})
    file_name = 'products.txt'
    csv_path = os.path.join('data', 'contaverde', file_name)
    product_pd.to_csv(csv_path, index=False, sep=',')

def gen_contaverde_stock():
    stocks = pd.DataFrame({'product_id': product.keys(), 'available_quantity': product_stock})
    stock_df = stocks
    file_name = 'stock.txt'
    csv_path = os.path.join('data', 'contaverde', file_name)
    stocks.to_csv(csv_path, index=False, sep=',')
    return stock_df

def gen_purchase_order(num_events):
    df_audit = gen_logaudit(num_events)
    df_behavior = gen_logbehavior(num_events)
    user_id = pd.concat([df_audit['user_id'], df_behavior['user_id']])
    product_id = []
    quantity = []
    creation_date = []
    payment_date = []
    deliver_date = []
    start_date1 = datetime(2023, 1, 1)
    end_date1 = datetime(2024, 2, 1)
    start_date2 = datetime(2023, 2, 1)
    end_date2 = datetime(2024, 1, 1)
    start_date3 = datetime(2024, 4, 1)
    end_date3 = datetime(2024, 4, 17)
    for i in range(2*num_events):
        id = random.choice(list(product.keys()))
        product_id.append(id)
        quantity.append(random.randint(1,8))
        creation_date.append(datetime.now())
        payment_date.append(datetime.now())
        deliver_date.append(datetime.now())
    purchase_orders = pd.DataFrame({'user_id': user_id, 'product_id': product_id, 'quantity': quantity, 'creation_date': creation_date, 'payment_date': payment_date, 'deliver_date': deliver_date})
    purchase_orders_df = purchase_orders
    file_name = 'purchase_orders.txt'
    csv_path = os.path.join('data', 'contaverde', file_name)
    purchase_orders.to_csv(csv_path, index=False, sep=',')
    return purchase_orders_df

def update_stock(orders, stock=gen_contaverde_stock()):
    for index, order in orders.iterrows():
        product_id = order['product_id']
        quantity = order['quantity']
        stock_index = stock[stock['product_id'] == product_id].index[0]
        stock.loc[stock_index, 'available_quantity'] -= quantity
    file_name = 'stock.txt'
    csv_path = os.path.join('data', 'contaverde', file_name)
    stock.to_csv(csv_path, index=False, sep=',')
    return stock

while True:
    num_events = random.randint(5000,10000)
    gen_contaverde_users(num_events)
    gen_contaverde_products(num_events, prod=product)
    stock = gen_contaverde_stock()
    orders = gen_purchase_order(num_events)
    update_stock(orders=orders, stock=stock)
    gen_cadeanalytics(num_events)
    gen_randomlog(num_events)
    folder_path = os.path.join('data', 'datacat')
    delete_old_files(folder_path=folder_path, waiting_time=120)
    time.sleep(1)