FROM alpine:3.6

RUN apk update; \
		apk add --no-cache mysql mysql-client

# RUN set -ex; \
# 		cd /var/lib/mysql; \
# 		mysql_install_db --bootstarp --user=mysql;

COPY ./srcs/setup.sh /var/lib/mysql
CMD sh /var/lib/mysql/setup.sh

# ========================

# run
# docker build . -t mysql_images_koto && docker run -d --name mysql_container_koto mysql_images_koto

# ash
# docker build . -t mysql_images_koto &&  docker run -ti --name mysql_container_koto mysql_images_koto ash

# remove
# docker container stop mysql_container_koto && docker rm mysql_container_koto && docker rmi mysql_images_koto

# restart ash
# docker container stop mysql_container_koto && docker rm mysql_container_koto && docker rmi mysql_images_koto && docker build . -t mysql_images_koto &&  docker run -ti --name mysql_container_koto mysql_images_koto ash

# restart run
# docker container stop mysql_container_koto && docker rm mysql_container_koto && docker rmi mysql_images_koto && docker build . -t mysql_images_koto &&  docker run -d --name mysql_container_koto mysql_images_koto 

# into container
# docker exec -ti mysql_container_koto sh
