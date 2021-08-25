/* appearance */
static const int sloppyfocus        = 1;  /* focus follows mouse */
static const unsigned int borderpx  = 2;  /* border pixel of windows */
static const unsigned int gappx     = 6;  /* gaps between windows */
static const float rootcolor[]      = {0.3, 0.3, 0.3, 1.0};
static const float focuscolor[]     = {0.4, 0.0, 1.0, 1.0};
static const float bordercolor[]    = {0.0, 0.0, 0.0, 0.7};

#ifdef DEBUG
static const char *const autostart[] = { NULL };
#else
static const char *const autostart[] = {
	"swaylock", "--daemonize", "--image", "/usr/share/backgrounds/archlinux/wave.png", "--scaling", "fill", NULL,
	"sh", "-c", "swaybg --image $(chbg --print) --mode fill", NULL,
	"swayidle", "-w",
			"timeout", "600", "output-power -d", "resume", "output-power -e",
			"timeout", "900", "swaylock --daemonize --image $(chbg --print) --scaling fill",
			"timeout", "1200", "loginctl suspend-then-hibernate", NULL,
	"sh", "-c", "slstatus.bottom -s | dtao -z -z -ta l -b -L bottom -fn 'UbuntuMono Nerd Font:size=16:antialias=true:autohint:true'", NULL,
	"redshift", "-m", "wayland", NULL,
	NULL /* terminate */
};
#endif

/* tagging */
static const char *tags[] = { " ", "﬏ ", " ", " ", " ", " ", " ", " ", " ", " " };

static const Rule rules[] = {
	/* app_id      title       tags mask  isfloating  monitor */
	/* examples:
	{ "Gimp",      NULL,       0,         1,          -1 },
	{ "firefox",   NULL,       1 << 8,    0,          -1 },
	*/
	{ "firefox",   NULL,       1 << 0,    0,          -1 },
	{ "edge",      NULL,       1 << 0,    0,          -1 },
	{ "Alacritty", NULL,       1 << 2,    0,          -1 },
	{ "foot",      NULL,       1 << 2,    0,          -1 },
	{ "office",    NULL,       1 << 4,    0,          -1 },
	{ "zathura",   NULL,       1 << 4,    0,          -1 },
	{ "zoom",      NULL,       1 << 6,    1,          -1 },
	{ "Spotify",   NULL,       1 << 7,    0,          -1 },
	{ "discord",   NULL,       1 << 8,    0,          -1 },
	{"thunderbird",NULL,       1 << 8,    0,          -1 },
	{ "droidcam",  NULL,       1 << 9,    1,          -1 },
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

/* Trackpad */
static const int tap_to_click = 1;
static const int natural_scrolling = 0;

#ifdef DEBUG
#define MODKEY  WLR_MODIFIER_ALT
#define ALTKEY  WLR_MODIFIER_LOGO
#else
#define MODKEY  WLR_MODIFIER_LOGO
#define ALTKEY  WLR_MODIFIER_ALT
#endif

#define Control WLR_MODIFIER_CTRL
#define Shift   WLR_MODIFIER_SHIFT

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, KEY,            tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,KEY,toggletag,  {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* helper for run programs */
#define RUN(cmd, ...)   { .v = (const char*[]){ cmd, ##__VA_ARGS__, NULL } }

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
	{ MODKEY,              Key_Menu,        spawn,            RUN("wofi", "--show=run") },

	/* Terminal emulators */
	{ MODKEY,              Key_Return,      spawn,            {.v = termcmd} },
	{ MODKEY|Shift,        Key_Return,      spawn,            RUN("alacritty") },

	/* Browsers */
	{ MODKEY,              Key_b,           spawn,            RUN("microsoft-edge-dev") },
	{ MODKEY,              Key_f,           spawn,            RUN("firefox") },


	/* Redshift */
	{ MODKEY,              Key_r,           spawn,            RUN("redshift", "-O", "2400") },
	{ MODKEY|Shift,        Key_r,           spawn,            RUN("redshift", "-x") },

	/* Screenshot */
	{ MODKEY,              Key_s,           spawn,            SHCMD("grim - | swappy -f -") },
	{ MODKEY|Shift,        Key_s,           spawn,            SHCMD("grim -g \"$(slurp)\" - | swappy -f -") },

	/* Music Players */
	{ MODKEY,              Key_p,           spawn,            RUN("spotify") },

	/* Messengers */
	{ MODKEY,              Key_d,           spawn,            RUN("discord") },

	/* Mail client */
	{ MODKEY,              Key_t,           spawn,            RUN("thunderbird") },


	/* ----------------- Hardware ------------------ */

	/* Shutdown computer */
	{ ALTKEY|Control,      Key_Delete,      spawn,            RUN("loginctl", "poweroff") },

	/* Restart computer */
	{ ALTKEY|Control,      Key_Insert,      spawn,            RUN("loginctl", "reboot") },

	/* Hibernate computer */
	{ MODKEY|Control,      Key_Delete,      spawn,            RUN("loginctl", "hibernate") },

	/* Suspend computer */
	{ MODKEY|Control,      Key_Insert,      spawn,            RUN("loginctl", "suspend") },

	/* Volume */
	{ MODKEY,              Key_minus,       spawn,            RUN("amixer", "set", "Master", "2%-")},
	{ MODKEY,              Key_equal,       spawn,            RUN("amixer", "set", "Master", "2%+")},
	{ MODKEY,              Key_BackSpace,   spawn,            RUN("amixer", "set", "Master", "toggle")},


	/* ------------ Control music players ------------ */

	/* Previus or next song */
	{ MODKEY,              Key_F1,          spawn,            RUN("playerctl", "--ignore-player=spotify", "previous") },
	{ MODKEY,              Key_F3,          spawn,            RUN("playerctl", "--ignore-player=spotify", "next") },
 
	{ ALTKEY,              Key_F1,          spawn,            RUN("playerctl", "--player=spotify", "previous") },
	{ ALTKEY,              Key_F3,          spawn,            RUN("playerctl", "--player=spotify", "next") },

	/* Play or pause */
	{ MODKEY,              Key_F2,          spawn,            RUN("playerctl", "--ignore-player=spotify", "play-pause") },
	{ ALTKEY,              Key_F2,          spawn,            RUN("playerctl", "--player=spotify", "play-pause") },

	/* Volume (all except spotify) */
	{ MODKEY|Shift,        Key_minus,       spawn,            RUN("playerctl", "--ignore-player=spotify", "volume", "0.02-") },
	{ MODKEY|Shift,        Key_equal,       spawn,            RUN("playerctl", "--ignore-player=spotify", "volume", "0.02+") },

	/* Volume (only for spotify) */
	{ ALTKEY,              Key_minus,       spawn,            RUN("vol_spotify", "-2%") },
	{ ALTKEY,              Key_equal,       spawn,            RUN("vol_spotify", "+2%") },
	{ ALTKEY,              Key_BackSpace,   spawn,            RUN("vol_spotify", "toggle-mute")},


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
