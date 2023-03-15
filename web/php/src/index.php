<?php
session_start();

define("ROOT", str_replace("index.php", "", $_SERVER["SCRIPT_FILENAME"]));
require_once(ROOT . "controllers/Articles.php");
require_once(ROOT . "controllers/Connection.php");

require_once(ROOT . "models/Article.php");
require_once(ROOT . "models/User.php");

require_once(ROOT . "app/Router.php");

$r = new Router($_GET['url']);

$r->get('/', function () {
    $a = new Articles();

    $a->index();
});

$r->get('/posts/:id', function ($id) {
    $a = new Articles();

    $a->one($id);
});

$r->post('/posts', function () {
    $a = new Article();
    $a->insert($_POST["title"], $_POST["body"], $_SESSION["user"]["username"]);

    header("Location: /");
    die();
});

$r->get('/signin', function () {
    $c = new Connection();

    $c->signin();
});

$r->post('/signin', function () {
    if (!isset($_POST["username"])) {
        return;
    }
    if (!isset($_POST["password"])) {
        return;
    }
    if (!isset($_POST["password2"])) {
        return;
    }

    if ($_POST["password2"] == $_POST["password"]) {
        $u = new User();

        $u->insert($_POST["username"], $_POST["password"]);
    }


    header("Location: /");
});

$r->get('login', function () {

    $c = new Connection();

    $c->login();
});

$r->post('login', function () {
    if (!isset($_POST["username"])) {
        return;
    }
    if (!isset($_POST["password"])) {
        return;
    }

    $u = new User();
    $fetchedUser = $u->findByUsername($_POST["username"]);

    $isPassValid = password_verify($_POST["password"], $fetchedUser["passwordHash"]);
    unset($fetchedUser["passwordHash"]);
    unset($fetchedUser[2]);

    if ($isPassValid) {
        $_SESSION["user"] = $fetchedUser;
    }

    header("Location: /");
});

$r->get('logout', function () {
    unset($_SESSION["user"]);

    header("Location: /");
});


$r->run();
