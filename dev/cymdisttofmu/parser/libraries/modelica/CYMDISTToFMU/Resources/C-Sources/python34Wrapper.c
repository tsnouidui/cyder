/*  moduleName            - Name of the Python module.*/
/*  functionName          - Name of the Python function.*/
/*  inputFileName         - Name of the input file.*/
/*  nDblWri               - Number of inputs values to write.*/
/*  strWri                - Name of inputs to write.*/
/*  strTypWri             - Name of inputs types to write.*/
/*  strLocWri             - Name of inputs locations to write.*/
/*  dblValWri             - Double inputs values to write.*/
/*  nDblRea               - Number of outputs values to read.*/
/*  strRea                - Name of outputs to read.*/
/*  strLocRea             - Name of output locations to read.*/
/*  dblValRea             - Double outputs values to read.*/
/*  nDblParWri            - Number of parameters to write.*/
/*  strParWri             - Name of parameters to write.*/
/*  dblValParWri          - Double values of parameters to write.*/
/*  resWri                - Integer value to indicate if results should be written.*/
#include <ModelicaUtilities.h>

void pythonExchangeValuesCymdist(const char * moduleName,
								const char * functionName,
								const char * inputFileName,
								const size_t nDblWri, const char ** strWri,
								const char ** strTypWri, const char ** strLocWri,
								double * dblValWri, size_t nDblRea, const char ** strRea,
								const char ** strNodRea, double * dblValRea, size_t nDblParWri,
								const char ** strParWri, double * dblValParWri,
								const int * resWri)
{
  pythonExchangeValuesCymdistNoModelica(
   moduleName,
   functionName,
   inputFileName,
   nDblWri, strWri,
   strTypWri, strLocWri,
   dblValWri, nDblRea,
   strRea, strNodRea, dblValRea,
   nDblParWri, strParWri,
   dblValParWri, resWri,
   ModelicaFormatError
  );
}

