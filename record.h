#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
}RecordType;

int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

void displayRecordsInHash(struct HashTable *hashTable, int hashSz)
{
	int i;
    struct HashType ** ppHashArray=hashTable->arr;
	for (i=0;i<hashSz;++i)
	{
		printf("\nIndex %d:", i);
		struct HashType * tmp = ppHashArray[i];
		while(tmp!=NULL){
			printf(" (%d, %c, %d)",((struct RecordType*)(tmp->data))->id,((struct RecordType*)(tmp->data))->name,((struct RecordType*)(tmp->data))->order);
			tmp = tmp->next;
		}
	}
}

void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}
