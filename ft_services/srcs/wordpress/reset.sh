kubectl delete deployment wordpress-deployment
eval $(minikube docker-env)
docker rmi wordpress_images_koto
docker build . -t wordpress_images_koto
kubectl apply -f ../wordpress.yaml
