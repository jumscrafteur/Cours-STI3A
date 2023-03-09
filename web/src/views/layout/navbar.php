<div class="nav">
    <div class="left">
        <a href="/">Home</a>
        <?php if ($_SESSION["user"]) { ?>
            <a href="/logout">LogOut</a>
        <?php } else { ?>
            <a href="/signin">Signin</a>
            <a href="/login">LogIn</a>
        <?php } ?>
    </div>
    <div class="right">
        <button onClick="toggleDark()" class="darkToggle">dark</button>
    </div>
</div>