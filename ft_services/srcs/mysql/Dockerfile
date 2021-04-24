FROM alpine:3.6

RUN apk update; \
		apk add --no-cache mysql mysql-client

# RUN set -ex; \
# 		cd /var/lib/mysql; \
# 		mysql_install_db --bootstarp --user=mysql;

# RUN mkdir /run/mysqld/

COPY ./srcs/setup.sh /setup.sh
COPY ./srcs/init_mysql /init_mysql
COPY ./srcs/my.cnf /etc/my.cnf
RUN mkdir -p /run/mysqld

ENTRYPOINT [ "sh", "/setup.sh" ]
# CMD ["/setup.sh"]
# ========================

# run
# docker build . -t mysql_images_koto && docker run -d --name mysql_container_koto mysql_images_koto

# sh
# docker build . -t mysql_images_koto &&  docker run -ti --name mysql_container_koto mysql_images_koto sh

# remove
# docker container stop mysql_container_koto && docker rm mysql_container_koto && docker rmi mysql_images_koto

# restart sh
# docker container stop mysql_container_koto && docker rm mysql_container_koto && docker rmi mysql_images_koto && docker build . -t mysql_images_koto &&  docker run -ti --name mysql_container_koto mysql_images_koto sh

# restart run
# docker container stop mysql_container_koto && docker rm mysql_container_koto && docker rmi mysql_images_koto && docker build . -t mysql_images_koto &&  docker run -d --name mysql_container_koto mysql_images_koto 

# into container
# docker exec -ti mysql_container_koto sh




# ------------



# docker run -d --name mysql_container_koto mysql_images_koto
# &&
# docker exec -it mysql_container_koto sh



# docker run -it --name mysql_container_koto mysql_images_koto bash


