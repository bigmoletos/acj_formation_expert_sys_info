document.addEventListener('DOMContentLoaded', function() {
    // Ajouter une animation de chargement pendant la recherche
    const form = document.querySelector('form');
    const submitBtn = form.querySelector('input[type="submit"]');

    form.addEventListener('submit', function() {
        submitBtn.value = 'Recherche en cours...';
        submitBtn.disabled = true;
    });
});
