/**
 * Integration plugin for the stylish extension.
 *
 * Usage:
 *   :stylish popup   opens the stylish menu popup.
 *   :stylish sidebar open the stylish sidebar.
 *   :stylish toggle  toggles styles on the current page.
 *
 * Note: when the stylish popup is open, you can scroll through the items
 * using the following standard vimperator key bindings:
 *   j  move down one
 *   k  move up one
 *   l  open the sub-menu
 *   h  close the sub-menu
 * For implementation simplicity, only single character bindings are supported,
 * so you cannot supply counts to any of the above.
 *
 * TODO:
 *   - :stylish manage        open the manage popup
 *   - :stylish edit <style>  edit the specified style (enable completion)
 *   - enable editing via &editor
 *
 * @author Eric Van Dewoestine (ervandew@gmail.com)
 * @version 0.2
 */

/**
 * Class which provides support for stylish commands and hooks into the
 * stylish popup to provide vimperator scrolling bindings (j,k,l,h,g,G).
 *
 * Note: There appears to be a bug in firefox's menupopup key bindings, where
 * if you navigate to a sub popup (l or right arrow), and navigate back to the
 * main popup (h or left arrow), then the menupopup seems to lose the ability
 * to navigate back to the sub menu, and loses the ability to close the main
 * popup via esc (an alt-tab should still close it).  This behavior is
 * reproducable with or without this plugin.
 */
function StylishVimperator() {
  var popup = document.getElementById("stylish-popup");
  if (!popup){ // < stylish 1.0
    popup = document.getElementById("stylish-status-popup");
  }

  popup.addEventListener('popupshown', popupshown, true);
  popup.addEventListener('popuphidden', popuphidden, true);

  function popupshown(event){
    if (event.target == popup){
      window.addEventListener("keypress", keypress, true);
    }
  }

  function popuphidden(event){
    if (event.target == popup){
      window.removeEventListener("keypress", keypress, true);
    }
  }

  function keypress(event){
    var keyCode = null;
    switch(String.fromCharCode(event.which)){
      case "j":
        keyCode = 40;
        break;
      case "k":
        keyCode = 38;
        break;
      case "l":
        keyCode = 39;
        break;
      case "h":
        keyCode = 37;
        break;
      default:
        break;
    }

    if (keyCode){
      var newEvent = window.document.createEvent('KeyboardEvent');
      newEvent.initKeyEvent(
        "keypress", true, true, null, false, false, false, false, keyCode, 0);
      popup.dispatchEvent(newEvent);
    }
  }

  return {
    popup: function(){
      popup.openPopup();
    },

    sidebar: function(){
      if (typeof(stylishBrowserOverlay) != 'undefined'){ // < stylish 1.0
        stylishBrowserOverlay.openSidebar();
      }else{
        var em = Components.classes["@mozilla.org/appshell/window-mediator;1"]
          .getService(Components.interfaces.nsIWindowMediator)
          .getMostRecentWindow(name);
        if (em) {
          em.toggleSidebar('viewStylishSidebar');
        }
      }
    },

    toggle: function(){
      var applicableStyles;
      if (typeof(stylishBrowserOverlay) != 'undefined'){ // < stylish 1.0
        applicableStyles = stylishBrowserOverlay.getApplicableStyles();
      }else{
        applicableStyles = stylishOverlay.service.findForUrl(
          content.location.href, false, 0, {});
      }

      if (applicableStyles.length > 0) {
        for each (style in applicableStyles){
          style.enabled = !style.enabled;
          if (typeof(StylishStyle) == 'undefined'){ // >= stylish 1.0
            style.save();
          }
        }
        if (typeof(StylishStyle) != 'undefined'){ // < stylish 1.0
          StylishStyle.prototype.ds.save();
          stylishCommon.reloadManage();
        }
      }
    },

    _execute: function(args){
      var name = args.shift();
      var cmd = sv[name];
      if (!cmd){
        liberator.echoerr('Unsupported stylish command: ' + name);
        return false;
      }
      return cmd(args);
    },

    _completer: function(context){
      var commands = [];
      for (var name in sv){
        if (name.indexOf('_') !== 0 && sv.hasOwnProperty(name)){
          commands.push(name);
        }
      }
      context.completions = [[c, ''] for each (c in commands)];
    }
  };
}

var sv = StylishVimperator();

commands.addUserCommand(["stylish"],
  "Execute stylish commands",
  function(args) { sv._execute(args); },
  { argCount: '1', completer: sv._completer }
);
