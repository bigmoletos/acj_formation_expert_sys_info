from flask import Blueprint, render_template, request, redirect, url_for, flash, current_app
from flask_login import login_user, logout_user, login_required, current_user
from app.extensions import db
from app.models import User, CitySearch
from app.forms import LoginForm, RegistrationForm
from bs4 import BeautifulSoup
import logging
import requests
import os

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
@main.route('/docs/')
@login_required
def docs():
    """Affiche la documentation générée dans une iframe"""
    try:
        # Chemin absolu vers le fichier index.html de Doxygen
        docs_path = os.path.join(current_app.root_path, 'templates',
                                 'docs/html/index.html')

        # Chemin absolu vers le fichier index.html généré par Doxygen
        docs_url = url_for('static', filename='docs/html/index.html')

        # Retourne la page avec une iframe pointant vers le fichier généré
        return render_template('docs.html', docs_url=docs_url)
    except Exception as e:
        logger.error(f"Erreur lors de l'accès à la documentation: {str(e)}")
        flash(
            "Une erreur est survenue lors du chargement de la documentation.")
        return render_template('docs.html', docs_url=None)


# @main.route('/docs')
# @main.route('/docs/')
# @login_required
# def docs():
#     """Affiche la documentation générée ou un fallback par défaut"""
#     try:
#         # Chemin absolu vers le fichier index.html de Doxygen
#         docs_path = os.path.join(current_app.root_path, 'templates',
#                                  'docs/html/index.html')

#         # Vérifier la présence du fichier
#         if os.path.exists(docs_path):
#             with open(docs_path, 'r', encoding='utf-8') as f:
#                 doxygen_content = f.read()
#             return render_template('docs.html',
#                                    doxygen_content=doxygen_content)
#         else:
#             logger.warning("Fichier index.html de Doxygen introuvable.")
#             flash(
#                 "La documentation générée est indisponible. Une version de secours est affichée."
#             )
#             return render_template('docs.html', doxygen_content=None)
#     except Exception as e:
#         logger.error(
#             f"Erreur lors du chargement de la documentation : {str(e)}")
#         flash(
#             "Une erreur est survenue lors du chargement de la documentation.")
#         return render_template('docs.html', doxygen_content=None)

# @main.route('/docs')
# @main.route('/docs/')
# @login_required
# def docs():
#     """Affiche la documentation générée avec les headers et footers"""
#     try:
#         # Chemin absolu vers le fichier index.html généré par Doxygen
#         docs_path = os.path.join(current_app.root_path, 'templates',
#                                  'docs/html/index.html')

#         # Vérifier l'existence du fichier
#         if not os.path.exists(docs_path):
#             flash("La documentation n'est pas encore générée.")
#             return render_template(
#                 'docs.html',
#                 doxygen_content=
#                 "<p>Aucune documentation disponible. Veuillez la générer.</p>")

#         # Lire le contenu de la documentation générée
#         with open(docs_path, 'r', encoding='utf-8') as f:
#             doxygen_content = f.read()

#         # Retourner le contenu dans le layout principal
#         return render_template('docs.html', doxygen_content=doxygen_content)

#     except Exception as e:
#         logger.error(f"Erreur lors de l'accès à la documentation: {str(e)}")
#         flash(
#             "Une erreur est survenue lors du chargement de la documentation.")
#         return render_template(
#             'docs.html',
#             doxygen_content=
#             "<p>Erreur lors du chargement de la documentation.</p>")

# @main.route('/docs')
# @main.route('/docs/')
# @login_required
# def docs():
#     """Affiche la documentation générée dans le layout global"""
#     try:
#         # Chemin absolu vers le fichier index.html généré par Doxygen
#         docs_path = os.path.join(current_app.root_path, 'templates',
#                                  'docs/html/index.html')
#         with open(docs_path, 'r', encoding='utf-8') as f:
#             doxygen_content = f.read()
#         return render_template('docs.html', doxygen_content=doxygen_content)
#     except FileNotFoundError:
#         logger.error("Le fichier index.html de Doxygen est introuvable")
#         flash("La documentation n'est pas encore générée.")
#         return redirect(url_for('main.index'))
#     except Exception as e:
#         logger.error(f"Erreur lors de l'accès à la documentation: {str(e)}")
#         flash(
#             "Une erreur est survenue lors du chargement de la documentation.")
#         return redirect(url_for('main.index'))

# def docs():
#     return render_template('docs.html')



@main.route('/generate-docs')
@login_required
def generate_docs():
    try:
        # Logique pour générer la documentation
        flash('Documentation générée avec succès')
        return redirect(url_for('main.docs'))
    except Exception as e:
        current_app.logger.error(
            f"Erreur lors de la génération de la documentation: {str(e)}")
        flash('Erreur lors de la génération de la documentation')
        return redirect(url_for('main.docs'))


@main.route('/logout')
def logout():
    logout_user()
    return redirect(url_for('main.login'))
