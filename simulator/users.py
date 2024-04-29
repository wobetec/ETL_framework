import random
import datetime


class UserGenerator:

    first_name = [
        'John', 'Jane', 'Jack', 'Jill', 'James', 'Jenny', 'Jim', 'Judy', 'Joe', 'Julie',
        'Robert', 'Rebecca', 'Richard', 'Rose', 'Randy', 'Rita', 'Ron', 'Rachel', 'Ryan', 'Renee',
        'Michael', 'Mary', 'Matthew', 'Megan', 'Mark', 'Michelle', 'Marty', 'Mindy', 'Miles', 'Mabel',
        'William', 'Wendy', 'Walter', 'Wanda', 'Wesley', 'Wilma', 'Wayne', 'Winona', 'Winston', 'Winnie',
        'David', 'Diane', 'Daniel', 'Dorothy', 'Dennis', 'Debbie', 'Dale', 'Dawn', 'Dylan', 'Diana',
    ]

    last_name = [
        'Smith', 'Johnson', 'Williams', 'Jones', 'Brown', 'Davis', 'Miller', 'Wilson', 'Moore', 'Taylor',
        'Anderson', 'Thomas', 'Jackson', 'White', 'Harris', 'Martin', 'Thompson', 'Garcia', 'Martinez', 'Robinson',
        'Clark', 'Rodriguez', 'Lewis', 'Lee', 'Walker', 'Hall', 'Allen', 'Young', 'Hernandez', 'King',
        'Wright', 'Lopez', 'Hill', 'Scott', 'Green', 'Adams', 'Baker', 'Gonzalez', 'Nelson', 'Carter',
        'Mitchell', 'Perez', 'Roberts', 'Turner', 'Phillips', 'Campbell', 'Parker', 'Evans', 'Edwards', 'Collins',
    ]

    street = [
        'Main', 'First', 'Second', 'Third', 'Fourth', 'Fifth', 'Sixth', 'Seventh', 'Eighth', 'Ninth',
        'Park', 'Oak', 'Pine', 'Maple', 'Cedar', 'Elm', 'Hill', 'Lake', 'River', 'Valley',
        'Sunset', 'Sunrise', 'Meadow', 'Forest', 'Grove', 'Orchard', 'Meadow', 'Brook', 'Creek', 'Spring',
        'Highland', 'Lowland', 'East', 'West', 'North', 'South', 'Old', 'New', 'Lake', 'Mountain',
        'Hill', 'Valley', 'River', 'Creek', 'Brook', 'Spring', 'Garden', 'Meadow', 'Forest', 'Orchard',
    ]

    city = [
        'New York', 'Los Angeles', 'Chicago', 'Houston', 'Phoenix', 'Philadelphia', 'San Antonio', 'San Diego', 'Dallas', 'San Jose',
        'Austin', 'Jacksonville', 'San Francisco', 'Indianapolis', 'Columbus', 'Fort Worth', 'Charlotte', 'Seattle', 'Denver', 'El Paso',
        'Detroit', 'Washington', 'Boston', 'Memphis', 'Nashville', 'Portland', 'Oklahoma City', 'Las Vegas', 'Baltimore', 'Louisville', 'Milwaukee',
        'Albuquerque', 'Tucson', 'Fresno', 'Sacramento', 'Mesa', 'Kansas City', 'Atlanta', 'Long Beach', 'Omaha', 'Raleigh',
        'Miami', 'Oakland', 'Minneapolis', 'Tulsa', 'Cleveland', 'Wichita', 'Arlington', 'New Orleans', 'Bakersfield', 'Tampa',
    ]

    state = [
        'Alabama', 'Alaska', 'Arizona', 'Arkansas', 'California', 'Colorado', 'Connecticut', 'Delaware', 'Florida', 'Georgia',
        'Hawaii', 'Idaho', 'Illinois', 'Indiana', 'Iowa', 'Kansas', 'Kentucky', 'Louisiana', 'Maine', 'Maryland',
        'Massachusetts', 'Michigan', 'Minnesota', 'Mississippi', 'Missouri', 'Montana', 'Nebraska', 'Nevada', 'New Hampshire', 'New Jersey',
        'New Mexico', 'New York', 'North Carolina', 'North Dakota', 'Ohio', 'Oklahoma', 'Oregon', 'Pennsylvania', 'Rhode Island', 'South Carolina',
        'South Dakota', 'Tennessee', 'Texas', 'Utah', 'Vermont', 'Virginia', 'Washington', 'West Virginia', 'Wisconsin', 'Wyoming',
    ]

    country = [
        'United States', 'Canada', 'Mexico', 'Brazil', 'Argentina', 'Chile', 'Peru', 'Colombia', 'Venezuela', 'Ecuador',
        'Uruguay', 'Paraguay', 'Bolivia', 'Guyana', 'Suriname', 'French Guiana', 'United Kingdom', 'Ireland', 'France', 'Belgium',
        'Netherlands', 'Luxembourg', 'Germany', 'Switzerland', 'Austria', 'Italy', 'Spain', 'Portugal', 'Andorra', 'Monaco',
        'Liechtenstein', 'Poland', 'Czech Republic', 'Slovakia', 'Hungary', 'Slovenia', 'Croatia', 'Bosnia and Herzegovina', 'Serbia', 'Montenegro',
        'Kosovo', 'Albania', 'Macedonia', 'Greece', 'Bulgaria', 'Romania', 'Moldova', 'Ukraine', 'Belarus', 'Lithuania', 'Latvia',
    ]

    def __init__(self):
        pass

    def generate_user_id(self, user_id_num: int):
        return f'user_{user_id_num:06d}'

    def generate_user_firstname(self):
        return random.choice(self.first_name)
    
    def generate_user_lastname(self):
        return random.choice(self.last_name)
    
    def generate_user_address(self):
        return f'{random.randrange(1, 10000)} {random.choice(self.street)} - {random.choice(self.city)} - {random.choice(self.state)} - {random.choice(self.country)} - {random.randrange(10000, 99999)}/{random.randrange(10, 99)}'
    
    def generate_user_signup_date(self):
        return datetime.datetime.now() - datetime.timedelta(days=random.randrange(1, 365 * 8))
    
    def generate_user_birthdate(self):
        return datetime.datetime.now() - datetime.timedelta(days=random.randrange(365 * 18, 365 * 100))
    
    def generate_user(self, user_id_num: int):
        return {
            'user_id': self.generate_user_id(user_id_num),
            'user_firstname': self.generate_user_firstname(),
            'user_lastname': self.generate_user_lastname(),
            'user_address': self.generate_user_address(),
            'user_signup_date': self.generate_user_signup_date(),
            'user_birthdate': self.generate_user_birthdate()
        }


class Users:

    def __init__(self):
        pass