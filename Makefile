export DESTDIR ?=
export PREFIX ?= /usr/local
export CROSS_COMPILE =

export INCDIR ?= $(PREFIX)/include/audio_route
export LIBDIR ?= $(PREFIX)/lib
export BINDIR ?= $(PREFIX)/bin
export MANDIR ?= $(PREFIX)/share/man

CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
LD = $(CROSS_COMPILE)gcc

LIBS=-laudioroute -ltinyalsa -lexpat

WARNINGS = -Wall -Wextra -Werror -Wfatal-errors
override CFLAGS := $(WARNINGS) $(INCLUDE_DIRS) -fPIC $(CFLAGS)


OBJECTS = main.o

.PHONY: all
audiorouteconfig: $(OBJECTS)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f audiorouteconfig
	rm -f $(OBJECTS)

.PHONY: install
install:
	install -d $(DESTDIR)$(BINDIR)/
	install audiorouteconfig  $(DESTDIR)$(BINDIR)/
