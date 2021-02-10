#ifndef SIM02_H
#define SIM02_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "StringUtils.h"
#include "ConfigAccess.h"
#include "MetaDataAccess.h"
#include "Log2File.h"



// Struct: Defines a Process Control Block structure
typedef enum
   {  NEW,
      READY,
      RUNNING,
      WAITING,
      EXIT,
   } pcbState;

typedef struct pcbType
   {
   // Time for this PCb to complete
   int procTime;
   int state;
   int pid;
   OpCodeType *mdPtr;
   struct pcbType *next;
   int rqMemory;
   } pcbType;


// Function delcarations:
void runSimulator(OpCodeType *mdData, ConfigDataType *configData, logOutType **outPut);
int setProcesses(OpCodeType *mdData, pcbType **headPtr, ConfigDataType *configData);
pcbType *createPCB(OpCodeType *mdData, int id);
pcbType *addPCB(pcbType *localPtr, pcbType *newNode);
void setReady(pcbType *headPtrPCB);
void displayDump(ConfigDataType *configData, logOutType **outPut,
   pcbType *headNodePtr, int ioTime, int procTime);
int calcProcTime(ConfigDataType *configPtr, OpCodeType *mdDataPtr);
void freeList(pcbType *headPtr);
void doIOThread(OpCodeType *mdDataPtr, int ioTime);
int memoryCheck(int value, int bound, pcbType *headPtr,
   OpCodeType *mdPtr, ConfigDataType *configData,
      logOutType **outPut);
void opCodeDisplay(logOutType **outPut, ConfigDataType *configData,
   OpCodeType *mdPtr, pcbType *headPtr,char concatChar);
void checkSchedCode(ConfigDataType *configData, logOutType **outPut, int processes,
  pcbType *headNodePtr, int schedCode, int ioTime, int processTime);


#endif //SIM02_H
