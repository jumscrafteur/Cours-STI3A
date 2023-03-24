<?php
abstract class Controller
{
    public function loadModel(string $model)
    {
        require_once(APP_ROOT . '/models/' . $model . '.php');

        return new $model();
    }

    public function render($vue, array $data)
    {
        if (!empty($data))
            extract($data);

        ob_start();

        require_once(APP_ROOT . '/views/' . strtolower(get_class($this)) . '/' . $vue . '.php');

        $content = ob_get_clean();

        require_once(APP_ROOT . '/views/layout.php');
    }
}
