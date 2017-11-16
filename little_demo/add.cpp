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

	PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pRet;

	
	pName = PyUnicode_DecodeFSDefault("evaluate");
	
	pModule = PyImport_Import(pName);
	if ( !pModule ){
		return -1;
	}
	pDict = PyModule_GetDict(pModule);
	if ( !pDict ){
		return -1;
	}
	pFunc = PyDict_GetItemString(pDict, "addition");
	if ( !pFunc || !PyCallable_Check(pFunc) ){
		return -1;
	}

	long arr1[5] = {1, 3, 5, 7, 9};
	long arr2[5] = {2, 4, 6, 8, 10};
	long total = 0;


	pArgs = PyTuple_New(2);  // create a tuple which has two elements

	for( int i = 0; i < 5; ++i ){

		//PyLong_AsLong for python3.x
		//PyInt_AsLong for python2.x

		PyObject* arg1 = PyLong_FromLong(arr1[i]);    // set para1 
		PyObject* arg2 = PyLong_FromLong(arr2[i]);    // set para2 
		PyTuple_SetItem(pArgs, 0, arg1);              // set tuple 
		PyTuple_SetItem(pArgs, 1, arg2);

		printf(" ===========> START CALL PYTHON SCRIPT %d <===========\n", i + 1);
		pRet = PyObject_CallObject(pFunc, pArgs);     // call the function
		printf(" ===========> CALLING FINISHED  %d <===========\n", i + 1);

		long result = PyLong_AsLong(pRet);            // get the return value by pRet
		printf(" ===========> result = %ld <===========\n", result);

		total += result;
	}

	printf(" ===========> total = %ld <===========\n", total);

	Py_DECREF(pName);
	Py_DECREF(pModule);
	Py_DECREF(pArgs);
	Py_DECREF(pRet);
	Py_DECREF(pDict);

	// close Python
	Py_Finalize();
    return 0;
}

/*
bg@bg-cgi:~/Desktop/C_python/little_demo$ make all
g++ -std=c++11 -Wall -O3 add.cpp -lpython3.5m -L/usr/include/python3.5m/ -I/usr/include/python3.5m/ -o add
bg@bg-cgi:~/Desktop/C_python/little_demo$ ./add 
 ===========> START CALL PYTHON SCRIPT 1 <===========
 ===========> CALLING FINISHED  1 <===========
 ===========> result = 3 <===========
 ===========> START CALL PYTHON SCRIPT 2 <===========
 ===========> CALLING FINISHED  2 <===========
 ===========> result = 7 <===========
 ===========> START CALL PYTHON SCRIPT 3 <===========
 ===========> CALLING FINISHED  3 <===========
 ===========> result = 11 <===========
 ===========> START CALL PYTHON SCRIPT 4 <===========
 ===========> CALLING FINISHED  4 <===========
 ===========> result = 15 <===========
 ===========> START CALL PYTHON SCRIPT 5 <===========
 ===========> CALLING FINISHED  5 <===========
 ===========> result = 19 <===========
 ===========> total = 55 <===========
*/