import random
import time
import numpy as np
import pandas as pd
import datetime
from random import randrange
from names_generator import generate_name
from random import randrange
from datetime import timedelta
from datetime import datetime


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
    actions = ['Login', 'Logout', 'Update', 'Delete', 'Add', 'Search', 'Purchase', 'Visualization']
    return random.choice(actions)

def genLineCode():
    return random.randint(1000, 9999)

def genStimulus():
    stimuli = ['Click', 'Hover', 'Type', 'Scroll', 'Swipe']
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
    elif action == 'Visualization':
        phrases = "User {username} visualized {Product}."
        return phrases.format(username=name, Product=prod)
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
    else:
        phrases = "No behavior captured from {username} after 15 seconds."
        return phrases.format(username = name)


def gen_logaudit(num_events, interval_minutes=30):
    start_date = datetime.now()
    end_date = start_date+timedelta(seconds=interval_minutes)
    interval_start = start_date
    interval_end = start_date + timedelta(seconds=interval_minutes)
    #print(interval_end)
    
    simulated_data = []
    for k in range(num_events):
        event_type = 'audit'
        notification_date = genRandDate(start_date, end_date)
        user_id = random.choice(list_ids) #audit, behavior
        action = genAction() #audit
        product = random.choice(products)
        message = genAuditMessage(action, id_names[user_id], product)
        
        event_data = {'notification_date': notification_date.strftime('%Y-%m-%d %H:%M:%S'), 'event_type': event_type, 'message': message,  'user_id': user_id, 'action': action}
        #event_data = [notification_date.strftime('%Y-%m-%d %H:%M:%S'), event_type, message, user_id, action]
        
        #simulated_data.append(event_data.values())
        simulated_data.append(event_data)
        df = pd.DataFrame(data = simulated_data, columns = event_data.keys())
        df['notification_date'] = sorted(df['notification_date'])
        #print(1)
        time = datetime.now()
        if time > interval_end:
            # Salva o arquivo de log atual antes de iniciar um novo
            file_name = f"log_{event_type}_{start_date.strftime('%Y-%m-%d_%H-%M-%S')}.txt"
            #print(1)
            df.to_csv(file_name, index=False, sep=',')
            return df
        elif k==num_events-1: 
            file_name = f"log_{event_type}_{start_date.strftime('%Y-%m-%d_%H-%M-%S')}.txt"
            #print(1)
            df.to_csv(file_name, index=False, sep=',')
            return df
    #return simulated_data

def gen_logbehavior(num_events, interval_minutes=30):
    start_date = datetime.now()
    end_date = start_date+timedelta(seconds=interval_minutes)
    interval_start = start_date
    interval_end = start_date + timedelta(seconds=interval_minutes)
    #print(interval_end)
    
    simulated_data = []
    for k in range(num_events):
        event_type = 'behavior'
        notification_date = genRandDate(start_date, end_date)
        user_id = random.choice(list_ids) #audit, behavior
        stimulus = genStimulus() #behavior
        target_component = genTargetComp() #behavior, failings
        message = genBehaviorMessage(stimulus, id_names[user_id])
        
        event_data = {'notification_date': notification_date.strftime('%Y-%m-%d %H:%M:%S'), 'event_type': event_type, 'message': message, 'user_id': user_id, 'stimulus': stimulus, 'target_component': target_component}
        #event_data = [notification_date.strftime('%Y-%m-%d %H:%M:%S'), event_type, message, user_id, stimulus, target_component]
        
        #simulated_data.append(event_data.values())
        simulated_data.append(event_data)
        df = pd.DataFrame(data = simulated_data, columns = event_data.keys())
        df['notification_date'] = sorted(df['notification_date'])
        #print(1)
        time = datetime.now()
        if time > interval_end:
            # Salva o arquivo de log atual antes de iniciar um novo
            file_name = f"log_{event_type}_{start_date.strftime('%Y-%m-%d_%H-%M-%S')}.txt"
            print(1)
            df.to_csv(file_name, index=False, sep=',')
            return
        elif k==num_events-1: 
            file_name = f"log_{event_type}_{start_date.strftime('%Y-%m-%d_%H-%M-%S')}.txt"
            #print(1)
            df.to_csv(file_name, index=False, sep=',')
    return df
    #return simulated_data

def gen_logfailings(num_events, interval_minutes=30):
    start_date = datetime.now()
    end_date = start_date+timedelta(seconds=interval_minutes)
    interval_start = start_date
    interval_end = start_date + timedelta(seconds=interval_minutes)
    #print(interval_end)
    
    simulated_data = []
    for k in range(num_events):
        event_type = 'failure'
        notification_date = genRandDate(start_date, end_date)
        target_component = genTargetComp() #behavior, failings
        linecode = genLineCode() #failings
        severity = genSeverity() #failings
        err = genErrorMsg()
        message = genFailureMsessage(err)
        
        event_data = {'notification_date': notification_date.strftime('%Y-%m-%d %H:%M:%S'), 'event_type': event_type, 'message': message, 'target_component': target_component, 'linecode': linecode, 'severity': severity}
        #event_data = [notification_date.strftime('%Y-%m-%d %H:%M:%S'), event_type, message, target_component, linecode, severity]
        
        simulated_data.append(event_data.values())
        #simulated_data.append(event_data)
        df = pd.DataFrame(data = simulated_data, columns = event_data.keys())
        df['notification_date'] = sorted(df['notification_date'])
        #print(1)
        time = datetime.now()
        if time > interval_end:
            # Salva o arquivo de log atual antes de iniciar um novo
            file_name = f"log_{event_type}_{start_date.strftime('%Y-%m-%d_%H-%M-%S')}.txt"
            print(1)
            df.to_csv(file_name, index=False, sep=',')
            return
        elif k==num_events-1: 
            file_name = f"log_{event_type}_{start_date.strftime('%Y-%m-%d_%H-%M-%S')}.txt"
            #print(1)
            df.to_csv(file_name, index=False, sep=',')
    return df
    #return simulated_data

def gen_randomlog(num_events):
    #logs = [1, 2, 3]
    #simulated_logs = []
    #for k in range(num_events):
    #choice = random.choice(logs)
    p = np.random.uniform(0,1/3)
    q = np.random.uniform(0,1-p)
    r = 1-p-q
    gen_logfailings(int(num_events*p))
            #simulated_logs.append(log)
    gen_logbehavior(int(num_events*q))
    #    simulated_logs.append(log)
    gen_logaudit(int(num_events*r))
    #        simulated_logs.append(log)
    #pd.DataFrame(simulated_logs)
    
