from flask import Blueprint, render_template, request, redirect, url_for
from app import db, logger

bp = Blueprint('main', __name__)


@bp.route('/')
def index():
    return redirect(url_for('main.login'))


@bp.route('/login')
def login():
    return render_template('index.html')


@bp.route('/weather')
def weather():
    return render_template('weather.html')
