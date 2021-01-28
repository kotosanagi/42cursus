# install OS
FROM debian:buster

# set metadata 
LABEL maintainer="KOTO <skotoyor@student.42tokyo.jp>"

# copy files
COPY ./srcs/wp-config.php /var/www/html/wordpress/wp-config.php
COPY ./srcs/config.inc.php /var/www/html/phpmyadmin/config.inc.php
COPY ./srcs/default.tmpl /etc/nginx/sites-available/default.tmpl
COPY ./srcs/supervisord.conf /etc/supervisor/conf.d/supervisord.conf

# install tools
RUN	set -ex; \
		apt-get update; \
		apt-get install -y --no-install-recommends \
		ca-certificates wget vim openssl nginx supervisor\
		mariadb-server mariadb-client \
		php-cgi php-common php-fpm php-pear php-mbstring php-zip php-net-socket php-gd php-xml-util php-gettext php-mysql php-bcmath; \
		rm -rf /var/lib/apt/lists/*;

# install database
ENV DB_NAME=dbname \
	DB_USER=user \
	DB_HOST=localhost \
	DB_PASS=pass
RUN set -ex; \
		service mysql start; \
		mysql -e "CREATE DATABASE $DB_NAME"; \
		mysql -e "GRANT ALL ON $DB_NAME.* TO '$DB_USER'@'$DB_HOST' IDENTIFIED BY '$DB_PASS';";

# install wordpress
ENV WP_PATH=/var/www/html/wordpress \
 	WP_TAR=wordpress.tar.gz \
 	WP_URL=https://ja.wordpress.org/latest-ja.tar.gz
RUN set -ex; \
		wget -O $WP_TAR $WP_URL; \
		tar -xvf $WP_TAR -C $WP_PATH --strip-components=1; \
		rm $WP_TAR;

# install phpMyAdmin
ENV PHPMA_PATH=/var/www/html/phpmyadmin \
 	PHPMA_TAR=phpMyAdmin.tar.gz \
 	PHPMA_URL=https://files.phpmyadmin.net/phpMyAdmin/5.0.4/phpMyAdmin-5.0.4-all-languages.tar.gz
RUN set -ex; \
		wget -O $PHPMA_TAR $PHPMA_URL; \
		tar -xvf $PHPMA_TAR -C $PHPMA_PATH --strip-components=1; \
		rm $PHPMA_TAR; 

# change owner
RUN chown -R www-data:www-data /var/www/html/*;

# setting SSl
ENV SSL_PATH=/etc/nginx/ssl \
	KEY=server.key \
	CSR=server.csr \
	CRT=server.crt
RUN set -ex; \
		mkdir -p $SSL_PATH; \
		openssl genrsa \
			-out "$SSL_PATH/$KEY" 2048; \
		openssl req -new \
			-subj "/C=JP/ST=Tokyo/L=Minato/O=42Tokyo/OU=42cursus/CN=localhost" \
			-key "$SSL_PATH/$KEY" \
			-out "$SSL_PATH/$CSR"; \
		openssl x509 -req \
			-days 3650 \
			-signkey "$SSL_PATH/$KEY" \
			-in "$SSL_PATH/$CSR" \
			-out "$SSL_PATH/$CRT";

# install entrykit
ENV E_KIT_URL=https://github.com/progrium/entrykit/releases/download/v0.4.0/entrykit_0.4.0_Linux_x86_64.tgz \
    E_KIT_TAR=entrykit.tgz \
    E_KIT_PATH=/bin
RUN set -ex; \
        wget -O $E_KIT_TAR $E_KIT_URL; \
        tar -xvf $E_KIT_TAR -C $E_KIT_PATH; \
        rm $E_KIT_TAR; \
        chmod +x $E_KIT_PATH/entrykit; \
        entrykit --symlink;

# chmod supervisord.conf
RUN	chmod +x /etc/supervisor/conf.d/supervisord.conf;

# exec entrypoint
ENTRYPOINT ["render", "/etc/nginx/sites-available/default", "--", "/usr/bin/supervisord"]

# expose
EXPOSE 80 443
