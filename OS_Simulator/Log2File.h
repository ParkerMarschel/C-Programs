#include <stdio.h>
#include <stdlib.h>
#include "ConfigAccess.h"
#include "StringUtils.h"


typedef struct logOutType
    {
    char strBuffer[200];
    struct logOutType *next;
    } logOutType;

// Function Delcarations
void initLogDataList(ConfigDataType *configData, logOutType **outPut, char *logLine);
logOutType *addLine(logOutType *locPtr, logOutType *newLineNode);
void writeLogToFile(ConfigDataType *configData, logOutType *outHead);
char *setTimer(char *logLine);


