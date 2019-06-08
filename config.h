/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 10;       /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=8" };
static const char dmenufont[]       = "monospace:size=8";
static const char col_gray1[]       = "#1b1b22";
static const char col_gray2[]       = "#2b303b";
static const char col_gray3[]       = "#7e7e7e";
static const char col_gray4[]       = "#c0c5ce";
static const char col_black[]       = "#1b1b22";
static const char col_white[]       = "#f6f6f6";
static const char col_red[]         = "#bf4e5c";
static const char col_yellow[]      = "#ebeb8b";
static const char col_green[]       = "#a3be8c";
static const char col_cyan[]        = "#96b5b4";
static const char col_blue[]        = "#658cb2";
static const char col_magenta[]     = "#b48ead";
static const char *colors[][10]     = {
	/*               fg              bg          border   */
	[SchemeNorm]   = { col_gray3,    col_gray1,  col_gray2 },       // \x01
	[SchemeSel]    = { col_gray1,    col_red,    col_red  },
	[SchemeWarn]   = { col_black,    col_yellow, col_red },
	[SchemeUrgent] = { col_white,    col_red,    col_red },
	[SchemeFive]   = { col_red,      col_gray1,  col_red },
	[SchemeSix]    = { col_yellow,   col_gray1,  col_red },
	[SchemeSeven]  = { col_green,    col_gray1,  col_red },
	[SchemeEight]  = { col_cyan,     col_gray1,  col_red },
	[SchemeNine]   = { col_blue,     col_gray1,  col_red },
	[SchemeTen]    = { col_magenta,  col_gray1,  col_red },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
 /* modifier            key                  function        argument */
 { MODKEY,              XK_b,                togglebar,      {0} },
 { MODKEY,              XK_j,                focusstack,     {.i = +1 } },
 { MODKEY,              XK_k,                focusstack,     {.i = -1 } },
 /* { MODKEY|ShiftMask,    XK_j,                movestack,      {.i = +1 } }, */
 /* { MODKEY|ShiftMask,    XK_k,                movestack,      {.i = -1 } }, */
 { MODKEY|ShiftMask,    XK_i,                incnmaster,     {.i = +1 } },
 { MODKEY|ShiftMask,    XK_o,                incnmaster,     {.i = -1 } },
 { MODKEY,              XK_h,                setmfact,       {.f = -0.05} },
 { MODKEY,              XK_l,                setmfact,       {.f = +0.05} },
 { MODKEY,              XK_Tab,              view,           {0} },
 { MODKEY|ShiftMask,    XK_q,                killclient,     {0} },
 { MODKEY,              XK_f,                setlayout,      {.v = &layouts[1]} },
 { MODKEY|ShiftMask,    XK_f,                setlayout,      {0} },
 { MODKEY|ShiftMask,    XK_space,            togglefloating, {0} },
 /* { MODKEY,              XK_bracketleft,      shiftview,      { .i = -1 } }, */
 /* { MODKEY,              XK_bracketright,     shiftview,      { .i = 1 } }, */
 { MODKEY|ShiftMask,    XK_Return,           zoom,           {0} },
 { MODKEY,              XK_0,                view,           {.ui = ~0 } },
 { MODKEY|ShiftMask,    XK_0,                tag,            {.ui = ~0 } },
 { MODKEY,              XK_F2,               quit,           {0} },
 /* { MODKEY,              XK_period,           cyclelayout,    {.i = +1 } }, */
 /* { MODKEY,              XK_comma,            cyclelayout,    {.i = -1 } }, */
 /* { MODKEY,              XK_minus,            setgaps,        {.i = -1 } }, */
 /* { MODKEY|ShiftMask,    XK_equal,            setgaps,        {.i = +1 } }, */
 /* { MODKEY,              XK_equal,            setgaps,        {.i = 0 } }, */
 TAGKEYS(XK_1, 0)
 TAGKEYS(XK_2, 1)
 TAGKEYS(XK_3, 2)
 TAGKEYS(XK_4, 3)
 TAGKEYS(XK_5, 4)
 TAGKEYS(XK_6, 5)
 TAGKEYS(XK_7, 6)
 TAGKEYS(XK_8, 7)
 TAGKEYS(XK_9, 8)
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

