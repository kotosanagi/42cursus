FROM alpine:3.6

COPY ./srcs/config.inc.php /var/www/html/phpmyadmin/config.inc.php

RUN apk update && apk add --no-cache curl;

RUN set -ex; \
		curl -L -O https://files.phpmyadmin.net/phpMyAdmin/5.0.4/phpMyAdmin-5.0.4-all-languages.tar.gz; \
		tar -xvf phpMyAdmin-5.0.4-all-languages.tar.gz -C var/www/html/phpmyadmin/ --strip-components=1; \
		rm phpMyAdmin-5.0.4-all-languages.tar.gz;


# ========================
# docker build . -t hoge &&  docker run -ti --name fuga hoge ash

# docker container stop fuga && docker rm fuga