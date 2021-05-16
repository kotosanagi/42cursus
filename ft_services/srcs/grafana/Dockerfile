FROM alpine:3.12
# FROM alpine:3.6 <- doesn't work

COPY ./srcs/setup.sh /

RUN apk update; \
	apk add libc6-compat openssl;

# ssl
RUN set -ex; \
		mkdir -p etc/grafana/ssl; \
		openssl genrsa 4048 > etc/grafana/ssl/grafana.key; \
		openssl req -new -subj "/C=JP/ST=Tokyo/L=Minato/O=42Tokyo/OU=42cursus/CN=localhost" -key etc/grafana/ssl/grafana.key > etc/grafana/ssl/grafana.csr; \
		openssl x509 -req -days 365 -signkey etc/grafana/ssl/grafana.key -in etc/grafana/ssl/grafana.csr > etc/grafana/ssl/grafana.crt;


####### install grafana #######
RUN wget https://dl.grafana.com/enterprise/release/grafana-enterprise-7.5.5.linux-amd64.tar.gz
RUN tar -zxvf grafana-enterprise-7.5.5.linux-amd64.tar.gz
RUN rm grafana-enterprise-7.5.5.linux-amd64.tar.gz
COPY ./srcs/grafana.ini /grafana-7.5.5/conf/grafana.ini
RUN chmod 644 /grafana-7.5.5/conf/grafana.ini
# RUN cp grafana-7.5.5/conf/defaults.ini grafana-7.5.5/conf/grafana.ini
# RUN sed -i -e 's/protocol = http/protocol = https/g' /grafana-7.5.5/conf/grafana.ini 
# RUN sed -i -e 's/cert_file =/cert_file = \/etc\/grafana\/ssl\/grafana.crt/g' /grafana-7.5.5/conf/grafana.ini 
# RUN sed -i -e 's/cert_key =/cert_key = \/etc\/grafana\/ssl\/grafana.key/g' /grafana-7.5.5/conf/grafana.ini 
# RUN sed -i -e 's/provisioning = conf\/provisioning/provisioning = conf\/provisioning\/dashboards/g' /grafana-7.5.5/conf/grafana.ini 
COPY ./srcs/datasource.yaml /grafana-7.5.5/conf/provisioning/datasources
RUN chmod 644 /grafana-7.5.5/conf/provisioning/datasources/datasource.yaml

COPY ./srcs/dashboards.yaml /grafana-7.5.5/conf/provisioning/dashboards/dashboard.yaml
RUN chmod 644 /grafana-7.5.5/conf/provisioning/dashboards/dashboard.yaml

COPY ./srcs/dashboard_json/*.json /grafana-7.5.5/conf/provisioning/dashboards/
RUN chmod 644 /grafana-7.5.5/conf/provisioning/dashboards/*.json
# RUN rm grafana-7.5.5/conf/provisioning/dashboards/sample.yaml 

###### install grafana #######


# telegraf
RUN wget https://dl.influxdata.com/telegraf/releases/telegraf-1.16.2_linux_amd64.tar.gz
RUN tar -xvf telegraf-1.16.2_linux_amd64.tar.gz
RUN sed -i -e 's/hostname = ""/hostname = "grafana"/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN sed -i -e 's/# urls = \["http:\/\/127.0.0.1:8086"\]/urls = \["http:\/\/influxdb-service:8086"\]/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf
RUN sed -i -e 's/# database = "telegraf"/database = "grafana"/g' /telegraf-1.16.2/etc/telegraf/telegraf.conf



EXPOSE 3000

CMD sh ./setup.sh



# run
# docker build . -t grafana_images_koto && docker run -d --name grafana_container_koto grafana_images_koto

# sh
# docker build . -t grafana_images_koto && docker run -d --name grafana_container_koto grafana_images_koto && docker exec -ti grafana_container_koto sh

# remove
# docker container stop grafana_container_koto && docker rm grafana_container_koto && docker rmi grafana_images_koto

# restart sh
# docker container stop grafana_container_koto && docker rm grafana_container_koto && docker rmi grafana_images_koto && docker build . -t grafana_images_koto && docker run -d --name grafana_container_koto grafana_images_koto && docker exec -ti grafana_container_koto sh


# restart run
# docker container stop grafana_container_koto && docker rm grafana_container_koto && docker rmi grafana_images_koto && docker build . -t grafana_images_koto &&  docker run -d --name grafana_container_koto grafana_images_koto 

# into container
# docker exec -ti grafana_container_koto sh

################################################