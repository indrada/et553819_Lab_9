#include <stdio.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
}RecordType;

// Fill out this structure
struct HashType
{
	struct RecordType data;
	struct HashType * next;
}HashType;

void insertAtIndex(int index, struct RecordType data,struct HashType ** HashTable){
	struct HashType * pHead = malloc(sizeof(HashType));
	pHead->data=data;
	pHead->next = HashTable[index];
	HashTable[index]=pHead;
}
// Compute the hash function
int hash(int x)
{
 return x%15;
}

// parses input file to an integer array
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

// prints the records
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

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType **ppHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		printf("\nIndex %d", i);
		struct HashType * tmp = ppHashArray[i];
		while(tmp!=NULL){
			printf("->%d %c %d",tmp->data.id,tmp->data.name,tmp->data.order);
			tmp = tmp->next;
		}
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	struct HashType ** hashTable=malloc(15*sizeof(struct HashType *));
	for(int i = 0; i<15; i++){
		hashTable[i]=NULL;
	}
	for(int i = 0; i < recordSz;i++){
		insertAtIndex(hash((pRecords+i)->order),pRecords[i],hashTable);
	}
	displayRecordsInHash(hashTable,15);


}