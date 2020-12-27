/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */

static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const unsigned int gappih    = 3;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 3;       /* vert inner gap between windows */
static const unsigned int gappoh    = 3;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 3;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "DroidSansMono Nerd Font:size=10:antialias=true:autohint=true", "JoyPixels:pixelsize=10:antialias=true:autohint=true" };
static const char dmenufont[]       = "DroidSansMono Nerd Font:size=10:antialias=true:autohint:true"; 
//backgorund color
static const char col_gray1[]       = "#222222";
//inactive window border color
static const char col_gray2[]       = "#444444";
//fontcolor
static const char col_gray3[]       = "#bbbbbb";
//current tag and current window font color
static const char col_gray4[]       = "#eeeeee";
//static const char col_gray4[]       = "#27292c";
//Top bar second color (blue) and active window border
//static const char col_cyan[]        = "#005577";
static const char col_cyan[]        = "#4c7965";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */

static const char *tags[] = { "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "  " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                     instance    title         tags mask     isfloating   monitor */
	{ "Gimp",                    NULL,       NULL,         1 << 3,       0,           -1 },
	{ "Spotify",                 NULL,       NULL,         1 << 8,       0,           -1 },
	{ "discord",                 NULL,       NULL,         1 << 6,       0,           -1 },
	{ "Steam",                   NULL,       NULL,         1 << 7,       0,           -1 },
//	{ "libreoffice-writer",      NULL,       NULL,         1 << 4,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },                       /* Default: Master on left, salves on right */
	{ "TTT",      bstack },                     /* Master on top, slaves on bottom */

	{ "|M|",      centeredmaster },             /* Master in middle, slaves on sides */
	{ ">M>",      centeredfloatingmaster },     /* Same but master floats */

	{ "[D]",      deck },                       /* Master on left, slaves in monocle-like mode on right */
	{ "[M]",      monocle },                    /* All windows on top of each other */

	{ "===",      bstackhoriz },                /* Stack horizontal */
	{ "HHH",      grid },                       /* Grid */

	{ "[@]",      spiral },                     /* Fibonnaci spiral */
	{ "[\\]",     dwindle },                    /* Decreasing in size right and leftward */

	{ "###",      nrowgrid },
	{ "---",      horizgrid },

	{ ":::",      gaplessgrid },
	{ "><>",      NULL },    /* no layout function means floating behavior */

	{ NULL,       NULL },
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
static const char *termcmd[]  = { "alacritty", NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                 key              function        argument */
	{ MODKEY,                   XK_d,            spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,         XK_Return,       spawn,          {.v = termcmd } },
	{ MODKEY,                   XK_b,            togglebar,      {0} },
	{ MODKEY,                   XK_j,            focusstack,     {.i = +1 } },
	{ MODKEY,                   XK_k,            focusstack,     {.i = -1 } },
	{ MODKEY,                   XK_h,            setmfact,       {.f = -0.05} },
	{ MODKEY,                   XK_l,            setmfact,       {.f = +0.05} },
	{ MODKEY,                   XK_Return,       zoom,           {0} },
	{ MODKEY,                   XK_Tab,          view,           {0} },
	//{ MODKEY|ShiftMask,         XK_c,            killclient,     {0} },
	{ MODKEY,                   XK_space,        setlayout,      {0} },
    { MODKEY,		            XK_t,		     setlayout,	     {.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,		    XK_t,		     setlayout,	     {.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			        XK_y,		     setlayout,	     {.v = &layouts[2]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,		    XK_y,		     setlayout,	     {.v = &layouts[3]} }, /* centeredfloatingmaster */
	{ MODKEY,			        XK_u,		     setlayout,	     {.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,		    XK_u,		     setlayout,	     {.v = &layouts[5]} }, /* monocle */
	{ MODKEY,			        XK_i,		     setlayout,	     {.v = &layouts[6]} }, /* bstackgrid */
	{ MODKEY|ShiftMask,		    XK_i,		     setlayout,	     {.v = &layouts[7]} }, /* grid */
	{ MODKEY,			        XK_o,		     incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,		    XK_o,		     incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,         XK_space,        togglefloating, {0} },
	{ MODKEY,                   XK_0,            view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,         XK_0,            tag,            {.ui = ~0 } },
	{ MODKEY,                   XK_comma,        focusmon,       {.i = -1 } },
	{ MODKEY,                   XK_period,       focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,         XK_comma,        tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,         XK_period,       tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,         XK_f,            spawn,          SHCMD("thunar") },
	{ MODKEY|ShiftMask,         XK_w,            spawn,          SHCMD("brave") },
	{ MODKEY|ShiftMask,         XK_s,            spawn,          SHCMD("flameshot gui") },
    { 0,                        XK_Print,        spawn,          SHCMD("flameshot screen") },
	TAGKEYS(                    XK_1,                            0)
	TAGKEYS(                    XK_2,                            1)
	TAGKEYS(                    XK_3,                            2)
	TAGKEYS(                    XK_4,                            3)
	TAGKEYS(                    XK_5,                            4)
	TAGKEYS(                    XK_6,                            5)
	TAGKEYS(                    XK_7,                            6)
	TAGKEYS(                    XK_8,                            7)
	TAGKEYS(                    XK_9,                            8)
	{ MODKEY|ShiftMask,         XK_q,            killclient,           {0} },
	{ MODKEY|ShiftMask,         XK_BackSpace,    quit,     {0} },

	{ 0, XF86XK_AudioMute,		    spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,		spawn,		SHCMD("playerctl previous") },
	{ 0, XF86XK_AudioNext,		spawn,		SHCMD("playerctl next") },
	{ 0, XF86XK_AudioPause,		spawn,		SHCMD("playerctl play-pause") },
	{ 0, XF86XK_AudioPlay,		spawn,		SHCMD("playerctl play-pause") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("light -A 10") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("light -U 10") },

	/* { MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} }, */
	/* { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } }, */
	/* { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } }, */
	/* { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } }, */
	/* { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } }, */
	/* { MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } }, */
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

