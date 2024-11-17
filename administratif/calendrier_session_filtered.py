# import datetime
from datetime import datetime, timedelta, date


# Mise à jour de la liste des événements avec heures et gestion des jours fériés et week-ends
def generate_icalendar_with_times(events2):
    contenu_calendrier = "BEGIN:VCALENDAR\nVERSION:2.0\nPRODID:-//Your Calendar//EN\n"

    # Dates fériées en France pour la période concernée
    holidays = [
        date(2024, 11, 1),  # Toussaint
        date(2024, 11, 11),  # Armistice
        date(2024, 12, 24),  # Noel
        date(2025, 1, 1)  # jour de l'an
    ]

    for start_date, end_date, module, evaluation, code in events2:
        current_date = datetime.strptime(start_date, "%d/%m/%Y").date()
        end_date = datetime.strptime(end_date, "%d/%m/%Y").date()

        # Boucle sur chaque jour entre start_date et end_date
        while current_date <= end_date:
            # Vérification si c'est un week-end ou un jour férié
            if current_date.weekday() < 5 and current_date not in holidays:
                dtstart_am = current_date.strftime("%Y%m%dT090000")
                dtend_am = current_date.strftime("%Y%m%dT123000")
                dtstart_pm = current_date.strftime("%Y%m%dT133000")
                dtend_pm = current_date.strftime("%Y%m%dT170000")

                # Matin session
                contenu_calendrier += f"BEGIN:VEVENT\n"
                contenu_calendrier += f"UID:{code}-AM-{current_date}@example.com\n"
                contenu_calendrier += f"SUMMARY:{module}\n"
                contenu_calendrier += f"DESCRIPTION:Évaluation: {evaluation} - Code: {code}\n"
                contenu_calendrier += f"DTSTART;TZID=Europe/Paris:{dtstart_am}\n"
                contenu_calendrier += f"DTEND;TZID=Europe/Paris:{dtend_am}\n"
                contenu_calendrier += f"END:VEVENT\n"

                # Après-midi session
                contenu_calendrier += f"BEGIN:VEVENT\n"
                contenu_calendrier += f"UID:{code}-PM-{current_date}@example.com\n"
                contenu_calendrier += f"SUMMARY:{module}\n"
                contenu_calendrier += f"DESCRIPTION:Évaluation: {evaluation} - Code: {code}\n"
                contenu_calendrier += f"DTSTART;TZID=Europe/Paris:{dtstart_pm}\n"
                contenu_calendrier += f"DTEND;TZID=Europe/Paris:{dtend_pm}\n"
                contenu_calendrier += f"END:VEVENT\n"

            # Passage au jour suivant
            current_date += timedelta(days=1)

    contenu_calendrier += "END:VCALENDAR"

    return contenu_calendrier


# Événements à ajouter au calendrier avec nouvelles spécifications
# events = [
#     ("30/09/2024", "30/09/2024", "PRESENTATION LINUX", "30/09/2024", "6707"),
#     ("01/10/2024", "04/10/2024", "COMMANDE LINUX", "04/10/2024", "7568"),
#     ("07/10/2024", "07/10/2024", "GIT", "07/10/2024", "2131"),
#     ("08/10/2024", "09/10/2024", "RÔLE ET COMPORTEMENT DU CONSULTANT",
#      "09/10/2024", "2031"),
#     ("10/10/2024", "11/10/2024", "ALGORITHMIE", "11/10/2024", "6675"),
#     ("14/10/2024", "18/10/2024", "PROGRAMMATION C", "18/10/2024", "7387"),
#     ("21/10/2024", "22/10/2024", "INTRODUCTION A DOCKER ET AUX CONTENEURS",
#      "22/10/2024", "1039"),
#     ("23/10/2024", "25/10/2024", "C VERS C++ 11", "25/10/2024", "9015"),
#     ("28/10/2024", "29/10/2024", "INTRODUCTION A DOCKER ET AUX CONTENEURS",
#      "29/10/2024", "1983"),
#     ("30/10/2024", "31/10/2024", "C VERS C++ 11", "31/10/2024", "7836"),
#     ("04/11/2024", "04/11/2024", "C VERS C++ 11", "04/11/2024", "4839"),
#     ("05/11/2024", "12/11/2024", "GESTION DE PROJET", "12/11/2024", "9470"),
#     ("13/11/2024", "18/11/2024", "C VERS C++ 11", "18/11/2024", "1181"),
#     ("19/11/2024", "19/11/2024", "INTRODUCTION A DOCKER ET AUX CONTENEURS",
#      "19/11/2024", "3203"),
#     ("20/11/2024", "03/12/2024", "PYTHON ET MACHINE LEARNING", "03/12/2024",
#      "3299"),
#     ("04/12/2024", "04/12/2024", "SQLITE", "04/12/2024", "6781"),
#     ("05/12/2024", "05/12/2024", "AGILE TDD", "05/12/2024", "2527"),
#     ("06/12/2024", "10/12/2024", "BIG DATA", "10/12/2024", "9380"),
#     ("11/12/2024", "11/12/2024", "PRÉSENTER SES NOUVELLES COMPÉTENCES",
#      "11/12/2024", "6798"),
#     ("12/12/2024", "18/12/2024", "PROJET FINAL & SOUTENANCE - APPLICATION",
#      "18/12/2024", "3715"),
# ]

events = [
    # ("30/09/2024", "30/09/2024", "PRESENTATION LINUX", "30/09/2024", "6707"),
    # ("01/10/2024", "04/10/2024", "COMMANDE LINUX", "04/10/2024", "7568"),
    # ("07/10/2024", "07/10/2024", "GIT", "07/10/2024", "2131"),
    # ("08/10/2024", "09/10/2024", "RÔLE ET COMPORTEMENT DU CONSULTANT", "09/10/2024", "2031"),
    # ("10/10/2024", "11/10/2024", "ALGORITHMIE", "11/10/2024", "6675"),
    # ("14/10/2024", "18/10/2024", "PROGRAMMATION C", "18/10/2024", "7387"),
    # ("21/10/2024", "22/10/2024", "INTRODUCTION A DOCKER ET AUX CONTENEURS", "22/10/2024", "1039"),
    # ("23/10/2024", "25/10/2024", "C VERS C++ 11", "25/10/2024", "9015"),
    # ("28/10/2024", "29/10/2024", "INTRODUCTION A DOCKER ET AUX CONTENEURS", "29/10/2024", "1983"),
    # ("30/10/2024", "31/10/2024", "C VERS C++ 11", "31/10/2024", "7836"),
    # ("04/11/2024", "04/11/2024", "C VERS C++ 11", "04/11/2024", "4839"),
    # ("05/11/2024", "12/11/2024", "GESTION DE PROJET", "12/11/2024", "9470"),
    ("13/11/2024", "19/11/2024", "C VERS C++ 11 code: 1181", "18/11/2024",
     "1181"),
    # ("19/11/2024", "19/11/2024",
    #  "INTRODUCTION A DOCKER ET AUX CONTENEURS code: 3203", "19/11/2024",
    #  "3203"),
    ("20/11/2024", "03/12/2024", "PYTHON ET MACHINE LEARNING code: 3299",
     "03/12/2024", "3299"),
    ("04/12/2024", "04/12/2024", "SQLITE code: 6781", "04/12/2024", "6781"),
    ("05/12/2024", "05/12/2024", "AGILE TDD code: 2527", "05/12/2024", "2527"),
    ("06/12/2024", "10/12/2024", "BIG DATA code: 9380 ", "10/12/2024", "9380"),
    ("11/12/2024", "11/12/2024",
     "PRÉSENTER SES NOUVELLES COMPÉTENCES code: 6798", "11/12/2024", "6798"),
    ("12/12/2024", "18/12/2024",
     "PROJET FINAL & SOUTENANCE - APPLICATION code: 3715", "18/12/2024",
     "3715"),
]
#  Modif du planning pour le 19 novembre
# events2 = [
#     ("19/11/2024", "19/11/2024", "C VERS C++ 11 code: 4839", "19/11/2024",
#      "4839"),
#     ("20/11/2024", "03/12/2024", "PYTHON ET MACHINE LEARNING code: 3299",
#      "03/12/2024", "3299"),
#     ("04/12/2024", "04/12/2024", "SQLITE code: 6781"
#      "04/12/2024", "6781"),
#     ("(05/12/2024", "05/12/2024", "AGILE TDD code:  2527"
#      "05/12/2024", "2527"),
#     ("06/12/2024", "10/12/2024", "BIG DATA code: 9380"
#      "10/12/2024", "9380"),
#     ("11/12/2024", "11/12/2024",
#      "PRÉSENTER SES NOUVELLES COMPÉTENCES code: 6798", "11/12/2024", "6798"),
#     ("12/12/2024", "18/12/2024",
#      "PROJET FINAL & SOUTENANCE - APPLICATION code: 3715", "18/12/2024",
#      "3715")
# ]
events2 = [
    ("19/11/2024", "19/11/2024", "C VERS C++ 11 code: 4839",
     "Évaluation: 4839", "4839"),
    ("20/11/2024", "03/12/2024", "PYTHON ET MACHINE LEARNING code: 3299",
     "Évaluation: 3299", "3299"),
    ("04/12/2024", "04/12/2024", "SQLITE code: 6781", "Évaluation: 6781",
     "6781"),
    ("05/12/2024", "05/12/2024", "AGILE TDD code: 2527", "Évaluation: 2527",
     "2527"),
    ("06/12/2024", "10/12/2024", "BIG DATA code: 9380", "Évaluation: 9380",
     "9380"),
    ("11/12/2024", "11/12/2024",
     "PRÉSENTER SES NOUVELLES COMPÉTENCES code: 6798", "Évaluation: 6798",
     "6798"),
    ("12/12/2024", "18/12/2024",
     "PROJET FINAL & SOUTENANCE - APPLICATION code: 3715", "Évaluation: 3715",
     "3715"),
]

# Génération du contenu iCalendar avec les spécifications de temps et jours fériés
contenu_calendrier = generate_icalendar_with_times(events2)

# Écriture du contenu dans un fichier .ics
# file_path = '/mnt/data/calendar_events2_filtered.ics'
file_path = './administratif/calendar_events2_filtered.ics'
with open(file_path, 'w') as f:
    f.write(contenu_calendrier)

file_path
