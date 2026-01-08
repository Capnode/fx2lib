# Makefile for blink with USB support
# Uses fx2lib

FX2LIBDIR=../..
SOURCES=blink.c
DSCR_FILE=dscr.a51
A51_SOURCES=$(DSCR_FILE)
LIBS=../../lib/setupdat.rel ../../lib/delay.rel

CC=/mingw64/bin/sdcc
AS8051=/mingw64/bin/sdas8051

BASENAME=blink

include $(FX2LIBDIR)/lib/fx2.mk
