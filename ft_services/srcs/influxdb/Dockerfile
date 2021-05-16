# FROM alpine:3.6
FROM alpine:3.13

RUN apk update; \
		apk add influxdb libc6-compat; \
		rm -fr /var/cache/apk/*

COPY ./srcs/setup.sh /setup.sh
RUN mkdir -p /var/lib/influxdb

# telegraf
RUN wget https://dl.influxdata.com/telegraf/releases/telegraf-1.16.2_linux_amd64.tar.gz
RUN tar -xvf telegraf-1.16.2_linux_amd64.tar.gz
RUN sed -i -e 's/hostname = ""/hostname = "influxdb"/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
# RUN sed -i -e 's/# urls = \["http:\/\/127.0.0.1:8086"\]/urls = \["http:\/\/influxdb-service:8086"\]/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN sed -i -e 's/# database = "telegraf"/database = "influxdb"/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf


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

