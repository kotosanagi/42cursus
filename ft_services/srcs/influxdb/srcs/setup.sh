#!/bin/sh

/usr/sbin/influxd &

tail -f /dev/null
