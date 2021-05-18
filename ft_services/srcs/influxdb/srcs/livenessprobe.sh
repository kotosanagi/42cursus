#!/bin/sh

pgrep /telegraf-1.16.2/usr/bin/telegraf
RET_TELEGRAF=$?

pgrep /usr/sbin/influxd
RET_INFLUXD=$?

if [ $RET_TELEGRAF == 1 -o $RET_INFLUXD == 1 ]; then
    exit 1
else
    exit 0
fi