# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.

from beets.plugins import BeetsPlugin
from beets import config
import musicbrainzngs
import re


class PrimaryArtistPath(BeetsPlugin):
    def __init__(self):

        musicbrainzngs.set_useragent(
        'primaryartist-plugin', '0.0.1', contact='beetsplug@chris.oldnest.ca'
        )
        MBID_REGEX = r"(\d|\w){8}-(\d|\w){4}-(\d|\w){4}-(\d|\w){4}-(\d|\w){12}"
        locales = ['en']
        locales = config['import']['languages'].as_str_seq()
        locales = [x.lower() for x in locales]
        artist_names = ()
        cached_mbids = {}

        print('Using locales: {0}' .format(locales))

        def alias_picker(candidates_list, locales):
            """Takes a list of MusicBrainz artist aliases and returns the
            Artist Name alias that matches user-defined language preference.
            """
            if not candidates_list:
                return
            picked_names = []
            # Filter out irrelevant aliases
            candidates_list = [
            a for a in candidates_list
            if not 'end date year' in a
            if a.get("type") == 'Artist name'
            if 'locale' in a
            ]
            # Prioritize user's locale order above all, then primary alias
            for locale in locales:
                matches = []
                for a in candidates_list:
                    if a.get('primary'):
                        if locale == a.get('locale').lower():
                            return (a['alias'], a['sort-name'])
                        if locale in a.get('locale').lower():
                            return (a['alias'], a['sort-name'])
                        if locale.partition('_')[0] in a.get('locale').lower():
                            return (a['alias'], a['sort-name'])
                for a in candidates_list:
                    if locale == a.get('locale').lower():
                        return (a['alias'], a['sort-name'])
                    if locale in a.get("locale").lower():
                        return (a['alias'], a['sort-name'])
                    if locale.partition('_')[0] in a.get('locale').lower():
                        return (a['alias'], a['sort-name'])
            return

        def request_id(mb_id):
            """Retrieves an artist entry from MusicBrainz, calls alias_picker()
            to sort through it for best choice per user's locale, and returns a
            tuple of (artist name, sort-name). May raise MB connection error.
            """
            try:
                artist_info = musicbrainzngs.get_artist_by_id(
                mb_id, includes=['aliases']
                )
            except:
                raise
            else:
                print('Grabbing top-level names first.')
                names = (
                artist_info.get('artist').get('name'), 
                artist_info.get('artist').get('sort-name')
                )
                print(names)
                alias_list = artist_info.get('artist').get('alias-list')
                # What if no user-defined locale? Take artist name as-is?
                # Default to English? Set up a plugin pref for this question?
                picker_names = alias_picker(alias_list, locales)
                if picker_names:
                    return picker_names
                else:
                    return names
            return

        def resolve_names(mb_id):
            """Sanity-checks MusicBrainz ID, retrieves tuple of artist name and
            sort-name from MB database, with local caching. Returns None on
            failure.
            """
            if not mb_id:
                print('MusicBrainz ID missing for: ')
                return
            if not re.match(MBID_REGEX, mb_id):
                print('Invalid MusicBrainz ID {0} for:' .format(mb_id))
                return()
            artist_names = cached_mbids.get(mb_id)
            if artist_names:
                print(
                'Key found in local cache! Using names: {0}' 
                .format(artist_names)
                )
                return artist_names
            try:
                artist_names = request_id(mb_id)
            except:
                print('Lookup of names by MusicBrainz ID failed!')
                return
            if artist_names:
                cached_mbids[mb_id] = artist_names
                return artist_names
            return

        def _tmpl_primary_artist(item):
            name = resolve_names(item.mb_artistid)[0]
            if name:
                return name
            else:
                return item.artist

        def _tmpl_primary_artist_sort(item):
            name = resolve_names(item.mb_artistid)[1]
            if name:
                return name
            else:
                return item.artist_sort

        def _tmpl_primary_albumartist(album):
            name = resolve_names(album.mb_albumartistid)[0]
            if name:
                return name
            else:
                return album.albumartist

        def _tmpl_primary_albumartist_sort(album):
            name = resolve_names(album.mb_albumartistid)[1]
            if name:
                return name
            else:
                return album.albumartist_sort

        super(PrimaryArtistPath, self).__init__()
        self.template_fields['primary_artist'] = _tmpl_primary_artist
        
        self.template_fields['primary_artist_sort'] = _tmpl_primary_artist_sort
        
        self.album_template_fields['primary_albumartist'] = _tmpl_primary_albumartist
        
        self.album_template_fields['primary_albumartist_sort'] = _tmpl_primary_albumartist_sort
