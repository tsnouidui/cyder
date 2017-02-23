#include "testProgram.h"

void ModelicaFormatError(const char* string, const char* fmt, const char* val){
  fprintf(stderr, string, fmt, val);
  fprintf(stderr, "\n");
  exit(1);
}

int main(int nArgs, char ** args){
  
  /* Parameters for testing cymdist interface*/
  const char * moduleName = "testCymdist";
  const char * functionName = "r1_r1";
  const char * inputFileName = "cymdist.inp";
  
  size_t nDblWri = 1;
  double dblValWri[] = {15.0};
  const char *strWri[] = {"u"};
  const char *strTypWri[] = {"typ"};
  const char *strLocWri[] = {"loc"};
  
  size_t nDblRea = 1;
  double dblValRea[1];
  const char *strRea[] = {"y"};
  const char *strLocRea[] = {"loc"};
  
  size_t nDblParWri = 0;
  const char * strParWri[] = {""};
  int dblValParWri[] = {0};
  int resWri = 0;

  int i;
  
  for(i=0; i < 10; i++){
	  printf("Calling with i for cymdist = %d.\n", i);
	  pythonExchangeValuesCymdistNoModelica(moduleName,
		  functionName, inputFileName,
		  nDblWri, strWri, strTypWri, strLocWri, 
		  dblValWri, nDblRea, strRea, strLocRea, 
		  dblValRea, nDblParWri, strParWri, 
		  dblValParWri, resWri,
		  ModelicaFormatError);
  }

  return 0;
}

