#!/usr/bin/env python3

import sys

import matplotlib.patches as mpatches
import matplotlib.pyplot as plt


def parse_events(lines: list) -> list:
    events = []
    for line in lines:
        line = line.strip()
        parts = line.split(
            maxsplit=2
        )  # Split into at most three parts: timestamp, ID, and action
        timestamp = int(parts[0])
        id = int(parts[1])
        action = parts[2].replace("\\n", "")
        events.append((timestamp, id, action))
    return events


def sort_by_philo_id(events: list) -> dict:
    philosophers = {}
    for timestamp, id, action in events:
        if id not in philosophers:
            philosophers[id] = []
        philosophers[id].append((timestamp, action))
    return dict(sorted(philosophers.items()))


def get_last_timestamp(lines: list) -> int:
    return int(lines[-1].split(maxsplit=2)[0])


action_colors = {
    "has taken a fork": "gray",
    "is eating": "#e34f44",
    "is sleeping": "#4278f5",
    "is thinking": "#78b33e",
    "died": "#7d23eb"
}


def render(s_events: dict, last_timestamp: int, lgnd: bool = True) -> None:
    n_philos = len(s_events)
    fig, axes = plt.subplots(n_philos, 1, sharex=True)
    if n_philos == 1:
        axes = [axes]  # TODO: double check this moment

    for index, pid in enumerate(s_events):
        events = s_events[pid]
        for i in range(len(events) - 1):
            if events[i][1] == "has taken a fork":
                continue
            start_time = events[i][0]
            end_time = events[i + 1][0]
            action = events[i][1]
            duration = end_time - start_time
            axes[index].broken_barh(
                [(start_time, duration)], (0, 1), facecolors=action_colors[action]
            )
        last_time = events[-1][0]
        last_action = events[-1][1]
        if last_action != "has taken a fork" and last_action != "died":
            last_duration = last_timestamp - last_time
            axes[index].broken_barh(
                [(last_time, last_duration)],
                (0, 1),
                facecolors=action_colors[last_action],
            )
        elif last_action == "died":
            last_duration = 10
            axes[index].broken_barh(
                [(last_time, last_duration)],
                (0, 1),
                facecolors=action_colors[last_action],
            )
        axes[index].set_ylabel(f"Philo {pid}")
        axes[index].grid(True, which="both", axis="x", linestyle="--", linewidth=0.5)

    axes[-1].set_xlabel("Time")
    if lgnd:
        patches = [
            mpatches.Patch(color=color, label=action)
            for action, color in action_colors.items()
        ]
        fig.legend(handles=patches, loc="upper right")  # , bbox_to_anchor=(0.9, 0.9))
    fig.canvas.manager.set_window_title("Zeno")
    plt.tight_layout(h_pad=0.000)
    plt.show()


if __name__ == "__main__":
    output = sys.stdin.readlines()
    if len(output) <= 0:
        exit(1)
    events = parse_events(output)
    s_events = sort_by_philo_id(events)
    render(s_events, get_last_timestamp(output), False)
