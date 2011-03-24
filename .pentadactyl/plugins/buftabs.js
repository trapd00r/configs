// {{{ Information
var INFO =
<plugin name="buftabs" version="1.0"
    href="http://git.glacicle.org/vimperator-buftabs/"
    summary="Buftabs: show the tabbar in the statusline"
    xmlns={NS}>
    <author email="lucas@glacicle.org">Lucas de Vries</author>
    <license href="http://sam.zoy.org/wtfpl/">WTFPL</license>
    <project name="Pentadactyl" minVersion="1.0"/>
    <p>
        When the script is loaded it hijacks the statusline to display a
        list of tabs, you can use the <o>buftabs</o> option to toggle it
        on or off.
    </p>

    <p>
        Use the BufTab and BufTabSelected highlight groups to style the
        buftabs. Make sure youve called the "loadplugins" command
        before using the highlight groups in your vimperatorrc.
    </p>

    <p>
        You can set the max length of a title before it is cut off with
        the <o>buftabs-maxlength</o> option. It is set to 25 by default.
    </p>
    <item>
        <tags>'bt' 'buftabs'</tags>
        <spec>'buftabs' 'bt'</spec>
        <type>boolean</type> <default>true</default>
        <description>
            Toggle the buftabs on or off.
        </description>
    </item>
    <item>
        <tags>'btm' 'buftabs-maxlength'</tags>
        <spec>'buftabs-maxlength' 'btm'</spec>
        <type>number</type> <default>13</default>
        <description>
            The maximum length in characters of a single entry in the buftabs line.
            Set to 0 for unlimited.
        </description>
    </item>
    <item>
        <tags>'btf' 'buftabs-showicons'</tags>
        <spec>'buftabs-showicons' 'btf'</spec>
        <type>number</type> <default>false</default>
        <description>
            Toggle favicon support on or off.
        </description>
    </item>
    <item>
        <tags>'btc' 'buftabs-completer'</tags>
        <spec>'buftabs-completer' 'btc'</spec>
        <type>number</type> <default>"..."</default>
        <description>
            Trailing string when title longer than maxlength.
            Set to empty string for no trailing string.
        </description>
    </item>
</plugin>;
// }}}

let buftabs = {
    // Update the tabs
    update: function ()
    {
        if (!options["buftabs"])
            return;

        // Get buftabbar
        var btabs = commandline.widgets.statusbar.buftabs;
        var visibleTabs = tabs.visibleTabs;
        var position=0, selpos;

        // Make sure we have an appropriate amount of labels
        while (btabs.childNodes.length > visibleTabs.length)
        {
            btabs.removeChild(btabs.lastChild);
        }

        while (btabs.childNodes.length < visibleTabs.length)
        {
            let label = document.createElement("label");
            btabs.appendChild(label);

            label.addEventListener("click", function (ev)
            {
                if (ev.button == 0)
                    tabs.select(this.tabpos);
                else if (ev.button == 1)
                    tabs.remove(tabs.getTab(this.tabpos), 1, false, 0);
            }, false);
        }

        // Create the new tabs
        for (let [i, tab] in iter(visibleTabs))
        {
            // Create label
            let browser = tab.linkedBrowser;
            let label = btabs.childNodes[i];

            // Hook on load
            if (browser.webProgress.isLoadingDocument)
            {
                browser._buftabs_label = label;
                browser.contentDocument.addEventListener("load", function ()
                {
                    buftabs.fillLabel(this._buftabs_label, this);
                }, false);
            }

            // Fill label
            label.tabpos = i;
            buftabs.fillLabel(label, browser);

            if (tabs.index(null, true) == label.tabpos)
            {
                selpos = [position, label.clientWidth+position];
            }

            position += label.clientWidth;
        }

        // Scroll
        if (selpos[0] < btabs.scrollLeft || selpos[1] > btabs.scrollLeft+btabs.clientWidth)
            btabs.scrollLeft = selpos[0];

        // Show the entire line if possible
        if (btabs.scrollWidth == btabs.clientWidth)
            btabs.scrollLeft = 0;
    },

    // Fill a label with browser content
    fillLabel: function(label, browser)
    {
        var maxlength = options.get("buftabs-maxlength").get();
        var showicons = options.get("buftabs-showicons").get();
        var threedots = options.get("buftabs-completer").get();
        var tabvalue;
        var favicon = BookmarkCache.getFavicon(browser.contentDocument.location.href);

        // Get title
        if (browser.webProgress.isLoadingDocument)
        {
            tabvalue = "Loading...";
        } else {
            tabvalue = browser.contentTitle || "Untitled";
        }

        // Check length
        if (maxlength > 0 && tabvalue.length > maxlength)
            tabvalue = tabvalue.substr(0, maxlength-threedots.length)+threedots;

        // Bookmark icon
        if (bookmarkcache.isBookmarked(browser.contentDocument.location.href))
            tabvalue += "\u2764";

        // Brackets and index
        tabvalue = "["+(label.tabpos+1)+"-"+tabvalue+"]";

        label.setAttribute("value", tabvalue);
        if (showicons==true)
        {
            label.style.paddingLeft="20px";
            label.style.background='url("'+favicon+'") no-repeat left top';
            label.style.MozBackgroundSize='16px 16px';
        }
	else
	{
	    label.style.paddingLeft="0px";
            label.style.background='';
            label.style.MozBackgroundSize='0px 0px';
	}

        // Set the correct highlight group
        if (tabs.index(null, true) == label.tabpos)
            label.setAttributeNS(NS.uri, "highlight", "BufTabSelected");
        else
            label.setAttributeNS(NS.uri, "highlight", "BufTab");


    },

    // Create the horizontal box for adding the tabs to
    createBar: function()
    {
        let id = "dactyl-statusline-field-buftabs";
        if (document.getElementById(id))
            return;

        let widget = util.xmlToDom(
            <hbox xmlns={XUL} highlight="BufTabs" id={id} flex="1" style="overflow: hidden"/>,
            document);
        statusline.widgets.url.parentNode.insertBefore(
            widget, statusline.widgets.url.nextSibling);
        commandline.widgets.addElement({
            name: "buftabs",
            getGroup: function () this.statusbar,
            getValue: function () statusline.visible && options["buftabs"],
            noValue: true
        });
    }
};

/// Attach to events in order to update the tabline
var tabContainer = window.getBrowser().mTabContainer;
["TabMove", "TabOpen", "TabClose", "TabSelect"].forEach(function (event) {
    tabContainer.addEventListener(event, function (event) {
        buftabs.update();
    }, false);
});

document.getElementById("appcontent").addEventListener("load", function (event) {
    buftabs.update();
}, true);

/// Initialise highlight groups
highlight.loadCSS(<![CDATA[
    !BufTabs          background: inherit; color: inherit;
    !BufTab
    !BufTabSelected   font-weight: bold;
]]>);

/// Options
options.add(["buftabs", "bt"],
        "Control whether to use buftabs in the statusline",
        "boolean", true, 
        {
            setter: function (value)
            {
                if (value)
                    buftabs.createBar();
                commandline.widgets.updateVisibility();
                buftabs.update();
                return value;
            }
        });

options.add(["buftabs-maxlength", "btm"],
        "Max length of an entry in the buftabs list",
        "number", "13", 
        {
            setter: function (value)
            {
                buftabs.update();
                return value;
            }
        });

options.add(["buftabs-showicons", "btf"],
        "Show Favicons in buftabs",
        "boolean", false, 
        {
            setter: function (value)
            {
                buftabs.createBar();
		commandline.widgets.updateVisibility();
                buftabs.update();
		return value;
            }
        });

options.add(["buftabs-completer", "btc"],
        "How to complete title if longer than maxlength",
        "string", "...", 
        {
            setter: function (value)
            {
                buftabs.update();
                return value;
            }
        });