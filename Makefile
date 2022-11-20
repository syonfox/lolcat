
CC ?= gcc
LOLCAT_SRC ?= src/lolcat.c
CENSOR_SRC ?= src/censor.c
COWSAY_SRC ?= src/cowsay.c
TEST_SRC ?= src/resize.c

CFLAGS ?= -std=c11 -Wall -Wextra -O3 -Wno-sign-compare
LIBS := -lm

DESTDIR ?= /usr/local/bin

all: lolcat censor cowsay

debug: CFLAGS += -g
debug: all

.PHONY: install clean debug

lolcat: $(LOLCAT_SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

censor: $(CENSOR_SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

cowsay: $(COWSAY_SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

test: $(TEST_SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

install: lolcat censor
	install lolcat $(DESTDIR)/lolcat
	install censor $(DESTDIR)/censor
	install cowsay $(DESTDIR)/cowsay
clean:
	rm -f lolcat censor cowsay resize 'test'
