#include "hash.h"
#include "record.h"


int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	struct HashTable * hashTable = initTable(15);
	for(int i = 0; i < recordSz;i++){
		add(hashTable,(pRecords+i)->order,pRecords+i);
	}
	
	displayRecordsInHash(hashTable,15);



}