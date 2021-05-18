#!/bin/sh

pgrep /telegraf-1.16.2/usr/bin/telegraf
RET_TELEGRAF=$?

pgrep nginx
RET_NGINX=$?

if [ $RET_TELEGRAF == 1 -o $RET_NGINX == 1 ]; then
    exit 1
else
    exit 0
fi