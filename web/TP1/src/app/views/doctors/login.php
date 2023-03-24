<?php
// var_dump($data);

foreach ($data['error'] as $error) {
    echo $error;
}

if (isset($_SESSION['doctor_name'])) {
    echo "Hello : " . $_SESSION['doctor_name'];
}
?>

<form action="/" method="post">
    <label for="email">Email</label><input name="email" type="text" value="<?= $data['email'] ?>">
    <label for="password">Password</label><input name="password" type="password" value="<?= $data['password'] ?>">
    <button type="submit">Envoyer</button>
</form>