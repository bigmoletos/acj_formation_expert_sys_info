from setuptools import setup, find_packages

setup(
    name="ma_bibliotheque",
    version="0.1",
    packages=find_packages(),
    install_requires=[
        "numpy>=1.18.0",
        "pandas>=1.0.0",
    ],
)
