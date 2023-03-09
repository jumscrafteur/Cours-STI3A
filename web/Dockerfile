FROM php:7.2-apache
RUN apt-get update && apt-get install -y
COPY src/ /var/www/html/
COPY ./LeQuotidienIntemporel.conf /etc/apache2/sites-available/LeQuotidienIntemporel.conf
RUN a2ensite LeQuotidienIntemporel.conf
RUN docker-php-ext-install pdo pdo_mysql
RUN a2enmod rewrite