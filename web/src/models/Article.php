<?php
require_once(ROOT . "app/Model.php");

class Article extends Model
{
    public function __construct()
    {
        $this->table = 'post';
        $this->getConnection();
    }

    public function findById(int $id)
    {
        $sql = "SELECT * FROM " . $this->table . " WHERE id = :id";
        $querry = $this->_connection->prepare($sql);
        $querry->execute(['id' => $id]);
        return $querry->fetch();
    }

    public function insert($title, $body, $author)
    {
        $sql = "INSERT INTO " . $this->table . " (`title`, `body`, `author`) VALUES (:title, :body, :author)";
        $querry = $this->_connection->prepare($sql);
        $querry->execute(['title' => $title, 'body' => $body, 'author' => $author]);
    }
}
