<?php
require_once(ROOT . "app/Controller.php");

class Articles extends Controller
{
    public function index()
    {
        $this->loadModel('Article');
        $this->render("index", ["articles" => $this->Article->getALL()], "Home");
    }

    public function one($id)
    {
        $this->loadModel('Article');
        $selectedArticle = $this->Article->findById($id);
        $this->render("one", ["article" => $selectedArticle], $selectedArticle['title']);
    }
}
