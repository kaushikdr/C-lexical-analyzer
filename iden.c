#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>








int check(char* data){
        regex_t regex_iden,regex_charconst,regex_intconst,regex_floatconst,regex_strconst;
        int reti_charconst,reti_iden,reti_intconst,reti_floatconst,reti_strconst;
        char msgbuf[100],msgbuf1[100],datastr[100];
	//char word[15];
	//scanf("%s",word);
	
		/* Compile regular expression */
		reti_iden = regcomp(&regex_iden, "^([a-zA-Z]|_)(([a-zA-Z0-9]*)|(_[a-zA-Z0-9]_*)|(_[a-zA-Z0-9]*)|([a-zA-Z0-9]_*))$", REG_EXTENDED);
		reti_charconst = regcomp(&regex_charconst, "^(')([a-zA-Z0-9]*)(')$", REG_EXTENDED);
		//reti_strconst = regcomp(&regex_strconst, "^""$", REG_EXTENDED);
		reti_intconst = regcomp(&regex_intconst, "^([0-9]*)(([0-9])|(u)|(l)|(ll)|(ul)|(ull))$", REG_EXTENDED);
		reti_floatconst = regcomp(&regex_floatconst, "^(([0-9][0-9]*\\.?[0-9]*)|(\\.[0-9]+))([Ee][+-]?[0-9]+)?(f?)(l?)$", REG_EXTENDED);        
		if( reti_iden || reti_charconst || reti_intconst || reti_floatconst){
			fprintf(stderr, "Could not compile regex\n"); 
			exit(1);
		}
		strcpy(datastr,data);
	/* Execute regular expression */
		reti_iden = regexec(&regex_iden, datastr, 0, NULL, 0);
		reti_charconst = regexec(&regex_charconst, datastr, 0, NULL, 0);
		reti_intconst = regexec(&regex_intconst, datastr, 0, NULL, 0);
		reti_floatconst = regexec(&regex_floatconst, datastr, 0, NULL, 0);
		//reti_strconst = regexec(&regex_strconst, data, 0, NULL, 0);
		if( !reti_iden ){
		      printf("Identifier : %s\n",data);
			//printf("IdenMAtch\n");
		}
		else if( !reti_charconst ){
		        printf("Character Constant: %s\n",data);
			//printf("CharConstMAtch\n");		
		}
		else if( !reti_intconst ){
		        printf("Integer Constant: %s\n",data);
			//printf("IntMAtch\n");		
		}
		else if( !reti_floatconst ){
		        printf("Float Constant: %s\n",data);
			//printf("FloatMAtch\n");		
		}
		/*else if( !reti_strconst ){
		        printf("<StringConst: `%s`>\n",data);
			//printf("FloatMAtch\n");		
		}*/
		else if( reti_iden == REG_NOMATCH && reti_charconst == REG_NOMATCH && reti_intconst == REG_NOMATCH && reti_floatconst == REG_NOMATCH  ){
			//printf("Invalid: %s\n---Exiting---\n",data); //&& reti_strconst == REG_NOMATCH
			printf("Unrecognised: %s\n",data);			
			//exit(1);		
		}
		else{
		        regerror(reti_iden, &regex_iden, msgbuf, sizeof(msgbuf));
			regerror(reti_charconst, &regex_charconst, msgbuf1, sizeof(msgbuf1));
			regerror(reti_intconst, &regex_intconst, msgbuf1, sizeof(msgbuf1));
			regerror(reti_floatconst, &regex_floatconst, msgbuf1, sizeof(msgbuf1));
			//regerror(reti_strconst, &regex_strconst, msgbuf1, sizeof(msgbuf1));
		        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
			fprintf(stderr, "Regex match failed: %s\n", msgbuf1);
		        exit(1);
		}

	/* Free compiled regular expression if you want to use the regex_t again */
		regfree(&regex_iden);
		regfree(&regex_charconst);
		regfree(&regex_floatconst);
		regfree(&regex_intconst);
		//regfree(&regex_strconst);

		return 0;

}
