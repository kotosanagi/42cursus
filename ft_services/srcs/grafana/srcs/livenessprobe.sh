#!/bin/sh

pgrep /telegraf-1.16.2/usr/bin/telegraf
RET_TELEGRAF=$?

pgrep /grafana-7.5.5/bin/grafana-server
RET_GRAFANA=$?

if [ $RET_TELEGRAF == 1 -o $RET_GRAFANA == 1 ]; then
    exit 1
else
    exit 0
fi