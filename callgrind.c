#include <Python.h>

#include "valgrind/callgrind.h"

static PyObject* callgrind_dump_stats(PyObject* self, PyObject* args) {
  const char* description = NULL;
  if (!PyArg_ParseTuple(args, "|s", &description)) {
    return NULL;
  }

  if (description == NULL) {
    CALLGRIND_DUMP_STATS;
  } else {
    CALLGRIND_DUMP_STATS_AT(description);
  }
  Py_RETURN_NONE;
}

static PyObject* callgrind_start_instrumentation(PyObject* self) {
  CALLGRIND_START_INSTRUMENTATION;
  Py_RETURN_NONE;
}

static PyObject* callgrind_stop_instrumentation(PyObject* self) {
  CALLGRIND_STOP_INSTRUMENTATION;
  Py_RETURN_NONE;
}

static PyObject* callgrind_zero_stats(PyObject* self) {
  CALLGRIND_ZERO_STATS;
  Py_RETURN_NONE;
}

static PyMethodDef callgrind_methods[] = {
    {"callgrind_dump_stats", (PyCFunction)callgrind_dump_stats, METH_VARARGS,
     NULL},
    {"callgrind_start_instrumentation",
     (PyCFunction)callgrind_start_instrumentation, METH_NOARGS, NULL},
    {"callgrind_stop_instrumentation",
     (PyCFunction)callgrind_stop_instrumentation, METH_NOARGS, NULL},
    {"callgrind_zero_stats", (PyCFunction)callgrind_zero_stats, METH_NOARGS,
     NULL},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef callgrindmodule = {PyModuleDef_HEAD_INIT, "callgrind",
                                             NULL, -1, callgrind_methods};

PyMODINIT_FUNC PyInit_callgrind(void) {
  PyObject* m = PyState_FindModule(&callgrindmodule);
  if (m != NULL) {
    Py_INCREF(m);
    return m;
  }
  m = PyModule_Create(&callgrindmodule);
  if (m == NULL) {
    return NULL;
  }
  PyState_AddModule(m, &callgrindmodule);
  return m;
}
