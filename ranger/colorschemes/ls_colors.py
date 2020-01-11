from ranger.gui.colorscheme import ColorScheme
import ranger.gui.color as style
import ranger.gui.context
import ranger.gui.widgets.browsercolumn
from os import getenv
from subprocess import check_output, CalledProcessError


def get_default_lscolors():
    """Returns the default value for LS_COLORS
    as parsed from the `dircolors` command
    """
    ls_colors = check_output('dircolors')
    ls_colors = ls_colors.splitlines()[0].decode('UTF-8').split("'")[1]
    return ls_colors


try:
    ls_colors = getenv('LS_COLORS', get_default_lscolors()).split(':')
except (CalledProcessError, FileNotFoundError):
    ls_colors = []

# Gets all the keys corresponding to extensions
ls_colors_keys = [k.split('=')[0] for k in ls_colors if k != '']
ls_colors_keys = [k.split('*.')[1] for k in ls_colors_keys if '*.' in k]

# Add the key names to ranger context keys
for key in ls_colors_keys:
    ranger.gui.context.CONTEXT_KEYS.append(key)
    setattr(ranger.gui.context.Context, key, False)

OLD_HOOK_BEFORE_DRAWING = ranger.gui.widgets.browsercolumn.hook_before_drawing


def new_hook_before_drawing(fsobject, color_list):
    for key in ls_colors_keys:
        if fsobject.basename.endswith(key):
            color_list.append(key)

    return OLD_HOOK_BEFORE_DRAWING(fsobject, color_list)


ranger.gui.widgets.browsercolumn.hook_before_drawing = new_hook_before_drawing


class ls_colors(ColorScheme):
    progress_bar_color = 1

    ls_colors_keys = [k.split('=') for k in ls_colors if k != '']
    tup_ls_colors = []

    # Not considering file extensions
    # The order of these two block matters, as extensions colouring should take
    # precedence over file type
    for key in [k for k in ls_colors_keys if '.*' not in k]:
        if key[0] == 'fi':
            tup_ls_colors += [('file', key[1])]

    # Considering files extensions
    tup_ls_colors += [(k[0].split('*.')[1], k[1]) for k in ls_colors_keys
                      if '*.' in k[0]]

    for key in [k for k in ls_colors_keys if '.*' not in k]:
        if key[0] == 'ex':
            tup_ls_colors += [('executable', key[1])]
        elif key[0] == 'pi':
            tup_ls_colors += [('fifo', key[1])]
        elif key[0] == 'ln':
            tup_ls_colors += [('link', key[1])]
        elif key[0] == 'bd' or key[0] == 'cd':
            tup_ls_colors += [('device', key[1])]
        elif key[0] == 'so':
            tup_ls_colors += [('socket', key[1])]
        elif key[0] == 'di':
            tup_ls_colors += [('directory', key[1])]

    def get_attr_from_lscolors(self, attribute_list):
        return_attr = 0
        to_del = []

        for i, attr in enumerate(attribute_list):
            attr = int(attr)
            to_del.append(i)
            if attr == 1:
                return_attr |= style.bold
            elif attr == 4:
                return_attr |= style.underline
            elif attr == 5:
                return_attr |= style.blink
            elif attr == 7:
                return_attr |= style.reverse
            elif attr == 8:
                return_attr |= style.invisible
            else:
                to_del.pop(-1)

            return return_attr

    def get_256_background_color_if_exists(self, attribute_list):
        colour256 = False
        for i, key in enumerate(attribute_list):
            if key == '48' and attribute_list[i + 1] == '5':
                colour256 = True
                break
        if colour256 and len(attribute_list) >= i + 3:
            return_colour = int(attribute_list[i + 2])
            del attribute_list[i:i + 3]
            return return_colour
        else:
            return None

    def get_256_foreground_color_if_exists(self, attribute_list):
        colour256 = False
        for i, key in enumerate(attribute_list):
            if key == '38' and attribute_list[i + 1] == '5':
                colour256 = True
                break
        if colour256 and len(attribute_list) >= i + 3:
            return_colour = int(attribute_list[i + 2])
            del attribute_list[i:i + 3]
            return return_colour
        else:
            return None

    def use(self, context):
        fg, bg, attr = style.default_colors

        if context.reset:
            return style.default_colors

        elif context.in_browser:
            if context.selected:
                attr = style.reverse

        # Values found from
        # http://www.bigsoft.co.uk/blog/2008/04/11/configuring-ls_colors
        for key, t_attributes in self.tup_ls_colors:
            if getattr(context, key):
                if key == 'executable' and (context.directory or context.link):
                    continue
                t_attributes = t_attributes.split(';')
                colour256_fg = self.get_256_foreground_color_if_exists(
                    t_attributes)
                colour256_bg = self.get_256_background_color_if_exists(
                    t_attributes)
                new_attr = self.get_attr_from_lscolors(t_attributes)
                if new_attr is not None:
                    attr |= new_attr

                # Now only the non-256 colours should be left.
                # Let's fetch them
                colour16_fg, colour16_bg = None, None
                for colour_val in t_attributes:
                    colour_val = int(colour_val)
                    # This is an attribute
                    if (colour_val >= 30
                            and colour_val <= 37):  # Basic colours
                        colour16_fg = colour_val - 30
                    # eight more basic colours
                    elif (colour_val >= 90 and colour_val <= 97):
                        colour16_fg = colour_val - 82

                    elif (colour_val >= 40 and colour_val <= 47):
                        colour16_bg = colour_val
                    # eight more basic colours
                    elif (colour_val >= 90 and colour_val <= 97):
                        colour16_bg = colour_val

                if colour256_fg is not None:
                    fg = colour256_fg
                elif colour16_fg is not None:
                    fg = colour16_fg

                if colour256_bg is not None:
                    bg = colour256_bg
                elif colour16_bg is not None:
                    bg = colour16_bg

        return fg, bg, attr
