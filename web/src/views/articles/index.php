<h1>Liste de articles</h1>
<div class="articleContainer">
    <?php foreach ($data['articles'] as $article) : ?>
        <div class="card">
            <h2><?= $article['title'] ?></h2>
            <p><?= explode("\n", $article['body'])[0] ?></p>
            <a href="/posts/<?= $article['id'] ?>"> voir l'article</a>
        </div>
    <?php endforeach ?>
    <?php if (isset($_SESSION['user'])) { ?>
        <div class="card">
            <h2>Poster un article</h2>
            <form action="/posts" method="post">
                <div>
                    <label for="title">Titre </label><br><input type="text" id="title" name="title">
                </div>
                <div>
                    <label for="body">Body </label><br><textarea type="text" id="body" name="body" rows="7"></textarea>
                </div>
                <button type=" submit">ENVOYER</button>
            </form>
        </div>
    <?php } ?>
</div>