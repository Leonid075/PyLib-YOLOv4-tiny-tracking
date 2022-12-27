#include <Python.h>
#include "demo.h"
#include "list.h"
#include <stdlib.h>
#include "darknet.h"
#include "network.h"
#include "region_layer.h"
#include "cost_layer.h"
#include "utils.h"
#include "parser.h"
#include "box.h"
#include "option_list.h"

static PyObject* spam_system(PyObject* self, PyObject* args)
{
  char* cfg;
  char* datacfg;
  char* weights;
  float thresh;
  char* filename;
  char* out_filename;
  int dontdraw_bbox;

  PyArg_ParseTuple(args,"sssfssi", &cfg, &datacfg, &weights, &thresh, &filename, &out_filename, &dontdraw_bbox);
  int classes = option_find_int(read_data_cfg(datacfg), "classes", 20);
  demo(cfg, weights, thresh, .5, 0, filename, 0, classes, 3, 0, 0, out_filename, -1, dontdraw_bbox, -1, 1, 0, 0, 0, 0, 0, 0);

  PyObject* out = PyTuple_New(Py_ssize_t(6));
  for (int i = 0; i < 6; i++) {
      PyTuple_SetItem(out, Py_ssize_t(i), PyLong_FromLong(detections[i]));
  }
  return out;
}

static PyMethodDef SpamMethods[] = {
    {"system",  spam_system, METH_VARARGS,
     "Execute a shell command."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef spammodule = {
    PyModuleDef_HEAD_INIT,
    "spam",//module name
    NULL,
    -1,
    SpamMethods//methods
};

static PyObject* SpamError;
PyMODINIT_FUNC
PyInit_spam(void)
{
    PyObject* m;

    m = PyModule_Create(&spammodule);
    if (m == NULL)
        return NULL;

    return m;
}