<?php

abstract class Model
{
    private $host = "db";
    private $dbname = "blog";
    private $username = "root";
    private $password = "example";

    protected $_connection;
    public $table;
    public $id;

    public function getConnection()
    {
        $this->_connection = null;
        try {
            $this->_connection = new PDO(
                "mysql:host=" . $this->host . ";dbname=" . $this->dbname,
                $this->username,
                $this->password
            );
        } catch (PDOException $exception) {
            echo "Error:" . $exception->getMessage();
        }
    }

    public function getAll()
    {
        $sql = "SELECT * FROM " . $this->table;
        $query = $this->_connection->prepare($sql);
        $query->execute();

        return $query->fetchAll();
    }
}
