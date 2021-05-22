#!/bin/sh

kubectl delete deployment grafana-deployment
eval $(minikube docker-env)
docker rmi grafana_images_koto
docker build ./srcs/grafana/ -t grafana_images_koto
kubectl apply -f ./srcs/grafana.yaml

########
sleep 10
kubectl get pod