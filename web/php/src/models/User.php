<?php
require_once(ROOT . "app/Model.php");

class User extends Model
{
    public function __construct()
    {
        $this->table = 'user';
        $this->getConnection();
    }

    public function findById(int $id)
    {
        $sql = "SELECT * FROM " . $this->table . " WHERE id = :id";
        $querry = $this->_connection->prepare($sql);
        $querry->execute(['id' => $id]);
        return $querry->fetch();
    }

    public function insert($username, $password)
    {
        $hashPassword = password_hash($password, PASSWORD_BCRYPT);

        $sql = "INSERT INTO " . $this->table . " (`username`, `passwordHash`) VALUES (:username, :passwordHash)";
        $querry = $this->_connection->prepare($sql);
        $querry->execute(['username' => $username, 'passwordHash' => $hashPassword]);
    }

    public function findByUsername($username)
    {
        $sql = "SELECT * FROM " . $this->table . " WHERE username = :username";
        $querry = $this->_connection->prepare($sql);
        $querry->execute(['username' => $username]);
        return $querry->fetch();
    }
}
