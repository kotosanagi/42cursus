
rc-status
rc-service php-fpm7 start


wp core install \
	--url=https://192.168.49.2:5050 \
	--title=test --admin_user=user \
	--admin_password=pass \
	--admin_email=admin@example.com \
	--path=/var/www/html/wordpress




nginx -g "daemon off;"

# nginx
# sleep infinity
