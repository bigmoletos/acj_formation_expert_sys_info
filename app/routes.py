from flask import Blueprint, render_template, request, redirect, url_for, flash, jsonify
from flask_login import login_user, logout_user, login_required, current_user
from app import db, logger
from app.models import User
from app.forms import LoginForm
import requests

# Création du blueprint
bp = Blueprint('main', __name__)

print("Routes chargées!")  # Debug print


@bp.route('/')
def index():
    return redirect(url_for('main.login'))


@bp.route('/weather')
def weather():
    try:
        city = request.args.get('city')
        if not city:
            return render_template('weather.html')

        api_key = current_app.config.get('OPENWEATHER_API_KEY')
        if not api_key:
            logger.error("Clé API OpenWeather non configurée")
            return jsonify({'error': 'Configuration error'}), 500

        response = requests.get(
            'http://api.openweathermap.org/data/2.5/weather',
            params={
                'q': city,
                'appid': api_key,
                'units': 'metric',
                'lang': 'fr'
            })

        if response.status_code == 200:
            data = response.json()
            return render_template(
                'weather.html',
                temperature=data['main']['temp'],
                description=data['weather'][0]['description'],
                city=data['name'])
        else:
            return jsonify({'error': 'City not found'}), 404

    except Exception as e:
        logger.error(f"Erreur lors de la requête météo: {str(e)}")
        return jsonify({'error': str(e)}), 500


@bp.route('/docs')
def docs():
    try:
        return render_template('docs.html')
    except Exception as e:
        logger.error(f"Erreur d'accès à la documentation: {str(e)}")
        return jsonify({'error': 'Documentation not available'}), 500
