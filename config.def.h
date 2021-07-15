/* appearance */
static const int sloppyfocus        = 1;  /* focus follows mouse */
static const unsigned int borderpx  = 2;  /* border pixel of windows */
static const unsigned int gappx     = 6;  /* gaps between windows */
static const float rootcolor[]      = {0.3, 0.3, 0.3, 1.0};
static const float focuscolor[]     = {0.4, 0.0, 1.0, 1.0};
static const float bordercolor[]    = {0.0, 0.0, 0.0, 0.7};
static const double default_alpha   = 0.9;

static const char *const autostart[] = {
	"sh", "-c", "swaylock --image $(chbg --print)", NULL,
	"sh", "-c", "swaybg --image $(chbg --print) --mode fill", NULL,
	"sh", "-c", "slstatus.bottom -s | dtao -z -z -ta l -b -L bottom -fn 'UbuntuMono Nerd Font:size=16:antialias=true:autohint:true'", NULL,
	"redshift", "-m", "wayland", NULL,
	"pipewire", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { " ", "﬏ ", " ", " ", " ", " ", " ", " ", " ", " " };

static const Rule rules[] = {
	/* app_id     title       tags mask     isfloating   alpha           monitor */
	/* examples:
	{ "Gimp",     NULL,       0,            1,           default_alpha   -1 },
	{ "firefox",  NULL,       1 << 8,       0,           default_alpha   -1 },
	{ "Alacritty",NULL,       1 << 2,       0,           1.0             -1 },
	*/
	{"Alacritty", NULL,       1<<2,         0,           1.0,            -1},
	{"foot",      NULL,       1<<2,         0,           1.0,            -1},
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ NULL,       NULL },
};

/* monitors
 * The order in which monitors are defined determines their position.
 * Non-configured monitors are always added to the left. */
static const MonitorRule monrules[] = {
	/* name       mfact nmaster scale layout       rotate/reflect x y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 0, 0 },
	*/
	/* defaults */
	{ NULL,       0.50, 1,      1,    &layouts[2], WL_OUTPUT_TRANSFORM_NORMAL, 0, 0 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.layout  = "latam,latam,us",
	.model   = "pc105",
	.variant = "dvorak,,",
	.options = "grp:win_space_toggle , keypad:pointerkeys , terminate:ctrl_alt_bksp",
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Time (in miliseconds) until the cursor will hidde */
static const int cursor_inactive = 1000;
static const int hide_cursor = 0;

/* Trackpad */
static const int tap_to_click = 1;
static const int natural_scrolling = 0;

#define MODKEY  WLR_MODIFIER_LOGO
#define ALTKEY  WLR_MODIFIER_ALT
#define Control WLR_MODIFIER_CTRL
#define Shift   WLR_MODIFIER_SHIFT

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, KEY,            tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,KEY,toggletag,  {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[] = { "foot", NULL };
static const char *menucmd[] = {
	"wofi",
	"--show=drun",
	"--lines=10",
	"--allow-images",
	NULL
};

#include "keys.h"
#include "mpdcontrol.c"
static const Key keys[] = {
	/* modifier            key              function          argument */

	/* ------------------ Windows ------------------ */

	/* Switch between windows */
	{ MODKEY,              Key_j,           focusstack,       {.i = +1} },
	{ MODKEY,              Key_k,           focusstack,       {.i = -1} },

	/* Change window sizes */
	{ MODKEY,              Key_i,           incnmaster,       {.i = +1} },
	{ MODKEY|Shift,        Key_i,           incnmaster,       {.i = -1} },
	{ MODKEY,              Key_h,           setmfact,         {.f = -0.05} },
	{ MODKEY,              Key_l,           setmfact,         {.f = +0.05} },

	/* Toggle floating */
	{ MODKEY|Control,      Key_f,           togglefloating,   {0} },

	/* Toggle fullscreen */
	{ MODKEY|Shift,        Key_f,           togglefullscreen, {0} },

	/* Cycle layouts */
	{ MODKEY,              Key_Tab,         cyclelayout,      {.i = +1 } },
	{ MODKEY|Shift,        Key_Tab,         cyclelayout,      {.i = -1 } },

	/* Focus next - prev monitor */
	{ MODKEY,              Key_comma,       focusmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,              Key_period,      focusmon,         {.i = WLR_DIRECTION_RIGHT} },

	/* Send window to next - prev monitor */
	{ MODKEY|Shift,        Key_comma,       tagmon,           {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|Shift,        Key_period,      tagmon,           {.i = WLR_DIRECTION_RIGHT} },

	/* Change opacity for clients */
	{ MODKEY|Shift,        Key_KP_Add,      changealpha,      {.f = +0.1 } },
	{ MODKEY|Shift,        Key_KP_Subtract, changealpha,      {.f = -0.1 } },

	/* Kill window */
	{ MODKEY,              Key_w,           killclient,       {0} },

	/* Quit dwl */
	{ MODKEY|Control,      Key_q,           quit,             {.i = EXIT_SUCCESS } },

	/* Restart dwl */
	{ MODKEY|Control,      Key_r,           quit,             {.i = EXIT_FAILURE } },


	/* ---------------- Workspaces ----------------- */
	TAGKEYS(               Key_1,                             0),
	TAGKEYS(               Key_2,                             1),
	TAGKEYS(               Key_3,                             2),
	TAGKEYS(               Key_4,                             3),
	TAGKEYS(               Key_5,                             4),
	TAGKEYS(               Key_6,                             5),
	TAGKEYS(               Key_7,                             6),
	TAGKEYS(               Key_8,                             7),
	TAGKEYS(               Key_9,                             8),
	TAGKEYS(               Key_0,                             9),

	/* Switch between the last tag and the current */
	{ MODKEY,              Key_slash,       view,             { .ui = 0 } },


	/* ------------------- Apps -------------------- */

	{ MODKEY,              Key_m,           spawn,            {.v = menucmd} },

	/* wofi */
	{ MODKEY,              Key_Menu,        spawn,            SHCMD("wofi --show=run") },

	/* Terminal emulators */
	{ MODKEY,              Key_Return,      spawn,            {.v = termcmd} },
	{ MODKEY|Shift,        Key_Return,      spawn,            SHCMD("alacritty") },

	/* File explorers */
	{ MODKEY,              Key_e,           spawn,            SHCMD("pcmanfm") },
	{ MODKEY|Shift,        Key_e,           spawn,            SHCMD("thunar") },


	/* Browsers */
	{ MODKEY,              Key_b,           spawn,            SHCMD("microsoft-edge-dev") },
	{ MODKEY,              Key_f,           spawn,            SHCMD("firefox") },


	/* Redshift */
	{ MODKEY,              Key_r,           spawn,            SHCMD("redshift -O 2400") },
	{ MODKEY|Shift,        Key_r,           spawn,            SHCMD("redshift -x") },

	/* Screenshot */
	{ MODKEY,              Key_s,           spawn,            SHCMD("grim - | swappy -f -") },
	{ MODKEY|Shift,        Key_s,           spawn,            SHCMD("grim -g \"$(slurp)\" - | swappy -f -") },

	/* Music Players */
	{ MODKEY,              Key_p,           spawn,            SHCMD("spotify") },

	/* Messengers */
	{ MODKEY,              Key_d,           spawn,            SHCMD("discord") },

	/* Mail client */
	{ MODKEY,              Key_t,           spawn,            SHCMD("thunderbird") },

	/* Miscellaneous */
	{ MODKEY,              Key_z,           spawn,            SHCMD("zoom") },


	/* ----------------- Hardware ------------------ */

	/* Shutdown computer */
	{ ALTKEY|Control,      Key_Delete,      spawn,            SHCMD("loginctl poweroff || systemctl poweroff") },

	/* Restart computer */
	{ ALTKEY|Control,      Key_Insert,      spawn,            SHCMD("loginctl reboot || systemctl reboot") },

	/* Hibernate computer */
	{ MODKEY|Control,      Key_Delete,      spawn,            SHCMD("loginctl hibernate || systemctl hibernate") },

	/* Suspend computer */
	{ MODKEY|Control,      Key_Insert,      spawn,            SHCMD("loginctl suspend || systemctl suspend") },

	/* Volume */
	{ MODKEY,              Key_minus,       spawn,            SHCMD("amixer set Master 2%-")},
	{ MODKEY,              Key_equal,       spawn,            SHCMD("amixer set Master 2%+")},
	{ MODKEY,              Key_BackSpace,   spawn,            SHCMD("amixer set Master toggle")},


	/* --------------------- MPD ------------------- */

	/* Clients */
	{ MODKEY,              Key_n,           spawn,            SHCMD("foot ncmpcpp") },
	{ MODKEY|Shift,        Key_n,           spawn,            SHCMD("cantata") },

	/* Previus or next song */
	{ MODKEY|ALTKEY,       Key_F1,          mpdchange,        {.i = -1} },
	{ MODKEY|ALTKEY,       Key_F3,          mpdchange,        {.i = +1} },

	/* Play or pause */
	{ MODKEY|ALTKEY,       Key_F2,          mpdcontrol,       {0} },

	/* Volume */
	{MODKEY|ALTKEY,        Key_minus,       mpd_volume,       {.i = -2 } },
	{MODKEY|ALTKEY,        Key_equal,       mpd_volume,       {.i = +2 } },


	/* ------------ Other music players ------------ */

	/* Previus or next song */
	{ MODKEY,              Key_F1,          spawn,            SHCMD("playerctl --ignore-player=spotify previous") },
	{ ALTKEY,              Key_F3,          spawn,            SHCMD("playerctl --ignore-player=spotify next") },
 
	{ MODKEY,              Key_F1,          spawn,            SHCMD("playerctl --player=spotify previous") },
	{ ALTKEY,              Key_F3,          spawn,            SHCMD("playerctl --player=spotify next") },

	/* Play or pause */
	{ MODKEY,              Key_F2,          spawn,            SHCMD("playerctl --ignore-player=spotify play-pause") },
	{ ALTKEY,              Key_F2,          spawn,            SHCMD("playerctl --player spotify play-pause") },

	/* Volume (all except mpd and spotify) */
	{ MODKEY|Shift,        Key_minus,       spawn,            SHCMD("playerctl --ignore-player spotify,mpd volume 0.02-") },
	{ MODKEY|Shift,        Key_equal,       spawn,            SHCMD("playerctl --ignore-player spotify,mpd volume 0.02+") },

	/* Volume (only for spotify) */
	{ ALTKEY,              Key_minus,       spawn,            SHCMD("vol_spotify -2%") },
	{ ALTKEY,              Key_equal,       spawn,            SHCMD("vol_spotify +2%") },
	{ ALTKEY,              Key_BackSpace,   spawn,            SHCMD("vol_spotify toggle-mute")},


	/* ------------------- TTY's ------------------- */
	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,Key_BackSpace, quit, {0} },
#define CHVT(KEY,n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT, KEY, chvt, {.ui = (n)} }
	CHVT(Key_F1, 1), CHVT(Key_F2,  2),  CHVT(Key_F3,  3),  CHVT(Key_F4,  4),
	CHVT(Key_F5, 5), CHVT(Key_F6,  6),  CHVT(Key_F7,  7),  CHVT(Key_F8,  8),
	CHVT(Key_F9, 9), CHVT(Key_F10, 10), CHVT(Key_F11, 11), CHVT(Key_F12, 12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
