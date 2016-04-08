/**
 * \file 		LinkedList.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_
#pragma once

typedef struct _TypLinkedList
{
	void* e;
	_TypLinkedList* next;
} TypLinkedList;

TypLinkedList* lAddItem(TypLinkedList* l, void* e);
TypLinkedList* lDelItem(TypLinkedList* l, void* e);
int lCountItems(TypLinkedList *l);

inline int memIsValidPtr(void *ptr)
{
#ifndef __linux__
	int *iValRef = (int*)0x10000;
	return ( (int*)ptr >= iValRef );
#else //__linux__
	return 1;
#endif //__linux__
}

#else
#error "LinkedList déjà inclus"
#endif
