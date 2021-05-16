# FROM alpine:3.6
FROM alpine:3.12

RUN apk update; \
		apk add --no-cache mysql mysql-client libc6-compat wget;

# RUN set -ex; \
# 		cd /var/lib/mysql; \
# 		mysql_install_db --bootstarp --user=mysql;

# RUN mkdir /run/mysqld/

COPY ./srcs/setup.sh /setup.sh
COPY ./srcs/init_mysql /init_mysql
COPY ./srcs/my.cnf /etc/my.cnf
RUN mkdir -p /run/mysqld

# telegraf
RUN wget https://dl.influxdata.com/telegraf/releases/telegraf-1.16.2_linux_amd64.tar.gz
RUN tar -xvf telegraf-1.16.2_linux_amd64.tar.gz
RUN sed -i -e 's/hostname = ""/hostname = "mysql"/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN sed -i -e 's/# urls = \["http:\/\/127.0.0.1:8086"\]/urls = \["http:\/\/influxdb-service:8086"\]/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN sed -i -e 's/# database = "telegraf"/database = "mysql"/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf



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


