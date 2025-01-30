#!/usr/bin/env python3

# can't copy from dbeaver out to x, this fixes that

import i3ipc
import subprocess

i3 = i3ipc.Connection()
previous_focused_id = None

def on_window_focus(i3conn, event):
    global previous_focused_id

    new_focused_id = event.container.id
    # Fetch the container that was focused before
    if previous_focused_id is not None:
        old_container = i3conn.get_tree().find_by_id(previous_focused_id)
        if old_container and old_container.window_class == "DBeaver":
            # We just left focus on a DBeaver window:
            subprocess.Popen(["clipboard-to-primary"])

    previous_focused_id = new_focused_id

# Subscribe to focus events
i3.on("window::focus", on_window_focus)

# Start listening
i3.main()
