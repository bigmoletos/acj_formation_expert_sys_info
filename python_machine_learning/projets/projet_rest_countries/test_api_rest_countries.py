import requests


def get_country_info(country_name):
    """
    Récupérer les informations d'un pays via l'API REST Countries.
    :param country_name: Nom du pays (ex: "France")
    :return: Informations sur le pays ou un message d'erreur.
    """
    url = f"https://restcountries.com/v3.1/name/{country_name}"

    try:
        response = requests.get(url)
        response.raise_for_status()  # Vérifie si la requête est réussie
        data = response.json()
        return data
        # if data:
        #     country = data[0]
        #     return {
        #         "Nom": country.get("name", {}).get("common", "N/A"),
        #         "Capitale": country.get("capital", ["N/A"])[0],
        #         "Région": country.get("region", "N/A"),
        #         "Population": country.get("population", "N/A"),
        #         "Devises": ", ".join(country.get("currencies", {}).keys()),
        #         "Langues": ", ".join(country.get("languages", {}).values())
        #     }
        # else:
        #     return {"Erreur": "Aucun résultat trouvé"}
    except requests.exceptions.RequestException as e:
        return {"Erreur": str(e)}


if __name__ == "__main__":
    country_name = input("Entrez le nom d'un pays : ")
    info = get_country_info(country_name)
    print(info)
