// header files
#include <stdio.h>
#include "ConfigAccess.h"
#include "MetaDataAccess.h"
#include "StringUtils.h"
#include "simulator_432573.h"

/*Function name: main
Algorithm: driver function to test config and metadata file
           upload operation together
Precondition: none
Postcondition: returns zero (0) on success
Exceptions: none
Note: demonstrates use of combined files
*/
int main(int argc, char **argv)
   {
   // initialize function/variables
   int configAccessResult, mdAccessResult;
   char configFileName[MAX_STR_LEN];
   char mdFileName[MAX_STR_LEN];
   ConfigDataType *configDataPtr;
   OpCodeType *mdData;
   logOutType *returnLogHead;

   // display component title
      // function: printf
   printf("\n  Simulator Program\n");
   printf("  ======================\n\n");

   // check for correct number of command line arguements (two)
   if(argc < 2)
      {
      // print missing command line arguement error
         // function: printf
      printf("ERROR: Program requires file name for config file ");
      printf("as command line arguement\n");\
      printf("Program Terminated\n");

      // return non-normal program result
      return 1;
      }

   printf("  Uploading configuration Files\n");

   // get data from configuration file
      // funnction: copyString, getConfigData
   copyString(configFileName, argv[1]);
   configAccessResult = getConfigData(configFileName, &configDataPtr);

   // check for unsuccessful upload
   if(!(configAccessResult == NO_ERR))
      {
      // failed config data upload display
         // function: displayConfigData
      printf("Failed config data upload");
      }

   // othewise, assume failed upload

   // display component title
      // function: printf
   printf("\n  Uploading Meta Data Files\n");
   printf("\n  ======================\n");

   // get data from meta data file
      // function: copyString, getOpCodes
   copyString(mdFileName, configDataPtr->metaDataFileName);
   mdAccessResult = getOpCodes(mdFileName, &mdData);

   // check for unsuccessful upload
   if(!(mdAccessResult == NO_ERR))
      {
      // failed meta data upload display
         // function: printf
      printf("failed mdData upload\n\n");
      }
   


   // Check both monitor or file and call run sim
   if (configDataPtr->logToCode == LOGTO_MONITOR_CODE)
   {
      runSimulator(mdData, configDataPtr, &returnLogHead);
   }
   else if (configDataPtr->logToCode == LOGTO_FILE_CODE || 
         configDataPtr->logToCode == LOGTO_BOTH_CODE)
   {
      runSimulator(mdData, configDataPtr, &returnLogHead);
      writeLogToFile(configDataPtr, returnLogHead);
   }


      // call write log data using referenced logOutType variable

   

   // clear configuration data
         // function: clearConfigData
      clearConfigData( &configDataPtr);

   // clear meta data
         // function: clearMetaDataList
      mdData = clearMetaDataList(mdData);

   
   // add endline for vertical spacing
      // function: printf
   printf("\n");

   // return success
   return 0;
}