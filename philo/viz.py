#!/usr/bin/env python3

import subprocess
import re
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import time

def run_program(args):
    """Run the external program and capture its output."""
    result = subprocess.run(args, capture_output=True, text=True)
    with open(f"./{time.strftime('%Y%m%d-%H%M%S')}_{args[0][2:]}.log", "w+") as log_file:
        log_file.write(result.stdout)
    return result.stdout

def parse_output(output):
    """Parse the program output into a structured format."""
    events = []
    lines = output.strip().split("\n")
    for line in lines:
        match = re.match(r'(\d+)\s+(\d+)\s+(.*)', line)
        if match:
            timestamp, philo, action = match.groups()
            events.append({
                'timestamp': int(timestamp),
                'philo': int(philo),
                'action': action
            })
    # Calculate the end times
    for i in range(len(events) - 1):
        events[i]['end_timestamp'] = events[i]['timestamp']
        if events[i]['philo'] == events[i + 1]['philo']:
            events[i]['end_timestamp'] = events[i + 1]['timestamp']
        else:
            for j in range(i + 1, len(events) - 1):
                if (events[i]['philo'] == events[j]['philo']
                    and events[i]['action'] != events[j]['action']):
                    events[i]['end_timestamp'] = events[j]['timestamp']
    events[-1]['end_timestamp'] = events[-1]['timestamp']  # Last event ends at its own timestamp

    return events

def visualize(events, num_philos):
    """Visualize the events chronologically."""
    colors = {
        'has taken a fork': 'gray',
        'is eating': 'green',
        'is sleeping': 'blue',
        'is thinking': 'yellow',
        'died': 'red'
    }

    fig, ax = plt.subplot(figsize=(5, num_philos))

    philos = list(set(event['philo'] for event in events))
    philos.sort()

    ax.set_yticks(philos)
    ax.set_yticklabels([f'Philo N {p}' for p in philos])
    ax.set_xlabel('Time (ms)')
    ax.set_title('Philosophers Dining Timeline')

    plt.show()

"""
    fig, ax = plt.subplots(figsize=(10, num_philos))

    philo_rows = {i: i for i in range(1, num_philos + 1)}

    for event in events:
        philo = event['philo']
        start_time = event['timestamp']
        end_time = event['end_timestamp']
        action = event['action']
        color = colors.get(action, 'black')
        duration = end_time - start_time
        ax.broken_barh([(start_time, duration)], (philo_rows[philo] - 0.4, 0.8), facecolors=color)

    ax.set_yticks([philo_rows[i] for i in range(1, num_philos + 1)])
    ax.set_yticklabels([f'Philo {i}' for i in range(1, num_philos + 1)])
    ax.set_xlabel('Time (ms)')
    ax.set_title('Dining Timeline')

    # Create legend
    patches = [mpatches.Patch(color=color, label=action) for action, color in colors.items()]
    ax.legend(handles=patches, loc='upper right')
plt.show()
"""


def main():
    # Arguments: number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philo_must_eat]
    args = ['./philo', '4', '200', '100', '150']  # example arguments
    output = run_program(args)
    print(output)
    events = parse_output(output)
    # print(events)
    visualize(events, 4)

if __name__ == '__main__':
    main()
