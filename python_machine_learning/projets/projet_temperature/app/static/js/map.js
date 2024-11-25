document.addEventListener('DOMContentLoaded', function() {
    // Vérifie si les coordonnées sont disponibles
    const coordinates = document.getElementById('coordinates');
    if (!coordinates) return;

    // Récupère les données
    const lat = parseFloat(coordinates.dataset.lat);
    const lon = parseFloat(coordinates.dataset.lon);
    const temp = coordinates.dataset.temp;
    const city = coordinates.dataset.city;

    // Crée la carte centrée sur la ville
    const map = L.map('map').setView([lat, lon], 10);

    // Ajoute la couche OpenStreetMap
    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
        attribution: '© OpenStreetMap contributors'
    }).addTo(map);

    // Crée une icône personnalisée pour le marqueur
    const customIcon = L.divIcon({
        className: 'custom-marker',
        html: `<div class="marker-content">
                <div class="temperature-flag">${temp}°C</div>
                <div class="city-name">${city}</div>
               </div>`,
        iconSize: [60, 40],
        iconAnchor: [30, 40]
    });

    // Ajoute le marqueur avec l'icône personnalisée
    L.marker([lat, lon], {icon: customIcon}).addTo(map);
});