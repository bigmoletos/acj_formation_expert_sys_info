import unittest
from unittest.mock import patch, MagicMock
import requests
from openaq_client import OpenAQLocationFetcher


class TestOpenAQLocationFetcher(unittest.TestCase):

    def setUp(self):
        self.api_key = "fake_api_key"
        self.fetcher = OpenAQLocationFetcher(self.api_key)

    def test_init_without_api_key(self):
        with self.assertRaises(ValueError):
            OpenAQLocationFetcher("")

    @patch("openaq_client.requests.get")
    def test_fetch_location_data_success(self, mock_get):
        # Simuler une réponse réussie
        mock_response = MagicMock()
        mock_response.json.return_value = {"results": [{"id": 1234}]}
        mock_response.raise_for_status.return_value = None
        mock_get.return_value = mock_response

        data = self.fetcher.fetch_location_data(1234)
        self.assertIn("results", data)
        self.assertEqual(data["results"][0]["id"], 1234)

    @patch("openaq_client.requests.get")
    def test_fetch_location_data_http_error(self, mock_get):
        """!
        \brief Test la gestion des erreurs HTTP lors de la récupération des données
        """
        # Simuler une erreur HTTP
        mock_response = MagicMock()
        mock_response.raise_for_status.side_effect = requests.exceptions.HTTPError(
            "HTTP Error")
        mock_get.return_value = mock_response

        with self.assertRaises(ValueError) as context:
            self.fetcher.fetch_location_data(9999)
        self.assertIn("HTTP", str(context.exception))
        self.assertIn("HTTP", str(context.exception))

    @patch("openaq_client.requests.get")
    def test_fetch_location_data_no_data(self, mock_get):
        # Simuler une réponse vide
        mock_response = MagicMock()
        mock_response.json.return_value = {}
        mock_response.raise_for_status.return_value = None
        mock_get.return_value = mock_response

        with self.assertRaises(ValueError) as context:
            self.fetcher.fetch_location_data(9999)
        self.assertIn("Données introuvables", str(context.exception))


if __name__ == '__main__':
    unittest.main()
