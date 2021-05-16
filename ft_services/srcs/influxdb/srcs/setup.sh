#!/bin/sh

/telegraf-1.16.2/usr/bin/telegraf --config /telegraf-1.16.2/etc/telegraf/telegraf.conf &

/usr/sbin/influxd &

tail -f /dev/null
