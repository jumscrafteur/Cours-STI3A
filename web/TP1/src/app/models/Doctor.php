<?php
require_once(APP_ROOT . "/librairies/Database.php");

class Doctor
{
    private $db;
    private $table = "doctor";

    public $id;
    private $name;
    private $email;
    private $password;
    private $specialist;
    private $gender;

    public function __construct()
    {
        $this->db = new Database();
    }

    public function findByEmail($email)
    {
        $sql = "SELECT * FROM $this->table  WHERE email = '$email'";
        $this->db->query($sql);
        $this->db->execute();

        return $this->db->rowCount() >= 1;
    }

    public function findByID($id)
    {
        $sql = "SELECT * FROM $this->table  WHERE id = :id";
        $this->db->query($sql);
        $this->db->execute(['id' => $id]);

        return $this->db->single();
    }

    public function create($data)
    {
        $data['password'] = password_hash($data['password'], PASSWORD_DEFAULT);


        $this->db->query("INSERT INTO $this->table (name, email, password, specialist, gender) VALUES  (:name, :email, :password, :specialist, :gender)");

        if ($this->db->execute($data)) {
            $this->id = $this->db->lastInsertId();
            return true;
        }

        return $this->db->execute($data);
    }

    public function login($email, $password)
    {
        $this->db->query("SELECT * from $this->table WHERE email = :email");

        $this->db->execute(['email' => $email]);
        $res = $this->db->single();

        if (password_verify($password, $res['password']))
            return $res;

        return false;
    }
}

// $doc = new Doctor();
// var_dump($doc->create([
//     "name" => 'Dr. James Park',
//     "email" => 'james.park@example.com',
//     "password" => 'passwordJKL',
//     "specialist" => 'Cardiology',
//     "gender" => 'M'
// ]));
