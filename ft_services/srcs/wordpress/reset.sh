#!/bin/sh

kubectl delete deployment wordpress-deployment
eval $(minikube docker-env)
docker rmi wordpress_images_koto
docker build ./srcs/wordpress/ -t wordpress_images_koto
kubectl apply -f ./srcs/wordpress.yaml

########
sleep 10
kubectl get pod