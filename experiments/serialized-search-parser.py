#! /usr/bin/env python

from lab.parser import Parser


def try_delete(map, key):
    try:
        del map[key]
    except KeyError:
        pass


def post_process(content, props):
    """ Removes values if the instance was not solved. """
    if "plan_length" not in props:
        try_delete(props, "width_average")
        try_delete(props, "width_maximum")


def main():
    parser = Parser()
    parser.add_pattern("width_average", r"Average effective width (.+)\n", type=float)
    parser.add_pattern("width_maximum", r"Maximum effective width (\d+)\n", type=int)
    parser.add_function(post_process)
    parser.parse()


if __name__ == "__main__":
    main()
