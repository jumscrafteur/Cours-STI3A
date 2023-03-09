<?php
require_once(ROOT . "app/Controller.php");

class Connection extends Controller
{
    public function signin()
    {
        $this->render("signin", [], "SignIn");
    }

    public function login()
    {
        $this->render("login", [], "LogIn");
    }
}
