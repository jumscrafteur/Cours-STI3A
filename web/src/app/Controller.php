<?php
require_once(ROOT . "app/Controller.php");

abstract class Controller
{
    public function loadModel(string $model)
    {
        require_once(ROOT . 'models/' . $model . '.php');
        $this->$model = new $model();
    }
    public function render($vue, array $data = [], $title)
    {
        if (!empty($data))
            extract($data);

        ob_start();

        require_once(ROOT . 'views/' . strtolower(get_class($this)) . '/' . $vue . '.php');

        $content = ob_get_clean();

        require_once(ROOT . 'views/layout/default.php');
    }
}
