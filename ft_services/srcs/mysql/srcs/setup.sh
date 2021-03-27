cd /var/lib/mysql ; mysql_install_db --user=mysql

cd '/usr' ; /usr/bin/mysqld_safe --datadir='/var/lib/mysql/data' &

tail -f /dev/null
