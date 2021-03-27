FROM alpine:3.6


RUN apk update; \
		apk add --no-cache vim mysql mysql-client

COPY ./srcs/setup.sh /var/lib/mysql
CMD sh /var/lib/mysql/setup.sh

# ========================

# run
# docker build . -t koto_image && docker run -d --name koto_container koto_image

# ash
# docker build . -t koto_image &&  docker run -ti --name koto_container koto_image ash

# remove
# docker container stop koto_container && docker rm koto_container && docker rmi koto_image


# restart ash
# docker container stop koto_container && docker rm koto_container && docker rmi koto_image && docker build . -t koto_image &&  docker run -ti --name koto_container koto_image ash

# restart run
# docker container stop koto_container && docker rm koto_container && docker rmi koto_image && docker build . -t koto_image &&  docker run -d --name koto_container koto_image 


# into container
# docker exec -ti koto_container sh