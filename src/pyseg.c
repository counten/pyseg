#include <Python.h>
#include "friso_API.h"
#include "friso.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

friso_t friso;
friso_config_t config;
friso_task_t task;
fstring __path__ = NULL, mode = NULL;

static int initSeg(char *path){
    printf("[PySeg] init from: %s\n", path);
    __path__ = path;
    if ( __path__ == NULL ) {
        println("Use default config.ini");
        __path__ = "./config.ini";
    }
    //initialize
    friso = friso_new();
    config = friso_new_config();
    if ( friso_init_from_ifile(friso, config, __path__) != 1 ) {
        printf("fail to initialize friso and config.\n");
        return -1;
    }
    switch ( config->mode ) {
    case __FRISO_SIMPLE_MODE__:
        mode = "Simple";
        break;
    case __FRISO_COMPLEX_MODE__:
        mode = "Complex";
        break;
    case __FRISO_DETECT_MODE__:
        mode = "Detect";
        break;
    }
    printf("[PySeg] Model:%s-Version: %s (%s)\n", mode, friso_version(), friso->charset == FRISO_UTF8 ? "UTF-8" : "GBK" );
    //set the task.
    task = friso_new_task();
    return 0;
}

static char * seg(char *line){
    // segment
    printf("[PySeg] seg line: %s\n",line);
    friso_set_text(task, line);
    char *result = (char*)malloc( 100 * sizeof(char));
    if(result == NULL)
    {
        printf("[PySeg] memory cannot be allocated\n");
    }
    else{
         int first = 1;
        while ((config->next_token(friso, config, task)) != NULL)
        {
            if (first == 1)
            {
                strcpy(result, task->token->word);
                first++;
            } else
            {
                strcat(result, ",");
                strcat(result, task->token->word);
            }
        }
    }
    return result;
}

//wrapper for python.
static PyObject *py_init_seg_with_conf(PyObject *self, PyObject* args){
   char * name = NULL;
   if(!PyArg_ParseTuple(args, "s", &name)) {
   	  return NULL;
   }
   int res = initSeg(name);
   return Py_BuildValue("i", res);
}

// inner config file and lexicon
static PyObject *py_init_seg(PyObject *self, PyObject* args){
   int res = initSeg(NULL);
   return Py_BuildValue("i", res);
}

static PyObject *py_seg(PyObject *self, PyObject* args){
   char * line = NULL;
   if(!PyArg_ParseTuple(args, "s", &line)) {
   	  return NULL;
   }
   char * res = seg(line);
   return Py_BuildValue("s", res);
}

/* Module method table */
static PyMethodDef pySegMethods[] = {
  {"init_seg", py_init_seg, METH_VARARGS, "init segmentor"},
  {"init_seg_with_conf", py_init_seg_with_conf, METH_VARARGS, "init segmentor with conf"},
  {"seg", py_seg, METH_VARARGS, "segment"},
  { NULL, NULL, 0, NULL}
};

/* Module structure */
static struct PyModuleDef pySegModule = {
  PyModuleDef_HEAD_INIT,
  "pyseg",           /* name of module */
  "A chinese seg module",  /* Doc string (may be NULL) */
  -1,                 /* Size of per-interpreter state or -1 */
  pySegMethods       /* Method table */
};

/* Module initialization function */
PyMODINIT_FUNC
PyInit_pyseg(void) {
  return PyModule_Create(&pySegModule);
}
