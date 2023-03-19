/******************************************************************
 * Copyright 2023 Leonardo Hernández Hernández
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 ******************************************************************/

/* cc -lxkbcommon -o generate-keys generate-keys.c */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <xkbcommon/xkbcommon.h>

int
main(void)
{
	struct xkb_context *context;
	/* Allow generate keys with a different layout and variant.
	 * You can also use XKB_DEFAULT_* environmental variables and let this as is */
	struct xkb_rule_names rules = {
		0
	};
	struct xkb_keymap *keymap;
	struct xkb_state *state;
	xkb_keycode_t keycode, min_keycode, max_keycode;
	int i, nsyms;
	const xkb_keysym_t *syms;
	char keyname[64];
	FILE *f = fopen("keys.h", "w");
	if (!f) {
		perror("Couldn't open keys.h");
		return EXIT_FAILURE;
	}

	if (!(context = xkb_context_new(XKB_CONTEXT_NO_FLAGS))) {
		fputs("Couldn't create xkbcommon context\n", stderr);
		return EXIT_FAILURE;
	}

	if (!(keymap = xkb_keymap_new_from_names(context, &rules,
			XKB_KEYMAP_COMPILE_NO_FLAGS))) {
		fputs("Couldn't create xkbcommon keymap\n", stderr);
		return EXIT_FAILURE;
	}

	if (!(state = xkb_state_new(keymap))) {
		fputs("Couldn't create xkbcommon state\n", stderr);
		return EXIT_FAILURE;
	}

	min_keycode = xkb_keymap_min_keycode(keymap);
	max_keycode = xkb_keymap_max_keycode(keymap);

	for (keycode = min_keycode; keycode <= max_keycode; keycode++) {
		nsyms = xkb_state_key_get_syms(state, keycode, &syms);
		for (i = 0; i < nsyms; i++) {
			xkb_keysym_get_name(syms[i], keyname, sizeof(keyname) / sizeof(keyname[0]));
			fprintf(f, "#define Key_%-24s %d\n", keyname, keycode);
		}
	}

	xkb_state_unref(state);
	xkb_keymap_unref(keymap);
	xkb_context_unref(context);
}
