FROM alpine:3.6

COPY ./srcs/setup.sh /
COPY ./srcs/nginx.conf /etc/nginx/nginx.conf

RUN	set -ex; \
		apk update && apk add --no-cache curl nginx openssl php7-common php7-session php7-iconv php7-json php7-gd php7-curl php7-xml php7-mysqli php7-imap php7-cgi fcgi php7-pdo php7-pdo_mysql php7-soap php7-xmlrpc php7-posix php7-mcrypt php7-gettext php7-ldap php7-ctype php7-dom php7 php7-fpm openrc;

##########
RUN sed -i'.bak' 's/^#rc_sys=""/rc_sys="lxc"/' /etc/rc.conf \
    && sed -i 's/^#rc_provide="!net"/rc_provide="loopback net"/' /etc/rc.conf \
    && sed -i'.bak' '/getty/d' /etc/inittab \
    && sed -i'.bak' 's/mount -t tmpfs/# mount -t tmpfs/' /lib/rc/sh/init.sh \
    && sed -i'.bak' 's/hostname $opts/# hostname $opts/' /etc/init.d/hostname \
    && sed -i'.bak' 's/cgroup_add_service$/# cgroup_add_service/' /lib/rc/sh/openrc-run.sh \
    && mkdir /run/openrc \
    && touch /run/openrc/softlevel \
    && sed -i'.bak' 's/return 404;/root html;\n\t\tindex index.html;/' /etc/nginx/conf.d/default.conf
##########

RUN mkdir -p /run/nginx
RUN mkdir -p var/www/html/phpmyadmin

RUN set -ex; \
		curl -L -O https://files.phpmyadmin.net/phpMyAdmin/5.0.4/phpMyAdmin-5.0.4-all-languages.tar.gz; \
		tar -xvf phpMyAdmin-5.0.4-all-languages.tar.gz -C var/www/html/phpmyadmin/ --strip-components=1; \
		rm phpMyAdmin-5.0.4-all-languages.tar.gz;
COPY ./srcs/config.inc.php /var/www/html/phpmyadmin/config.inc.php
RUN chmod -R 775 /var/www/html/phpmyadmin/*

# ssl
RUN set -ex; \
		mkdir -p etc/phpmyadmin/ssl; \
		openssl genrsa 4048 > etc/phpmyadmin/ssl/phpmyadmin.key; \
		openssl req -new -subj "/C=JP/ST=Tokyo/L=Minato/O=42Tokyo/OU=42cursus/CN=localhost" -key etc/phpmyadmin/ssl/phpmyadmin.key > etc/phpmyadmin/ssl/phpmyadmin.csr; \
		openssl x509 -req -days 365 -signkey etc/phpmyadmin/ssl/phpmyadmin.key -in etc/phpmyadmin/ssl/phpmyadmin.csr > etc/phpmyadmin/ssl/phpmyadmin.crt;

EXPOSE 5000

ENTRYPOINT [ "sh", "/setup.sh" ]

# ========================

# run and sh
# docker build . -t phpmyadmin_images_koto && docker run -d -p 5050:5050 --name phpmyadmin_container_koto phpmyadmin_images_koto && docker exec -ti phpmyadmin_container_koto sh

# delete
# docker container stop phpmyadmin_container_koto && docker rm phpmyadmin_container_koto && docker rmi phpmyadmin_images_koto

# restart
# docker container stop phpmyadmin_container_koto && docker rm phpmyadmin_container_koto && docker build . -t phpmyadmin_images_koto && docker run -d -p 5050:5050 --name phpmyadmin_container_koto phpmyadmin_images_koto && docker exec -ti phpmyadmin_container_koto sh
