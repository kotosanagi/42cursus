# FROM alpine:3.6
FROM alpine:3.12
# FROM alpine:3.13

COPY ./srcs/setup.sh /
COPY ./srcs/nginx.conf /etc/nginx/nginx.conf
COPY ./srcs/livenessprobe.sh /livenessprobe.sh

RUN	set -ex; \
		apk update && apk add --no-cache \
		curl \
		fcgi \
		openssl \
		nginx \
		openrc \
		libc6-compat \
		php7 \
		php7-cgi \
		php7-common \
		php7-ctype \
		php7-curl \
		php7-dom \
		php7-fpm \
		php7-gd \
		php7-gettext \
		php7-iconv \
		php7-imap \
		php7-json \
		php7-ldap \
		php7-mbstring \
		php7-mcrypt \
		php7-mysqli \
		php7-pdo \
		php7-pdo_mysql \
		php7-posix \
		php7-session \
		php7-soap \
		php7-xml \
		php7-xmlrpc;

#########
RUN sed -i'.bak' 's/^#rc_sys=""/rc_sys="lxc"/' /etc/rc.conf \
    && sed -i 's/^#rc_provide="!net"/rc_provide="loopback net"/' /etc/rc.conf \
    && sed -i'.bak' '/getty/d' /etc/inittab \
    && sed -i'.bak' 's/mount -t tmpfs/# mount -t tmpfs/' /lib/rc/sh/init.sh \
    && sed -i'.bak' 's/hostname $opts/# hostname $opts/' /etc/init.d/hostname \
    && sed -i'.bak' 's/cgroup_add_service$/# cgroup_add_service/' /lib/rc/sh/openrc-run.sh \
    && mkdir /run/openrc \
    && touch /run/openrc/softlevel
##########

RUN mkdir -p /run/nginx
RUN mkdir -p /var/www/html/phpmyadmin
RUN mkdir -p /var/www/html/phpmyadmin/tmp

# add user
RUN adduser -D -g www www \
	&& chown -R www:www /var/lib/nginx \
	&& chown -R www:www /var/www/html/phpmyadmin \
	&& chmod 777 /var/www/html/phpmyadmin

# install phpmyadmin
RUN set -ex; \
		curl -L -O https://files.phpmyadmin.net/phpMyAdmin/4.9.3/phpMyAdmin-4.9.3-all-languages.tar.gz; \
		tar -xvf phpMyAdmin-4.9.3-all-languages.tar.gz -C var/www/html/phpmyadmin/ --strip-components=1; \
		rm phpMyAdmin-4.9.3-all-languages.tar.gz;
COPY ./srcs/config.inc.php /var/www/html/phpmyadmin/config.inc.php
RUN chmod -R 775 /var/www/html/phpmyadmin/*
RUN chmod -R 777 /var/www/html/phpmyadmin/tmp
RUN chown -R www:www /var/www/html/phpmyadmin/


# ssl
RUN set -ex; \
		mkdir -p etc/phpmyadmin/ssl; \
		openssl genrsa 4048 > etc/phpmyadmin/ssl/phpmyadmin.key; \
		openssl req -new -subj "/C=JP/ST=Tokyo/L=Minato/O=42Tokyo/OU=42cursus/CN=localhost" -key etc/phpmyadmin/ssl/phpmyadmin.key > etc/phpmyadmin/ssl/phpmyadmin.csr; \
		openssl x509 -req -days 365 -signkey etc/phpmyadmin/ssl/phpmyadmin.key -in etc/phpmyadmin/ssl/phpmyadmin.csr > etc/phpmyadmin/ssl/phpmyadmin.crt;



# telegraf
RUN wget https://dl.influxdata.com/telegraf/releases/telegraf-1.16.2_linux_amd64.tar.gz
RUN tar -xvf telegraf-1.16.2_linux_amd64.tar.gz
RUN sed -i -e 's/hostname = ""/hostname = "phpmyadmin"/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN sed -i -e 's/# urls = \["http:\/\/127.0.0.1:8086"\]/urls = \["http:\/\/influxdb-service:8086"\]/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN sed -i -e 's/# database = "telegraf"/database = "phpmyadmin"/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN rm telegraf-1.16.2_linux_amd64.tar.gz

EXPOSE 5000

ENTRYPOINT [ "sh", "/setup.sh" ]
# CMD sh /setup.sh

# ========================

# run and sh
# docker build . -t phpmyadmin_images_koto && docker run -d -p 5050:5050 --name phpmyadmin_container_koto phpmyadmin_images_koto && docker exec -ti phpmyadmin_container_koto sh

# delete
# docker container stop phpmyadmin_container_koto && docker rm phpmyadmin_container_koto && docker rmi phpmyadmin_images_koto

# restart
# docker container stop phpmyadmin_container_koto && docker rm phpmyadmin_container_koto && docker build . -t phpmyadmin_images_koto && docker run -d -p 5050:5050 --name phpmyadmin_container_koto phpmyadmin_images_koto && docker exec -ti phpmyadmin_container_koto sh
