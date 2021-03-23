include config.mk

CFLAGS += -I. -DWLR_USE_UNSTABLE -std=c99

WAYLAND_PROTOCOLS=$(shell pkg-config --variable=pkgdatadir wayland-protocols)
WAYLAND_SCANNER=$(shell pkg-config --variable=wayland_scanner wayland-scanner)

PKGS = wlroots wayland-server xcb xkbcommon libinput
CFLAGS += $(foreach p,$(PKGS),$(shell pkg-config --cflags $(p)))
LDLIBS += $(foreach p,$(PKGS),$(shell pkg-config --libs $(p)))

all: dwl

# wayland-scanner is a tool which generates C headers and rigging for Wayland
# protocols, which are specified in XML. wlroots requires you to rig these up
# to your build system yourself and provide them in the include path.
xdg-shell-protocol.h:
	$(WAYLAND_SCANNER) server-header \
		$(WAYLAND_PROTOCOLS)/stable/xdg-shell/xdg-shell.xml $@

xdg-shell-protocol.c:
	$(WAYLAND_SCANNER) private-code \
		$(WAYLAND_PROTOCOLS)/stable/xdg-shell/xdg-shell.xml $@

xdg-shell-protocol.o: xdg-shell-protocol.h

wlr-layer-shell-unstable-v1-protocol.h:
	$(WAYLAND_SCANNER) server-header \
		protocols/wlr-layer-shell-unstable-v1.xml $@

wlr-layer-shell-unstable-v1-protocol.c:
	$(WAYLAND_SCANNER) private-code \
		protocols/wlr-layer-shell-unstable-v1.xml $@

wlr-layer-shell-unstable-v1-protocol.o: wlr-layer-shell-unstable-v1-protocol.h

idle-protocol.h:
	$(WAYLAND_SCANNER) server-header \
		protocols/idle.xml $@

idle-protocol.c:
	$(WAYLAND_SCANNER) private-code \
		protocols/idle.xml $@

idle-protocol.o: idle-protocol.h

config.h: | config.def.h
	cp config.def.h $@

dwl.o: config.h client.h xdg-shell-protocol.h wlr-layer-shell-unstable-v1-protocol.h idle-protocol.h

dwl: xdg-shell-protocol.o wlr-layer-shell-unstable-v1-protocol.o idle-protocol.o

clean:
	rm -f dwl *.o *-protocol.h *-protocol.c dwl-$(VERSION).tar.gz

install: dwl
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f dwl $(DESTDIR)$(PREFIX)/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwl

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/dwl

dist: clean
	mkdir -p dwl-$(VERSION)
	cp -R LICENSE LICENSE.dwm LICENSE.tinywl README.md config.def.h \
		config.mk dwl.c client.h Makefile applied_patches.txt protocols \
		dwl-$(VERSION)
	tar -cf dwl-$(VERSION).tar dwl-$(VERSION)
	gzip dwl-$(VERSION).tar
	rm -rf dwl-$(VERSION)

.DEFAULT_GOAL=dwl
.PHONY: clean
