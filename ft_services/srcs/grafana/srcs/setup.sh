#!/bin/sh

/telegraf-1.16.2/usr/bin/telegraf --config /telegraf-1.16.2/etc/telegraf/telegraf.conf &

/grafana-7.5.5/bin/grafana-server --config /grafana-7.5.5/conf/grafana.ini --homepath /grafana-7.5.5/ &

tail -f /dev/null
