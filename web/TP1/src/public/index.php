<?php
define("ROOT", str_replace("/public/index.php", "", $_SERVER["SCRIPT_FILENAME"]));

require_once(ROOT . "/app/controllers/Doctors.php");

$ds = new Doctors();

$ds->login();
