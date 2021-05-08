FROM alpine:3.13
# FROM alpine:3.6

COPY	./srcs/nginx.conf /etc/nginx/nginx.conf
COPY	./srcs/setup.sh /

# setup nginx
RUN apk update; \
	apk add --no-cache nginx openssl libc6-compat;
RUN mkdir -p /run/nginx;
RUN mkdir -p /var/www/html;
COPY ./srcs/index.html /var/www/html/index.html
RUN chmod 755 -R /var/www/html/
# RUN echo "hello KOTO" > /var/www/html/index.html;

# ssl
RUN set -ex; \
		mkdir -p etc/nginx/ssl; \
		openssl genrsa 4048 > etc/nginx/ssl/nginx.key; \
		openssl req -new -subj "/C=JP/ST=Tokyo/L=Minato/O=42Tokyo/OU=42cursus/CN=localhost" -key etc/nginx/ssl/nginx.key > etc/nginx/ssl/nginx.csr; \
		openssl x509 -req -days 365 -signkey etc/nginx/ssl/nginx.key -in etc/nginx/ssl/nginx.csr > etc/nginx/ssl/nginx.crt;

EXPOSE 80
EXPOSE 443

##### struggling to telegraf #####

RUN wget https://dl.influxdata.com/telegraf/releases/telegraf-1.16.2_linux_amd64.tar.gz
RUN tar -xvf telegraf-1.16.2_linux_amd64.tar.gz
RUN sed -i -e 's/hostname = ""/hostname = "nginx"/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN sed -i -e 's/# urls = \["http:\/\/127.0.0.1:8086"\]/urls = \["http:\/\/influxdb-service:8086"\]/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf

##### struggling to telegraf #####


# CMD tail -f /dev/null
# CMD nginx -g "daemon off;"
CMD sh /setup.sh


# -------------------------------------
# -------------------------------------

# docker build . -t nginx_images_koto && docker run -d -p 8080:80 -p 443:443 --name nginx_container_koto nginx_images_koto

# docker exec -ti nginx_container_koto ash

# http://localhost:8080
# https://localhost:443

# docker container stop nginx_container_koto && docker rm nginx_container_koto && docker rmi nginx_images_koto


