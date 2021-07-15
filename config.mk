# dwl version
VERSION = 0.2

# paths
PREFIX = /usr/local

# Default compile flags (overridable by environment)
CFLAGS ?= -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-sign-compare -Wno-unused-function -Wno-unused-variable -Wdeclaration-after-statement -Wno-unused-result

# Uncomment to build XWayland support
CFLAGS += -DXWAYLAND

# Optimizations
CFLAGS += -march=native -O2
