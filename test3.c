#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "header.h"
#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100

//! \brief Generate the hash slot number for each string.
int make_hash(char* c) {
  return (hash1(c)%(MAX_HASH_SLOT - 1));
}

/*pseudocode*/
// 1 malloc a DICTIONARY to d
// 2 initialize start end to null
// 3 initialize each hash slot to null
DICTIONARY* InitDictionary() {
  DICTIONARY* d = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  MALLOC_CHECK(d);
  d->start = NULL;
  d->end = NULL;
  int i;
  for (i = 0; i < MAX_HASH_SLOT; i++) {
    d->hash[i] = NULL;
  }
  return d;
}



/*pseudocode*/
// 1 h = hash value of the key
// 2 if (dict->start is null, implies dict is empty)
// 3   add the new DNODE to the dict,
// 4   updating start and end pointer
// 5 else (there is already some DNODE in dict)
// 6   if (the h slot is occupied)
// 7     for each DNODE with hash value h
// 8        find is there a DNODE with the same key
// 9        if find, do nothing
// 10    end
// 11    if (not find a DNODE with the same key)
// 12      add the DNODE after the last DNODE with hash value h
// 13  else (the h slot is not occupied)
// 14    add the new DNODE to the end, update end
// 15    update hashtable
// 16 Done
void DAdd(DICTIONARY* dict, char* data) {
  MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    MALLOC_CHECK(dict->start);
    dict->start->prev = dict->start->next = NULL; 
    dict->start->data = data;
    dict->hash[h] = dict->start;
    dict->end = dict->hash[h];
    //BZERO(dict->start->key, KEY_LENGTH);
    //strncpy(dict->start->data, data, strlen(data));
  } else {
    DNODE* d;
    //! Not the first element.
    if (dict->hash[h]) {
      //! Same hash.
      int flag = 0; //!< zero the key is not in our dictionary, one if does
      //! First, we want to see is this key already in our dictionary
      for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);d = d->next) {
        if (strcmp(d->data, data)==0) {
		flag = 1;		
		break;
/*          //! We find the same key.
          if (d->data != NULL)
            free(d->data);
          d->data = data;
          
          break; */
        }        
      }
      //! not in.
      if (flag == 0) {
        //! We didin't find the same key.
        /*if (d == NULL)
          d = dict->end;
        else*/
        d = d->prev;
        DNODE* dd = (DNODE*)malloc(sizeof(DNODE));
        MALLOC_CHECK(dd);
        //dd = d->next;
        dd->prev = d;
        if (d->next == NULL){
		dd->next == NULL;        	
		dict->end = dd;
	}else{
		dd->next=d->next;
		d->next->prev = dd;        
	}
	d->next = dd;
        //BZERO(dd->key, KEY_LENGTH);
       // strncpy(dd->data, data, strlen(data));
        dd->data = data;
      }
     } else {
      //! No same hash, create at the end of the list.
      DNODE* d = (DNODE*)malloc(sizeof(DNODE));
      d->next = NULL;
      d->prev = dict->end;
      dict->end->next = d;
      //! add to our cash slot
      dict->hash[h] = d;
      d->data = data;
     // BZERO(d->key, KEY_LENGTH);
     // strncpy(d->data, data, strlen(data));
      //! change the end of our list
      dict->end = d;
    }
  }
}


/*Pseudocode*/
// 1 get the hash value of key, save to h
// 2 get the pointer of hash slot h
// 3   for (each DNODE d with same hash value)
// 4     if (d is the same key)
// 5       return data of d
// 6   end
// 7 return null
void* GetDataWithKey(DICTIONARY* dict, char* dat) {
  char datacheck[15];
  strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(datacheck);
  //! This speed up the process.
  if (dict->hash[h] == NULL)
    return NULL;
  //! ok, we have the hash, so we find the actual key.
  for (d = dict->hash[h]; (d!=NULL) && (make_hash(d->data) == h);
       d = d->next) 
    if (strcmp(d->data, dat)==0) 
      return d->data;
  return NULL;
}


int searchKey(char* datastring){
	int i;
	
	char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		//printf("%s",keywrd[i]);
		//datastring= "\0";
		//printf("mkh %d\n",make_hash(keywrd[i]));
		//strcpy(datastr,keywrd[i]);	
		DAdd(dict,keywrd[i]);
	}
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		printf("<Keywrd: '%s'>\n", datastring);
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}

