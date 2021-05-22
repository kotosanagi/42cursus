#!/bin/sh

kubectl delete deployment nginx-deployment
eval $(minikube docker-env)
docker rmi nginx_images_koto
docker build ./srcs/nginx/ -t nginx_images_koto
kubectl apply -f ./srcs/nginx.yaml

########
sleep 10
kubectl get pod