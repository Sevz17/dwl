/* appearance */
static const int sloppyfocus        = 1;  /* focus follows mouse */
static const int lockfullscreen     = 1;  /* 1 will force focus on the fullscreen window */
static const unsigned int borderpx  = 2;  /* border pixel of windows */
static const unsigned int gappih    = 6;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 6;       /* vert inner gap between windows */
static const unsigned int gappoh    = 6;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 6;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int smartborders       = 0;        /* 1 means no borders when there is only one window */
static const int monoclegaps        = 1;        /* 1 means outer gaps in monocle layout */
static const int numlock            = 1;
static const int capslock           = 0;
static const float rootcolor[]      = {0.3, 0.3, 0.3, 1.0};
static const float focuscolor[]     = {0.37, 0.0, 1.0, 1.0};
static const float bordercolor[]    = {0.0, 0.0, 0.0, 0.7};
/* To conform the xdg-protocol, set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]  = {0.1, 0.1, 0.1, 0.0};
static const char *cursortheme      = "breeze_cursors"; /* theme from ${XCURSOR_PATH} or /usr/share/cursors/xorg-x11 if emtpy*/
static const char cursorsize[]      = "24";

static const char *const autostart[] = {
	/* from https://github.com/swaywm/sway/wiki/GTK-3-settings-on-Wayland */
	"import-gsettings", NULL,

	/* https://sr.ht/~kennylevinsen/wlsunset/ */
	"sh", "-c", "wlsunset $(tr '\\n' ' ' < ~/.config/wlsunset/wlsunset.conf)", NULL,

	"fnott", NULL,          /* https://codeberg.org/dnkl/fnott */

	"swayidle", "-w", NULL,

	"foot", "--log-level=none", "--server", NULL,

	/* chbg is a script that print a random image. */
	"sh", "-c", "wbg $(chbg --print)", NULL, /* https://codeberg.org/dnkl/wbg */

	"yambar", NULL,
	"sh", "-c", "yambar -c ~/.config/yambar/config-bottom.yml", NULL,

	"sh", "-c", "pidof wireplumber 2>&1 > /dev/null || gentoo-pipewire-launcher 2>/dev/null", NULL,

	"sh", "-c", "pidof emacs 2>&1 > /dev/null || emacs --fg-daemon", NULL,

	NULL /* terminate */
};

/* tagging */
static const char *tags[] = {
	"爵 ", " ", " ", " ", " ", " ", " ", " ", " ", " "
};

static const Rule rules[] = {
	/* app_id      title       tags mask  isfloating  monitor */
	/* examples:
	*/
	{ "tag1",      NULL,       1 << 0,    0,          -1 },
	{ "tag2",      NULL,       1 << 1,    0,          -1 },
	{ "tag3",      NULL,       1 << 2,    0,          -1 },
	{ "tag4",      NULL,       1 << 3,    0,          -1 },
	{ "tag5",      NULL,       1 << 4,    0,          -1 },
	{ "tag6",      NULL,       1 << 5,    0,          -1 },
	{ "tag7",      NULL,       1 << 6,    0,          -1 },
	{ "tag8",      NULL,       1 << 7,    0,          -1 },
	{ "tag9",      NULL,       1 << 8,    0,          -1 },
	{ "tag0",      NULL,       1 << 9,    0,          -1 },

	{ "firefox",   NULL,       1 << 0,    0,          -1 },
	{ "chromium",  NULL,       1 << 0,    0,          -1 },
	{ "Emacs",     NULL,       1 << 1,    0,          -1 },
	{ "emacs",     NULL,       1 << 1,    0,          -1 },
	{ "Alacritty", NULL,       1 << 2,    0,          -1 },
	{ "foot",      NULL,       1 << 2,    0,          -1 },
	{ "office",    NULL,       1 << 4,    0,          -1 },
	{ "zathura",   NULL,       1 << 4,    0,          -1 },
	{ "imv",       NULL,       1 << 5,    0,          -1 },
	{ "zoom",      NULL,       1 << 6,    0,          -1 },
	{ "mpv",       NULL,       1 << 6,    0,          -1 },
	{ "telegram",  NULL,       1 << 8,    0,          -1 },
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
	/* name       mfact nmaster scale layout       rotate/reflect              x  y  resx resy rate     adaptive custom*/
	/* example of a HiDPI laptop monitor at 120Hz:
	{ "eDP-1",    0.5,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 0, 0, 0,   0,   120.000, 1,       0 },
	*/
	/* defaults */
	{ NULL,       0.5,  1,      1,    &layouts[2], WL_OUTPUT_TRANSFORM_NORMAL, 0, 0, 0,   0,   40.005,  0,       0 },
};


/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	0
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT;
static const double accel_speed = 0.0;

#define MODKEY  WLR_MODIFIER_LOGO
#define ALTKEY  WLR_MODIFIER_ALT
#define Control WLR_MODIFIER_CTRL
#define Shift   WLR_MODIFIER_SHIFT

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,               KEY, view,       {.ui = 1 << TAG} }, \
	{ MODKEY|Control,       KEY, toggleview, {.ui = 1 << TAG} }, \
	{ MODKEY|Shift,         KEY, tag,        {.ui = 1 << TAG} }, \
	{ MODKEY|Control|Shift, KEY, toggletag,  {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* helper for run programs */
#define RUN(...)   { .v = (const char*[]){ __VA_ARGS__, NULL } }

#include "keys.h"
#define DEFAULT_STEP "2"

/* You'll probably wanna change some of these */
static const Key keys[] = {

	/* ------------------ Windows ------------------ */

	/* Switch between windows */
	{ MODKEY,              Key_j,           focusstack,       {.i = +1} },
	{ MODKEY,              Key_k,           focusstack,       {.i = -1} },

	/* Move windows */
	{ MODKEY|Control,      Key_j,           pushdown,         {0} },
	{ MODKEY|Control,      Key_k,           pushup,           {0} },

	/* Change window sizes */
	{ MODKEY,              Key_i,           incnmaster,       {.i = +1} },
	{ MODKEY|Shift,        Key_i,           incnmaster,       {.i = -1} },
	{ MODKEY,              Key_h,           setmfact,         {.f = -0.05} },
	{ MODKEY,              Key_l,           setmfact,         {.f = +0.05} },

	/* Toggle floating */
	{ MODKEY|Control,      Key_f,           togglefloating,   {0} },

	/* Toggle fullscreen */
	{ MODKEY|Shift,        Key_f,           togglefullscreen, {0} },

	/* Toggle bars */
	/* SIGUSR1 toggle somebar */
	{ MODKEY|Control,      Key_b,           spawn,            RUN("pkill", "runbars", "-USR1") },
	/* SIGUSR2 toggle dtao */
	{ MODKEY|ALTKEY,       Key_b,           spawn,            RUN("pkill", "runbars", "-USR2") },

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
	{ MODKEY|Control,      Key_q,           quit,             {0} },


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

	{ MODKEY,              Key_m,           spawn,            RUN("fuzzel_run") },
	{ MODKEY|Shift,        Key_m,           spawn,            RUN("fuzzel") },
	{ MODKEY,              Key_d,           spawn,            RUN("fnott-select-n-run", "dismiss") },
	{ MODKEY|Shift,        Key_d,           spawn,            RUN("fnottctl", "dismiss") },
	{ MODKEY|Control,      Key_d,           spawn,            RUN("fnottctl", "dismiss" "all") },
	{ MODKEY,              Key_a,           spawn,            RUN("fnott-select-n-run", "actions") },
	{ MODKEY|Shift,        Key_a,           spawn,            RUN("fnottctl", "actions") },

	/* Terminal emulators */
	{ MODKEY,              Key_Return,      spawn,            RUN("footclient") },
	{ MODKEY|Shift,        Key_Return,      spawn,            SHCMD("alacritty msg create-window || alacritty") },

	/* Browsers */
	{ MODKEY,              Key_b,           spawn,            RUN("chromium") },
	{ MODKEY|Shift,        Key_b,           spawn,            RUN("firefox") },

	{ MODKEY,              Key_e,           spawn,            RUN("emacsclient", "-c", "-a", "") },

	/* Screenshot */
	{ MODKEY,              Key_s,           spawn,            SHCMD("grim - | swappy -f -") },
	{ MODKEY|Shift,        Key_s,           spawn,            SHCMD("grim -g \"$(slurp)\" - | swappy -f -") },

	/* Music Players */
	{ MODKEY,              Key_p,           spawn,            RUN("spotify") },

	/* Mail client */
	{ MODKEY,              Key_n,           spawn,            RUN("footclient", "-a", "tag9", "startneomutt") },
	{ MODKEY|Shift,        Key_n,           spawn,            RUN("footclient", "-a", "tag9", "startweechat") },


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
	{ 0,         Key_XF86AudioLowerVolume,  spawn,            RUN("pactl", "set-sink-volume", "@DEFAULT_SINK@", "-"DEFAULT_STEP"%")},
	{ 0,         Key_XF86AudioRaiseVolume,  spawn,            RUN("pactl", "set-sink-volume", "@DEFAULT_SINK@", "+"DEFAULT_STEP"%")},
	{ 0,         Key_XF86AudioMute,         spawn,            RUN("pactl", "set-sink-mute",   "@DEFAULT_SINK@", "toggle")},

	{ 0,         Key_XF86MonBrightnessDown, spawn,            RUN("brightnessctl", "set", DEFAULT_STEP"%-") },
	{ 0,         Key_XF86MonBrightnessUp,   spawn,            RUN("brightnessctl", "set", "+"DEFAULT_STEP"%") },

	/* ------------ Control music players ------------ */

	/* Previus or next song */
	{ 0,                 Key_XF86AudioPrev, spawn,            RUN("playerctl", "-i", "spotify", "previous") },
	{ 0,                 Key_XF86AudioNext, spawn,            RUN("playerctl", "-i", "spotify", "next") },

	{ MODKEY,            Key_XF86AudioPrev, spawn,            RUN("playerctl", "-p", "spotify", "previous") },
	{ MODKEY,            Key_XF86AudioNext, spawn,            RUN("playerctl", "-p", "spotify", "next") },

	/* Play or pause */
	{ 0,                 Key_XF86AudioPlay, spawn,            RUN("playerctl", "-i", "spotify", "play-pause") },
	{ MODKEY,            Key_XF86AudioPlay, spawn,            RUN("playerctl", "-p", "spotify", "play-pause") },

	/* Volume (all except spotify) */
	{ MODKEY,     Key_XF86AudioLowerVolume, spawn,            RUN("playerctl", "-i", "spotify", "volume", "0.0"DEFAULT_STEP"-") },
	{ MODKEY,     Key_XF86AudioRaiseVolume, spawn,            RUN("playerctl", "-i", "spotify", "volume", "0.0"DEFAULT_STEP"+") },

	/* Volume (only for spotify) */
	{ ALTKEY,     Key_XF86AudioLowerVolume, spawn,            RUN("vol_spotify", "-"DEFAULT_STEP"%") },
	{ ALTKEY,     Key_XF86AudioLowerVolume, spawn,            RUN("vol_spotify", "+"DEFAULT_STEP"%") },
	{ ALTKEY,     Key_XF86AudioMute,        spawn,            RUN("vol_spotify", "toggle-mute")},


	/* ------------------- TTY's ------------------- */
	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ Control|ALTKEY,      Key_BackSpace,   quit,             {0} },
#define CHVT(KEY,n) { Control|ALTKEY, KEY, chvt, {.ui = (n)} }
	CHVT(Key_F1, 1), CHVT(Key_F2,  2),  CHVT(Key_F3,  3),  CHVT(Key_F4,  4),
	CHVT(Key_F5, 5), CHVT(Key_F6,  6),  CHVT(Key_F7,  7),  CHVT(Key_F8,  8),
	CHVT(Key_F9, 9), CHVT(Key_F10, 10), CHVT(Key_F11, 11), CHVT(Key_F12, 12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
