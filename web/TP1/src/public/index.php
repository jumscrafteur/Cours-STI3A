<?php
require_once("../bootstrap.php");

require_once(APP_ROOT . "/controllers/Doctors.php");


$ds = new Doctors();

$ds->login();
