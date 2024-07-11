#!/usr/bin/env python3

import subprocess as sp
import signal
import re
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import time
import logging


logging.basicConfig(
    filename="visualizer.log",
    format="%(levelname)s :: %(message)s",
    level=logging.DEBUG,
)

current_process = None


def sigint_handler(signum, frame):
    global current_process
    if current_process is not None:
        current_process.terminate()
        current_process = None
    logging.warning("Recieved SIGINT. Terminated.")


signal.signal(signal.SIGINT, sigint_handler)


def run_program(args):
    """Run the external program and capture its output."""
    global current_process
    try:
        current_process = sp.Popen(args, stdout=sp.PIPE, stderr=sp.PIPE, text=True)
        out, err = current_process.communicate()
        filename = f"./{time.strftime('%Y%m%d-%H%M%S')}_{args[0][2:]}.log"
        with open(filename, "w+") as log_file:
            log_file.write(out)
        logging.info(f"Program output has been saved into `{filename}`")
        return out
    finally:
        current_process = None


def parse_output(output):
    """Parse the program output into a structured format."""
    events = []
    lines = output.strip().split("\n")
    for line in lines:
        match = re.match(r"(\d+)\s+(\d+)\s+(.*)", line)
        if match:
            timestamp, philo, action = match.groups()
            events.append(
                {"timestamp": int(timestamp), "philo": int(philo), "action": action}
            )

    last_timestamp = events[-1]["timestamp"]
    logging.debug(f"Last event timestamp: {last_timestamp}")
    # Calculate the end times
    logging.debug("Enter loop to calculate event end timestamps")
    for i in range(len(events) - 1):
        logging.debug(f"Current event index: {i}")
        events[i]["end_timestamp"] = events[i]["timestamp"]
        if events[i]["philo"] == events[i + 1]["philo"]:
            events[i]["end_timestamp"] = events[i + 1]["timestamp"]
        else:
            for j in range(i + 1, len(events)):
                if (
                    events[i]["philo"] == events[j]["philo"]
                    and events[i]["action"] != events[j]["action"]
                ):
                    events[i]["end_timestamp"] = events[j]["timestamp"]
                else:
                    events[i]["end_timestamp"] = last_timestamp
        logging.debug(f"Event end timestamp set to: {events[i]['end_timestamp']}")
    events[-1]["end_timestamp"] = last_timestamp  # Last event ends at its own timestamp
    logging.debug(
        f"Last event timestamps: from {events[-1]['timestamp']} to {events[-1]['end_timestamp']}"
    )

    return events


def sort_events(events, num_philos):
    """Sort parsed events by philo N"""
    sorted_e = {(i + 1): [] for i in range(num_philos)}
    for event in events:
        sorted_e[event["philo"]].append(event)
    logging.debug("Event list has been sorted by philo ID")
    return sorted_e


def visualize(events_by_philo, num_philos):
    """Visualize the events chronologically."""
    colors = {
        "has taken a fork": "gray",
        "is eating": "green",
        "is sleeping": "blue",
        "is thinking": "yellow",
        "died": "red",
    }

    ax = plt.subplot()

    philos = [
        p for p in range(num_philos)
    ]  # list(set(event['philo'] for event in events))
    # philos.sort()

    ax.set_yticks(philos)
    ax.set_yticklabels([f"Philo N {p + 1}" for p in philos])
    ax.set_xlabel("Time (ms)")
    ax.set_title("Philosophers Dining Timeline")
    logging.debug("Set plot meta info")

    logging.debug("Enter loop to make a plot")
    for p in events_by_philo:
        logging.debug(f"Current events group for philo N {p}")
        durations = []
        clrs = []
        actions = []
        for e in events_by_philo[p]:
            if e["action"] == "has taken a fork":
                continue
            logging.debug(f"[PID {p}] - Event: {e['action']}")
            start_time = e["timestamp"]
            end_time = e["end_timestamp"]
            actions.append(e["action"])
            clrs.append(colors.get(e["action"], "black"))
            duration = end_time - start_time if e["action"] != "died" else 10
            logging.debug(f"Duration ({duration}) : {start_time} - {end_time}")
            logging.debug(f"Color: {clrs[-1]}")
            durations.append((start_time, duration))
        ax.broken_barh(durations, (p - 1.5, 1), facecolors=clrs)
        # Place action lables on the plot
        logging.debug("List of text labels for current PID")
        for i in range(len(actions)):
            logging.debug(
                f"Lable: {actions[i]} (x: {durations[i][0] + 10}, y: {p - 1})"
            )
            ax.text(durations[i][0] + 10, p - 1, actions[i])

    ax.xaxis.grid(True)

    patches = [
        mpatches.Patch(color=color, label=action) for action, color in colors.items()
    ]
    ax.legend(handles=patches, loc="upper right")

    plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.1)
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

PHILOS_N = 5


def main():
    # Arguments: number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philo_must_eat]
    args = ["./philo", f"{PHILOS_N}", "210", "100", "100", "3"]  # example arguments
    output = run_program(args)
    print(f":::PROGRAM OUTPUT:::\n{output}\n\n")
    events = parse_output(output)
    print(f":::PARSED EVENTS:::\n{events}\n\n")
    events = sort_events(events, PHILOS_N)
    visualize(events, PHILOS_N)


if __name__ == "__main__":
    main()
