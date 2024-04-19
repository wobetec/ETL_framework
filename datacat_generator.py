import random
import pandas as pd
from names_generator import generate_name
from random import randrange
from datetime import timedelta
from datetime import datetime

def genUserId():
    return random.randint(100000, 999999)

def genEventType():
    eventType = ['audit', 'behavior', 'failings']
    return random.choice(eventType)

def genAction():
    actions = ['Login', 'Logout', 'Update', 'Delete', 'Add', 'Search']
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

def genAuditMessage(action): 
    phrases = None

    if action == 'Login': 
        phrases = "User {username} logged in."
        name = generate_name(style='capital')
        return phrases.format(username = name)
    elif action == 'Logout':
        phrases = "User {username} logged out."
        name = generate_name(style='capital')
        return phrases.format(username = name)
        
    elif action == 'Update':
        phrases = "User {username} updated settings."
        name = generate_name(style='capital')
        return phrases.format(username = name)
    elif action == 'Delete':
        phrases = "User {username} deleted account."
        name = generate_name(style='capital')
        return phrases.format(username = name)
    elif action == 'Add':
        phrases = "User {username} added a new address."
        name = generate_name(style='capital')
        return phrases.format(username = name)
    elif action == 'Search':
        phrases = "User {username} searched for a product."
        name = generate_name(style='capital')
        return phrases.format(username = name)
    else:
        phrases = "User {username} did not make any action after 15 seconds."
        name = generate_name(style='capital')
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
        
def genBehaviorMessage(stimulus):
    if stimulus == 'Click':
        phrases = "{username} clicked on {target} component."
        return phrases.format(username = generate_name(style='capital'), target = genTargetComp())
    elif stimulus == 'Type':
        phrases = "{username} searched for {target}."
        return phrases.format(username = generate_name(style='capital'), target = genTargetComp())
    elif stimulus == 'Hover':
        phrases = "{username} hovered over {target}."
        return phrases.format(username = generate_name(style='capital'), target = genTargetComp())
    elif stimulus == 'Scroll':
        phrases = "{username} scrolled over {target}."
        return phrases.format(username = generate_name(style='capital'), target = genTargetComp())
    elif stimulus == 'Swipe':
        phrases = "{username} swiped {target}."
        return phrases.format(username = generate_name(style='capital'), target = genTargetComp())
    else:
        phrases = "No behavior captured from {username} after 15 seconds."
        return phrases.format(username = generate_name(style='capital'))


def gen_logaudit(num_events):
    start_date = datetime(2015, 1, 1)
    end_date = datetime(2020, 1, 1)
    
    simulated_data = []
    for _ in range(num_events):
        event_type = 'audit'
        notification_date = genRandDate(start_date, end_date)
        user_id = genUserId() #audit, behavior
        action = genAction() #audit
        message = genAuditMessage(action)
        
        event_data = {'notification_date': notification_date.strftime('%Y-%m-%d %H:%M:%S'), 'event_type': event_type, 'message': message,  'user_id': user_id, 'action': action}
        
        simulated_data.append(event_data.values())
        df = pd.DataFrame(data = simulated_data, columns = event_data.keys())
    return df

def gen_logbehavior(num_events):
    start_date = datetime(2015, 1, 1)
    end_date = datetime(2020, 1, 1)
    
    simulated_data = []
    for _ in range(num_events):
        event_type = 'behavior'
        notification_date = genRandDate(start_date, end_date)
        user_id = genUserId() #audit, behavior
        stimulus = genStimulus() #behavior
        target_component = genTargetComp() #behavior, failings
        message = genBehaviorMessage(stimulus)
        
        event_data = {'notification_date': notification_date.strftime('%Y-%m-%d %H:%M:%S'), 'event_type': event_type, 'message': message, 'user_id': user_id, 'stimulus': stimulus, 'target_component': target_component}
        simulated_data.append(event_data.values())
        df = pd.DataFrame(data = simulated_data, columns = event_data.keys())
    return df

def gen_logfailings(num_events):
    start_date = datetime(2015, 1, 1)
    end_date = datetime(2020, 1, 1)
    
    simulated_data = []
    for _ in range(num_events):
        event_type = 'failure'
        notification_date = genRandDate(start_date, end_date)
        target_component = genTargetComp() #behavior, failings
        linecode = genLineCode() #failings
        severity = genSeverity() #failings
        err = genErrorMsg()
        message = genFailureMsessage(err)
        
        event_data = {'notification_date': notification_date.strftime('%Y-%m-%d %H:%M:%S'), 'event_type': event_type, 'message': message, 'target_component': target_component, 'linecode': linecode, 'severity': severity}
        
        simulated_data.append(event_data.values())
        df = pd.DataFrame(data = simulated_data, columns = event_data.keys())
    return df

def gen_randomlog(num_events):
    logs = [gen_logaudit(num_events), gen_logbehavior(num_events), gen_logfailings(num_events)]
    return random.choice(logs)
