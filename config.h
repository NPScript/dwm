/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 10;
static const int sidepad            = 10;
static const char *fonts[]          = { "SauceCodePro Nerd Font:style=Regular:pixelsize=14:antialias=true:autohint=true" };
static const char dmenufont[]       = "SauceCodePro Nerd Font:style=Regular:pixelsize=14:antialias=true:autohint=true";
static unsigned long barbg					= 0x191919;
static const char col_gray1[]       = "#191919";
static const char col_gray2[]       = "#2c2c2c";
static const char col_gray3[]       = "#888888";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#547f62";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "st",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
	{ "floating",NULL,     NULL,           0,         1,          0,           1,        -1 },
	{ "st",      NULL,     "cmus",         0x100, 0,          1,           0,        0  },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "Tiled",     tile },    /* first entry is default */
	{ "Free",      NULL },    /* no layout function means floating behavior */
	{ "Monocle",   monocle },
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
static const char *bravecmd[] = { "qutebrowser", NULL };
static const char *musiccmd[] = { "st", "cmus", NULL };
static const char *mailcmd[] = { "st", "neomutt", NULL };
static const char *filescmd[] = { "st", "sfm", NULL };
static const char *vimcmd[] = { "st", "nvim", NULL };
static const char *lockscr[] = { "slock", NULL };
static const char *ctrlcmd[] = { "smessage", NULL };
static const char *sayit[] = { "say-clip", "de-DE", NULL };
static const char *passm[] = { "passmenu", "--type", NULL };
static const char *manuals[] = { "manuals", NULL };
static const char *w3m[] = { "st", "w3m", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,							XK_i,			 spawn,					 {.v = ctrlcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_y,  setgaps,      		   {.i = -1 } },
	{ MODKEY,                       XK_x,  setgaps,       		 {.i = +1 } },
	{ MODKEY,         					    XK_r,  setgaps,    		     {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	{ MODKEY|ShiftMask,							XK_b,			 spawn,					 {.v = bravecmd } },
	{ MODKEY|ShiftMask,							XK_m,			 spawn,					 {.v = musiccmd } },
	{ MODKEY|ShiftMask,							XK_l,			 spawn,					 {.v = lockscr } },
	{ MODKEY|ShiftMask,							XK_e,			 spawn,					 {.v = mailcmd } },
	{ MODKEY|ShiftMask,							XK_f,			 spawn,					 {.v = filescmd } },
	{ MODKEY|ShiftMask,							XK_v,			 spawn,					 {.v = vimcmd } },
	{ MODKEY|ShiftMask,							XK_d,			 spawn,					 {.v = manuals } },
	{ MODKEY|ShiftMask,						XK_w,			 spawn,					 	 {.v = w3m } },
	{ MODKEY,												XK_s,			 spawn,					 {.v = sayit } },
	{ MODKEY|ControlMask,						XK_p,			 spawn,					 {.v = passm } },
	{ MODKEY,												XK_e, 		 spawn, 				 SHCMD("emojimenu -t -d 0") },
	{ 0,                       XF86XK_AudioLowerVolume, spawn, SHCMD("pactl set-sink-volume 0 -3%; pkill -RTMIN+10 dwmblocks") },
	{ 0,                       XF86XK_AudioMute, spawn, SHCMD("pactl set-sink-mute 0 toggle; pkill -RTMIN+10 dwmblocks") },
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, SHCMD("pactl set-sink-volume 0 +3%; pkill -RTMIN+10 dwmblocks") },
	{ 0,                       XF86XK_AudioPlay, spawn, SHCMD("playerctl play-pause") },
	{ 0,                       XF86XK_AudioNext, spawn, SHCMD("playerctl next") },
	{ 0,                       XF86XK_AudioPrev, spawn, SHCMD("playerctl previous") },
};
/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

