# FROM alpine:3.6
FROM alpine:3.13

RUN apk update; \
		apk add influxdb; \
		rm -fr /var/cache/apk/*


COPY ./srcs/setup.sh /setup.sh
# COPY ./srcs/init_mysql /init_mysql
# COPY ./srcs/my.cnf /etc/my.cnf
# RUN mkdir -p /run/mysqld

# ENTRYPOINT [ "sh", "/setup.sh" ]
CMD ["/setup.sh"]

# ========================

# run
# docker build . -t influx_images_koto && docker run -d --name influx_container_koto influx_images_koto

# sh
# docker build . -t influx_images_koto &&  docker run -ti --name influx_container_koto influx_images_koto sh

# remove
# docker container stop influx_container_koto && docker rm influx_container_koto && docker rmi influx_images_koto

# restart sh
# docker container stop influx_container_koto && docker rm influx_container_koto && docker rmi influx_images_koto && docker build . -t influx_images_koto &&  docker run -ti --name influx_container_koto influx_images_koto sh

# restart run
# docker container stop influx_container_koto && docker rm influx_container_koto && docker rmi influx_images_koto && docker build . -t influx_images_koto &&  docker run -d --name influx_container_koto influx_images_koto 

# into container
# docker exec -ti influx_container_koto sh

# ------------

# docker run -d --name influx_container_koto influx_images_koto
# &&
# docker exec -it influx_container_koto sh

# docker run -it --name influx_container_koto influx_images_koto bash


