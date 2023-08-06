// Copyright (c) Meta Platforms, Inc. and affiliates. (http://www.meta.com)
// Originally authored by Matthias Braun.
#include <Python.h>

#include "valgrind/callgrind.h"
#include "valgrind/memcheck.h"

// --- callgrind ---

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


// --- memcheck ---

static PyObject* memcheck_do_leak_check(PyObject* self) {
  VALGRIND_DO_LEAK_CHECK;
  Py_RETURN_NONE;
}

static PyObject* memcheck_do_added_leak_check(PyObject* self) {
  VALGRIND_DO_ADDED_LEAK_CHECK;
  Py_RETURN_NONE;
}

static PyObject* memcheck_do_changed_leak_check(PyObject* self) {
  VALGRIND_DO_CHANGED_LEAK_CHECK;
  Py_RETURN_NONE;
}

static PyObject* memcheck_count_leaks(PyObject* self) {
  int leaked, dubious, reachable, suppressed;
  VALGRIND_COUNT_LEAKS(leaked, dubious, reachable, suppressed);
  return Py_BuildValue("(iiii)", leaked, dubious, reachable, suppressed);
}

static PyObject* memcheck_count_leak_blocks(PyObject* self) {
  int leaked, dubious, reachable, suppressed;
  VALGRIND_COUNT_LEAK_BLOCKS(leaked, dubious, reachable, suppressed);
  return Py_BuildValue("(iiii)", leaked, dubious, reachable, suppressed);
}

static const char* const memcheck_do_leak_check_doc =
  "does a full memory leak check (like --leak-check=full) right now. "
  "This is useful for incrementally checking for leaks between arbitrary "
  "places in the program's execution. It has no return value.";

static const char* const memcheck_do_added_leak_check_doc =
  "same as VALGRIND_DO_LEAK_CHECK but only shows the entries for which "
  "there was an increase in leaked bytes or leaked number of blocks "
  "since the previous leak search. It has no return value.";

static const char* const memcheck_do_changed_leak_check_doc =
  "same as VALGRIND_DO_LEAK_CHECK but only shows the entries for "
  "which there was an increase or decrease in leaked bytes or leaked "
  "number of blocks since the previous leak search. It has no return value.";

static const char* const memcheck_count_leaks_doc =
  "fills in the four arguments with the number of bytes of memory found "
  "by the previous leak check to be leaked (i.e. the sum of direct leaks "
  "and indirect leaks), dubious, reachable and suppressed. This is "
  "useful in test harness code, after calling VALGRIND_DO_LEAK_CHECK "
  "or VALGRIND_DO_QUICK_LEAK_CHECK.";

static const char* const memcheck_count_leak_blocks_doc =
  "identical to VALGRIND_COUNT_LEAKS except that it returns the number "
  "of blocks rather than the number of bytes in each category.";


// --- python module initialization ---

static PyMethodDef valgrind_methods[] = {
    // callgrind
    {"callgrind_dump_stats", (PyCFunction)callgrind_dump_stats, METH_VARARGS,
     NULL},
    {"callgrind_start_instrumentation",
     (PyCFunction)callgrind_start_instrumentation, METH_NOARGS, NULL},
    {"callgrind_stop_instrumentation",
     (PyCFunction)callgrind_stop_instrumentation, METH_NOARGS, NULL},
    {"callgrind_zero_stats", (PyCFunction)callgrind_zero_stats, METH_NOARGS,
     NULL},
    // memcheck
    {
      "memcheck_do_leak_check",
      (PyCFunction)memcheck_do_leak_check,
      METH_NOARGS,
      memcheck_do_leak_check_doc,
    },
    {
      "memcheck_do_added_leak_check",
      (PyCFunction)memcheck_do_added_leak_check,
      METH_NOARGS,
      memcheck_do_added_leak_check_doc,
    },
    {
      "memcheck_do_changed_leak_check",
      (PyCFunction)memcheck_do_changed_leak_check,
      METH_NOARGS,
      memcheck_do_changed_leak_check_doc,
    },
    {
      "memcheck_count_leaks",
      (PyCFunction)memcheck_count_leaks,
      METH_NOARGS,
      memcheck_count_leaks_doc,
    },
    {
      "memcheck_count_leak_blocks",
      (PyCFunction)memcheck_count_leak_blocks,
      METH_NOARGS,
      memcheck_count_leak_blocks_doc,
    },
    // end of list
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef valgrindmodule = {PyModuleDef_HEAD_INIT, "valgrind",
                                             NULL, -1, valgrind_methods};

PyMODINIT_FUNC PyInit_valgrind(void) {
  PyObject* m = PyState_FindModule(&valgrindmodule);
  if (m != NULL) {
    Py_INCREF(m);
    return m;
  }
  m = PyModule_Create(&valgrindmodule);
  if (m == NULL) {
    return NULL;
  }
  PyState_AddModule(m, &valgrindmodule);
  return m;
}
