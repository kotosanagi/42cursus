#!/bin/sh

kubectl delete deployment ftps-deployment
eval $(minikube docker-env)
docker rmi ftps_images_koto
docker build ./srcs/ftps/ -t ftps_images_koto
kubectl apply -f ./srcs/ftps.yaml

########
sleep 10
kubectl get pod