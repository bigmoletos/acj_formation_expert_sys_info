# mettre python à jour
python.exe -m pip install --upgrade pip

# Installer virtualenv
pip install virtualenv

# Créer un environnement virtuel
virtualenv envFlask
[text](../../../../../../WildCodeSchool/Formation_IA_DATA_nov2023/Projets/Projet2_NetFlix/Django/lancement_envi_virtuel_django.md)
# Activer l'environnement virtuel
.\envFlask\Scripts\activate

# Installer les packages
pip install flask pandas numpy plotly seaborn scikit-learn

# Enregistrer les packages installés dans un fichier requirements.txt
pip freeze > requirements.txt

# Installer les packages à partir du fichier requirements.txt
pip install -r requirements.txt


# lancer le fichier app.py
[Running] python -u "n:\programmation\WildCodeSchool\Formation_IA_DATA_nov2023\live_coding\flask\sauvegarde\app.py"
 * Serving Flask app 'app'
 * Debug mode: on
WARNING: This is a development server. Do not use it in a production deployment. Use a production WSGI server instead.
 * Running on http://127.0.0.1:5000
Press CTRL+C to quit
 * Restarting with watchdog (windowsapi)
 * Debugger is active!
 * Debugger PIN: 357-821-041
 *

# http://127.0.0.1:5000 sur le port 5000. Donc, l’URL serait http://localhost:5000 ou http://127.0.0.1:5000.

# pour arreter l'environnement virtuel
deactivate

# si besoin de désinstaller des prog
pip uninstall flask pandas numpy plotly seaborn scikit-learn

#  les templates par défaut doivent se trouver dans le repertoire à la racine de app.py dans un dossier templates
templates
