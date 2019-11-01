/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <string>
#include <string.h>
#include <sstream>
#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"
#include "../327_proj3_test/includes/FileIO.h"

using namespace KP_StringParserClass;

char *pStartTag;
char *pEndTag;
bool areTagsSet;

//dont forget to initialize member variables
StringParserClass::StringParserClass(void) {
	pStartTag = NULL;
	pEndTag = NULL;
	areTagsSet = false;
}

//call cleanup to release any allocated memory
StringParserClass::~StringParserClass(void) {
	cleanup();
}

//these are the start tag and the end tags that we want to find,
//presumably the data of interest is between them, please make a
//COPY of what pStartTag and pEndTag point to.  In other words
//DO NOT SET pStartTag = pStart
//returns:
//SUCCESS
//ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::setTags(const char *pStart, const char *pEnd) {
	if (pStart == NULL || pEnd == NULL) {
		return ERROR_TAGS_NULL;
	}
	pStartTag = new char[strlen(pStart) + 1];
	pEndTag = new char[strlen(pEnd) + 1];

	strncpy(pStartTag, pStart, strlen(pStart));
	strncpy(pEndTag, pEnd, strlen(pEnd));
	areTagsSet = true;

	return SUCCESS;

}

//First clears myVector
//going to search thru pDataToSearchThru, looking for info bracketed by
//pStartTag and pEndTag, will add that info only to myVector
//returns
//SUCCESS  finished searching for data between tags, results in myVector (0 or more entries)
//ERROR_TAGS_NULL if either pStart or pEnd is null
//ERROR_DATA_NULL pDataToSearchThru is null
int StringParserClass::getDataBetweenTags(char *pDataToSearchThru,
		std::vector<std::string> &myVector) {
	myVector.clear();
	std::string ofstuff = "";

	if (pStartTag == NULL || pEndTag == NULL || pStartTag == 0
			|| pEndTag == 0) {
		return ERROR_TAGS_NULL;
	}

	if (pDataToSearchThru == NULL) {
		return ERROR_DATA_NULL;
	}

	int size = strlen(pDataToSearchThru);
	char *blh = pDataToSearchThru;
	char *grr = pDataToSearchThru + size;
	char *bet = pDataToSearchThru + size;

	while (findTag(pStartTag, pDataToSearchThru, grr) == SUCCESS) {
		if (findTag(pEndTag, blh, bet) == SUCCESS) {
			while (grr != blh) {
				ofstuff = ofstuff + *grr;
				grr++;
			}
			myVector.push_back(ofstuff);
			pDataToSearchThru = bet;
			size = strlen(pDataToSearchThru);
			ofstuff = "";
			grr = pDataToSearchThru + size;
			bet = pDataToSearchThru + size;
			blh = pDataToSearchThru;

		} else {
			return SUCCESS;
		}
	}

	return SUCCESS;
}

void StringParserClass::cleanup() {

}
//Searches a string starting at pStart for pTagToLookFor
//returns:
//SUCCESS  found pTagToLookFor, pStart points to beginning of tag and pEnd points to end of tag
//FAIL did not find pTagToLookFor and pEnd points to 0
//ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::findTag(char *pTagToLookFor, char *&pStart,
		char *&pEnd) {
	bool found = false;

	if (pStart == NULL || pEnd == NULL) {
		return ERROR_TAGS_NULL;
	}

	if (pStartTag == NULL & pEndTag == NULL) {
		return FAIL;
	}
	int lookfor = strlen(pTagToLookFor);
	int thisthing = strlen(pStart);

	char *len = new char[thisthing];
	strncpy(len, pStart, lookfor);

	for (int i = 0; i < strlen(len); i++) {
		if (*len + i == pTagToLookFor[0]) {
			if (strncmp(len, pTagToLookFor, lookfor) == 0) {
				pStart = len + i;
				pEnd = pStart + lookfor - 1;
				return SUCCESS;
			}
		}
	}
	return FAIL;

}

