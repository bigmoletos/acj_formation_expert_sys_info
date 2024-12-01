from flask import Blueprint, render_template, request, redirect, url_for

bp = Blueprint('main', __name__)


@bp.route('/')
def index():
    return redirect(url_for('main.login'))


@bp.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        return redirect(url_for('main.weather'))
    return render_template('index.html')


@bp.route('/weather')
def weather():
    return render_template('weather.html')


@bp.route('/logout')
def logout():
    return redirect(url_for('main.login'))
