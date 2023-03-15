<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!-- <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/purecss@3.0.0/build/pure-min.css" integrity="sha384-X38yfunGUhNzHpBaEBsWLO+A0HDYOQi8ufWDkZ0k9e0eXz/tH3II7uKZ9msv++Ls" crossorigin="anonymous"> -->
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Roboto&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="/static/style.css">
    <title><?= $title ?></title>
</head>

<body>
    <?php require_once(ROOT . "views/layout/navbar.php"); ?>
    <div class="container">
        <?= $content ?>
    </div>

</body>

</html>

<script>
    const prefersDarkScheme = window.matchMedia("(prefers-color-scheme: dark)");
    const root = document.documentElement
    const switchBtn = document.querySelector(".darkToggle")

    function toggleDark() {
        if (root.classList.contains("light")) {
            root.classList.remove("light")
            root.classList.add("dark")
            switchBtn.innerText = "Light 🌞"
        } else if (root.classList.contains("dark")) {
            root.classList.remove("dark")
            root.classList.add("light")
            switchBtn.innerText = "Dark 🌙"


        } else {
            if (window.matchMedia && window.matchMedia('(prefers-color-scheme: dark)').matches) {
                root.classList.add("dark")
                switchBtn.innerText = "Light 🌞"

            } else {
                root.classList.add("light")
                switchBtn.innerText = "Dark 🌙"

            }
        }
    }

    toggleDark()
</script>