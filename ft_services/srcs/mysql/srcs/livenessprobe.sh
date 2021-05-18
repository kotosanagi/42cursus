#!/bin/sh

pgrep /telegraf-1.16.2/usr/bin/telegraf
RET_TELEGRAF=$?

pgrep /usr/bin/mysqld
RET_MYSQLD=$?

if [ $RET_TELEGRAF == 1 -o $RET_MYSQLD == 1 ]; then
    exit 1
else
    exit 0
fi