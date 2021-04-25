FROM alpine:3.6

COPY ./srcs/setup.sh /
COPY ./srcs/nginx.conf /etc/nginx/nginx.conf

RUN	set -ex; \
		apk update && apk add --no-cache curl nginx openssl php7-common php7-session php7-iconv php7-json php7-gd php7-curl php7-xml php7-mysqli php7-imap php7-cgi fcgi php7-pdo php7-pdo_mysql php7-soap php7-xmlrpc php7-posix php7-mcrypt php7-gettext php7-ldap php7-ctype php7-dom php7 php7-fpm openrc;


##########

# rc_sys="lxc"	// linux containers
# rc_provide=""	// 
# getty			// 

# mount -t tmpfs		// comment out
# host name				// comment out
# cgroup_add_service$	// comment out

# mkdir /run/openrc 
# touch /run/openrc/softlevel

# edit -> /etc/nginx/conf.d/default.conf


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

RUN	set -ex; \
		mkdir -p /var/www/html/wordpress; \
		curl -L -O https://ja.wordpress.org/latest-ja.tar.gz; \
		tar -xvf latest-ja.tar.gz -C /var/www/html/; \
		rm latest-ja.tar.gz ;
COPY ./srcs/wp-config.php /var/www/html/wordpress/wp-config.php
RUN chmod -R 775 /var/www/html/wordpress/*
# cat /var/log/nginx/error.log 

# ssl
RUN set -ex; \
		mkdir -p etc/wordpress/ssl; \
		openssl genrsa 4048 > etc/wordpress/ssl/wordpress.key; \
		openssl req -new -subj "/C=JP/ST=Tokyo/L=Minato/O=42Tokyo/OU=42cursus/CN=localhost" -key etc/wordpress/ssl/wordpress.key > etc/wordpress/ssl/wordpress.csr; \
		openssl x509 -req -days 365 -signkey etc/wordpress/ssl/wordpress.key -in etc/wordpress/ssl/wordpress.csr > etc/wordpress/ssl/wordpress.crt;

EXPOSE 5050

# CMD sh /setup.sh
ENTRYPOINT [ "sh", "/setup.sh" ]


# ========================

# run and sh
# docker build . -t wordpress_images_koto && docker run -ti -d -p 5050:5050 --name wordpress_container_koto wordpress_images_koto sh && docker exec -ti wordpress_container_koto sh

# delete
# docker container stop wordpress_container_koto && docker rm wordpress_container_koto && docker rmi wordpress_images_koto

# restart
# docker container stop wordpress_container_koto && docker rm wordpress_container_koto && docker build . -t wordpress_images_koto && docker run -ti -d -p 5050:5050 --name wordpress_container_koto wordpress_images_koto sh && docker exec -ti wordpress_container_koto sh


# !!!!!!IT MUST BE MODIFIED ABOUT wp-config.php!!!!!!
