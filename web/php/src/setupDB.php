<?php

$host = "db";
$dbname = "blog";
$username = "root";
$password = "example";

$db = new PDO(
  "mysql:host=$host",
  $username,
  $password
);

$db->query("CREATE DATABASE $dbname")->execute();

$db = new PDO(
  "mysql:host=$host;dbname=$dbname",
  $username,
  $password
);

$db->query("CREATE TABLE `post` (
  `id` int NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `title` varchar(255) NOT NULL,
  `body` text NOT NULL,
  `author` varchar(255) NOT NULL
);")->execute();

$db->query("CREATE TABLE `user` (
  `id` int NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `username` varchar(255) NOT NULL,
  `passwordHash` varchar(255) NOT NULL
);")->execute();
