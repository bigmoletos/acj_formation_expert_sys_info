@echo off
setlocal EnableDelayedExpansion

:: Définition des couleurs
set "GREEN=[32m"
set "YELLOW=[33m"
set "RED=[31m"
set "BLUE=[34m"
set "NC=[0m"

:: Variables pour les chemins
set "APP_DIR=app"
set "TEMPLATES_DIR=%APP_DIR%\templates"
set "BLUEPRINTS_DIR=%APP_DIR%\blueprints"
set "SERVICES_DIR=%APP_DIR%\services\pollution"
set "PROJET_DIR=%SERVICES_DIR%\pollution"
set "STATIC_DIR=%APP_DIR%\static"
set "CSS_DIR=%STATIC_DIR%\css"
set "JS_DIR=%STATIC_DIR%\js"
set "DOCS_DIR=docs"
set "LOGS_DIR=logs"
set "TESTS_DIR=tests"

echo %BLUE%Creation de la structure du projet Temperature...%NC%

:: Création des dossiers
for %%D in (
    "%APP_DIR%"
    "%TEMPLATES_DIR%"
    "%STATIC_DIR%"
    "%CSS_DIR%"
    "%JS_DIR%"
    "%DOCS_DIR%"
    "%LOGS_DIR%"
    "%TESTS_DIR%"
) do (
    if not exist "%%D" (
        mkdir "%%D"
        echo %GREEN%Creation du dossier: %%D%NC%
    ) else (
        echo %YELLOW%Le dossier existe deja: %%D%NC%
    )
)

:: Création des fichiers
for %%F in (
    "%APP_DIR%\__init__.py"
    "%APP_DIR%\routes.py"
    "%APP_DIR%\models.py"
    "%APP_DIR%\forms.py"
    "%APP_DIR%\logging_config.py"
    "%TEMPLATES_DIR%\index.html"
    "%TEMPLATES_DIR%\weather.html"
    "%BLUEPRINTS_DIR%\routes.py"
    "%BLUEPRINTS_DIR%\__init__.py"
    "%SERVICES_DIR%\__init__.py"
    "%SERVICES_DIR%\openaq_client.py"
    "%CSS_DIR%\style.css"
    "%JS_DIR%\main.js"
    ".env"
    ".gitignore"
    "Dockerfile"
    "docker-compose.yml"
    "requirements.txt"
    "Makefile"
    "Doxyfile"
    "README.md"
    "ci-cd.yml"
    "%TESTS_DIR%\__init__.py"
    "%TESTS_DIR%\test_routes.py"
    "%TESTS_DIR%\test_models.py"
    "%TESTS_DIR%\conftest.py"
) do (
    if not exist "%%F" (
        type nul > "%%F"
        echo %GREEN%Creation du fichier: %%F%NC%
    ) else (
        echo %YELLOW%Le fichier existe deja: %%F%NC%
    )
)

echo.
echo %GREEN%Structure du projet creee avec succes!%NC%
echo.
echo %BLUE%Pour commencer a travailler sur le projet:%NC%
echo %GREEN%1. python -m venv venv%NC%
echo %GREEN%2. venv\Scripts\activate%NC%
echo %GREEN%3. pip install -r requirements.txt%NC%

endlocal
pause