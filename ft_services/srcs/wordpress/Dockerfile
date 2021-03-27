FROM alpine:3.6

RUN	set -ex; \
		apk update && apk add curl;
		# php7 php7-fpm ... and more
		

RUN	set -ex; \
		mkdir -p /var/www/html/wordpress; \
		curl -L -O https://ja.wordpress.org/latest-ja.tar.gz; \
		tar -xvf latest-ja.tar.gz -C /var/www/html/; \
		rm latest-ja.tar.gz ;

# CMD	tail -f /dev/null



# ========================
# docker build . -t hoge &&  docker run -ti --name fuga hoge ash


# docker container stop fuga && docker rm fuga





# IT MUST BE MODIFIED ABOUT wp-config.php