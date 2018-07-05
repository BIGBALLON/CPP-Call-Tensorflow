#include <Python.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]){

	Py_Initialize();
	if( !Py_IsInitialized() ){
		printf("Initialize failed\n");
		return -1;
	}
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");

	PyObject *pName,*pModule,*pDict,*pFunc;
	
	// PyString_FromString for python2.x
	// PyUnicode_DecodeFSDefault for python3.x
	pName = PyUnicode_DecodeFSDefault("vgg_model");
	
	pModule = PyImport_Import(pName);
	if ( !pModule ){
		printf("Can't find Module\n");
		PyErr_Print();
		return -1;
	}
	pDict = PyModule_GetDict(pModule);
	if ( !pDict ){
		return -1;
	}
	pFunc = PyDict_GetItemString(pDict, "predict");
	if ( !pFunc || !PyCallable_Check(pFunc) ){
		printf("can't find function [predict]\n");
		return -1;
	}


	printf(" ===========> START CALL PYTHON SCRIPT <===========\n");

	printf(" ===========> 1st CALL <===========\n");
	PyObject_CallObject(pFunc,NULL);
	printf(" ===========> 2nd CALL <===========\n");
	PyObject_CallObject(pFunc,NULL);
	printf(" ===========> 3rd CALL <===========\n");
	PyObject_CallObject(pFunc,NULL);
	printf(" ===========> 4th CALL <===========\n");
	PyObject_CallObject(pFunc,NULL);

	printf(" ===========> CALLING FINISHED <===========\n");

	Py_DECREF(pName);
	Py_DECREF(pModule);

	// close Python
	Py_Finalize();
    return 0;
}