<style>
    h1 {
        padding: 0;
        margin: 0;
    }

    h3 {
        margin-bottom: 1rem;
    }
</style>

<h1><?= $data['article']['title'] ?></h1>
<h3>- <?= $data['article']['author'] ?></h3>
<p><?= $data['article']['body'] ?></p>