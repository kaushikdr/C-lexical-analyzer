#include<stdio.h>
#include<string.h>
//#include "iden.c"
#include <time.h>


#include <stdlib.h>
#include <memory.h>

#include "hash.h"
#include "dictionary.h"
#define MAX_HASH_SLOT 100



#include <sys/types.h>
#include <regex.h>



int check(char* data,regex_t regex_iden,regex_t regex_charconst,regex_t regex_intconst,regex_t regex_floatconst,regex_t regex_strconst){
        
        int reti_charconst,reti_iden,reti_intconst,reti_floatconst;
        char datastr[100];
	//char word[15];
	//scanf("%s",word);
	strcpy(datastr,data);
		/* Compile regular expression */
		/*identifier check*/
		reti_iden = regexec(&regex_iden, datastr, 0, NULL, 0);	/* Execute regular expression */	
		if( !reti_iden ){
		      printf("Identifier : %s\n",data);
			//printf("IdenMAtch\n");
			return 0;
		}

		/*Charaacter conastant check*/
		reti_charconst = regexec(&regex_charconst, datastr, 0, NULL, 0); /* Execute regular expression */
		if( !reti_charconst ){
		        printf("Character Constant: %s\n",data);
			//printf("CharConstMAtch\n");
			return 0;		
		}


		/*integer constant check*/
		reti_intconst = regexec(&regex_intconst, datastr, 0, NULL, 0);  /* Execute regular expression */
		if( !reti_intconst ){
		        printf("Integer Constant: %s\n",data);
			//printf("IntMAtch\n");		
			return 0;		
		}

		/*float constant check*/		
		reti_floatconst = regexec(&regex_floatconst, datastr, 0, NULL, 0);  /* Execute regular expression */
       		if( !reti_floatconst ){
		        printf("Float Constant: %s\n",data);
			//printf("FloatMAtch\n");		
			return 0;
		} 
		
		
	
		
		
		
		
		
		
		else {
			//printf("Invalid: %s\n---Exiting---\n",data); //&& reti_strconst == REG_NOMATCH
			printf("Unrecognised: %s\n",data);			
					
		}
		
		return 0;

}




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
  //MALLOC_CHECK(d);
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
  //MYASSERT(strlen(data) > 0);
  int h = make_hash(data);
  if (dict->start == NULL) {
    //! The first element of our dictionary
    //! I assume \a dict->end is also NULL
    //MYASSERT(dict->end == NULL);
    dict->start = dict->end = (DNODE*)malloc(sizeof(DNODE));
    //MALLOC_CHECK(dict->start);
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
        //MALLOC_CHECK(dd);
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
  //strcpy(datacheck,dat);
  DNODE* d;  
  int h = make_hash(dat);
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

/*function for keyword search*/
int searchKey(DICTIONARY* dict, char* datastring){
	int i;
	
	
	//printf("\nEnter the keyword to be searched:");
	
	//scanf("%s",datastring);
	//gets(datastring);
	//strcpy(datastr,datastring);
	if(GetDataWithKey(dict,datastring)){
		
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);
		return 1;
	}
	else
		memset(&dict, 0, sizeof(dict));
		//CleanDictionary(dict);		
		return 0;

}



void main()
{
clock_t begin, end;
double time_spent;
begin = clock();

regex_t regex_iden,regex_charconst,regex_intconst,regex_floatconst,regex_strconst;
int reti_charconst,reti_iden,reti_intconst,reti_floatconst;

FILE *fp;
char c;
int i=0,rel=0,arithasgn=0,asgn=0,log=0,comnt=0,unrec=0;
char temp[200];

char *keywrd[35]={ "return", "unsigned", "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",  "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",  "void", "volatile", "while" };
	int num;
	//unsigned long c;
	char datastr[15];
	//data = (char *)malloc(sizeof(char)*15);
	DICTIONARY* dict;
	dict = InitDictionary();
	for (i=0;i<32;i++){
		DAdd(dict,keywrd[i]);        //add keywords to hash table
	}


/*compile regular expression*/
reti_iden = regcomp(&regex_iden, "^([a-zA-Z]|_)(([a-zA-Z0-9]*)|(_[a-zA-Z0-9]_*)|(_[a-zA-Z0-9]*)|([a-zA-Z0-9]_*))$", REG_EXTENDED);
reti_charconst = regcomp(&regex_charconst, "^(')([a-zA-Z0-9]*)(')$", REG_EXTENDED);
reti_intconst = regcomp(&regex_intconst, "^([0-9]*)(([0-9])|(u)|(l)|(ll)|(ul)|(ull))$", REG_EXTENDED);
reti_floatconst = regcomp(&regex_floatconst, "^(([0-9][0-9]*\\.?[0-9]*)|(\\.[0-9]+))([Ee][+-]?[0-9]+)?(f?)(l?)$", REG_EXTENDED);
if( reti_iden || reti_charconst || reti_intconst || reti_floatconst){ fprintf(stderr, "Could not compile regex\n"); exit(1); }


fp=fopen("test3.c","r");
temp[0] = '\0';
while(1)
{
c=fgetc(fp);

if(c==EOF)
break;
else
{
temp[i+1] = temp[i];
temp[i]=c;

/*if rel flag is encountered i.e, previous character is either < or > or !, 
 then 
 if present character is =, generate token relational operator, empty variable,
 if present character and previous character are same and previous character is not !, i.e, if << or >>, then generate token bitwise shift operater,
 if whitespace or anything else is encountered, then if previous character is !,generate token logical operator, else generate token relational operator,empty variable,	
*/
if(rel){
	if(c=='='){
		if (temp[0]!='\0'){
		//printf("%s\n",temp);
			printf("Relational Operator: %s\n",temp);
		}
		i=-1;
		temp[0]='\0';
	}
	else if(c==temp[i-1] && c!='!'){
		printf("Bitwise Shift Operator: %s\n",temp);
		i=-1;
		temp[0]='\0';
	}
	else if(c==' '){
		temp[i]='\0';
		if (temp[i-1]=='!'){
			printf("Logical Operator: %s\n",temp);
		}
		else{		
			//printf("%s\n",temp);
			printf("Relational Operator: %s\n",temp);	
		}
		
		/*empty variable(when whitespace, present character is not stored in the variable again)*/		
		i=-1;                   
		temp[0]='\0';           
	}
	else{
		temp[i]='\0';
		if (temp[i-1]=='!'){
			printf("Logical Operator: %s\n",temp);
		}
		else{		
			//printf("%s\n",temp);
			printf("Relational Operator: %s\n",temp);	
		}

		/*empty variable */
		i=0;
		temp[i]=c;   //present character is stored in the variable again
		temp[i+1]='\0';
	}
	rel=0;  //flag reset
}

/*if arithasgn flag is encountered i.e, previous character is either + or - or * or / or %, 
 then 
  if present character is =, generate token Arithmatic Assignment Operator, empty variable,
  if present character is * and previous character is /, empty the variable, ignore until * and /,
  if present character is / and previous character is /, ignore until \n,empty the variable,
  if present character is + and previous character is +, generate token Increment Operator, empty the variable,
  if present character is - and previous character is -, generate token Decrement Operator, empty the variable,
  else if present character is whitespace or anything else, generate token Arithmatic Operator, empty the variable,
*/
else if(arithasgn){
	if(c=='='){
		printf("Arithmatic Asignment Operator: %s\n",temp);
		i=-1;
		temp[0]='\0';
	}
	else if(c=='*' && temp[i-1]=='/'){
		i=-1;
		temp[0]='\0';
		while(1){
			c=fgetc(fp);
			if(comnt){
				if (c=='/'){
					comnt = 0;
					break;
				}			
			}			
			else if(c=='*'){
				comnt = 1;			
			}
			else{
				comnt=0;			
			}
			
			
		}
	}	
	else if(c=='/' && temp[i-1]=='/'){
		while(c!='\n'){
			c=fgetc(fp);
			//if(c=='\n'){
			//	break;			
			//}
		}
	i=-1;
	temp[0]='\0';
	}
	else if(c=='+' && temp[i-1]=='+'){
		printf("Increment Operator: %s\n",temp);
		i=-1;
		temp[0]='\0';
	}
	else if(c=='-' && temp[i-1]=='-'){
		printf("Decrement Operator: %s\n",temp);
		i=-1;
		temp[0]='\0';
	}
	else if(c==' '){
		temp[i]='\0';
		printf("Arithmatic Operator: %s\n",temp);
		i = -1;
		temp[0]='\0';
	}
	
	else{
		temp[i]='\0';
		printf("Arithmatic Operator: %s\n",temp);		
		i=0;
		temp[i]=c;  //present character is stored in the variable while emptying the variable
		temp[i+1]='\0';
	}
	arithasgn=0;//flag reset
}

/*if asgn flag is encountered i.e, previous character is =, 
 then
  if present character is =, generate token Relational Operator, empty the variable,
  if present character is ", check for string constant. if \n is encountered before ", generate unrecognised, empty the variable,
  else if present character is whitespace or anything else, generate token Asignment Operator, empty the variable,
*/
else if(asgn){
	if(c=='='){
		printf("Relational Operator: %s\n",temp);
		i=-1;
		temp[0]='\0';
	}
	
	else if(c=='"'){		
		do{
			if(c=='\n'){
				printf("Unrecognised: %s\n",temp);
				unrec=1;
				break;
			}
			c=fgetc(fp);
			i++;
			temp[i+1] = temp[i];
			temp[i] = c;
		}while(c!='"');
		if (unrec==0)
			printf("StringConst: %s\n",temp);
		i=-1;
		temp[0]='\0';
		unrec = 0;	
	}
	//else if(isdigit(c)||c=='.'){
		
	
		
	//}
	else if(c==' '){
		temp[i]='\0';
		printf("Asignment Operator: %s\n",temp);
		i=-1;
		temp[0]='\0';
	}
	else{
		temp[i]='\0';
		printf("Asignment Operator: %s\n",temp);		
		i=0;
		temp[i]=c;  //present character is stored in the variable while emptying the variable
		temp[i+1]='\0';
		
	}
	asgn=0; //flag reset
}


/*if asgn flag is encountered i.e, previous character is either & or |, 
 then
  if present character and previous character are same, the generate token Logical Operator,
  else if present character is whitespace or anything else, generate token Asignment Operator, empty the variable,
*/
else if(log){
	if(c==temp[i-1]){
		printf("Logical Operator: %s\n",temp);
		i=-1;
		temp[0]='\0';
	}
	else if(c==' '){
		temp[i]='\0';
		printf("Bitwise Operator: %s\n",temp);
		i=-1;
		temp[0]='\0';
	}
	else{
		temp[i]='\0';
		printf("Bitwise Operator: %s\n",temp);		
		i=0;
		temp[i]=c;  //present character is stored in the variable while emptying the variable
		temp[i+1]='\0';
	}
	log=0; //flag reset
}


/*if # is encountered, ignored till \n */
else if(c=='#'){
	printf("ERORR! Preprocessor directive encountered\n");
	while(c!='\n'){
			c=fgetc(fp);
	}
	i=-1;
	temp[0]='\0';
}

/*condition for exponent.
when a digit or . or e or (+ or - with character e before that) is encountered and the first character is either digit or ., it is appended in 
the variable temp
*/
else if((isdigit(c) || c=='.' || c=='e'||c=='E' || ((c=='+'||c=='-')&&(temp[i-1]=='e'||temp[i-1]=='E'))) && (isdigit(temp[0])||temp[0]=='.')){
		
	//while(isdigit(c)||((c=='+'||c=='-')&&temp[i-1]=='e')||c=='.'||c=='e'){
		temp[i]=c;
		temp[i+1]='\0';		
		//c=fgetc(fp);
		//i++;
	//}
	//check(temp);
	
}

/*if a whitespace or newline or tab is encountered, check for keyword or identifier or constant and the empty the variable temp*/
else if(c==' '||c=='\n'||c=='\t'||c=='\r')
{
	//temp[i-1]=temp[i];
	temp[i]='\0';
	if (temp[0]!='\0'){
		//printf("%s\n",temp);
		if(searchKey(dict,temp)){      //keyword check
			printf("Keyword: %s\n", temp);
		}
		else{
			check(temp,regex_iden,regex_charconst,regex_intconst,regex_floatconst,regex_strconst);  //identifier or constant check
		}
	}
	i=-1;
	temp[0]='\0';
}


/*if = is encountered, check for keyword or identifier or constants for the string stored in variable first, then empty the variable,
  then raise a flag asgn to 1. This flag and next character will decide token to generate.
*/
else if(c=='='){
	temp[i]='\0';
	if (temp[0]!='\0'){
		//printf("%s\n",temp);
		if(searchKey(dict,temp)){         //keyword check
			printf("Keyword: %s\n", temp);
		}
		else{
			check(temp,regex_iden,regex_charconst,regex_intconst,regex_floatconst,regex_strconst);  //identifier or constants check
		}
	}	
	i=0;
	temp[i]=c;
	temp[i+1]='\0';
	asgn=1;       //raise flag 
}

/*if seperators are encountered, check for keyword or identifier or constants for the string stored in variable first, then empty the variable */
else if(c=='('||c==')'||c=='{'||c=='}'||c=='['||c==']'||c==':'||c==','||c==';'){
	temp[i]='\0';
	i=-1;
	if (temp[0]!='\0'){
		//printf("%s\n",temp);
		if(searchKey(dict,temp)){   //keyword check
			printf("Keyword: %s\n", temp);
		}
		else{
			check(temp,regex_iden,regex_charconst,regex_intconst,regex_floatconst,regex_strconst);  //identifier or constants check
		}
	}	
	printf("Separator: %c\n",c);
	temp[0]='\0';
	
}


/*if arithmatic operator is encountered, check for keyword or identifier or constants for the string stored in variable first, then empty the variable, then raise a flag arithasgn to 1. This flag and next character will decide token to generate. */

else if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%' ){	
	temp[i]='\0';
	//printf("%s\n",temp);		
	if (temp[0]!='\0'){
		//printf("%s\n",temp);
		if(searchKey(dict,temp)){           //keyword check
			printf("Keyword: %s\n", temp);
		}
		else{
			check(temp,regex_iden,regex_charconst,regex_intconst,regex_floatconst,regex_strconst);  //identifier or constants check
		}
	}	
	i=0;
	temp[i]=c;
	temp[i+1]='\0';
	arithasgn=1;   //raise flag
}

/*if relational operator or logical ! is encountered, check for keyword or identifier or constants for the string stored in variable first, then empty the variable, then raise a flag rel to 1. This flag and next character will decide token to generate.*/
else if(c=='<'||c=='>'||c=='!'){
	temp[i]='\0';
	if (temp[0]!='\0'){
		//printf("%s\n",temp);
		if(searchKey(dict,temp)){  //keyword check
			printf("Keyword: %s\n", temp);
		}
		else{
			check(temp,regex_iden,regex_charconst,regex_intconst,regex_floatconst,regex_strconst);  //identifier or constants check
		}
	}	
	i=0;
	temp[i]=c;
	temp[i+1]='\0';
	rel=1;  //raise flag
	
}

/*if logical operator is encountered, check for keyword or identifier or constants for the string stored in variable first, then empty the variable, then raise a flag log to 1. This flag and next character will decide token to generate.*/
else if(c=='&'||c=='|'){
	temp[i]='\0';
	if (temp[0]!='\0'){
		//printf("%s\n",temp);
		if(searchKey(dict,temp)){  //keyword check
			printf("Keyword: %s\n", temp);
		}
		else{
			check(temp,regex_iden,regex_charconst,regex_intconst,regex_floatconst,regex_strconst);  //identifier or constants check
		}
	}	
	i=0;
	temp[i]=c;
	temp[i+1]='\0';
	log=1;    //raise flag
}

/*if ~ is encountered, check for keyword or identifier or constants for the string stored in variable first, then generate token for bitwise not, the empty the variable*/
else if(c=='~'){
	temp[i]='\0';
	i=-1;
	if (temp[0]!='\0'){
		//printf("%s\n",temp);
		if(searchKey(dict,temp)){
			printf("Keyword: %s\n", temp);
		}
		else{
			check(temp,regex_iden,regex_charconst,regex_intconst,regex_floatconst,regex_strconst);
		}
	}	
	printf("Bitwise NOT: %c\n",c);
	temp[0]='\0';
	
}



/*if " is encountered, check for keyword or identifier or constants for the string stored in variable first, the empty the variable,
 then append characters until " or \n is encountered. if \n is encountered, generate unrecognised string and raise a flag unrec to 1 and break from the loop. if unrec is not raised to 1 and " is encountered, generate token String. Empty the variable and reset unrec to 0.
 */
else if(c=='"'){
	temp[i]='\0';
	//i=-1;
	
	/*check for keyword or identifier or constants*/
	if (temp[0]!='\0'){
		//printf("%s\n",temp);
		if(searchKey(dict,temp)){
			printf("Keyword: %s\n", temp);
		}
		else{
			check(temp,regex_iden,regex_charconst,regex_intconst,regex_floatconst,regex_strconst);
		}
	}
	
	/*empty variable and storing temp[0] with the encountered character*/
	i=0;
	temp[i]=c;
	temp[i+1]='\0';	
	
	//append until \n or "
	do{	
		if(c=='\n'){
			printf("Unrecognised: %s\n",temp);
			unrec=1;  //raise flag
			break;
		}
		c=fgetc(fp);
		i++;
		temp[i+1] = temp[i];
		temp[i] = c;
	}while(c!='"');
	if (unrec==0)
		printf("String Constant: %s\n",temp);
	i=-1;
	temp[0]='\0';
	unrec = 0;	
}

/*if ^ is encountered, check for keyword or identifier or constants for the string stored in variable first, then generate token for bitwise not, the empty the variable*/
else if(c=='^'){
	temp[i]='\0';
	i=-1;
	if (temp[0]!='\0'){
		//printf("%s\n",temp);
		if(searchKey(dict,temp)){
			printf("Keyword: %s\n", temp);
		}
		else{
			check(temp,regex_iden,regex_charconst,regex_intconst,regex_floatconst,regex_strconst);
		}
	}	
	printf("Bitwise XOR: %c\n",c);
	temp[0]='\0';
	
}


}
i++;
}


fclose(fp);
end = clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
//printf("%ld",CLOCKS_PER_SEC);
printf("\n\nExecution Time: %g\n",time_spent);
}

