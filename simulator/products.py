import random
import lorem


class ProductGenerator:

    brands = [
        'Apple', 'Samsung', 'Xiaomi', 'Huawei', 'Sony', 'LG', 'Motorola', 'Lenovo', 'Nokia', 'Blackberry',
        'HTC', 'Google', 'OnePlus', 'Asus', 'Acer', 'HP', 'Dell', 'Toshiba', 'Fujitsu', 'Panasonic',
        'Sharp', 'Philips', 'JVC', 'Hitachi', 'Pioneer', 'Yamaha', 'Bose', 'JBL', 'Harman Kardon', 'Beats',
        'Sennheiser', 'AKG', 'Beyerdynamic', 'Audio-Technica', 'Shure', 'Razer', 'SteelSeries', 'Logitech', 'Corsair', 'Cooler Master',
        'Thermaltake', 'NZXT', 'Fractal Design', 'Phanteks', 'Lian Li', 'Silverstone', 'BitFenix', 'Antec', 'Seasonic', 'EVGA',
    ]

    categories = [
        'Smartphone', 'Tablet', 'Laptop', 'Desktop', 'Monitor', 'Headphones', 'Keyboard', 'Mouse', 'Speaker', 'Power Supply',
        'PC Case', 'Motherboard', 'CPU', 'GPU', 'RAM', 'Storage', 'Cooler', 'Thermal Paste', 'Fan', 'Cable',
        'Adapter', 'Router', 'Switch', 'Access Point', 'Firewall', 'Modem', 'NAS', 'Printer', 'Scanner', 'Projector',
        'TV', 'Camera', 'Drone', 'Smartwatch', 'Fitness Tracker', 'VR Headset', 'Game Console', 'Game', 'Software', 'Service',
        'Subscription', 'Gift Card', 'Accessory'
    ]

    product = [
        'iPhone', 'Galaxy', 'Redmi', 'P', 'Xperia', 'G', 'Moto', 'Vibe', 'Lumia', 'Key',
        'Desire', 'Pixel', 'One', 'ZenFone', 'Predator', 'Swift', 'Elite', 'ThinkPad', 'LifeBook', 'ToughBook',
        'Aquos', 'Ambilight', 'Everio', 'Plasma', 'RX', 'SoundBar', 'SoundDock', 'SoundLink', 'SoundTouch', 'SoundWear',
        'HD', 'HDJ', 'DT', 'DTX', 'ATH', 'SRH', 'Kraken', 'Arctis', 'G', 'K', 'MasterKeys', 'Gaming', 'Elite',
    ]

    def __init__(self):
        pass

    def generate_product_name(self):
        brand = random.choice(self.brands)
        category = random.choice(self.categories)
        product = random.choice(self.product)
        return f'{brand} {category} {product}'
    
    def generate_product_description(self):
        return lorem.sentence()
    
    def generate_product_price(self):
        return round(random.uniform(0, 10000), 2)

    def generate_product_id(self, product_id_num: int):
        return f'product_{product_id_num:06d}'

    def generate_product(self, product_id_num: int):
        return {
            'product_id': self.generate_product_id(product_id_num),
            'product_name': self.generate_product_name(),
            'product_description': self.generate_product_description(),
            'product_price': self.generate_product_price()
        }


class Products:

    def __init__(self):
        pass