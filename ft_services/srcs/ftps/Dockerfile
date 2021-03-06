FROM alpine:3.12

COPY ./srcs/setup.sh /
COPY ./srcs/livenessprobe.sh /livenessprobe.sh

RUN apk update; \
	apk add vsftpd openssl lftp libc6-compat;

#adduser
RUN mkdir -p /etc/ftps/ftp_admin && \
	adduser --home=/etc/ftps/ftp_admin -D ftp_admin && \
	echo "ftp_admin:ftp_admin" | chpasswd

# ssl
RUN set -ex; \
		mkdir -p etc/ftps/ssl; \
		openssl genrsa 4048 > etc/ftps/ssl/ftps.key; \
		openssl req -new -subj "/C=JP/ST=Tokyo/L=Minato/O=42Tokyo/OU=42cursus/CN=localhost" -key etc/ftps/ssl/ftps.key > etc/ftps/ssl/ftps.csr; \
		openssl x509 -req -days 365 -signkey etc/ftps/ssl/ftps.key -in etc/ftps/ssl/ftps.csr > etc/ftps/ssl/ftps.crt;

COPY ./srcs/vsftpd.conf /etc/vsftpd/vsftpd.conf

# telegraf
RUN wget https://dl.influxdata.com/telegraf/releases/telegraf-1.16.2_linux_amd64.tar.gz
RUN tar -xvf telegraf-1.16.2_linux_amd64.tar.gz
RUN sed -i -e 's/hostname = ""/hostname = "ftps"/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN sed -i -e 's/# urls = \["http:\/\/127.0.0.1:8086"\]/urls = \["http:\/\/influxdb-service:8086"\]/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN sed -i -e 's/# database = "telegraf"/database = "ftps"/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN rm telegraf-1.16.2_linux_amd64.tar.gz

EXPOSE 21 40001-40003

CMD sh ./setup.sh
