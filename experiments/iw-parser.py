#! /usr/bin/env python

import re

from lab.parser import Parser


def try_delete(map, key):
    try:
        del map[key]
    except KeyError:
        pass


def post_process(content, props):
    """ Removes values if the instance was not solved. """
    if not int("plan_length" in props):
        try_delete(props, "expanded")
        try_delete(props, "generated")
        try_delete(props, "pruned")
        try_delete(props, "effective_width")
        try_delete(props, "successor_time")
        try_delete(props, "apply_time")
        try_delete(props, "grounding_time")
        try_delete(props, "goal_time")
        try_delete(props, "search_time")
        try_delete(props, "total_time")
        try_delete(props, "plan_length")

def convert_time_to_seconds(content, props):
    if "successor_time" in props:
        props["successor_time"] = props["successor_time"] / 1000
    if "apply_time" in props:
        props["apply_time"] = props["apply_time"] / 1000
    if "apply_time" in props:
        props["apply_time"] = props["apply_time"] / 1000
    if "grounding_time" in props:
        props["grounding_time"] = props["grounding_time"] / 1000
    if "goal_time" in props:
        props["goal_time"] = props["goal_time"] / 1000
    if "search_time" in props:
        props["search_time"] = props["search_time"] / 1000
    if "total_time" in props:
        props["total_time"] = props["total_time"] / 1000


def coverage(content, props):
    props["coverage"] = int("plan_length" in props)


def search_exhausted_without_solution(content, props):
    matches = re.findall(r"No solution found!", content)
    props["search_exhausted_without_solution"] = len(matches)


def main():
    parser = Parser()
    parser.add_pattern("expanded", r"^Expanded (\d+) states\n", type=int, flags="M")
    parser.add_pattern("generated", r"^Generated (\d+) states\n", type=int, flags="M")
    parser.add_pattern("pruned", r"^Pruned (\d+) states\n", type=int, flags="M")
    parser.add_pattern("effective_width", r"^Maximum effective width (\d+)\n", type=int, flags="M")
    parser.add_pattern("successor_time", r"^Successor time: (.+) ms .*\n", type=float, flags="M")
    parser.add_pattern("apply_time", r"^Apply time: (.+) ms .*\n", type=float, flags="M")
    parser.add_pattern("grounding_time", r"^Grounding time: (.+) ms .*\n", type=float, flags="M")
    parser.add_pattern("goal_time", r"^Goal time: (.+) ms .*\n", type=float, flags="M")
    parser.add_pattern("search_time", r"^Search time: (.+) ms\n", type=float, flags="M")
    parser.add_pattern("total_time", r"^Total time: (.+) ms\n", type=float, flags="M")
    parser.add_pattern("plan_length", r"^Plan length: (\d+)\n", type=int, flags="M")
    parser.add_function(search_exhausted_without_solution)
    parser.add_function(convert_time_to_seconds)
    parser.add_function(coverage)
    parser.add_function(post_process)
    parser.parse()


if __name__ == "__main__":
    main()
