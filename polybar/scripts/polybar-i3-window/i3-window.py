#!/usr/bin/env python3

import sys
from argparse import ArgumentParser
import i3ipc

parser = ArgumentParser(
    description="Prints the title of the currently focused i3 window for given monitor."
)

parser.add_argument(
    "monitor",
    type=str,
    help="The monitor name according to xrandr",
    nargs="+",
    default=None,
)

argsv = parser.parse_args()

i3 = i3ipc.Connection()
monitor = argsv.monitor[0]
# _window_class = "" # possible future use (icon??)

output = i3.get_tree().find_named("^{}$".format(monitor))

if not output:  # monitor not found
    print("Cannot find specified monitor.")
    sys.exit()
else:
    output = output[0]  # id


def print_window_title(title):
    last = title.rfind(" - ")
    if last < 0:  # check alternate hyphen
        last = title.rfind(" – ")
    if last > 0:  # we have a winner
        title = title[:last]
    print(title, flush=True)


def print_empty():
    print("", flush=True)


def print_focused_window_title():
    print_window_title(get_focused_window_title())


def get_focused_window_title():
    # global _window_class
    tree = i3.get_tree()
    window = None
    title = ""  # default empty
    content_node = output.find_named("^content$")[0]  # visible content window in output
    focused_id = content_node.focus[0]  # ID of focused parent
    root_window = tree.find_by_id(focused_id)
    if root_window.focus:  # do we have any children windows?
        root_window_id = root_window.focus[0]
        window = get_active_window(root_window_id)
        title = window.name
        # _window_class = window.ipc_data['window_properties']['class']
    return title


def get_active_window(node_id):
    node = i3.get_tree().find_by_id(node_id)
    if node.name == None:
        return get_active_window(node.focus[0])
    return node


def on_window(i3, e):
    # global _window_class
    if e.container.ipc_data["output"] == monitor:
        if e.change == "focus" or e.change == "move" or e.change == "title":
            # _window_class = e.container.ipc_data['window_properties']['class']
            print_window_title(e.container.name)


def on_workspace(i3, e):
    if e.current.ipc_data["output"] == monitor:
        if e.old != None:
            if e.change == "init" or e.current.id != e.old.id:
                print_empty()
    elif e.old.ipc_data["output"] == monitor:
        print_focused_window_title()


i3.on("window", on_window)
i3.on("workspace", on_workspace)

try:
    print_focused_window_title()
    i3.main()
except:
    print("Unexpected error:", sys.exc_info()[0])
    raise
