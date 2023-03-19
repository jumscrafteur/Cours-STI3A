<?php
require_once(ROOT . "/app/librairies/Controller.php");

class Doctors extends Controller
{
    private $DoctorModel;

    public function __construct()
    {
        $this->DoctorModel = $this->loadModel('Doctor');
    }

    public function login()
    {
        $data = [
            "email" => "",
            "password" => "",
            "error" => []
        ];

        if ($_SERVER['REQUEST_METHOD'] == 'POST') {
            if (!isset($_POST['email']))
                $data['error']->append('Enter an Email');

            if (!isset($_POST['password']))
                $data['error']->append('Enter an Password');
        } else {
            $data = [
                "email" => "",
                "password" => "",
                "error" => []
            ];

            $this->render("login", $data);
        }
    }
}
