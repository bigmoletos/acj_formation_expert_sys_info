# installation du site WORDPRESS sur 2 instances aws EC2 et sur 2 instances en local
# Installation
Pour configurer l'application, utilisez les identifiants suivants :
Les identifaints ci-dessous seront remplacés par les valeurs issue du fichier .env et le fichier .md sera renommé en _securised.md
nom: ${name}
root: ${root}
mot de passe: ${password}
utilisateur: ${user}



## AWS EC2 au niveau des instances aws groupe de securité il faut autorier SSh HTTP et MySQL/Aurora

Vérifier les Groupes de Sécurité sur AWS
Connectez-vous à la console AWS et accédez à EC2 > Groupes de sécurité.
Sélectionnez le groupe de sécurité associé à l'instance MariaDB (3.135.226.41).

Vérifiez les règles entrantes et assurez-vous qu'il y a une règle qui autorise les connexions entrantes sur le port 3306 :

Type : MySQL/Aurora
Protocole : TCP
Port : 3306
Source : 3.128.29.116/32 (adresse IP de l'instance WordPress) ou 0.0.0.0/0 (moins sécurisé, à n'utiliser que pour tester).

# Fiche d'Installation de WordPress sur Debian 12

## Prérequis
- Une instance Debian 12 avec les privilèges `sudo`.
- Un nom de domaine pointant vers l'adresse IP de l'instance ou son IP publique.
- Accès SSH à l'instance.

## 1. Mise à Jour du Système

```bash
sudo apt update && sudo apt upgrade -y

sudo apt install build-essential libncursesw5-dev libncurses-dev autoconf autoconf-archive automake make pkgconf m4 build-essential gdb lcov pkg-config   libbz2-dev libffi-dev libgdbm-dev libgdbm-compat-dev liblzma-dev   libncurses5-dev libreadline6-dev libsqlite3-dev libssl-dev  lzma lzma-dev tk-dev uuid-dev zlib1g-dev unzip apache2 ssh ufw htop -y
```


## 2. Installation de LAMP (Linux, Apache, MySQL, PHP)
### 2.1. Installer Apache
```bash
sudo apt install apache2 -y
sudo systemctl start apache2
sudo systemctl enable apache2

sudo systemctl status apache2
```

### Installer MariaDB (MySQL)

```bash
sudo apt install mariadb-server -y
sudo systemctl start mariadb
sudo systemctl enable mariadb
```



### Sécuriser l'Installation de MariaDB

```bash
sudo mysql_secure_installation
```

NOTE: RUNNING ALL PARTS OF THIS SCRIPT IS RECOMMENDED FOR ALL MariaDB
      SERVERS IN PRODUCTION USE!  PLEASE READ EACH STEP CAREFULLY!

In order to log into MariaDB to secure it, we'll need the current
password for the root user. If you've just installed MariaDB, and
haven't set the root password yet, you should just press enter here.

Enter current password for root (enter for none):
OK, successfully used password, moving on...

Setting the root password or using the unix_socket ensures that nobody
can log into the MariaDB root user without the proper authorisation.

You already have your root account protected, so you can safely answer 'n'.

Switch to unix_socket authentication [Y/n] y
Enabled successfully!
Reloading privilege tables..
 ... Success!


You already have your root account protected, so you can safely answer 'n'.

Change the root password? [Y/n] y
New password:
Re-enter new password:
Sorry, you can't use an empty password here.

New password:
Re-enter new password:
Password updated successfully!
Reloading privilege tables..
 ... Success!


By default, a MariaDB installation has an anonymous user, allowing anyone
to log into MariaDB without having to have a user account created for
them.  This is intended only for testing, and to make the installation
go a bit smoother.  You should remove them before moving into a
production environment.

Remove anonymous users? [Y/n] n
 ... skipping.
Normally, root should only be allowed to connect from 'localhost'.  This
ensures that someone cannot guess at the root password from the network.
Disallow root login remotely? [Y/n] n
 ... skipping.

By default, MariaDB comes with a database named 'test' that anyone can
access.  This is also intended only for testing, and should be removed
before moving into a production environment.

Remove test database and access to it? [Y/n] n
 ... skipping.

Reloading the privilege tables will ensure that all changes made so far
will take effect immediately.

Reload privilege tables now? [Y/n] y
 ... Success!

Cleaning up...

All done!  If you've completed all of the above steps, your MariaDB
installation should now be secure.

Thanks for using MariaDB!

## 2.4. Créer la Base de Données WordPress

```bash
sudo mysql -u root -p
```


```bash
CREATE DATABASE wordpress;
CREATE USER 'franck'@'%' IDENTIFIED BY 'xxxxxxxxxxxxxxx';
GRANT ALL PRIVILEGES ON wordpress.* TO 'franck'@'%';
FLUSH PRIVILEGES;
EXIT;
```

#### pour tester
```bash
sudo mysql -u root -p
GRANT ALL PRIVILEGES ON wordpress.* TO 'franck'@'%' IDENTIFIED BY 'xxxxxxxxxxxxxxx';
FLUSH PRIVILEGES;
exit;
```
##  Installer PHP et les Extensions Nécessaires

```bash
sudo apt install php libapache2-mod-php php-mysql php-xml php-gd php-curl php-mbstring php-xmlrpc php-soap php-intl php-zip unzip -y
```

## Téléchargement de WordPress

```bash
cd /var/www/html/
sudo wget https://wordpress.org/latest.zip
sudo unzip latest.zip
sudo mv wordpress/* /var/www/html/
sudo chown -R www-data:www-data /var/www/html/
sudo chmod -R 755 /var/www/html/
```

## Configurer WordPress


```bash
sudo mv /var/www/html/wp-config-sample.php /var/www/html/wp-config.php
```

### Modifiez le fichier de configuration WordPress :
```bash
sudo nano /var/www/html/wp-config.php

#// ** Database settings - You can get this info from your web host ** //
#/** The name of the database for WordPress */
define( 'DB_NAME', $DEBIAN_NAME );

#/** Database username */
define( 'DB_USER', 'franck' );

#/** Database password */
define( 'DB_PASSWORD', 'xxxxxxx' );

#/** Database hostname */
define( 'DB_HOST', '3.135.226.41' );

#/** Database charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8' );

#/** The database collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );
```


## Configurer Apache pour WordPress
### Créez un nouveau fichier de configuration pour le site WordPress et Ajoutez la configuration suivante :
```bash
sudo nano /etc/apache2/sites-available/wordpress.conf

<VirtualHost *:80>
    ServerName 3.128.29.116
    DocumentRoot /var/www/html/

    <Directory /var/www/html/>
        AllowOverride All
    </Directory>

    ErrorLog ${APACHE_LOG_DIR}/error.log
    CustomLog ${APACHE_LOG_DIR}/access.log combined
</VirtualHost>
```

```bash
sudo nano /etc/mysql/mariadb.conf.d/50-server.cnf
remplacer
bind-address            = 127.0.0.1
par
bind-address            = 0.0.0.0
```

### Activez la configuration du site et le module rewrite :

```bash
sudo nano /etc/apache2/apache2.conf

### à la fin du fichier il faut rajouter
ServerName 3.128.29.116
```

```bash
sudo a2ensite wordpress.conf
sudo a2enmod rewrite
```

### Vérifiez la syntaxe Apache et redémarrez le service :
```bash
sudo apache2ctl configtest
sudo systemctl reload apache2
```


## verfication du parfeu

```bash
sudo apt install ufw -y
sudo ufw status
# pour autiser le port par defaut 3306
sudo ufw allow from 3.128.29.116 to any port 3306

# Pour tester, vous pouvez désactiver temporairement ufw :
sudo ufw disable
```

## pour relancer le serveur mariaDb

```bash
sudo systemctl start mariadb
sudo systemctl enable mariadb
```

## pour relancer le serveur Web

```bash
sudo systemctl start apache2
sudo systemctl enable apache2
```

### Pour voir les tables mariadb et les users
```bash

sudo mysql -u root -p

SHOW DATABASES;
SELECT User, Host FROM mysql.user;
SHOW GRANTS FOR 'franck'@'%';
```

### pour changer le mot de passe du user de la Bdd

```bash
sudo mysql -u root -p
ALTER USER 'franck'@'%' IDENTIFIED BY 'xxxxxxxxxxxxxxx';
FLUSH PRIVILEGES;
EXIT;

CREATE USER 'franck'@'localhost' IDENTIFIED BY 'xxxxxxxxxxxxxxx';
ALTER USER 'wordpress'@'localhost' IDENTIFIED BY 'xxxxxxxxxxxxxxx';
GRANT ALL PRIVILEGES ON wordpress.* TO 'franck'@'%' IDENTIFIED BY 'xxxxxxxxxxxxxxx';
FLUSH PRIVILEGES;
EXIT;

### pour autoriser toutes les ip et pas que le localhost
EXIT;
CREATE USER 'franck'@'%' IDENTIFIED BY 'xxxxxxxxxxxxxxx';
```

### pour tester l'acces à l'instance de la BDD de puis celle du site wordpress il faut installer un client mariadb dessus

```bash
sudo apt install mariadb-client -y
mysql -h 3.135.226.41 -P 3306 -u franck -p
```

# acceder à la vm aws franckBDD depuis une Vm locale et non aws on peut creer un tunnel ssh

```bash
ssh -i  C:/AJC_formation/linux/doc/debian12/keyfranck2.pem  -L 3306:localhost:3306 franck@3.135.226.41
mkdir -p ~/.ssh
cp /path/to/keyfile.pem ~/.ssh/
chmod 600 ~/.ssh/keyfile.pem
chmod 700 ~/.ssh

# avant il faut copier la clé pem sur l'instance dans un dossier .ssh

~/.ssh/

ssh -i ~/.ssh/keyfranck2.pem -L 3306:localhost:3306 franck@3.135.226.41
```

## instance wordpress locale bdd sur 192.168.1.189, instance site wordpress 192.168.1.188

```bash
USE wordpress;
SELECT option_name, option_value FROM wp_options WHERE option_name IN ('siteurl', 'home');
UPDATE wp_options SET option_value = 'http://192.168.1.188:9500' WHERE option_name = 'siteurl' OR option_name = 'home';

# Pour tester le site en local:
http://192.168.1.188:9500/wp-admin/install.php
```


