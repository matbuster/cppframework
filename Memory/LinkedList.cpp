/**
 * \file 		LinkedList.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

// Début modif YR.
#ifndef __linux__
#include <windows.h>
#else //__linux__
#include <iostream>
#endif // __linux__
#include <stdlib.h>
#include <stdio.h>
//#include "../FileIO/fileLog.h"
#include "LinkedList.h"
//#include "MemMgr.h"
//#include "wx/wxprec.h"
//#include "wx/wx.h"
// Fin modif YR.

TypLinkedList* lAddItem(TypLinkedList* l, void* e)
{
	TypLinkedList* ll;
	if(!memIsValidPtr((void*)e))
	{
#ifndef __linux__
		MessageBoxA(NULL, "lAddItem", "Linked list Error", MB_OK|MB_ICONERROR);
#else //__linux__
		std::cout<< "lAddItem" << "\t" << "Linked list Error" << "\n";
#endif //__linux__
	}
	if(!l)
	{
#ifndef M3D_UseSPG_MemAlloc
		l=(TypLinkedList*)malloc(sizeof(TypLinkedList));
#else
		l=(TypLinkedList*)SPG_MemAlloc(sizeof(TypLinkedList),"lAddItem:TypLinkedList l");
#endif
		l->e=e;
		l->next=NULL;
		return l;
	}
	else
	{
		ll=l;
		while((ll->next!=NULL) && (memIsValidPtr((void*)(ll->next))))
			ll=ll->next;
		ll->next=(TypLinkedList*)malloc(sizeof(TypLinkedList));
		if(!memIsValidPtr((void*)(ll->next)))
		{
#ifndef __linux__
			MessageBoxA(NULL, "lAddItem", "Linked list Error", MB_OK|MB_ICONERROR);
#else //__linux__
			std::cout<< "lAddItem" << "\t" << "Linked list Error 2" << "\n";
#endif //__linux__
		}
		ll->next->next=NULL;
		ll->next->e=e;
		return l;
	}
}

/*
void lFreeItem(volatile TypLinkedList* l,volatile void* e)
{
	while(l)
	{
		if(l->e==e)
		{
			memFree((void*)l->e);
			return;
		}
		l=l->next;
	}
}
*/

TypLinkedList* lDelItem(TypLinkedList* l,void* e)
{
	TypLinkedList* ll,*ll1;
	if(!l)
		return NULL;
	if(l->e==e)
	{
		ll=l;
		l=l->next;
		free((void*)ll);
		return l;
	}
	ll=l;
	while(ll->next)
	{
		if(ll->next->e==e)
		{
			ll1=ll->next;
			ll->next=ll1->next;
			ll1->e=NULL;
#ifndef M3D_UseSPG_MemAlloc
			free((void*)ll1);
#else
			SPG_MemFree((void*)ll1);
#endif
			return l;
		}
		ll=ll->next;
	}
#ifdef _DEBUG
	MessageBoxA(NULL, "lDelItem: item not found", "Linked list debug", MB_OK);
#endif //_DEBUG
	return l;
}

/**
 * Compte le nombre d'elements dans une chaine
 *
 * @param *l   liste chainee
 * @return     la taille de la liste en int, 0 si l est NULL
 */
int lCountItems(volatile TypLinkedList *l)
{
	if (l == NULL)
	{
		return 0;
	}

	int size = 1;

	while (l->next)
	{
		size++;
		l = l->next;
	}

	return size;
}

