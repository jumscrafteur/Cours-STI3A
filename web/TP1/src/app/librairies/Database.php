<?php

class Database
{
    private $db;
    private $query;

    public function __construct()
    {
        $this->db = null;
        try {
            $this->db = new PDO(
                "mysql:host=" . DB_HOST . ";dbname=" . DB_NAME,
                DB_USER,
                DB_PASS
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
