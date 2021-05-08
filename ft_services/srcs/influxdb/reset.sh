kubectl delete deployment influxdb-deployment
eval $(minikube docker-env)
docker rmi influxdb_images_koto
docker build ./srcs/influxdb/ -t influxdb_images_koto
kubectl apply -f ./srcs/influxdb.yaml

########
sleep 10
kubectl get pod