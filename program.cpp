#include <stdio.h> 
#include<string.h> 
#include <conio.h>

void func(char* arrayWord,char* array_meanings, FILE* fp)
{
	char oneword[80];
	char wholeWord[100];
	char arrayWord2[5000][100];
	char array_meanings2[5000][100];
	bool is_meaning;
	bool isWord;
	int charIndex =0;
	int wordIndex=0;
	int wordCount =0;
	char c,x;
	
	do {
		c = fscanf(fp,"%s",oneword);
		charIndex = 0;

		if (':' != oneword[0] && ';' != oneword[0])
		{
			if (wordIndex > 0)
			{
				wholeWord[wordIndex] = 32;
				wordIndex++;
			}
			while (oneword[charIndex] != '\0' && wordIndex<100)
			{
				if ((oneword[charIndex] >= 65 && oneword[charIndex] <= 90) //A-Z
				|| (oneword[charIndex] >= 97 && oneword[charIndex] <= 122)//a-z
				|| (oneword[charIndex] >= 48 && oneword[charIndex] <= 57))//0-9
				{
					wholeWord[wordIndex] = oneword[charIndex];
					wordIndex++;
				}
				charIndex++;
			}
		}
		else
		{
			if (':' == oneword[0])
			{
				isWord = true;
				strcpy(arrayWord, wholeWord);
			}
			else
			{
				is_meaning = true;
				strcpy(array_meanings, wholeWord);
			}
			for (int a = 0; a<wordIndex; a++)
			{
				wholeWord[a] = 0;
			}
			wordIndex = 0;

			if (true == isWord && true == is_meaning)
			{
				wordCount++;
				isWord = false;
				is_meaning = false;
			}
		}
	} while (c != EOF && wordCount <= 4999);
}

bool match(char word[100], char token[100])
{
	 int wordIndex =0, tokenIndex =0;
	while(tokenIndex <100)
	{
  		if(token[tokenIndex] == 32)
  		{
  			tokenIndex++;
   			continue;
  		}
  
  		if(word[wordIndex] == 32)
  		{
   			wordIndex++;
   			continue;
  		}	
  
  		if(token[tokenIndex] == '\0' )
  		{
   			return true;
  		}
  
  		if(word[wordIndex] == '\0')
  		{
   			return false;
  		}
  		if(word[wordIndex]!= token[tokenIndex] && (word[wordIndex]!= token[tokenIndex]-32) && (word[wordIndex]!= token[tokenIndex]+32))
  		{
   			return false;
  		}
   		tokenIndex++;
   		wordIndex++;
 	}
 return true;
}

int Search(char words[][100], char searchToken[])
{
 	for(int i=0;i<10000; i++)
 	{
  		if(match(words[i],searchToken))
  		{
  		return i;
 		}
 	}
 	return -1;
}
 
int main(int argc, char** argv) 
{
	FILE *fp;
	char wholeWord[100];
	char arrayWord[5000][100];
	char arraySynonym[5000][100];
	char arrayWord2[5000][100];
	char array_meanings2[5000][100];
	bool isWord;
	bool isSynonym;
	int charIndex =0;
	int wordIndex=0;
	int wordCount =0;
	char c,x;
	bool is_meaning;
	FILE *fp1;
	//Loading Word meaning.........
	fp = fopen("c:\\bilal\\meaning_New.txt", "r");
	func(arrayWord2,array_meanings2, fp);
		
	fclose(fp);

	wordCount=0;
	//Loading Word Synonyms
	fp1 = fopen("c:\\bilal\\synonyms_New.txt", "r");
	func(arrayWord,arraySynonym,fp1);

	fclose(fp1);

	do
	{
	printf("\nwhat operation do you want \n press 1 for find the synonyms \n press 2 for find the meanings ");
	scanf("%d",&x);
	
	switch(x)
	{
			case 1:
			{
		 	char input[100];
 			do
		 	{
 				printf("\nenter the word1 : ");
 				fflush(stdin);
				scanf("%[^\n]s",input);					//^\n is ka kia matlb hai?
		 		fflush(stdin);
	 		  	int searchIndex = Search(arrayWord, input);
 		
				 if(searchIndex >= 0)
  				{
   					printf("word is %s and synonyms is %s\n",arrayWord[searchIndex], arraySynonym[searchIndex+1]);
		 		}
 				else
 				{
  					printf("word not found");
	 			}
	 				printf("\ndo you want to find more synonyms? press \"y\" for yes or \"n\" for no");
 			}while(getch()=='y');
		}
		break;
	case 2:
	{
		char input2[100];
  			do
 			{
 				printf("\nenter the word : ");
 				fflush(stdin);
				scanf("%[^\n]s",input2);
 				fflush(stdin);
   				int searchIndex2 = Search(arrayWord2, input2);
  				
				if(searchIndex2 >= 0)
  				{
 				  printf("word is %s and meaning is %s\n",arrayWord2[searchIndex2], array_meanings2[searchIndex2+1]);
 				}
 				else
 				{
  				  printf("word not found");
 				}
 				printf("\ndo you want to find more meanings? press \"y\" for yes or \"n\" for no");
 			}while(getch()=='y');
		}
	break;
	}
	
	printf("\n\ndo you want perform another function? press y or n");
	}while(getch()=='y');
}
