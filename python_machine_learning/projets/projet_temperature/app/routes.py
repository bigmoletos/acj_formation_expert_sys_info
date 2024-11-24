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
@app.route('/', methods=['GET', 'POST'])
@log_function_call(logger)
def index():
    try:
        form = LoginForm()
        if form.validate_on_submit():
            logger.info(
                f"Tentative de connexion pour l'utilisateur: {form.username.data}"
            )
            return redirect(url_for('weather'))
        return render_template('index.html', form=form)
    except Exception as e:
        log_exception(logger, e, "Erreur dans la route index")
        flash("Une erreur est survenue. Veuillez réessayer.")
        return redirect(url_for('index'))


##
# @brief Route pour afficher la météo d'une ville
# @details Récupère les données météorologiques via l'API OpenWeatherMap
#
# @param city Nom de la ville (via query parameter)
# @return Template HTML avec les données météo ou redirection
##
@app.route('/weather', methods=['GET'])
@log_function_call(logger)
def weather():
    try:
        city = request.args.get('city')
        if not city:
            logger.warning("Tentative d'accès à /weather sans paramètre city")
            return redirect(url_for('index'))

        try:
            response = requests.get(
                f'http://api.openweathermap.org/data/2.5/weather?q={city}&appid=YOUR_API_KEY&units=metric'
            )
            response.raise_for_status()

            data = response.json()
            temperature = data['main']['temp']
            logger.info(
                f"Données météo récupérées pour {city}: {temperature}°C")

            return render_template('weather.html',
                                   temperature=temperature,
                                   city=city)

        except requests.RequestException as e:
            logger.error(f"Erreur API météo pour {city}: {str(e)}")
            flash(
                "Impossible de récupérer les données météo. Veuillez réessayer."
            )
            return redirect(url_for('index'))

    except Exception as e:
        log_exception(logger, e, "Erreur dans la route weather")
        flash("Une erreur est survenue. Veuillez réessayer.")
        return redirect(url_for('index'))
