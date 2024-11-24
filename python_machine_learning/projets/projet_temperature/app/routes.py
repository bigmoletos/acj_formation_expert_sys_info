from flask import render_template, request, redirect, url_for, flash
from app import app, db
from app.models import User
from app.forms import LoginForm
import requests


@app.route('/', methods=['GET', 'POST'])
def index():
    form = LoginForm()
    if form.validate_on_submit():
        # Authentification de l'utilisateur
        return redirect(url_for('weather'))
    return render_template('index.html', form=form)


@app.route('/weather', methods=['GET'])
def weather():
    city = request.args.get('city')
    if city:
        # Remplacez 'YOUR_API_KEY' par votre clé API
        response = requests.get(
            f'http://api.openweathermap.org/data/2.5/weather?q={city}&appid=YOUR_API_KEY&units=metric'
        )
        data = response.json()
        temperature = data['main']['temp']
        return render_template('weather.html',
                               temperature=temperature,
                               city=city)
    return redirect(url_for('index'))
