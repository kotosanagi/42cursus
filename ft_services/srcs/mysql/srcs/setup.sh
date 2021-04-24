#!/bin/sh

# cd /var/lib/mysql ; mysql_install_db --datadir='/var/lib/mysql/data'
# cd /var/lib/mysql ; mysql_install_db --user=mysql --datadir='/var/lib/mysql/data'

# cd '/usr' ; /usr/bin/mysqld_safe --datadir='/var/lib/mysql/data' --init_file=/init_mysql &

# mysql -e "CREATE USER 'user'@'%' IDENTIFIED BY 'pass';"

# mysql -e "GRANT ALL PRIVILEGES ON wp_ftdb.* TO 'user'@'%' IDENTIFIED BY 'pass' WITH GRANT OPTION;";

# mysql -e "FLUSH PRIVILEGES;";

# mysql -e "create database mydbbbbbbbbbbbbbbb;"

/usr/bin/mysql_install_db --datadir=/var/lib/mysql

/usr/bin/mysqld --user=root --init_file=/init_mysql &


touch /bbbbb

tail -f /dev/null
