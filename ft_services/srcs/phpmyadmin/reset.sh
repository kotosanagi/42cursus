kubectl delete deployment phpmyadmin-deployment
eval $(minikube docker-env)
docker rmi phpmyadmin_images_koto
docker build ./srcs/phpmyadmin/ -t phpmyadmin_images_koto
kubectl apply -f ./srcs/phpmyadmin.yaml

########
sleep 10
kubectl get pod