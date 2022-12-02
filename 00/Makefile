CC?=gcc
SHELL=bash

APP_NAME=$(shell basename $(shell pwd))

INCL_DIRS=../common
SRCS = ${wildcard *.c }
OBJS = ${patsubst %.c,%.o,${SRCS}}

CFLAGS+=-O2 -Wall -Wextra
CFLAGS+=-I${INCL_DIRS} -D_FORTIFY_SOURCE=2
CFLAGS+=-Wformat -Wformat-security -Werror=format-security
CFLAGS+=-Wshadow

.PHONY: all clean tidy debug
all: clean ${APP_NAME}

debug: CFLAGS += -g -ggdb3 -O0 -U_FORTIFY_SOURCE
debug: all

${APP_NAME}: ${OBJS} ${ABS_COMMONOBJS}
	@echo -e "\033[0;93m[LD]\033[0m \t\033[0;1m$@\033[0m"
	@${CC} -o $@ $^ ${CFLAGS} ${LDFLAGS}

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)
	@echo -e "\033[0;33m[CC] \t\033[0m$<"

clean:
	@-${RM} ${OBJS} ${APP_NAME}
	@echo -e "\033[0;32m[RM] \t\033[0mClean temporary objects"
