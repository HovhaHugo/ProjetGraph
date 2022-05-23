#include "CParser.h"
#include "CException.h"
#include <string.h>


/***
* Constructor of CParser
* Input: pcFilePathParam : char*
* Output: /
* Precondition: /
* Postcondition: The object is initialized if the pcFilePathParam file was successfully opened.
*   In this case, pcPARFilePath = pcFilePathParam
***/
CParser::CParser(char* pcFilePathParam) {

    pcPARFilePath = pcFilePathParam;

    std::ifstream fichier(pcPARFilePath);

    if (!fichier.is_open()) {
        CException EXCError(EXCEPTION_MissingFile);
        throw EXCError;
    }

    fichier.close();

    bPARInitialized = true;

}


/***
* Read the file until a line that contains pcIdentifier has been found
* Input: *ifFile : ifstream, pcIdentifier : const char*
* Output: char* the entire line read (and that contains pcIdentifier)
* Precondition: /
* Postcondition: If a line that contains pcIdentifier is found, the data associated is returned.
*   Else \0 is returned.
***/
char* CParser::PARJumpToIdentifier(ifstream *ifFile, const char* pcIdentifier) {

    char cLigne[LINE_LENGTH];
    bool bContinueRead = true;

    char* pcLineIdentifier = (char*)malloc(sizeof(char)*LINE_LENGTH);
    if (pcLineIdentifier == nullptr) {
        throw CException(EXCEPTION_MallocError);
    }

    const char* pcNullIdentifier = "\0";
    sprintf_s(pcLineIdentifier, LINE_LENGTH, pcNullIdentifier);

    while (bContinueRead) {

        if (ifFile->eof()) {
            bContinueRead = false;
            continue;
        }

        ifFile->getline(cLigne, LINE_LENGTH);

        //Identify which data is on this line
        pcLineIdentifier = strtok(cLigne, &cPARSeparator);

        //Put the word to upper to avoid case error
        char* tcUpperText = (char*)malloc(sizeof(char) * LINE_LENGTH);
        if (tcUpperText == nullptr) {
            throw CException(EXCEPTION_MallocError);
        }

        //strcpy(tcUpperText, pcLineIdentifier);
        PARToUpper(tcUpperText, pcLineIdentifier);

        pcLineIdentifier = strtok(nullptr, " ");    //pcLineIdentifier contains now the data to get
        if (pcLineIdentifier == nullptr) {
            free(tcUpperText);
            throw CException(EXCEPTION_ErrorDataFile);
        }

        if (strstr(tcUpperText, pcIdentifier)) {

            free(tcUpperText);
            bContinueRead = false;
            continue;
        }

    }//while(bContinueRead)

    return pcLineIdentifier;

}


/***
* Get a specific number in the file
* Input: pcIdentifier : const char*
* Output: unsigned int
* Precondition: /
* Postcondition: If the label has been found, the number associated is returned
***/
unsigned int CParser::PARGetNumber(const char* pcIdentifier) {

    if (bPARInitialized == false) {
        throw CException(EXCEPTION_Parser_not_init);
    }

    ifstream ifFile(pcPARFilePath);

    char* pcData = PARJumpToIdentifier(&ifFile, pcIdentifier);

    int iNbOfNode = -1;

    char* pcEndPtr;
    iNbOfNode = strtod(pcData, &pcEndPtr);

    if (pcEndPtr == pcData) {
        throw CException(EXCEPTION_ConversionError);
    }

    if (iNbOfNode < 0) {
        throw CException(EXCEPTION_invalide_node_number);
    }

}


/***
* Get the list of nodes
* Input: uiNodeListSize : unsigned int
* Output: piFrom : CNode*
* Precondition: uiNodeListSize is the number read with PARGetNumber(const char* pcIdentifier)
* Postcondition: If the number of CNode read is the same as uiNodeListSize, the list of CNode is returned
***/
CNode* CParser::PARGetNodes(unsigned int uiNodeListSize) {

    if (bPARInitialized == false) {
        throw CException(EXCEPTION_Parser_not_init);
    }

    CNode* pNODNodeList = (CNode*)malloc(uiNodeListSize * sizeof(CNode));
    if (pNODNodeList == nullptr) {
        throw CException(EXCEPTION_MallocError);
    }

    ifstream ifFile(pcPARFilePath);

    PARJumpToIdentifier(&ifFile, "SOMMETS");

    char cLigne[LINE_LENGTH];
    bool bContinueRead = true;

    unsigned int uiNbOfNodeFound = 0;

    while (bContinueRead) {

        if (ifFile.eof()) {
            bContinueRead = false;
            continue;
        }

        ifFile.getline(cLigne, LINE_LENGTH);

        if (cLigne[0] == ']') {   //End of the reading
            bContinueRead = false;
            continue;
        }

        char* pcNodeNumber;
        pcNodeNumber = strtok(cLigne, "=");
        pcNodeNumber = strtok(nullptr, " ");    //pcLineIdentifier contains now the data to get

        char* pcEndPtr;

        int iNodeNumber = strtod(pcNodeNumber, &pcEndPtr);

        if (pcEndPtr == pcNodeNumber) {
            throw CException(EXCEPTION_ConversionError);
        }

        if (iNodeNumber < 0) {
            throw CException(EXCEPTION_invalide_node_number);
        }

        uiNbOfNodeFound++;

        if (uiNbOfNodeFound < uiNodeListSize)
            throw CException();

        pNODNodeList[uiNbOfNodeFound - 1] = new CNode(iNodeNumber);
        
    }//while(bContinueRead)

    return pNODNodeList;

}



/***
* Get the list of links
* Input: piFrom : int*, piTo : int*, iSize : int
* Output: piFrom : int*, piTo : int*
* Precondition: piFrom and piTo are allocated in memory with a space of iSize int
* Postcondition: piFrom contains the list of the begins of the links, piTo contains the list of ends
***/
void CParser::PARGetLink(int* piFrom, int* piTo, int iSize) {

    if (bPARInitialized == false) {
        throw CException(EXCEPTION_Parser_not_init);
    }

    ifstream ifFile(pcPARFilePath);

    PARJumpToIdentifier(&ifFile, "LIENS");

    char cLigne[LINE_LENGTH];
    bool bContinueRead = true;

    unsigned int uiNbOfLinkFound = 0;

    while (bContinueRead) {

        if (ifFile.eof()) {
            bContinueRead = false;
            continue;
        }

        ifFile.getline(cLigne, LINE_LENGTH);

        if (cLigne[0] == ']') {   //End of the reading
            bContinueRead = false;
            continue;
        }

        char* pcLine;
        pcLine = strtok(cLigne, "=");
        pcLine = strtok(nullptr, ",");  //pcLine contains the value of the beginning node

        char* pcEndPtr;
        int iNodeNumberFrom = strtod(pcLine, &pcEndPtr);

        if (pcEndPtr == pcLine) {
            throw CException(EXCEPTION_ConversionError);
        }

        pcLine = strtok(nullptr, "=");
        pcLine = strtok(nullptr, ","); //pcLine contains the value of the ending node

        int iNodeNumberTo = strtod(pcLine, &pcEndPtr);

        if (pcEndPtr == pcLine) {
            throw CException(EXCEPTION_ConversionError);
        }

        uiNbOfLinkFound++;

        if (uiNbOfLinkFound > iSize) {
            throw CException();
        }

        piFrom[uiNbOfLinkFound - 1] = iNodeNumberFrom;
        piTo[uiNbOfLinkFound - 1] = iNodeNumberTo;

    }


}


/***
* Convert the parameter pcOrigin to uppercase and store it in pcOutput
* Input: char*:pcOutput, char*:pcOrigin
* Output: char*:pcOutput
* Precondition: pcOutput must be initialized as the same size as pcOrigin
* Postcondition: pcOutput contains pcOrigin converted to uppercase
***/
void CParser::PARToUpper(char* pcOutput, const char* pcOrigin) {
    for (int iLoop = 0; pcOrigin[iLoop] != '\0'; iLoop++) {
        pcOutput[iLoop] = toupper(pcOrigin[iLoop]);
    }
}


