import random
import pandas as pd
from names_generator import generate_name
from random import randrange
from datetime import timedelta
from datetime import datetime
from data_generator import id_names, list_ids

#id_names = {f'{i}': generate_name(style='capital')  for i in range(1000, 6000)}
#list_ids = list(id_names.keys())

def genRandDate(start, end):
    delta = end - start
    int_delta = (delta.days * 24 * 60 * 60) + delta.seconds
    random_second = randrange(int_delta)
    return start + timedelta(seconds=random_second)

def genStimulus():
    stimuli = ['Click', 'Hover', 'Type', 'Scroll', 'Swipe']
    return random.choice(stimuli)

def genTargetComp():
    components = ['Button', 'Menu', 'Form', 'Image', 'Link']
    return random.choice(components)

def gen_cadeanalytics(num_events):
    start_date = datetime(2020, 1, 1)
    end_date = datetime(2024, 4, 16)
    
    simulated_data = []
    for _ in range(num_events):
        notification_date = genRandDate(start_date, end_date)
        user_id = random.choice(list_ids)
        stimulus = genStimulus()
        target_component = genTargetComp()
        
        event_data = {'notification_date': notification_date.strftime('%Y-%m-%d %H:%M:%S'), 'user_id': user_id, 'stimulus': stimulus, 'target_component': target_component}
        
        simulated_data.append(event_data.values())
        df = pd.DataFrame(data = simulated_data, columns = event_data.keys())
        date = datetime.now()
        file_name = f"{date.strftime('%Y-%m-%d_%H-%M-%S')}.txt"
        df.to_csv('file_name.txt')
