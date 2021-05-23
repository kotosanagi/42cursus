FROM alpine:3.12

RUN apk update; \
		apk add --no-cache mysql mysql-client libc6-compat wget;

COPY ./srcs/setup.sh /setup.sh
COPY ./srcs/init_mysql /init_mysql
COPY ./srcs/my.cnf /etc/my.cnf
COPY ./srcs/livenessprobe.sh /livenessprobe.sh
RUN mkdir -p /run/mysqld

# telegraf
RUN wget https://dl.influxdata.com/telegraf/releases/telegraf-1.16.2_linux_amd64.tar.gz
RUN tar -xvf telegraf-1.16.2_linux_amd64.tar.gz
RUN sed -i -e 's/hostname = ""/hostname = "mysql"/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN sed -i -e 's/# urls = \["http:\/\/127.0.0.1:8086"\]/urls = \["http:\/\/influxdb-service:8086"\]/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN sed -i -e 's/# database = "telegraf"/database = "mysql"/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN rm telegraf-1.16.2_linux_amd64.tar.gz

ENTRYPOINT [ "sh", "/setup.sh" ]
