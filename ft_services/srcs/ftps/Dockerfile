FROM alpine:3.12

COPY ./srcs/setup.sh /

RUN apk update; \
	apk add vsftpd openssl lftp;

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
# RUN mkdir /var/ftp



EXPOSE 20 21 40001-40003

CMD sh ./setup.sh

# run
# docker build . -t ftps_images_koto && docker run -d --name ftps_container_koto ftps_images_koto

# sh
# docker build . -t ftps_images_koto && docker run -d --name ftps_container_koto ftps_images_koto && docker exec -ti ftps_container_koto sh

# remove
# docker container stop ftps_container_koto && docker rm ftps_container_koto && docker rmi ftps_images_koto

# restart sh
# docker container stop ftps_container_koto && docker rm ftps_container_koto && docker rmi ftps_images_koto && docker build . -t ftps_images_koto && docker run -d --name ftps_container_koto ftps_images_koto && docker exec -ti ftps_container_koto sh


# restart run
# docker container stop ftps_container_koto && docker rm ftps_container_koto && docker rmi ftps_images_koto && docker build . -t ftps_images_koto &&  docker run -d --name ftps_container_koto ftps_images_koto 

# into container
# docker exec -ti ftps_container_koto sh



#### CONNECT LFTP ####
# lftp -e "set ssl:verify-certificate no" -u ftp_admin,ftp_admin 192.168.49.42 -p 21
######################