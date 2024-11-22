#include <Python.h>

// Fonction C pour calculer la factorielle
unsigned long long factorielle(int n) {
    if (n <= 1) return 1;
    else return n * factorielle(n - 1);
}

// Fonction wrapper pour l’API Python
static PyObject* py_factorielle(PyObject* self, PyObject* args) {
    int n;
    if (!PyArg_ParseTuple(args, "i", &n)) {
        return NULL;
    }
    unsigned long long result = factorielle(n);
    return PyLong_FromUnsignedLongLong(result);
}

// Table des fonctions du module
static PyMethodDef FactorielleMethods[] = {
    {"factorielle", py_factorielle, METH_VARARGS, "Calcul de la factorielle en C"},
    {NULL, NULL, 0, NULL}
};

// Définition du module
static struct PyModuleDef factoriellemodule = {
    PyModuleDef_HEAD_INIT,
    "factorielle_module",
    "Module C pour calculer la factorielle",
    -1,
    FactorielleMethods
};

// Initialisation du module
PyMODINIT_FUNC PyInit_factorielle_module(void) {
    return PyModule_Create(&factoriellemodule);
}