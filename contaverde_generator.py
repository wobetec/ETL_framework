import random
import pandas as pd
from names_generator import generate_name
from random import randrange
from datetime import timedelta
from random_address import real_random_address
from datetime import datetime
from datacat_generator import gen_logaudit, gen_logbehavior, id_names

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
    50,  # Laptop
    100,  # Smartphone
    200,  # Headphones
    150,  # Tablet
    120,  # Smartwatch
    80,  # Camera
    100,  # Printer
    150,  # External Hard Drive
    200,  # Wireless Mouse
    180,  # Keyboard
    90,  # Monitor
    60,  # Gaming Console
    150,  # Fitness Tracker
    200,  # Bluetooth Speaker
    300,  # Power Bank
    70,  # Drone
    80,  # Virtual Reality Headset
    100,  # Digital Camera
    150,  # Soundbar
    200,  # Router
    150,  # External SSD
    70,  # Action Camera
    200,  # Gaming Mouse
    180,  # Gaming Keyboard
    80,  # Graphics Card
    150,  # Fitness Watch
    200,  # Bluetooth Earbuds
    120,  # Wireless Headphones
    150,  # Smart Home Speaker
    50,  # Portable Projector
    200,  # Computer Case
    60,  # Gaming Chair
    180,  # Mechanical Keyboard
    90,  # Gaming Monitor
    40,  # Gaming Laptop
    150,  # SSD Drive
    180,  # Wireless Router
    200,  # Fitness Band
    150,  # Gaming Headset
    100  # Portable SSD
]

product_dict = dict(zip(list(product.values()), product_stock))

def genRandDate(start, end):
    delta = end - start
    int_delta = (delta.days * 24 * 60 * 60) + delta.seconds
    random_second = randrange(int_delta)
    return start + timedelta(seconds=random_second)

def gen_contaverde_users(num_events):
    df_audit = gen_logaudit(num_events)
    df_behavior = gen_logbehavior(num_events)
    user_id = pd.concat[df_audit['user_id'], df_behavior['user_id']]
    names = []
    last_names = []
    address = []
    start_date1 = datetime(2015, 1, 1)
    end_date1 = datetime(2024, 4, 16)
    start_date2 = datetime(1960, 1, 1)
    end_date2 = datetime(2000, 1, 1)
    register_day = []
    birth_day = []
    for i in range(num_events):
        full_name = random.choice(list(id_names.values()))
        name, last_name = full_name.split()
        names.append(name)
        last_names.append(last_name)
        addresses = real_random_address()
        address.append(random.choice(addresses.values()))
        register_day.append(genRandDate(start_date1, end_date1))
        birth_day.append(genRandDate(start_date2, end_date2))
        
    users = pd.DataFrame({'user_id': user_id, 'name': names, 'last_name': last_names, 'address': address, 'registar_day': register_day, 'birth_day': birth_day})
    users.to_csv('users.txt')

def gen_contaverde_products(num_events):

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
    product_description = [
    "Unleash your productivity with cutting-edge performance and sleek design.",  # Laptop
    "Stay connected and stylish with the latest technology at your fingertips.",  # Smartphone
    "Immerse yourself in crystal-clear sound and unparalleled comfort.",  # Headphones
    "Experience the power of portability with stunning visuals and versatility.",  # Tablet
    "Elevate your fitness and productivity with intelligent tracking and seamless connectivity.",  # Smartwatch
    "Capture life's moments in stunning detail with professional-grade imaging.",  # Camera
    "Print, scan, and copy with ease for vibrant documents and photos.",  # Printer
    "Expand your storage and safeguard your data with reliable performance.",  # External Hard Drive
    "Navigate with precision and freedom for seamless workflow.",  # Wireless Mouse
    "Enhance your typing experience with ergonomic design and customizable keys.",  # Keyboard
    "Immerse yourself in vibrant visuals and unparalleled clarity for work and play.",  # Monitor
    "Embark on epic gaming adventures with powerful graphics and immersive gameplay.",  # Gaming Console
    "Achieve your fitness goals with real-time tracking and personalized insights.",  # Fitness Tracker
    "Bring your music to life with rich, immersive sound and portable convenience.",  # Bluetooth Speaker
    "Stay charged on-the-go with reliable power for your devices.",  # Power Bank
    "Capture breathtaking aerial footage and explore new perspectives.",  # Drone
    "Step into immersive worlds and experience entertainment like never before.",  # Virtual Reality Headset
    "Capture memories in stunning detail with advanced imaging technology.",  # Digital Camera
    "Elevate your audio experience with rich, room-filling sound and sleek design.",  # Soundbar
    "Stay connected with fast, reliable Wi-Fi coverage for your home or office.",  # Router
    "Experience lightning-fast storage and transfer speeds for your data.",  # External SSD
    "Capture your adventures in stunning 4K resolution with rugged durability.",  # Action Camera
    "Dominate the game with precision control and customizable features.",  # Gaming Mouse
    "Level up your gaming experience with responsive keys and customizable RGB lighting.",  # Gaming Keyboard
    "Unleash the power of lifelike visuals and smooth gaming performance.",  # Graphics Card
    "Stay motivated and track your progress with smart fitness features.",  # Fitness Watch
    "Enjoy wireless freedom and immersive sound for music and calls.",  # Bluetooth Earbuds
    "Escape into your music with comfort and superior sound quality.",  # Wireless Headphones
    "Control your home and enjoy immersive audio with voice commands.",  # Smart Home Speaker
    "Transform any space into a theater with portable, high-quality projection.",  # Portable Projector
    "Protect and showcase your system with style and functionality.",  # Computer Case
    "Stay comfortable and focused during intense gaming sessions with ergonomic support.",  # Gaming Chair
    "Experience tactile precision and durability for gaming and typing.",  # Mechanical Keyboard
    "Immerse yourself in smooth, lag-free gaming visuals with high refresh rates.",  # Gaming Monitor
    "Take gaming on-the-go with powerful performance and stunning displays.",  # Gaming Laptop
    "Experience blazing-fast speeds and reliable storage for your data.",  # SSD Drive
    "Enjoy seamless connectivity and fast Wi-Fi speeds for your network.",  # Wireless Router
    "Stay active and connected with smart fitness tracking and sleek design.",  # Fitness Band
    "Experience immersive gaming audio and clear communication with teammates.",  # Gaming Headset
    "Carry your data securely and access it quickly with ultra-portable SSD technology."  # Portable SSD
]
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
        id = random.choice(list(product.keys()))
        product_id.append(id)
        names = product.values()
        name = names[id-1001]
        product_name.append(name)
        product_picture.append(products_jpg[id-1001])      
        description.append(product_description[id-1001]) 
        price.append(product_price[id-1001])
        
    product = pd.DataFrame({'product_id': product_id, 'name': product_name, 'picutre': product_picture, 'discription': description, 'price': price})
    product.to_csv('products.txt')

def gen_contaverde_stock():
    stocks = pd.DataFrame({'product_id': product.keys(), 'available_quantity': product_stock})
    stocks.to_csv('stock.txt')

def gen_purchase_order(num_events):
    df_audit = gen_logaudit(num_events)
    df_behavior = gen_logbehavior(num_events)
    user_id = pd.concat[df_audit['user_id'], df_behavior['user_id']]
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
    for i in range(num_events):
        id = random.choice(list(product.keys()))
        product_id.append(id)
        quantity.append(random.randint(1,8))
        creation_date.append(genRandDate(start_date1, end_date1))
        payment_date.append(genRandDate(start_date2, end_date2))
        deliver_date.append(genRandDate(start_date3, end_date3))
    purchase_orders = pd.DataFrame({'user_id': user_id, 'product_id': product_id, 'quantity': quantity, 'creation_date': creation_date, 'payment_date': payment_date, 'deliver_date': deliver_date})
    purchase_orders.to_csv('purchase_orders.txt')       