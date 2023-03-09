<h1>Creer un utilisateur</h1>
<form action="/signin" method="post">
    <div>
        <label for="username">Username </label><br><input type="text" id="username" name="username">
    </div>
    <div>
        <label for="password">Password </label><br><input type="password" id="password" name="password">
    </div>
    <div>
        <label for="password2">Password Confirmation</label><br><input type="password" id="password2" name="password2">
    </div>
    <button type=" submit">ENVOYER</button>
</form>

<script>
    let password = document.querySelector("#password")
    let password2 = document.querySelector("#password2")

    password2.addEventListener("input", () => {
        if (password.value != password2.value) {
            password2.classList.add("error");
        } else {
            password2.classList.remove("error");
        }
    })
</script>