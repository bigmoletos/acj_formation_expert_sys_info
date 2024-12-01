##
# @file routes.py
# @brief Module de routage pour l'application de température
#
# @details Ce module gère les différentes routes de l'application Flask:
# - La page d'accueil avec le formulaire de connexion
# - La page de météo qui affiche la température pour une ville donnée
#
# @dependencies
# - Flask pour le routage web
# - requests pour les appels API OpenWeatherMap
##

from flask import render_template, request, redirect, url_for, flash
from flask_login import login_user, logout_user, login_required, current_user
from app import app, db, logger
from app.models import User
from app.forms import LoginForm
from app.logging_config import log_function_call, log_exception
import requests


##
# @brief Route de la page d'accueil
# @details Gère l'affichage du formulaire de connexion et son traitement
#
# @return Template HTML rendu avec le formulaire
##
@app.route('/login', methods=['GET', 'POST'])
def login():
    try:
        if current_user.is_authenticated:
            return redirect(url_for('weather'))

        form = LoginForm()
        if form.validate_on_submit():
            user = User.query.filter_by(username=form.username.data).first()
            if user and user.check_password(form.password.data):
                login_user(user)
                logger.info(f"Utilisateur connecté: {user.username}")
                return redirect(url_for('weather'))
            else:
                flash('Nom d\'utilisateur ou mot de passe incorrect')
                logger.warning(
                    f"Tentative de connexion échouée pour: {form.username.data}"
                )

        return render_template('index.html', form=form)
    except Exception as e:
        log_exception(logger, e, "Erreur dans la route login")
        flash("Une erreur est survenue. Veuillez réessayer.")
        return redirect(url_for('login'))


##
# @brief Route de la page d'accueil
# @details Gère l'affichage du formulaire de connexion et son traitement
#
# @return Template HTML rendu avec le formulaire
##
@app.route('/')
@app.route('/index')
def index():
    return redirect(url_for('login'))


##
# @brief Route pour afficher la météo d'une ville
# @details Récupère les données météorologiques via l'API OpenWeatherMap
#
# @param city Nom de la ville (via query parameter)
# @return Template HTML avec les données météo ou redirection
##
@app.route('/weather')
@login_required
def weather():
    try:
        city = request.args.get('city')
        if not city:
            return render_template('weather.html')

        api_key = app.config.get('OPENWEATHER_API_KEY')
        if not api_key:
            logger.error("Clé API OpenWeather non configurée")
            flash(
                "Erreur de configuration du service météo. Contactez l'administrateur."
            )
            return render_template('weather.html')

        try:
            response = requests.get(
                'http://api.openweathermap.org/data/2.5/weather',
                params={
                    'q': city,
                    'appid': api_key,
                    'units': 'metric',
                    'lang': 'fr'
                })

            if response.status_code == 401:
                logger.error("Clé API OpenWeather invalide")
                flash("Erreur d'authentification avec le service météo")
                return render_template('weather.html')

            response.raise_for_status()
            data = response.json()

            # Extraction des données
            temperature = data['main']['temp']
            description = data['weather'][0]['description']
            ville = data['name']
            coordinates = {
                'lat': data['coord']['lat'],
                'lon': data['coord']['lon']
            }

            logger.info(
                f"Données météo récupérées pour {ville}: {temperature}°C")

            return render_template('weather.html',
                                   temperature=temperature,
                                   city=ville,
                                   description=description,
                                   coordinates=coordinates)

        except requests.RequestException as e:
            logger.error(f"Erreur API météo pour {city}: {str(e)}")
            flash(
                "Impossible de récupérer les données météo. Veuillez réessayer avec un nom de ville valide."
            )
            return render_template('weather.html')

    except Exception as e:
        log_exception(logger, e, "Erreur dans la route weather")
        flash("Une erreur est survenue. Veuillez réessayer.")
        return render_template('weather.html')


##
# @brief Route pour déconnecter l'utilisateur
# @details Déconnecte l'utilisateur actuellement connecté
#
# @return Redirection vers la page d'accueil
##
@app.route('/logout')
@login_required
def logout():
    try:
        username = current_user.username
        logout_user()
        logger.info(f"Utilisateur déconnecté: {username}")
        flash('Vous avez été déconnecté')
        return redirect(url_for('login'))
    except Exception as e:
        log_exception(logger, e, "Erreur lors de la déconnexion")
        return redirect(url_for('login'))
