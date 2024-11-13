from datetime import datetime

# Fonction pour générer un fichier iCalendar manuellement
def generate_icalendar(events):
    ical_content = "BEGIN:VCALENDAR\nVERSION:2.0\nPRODID:-//Your Calendar//EN\n"

    for start_date, end_date, module, evaluation, code in events:
        dtstart = datetime.strptime(start_date, "%d/%m/%Y").strftime("%Y%m%d")
        dtend = datetime.strptime(end_date, "%d/%m/%Y").strftime("%Y%m%d")
        uid = f"{code}-{start_date}@example.com"

        ical_content += f"BEGIN:VEVENT\n"
        ical_content += f"UID:{uid}\n"
        ical_content += f"SUMMARY:{module}\n"
        ical_content += f"DESCRIPTION:Évaluation: {evaluation} - Code: {code}\n"
        ical_content += f"DTSTART;VALUE=DATE:{dtstart}\n"
        ical_content += f"DTEND;VALUE=DATE:{dtend}\n"
        ical_content += f"END:VEVENT\n"

    ical_content += "END:VCALENDAR"

    return ical_content

# Liste des événements à ajouter au calendrier
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
    ("13/11/2024", "18/11/2024", "C VERS C++ 11 code: 1181", "18/11/2024",
     "1181"),
    ("19/11/2024", "19/11/2024",
     "INTRODUCTION A DOCKER ET AUX CONTENEURS code: 3203", "19/11/2024",
     "3203"),
    ("20/11/2024", "03/12/2024", "PYTHON ET MACHINE LEARNING code: 3299",
     "03/12/2024", "3299"),
    ("04/12/2024", "04/12/2024", "SQLITE code: 6781", "04/12/2024", "6781"),
    ("05/12/2024", "05/12/2024", "AGILE TDD code: 2527", "05/12/2024", "2527"),
    ("06/12/2024", "10/12/2024", "BIG DATA code: 9380 ", "10/12/2024", "9380"),
    ("11/12/2024", "11/12/2024", "PRÉSENTER SES NOUVELLES COMPÉTENCES code: 6798",
     "11/12/2024", "6798"),
    ("12/12/2024", "18/12/2024",
     "PROJET FINAL & SOUTENANCE - APPLICATION code: 3715", "18/12/2024", "3715"),
]

# Génération du contenu iCalendar
ical_content = generate_icalendar(events)

# Écriture du contenu dans un fichier .ics
file_path = 'calendrier_session_filtered2.ics'
with open(file_path, 'w') as f:
    f.write(ical_content)

file_path
