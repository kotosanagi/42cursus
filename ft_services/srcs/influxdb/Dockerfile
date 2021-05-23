FROM alpine:3.13

RUN apk update; \
		apk add influxdb libc6-compat; \
		rm -fr /var/cache/apk/*

COPY ./srcs/setup.sh /setup.sh
COPY ./srcs/livenessprobe.sh /livenessprobe.sh

RUN mkdir -p /var/lib/influxdb

# telegraf
RUN wget https://dl.influxdata.com/telegraf/releases/telegraf-1.16.2_linux_amd64.tar.gz
RUN tar -xvf telegraf-1.16.2_linux_amd64.tar.gz
RUN sed -i -e 's/hostname = ""/hostname = "influxdb"/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN sed -i -e 's/# database = "telegraf"/database = "influxdb"/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN rm telegraf-1.16.2_linux_amd64.tar.gz

CMD ["/setup.sh"]
