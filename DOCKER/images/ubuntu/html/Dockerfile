FROM ubuntu

RUN apt update && apt upgrade -y
RUN apt install -y apache2
ADD index.html /var/www/html

WORKDIR /var/www/html
EXPOSE 80
CMD ["/usr/sbin/apache2ctl", "-D", "FOREGROUND"]
