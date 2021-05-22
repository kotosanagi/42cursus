#!/bin/sh

/telegraf-1.16.2/usr/bin/telegraf --config /telegraf-1.16.2/etc/telegraf/telegraf.conf &

rc-status
rc-service php-fpm7 start

wp core install \
	--url=https://192.168.49.42:5050 \
	--title=KOTOblog \
	--admin_user=KOTO \
	--admin_password=KOTO \
	--admin_email=KOTO@example.com \
	--path=/var/www/html/wordpress

result=$?

if [ $result != 0 ]; then
	exit $result
fi

wp user create skotoyor skotoyor@example.com \
--user_pass=pw \
--role=author \
--first_name=shota \
--last_name=kotoyori \
--path=/var/www/html/wordpress

wp user create moco moco@example.com \
--user_pass=pw \
--role=subscriber \
--first_name=moco \
--last_name=kotoyori \
--path=/var/www/html/wordpress

nginx -g "daemon off;"
