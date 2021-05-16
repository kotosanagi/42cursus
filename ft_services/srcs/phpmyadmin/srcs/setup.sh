/telegraf-1.16.2/usr/bin/telegraf --config /telegraf-1.16.2/etc/telegraf/telegraf.conf &

rc-status
rc-service php-fpm7 start

nginx -g "daemon off;"

# nginx
# sleep infinity
