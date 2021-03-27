FROM alpine:3.6

COPY	./srcs/nginx.conf /etc/nginx/nginx.conf

# setup nginx
RUN	set -ex; \
	apk update; \
	apk add --no-cache nginx vim openssl; \
	mkdir -p /run/nginx; \
	mkdir -p /var/www/html; \
	echo "hello KOTO" > /var/www/html/index.html;

# ssl
RUN set -ex; \
		mkdir -p etc/nginx/ssl; \
		openssl genrsa 4048 > etc/nginx/ssl/nginx.key; \
		openssl req -new -subj "/C=JP/ST=Tokyo/L=Minato/O=42Tokyo/OU=42cursus/CN=localhost" -key etc/nginx/ssl/nginx.key > etc/nginx/ssl/nginx.csr; \
		openssl x509 -req -days 365 -signkey etc/nginx/ssl/nginx.key -in etc/nginx/ssl/nginx.csr > etc/nginx/ssl/nginx.crt;



EXPOSE 80
EXPOSE 443

# CMD tail -f /dev/null
CMD nginx -g "daemon off;"



# docker build . -t hoge && docker run -d -p 8080:80 -p 443:443 --name fuga hoge

# docker exec -ti fuga ash

# http://localhost:8080
# https://localhost:443

# docker container stop fuga && docker rm fuga && docker rmi hoge




# -------------------------------------
# -------------------------------------
# apk add --nocache openssl
# mkdir -p etc/nginx/ssl
# openssl genrsa 4048 > etc/nginx/ssl/nginx.key
# openssl req -new -subj "/C=JP/ST=Tokyo/L=Minato/O=42Tokyo/OU=42cursus/CN=localhost" -key etc/nginx/ssl/nginx.key > etc/nginx/ssl/nginx.csr
# openssl x509 -req -days 365 -signkey etc/nginx/ssl/nginx.key -in etc/nginx/ssl/nginx.csr > etc/nginx/ssl/nginx.crt
