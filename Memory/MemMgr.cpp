/**
 * \file 		MemMgr.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

//Information de debug des allocation et déallocation de la memoire
//#define DEBUG_ALLOCATION_AND_DEALLOCATION_MESSAGE

#ifndef __linux__
#include <windows.h>
#include <crtdbg.h>
#else
#include <string.h>
#endif // __linux__

#include <stdlib.h>
#include <stdio.h>
#include "../FileIO/fileLog.h"
#include "MemMgr.h"
#include "LinkedList.h"

#include "Threading/Mutex.h"

static TypLinkedList * mem_list;
static Threading::Mutex Mutex_MemMgr;

#define MEM_TEST_VALUE (0x55AA5AA5)

// ***************************************************************
#define LOG(ptext) printf(ptext);

//TODO: Faire le lien avec un fichier de log 
/*#define LOG(ptext) \
	if (ptext != NULL) \
	{ \
		Log(flPrioDebug, flOrigMemory, ptext); \
	} */

// ***************************************************************
// ***************************************************************
/**
 * Retourne l'utilisation memoire en pourcents.
 */
double memUsedMemory()
{
	Mutex_MemMgr.WaitOne();
	double percent = 0.0;

#ifndef __linux__
	MEMORYSTATUS MS;
	GlobalMemoryStatus(&MS);

	percent = 100.0f * (1.0f - ((double) MS.dwAvailPageFile / (double) MS.dwTotalPageFile));

	char text[STR_LONG];
	sprintf(text, "Memory usage: %.2f %%", percent);
	LOG(text);
#endif //__linux__
	
	Mutex_MemMgr.Release();
	return percent;
}


// ***************************************************************
// ***************************************************************
/**
 * Allocation d'un bloc de memoire avec le bound checker.
 * Si la taille specifiee est negative ou superieure a 1 Gb,
 * la fonction retourne NULL.
  
 * @param   size   taille en octet
 * @param  *name   nom du bloc memoire
 *
 * @return  le pointeur sur le bloc memoire, ou NULL en cas d'echec.
 */
void* memAlloc(long size, const char* name)
{
	Mutex_MemMgr.WaitOne();

#ifdef DEBUG_ALLOCATION_AND_DEALLOCATION_MESSAGE
	char textAllocation[LONG_STR];
	sprintf(textAllocation, "memAlloc: alloction size (%ld), bloc name\"%s\"", size, name);
	if (log != NULL) log->AddMessage(textAllocation, LOGFILE_DEBUG, LOGFILE_MEMORY);
#endif 

	char text[STR_LONG];
	if (size < 0)
	{
		sprintf(text, "memAlloc error: negative size (%ld), bloc name\"%s\"", size, name);
		LOG(text);
#ifdef _DEBUG
		MessageBoxA(NULL, text, "MemMgr Error", MB_OK|MB_ICONERROR);
#endif //_DEBUG
#ifdef _DEBUG_LINUX_
		//wxFMessageBox( text, "", wxOK|wxICON_ERROR);
#endif
		
		Mutex_MemMgr.Release();
		return NULL;
	}

	if (size >= (1024*1024*1024)) // 1 Go
	{
		sprintf(text, "memAlloc error: size too great (%.2f Gb), bloc name\"%s\"", (float) size / (1024*1024*1024), name);
		LOG(text);
#ifdef _DEBUG
		MessageBoxA(NULL, text, "MemMgr Error size", MB_OK|MB_ICONERROR);
#endif //_DEBUG
#ifdef _DEBUG_LINUX_
		//wxFMessageBox( text, "", wxOK|wxICON_ERROR);
#endif
		Mutex_MemMgr.Release();
		return NULL;
	}

	TypMemDescr* md = (TypMemDescr*) malloc(sizeof(TypMemDescr));
#ifndef __linux__
	int *iValRef = (int*)0x10000;
	if ( (int*)md < iValRef )
	{
		LOG(text);
#ifdef _DEBUG
		MessageBoxA(NULL, "memAlloc", "MemMgr Error", MB_OK|MB_ICONERROR);
#endif //_DEBUG
	}
#endif //__linux__


#ifdef DEBUG_MEM_MGR_INFO
	if (log != NULL) log->AddMessage(LOGFILE_DEBUG, LOGFILE_MEMORY, "memAlloc %s, %ld bytes", name, size);
#endif 

	if (md == NULL)
	{
	        sprintf(text, "memAlloc malloc failed %s, %ld, md == NULL", name, size);
#ifdef _DEBUG_LINUX_
		//wxFMessageBox( text, "", wxOK|wxICON_ERROR);
#endif
		LOG(text);
		Mutex_MemMgr.Release();
		return NULL;
	}

	memset(md, 0, sizeof(TypMemDescr));
	strncpy(md->name, name, STR_LONG - 1);
	md->size = size;
	md->ptr_orig = (char*) malloc(size + 16);

	if (md->ptr_orig == NULL)
	{
	        sprintf(text, "memAlloc malloc failed %s, %ld, md->ptr_orig == NULL", name,size);
#ifdef _DEBUG_LINUX_
		//wxFMessageBox( text, "", wxOK|wxICON_ERROR);
#endif
		LOG(text);
		free(md);
		Mutex_MemMgr.Release();
		return NULL;
	}

	md->ptr = (md->ptr_orig) + 8;

	((DWORD*)md->ptr)[-1] = MEM_TEST_VALUE;
	((DWORD*)md->ptr)[-2] = MEM_TEST_VALUE;
	((DWORD*)(((char*)md->ptr)+size))[0] = MEM_TEST_VALUE;
	((DWORD*)(((char*)md->ptr)+size))[1] = MEM_TEST_VALUE;
	
	mem_list = lAddItem(mem_list, md);
	Mutex_MemMgr.Release();
	return md->ptr;
}


// ***************************************************************
// ***************************************************************
/**
 * Idem que memAlloc(), avec en plus l'initialisation du bloc
 * memoire a zero.
 */
void* memAllocZ(long size,const char* name)
{
	void* p = memAlloc(size, name);
	
	if (p == NULL)
	{
		return NULL;
	}
	
	memset(p, 0, size);
	return p;
}



// ***************************************************************
// ***************************************************************
/**
 * Realloue un bloc memoire deja alloue avec memAllocZ() ou memAlloc()
 */
void* memRealloc(void *ptr, long size, const char* name)
{
	Mutex_MemMgr.WaitOne();

#ifdef DEBUG_ALLOCATION_AND_DEALLOCATION_MESSAGE
	char textAllocation[LONG_STR];
	sprintf(textAllocation, "memRealloc: alloction size (%ld), bloc name\"%s\"", size, name);
	if (log != NULL) log->AddMessage(textAllocation, LOGFILE_DEBUG, LOGFILE_MEMORY);
#endif 

	char text[STR_LONG];
	if (size < 0)
	{
		sprintf(text, "memRealloc error: negative size (%ld), bloc name\"%s\"", size, name);
		LOG(text);
#ifdef _DEBUG
		MessageBoxA(NULL, text, "MemMgr Error", MB_OK|MB_ICONERROR);
#endif //_DEBUG
#ifdef _DEBUG_LINUX_
		//wxFMessageBox( text, "", wxOK|wxICON_ERROR);
#endif
		Mutex_MemMgr.Release();
		return NULL;
	}

	if (size >= (1024*1024*1024)) // 1 Go
	{
		sprintf(text, "memRealloc error: size too great (%.2f Gb)", (float) size / (1024*1024*1024));
		LOG(text);
#ifdef _DEBUG
		MessageBoxA(NULL, text, "MemMgr Error", MB_OK|MB_ICONERROR);
#endif //_DEBUG
#ifdef _DEBUG_LINUX_
		//wxFMessageBox( text, "", wxOK|wxICON_ERROR);
#endif
		Mutex_MemMgr.Release();
		return NULL;
	}

	TypMemDescr *md = NULL;
	// Trouve le bloc memoire correspondant a 'ptr'
	for (TypLinkedList *ml = mem_list; ml; ml = ml->next)
	{
		TypMemDescr *mdtmp = (TypMemDescr*) ml->e;
		if (mdtmp->ptr == ptr)
		{
			md = mdtmp;
			break;
		}
	}


	if (!md)
	{
#ifdef DEBUG_MEM_MGR_INFO
		sprintf(text, "memRealloc : block not found, first time allocation");
		if (log != NULL) log->AddMessage(text, LOGFILE_DEBUG, LOGFILE_MEMORY);
#endif
		Mutex_MemMgr.Release();
		return memAllocZ(size, name);
	}

	// Garde en memoire les flags de fin de bloc
	DWORD flags[2];
	flags[0] = ((DWORD*)(((char*)md->ptr)+md->size))[0];
	flags[1] = ((DWORD*)(((char*)md->ptr)+md->size))[1];

	// Reallocation du bloc memoire
	void *newptr = realloc(md->ptr_orig, size + 16);
	if (!newptr)
	{
		sprintf(text, "memRealloc error: reallocation failed");
		LOG(text);
#ifdef _DEBUG
		MessageBoxA(NULL, text, "MemMgr Error", MB_OK|MB_ICONERROR);
#endif //_DEBUG
#ifdef _DEBUG_LINUX_
		//wxFMessageBox( text, "", wxOK|wxICON_ERROR);
#endif
		Mutex_MemMgr.Release();
		return NULL;
	}

#ifdef DEBUG_MEM_MGR_INFO
	if (log != NULL) log->AddMessage(LOGFILE_DEBUG, LOGFILE_MEMORY, "memRealloc %s, %ld bytes", md->name, size);
#endif 

	// Change l'adresse du bloc memoire
	md->size = size;
	md->ptr_orig = (char*) newptr;
	md->ptr = (md->ptr_orig) + 8;
	if (name != NULL)
	{
		strncpy(md->name, name, STR_LONG - 1);
	}

	// Restaure les flags de fin de bloc tels qu'ils etaient avant la reallocation
	((DWORD*)(((char*)md->ptr)+size))[0] = flags[0];
	((DWORD*)(((char*)md->ptr)+size))[1] = flags[1];

	Mutex_MemMgr.Release();
	return md->ptr;
}



// ***************************************************************
// ***************************************************************
// memRealloc
void memFree( void* ptr )
{
	Mutex_MemMgr.WaitOne();
	volatile TypLinkedList* ml;
	ml = mem_list;
	char text[STR_LONG];
	
	if (ptr == NULL)
	{
		sprintf(text, "memFree null pointer");
#ifdef DEBUG_MEM_MGR_INFO
		if (log != NULL) log->AddMessage(text, LOGFILE_DEBUG, LOGFILE_MEMORY);
#endif
#ifdef _DEBUG
		MessageBoxA(NULL, text, "MemMgr Debug", MB_OK);
#endif //_DEBUG
#ifdef _DEBUG_LINUX_
		//wxFMessageBox( text, "", wxOK|wxICON_ERROR);
#endif
		Mutex_MemMgr.Release();
		return;
	}

	while(ml)
	{
		if(((TypMemDescr*)(ml->e))->ptr==ptr)
		{
#ifdef DEBUG_MEM_MGR_INFO
			if (log != NULL) log->AddMessage(LOGFILE_DEBUG, LOGFILE_MEMORY, "memFree %s", ((TypMemDescr*)(ml->e))->name);
#endif 

			if( (((DWORD*)ptr)[-1]!=MEM_TEST_VALUE) || (((DWORD*)ptr)[-2]!=MEM_TEST_VALUE) )
			{
				sprintf(text,"Block \\""%s\\"" of %ld bytes corrupted at the beginning",((TypMemDescr*)(ml->e))->name,((TypMemDescr*)(ml->e))->size);
				LOG(text);
#ifdef _DEBUG
				MessageBoxA(NULL, text, "MemMgr Error", MB_OK|MB_ICONERROR);
#endif //_DEBUG
#ifdef _DEBUG_LINUX_
				//wxFMessageBox( text, "", wxOK|wxICON_ERROR);
#endif
			}
			
			if( (((DWORD*)(((char*)ptr)+((TypMemDescr*)(ml->e))->size))[0]!=MEM_TEST_VALUE) || (((DWORD*)(((char*)ptr)+((TypMemDescr*)(ml->e))->size))[1]!=MEM_TEST_VALUE) )
			{
				sprintf(text,"Block \\""%s\\"" of %ld bytes corrupted at the end",((TypMemDescr*)(ml->e))->name,((TypMemDescr*)(ml->e))->size);
				LOG(text);
#ifdef _DEBUG
				MessageBoxA(NULL, text, "MemMgr Error", MB_OK|MB_ICONERROR);
#endif //_DEBUG
#ifdef _DEBUG_LINUX_
				//wxFMessageBox( text, "", wxOK|wxICON_ERROR);
#endif
			}

#ifdef DEBUG_ALLOCATION_AND_DEALLOCATION_MESSAGE
			char textAllocation[LONG_STR];
			sprintf(textAllocation, "memFree: alloction size (%ld), bloc name\"%s\"", ((TypMemDescr*)(ml->e))->size, ((TypMemDescr*)(ml->e))->name);
			if (log != NULL) log->AddMessage(textAllocation, LOGFILE_DEBUG, LOGFILE_MEMORY);
#endif 

			TypMemDescr* md=(TypMemDescr*)(ml->e);
			free(md->ptr_orig);
			mem_list=lDelItem(mem_list,ml->e);
			free(md);
			Mutex_MemMgr.Release();
			return;
		}
		ml=ml->next;
	}
	
	LOG("memFree: Block not found");
#ifdef _DEBUG
	MessageBoxA(NULL, "memFree: Block not found", "MemMgr Error", MB_OK|MB_ICONERROR);
#endif //_DEBUG
#ifdef _DEBUG_LINUX_
	sprintf( text, "memFree: Block not found: %d ", ptr);
	//wxFMessageBox( text, "", wxOK|wxICON_ERROR);
#endif
	Mutex_MemMgr.Release();
}


// ***************************************************************
// ***************************************************************
void memCheck()
{
	Mutex_MemMgr.WaitOne();
	TypLinkedList* ml=mem_list;
	TypLinkedList* mll;
	char text[STR_LONG];
	while(ml && memIsValidPtr((void*)ml))
	{
		mll=ml->next;
		if (!memIsValidPtr((void*)(ml->e)))
		{
			LOG("memCheck");
			Mutex_MemMgr.Release();
			return;
		}
		DWORD* ptr=(DWORD*)((TypMemDescr*)(ml->e))->ptr;

		if( (((DWORD*)ptr)[-1]!=MEM_TEST_VALUE) || (((DWORD*)ptr)[-2]!=MEM_TEST_VALUE) )
		{
			sprintf(text,"Block \\""%s\\"" of %ld bytes corrupted at the beginning",((TypMemDescr*)(ml->e))->name,((TypMemDescr*)(ml->e))->size);
			LOG(text);
#ifdef _DEBUG
			MessageBoxA(NULL, text, "MemMgr Debug", MB_OK);
#endif //_DEBUG
#ifdef _DEBUG_LINUX_
			//wxFMessageBox( text, "", wxOK|wxICON_ERROR);
#endif
		}
		if( (((DWORD*)(((char*)ptr)+((TypMemDescr*)(ml->e))->size))[0]!=MEM_TEST_VALUE) || (((DWORD*)(((char*)ptr)+((TypMemDescr*)(ml->e))->size))[1]!=MEM_TEST_VALUE) )
		{
			sprintf(text,"Block \\""%s\\"" of %ld bytes corrupted at the end",((TypMemDescr*)(ml->e))->name,((TypMemDescr*)(ml->e))->size);
			LOG(text);
#ifdef _DEBUG
			MessageBoxA(NULL, text, "MemMgr Debug", MB_OK);
#endif //_DEBUG
#ifdef _DEBUG_LINUX_
			//wxFMessageBox( text, "", wxOK|wxICON_ERROR);
#endif
		}

		ml=mll;
	}
	Mutex_MemMgr.Release();
}


// ***************************************************************
// ***************************************************************
void memCheckIntegrity()
{
	Mutex_MemMgr.WaitOne();
	TypLinkedList* ml=mem_list;
	TypLinkedList* mll;
	char text[STR_LONG];
	while(ml)
	{
		mll=ml->next;
		sprintf(text,"Block \\""%s\\"" of %ld bytes not disallocated.\nDisallocate it ?",((TypMemDescr*)(ml->e))->name,((TypMemDescr*)(ml->e))->size);

		LOG(text);

#ifdef _DEBUG
		if (MessageBoxA(NULL, text, "Question", MB_YESNO | MB_ICONQUESTION) == IDYES)
#endif //_DEBUG
#ifdef _DEBUG_LINUX_
		  //wxFMessageBox( text, "", wxOK|wxICON_ERROR);
#endif
		{
			if(ml->e)
			{
				free((char*) ((TypMemDescr*) (ml->e))->ptr_orig);
			}
			else
			{
				break;
			}
		}
		ml=mll;
	}
	Mutex_MemMgr.Release();
}

void memTotalUsedMemory(int *szMem1, int *comp1 )
{
	Mutex_MemMgr.WaitOne();
	TypLinkedList* ml=mem_list;
	TypLinkedList* mll;
	long int szMem = 0, in;
	int comp = 0;
	while(ml)
	{
		mll=ml->next;
		in = ((TypMemDescr*)(ml->e))->size;
		szMem += ((TypMemDescr*)(ml->e))->size;
		ml=mll;
		comp += 1;
	}

	/*char text[LONG_STR];
	sprintf(text,"Mem Total %ld bytes for %d allocations",szMem, comp);
	if (log != NULL) log->AddMessage(text, LOGFILE_ERROR, LOGFILE_MEMORY);*/
	*szMem1 = szMem;
	*comp1 = comp;

	Mutex_MemMgr.Release();
}
