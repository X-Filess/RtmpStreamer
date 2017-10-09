#!/bin/sh

gcc -static -g rtmpSend.c demuxEs.c -o rtmpTool  ../lib/librtmp/librtmp.a -lpthread
