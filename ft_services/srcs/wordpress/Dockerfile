FROM alpine:3.12

COPY ./srcs/setup.sh /
COPY ./srcs/nginx.conf /etc/nginx/nginx.conf
COPY ./srcs/livenessprobe.sh /livenessprobe.sh

RUN	set -ex; \
		apk update && apk add \
		curl \
		nginx \
		openssl \
		openrc \
		mysql \
		mysql-client \
		libc6-compat \
		php \
		php7-apcu \
		php7-bcmath \
		php7-bz2 \
		php7-ctype \
		php7-curl \
		php7-dom \
		php7-fpm \
		php7-gmp \
		php7-gd \
		php7-gettext \
		php7-iconv \
		php7-json \
		php7-mcrypt \
		php7-mysqli \
		php7-odbc \
		php7-openssl \
		php7-pdo \
		php7-pdo_dblib \
		php7-pdo_mysql \
		php7-pdo_odbc \
		php7-pdo_pgsql \
		php7-pdo_sqlite \
		php7-phar \
		php7-soap \
		php7-sqlite3 \
		php7-xmlreader \
		php7-xmlrpc \
		php7-zip \
		php7-phar \
		fcgi ;

RUN sed -i'.bak' 's/^#rc_sys=""/rc_sys="lxc"/' /etc/rc.conf \
    && sed -i 's/^#rc_provide="!net"/rc_provide="loopback net"/' /etc/rc.conf \
    && sed -i'.bak' '/getty/d' /etc/inittab \
    && sed -i'.bak' 's/mount -t tmpfs/# mount -t tmpfs/' /lib/rc/sh/init.sh \
    && sed -i'.bak' 's/hostname $opts/# hostname $opts/' /etc/init.d/hostname \
    && sed -i'.bak' 's/cgroup_add_service$/# cgroup_add_service/' /lib/rc/sh/openrc-run.sh \
    && mkdir /run/openrc \
    && touch /run/openrc/softlevel

# ssl
RUN mkdir -p etc/wordpress/ssl; \
	openssl genrsa 4048 > etc/wordpress/ssl/wordpress.key; \
	openssl req -new -subj "/C=JP/ST=Tokyo/L=Minato/O=42Tokyo/OU=42cursus/CN=localhost" -key etc/wordpress/ssl/wordpress.key > etc/wordpress/ssl/wordpress.csr; \
	openssl x509 -req -days 365 -signkey etc/wordpress/ssl/wordpress.key -in etc/wordpress/ssl/wordpress.csr > etc/wordpress/ssl/wordpress.crt;

RUN mkdir -p /run/nginx

# install wordpress
RUN	mkdir -p /var/www/html/wordpress; \
	curl -L -O https://wordpress.org/wordpress-5.7.1.tar.gz; \
	tar -xvf wordpress-5.7.1.tar.gz -C /var/www/html/; \
	rm wordpress-5.7.1.tar.gz ;
COPY ./srcs/wp-config.php /var/www/html/wordpress/wp-config.php
RUN chmod -R 775 /var/www/html/wordpress/*

# add user
RUN adduser -D -g www www \
	&& chown -R www:www /var/lib/nginx \
	&& chown -R www:www /var/www/html/wordpress

# copy www.conf
COPY srcs/www.conf /etc/php7/php-fpm.d/
RUN chmod 775 /etc/php7/php-fpm.d/www.conf

# get wp-cli
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
	&& chmod 775 wp-cli.phar \
	&& mv wp-cli.phar /usr/local/bin/wp

# telegraf
RUN wget https://dl.influxdata.com/telegraf/releases/telegraf-1.16.2_linux_amd64.tar.gz
RUN tar -xvf telegraf-1.16.2_linux_amd64.tar.gz
RUN sed -i -e 's/hostname = ""/hostname = "wordpress"/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN sed -i -e 's/# urls = \["http:\/\/127.0.0.1:8086"\]/urls = \["http:\/\/influxdb-service:8086"\]/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN sed -i -e 's/# database = "telegraf"/database = "wordpress"/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN rm telegraf-1.16.2_linux_amd64.tar.gz


EXPOSE 5050

ENTRYPOINT [ "sh", "/setup.sh" ]
