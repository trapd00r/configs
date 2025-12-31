"""
autoalbumtype.py - Automatically set albumtype for asis imports based on track count.

This ensures asis imports get routed to the correct directory (+singles/, +eps/)
based on track count, since they would otherwise have no albumtype set.

Configuration (add to config.yaml):

    plugins: [autoalbumtype, ...]

    autoalbumtype:
      single_max: 2   # Albums with <= 2 tracks -> albumtype=single
      ep_max: 6       # Albums with 3-6 tracks  -> albumtype=ep
                      # Albums with 7+ tracks   -> albumtype unchanged (falls to default)
"""

from beets.plugins import BeetsPlugin
from beets.importer.tasks import Action


class AutoAlbumTypePlugin(BeetsPlugin):
    def __init__(self):
        super().__init__()
        self.config.add({
            'single_max': 2,
            'ep_max': 6,
        })
        self.register_listener('import_task_choice', self.on_import_task_choice)

    def on_import_task_choice(self, task, session):
        self._log.debug(f'import_task_choice fired, choice_flag={task.choice_flag}')

        # Only process asis imports
        if task.choice_flag != Action.ASIS:
            self._log.debug(f'Skipping: not ASIS (is {task.choice_flag})')
            return

        # Skip singleton imports
        if getattr(task, 'is_album', True) is False:
            self._log.debug('Skipping: singleton import')
            return

        # Don't override if albumtype already set (from existing tags)
        for item in task.items:
            if item.albumtype:
                self._log.debug(f'Skipping: albumtype already set to {item.albumtype}')
                return

        num_tracks = len(task.items)
        single_max = self.config['single_max'].get(int)
        ep_max = self.config['ep_max'].get(int)

        if num_tracks <= single_max:
            albumtype = 'single'
        elif num_tracks <= ep_max:
            albumtype = 'ep'
        else:
            # Full albums - don't set, let default path apply
            self._log.debug(f'Skipping: {num_tracks} tracks > ep_max ({ep_max})')
            return

        self._log.info(f'Auto-setting albumtype={albumtype} ({num_tracks} tracks)')

        for item in task.items:
            item.albumtype = albumtype

