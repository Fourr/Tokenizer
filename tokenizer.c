/*
 * tokenizer.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
  char *word;
	char type;
	char type2;
	char type3;
};

typedef struct TokenizerT_ TokenizerT;
 	
/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

char * TKGetNextToken( TokenizerT *tk);
TokenizerT *TKCreate( char * ts ) {
TokenizerT *Token = (TokenizerT*)malloc(sizeof(TokenizerT));
Token->word=(char*)malloc(sizeof(strlen(ts)));
	//int EOW =0;	
	int i=0;
 	int curr = 0;
	if(ts !=NULL) //Make sure that the char* that is passed into TKCreate is not NULL
	{
		//printf("%s\n", ts);
		int x = 0;
		char prev;
		if((ts[0] >= 'a' && ts[0] <= 'z') || (ts[0] >= 'A' && ts[0] <= 'Z'))
		{
			prev = 0;
		}
		else if(ts[0] > '0' && ts[0] <= '9')
		{
			//printf("gottem\n");
			prev = 1;
		
		}
		int size = strlen(ts);
		for(; i <= size; i++)
		{
 //This is Hexadecimal
			if(ts[i] == '0' &&( ts[i+1] == 'x' || ts[i+1] == 'X') &&( ts[i+2] >= '0' && ts[i+2] <= '9'))//&& prev!=1 && prev!=0) 	
			{
			//	printf("here\n");
					Token->word[x] = '\0';
	        TKGetNextToken(Token);
					x = 0;
				
				Token->type = 'h';
				Token->word[x] = '0';
				x++;
				i++;
				Token->word[x] =ts[i];
				x++;
				i++;
				//printf("%s\n", Token->word);
				while((ts[i] >= 'A' && ts[i] <= 'F')|| (ts[i] >= 'a' && ts[i] <= 'f') ||( ts[i] >= '0' && ts[i] <= '9'))
				{
						//printf("here\n");
						Token->word[x] = (char)ts[i];
						i++;
						x++;
				}
				Token->word[x] = '\0';
				TKGetNextToken(Token);
				x=0;
			
			i--;
				
			}
			//Dont tokenize comments
			//
			else if(ts[i] == '/' && ts[i+1] == '*')
			{
				//i++;
				while(ts[i] != '\0')
				{
					if(ts[i] == '*' && ts[i+1] == '/')
					{		//break;
							i++;
							break;
					}
				i++;
				}
				
				Token->word[x] = '\0';
				TKGetNextToken(Token);
			}
		else if(ts[i] == '/' && ts[i+1] == '/')
			{
				//i++;
				while(ts[i] != '\n')// && ts[i+1] != 'n')
				{
				
				i++;
				}
				
				Token->word[x] = '\0';
				TKGetNextToken(Token);
			}
			//sizeof()
			else if(ts[i] == 's' && ts[i+1] == 'i' && ts[i+2] == 'z' && ts[i+3] == 'e'&& ts[i+4] == 'o' && ts[i+5] == 'f' && ts[i+6] == '(')
				{
					 Token->word[x] = '\0';
	         TKGetNextToken(Token);
           x = 0;
					 curr=0;
			
					while(ts[i+curr] != '\0')
					{
						if(ts[i+curr] == ')')
						{
				/*			 Token->word[x] = '\0';
	      	  	 	TKGetNextToken(Token);
          			 x = 0;
								curr=0;
				*/
							Token->type = 's';
							for(; ts[i] != ')'; i++)
							{
						//	printf("in for loop\n");
								Token->word[x] = ts[i];
								x++;
							}
							Token->word[x] = ')';
							x++;
							i++;
							Token->word[x] = '\0';	
							TKGetNextToken(Token);
							x = 0;
							
						}
						curr++;
						//break;
					}
					//printf("i=%d\n",i);
					//i--;
					//curr = 0;
					//Token->word[x] = '\0';
					//TKGetNextToken(Token);
				//	x=0;
					//i--;
				//	x++;
				//	prev = 0;
			//	i--;
		/*		if(ts[i+1] != '\0')
				{
					if((ts[i+1] >= 'a' && ts[i+1] <= 'z') || (ts[i+1] >= 'A' && ts[i+1] <= 'Z'))
					{
						prev = 0;
					}
					if(ts[i+1] >= '0' && ts[i+1] <= '9')
					{
						prev = 1;
					}
				*/
				Token->word[x] = 's';
				x++;
				//x--;
				}
			//?true:false
			else if(ts[i] == '?' && ts[i+1] == 't' && ts[i+2] == 'r' && ts[i+3]=='u' &&ts[i+4] =='e' && ts[i+5] == ':' && ts[i+6] == 'f' && ts[i+7]=='a' && ts[i+8]=='l' && ts[i+9]=='s' && ts[i+10] == 'e')
			{
				//	printf("made it\n");
				 Token->word[x] = '\0';
         TKGetNextToken(Token);
         x = 0;
				 curr = 0;
				Token->type = 't';
				while(curr <= 10)
				{
					//printf("in while\n");
					Token->word[x] = ts[i];
				//	printf("Token->word = %s Token->tyep = %c\n", Token->word, Token->type);
					curr++;
					i++;
					x++;
				}
				Token->word[x] = '\0';
				TKGetNextToken(Token);
				x = 0;
				curr = 0;
				i--;	
			}
			//Float like a butterfly sting like a bee 
			else if(ts[i] == '.' && prev == 1 )
			{
			//	printf("here\n");
			if(ts[i+1]>= '0' && ts[i+1] <= '9')
				{ 
				Token->type = 'f';
				Token->word[x] = '.';
				x++;
				i++;
				
				while((ts[i] >= '0' && ts[i] <= '9') || (ts[i] == 'e'))
				{
					if(ts[i] == 'e')
					{
						if(ts[i+1] == '-')
						{
							if(ts[i+2] >= '0' && ts[i+2] <= '9')
							{
						//		Token->type = 'f';
							//	Token->word[x] =ts[i];
								//x++;
								//i++;	
								Token->word[x] = ts[i];
								x++;
								i++;
								Token->word[x] = ts[i];
								i++;
								x++;
							//	Token->word[x] = ts[i];
								//i++;
								//x++;
								
							}
						else
						{
							break;	
						}
						}
						else
						{
							break;	
						}
					}
				
				//Token->	
				Token->word[x] = (char)ts[i];
				i++;
				x++;
				}		

				Token->word[x] = '\0';
				TKGetNextToken(Token);
				x=0;
				i--;	
		}	
		}
			//Octal bitch	
			else if (ts[i] == '0' && prev!= 1 && (ts[i+1] >= '0' && ts[i+1] <= '9') )
			{	
				//		printf("token %s prev = %c\n", Token->word, prev);
						Token->word[x] = '\0';
	          TKGetNextToken(Token);
						x = 0;
				//		printf("i = %d\n", i);
					
				while( ts[i] >= '0' && ts[i] <= '9')
					{
							Token->type = 'o';
							Token->word[x] = (char)ts[i];
							i++;
							x++;
					}	//		printf("token %s\n", Token->word);
						Token->word[x] ='\0';
						TKGetNextToken(Token);
						x=0;
						i--;	
			}
			//single opperators
			else if((ts[i]!=' ') &&(ts[i]!='\0')&& !(ts[i] >=48 && ts[i] <=57) && !(ts[i] >=65 && ts[i] <=90) && !(ts[i]>=97 && ts[i] <=122))
				{	
				//	if(( ts[i+1] >= '0' && ts[i+1] <= '9') || (ts[i+1] >='a' && ts[i+1] <='z')||(ts[i+1] >='A' && ts[i+1] <='Z'))
			//	{
					//Token->word[x] = ts[i];
					//Token->type = Token->word[x];
					Token->word[x]='\0';
					TKGetNextToken(Token);
					x=0;
		
					 if((ts[i+1]!=' ') &&(ts[i+1]!='\0')&& !(ts[i+1] >=48 && ts[i+1] <=57) && !(ts[i+1] >=65 && ts[i+1] <=90) && !(ts[i+1]>=97 && ts[i+1] <=122))
						{
							if(ts[i]=='+' && ts[i+1]=='+')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								//printf("type2 = %c\n", Token->type2);
								TKGetNextToken(Token);
								Token->type2='d';
								i++;
								x=0;	
							}
						 else	if(ts[i]=='+' && ts[i+1]=='=')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								//printf("type2 = %c\n", Token->type2);
								TKGetNextToken(Token);
								Token->type2='d';
								i++;
								x=0;	
						}		
							else if(ts[i]=='-' && ts[i+1]=='>')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								//printf("type2 = %c\n", Token->type2);
								TKGetNextToken(Token);
								Token->type2='d';	
								i++;
								x=0;	
							}
								else if(ts[i]=='-' && ts[i+1]=='-')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								//printf("type2 = %c\n", Token->type2);
								TKGetNextToken(Token);
								Token->type2='d';		
								i++;
								x=0;	
							}
							else if(ts[i]=='-' && ts[i+1]=='=')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								//printf("type2 = %c\n", Token->type2);
								TKGetNextToken(Token);
								Token->type2='d';	
								i++;
								x=0;	
							}
							else if(ts[i]=='<' && ts[i+1]=='<')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								if(ts[i+2] == '=')
								{
									
									Token->type3='=';
									i++;
									//printf("got here %c\n", Token->type3);
								}	
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								TKGetNextToken(Token);
								Token->type2='d';	
								Token->type3='d';	
								i++;
								x=0;	
							}
						else if(ts[i]=='>' && ts[i+1]=='>')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								if(ts[i+2] =='=')
								{
									i++;
									Token->type3 ='=';
								}
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								TKGetNextToken(Token);
								Token->type2='d';	
								Token->type3='d';
								i++;
								x=0;	
							}
							else if(ts[i]=='>' && ts[i+1]=='=')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								//printf("type2 = %c\n", Token->type2);
								TKGetNextToken(Token);
								Token->type2='d';	
								i++;
								x=0;	
							}
							else if(ts[i]=='<' && ts[i+1]=='=')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								//printf("type2 = %c\n", Token->type2);
								TKGetNextToken(Token);
								Token->type2='d';	
								i++;
								x=0;	
							}
							else if(ts[i]=='=' && ts[i+1]=='=')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								//printf("type2 = %c\n", Token->type2);
								TKGetNextToken(Token);
								Token->type2='d';	
								i++;
								x=0;	
							}
							else if(ts[i]=='!' && ts[i+1]=='=')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								//printf("type2 = %c\n", Token->type2);
								TKGetNextToken(Token);
								Token->type2='d';	
								i++;
								x=0;	
							}	
							else if(ts[i]=='&' && ts[i+1]=='&')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								//printf("type2 = %c\n", Token->type2);
								TKGetNextToken(Token);
								Token->type2='d';	
								i++;
								x=0;	
							}
						

							else if(ts[i]=='|' && ts[i+1]=='|')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								//printf("type2 = %c\n", Token->type2);
								TKGetNextToken(Token);
								Token->type2='d';	
								i++;
								x=0;	
							}
						else if(ts[i]=='*' && ts[i+1]=='=')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								//printf("type2 = %c\n", Token->type2);
								TKGetNextToken(Token);
								Token->type2='d';	
								i++;
								x=0;	
							}
						else if(ts[i]=='/' && ts[i+1]=='=')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								//printf("type2 = %c\n", Token->type2);
								TKGetNextToken(Token);
								Token->type2='d';	
								i++;
								x=0;	
							}
							else if(ts[i]=='%' && ts[i+1]=='=')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								//printf("type2 = %c\n", Token->type2);
								TKGetNextToken(Token);
								Token->type2='d';	
								i++;
								x=0;	
							}
							else if(ts[i]=='&' && ts[i+1]=='=')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								//printf("type2 = %c\n", Token->type2);
								TKGetNextToken(Token);
								Token->type2='d';	
								i++;
								x=0;	
							}
						else if(ts[i]=='^' && ts[i+1]=='=')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								//printf("type2 = %c\n", Token->type2);
								TKGetNextToken(Token);
								Token->type2='d';	
								i++;
								x=0;	
							}
					else if(ts[i]=='|' && ts[i+1]=='=')
							{
								Token->word[x] = ts[i];
								Token->word[x+1] = ts[i+1];
								Token->word[x+2]='\0';
								Token->type = Token->word[x];
								Token->type2 = Token->word[x+1];
								//printf("type2 = %c\n", Token->type2);
								TKGetNextToken(Token);
								Token->type2='d';	
								i++;
								x=0;	
							}
						
						else
						{
							Token->word[x] = ts[i];
							Token->word[x+1] = '\0';
							Token->type = Token->word[x];
							TKGetNextToken(Token);	
					//	i++;
							x=0;
					}
	
							//printf("test\n");		
					/*		Token->word[x] = ts[i];
							Token->word[x+1] = '\0';
							Token->type = Token->word[x];
							TKGetNextToken(Token);	
							x=0;
				*/
						}
					else
					{
						Token->word[x] = ts[i];
						Token->word[x+1] = '\0';
						Token->type = Token->word[x];
						TKGetNextToken(Token);	
				//	i++;
						x=0;
					}
			//	}
				} 
			//This is the case for letters in a row, even after a hex number
			else	if((ts[i] >= 'a' && ts[i] <= 'z' && (prev == 0)) || (ts[i] >='A' && ts[i] <='Z' && (prev ==0) ))
			{
		//		printf("ts[i] = %c \n",ts[i]);
				   
	      //TKGetNextToken(Token);
				Token->word[x] = ts[i];
				//Token->word[x] ='\0';
				Token->type= 'w';	
				x++;
				prev=0;
			}
 			//this case is for multiple numbers in a row
			else if(ts[i] >= '0' && ts[i] <= '9' && prev == 1)
			{
				//printf("ts[i] = %c",ts[i]);
			//	printf("in statement\n");
				Token->word[x] = (char)ts[i];
				Token->type = 'n';
				x++;
			//	prev = 1;	
			} //This case is for a new letter appears after a number.
		// printf("prev = %d\n", prev);
			else if((ts[i] >= 'a' && ts[i] <= 'z' && prev == 1 ) || (ts[i] >='A' && ts[i] <= 'Z' && prev==1 ))
			{
				//printf("token %s\n", Token->word);
				Token->type = 'n';
				Token->word[x] = '\0';
				TKGetNextToken(Token);
				prev = 0;
				i--;
				x=0;
			//	Token->word[x] = '\0';
			}
			//This case is for a new number appearing after a word 
			else if((ts[i] >= '0') && (ts[i] <= '9') && (prev == 0))
			{
			//printf("token %s\n", Token->word);		
				Token->type = 'w';
				Token->word[x] = '\0';
				TKGetNextToken(Token);
				prev = 1;
				i--;
				x=0;
				//Token->word[x] = '\0';
			} 
		//printf("final prev = %d\n", prev); 
			else if(ts[i] == '\0' || ts[i] == ' ') //|| EOW ==1)
			{
				
	//		printf("prev = %d\n", prev);
		//	Token->word=(char*)malloc(sizeof(x));
		//	strcpy(Token->word,words);	
		//	substring(words, z, x, words);
			//z = x;
				if(prev == 0)
				{
				Token->type = 'w';
				Token->word[x]= '\0';
				TKGetNextToken(Token);
				x=0;
				 if(ts[i+1] > 0 && ts[i+1] <=9)
         {
           prev = 1;
         }
         else
         {
           prev = 0;
         }

				//prev = ' ';
				}
			//	prev = ' '; 
		
			else if(prev ==1 )
			{
				Token->type = 'n';
				Token->word[x]= '\0';
				TKGetNextToken(Token);
				x=0;
				if(ts[i+1] > 0 && ts[i+1] <=9)
				{
					prev = 1;
				}
				else
				{
					prev = 0;
				}
  		//	prev = ' ';
				}
			
		}
	}
}
	return Token;

}
/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
	free(tk->word);
	free(tk);
	return;
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {
	
	//char *currentWord;
if(strcmp(tk->word,"")==0)
{
	return NULL;
}
		
		switch(tk->type) 
		{
			case 'n' :
				printf("number \"%s\"",tk->word);
				printf("\n");
			//	TKDestroy(tk);
				break;

			case 'w':
				printf("word \"%s\"", tk->word);
				printf("\n");
				//TKDestroy(tk);
				break;

			case 'h' :
				printf("hex integer \"%s\"", tk->word);
				printf("\n"); 
				break;
 
			case 'f' :
				printf("floating point \"%s\"", tk->word);
				printf("\n");
				break;

			case 'o' :
				printf("octal integer \"%s\"", tk->word);
				printf("\n");
				break;

			case '(' :
				printf("left braket \" %s \"", tk->word);
				printf("\n");
				break;

			case ')' :
				printf("right braket \" %s \"", tk->word);
				printf("\n");
				break;

			case '[' :
				printf("right brace \"%s\"", tk->word); 
				printf("\n");
				break;

			case ']' :
				printf("left brace \"%s\"", tk->word);
				printf("\n"); 
				break;

			case '.' :
				printf("decimal \"%s\"", tk->word);
				printf("\n");
				break;

			case '*' :
				if(tk->type2== '=')
				{
					printf("multiply equals \"%s\"", tk->word);
					printf("\n");			
					break;
				}
				else
				{	
					printf("multiply \"%s\"", tk->word);
					printf("\n");
					break;
				}
			case '&' :
				if(tk->type2== '&')
				{
					printf("logical and \"%s\"", tk->word);
					printf("\n");			
					break;
				}
				else if(tk->type2== '=')
				{
					printf("address equals \"%s\"", tk->word);
					printf("\n");			
					break;
				}
				else
				{
					printf("address \"%s\"", tk->word);
					printf("\n");			
					break;
					}
			case '!' :
				if(tk->type2 == '=')
					{
					printf("not equals \"%s\"",tk->word);
					printf("\n");
					break;
					}
				else
				{
					printf("negate \"%s\"", tk->word);
					printf("\n");
					break;
				}
			case '~' :
				printf("1’s comp  \"%s\"", tk->word);
				printf("\n");
				break;

			case '+' :
				if(tk->type2 == '+')
				{
					printf("inc \"%s\"",tk->word);
					printf("\n");
					break;
				}
				else if(tk->type2 == '=')
				{
					printf("plus equals \"%s\"",tk->word);
					printf("\n");
					break;
				}
				else
				{
					printf("plus \"%s\"",tk->word);
					printf("\n");
					break;
				}
		
			case '-' :
				if(tk->type2 == '>')
				{
					printf("structure pointer \"%s\"",tk->word);
					printf("\n");	
					break;
				}
				else if(tk->type2=='-')
				{
					printf("dec \"%s\"",tk->word);
					printf("\n");
					break;
				}
				else if(tk->type2=='=')
				{
					printf("subtract equals \"%s\"",tk->word);
					printf("\n");
					break;	
				}
				else
				{
					printf("subtract \"%s\"",tk->word);
					printf("\n");
					break;
				}
			case '/' :
				if(tk->type2== '=')
				{
					printf("divide equals \"%s\"", tk->word);
					printf("\n");			
					break;
				}
				else
				{
					printf("divide \"%s\"",tk->word);
					printf("\n");
					break;
				}
			case '%' :
				if(tk->type2== '=')
				{
					printf("modulus equals \"%s\"", tk->word);
					printf("\n");			
					break;
				}
				else
				{
					printf("modulus \"%s\"",tk->word);
					printf("\n");
					break;
				}
			case '>' :
				if(tk->type3 =='=')
				{
					printf("shift right equals \"%s=\"",tk->word);
					printf("\n");
					break;

				}
				else if(tk->type2 =='>')
				{
					printf("shift right \"%s\"",tk->word);
					printf("\n");
					break;

				}
				else if(tk->type2=='=')
				{
					printf("greater or  equal \"%s\"",tk->word);
					printf("\n");
					break;
				}		
				
				else
				{
					printf("greater than \"%s\"",tk->word);
					printf("\n");
					break;
				}
			case '<' :
				if(tk->type3 =='=')
				{
					printf("shift left equals\"%s=\"",tk->word);
					printf("\n");
					break;	
				}		
				else if(tk->type2 =='<')
				{
					printf("shift left \"%s\"",tk->word);
					printf("\n");
					break;
				}
				else if(tk->type2=='=')
				{
					printf("less or equal \"%s\"",tk->word);
					printf("\n");
					break;
				}
				else
				{
					printf("less than \"%s\"",tk->word);
					printf("\n");
					break;
				}
			case '=' :
				if(tk->type2 =='=')
				{
					printf("equals equals \"%s\"",tk->word);
					printf("\n");
					break;
				}
				else
				{
					printf("equals \"%s\"",tk->word);
					printf("\n");
					break;
				}
			case '|' :
				if(tk->type2=='|')
				{
					printf("logical or \"%s\"",tk->word);
					printf("\n");
					break;
				}
				else if(tk->type2=='=')
				{
					printf("bitwise or equals \"%s\"",tk->word);
					printf("\n");
					break;
				}
				else
				{
					printf("bitwise or  \"%s\"",tk->word);
					printf("\n");
					break;
				}
			case '^' :
				if(tk->type2== '=')
				{
					printf("bitwise xor equals \"%s\"", tk->word);
					printf("\n");			
					break;
				}
				else
				{
					printf("bitwise xor  \"%s\"",tk->word);
					printf("\n");
					break;
			}
			case ',' :
				printf("comma \"%s\"",tk->word);
				printf("\n");
				break;

			case '{' :
				printf("right curly brace \"%s\"",tk->word);
				printf("\n");
				break;
		
			case '}' :		
				printf("left curly brace \"%s\"",tk->word);
				printf("\n");
				break;
			case 's' :
				printf("\"%s\"", tk->word);
				printf("\n");
				break;
			case 't' :
				printf("\"%s\"", tk->word);
				printf("\n");
				break;

			default :
		//		printf("word  \"%s" ,tk->word );
				break;					//for regular letters (not retarded ones like johnny)
		}
		
	
  return NULL;
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
	
	if(argc != 2)
	{
		return 0;
	}	
	else
	{
		TokenizerT *token = TKCreate(argv[1]);			
		TKDestroy(token);
	}
  return 0;
}
