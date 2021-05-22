#!/bin/sh

/telegraf-1.16.2/usr/bin/telegraf --config /telegraf-1.16.2/etc/telegraf/telegraf.conf &

/usr/bin/mysql_install_db --datadir=/var/lib/mysql

/usr/bin/mysqld --user=root --init_file=/init_mysql &

tail -f /dev/null
