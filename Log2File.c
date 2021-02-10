/*
Author: Parker Marschel
File: Log2File.c
Class: CS_480
Project: simulator 03 
*/

// Preprocessor directives
#include "simtimer.h"
#include "ConfigAccess.h"
#include "simulator_432573.h"

/*
Function: initLogDataList()
Algorithm: Function makes call to start the timer and then
           checks for MONITOR, FILE, or BOTH and will place
           the given string from the parameter into a buffer
           and then into the struct buffer contained in the 
           newly created node that will be added to the linked
           list.
Precondition: Pointer to config data, character pointer to the passed
              in string, and pointer to a pointer to be retured back
              out to the main for later use.
*/
void initLogDataList(ConfigDataType *configData, logOutType **outPut, char *logLine)
{
    logOutType *locNodeHead = *outPut; //  pointless???? Try just declaring *locNodeHead
    // New line node to be added to linked list 
    logOutType *newLine = NULL;
    char strBuffer[MAX_STR_LEN];
    char *timerBuffer; // Make constant later

    // set the timer
        // function: setTimer()
    timerBuffer = setTimer(logLine);

    // Check for MONITOR, FILE, OR BOTH
    if(configData->logToCode == LOGTO_MONITOR_CODE 
            || configData->logToCode == LOGTO_BOTH_CODE)
    {
        // Print to the monitor
        printf( "    %s, %s\n", timerBuffer, logLine);
    }

    // Checks for FILE or BOTH 
    if(configData->logToCode == LOGTO_FILE_CODE 
            || configData->logToCode == LOGTO_BOTH_CODE)
    {
        // places the output string passed in with the time to buffer
        sprintf(strBuffer, "    %s, %s\n", timerBuffer, logLine);

        // Allocates memory for the new node right beofre use
        newLine = (logOutType *) malloc(sizeof(logOutType));
        // Copies the string in the local buffer to the struct buffer
        copyString(newLine->strBuffer, strBuffer);

        // Call addLine to set the head node of the list to the local head
        locNodeHead = addLine(locNodeHead, newLine);

        // Clear the data as it will not be used until another call to function
        free(newLine);

        // Dereference outPut and save the head node to it
        *outPut = locNodeHead;
    }

}

/*
Function: writeLogToFile()
Algorithm: Function creates a FILE type variable and opens
           the file passed in the parameter to it. Strings
           are then placed into the file in the order they 
           appear on the output. 
Precondition: Pointer to config data and head node pointer
*/

void writeLogToFile(ConfigDataType *configData, logOutType *outHead)
{
    // Declare variables
    FILE *fileAccessPtr;
    char strBuffer[MAX_STR_LEN];
    char displayString[MAX_STR_LEN];

    // Open file with a write only flag & store in FILE variable
    fileAccessPtr = fopen(configData->logToFileName, WRITE_ONLY_FLAG);

    fputs("===================================\n", fileAccessPtr);
    fputs("Simulator Log File Header\n\n", fileAccessPtr);

    // write all config data required to the file
        // Functions: sprintf(), fputs()
    sprintf(strBuffer, "File Name                      :%s\n", configData->logToFileName);
    fputs(strBuffer, fileAccessPtr);

    // Change enumerated value into string to display
        // Function: configCodeToString()
    configCodeToString(configData->cpuSchedCode, displayString); // Create function in StringUtils
    sprintf(strBuffer, "CPU Scheduling                 :%s\n", displayString);
    fputs(strBuffer, fileAccessPtr);

    sprintf(strBuffer, "Quantum Cycles                 :%d\n", configData->quantumCycles);
    fputs(strBuffer, fileAccessPtr);

    sprintf(strBuffer, "Memory Avaliable (KB)          :%ld\n", configData->memAvailable);
    fputs(strBuffer, fileAccessPtr);

    sprintf(strBuffer, "Process Cycles Rate (ms/cycle) :%d\n", configData->procCycleRate);
    fputs(strBuffer, fileAccessPtr);

    sprintf(strBuffer, "I/O Cycles Rate (ms/cycle)     :%d\n", configData->ioCycleRate);
    fputs(strBuffer, fileAccessPtr);

    fputs("\n===============\nBegin Simulation\n\n", fileAccessPtr);

    // Put everything in the file into the struct buffer
    while(outHead != NULL)
    {
        fputs(outHead->strBuffer, fileAccessPtr);
        outHead = outHead->next;

    }
    fputs("End Simulation - Complete\n====================", fileAccessPtr);

    //close the file
    fclose(fileAccessPtr);

    // no return void function
}

/*
Function: *addLine()
Algorithm: Adds each new line node to the linked list first
           checking for a NULL value to copy data to NULL node
           that is linked. If the list has a node(s) then recurse
           passing in the next node that points to NULL. Same 
           behavior as addPCB function.
Precondition: local pointer of type logOutType and pointer of 
              logOutType with string to be copied as parameters
*/
logOutType *addLine(logOutType *locNodePtr, logOutType *newLineNode)
{
    // Checks for NULL node
    if(locNodePtr == NULL)
    {
        // allocate mem
        locNodePtr = (logOutType *) malloc(sizeof(logOutType));

        // Copies data to head node strruct buffer
            // Function: copyString()
        copyString(locNodePtr->strBuffer, newLineNode->strBuffer);
        // Set the next logOutType to NULL
        locNodePtr->next = NULL;
        return locNodePtr;
    }

    // recursive call for next node in linked list
    locNodePtr->next = addLine(locNodePtr->next, newLineNode);
    // return ptr
    return locNodePtr;
}


/*
Function: setTimer()
Algorithm: Checks for the start, stop, or running in order
           to start the correct timer.
Precondition: String passed in as char *
*/

char *setTimer(char *logLine)
{
    // Create char po
    char *timerStr = (char *) malloc(sizeof(char));

    if(compareString(logLine, "OS: System Start") == STR_EQ)
    {
        // Call access timer with ZERO_TIMER
        accessTimer(ZERO_TIMER, timerStr);
    }
    
    // Check if stopping for timer purposes
    else if(compareString(logLine, "OS: System stop") == STR_EQ)
    {
        // Call access timer with STOP_TIMER
        accessTimer(STOP_TIMER, timerStr);
    }

    // Else use LAP_TIMER
    else
    {
        accessTimer(LAP_TIMER, timerStr);
    }
    return timerStr;
}
