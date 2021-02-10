/*
File: simulator_432573.c
Class: CS_480
Project: simulator 03
*/

// Preproccessor directives
#include <stdio.h>
#include <stdlib.h>
#include "ConfigAccess.h"
#include "MetaDataAccess.h"
#include "StringUtils.h"
#include "simulator_432573.h"
#include "simtimer.h"


/*
Function: runSim()
Algorithm: This function will take in two arguements
           a linked list of meta-data and config-data.
           The function will make a call to the log file
*/
void runSimulator(OpCodeType *mdData, ConfigDataType *configData, logOutType **outPut)
{
        // Declare variables
        int processTime = configData->procCycleRate;
        int ioTime = configData->ioCycleRate;
        int schedCode = configData->cpuSchedCode;
        pcbType *head = NULL;
        int processes;


        if(configData->logToCode == LOGTO_MONITOR_CODE
            || configData->logToCode == LOGTO_BOTH_CODE)
        {
           printf("  Begin Simulation\n\n");
        }

        // Call logData function for System Start
        initLogDataList(configData, outPut, "OS: System Start");

        // call logData for process control blocks
        initLogDataList(configData, outPut,
                "OS: Create Process Control Blocks");

        // call logData for initialize
        initLogDataList(configData, outPut,
                "OS: All processes initialized in New state");

        // Allocate memory right before use
        head = (pcbType *) malloc(sizeof(pcbType));
        // initialzies PCB's and returns the number of PCB's created
        processes = setProcesses(mdData, &head, configData);

        // call logdata for setToReady
        initLogDataList(configData, outPut,
                "OS: All processes now set in Ready state");
        setReady(head);

        // Make seperate function
           // Function: checkSchedCode()
        checkSchedCode(configData, outPut, processes, head, schedCode,
                          ioTime, processTime);

        if(configData->logToCode == LOGTO_MONITOR_CODE
            || configData->logToCode == LOGTO_BOTH_CODE)
        {
           printf("  End Simulation - Complete\n  ====================");
        }
        // Free the PCB linked list for memory
        freeList(head);
}

/*
Function: initializePCB()
Algorithm: this function creates a copy of the metaData and
           loops through each process. Function calls to createPCB
           and then once the loop goes through the first process the
           PCB node that was previously created is added to the linked
           list by calling addPCB.
Precondition: An OpCodeType is passed in along with a reference to
              a head pointer.
*/
int setProcesses(OpCodeType *mdData, pcbType **headPtr,
   ConfigDataType *configData)
{
        // delcare variables
        int processes = 0;
        int procTime;

        // Allocate memory
        pcbType *createdPCB = (pcbType *) malloc(sizeof(pcbType));
        pcbType *localHeadPtrPCB = (pcbType *) malloc(sizeof(pcbType));
        OpCodeType *metaData = (OpCodeType *) malloc(sizeof(OpCodeType));

        // set headPtr to NULL
        localHeadPtrPCB = NULL;
        // OpCodeType structure that is a copy of the metadata list
        metaData = mdData->next;
        // While loop iterates until the end of all the data
        while(metaData->opLtr != 'S')
        {
            // Reset the total procTime for each new process
            procTime = 0;

            // Checks for the start process
            if(metaData->opLtr == 'A')
            {
                  // Initialize the declared PCB structure to the
                  createdPCB = createPCB(metaData, processes);
            }

            // Move to next process
            metaData = metaData->next;

            // while loop iterates through all threads of the process
            while(metaData->opLtr != 'A')
            {
               // Checks if the rqMemory has not been set to correct value
               if(compareString(metaData->opName, "allocate") == STR_EQ
               && !createdPCB->rqMemory)
               {
                  // Stores the opValue into the requested memory variable
                  createdPCB->rqMemory = metaData->opValue;
               }

               // Calculates the time for all processes inbetween
               // the A(start) and A(end)
               procTime += calcProcTime(configData, metaData);

               // Move to next thread in process
               metaData = metaData->next;
            }

        // Set the total time to the PCB struct variable
        createdPCB->procTime = procTime;
        //printf("The time for process %d is: %d\n",
                //createdPCB->pid, createdPCB->procTime);

        // call addNode functiono (addPCB)
        localHeadPtrPCB = addPCB(localHeadPtrPCB, createdPCB);

        metaData = metaData->next;
        // Increase by one for each PCB created
        processes++;
        }

        *headPtr = localHeadPtrPCB;

        // return the total number of PCB's there are
        return processes;
}

/*
Function: calcProcTime()
Algorithm: The function calcuates the time for each process
           to complete and returns the time to be added to
           a total for later use and comparison for certain
           scheduling types
Preconditon: A pointer to meta-data and config-data are passed
             in as arguements
Postcondition: Returns an int as the time in ms
*/
int calcProcTime(ConfigDataType *configPtr, OpCodeType *mdDataPtr)
{
        // Declare variables
        int procTime = 0;
        // Stores the letter of the current op code
        char procLetter = mdDataPtr->opLtr;

        // Checks for I/O or other
        if(procLetter == 'I' || procLetter == 'O')
        {
           // calculates the i/o cycle rate
           procTime = mdDataPtr->opValue * configPtr->ioCycleRate;
        }

        else if(procLetter == 'P')
        {
           procTime = mdDataPtr->opValue * configPtr->procCycleRate;
        }
        // For allocate and access memory opCode
        else
        {
           return 0;
        }
       return procTime;
}

/*
Function: addPCB
Algorithm: adds the pcb node created to the linked list by
           updating the local pointer that was originally
           pointing at NULL to the newNode
*/
pcbType *addPCB(pcbType *localPtr, pcbType *newNode)
    {
    // check for local pointer assigned to null
    if(localPtr == NULL)
      {
      // access memory for new link/node
         // funciton: malloc
      localPtr = (pcbType *) malloc(sizeof(pcbType));

      // Assign values to localPtr
      localPtr->state = newNode->state;
      localPtr->pid = newNode->pid;
      localPtr->mdPtr = newNode->mdPtr;
      localPtr->procTime = newNode->procTime;
      localPtr->rqMemory = newNode->rqMemory;
      localPtr->next = NULL;

      return localPtr;
      }

   // Rcurively call the function passing in the next pcb node
      // funciton: addPCB
   localPtr->next = addPCB(localPtr->next, newNode);

   // return current local pointer
   return localPtr;
   }


/*
Function: createPCB
Algorithm: This method will take in mdData and an id
           assign valules to each piece of the PCB. Memory
           will need tp be assigned allocated for each PCB
           after the initialization of each. This method
           will return the newly created PCB.
*/
pcbType *createPCB(OpCodeType *mdData, int id)
{
        // Initialize a new PCB
        pcbType *newPCB = (pcbType *) malloc(sizeof(pcbType));

        newPCB->state = NEW;
        newPCB->pid = id;
        newPCB->next = NULL;
        newPCB->mdPtr = mdData;
        newPCB->rqMemory = 0;

        // retutrn the pcb back to initializePCB
        return newPCB;
}

/*
Function: setReady()
Algorithm: Sets all of the pcb's to a ready state
Precondition: a data pointer of type pcbType that is
              the header of the linked list is passed
*/
void setReady(pcbType *headPtrPCB)
{
   while(headPtrPCB != NULL)
   {
      // Set the state to ready
      headPtrPCB->state = READY;
      headPtrPCB = headPtrPCB->next;
   }
}

/*
Function: displayDump()
Algorithm: Loops through the pcb linked list and
           then through each thread displaying to
           the screen
*/
void displayDump(ConfigDataType *configData, logOutType **outPut,
                pcbType *headNodePtr, int ioTime, int procTime)
{
   // Change and put into Config
   int bound = configData->memAvailable;

   // Declare variables
   char strBuffer[MAX_STR_LEN];
   OpCodeType *mdPtr;

   if(headNodePtr != NULL)
   {

      // log process selected in state
      sprintf(strBuffer, "OS: Process %d selected with %d ms remaining",
               headNodePtr->pid, headNodePtr->procTime);
      initLogDataList(configData, outPut, strBuffer);

      // set to run on just headPCB and log
      headNodePtr->state = RUNNING;

      // Store the string into buffer
      sprintf(strBuffer, "OS: Process %d set in RUNNING state\n",
               headNodePtr->pid);
      initLogDataList(configData, outPut, strBuffer);

      // allocate memory for metadata nodes
      mdPtr = (OpCodeType *) malloc(sizeof(OpCodeType));

      // set meta data node to process after the start
         // to save from using conditional
      mdPtr = headNodePtr->mdPtr->next;

      // check for a start or allocate to move pointer
      if(mdPtr->opLtr == 'A' &&
         compareString(mdPtr->opName, "start"))
      {
         mdPtr = mdPtr->next;
      }

      // Loop through processes
      while( mdPtr != NULL)
      {
         // Fisrt memory request
         if(mdPtr->opLtr == 'M' && bound == configData->memAvailable)
         {
            // Sets the boundary for the inner memory acceess codes
            bound = memoryCheck(mdPtr->opValue, bound, headNodePtr,
               mdPtr, configData, outPut);
            // If memory exceeds avaliable mem
            if(!bound)
            {
               // Breaks loop for to get next process
               mdPtr = NULL;
            }
            else
            {
               mdPtr = mdPtr->next;
            }
         }
         // Check for end to set pointer to NULL to break loop
         else if(mdPtr->opLtr == 'A' &&
            compareString(mdPtr->opName, "end") == STR_EQ)
         {
            // Set state to exit
            headNodePtr->state = EXIT;

            sprintf(strBuffer,
                  "OS: Process %d ended in and set in EXIT state",
                           headNodePtr->pid);
            initLogDataList(configData, outPut, strBuffer);

            // breaks the loop
            mdPtr = NULL;
         }

         // If not at the end and not NULL to keep looping
         else if(!(mdPtr->opLtr == 'A' &&
               compareString(mdPtr->opName, "end") == STR_EQ)
                     && mdPtr != NULL)
         {
            if(mdPtr->next->opLtr == 'A' &&
               compareString(mdPtr->next->opName, "end") == STR_EQ)
            {
               // Pass in a new line character
               if(mdPtr->opLtr == 'M')
               {
                  // if result is 0 then attempt to allocate failed
                  if(!memoryCheck(mdPtr->opValue, bound, headNodePtr,
                     mdPtr, configData, outPut))
                  {
                     mdPtr = NULL;
                  }
               }

               else
               {
                  // Checks the opCode for correct display
                  opCodeDisplay(outPut, configData, mdPtr,
                     headNodePtr, NEW_LINE);
               }
            }

         // Next opCode in not the end
         else
         {
            //Conditional for Memeory operation
            if(mdPtr->opLtr == 'M')
            {
               // if result is 0 then attempt to allocate failed
               if(!memoryCheck(mdPtr->opValue, bound, headNodePtr,
                  mdPtr, configData, outPut))
               {
                  mdPtr = NULL;
               }
            }
            // Non-memory access codes
            else
            {
               opCodeDisplay(outPut, configData, mdPtr, headNodePtr, SPACE);
            }
         }
      }
      // Moves the pointer to the next opCode if not NULL
      if(mdPtr != NULL)
      {
         //printf("\nMoving to the next node\n");
         mdPtr = mdPtr->next;
      }
      }

      // Free meta data pointer for the next pcb
      free(mdPtr);

   }
   // Free headNodePtr data as it is done with it's use currently
   free(headNodePtr);
}

/*
Function: freeList()
Algorithm: This method with iterate through the PCB linked list
           and free each node
Precondition: Program exxecution should be over before doing so
*/
void freeList(pcbType *headPtr)
{
   // Declare variables
   pcbType *temp;
   while(headPtr != NULL)
   {
      temp = (pcbType *) malloc(sizeof(pcbType));
      temp = headPtr;
      headPtr = headPtr->next;
      free(temp);
   }
}

/*
Function: doIOThread()
Algorithm: Function takes in meta Data and checks the op Letter
           determining if it is 'I', 'O', or other and performs operation.
           Function saves space.
Preconditon: Meta data is passed in
Psotconditon: Function doesn't return
*/
void doIOThread(OpCodeType *mdDataPtr, int ioTime)
{
   // Declare variables
   int rTime;
   pthread_t tid;
   int *tPtr;
   void *vPtr;

   rTime = ioTime * mdDataPtr->opValue;
   tPtr = &rTime;
   vPtr = (void *) tPtr;
   pthread_create(&tid, NULL, vRunTimer, vPtr);
   pthread_join(tid, NULL);
}

/*
Function: memoryCheck()
Algorithm: Checks the if the memory being requested is over
           the set boundary and will display accordingly.
Precondition: The function takes a value to check, a pcbType,
              ConfigDataType, OpCodeType, and a logOutType structure
Postcondition: Rerturns the memorry request int or 0 depending if there
               is a problem with the request or not.
*/
int memoryCheck(int value, int bound, pcbType *headPtr,
   OpCodeType *mdPtr, ConfigDataType *configData,
      logOutType **outPut)
{
   // Declare variables
   int fHalf, sHalf, total, base;
   char strBuffer[MAX_STR_LEN];
   // Base is for seperating the memory request in half by a decimal character
   base = MEM_LOG_BASE;

   /*
   Loop seperates the opValue with a decimal and
   then uses interger and modulus to get the number
   before and after the decimal
   */
   while((value / base) > base)
   {
      base *= base;
   }
   fHalf = value / base;
   sHalf = value % base;
   total = fHalf + sHalf;

   // Zero-padding used to fill in 0's missing from previous math operations
   sprintf(strBuffer,
   "Process: %d, MMU attempt to %s %04d/%04d",
      headPtr->pid, mdPtr->opName, fHalf, sHalf);
   initLogDataList(configData, outPut, strBuffer);

   // Exeeds the memory boundary set
   if(total > bound)
   {
      sprintf(strBuffer, "Process: %d, MMU failed to %s\n",
         headPtr->pid, mdPtr->opName);
            initLogDataList(configData, outPut, strBuffer);

      sprintf(strBuffer,
         "OS: Process %d experiences segmentation fault",
            headPtr->pid);
      initLogDataList(configData, outPut, strBuffer);

      // Set state tot EXIT as memory was insuficient
      headPtr->state = EXIT;

      sprintf(strBuffer, "OS: Process %d ended and set in EXIT state",
            headPtr->pid);
      initLogDataList(configData, outPut, strBuffer);
      return 0;
   }
   // Success
   else
   {
      sprintf(strBuffer, "Process: %d, MMU successful %s",
         headPtr->pid, mdPtr->opName);
      initLogDataList(configData, outPut, strBuffer);
      return total;
   }
}

/*
Function: opCodeDisplay()
Algorithm: Function checks the currrent OpLtr to do
           threading and display correct statement.
           Calls to initLogDataList for timer access
           and for logging to file.
Precondition: Takes in everything needed to call to
              initLogDataList and also ioTime for
              i/o time calculation.
Postcondition: None
*/
void opCodeDisplay(logOutType **outPut, ConfigDataType *configData,
   OpCodeType *mdPtr, pcbType *headPtr, char concatChar)
{
   char strBuffer[MAX_STR_LEN];
   int rTime, procTime = configData->procCycleRate;
   int ioTime = configData->ioCycleRate;


   if(mdPtr->opLtr == 'I')
   {
      sprintf(strBuffer, "Process: %d, %s input start",
         headPtr->pid, mdPtr->opName);
      initLogDataList(configData, outPut, strBuffer);

      // pthreading for i/o processes
      doIOThread(mdPtr, ioTime);

      sprintf(strBuffer, "Process: %d, %s input end%c",
         headPtr->pid, mdPtr->opName, concatChar);
      initLogDataList(configData, outPut, strBuffer);
   }

   else if(mdPtr->opLtr == 'O')
   {
      sprintf(strBuffer, "Process: %d, %s output start",
               headPtr->pid, mdPtr->opName);
      initLogDataList(configData, outPut, strBuffer);

      // pthreading for i/o processes
      doIOThread(mdPtr, ioTime);

      sprintf(strBuffer, "Process: %d, %s output end%c",
         headPtr->pid, mdPtr->opName, concatChar);
      initLogDataList(configData, outPut, strBuffer);
   }

   // Non-I/O operations
   else
   {
      sprintf(strBuffer, "Process: %d, %s operation start",
         headPtr->pid, mdPtr->opName);
      initLogDataList(configData, outPut, strBuffer);

      rTime = procTime * mdPtr->opValue;
      runTimer(rTime);

      sprintf(strBuffer, "Process: %d, %s operation end%c",
         headPtr->pid, mdPtr->opName, concatChar);
      initLogDataList(configData, outPut, strBuffer);
   }
}


/*
Function: checkSchedCode
Algorithm: Function checks the schedule code and runs process
           according to the schedule code provided.
Precondition: The number of processes is passed in as well as the
              head pointer to the linked list node, the schedule code,
              io time and process time.
Postcondition: None
*/
void checkSchedCode(ConfigDataType *configData, logOutType **outPut, int processes,
  pcbType *headNodePtr, int schedCode,int ioTime, int processTime)
{
    // Declare Variables
    int iteration;
    pcbType *cpyHead;
    pcbType *qPCB;
    char strBuffer[MAX_STR_LEN];

    switch(schedCode)
    {
     case CPU_SCHED_SJF_N_CODE:

        // tells outerloop when all have been tested agaist
        // eachother for each
        iteration = 0;
        cpyHead = (pcbType *) malloc(sizeof(pcbType));
        //Processes should be 5
        while(iteration < processes)
        {
            // Reset each time to iterate over list n number of times
            cpyHead = headNodePtr;

            // gets to the first avaliable node for comparison
            // will never get to NULL because outer loop will prevent
            while(cpyHead->state != READY)
            {
                // move the pointer to the next avaliable node
                //printf("\n\nFinally hit the conditonal****\n\n");
               cpyHead = cpyHead->next;
            }

            // allocate space right befire use only for non-NULL
            qPCB = (pcbType *) malloc(sizeof(pcbType));
            qPCB = cpyHead;

            // inner loop to go over each PCb in the list
            while(cpyHead != NULL)
            {
               // checks if the next pcb is quicker
               if(cpyHead->next != NULL
                     &&cpyHead->next->state == READY
                        && qPCB->procTime > cpyHead->next->procTime)
               {
                  // set current shortest time
                  qPCB = cpyHead->next;
               }

               // move to the next pcb even if NULL
               cpyHead = cpyHead->next;
            }

            // display the PCb with the shortest time
            displayDump(configData, outPut, qPCB, ioTime, processTime);

            // increase the interatioon number
            iteration++;
        }

        sprintf(strBuffer, "OS: System stop\n");
        initLogDataList(configData, outPut, strBuffer);
        break;

    case CPU_SCHED_FCFS_N_CODE:
          // Loops through the linked list displaying one PCB at a time
          while(headNodePtr != NULL)
          {
             displayDump(configData, outPut, headNodePtr, ioTime, processTime);
             headNodePtr = headNodePtr->next;
          }
          sprintf(strBuffer, "OS: System stop\n");
          initLogDataList(configData, outPut, strBuffer);
          break;

    // Checks for the preemtive SRTF code
    // Uses SJF function for assistance
    case CPU_SCHED_SRTF_P_CODE:
      // Do all of the same as SJF but check after each code if it is i/o
      // to do appropraite work


      iteration = 0;
      cpyHead = (pcbType *) malloc(sizeof(pcbType));
      //Processes should be 5
      while(iteration < processes)
      {
          // Reset each time to iterate over list n number of times
          cpyHead = headNodePtr;

          // gets to the first avaliable node for comparison
          // will never get to NULL because outer loop will prevent
          while(cpyHead->state != READY)
          {
              // move the pointer to the next avaliable node
             cpyHead = cpyHead->next;
          }

          // allocate space right befire use only for non-NULL
          qPCB = (pcbType *) malloc(sizeof(pcbType));
          qPCB = cpyHead;

          // inner loop to go over each PCb in the list
          while(cpyHead != NULL)
          {
            //

             // checks if the next pcb is quicker
             if(cpyHead->next != NULL
                   &&cpyHead->next->state == READY
                      && qPCB->procTime > cpyHead->next->procTime)
             {
                // set current shortest time
                qPCB = cpyHead->next;
             }

             // move to the next pcb even if NULL
             cpyHead = cpyHead->next;
          }

          // display the PCb with the shortest time
          displayDump(configData, outPut, qPCB, ioTime, processTime);

          // increase the interatioon number
          iteration++;
      }

      sprintf(strBuffer, "OS: System stop\n");
      initLogDataList(configData, outPut, strBuffer);
      break;


    // Checks for first come first serve

    // Use FCFS-N function as a helper to this
    // preemptive one.
    case CPU_SCHED_FCFS_P_CODE:

    // (FCFS-N Code Here)

    // Check next opCode in the OpCodeDisplay function

      break;

    // Checks for round robin scheduling
    case CPU_SCHED_RR_P_CODE:

    // Get more assitance for clarity

      break;
    }
}
