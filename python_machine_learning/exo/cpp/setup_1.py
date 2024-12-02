# code Python
from setuptools import setup, Extension

module = Extension("factorielle_module", sources=["factorielle_module.c"])

setup(name="factorielle_module",
      version="1.0",
      description="Module C pour calculer la factorielle",
      ext_modules=[module])
