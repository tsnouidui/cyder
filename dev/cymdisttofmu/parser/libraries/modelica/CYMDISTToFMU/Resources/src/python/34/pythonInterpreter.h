#ifndef _PYTHONINTERPRETER_H_
#define _PYTHONINTERPRETER_H_
/*////////////////////////////////////////////////////////////////////////////*/
/* Function that evaluates a Python function using*/
/* embedded Python.*/
/* The Python function must take as an argument one or more doubles, integers*/
/* and strings, in this order. If there is only one argument of each data type,*/
/* then it must be a scalar. Multiple arguments of the same data type*/
/* must be put in a list.*/
/**/
/* See the User's Guide of the Modelica package for instructions.*/
/**/
/* The PYTHONPATH must point to the directory that contains the function.*/
/* On Linux, run for example*/
/* export PYTHONPATH=xyz*/
/* where xyz is the directory that contains the file that implements the*/
/* function multiply.*/
/**/
/**/
/* First Implementation: Michael Wetter, LBNL, 1/31/2013*/
/* Modified: Thierry S. Nouidui, LBNL, 3/26/2013 to suport cross compilation*/
/* Modified: Thierry S. Nouidui, LBNL, 3/2/2017 for CYMDIST to FMU*/
/* svn-id=$Id: exchangeValues.c 2877 2011-09-11 00:46:02Z mwetter $*/
/*////////////////////////////////////////////////////////////////////////////*/
#include <stddef.h>  /* stddef defines size_t */

#ifdef __APPLE__
#include <Python/Python.h>
#else
#include <Python.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _MSC_VER
#ifdef EXTERNAL_FUNCTION_EXPORT
# define LBNLPYTHONINTERPRETER_EXPORT __declspec( dllexport )
#else
# define LBNLPYTHONINTERPRETER_EXPORT __declspec( dllimport )
#endif
#elif __GNUC__ >= 4
/* In gnuc, all symbols are by default exported. It is still often useful,
to not export all symbols but only the needed ones */
# define LBNLPYTHONINTERPRETER_EXPORT __attribute__ ((visibility("default")))
#else
# define LBNLPYTHONINTERPRETER_EXPORT
#endif

/* Exchange values with Cymdist.*/
/* Any argument that starts with 'n', such as nDblWri, may be zero.*/
/* If there is an error, then this function calls*/
/* ModelicaFormatError(...) which terminates the computation.*/
/**/
/* The arguments are as follows:*/
/*  moduleName            - Name of the Python module.*/
/*  functionName          - Name of the Python function.*/
/*  configFileName        - Name of the configuration file.*/
/*  modTim                - Model time.*/
/*  nDblWri               - Number of inputs values to write.*/
/*  strWri                - Name of inputs to write.*/
/*  dblValWri             - Double inputs values to write.*/
/*  nDblRea               - Number of outputs values to read.*/
/*  strRea                - Name of outputs to read.*/
/*  dblValRea             - Double outputs values to read.*/
/*  nDblParWri            - Number of parameters to write.*/
/*  strParWri             - Name of parameters to write.*/
/*  dblValParWri          - Double values of parameters to write.*/
/*  resWri                - Integer value to indicate if results should be written.*/
/*  inModelicaFormatError - Pointer to ModelicaFormatError*/
LBNLPYTHONINTERPRETER_EXPORT void pythonExchangeValuesCymdistNoModelica(const char * moduleName,
							const char * functionName, 
							const char * configFileName,
							double * modTim,
							const size_t nDblWri, 
							const char ** strWri,
							double * dblValWri, 
							size_t nDblRea, 
							const char ** strRea,
							double * dblValRea, size_t nDblParWri,
							const char ** strParWri, 
							double * dblValParWri, 
							double * resWri,
							void(*inModelicaFormatError)(const char *string, ...));

#ifdef __cplusplus
}
#endif


#endif /* _PYTHONINTERPRETER_H_ */

