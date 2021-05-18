# minikube delete && sh ./setup.sh

minikube delete
# ---------- #
# ---------- #

# before exec
# sudo chmod -R 777 ~/.minikube
# sudo chmod -R 777 ~/.kube

minikube start --vm-driver=docker --extra-config=apiserver.service-node-port-range=1-65535

# set workplace environment
eval $(minikube docker-env) 


# build images
### docker build ./srcs/XXX -t XXX_images_koto
docker build ./srcs/influxdb -t influxdb_images_koto
docker build ./srcs/grafana -t grafana_images_koto
docker build ./srcs/nginx -t nginx_images_koto
docker build ./srcs/mysql -t mysql_images_koto
docker build ./srcs/wordpress -t wordpress_images_koto
docker build ./srcs/phpmyadmin -t phpmyadmin_images_koto
docker build ./srcs/ftps -t ftps_images_koto


# create cluster
# MetalLB
# kubectl apply -f ./srcs/debug-pod.yaml ##########DEBUG###########
kubectl apply -f https://raw.githubusercontent.com/metallb/metallb/v0.9.3/manifests/namespace.yaml
kubectl apply -f https://raw.githubusercontent.com/metallb/metallb/v0.9.3/manifests/metallb.yaml
kubectl apply -f ./srcs/config.yaml
kubectl create secret generic -n metallb-system memberlist --from-literal=secretkey="$(openssl rand -base64 128)"

kubectl apply -f ./srcs/influxdb.yaml
kubectl apply -f ./srcs/nginx.yaml
kubectl apply -f ./srcs/mysql.yaml
kubectl apply -f ./srcs/wordpress.yaml
kubectl apply -f ./srcs/phpmyadmin.yaml
kubectl apply -f ./srcs/ftps.yaml
kubectl apply -f ./srcs/grafana.yaml


########
echo "please wait..."
sleep 25
kubectl get pod -o wide
kubectl get svc