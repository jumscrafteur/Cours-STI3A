<?php
abstract class Controller
{
    public function loadModel(string $model)
    {
        require_once(ROOT . '/app/models/' . $model . '.php');

        return new $model();
    }

    public function render($vue, array $data)
    {
        if (!empty($data))
            extract($data);

        ob_start();

        require_once(ROOT . '/app/views/' . strtolower(get_class($this)) . '/' . $vue . '.php');

        $content = ob_get_clean();

        require_once(ROOT . '/app/views/layout.php');
    }
}
