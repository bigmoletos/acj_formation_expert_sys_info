"""Modèles de données pour l'application."""
from dataclasses import dataclass
from typing import List, Optional


@dataclass
class Sensor:
    """Représente un capteur de pollution."""
    parameter: str
    unit: str
    value: float
    last_updated: str


@dataclass
class Location:
    """Représente une station de mesure de pollution."""
    id: int
    name: str
    city: str
    country: str
    latitude: float
    longitude: float
    sensors: List[Sensor]
