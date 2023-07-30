#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#ifndef HASH_H
#define HASH_H

struct HashType{
	void * data;
	struct HashType * next;
    int key;
}HashType;

struct HashTable{
    struct HashType**arr;
    int size;
}HashTable;

int containsKey(struct HashTable * HashTable,int key){
	struct HashType* checkNode = HashTable->arr[hash(key,HashTable->size)];
	while(checkNode!=NULL&&checkNode->key!=key)
	checkNode=checkNode->next;
	if(checkNode!=NULL)
	return 1;
    return 0;
}

void insertAtIndex(int index, void * data,struct HashType ** HashTable){
	struct HashType * pHead = (struct HashType *)malloc(sizeof(HashType));
	pHead->data=data;
	pHead->next = HashTable[index];
	HashTable[index]=pHead;
}

int hash(int x,int size){
 return x%size;
}

void * get(struct HashTable * HashTable,int key){
	struct HashType* checkNode = HashTable->arr[hash(key,HashTable->size)];
	while(checkNode!=NULL&&checkNode->key!=key)
	checkNode=checkNode->next;
	if(checkNode!=NULL)
	return &(checkNode->data);
	else return NULL;
}

void add(struct HashTable * HashTable, int key, void * value){
	insertAtIndex(hash(key,HashTable->size),value,HashTable->arr);
}

struct HashTable * initTable(int size){
	struct HashTable* hashTable=(struct HashTable *)malloc(sizeof(hashTable));
    hashTable->arr=(struct HashType**)malloc(size*sizeof(struct HashType *));
    hashTable->size=size;
	memset(hashTable->arr,NULL,size*sizeof(struct HashType *));
	return hashTable;
}
#endif
