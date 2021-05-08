kubectl delete deployment mysql-deployment
eval $(minikube docker-env)
docker rmi mysql_images_koto
docker build ./srcs/mysql/ -t mysql_images_koto
kubectl apply -f ./srcs/mysql.yaml

########
sleep 10
kubectl get pod