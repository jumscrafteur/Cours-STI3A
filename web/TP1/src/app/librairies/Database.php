<?php

class Database
{
    private $host = "db";
    private $dbname = "TP";
    private $username = "root";
    private $password = "marseille";

    private $db;
    private $query;

    public function __construct()
    {
        $this->db = null;
        try {
            $this->db = new PDO(
                "mysql:host=" . $this->host . ";dbname=" . $this->dbname,
                $this->username,
                $this->password
            );
        } catch (PDOException $exception) {
            echo "Error:" . $exception->getMessage();
        }
    }


    public function query($sql)
    {
        $this->query = $this->db->prepare($sql);
    }

    public function execute($data = [])
    {
        return $this->query->execute($data);
    }

    public function single()
    {
        return $this->query->fetch();
    }

    public function resultSet()
    {
        return $this->query->fetchAll();
    }

    public function rowCount()
    {
        return $this->query->rowCount();
    }

    public function lastInsertId()
    {
        return $this->db->lastInsertId();
    }
}


// $db = new Database();

// $db->query("SELECT * FROM doctor");
// var_dump($db->resultSet());
// echo "<br/>";
// var_dump($db->rowCount());
