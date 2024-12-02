from flask import Blueprint, render_template, request, redirect, url_for, flash, current_app
from flask_login import login_user, logout_user, login_required, current_user
from app.extensions import db
from app.models import User, CitySearch
from app.forms import LoginForm, RegistrationForm
import logging
import requests

logger = logging.getLogger(__name__)

main = Blueprint('main', __name__)


@main.route('/')
@main.route('/index')
def index():
    return redirect(url_for('main.login'))


@main.route('/login', methods=['GET', 'POST'])
def login():
    if current_user.is_authenticated:
        return redirect(url_for('main.weather'))

    form = LoginForm()
    if form.validate_on_submit():
        user = User.query.filter_by(username=form.username.data).first()
        if user is None or not user.check_password(form.password.data):
            flash('Invalid username or password')
            return redirect(url_for('main.login'))
        login_user(user)
        return redirect(url_for('main.weather'))

    return render_template('index.html', title='Sign In', form=form)


@main.route('/register', methods=['GET', 'POST'])
def register():
    if current_user.is_authenticated:
        return redirect(url_for('main.weather'))

    form = RegistrationForm()
    if form.validate_on_submit():
        user = User(username=form.username.data)
        user.set_password(form.password.data)
        db.session.add(user)
        db.session.commit()
        flash('Congratulations, you are now a registered user!')
        return redirect(url_for('main.login'))

    return render_template('register.html', title='Register', form=form)


@main.route('/weather')
@login_required
def weather():
    city = request.args.get('city', '')
    error = None
    temperature = None
    description = None
    coordinates = None

    if city:
        try:
            # Appel à l'API OpenWeather
            api_key = current_app.config['API_KEY_OPENWEATHER']
            url = f'http://api.openweathermap.org/data/2.5/weather?q={city}&appid={api_key}&units=metric'

            response = requests.get(url)
            if response.status_code == 200:
                data = response.json()
                temperature = round(data['main']['temp'], 1)
                description = data['weather'][0]['description']
                coordinates = {
                    'lat': data['coord']['lat'],
                    'lon': data['coord']['lon']
                }

                # Sauvegarder la recherche
                search = CitySearch(city_name=city,
                                    temperature=temperature,
                                    user_id=current_user.id)
                db.session.add(search)
                db.session.commit()
            else:
                error = "Ville non trouvée"
        except Exception as e:
            error = "Erreur lors de la recherche"
            current_app.logger.error(f"Erreur météo: {str(e)}")

    # Récupérer l'historique des recherches
    searches = CitySearch.query.filter_by(user_id=current_user.id)\
        .order_by(CitySearch.search_date.desc())\
        .limit(5)\
        .all()

    return render_template('weather.html',
                           city=city,
                           temperature=temperature,
                           description=description,
                           coordinates=coordinates,
                           error=error,
                           searches=searches)


@main.route('/admin')
@login_required
def admin():
    if not current_user.is_admin:
        flash('Access denied')
        return redirect(url_for('main.weather'))

    users = User.query.all()
    form = RegistrationForm()
    return render_template('admin.html', users=users, form=form)


@main.route('/docs')
@login_required
def docs():
    return render_template('docs.html')


@main.route('/logout')
def logout():
    logout_user()
    return redirect(url_for('main.login'))
