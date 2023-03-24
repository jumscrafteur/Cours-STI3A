<?php
require_once(APP_ROOT . "/librairies/Controller.php");

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
            if (!isset($_POST['email'])) {
                array_push($data['error'], 'Enter an Email');
            } else {
                $data['email'] = $_POST['email'];
            }

            if (isset($_POST['email']) && $_POST['email'] == "")
                array_push($data['error'], "Email can't be ampty");

            // if (isset($_POST['email']) && !$this->DoctorModel->findByEmail($_POST['email']))
            //     $data['error']->append("No doctor with email : " . $_POST['email']);

            if (!isset($_POST['password'])) {
                array_push($data['error'], 'Enter an Password');
                // array_push($data['error'],'Enter an Password');
            } else {
                $data['password'] = $_POST['password'];
            }

            if (isset($_POST['password']) && $_POST['password'] == "")
                array_push($data['error'], 'Password can\'t be empty');

            if (count($data['error']) == 0) {
                $loggedInDoctor = $this->DoctorModel->login($_POST['email'], $_POST['password']);
                if ($loggedInDoctor) {
                    $this->createDoctorSession($loggedInDoctor);
                } else {
                    array_push($data['error'], 'Invalid Email or Password');
                }
            }
        }

        $this->render("login", $data);
    }

    public function createDoctorSession($doctor)
    {
        $_SESSION['doctor_id'] = $doctor['id'];
        $_SESSION['doctor_name'] = $doctor['name'];

        header('/patiens');
    }
}
