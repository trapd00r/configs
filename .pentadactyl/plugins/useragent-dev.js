"use strict";
XML.ignoreWhitespace = false;
XML.prettyPrinting   = false;
var INFO =
<plugin name="useragent" version="0.2"
        href="http://dactyl.sf.net/pentadactyl/plugins#useragent-plugin"
        summary="User Agent Switcher"
        xmlns={NS}>
    <author email="maglione.k@gmail.com">Kris Maglione</author>
    <license href="http://opensource.org/licenses/mit-license.php">MIT</license>
    <project name="Pentadactyl" min-version="1.0"/>
    <p>
        Ths plugin allows you to switch the browser's reported user-agent to a
        number of preset values.
    </p>
    <item>
        <tags>:ua :useragent</tags>
        <spec>:useragent <oa>name</oa> <oa>useragent</oa></spec>
        <description>
            <p>
                With zero or one arguments, list the currently defined
                user-agent values.
            </p>

            <p>
                With two arguments, defines a new user-agent for use in the
                <o>useragent</o> option. When <o>useragent</o> is set to
                <oa>name</oa>, the <tt>User-Agent</tt> value sent to web
                servers, and the value returned by
                <tt>navigator.userAgent</tt> will be <oa>useragent</oa>.
                Additionally, the following options are available:
            </p>

            <dl>
                <dt>-appcodename</dt> <dd>The value of <tt>navigator.appCodeName</tt></dd>
                <dt>-appname</dt>     <dd>The value of <tt>navigator.appName</tt></dd>
                <dt>-appversion</dt>  <dd>The value of <tt>navigator.appVersion</tt></dd>
                <dt>-platform</dt>    <dd>The value of <tt>navigator.platform</tt></dd>
                <dt>-vendor</dt>      <dd>The value of <tt>navigator.vendor</tt></dd>
                <dt>-vendorsub</dt>   <dd>The value of <tt>navigator.vendorsub</tt></dd>
            </dl>
        </description>
    </item>
    <item>
        <tags>:deluseragent :delua</tags>
        <spec>:deluseragent <a>name</a></spec>
        <description>
            <p>Deletes a useragent created by <ex>:useragent</ex>.</p>
        </description>
    </item>
    <item>
        <tags>'useragent' 'ua'</tags>
        <spec>'useragent' 'ua'</spec>
        <type>string</type> <default>default</default>
        <description>
            <p>
                Changes the User-Agent string sent to the web server and
                returned by <tt>navigator.userAgent</tt>. If the value is the
                name of a user-agent defined by <ex>:useragent</ex>, or one of
                the predefined values, then the defined value is used.
                Otherwise, the value itself is used.
            </p>
        </description>
    </item>
</plugin>;

let UserAgent = Struct("name", "useragent", "appname", "appcodename",
                       "appversion", "platform", "vendor", "vendorsub", "userset");
UserAgent.prototype.__defineGetter__("options", function ()
    opts.slice(1).map(function (opt) [opt.name, this[opt.name]], this)
        .filter(function (opt) opt[1]));
let useragents = array([
    // From User Agent Switcher 0.7.2
    ["ie-6", "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)",
        "Mozilla", "Microsoft Internet Explorer", "4.0 (compatible; MSIE 6.0; Windows NT 5.1)",
        "Win32"],
    ["ie-7", "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0)",
        "Mozilla", "Microsoft Internet Explorer", "4.0 (compatible; MSIE 7.0; Windows NT 6.0)",
        "Win32"],
    ["ie-8", "Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1)",
        "Mozilla", "Microsoft Internet Explorer", "4.0 (compatible; MSIE 8.0; Windows NT 6.1)",
        "Win32"],
    ["bot-googlebot-2.1", "Mozilla/5.0 (compatible; Googlebot/2.1; +http://www.google.com/bot.html)"],
    ["bot-msnbot-1.1", "msnbot/1.1 (+http://search.msn.com/msnbot.htm)"],
    ["bot-yahoo", "Mozilla/5.0 (compatible; Yahoo! Slurp; http://help.yahoo.com/help/us/ysearch/slurp)"],
    ["iphone-3", "Mozilla/5.0 (iPhone; U; CPU iPhone OS 3_0 like Mac OS X; en-us) AppleWebKit/528.18 (KHTML, like Gecko) Version/4.0 Mobile/7A341 Safari/528.16",
        "Mozilla", "Netscape", "5.0 (iPhone; U; CPU iPhone OS 3_0 like Mac OS X; en-us) AppleWebKit/528.18 (KHTML, like Gecko) Version/4.0 Mobile/7A341 Safari/528.16",
        "iPhone", "Apple Computer, Inc.", ""]
]).map(function (ua) [ua[0], UserAgent.fromArray(ua)]).toObject();

let Opt = Struct("name", "description", "pref", "names");
Opt.defaultValue("names", function () ["-" + this.name]);
let opts = [
    ["useragent",   "The value of navigator.userAgent",   "general.useragent.override"],
    ["appcodename", "The value of navigator.appCodeName", "general.useragent.appName"],
    ["appname",     "The value of navigator.appName",     "general.appname.override"],
    ["appversion",  "The value of navigator.appVersion",  "general.appversion.override"],
    ["platform",    "The value of navigator.platform",    "general.platform.override"],
    ["vendor",      "The value of navigator.vendor",      "general.useragent.vendor"],
    ["vendorsub",   "The value of navigator.vendorsub",   "general.useragent.vendorSub"]
].map(Opt.fromArray, Opt);

options.add(["useragent", "ua"],
    "The current browser user-agent",
    "string", "default",
    {
        completer: function (context, args) {
            context.title = ["Name", "User-Agent"];
            context.keys = { text: "name", description: "useragent" };
            context.completions = array(values(useragents)).concat(
                [{ name: "default", useragent: navigator.userAgent }]);
        },
        setter: function (value) {
            let ua = useragents[value] ||
                (value == "default" ? UserAgent("default")
                                    : UserAgent("", value));
            for (let opt in values(opts))
                if (ua[opt.name])
                    prefs.safeSet(opt.pref, ua[opt.name], "See the 'useragent' option");
                else
                    prefs.safeReset(opt.pref, "See the 'useragent' option");
            return value;
        }
    });

group.commands.add(["useragent", "ua"],
    "Define a new useragent.",
    function (args) {
        if (args.length < 2)
            commandline.commandOutput(template.tabular(["Name", "User-Agent"], ["padding-right: 1em; min-width: 8em;", "white-space: normal;"],
                [[ua.name,
                  <>
                    {ua.useragent}
                    {
                        !ua.options.length ? "" :
                        <span class="extra-info">
                            ({
                                template.map(ua.options, function (o)
                                <><span highlight="Key Normal">{o[0]}</span>=<span highlight="String">{o[1]}</span></>,
                                <>&#xa0;</>)
                            })
                        </span>
                    }
                  </>]
                 for (ua in values(useragents))
                 if (!args[0] || ua.name.indexOf(args[0]) >= 0)]));
        else {
            dactyl.assert(args.bang || !set.has(useragents, args[0]),
                          "Useragent " + args[0].quote() + " already exists");
            useragents[args[0]] = UserAgent.fromArray(
                args.concat(opts.slice(1).map(
                    function (opt) args[opt.names[0]])));
            useragents[args[0]].userset = true;
        }
    }, {
        bang: true,
        completer: function (context, args) {
            if (args.completeArg == 1)
                context.completions = [[navigator.userAgent, "Default"]].concat(
                    [[v.useragent, k] for ([k, v] in Iterator(useragents))]);
        },
        literal: 1,
        options: opts.slice(1).map(function (opt) ({
            names: opt.names,
            description: opt.description,
            completer: function (context, args)
                array(values(useragents)).map(function (ua) ua[opt.name])
                                         .uniq()
                                         .map(function (val) [val, ""]).array,
            type: CommandOption.STRING
        })),
        serialize: function () [
            {
                command: this.name,
                arguments: [ua.name],
                bang: true,
                literalArg: ua.useragent,
                options: array(
                    [opt.names[0], ua[opt.name]]
                    for (opt in values(opts.slice(1)))
                    if (ua[opt.name] != null)
                ).toObject()
            }
            for (ua in values(useragents)) if (ua.userset)
        ]
    }, true);

group.commands.add(["deluseragent", "delua"],
    "Deletes a useragent.",
    function (args) {
        dactyl.assert(set.has(useragents, args[0]), "Invalid argument");
        if (options["useragent"] == args[0])
            options["useragent"] = "default";
        delete useragents[args[0]];
    }, {
        argCount: "1"
    }, true);

/* vim:se sts=4 sw=4 et: */
