/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "mono:pixelsize=10" };
static const char dmenufont[]       = "mono:pixelsize=10";
static const char col_gray1[]       = "#000000"; //05
static const char col_gray2[]       = "#ffffff"; //00
static const char col_gray3[]       = "#ffffff"; //00
static const char col_gray4[]       = "#000000"; //05
/* static const char col_cyan[]        = "#1d1f21"; //07 */
static const char col_cyan[]        = "#3e999f"; //07
static const char *colors[][3]      = {
        /*               fg         bg         border   */
        [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
        [SchemeSel]  = { col_gray4, col_gray3, col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
        /* xprop(1):
         *      WM_CLASS(STRING) = instance, class
         *      WM_NAME(STRING) = title
         */
        /* class      instance    title       tags mask     isfloating   monitor */
        { "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "mpv",      NULL,       NULL,       0,            1,           -1 },
	{ "sxiv",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  "Toolkit",  "Picture-in-Picture",     0,  1,  -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
        /* symbol     arrange function */
        { "[]=",      tile },    /* first entry is default */
        { "><>",      NULL },    /* no layout function means floating behavior */
        { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
        { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
        { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define XF86AudioLowerVolume    0x1008ff11
#define XF86AudioMicMute        0x1008ffb2
#define XF86AudioMute           0x1008ff12
#define XF86AudioNext           0x1008ff17
#define XF86AudioPlay           0x1008ff14
#define XF86AudioPrev           0x1008ff16
#define XF86AudioRaiseVolume    0x1008ff13
#define XF86AudioStop           0x1008ff15
#define XF86MonBrightnessDown   0x1008ff03
#define XF86MonBrightnessUp     0x1008ff02
#define XF86ScreenSaver         0x1008ff2d
#define XF86TouchpadToggle      0x1008ffa9

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(sh, cmd) { .v = (const char*[]){ "/usr/bin/env", sh, "-c", cmd, NULL } }
#define TERM "st", "-e"
#define DMENUOPS "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_gray2, "-sf", col_gray4, NULL
#define SCREENSHOT  "scrot '%Y-%m-%d-%H-%M-%S.png' -q 90 -e 'xclip -selection clipboard -t image/png \"$f\"; mv \"$f\" ~/Pictures/Screenshots'"
#define SCREENSHOTREGION  "sleep 0.4; scrot '%Y-%m-%d-%H-%M-%S.png' -q 90 -s -e 'xclip -selection clipboard -t image/png \"$f\"; mv \"$f\" ~/Pictures/Screenshots'"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]       = { "dmenu_run", DMENUOPS, NULL};
static const char *termcmd[]        = { "st", NULL };
static const char *brightnessdown[] = { "xbacklight", "-2", NULL };
static const char *brightnessup[]   = { "xbacklight", "+2", NULL };
static const char *clipmenu[]       = { "sh", "-c", "clipmenu", DMENUOPS };
static const char *irssi[]          = { TERM, "bash", "-ic", "tmux attach -t irssi || tmux new -s irssi irssi", NULL };
static const char *lock[]           = { "loginctl", "lock-session", NULL };
static const char *micmute[]        = { "amixer", "-q", "sset", "Capture", "toggle", NULL };
static const char *mutt[]           = { TERM, "bash", "-ic", "neomutt", NULL };
static const char *next[]           = { "playerctl", "next",  NULL };
static const char *passmenu[]       = { "passmenu", DMENUOPS };
static const char *play[]           = { "playerctl", "play-pause",  NULL };
static const char *prev[]           = { "playerctl", "previous",  NULL };
static const char *reboot[]         = { "sudo", "reboot", NULL };
static const char *rss[]            = { TERM, "newsboat", NULL };
static const char *shutdown[]       = { "sudo", "shutdown", "-h", "now", NULL };
static const char *sounddown[]      = { "amixer", "-q", "sset", "Master", "5%-", NULL };
static const char *soundtoggle[]    = { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *soundup[]        = { "amixer", "-q", "sset", "Master", "5%+", NULL };
static const char *stop[]           = { "playerctl", "stop",  NULL };
static const char *touchpadtoggle[] = { "touchpadtoggle.sh", NULL };

static Key keys[] = {
        /* modifier                     key        function        argument */
        { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
        /* { MODKEY,                       XK_Return, spawn,          SHCMD("sh", "$TERMINAL") }, */
        { MODKEY,                       XK_b,      togglebar,      {0} },
        { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
        { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
        { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
        { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
        { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
        { MODKEY,                       XK_Tab,    view,           {0} },
        { MODKEY,                       XK_q,      killclient,     {0} },
        { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
        { MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_space,  setlayout,      {0} },
        { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
        { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
        { MODKEY,                       XK_comma,  focusmon,       {.i = +1 } },
        { MODKEY,                       XK_period, focusmon,       {.i = -1 } },
        { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = +1 } },
        { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = -1 } },
        TAGKEYS(                        XK_1,                      0)
        TAGKEYS(                        XK_2,                      1)
        TAGKEYS(                        XK_3,                      2)
        TAGKEYS(                        XK_4,                      3)
        TAGKEYS(                        XK_5,                      4)
        TAGKEYS(                        XK_6,                      5)
        TAGKEYS(                        XK_7,                      6)
        TAGKEYS(                        XK_8,                      7)
        TAGKEYS(                        XK_9,                      8)
        { MODKEY|ShiftMask,     XK_q,                   quit,   {0} },
        /* { 0,                    XF86AudioLowerVolume,   spawn,  {.v = sounddown } }, */
        /* { 0,                    XF86AudioMicMute,       spawn,  {.v = micmute } }, */
        /* { 0,                    XF86AudioNext,          spawn,  {.v = next } }, */
        /* { 0,                    XF86AudioPlay,          spawn,  {.v = play } }, */
        /* { 0,                    XF86AudioPrev,          spawn,  {.v = prev } }, */
        /* { 0,                    XF86AudioStop,          spawn,  {.v = stop } }, */
        /* { 0,                    XF86AudioMute,          spawn,  {.v = soundtoggle } }, */
        /* { 0,                    XF86AudioRaiseVolume,   spawn,  {.v = soundup } }, */
        /* { 0,                    XF86MonBrightnessDown,  spawn,  {.v = brightnessdown } }, */
        /* { 0,                    XF86MonBrightnessUp,    spawn,  {.v = brightnessup } }, */
        /* { 0,                    XF86ScreenSaver,        spawn,  {.v = lock } }, */
        /* { 0,                    XF86TouchpadToggle,     spawn,  {.v = touchpadtoggle } }, */
        /* { MODKEY,               XK_m,                   spawn,  {.v = mutt } }, */
        /* { MODKEY,               XK_n,                   spawn,  {.v = rss } }, */
        /* { MODKEY,               XK_w,                   spawn,  SHCMD("sh", "$BROWSER") }, */
        /* { MODKEY,               XK_y,                   spawn,  {.v = clipmenu } }, */
        /* { MODKEY|ControlMask,   XK_i,                   spawn,  {.v = irssi } }, */
        /* { MODKEY|ShiftMask,     XK_BackSpace,           spawn,  {.v = reboot } }, */
        /* { MODKEY|ShiftMask,     XK_p,                   spawn,  {.v = passmenu} }, */
        /* { MODKEY|ShiftMask,     XK_x,                   spawn,  {.v = shutdown } }, */
        /* { 0,                    XK_Print,               spawn,  SHCMD("sh", SCREENSHOTREGION) }, */
        /* { ShiftMask,            XK_Print,               spawn,  SHCMD("sh", SCREENSHOT) }, */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
        /* click                event mask      button          function        argument */
        { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
        { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
        { ClkWinTitle,          0,              Button2,        zoom,           {0} },
        { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
        { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
        { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
        { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
        { ClkTagBar,            0,              Button1,        view,           {0} },
        { ClkTagBar,            0,              Button3,        toggleview,     {0} },
        { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
        { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
