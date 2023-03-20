#!/bin/sh

zip sources_AA_YM.zip \
    include/consigne.h \
    include/define.h \
    include/regulation.h \
    include/visualisationC.h \
    include/visualisationT.h \
    src/consigne.c \
    src/regulation.c \
    src/visualisationC.c \
    src/visualisationT.c \
    test/test_sim.c \
    Makefile
