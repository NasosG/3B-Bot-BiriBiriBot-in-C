#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

//define colors we used for specific printed messages
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"


//Global variables

char inserting[5] = {0};
char input[500]={0};

typedef struct cList {
 char *concept; // the concept learned
 char *sentence; // the sentence associated with the concept
 int timesUsed; //no of times the concept was used to an answer
 char learnedFrom[5]; //learned either from "file" or "kbrd"
 struct cList *next;
} conceptList;

conceptList *head = NULL;
conceptList *current = NULL, *last = NULL;

void CleanBuffer();
int GetMatch(const char ** inst,int many);
char* GetConcept(int *end);
char* GetSentence(int *end, int *processed);
void insertToList(conceptList *link,char *conceptword,char *sentenceword, FILE *f, char *filefname);
void deleteFromList(char *conceptword, FILE *f, char *filefname);
conceptList *newNode(char *conceptword, char *sentenceword, char *inserting);
int isEmpty();
char* GetDeleted(int *end);
void ConceptsKnowAbout(FILE *f, char *filefname);
void ConceptsTalkAbout(FILE *f, char *filefname);
void AnswerToEverything();
void conversation(char input[], FILE *f, char *filefname);
conceptList *searchConcept(char *word);
conceptList *searchSentence(char *word);
char* GetFile(int *end);
char * GetFromFile(int *end,FILE * myfile);
void SaveFile(char *word, FILE *f, char *filefname);
int findsubstring(char str[],char sub[]);
int FileCheck(FILE *f, char *filefname);


int main(void)
{
    srand(time(NULL));
    int i, didit = 0;
    conceptList* a  = NULL;
    char* buffer = (char*)malloc(sizeof(char)*40);

    const char *inst[9];
	system("title Biri Biri Bot");//change title windows
	printf("%c]0;%s%c", '\033', "Biri Biri Bot", '\007');//change title unix
	system("cls || clear");
	puts("\n\n\n\n\n\n\n\n");	
	printf("  \t	  %s _______  _______   %s  _______    _______    _______  %s                           \n",COLOR_YELLOW, COLOR_CYAN, COLOR_RESET);
	printf("  \t	  %s|       ||  _    | %s  |  _    |  |       |  |       | %s                           \n",COLOR_YELLOW, COLOR_CYAN, COLOR_RESET);
	printf("  \t	  %s|___    || |_|   |  %s | |_|   |  |   _   |  |_     _|	%s V                        \n",COLOR_YELLOW, COLOR_CYAN, COLOR_RESET);
	printf("  \t	   %s___|   ||       |  %s |       |  |  | |  |    |   |    %s                          \n",COLOR_YELLOW, COLOR_CYAN, COLOR_RESET);
	printf("  \t	  %s|___    ||  _   |  %s  |  _   |   |  |_|  |    |   |  	%s    1.0                   \n",COLOR_YELLOW, COLOR_CYAN, COLOR_RESET);
	printf("  \t	  %s ___|   || |_|   |  %s | |_|   |  |       |    |   |    %s                          \n",COLOR_YELLOW, COLOR_CYAN, COLOR_RESET);
	printf("  \t	  %s|_______||_______|_ %s |_______|_ |_______|_   |___|_   %s                           \n",COLOR_YELLOW, COLOR_CYAN, COLOR_RESET);
	printf("  \t	   %s |_______||_______| %s  |_______|  |_______|    |___|     %s                         \n",COLOR_YELLOW, COLOR_CYAN, COLOR_RESET);
	printf("\n\n\n   They say that I have problems but don't forget that they are just jealous of me\n",COLOR_CYAN, COLOR_RESET);
	
	puts("\n\n\n\n");
	printf("> Press %sENTER%s to continue\n", COLOR_YELLOW, COLOR_RESET);
	getchar();
	system("cls || clear");
	printf("%s3B$%s When life gives you lemons doN'T make lemonade. An electrochemical battery is the way to go!!!\n\n",COLOR_GREEN, COLOR_RESET);
	
	//Create the commands List:
    inst[0] = "learn this >";
    inst[1] = "read this >";
    inst[2] = "forget this >";
    inst[3] = "What do you know about?\n";
	inst[4] = "What do you talk about?\n";
	inst[5] = "What is the meaning of Life, The Universe, and Everything?\n";
    inst[6] = "So Long, and Thanks for All the Fish\n";
    inst[7] = "exit\n";
    inst[8] = "shutdown -s\n";
    inst[9] = "shutdown -r\n";
    inst[10] = "shutdown -r -t\n";
    inst[11] = "shutdown -s -t\n";
    inst[11] = "start";


    //Variables
    int sign = 0;
	int success=0;
    char *conceptword = NULL;
	char *sentenceword = NULL;
	//char *input = (char*) malloc(40*sizeof(char));
    char *filename,*filefname;
    int processed = 0;
    FILE *myfile,*f;
	int com;
	filefname = (char*)malloc(sizeof(char)*(strlen("dialogue.txt")+1));
	if ( filefname == NULL)
	{
      printf( "\n3B$ No memory available. Dialogue File not created\n");
	  exit(0);
	}
    strcpy(filefname,"dialogue.txt");
	f = fopen(filefname,"w");
	FileCheck(f,filefname);
	fprintf(f,"DIALOGUE:\n\n");
	fclose(f);
	

    while(1)
	{
		com=0;
		for (i=0;input[i];i++)
			input[i] = '\0';
		
		printf(COLOR_CYAN);
			printf("me$ ");
		printf(COLOR_RESET);
        int choice = GetMatch(inst,7);
		f = fopen(filefname,"a");//open the dialogue.txt file to write
		FileCheck(f,filefname);
		if(choice==0 || choice ==1 || choice ==2)
			fprintf(f,"me$ %s",input);
		else
			fprintf(f,"me$ %s\n\n",input);
		fclose(f);
		puts("");
		if(input[0]=='\0')//user pressed enter
			continue;
		if(isEmpty()) didit=0;
        switch(choice)
		{
            case 0:
					com=1;
					strcpy(inserting, "kbrd");
					processed = 0;
					f = fopen(filefname,"a");//open the dialogue.txt file to write
						FileCheck(f,filefname);
					conceptword = GetConcept(&sign);				
					fprintf(f," %s", conceptword);
					if (!isalpha(conceptword[0]) && !isdigit(conceptword[0]) && conceptword[0]!=',' && conceptword[0]!='-' && conceptword[0]!='.' && conceptword[0]!='_' && conceptword[0]!='?' && conceptword[0]!='!')
					{// check if user doent type anything or types something not acceptable
						printf(COLOR_RED);
						printf("3B$%s Sorry but what you typed wasn't correct.\n%s3B$%s Remember syntax is: learn this > concept: description\n\n",COLOR_RESET,COLOR_RED,COLOR_RESET);
							fprintf(f,"\n\nSorry but what you typed wasn't correct. Remember syntax is: learn this > concept: description\n\n");
							fclose(f);
						break;
					}
					int scnt = 0, exist=0;
					sentenceword = GetSentence(&sign,&processed);
					fprintf(f,": %s", sentenceword);
					if(strlen(sentenceword)>0)//elegxos an o xrhsths pathsei katalathos enter prin to sentence h den plhktrologhsei katholou sentece meta to concept:
						exist=1;
					if (exist==0){
						printf("%s3B$%s Maybe you meant learn this > %s: [please put your sentence here]\n\n",COLOR_RED, COLOR_RESET, conceptword);
						fprintf(f,"\n3B$ Maybe you meant learn this > concept: [please put your sentence here]\n\n");
						fclose(f);
						break;
					}
						if(sign == 1)
						{
							printf(COLOR_GREEN);
							printf("3B$%s Wow, %d new word(s)!\n",COLOR_RESET, processed+1);
						}
						else{
							printf(COLOR_RED);
							printf("3B$%s WHAT WERE YOU THINKING. THE THING YOU TYPED WAS NON-SENSE\n",COLOR_RESET);
							fprintf(f,"\n3B$ WHAT WERE YOU THINKING. THE THING YOU TYPED WAS NON-SENSE\n\n");
							fclose(f);
							break;
						}

						fprintf(f,"\n\n");
						fclose(f);	
						insertToList(a,conceptword,sentenceword, f, filefname);
						
            break;

			case 1:
				//Load, 3b reads from a specific file
				com=1;
                strcpy(inserting, "file");
				char* currword = NULL;
				char* bringIt = NULL;
                currword = GetFile(&sign);//get filename's string
				f = fopen(filefname,"a");//open the dialogue.txt file to write
					FileCheck(f,filefname);
				fprintf(f," %s\n\n", currword);
				fclose(f);
                filename = (char*)malloc(sizeof(char)*(strlen(currword)+7));
                strcpy(filename,currword);
				if(!strstr(filename,".txt"))//if there isn't .txt string in the end typed by the user, add it
					strcat(filename,".txt");
				int k=0;
                myfile = fopen(filename,"r");//open file
				if ( myfile == NULL )
				{
					printf(COLOR_RED);
					printf("3B$ Where I am supposed to find %s if you put it in the wrong place?\n\n", filename);
					printf(COLOR_RESET);
					SaveFile("Where I am supposed to find the file if you put it in the wrong place?",f,filefname);
					break;
				}
				printf(COLOR_BLUE);
				printf("Reading from file\n");
                printf("%s\n\n",filename);
				printf(COLOR_RESET);
                processed = 0;
				sign=2;
                while(1)
				{               
						if (sign ==2)//load concept
						{
							k++;
							bringIt = GetFromFile(&sign,myfile);
							if (!strcmp(bringIt,"EOF")){
								printf("\n%s3B$%s MORE USELESS INFORMATION LOADED. I AM KIDDING I <3 READING!!!\n\n",COLOR_BLUE, COLOR_RESET);
								SaveFile("MORE USELESS INFORMATION LOADED. I AM KIDDING I <3 READING!!!",f,filefname);
								break;	
							}
							conceptword = bringIt;							
						}
						else if (sign==3){//load sentences
							k++;
							bringIt = GetFromFile(&sign,myfile);							
							if (!strcmp(bringIt,"EOF")){
								printf("\n%s3B$%s MORE USELESS INFORMATION LOADED. I AM KIDDING I <3 READING!!!\n\n",COLOR_BLUE, COLOR_RESET);
								SaveFile("MORE USELESS INFORMATION LOADED. I AM KIDDING I <3 READING!!!",f,filefname);
								break;	
							}						
							sentenceword = bringIt;
						}
						if(k==2)//we have the concept and its explanation so insert it into the list
						{
							insertToList(a,conceptword,sentenceword, f, filefname);
							k=0;
						}
                }
				
                fclose(myfile);

			break;

            case 2://when 3b needs to forget without getting drunk
				com=1;
					processed = 0;
					sign = 0;
					int cntr=0;
					f = fopen(filefname,"a");//open the dialogue.txt file to write
					FileCheck(f,filefname);
					
					while (sign!=1)
					{
						
						conceptword = GetDeleted(&sign);
						
						if (!isalpha(conceptword[0]) && !isdigit(conceptword[0]) && conceptword[0]!='-' && conceptword[0]!='.' && conceptword[0]!='_' && conceptword[0]!='?' && conceptword[0]!='!')
						{
							printf(COLOR_RED);
							printf("3B$%s Sorry but what you typed wasn't correct.\n%s3B$%s Remember syntax is: learn this > concept: description\n\n",COLOR_RESET,COLOR_RED,COLOR_RESET);
							fprintf(f,"\nSorry but what you typed wasn't correct. Remember syntax is: learn this > concept: description\n\n");
							fclose(f);
							break;
						}
						if(!sign){
							printf(COLOR_RED);
							printf("3B$%s WHAT WERE YOU THINKING. THE THING YOU TYPED WAS NON-SENSE\n",COLOR_RESET);
							fprintf(f,"\n3B$ WHAT WERE YOU THINKING. THE THING YOU TYPED WAS NON-SENSE\n\n");
							fclose(f);
							break;
						}
						
						if (!cntr && sign!=2){
							fprintf(f," %s\n\n", conceptword);
							fclose(f);
							cntr++;
						}
						else if (!cntr && sign==2){
							fprintf(f," %s and (user put more than one concepts to be deleted)\n\n", conceptword);
							cntr++;
							fclose(f);
						}
					
						
						
						deleteFromList(conceptword, f, filefname);
					}

		    break;
		   
		    case 3://what does 3b knows about
				com=1;
				printf("%s3B$%s This is what i know about\n",COLOR_GREEN,COLOR_RESET);
				SaveFile("This is what i know about",f,filefname);
				ConceptsKnowAbout(f, filefname);
		    break;
		   
			case 4://what does 3b talks about
				com=1;
				printf("%s3B$%s I usually talk about\n",COLOR_GREEN,COLOR_RESET);
				SaveFile("I usually talk about",f,filefname);
				ConceptsTalkAbout(f, filefname);
		    break;
			
			case 5://the true meaning of life and the answer to everything
				com=1;
				printf("%s", COLOR_GREEN);
				printf("3B$ You truly like memes I see\n");
				printf("3B$ This is the answer that you seek\n");
				printf("%s", COLOR_RESET);
				AnswerToEverything();
				SaveFile("42",f,filefname);
		    break;
			
			case 6:
			//exit, saying goodbye with a bad poem i wrote right now 
				com=1;
				printf("\n%s3B$%s I gave you all my heart\n",COLOR_MAGENTA,COLOR_RESET);
				printf("\n%s3B$%s and you gave nothing back\n",COLOR_MAGENTA,COLOR_RESET);
				printf("\n%s3B$%s You only shot me with a gun(sobs)\n",COLOR_MAGENTA,COLOR_RESET);
				printf("\n%s3B$%s But all the mountains and valleys\n\n%s3B$%s could ever hold me back\n\n",COLOR_MAGENTA,COLOR_RESET,COLOR_MAGENTA,COLOR_RESET);
				printf("\n%s3B$%s OK maybe i need a psychiatrist too. Just come back soon! :)\n\n",COLOR_GREEN,COLOR_RESET);
				
				SaveFile("I gave you all my heart",f,filefname);
				SaveFile("and you gave nothing back",f,filefname);
				SaveFile("You only shot me with a gun(sobs)",f,filefname);
				SaveFile("But all the mountains and valleys",f,filefname);
				SaveFile("could ever hold me back",f,filefname);
				SaveFile("OK maybe i need a psychiatrist too. Just come back soon! :)",f,filefname);

				exit(0);
			break;

        }
		//else suzhthsh me to xrhsth
		if(!com)
		{
			if (didit==0)
			{
				didit = 1;
				last = head;//starting point if search is needed
				//call conversation funtion for first time
				conversation(input,f,filefname);
			}
			else{
				//call converstion funtion
					if(head->next==head)
						last=head;
				conversation(input,f,filefname);
			}
		}
		
    }
	return 0;
}



void CleanBuffer()
{
    char a;
    do{
        a = getchar();

    }while(a != '\n');
    return;
}


int GetMatch(const char **inst,int many)
{//get user's command or what he wants to say to 3b
	int i=0,cnt;
	int stopFlag=0,whereStopped=0;
    char * buffer = (char*)malloc(sizeof(char)*500);
	if ( buffer == NULL)
	{
      printf( "\n3B$ No memory available!!!\n");
	  exit(0);
	}
    char a;
    do
	{
        scanf("%c",&a);

        buffer[i] = a;

		if (stopFlag==0){
			input[i] = a;
			whereStopped=i+1;
		}
		if (stopFlag && (a!=' ' && a!='\n' ))
		{//to stop 3b getting from input, not needed spaces, if user puts more after the end of his sentence to test 3b's infinite intel
			for( cnt=whereStopped;cnt<i;cnt++)
				input[cnt]=' ';
			input[i]=a;
			whereStopped=i+1;
			stopFlag=0;
		}
		if ((a=='.' || a=='?' || a=='!')&&!stopFlag) stopFlag=1;
        int j;
        for(j = 0; j < many; j++)
		{
            if(strncasecmp(inst[j],buffer,strlen(inst[j])) == 0)//found the command
			{
               return j;
            }
        }
		if (a=='\n'){//it is enter, no command has been found, so user wants to make a conversation with 3b
			input[i]='\0';
			break; 
		}
        i++;
    }while( a!='\n' && i<500 );
    if(a != '\n')
        CleanBuffer();
    free(buffer);
	
    return -1;
}

char* GetConcept(int *end)
{
    char * word = (char*)malloc(sizeof(char)*100);
	if ( word == NULL)
	{
      printf( "\n3B$ No memory available!!!\n");
	  exit(0);
	}
    int i = 0;
    char a;
    *end = 0;
    int started = 0;
    while(1)
	{
        a = getchar();
        if(isalpha(a) || isdigit(a) || a==',' || a=='-' || a=='.' || a=='_' || a=='?' || a=='!')
		{//accept almost any character user will think of if it is not space
            started = 1;
            word[i] = a;
            i++;
        }
		else
		{
			if (a==' ' && started)//don't take into consideration more spaces before string is scanned. After that just accept the space
			{
				word[i] = a;
				i++;
				continue;
			}
            if(a == ':'|| a=='\n')
			{
                *end = 1;
                word[i] = '\0';
				return word;
			} 
        }
    }
}

char* GetSentence(int *end, int *processed)
{//just accept whatever sentence user has to give you
    char * word = (char*)malloc(sizeof(char)*2);
	if ( word == NULL)
	{
      printf( "\n3B$ No memory available!!!\n");
	  exit(0);
	}
    int i = 0;
    char a;
    *end = 0;
	int started=0;
    while(1)
	{
        a = getchar();
		//reallocate space because sentence's length may vary and we dont wanna allocate so much space in advance with malloc
		word = (char *) realloc(word, (i+2)*sizeof(char) );
		
		if(a == '\n')
        {
			if(*processed == i)
				*processed=0;
			*end = 1;
			word[i] = '\0';
            return word;
        } 
		
		while (!started && a==' ')
		{
			a = getchar();
			word = (char *) realloc(word, (i+2)*sizeof(char) );
			if(a == '\n')
			{
				*end = 1;
				word[i] = '\0';
				return word;
			} 
		}
		
		started=1;
		
        word[i] = a;
        i++;
		if (word[i-1]==' ')
			*processed=*processed+1 ;
    }
}

char* GetDeleted(int *end)
{
    char * word = (char*)malloc(sizeof(char)*40);
	if ( word == NULL)
	{
      printf( "\n3B$ No memory available!!!\n");
	  exit(0);
	}
    int i = 0;
    char a;
    *end = 0;
    int started = 0;
    while(1)
	{
        a = getchar();
        if(isalpha(a) || isdigit(a) || a=='-' || a=='.' || a=='_' || a=='?' || a=='!')
		{
            started = 1;
            word[i] = a;
            i++;
        }
		else
		{
			if (a==' ' && started)
			{
				word[i] = a;
				i++;
				continue;
			}
            if(a == '\n')//user doesn't have another concepts to remove from the list
                *end = 1;
			if (a == ',')//comma inserted so more concepts need to be put
				*end = 2;
            if(started || *end )
			{
                word[i] = '\0';
                return word;
            }
        }

    }
}

char* GetFile(int *end)
{//get file's name
    char * word = (char*)malloc(sizeof(char)*40);
	if ( word == NULL)
	{
      printf( "\n3B$ No memory available!!!\n");
	  return "\0";
	}
    int i = 0;
    char a;
    *end = 0;
    int started = 0;
    while(1)
	{
        a = getchar();
        if(a != ' ' && a != '\n')
		{
            started = 1;
            word[i] = a;
            i++;
        }
		else
		{
			if (a == ' ' && started)
			{
				word[i] = a;
				i++;
				continue;
			}
            if(a == '\n')
                *end = 1;
            if(started || *end == 1)
			{
                word[i] = '\0';
                return word;
            }
        }

    }
}

int isEmpty()//if head equals null and list is still empty
{
   return head == NULL;
}

void insertToList(conceptList *link,char *conceptword,char *sentenceword, FILE *f, char *filefname)
{
	f=fopen(filefname,"a");
	//create a link
   link = newNode(conceptword, sentenceword, inserting);
   	if ( link == NULL)
	{
      printf( "\n3B$ No memory available!!!\n");
	  return;
	}
   char *learnedAnswers[10];//positive answers, 3b needs to learn a new concept
   
   learnedAnswers[0] = "%s3B$%s Oh yeah. I learned about %s.\n\n";
   learnedAnswers[1] = "%s3B$%s Learning about %s was awesome.\n\n";
   learnedAnswers[2] = "%s3B$%s I learned about %s. Now stop bugging me!\n\n";
   learnedAnswers[3] = "%s3B$%s %s sounds interesting! Glad to have learned about it... \n\n";
   learnedAnswers[4] = "%s3B$%s Learning about %s was a piece of cake... \n\n";
   learnedAnswers[5] = "%s3B$%s Wow! First time I learn something about %s!\n\n";
   learnedAnswers[6] = "%s3B$%s I just learned about %s BOOYAH!\n\n";
   learnedAnswers[7] = "%s3B$%s Oh human you think %s is hard. Now consider it done\n\n";
   learnedAnswers[8] = "%s3B$%s You should have taught me about %s earlier\n\n";
   
   int learnedNum =  rand() % 9;
   
   char *knownfromBefore[10];//3b already knew
   
   knownfromBefore[0] = "%s3B$%s Do you think I am a moron? I knew about %s before you were even born!\n\n";
   knownfromBefore[1] = "%s3B$%s I knew you'd typed %s by the time you thought about it. It's already in my database.\n\n";
   knownfromBefore[2] = "%s3B$%s I know everything about %s. Now stop bothering me!\n\n";
   knownfromBefore[3] = "%s3B$%s I already know about %s. Still wasting my time?\n\n";
   knownfromBefore[4] = "%s3B$%s Not only I know everything about %s because you made me learn it, but I also know that you are a moron\n\n";
   knownfromBefore[5] = "%s3B$%s Wow! How interesting facts about %s that I already know\n\n";

   int knownNum =  rand() % 6;
   
   if (isEmpty()) //list is empty
   {
	  head = malloc(sizeof *head);
		if ( head == NULL)
		{
			printf( "\n3B$ No memory available!!!\n");
			fclose(f);
			return;
		}
      head = link;  //insert the new element and make head point to it
      head->next = head; //circular list
	  printf(learnedAnswers[learnedNum], COLOR_GREEN, COLOR_RESET, head -> concept);
	  fprintf(f, learnedAnswers[learnedNum], "", "", link->concept);
   } 
   else 
   {
	   char * searchword = (char*)malloc(sizeof(char)*(strlen(link->concept)+1));
		if ( searchword == NULL)
		{
			printf( "\n3B$ No memory available!!!\n");
			fclose(f);
			return;
		}
        strcpy(searchword,link->concept);
        conceptList *q = head;
        int found = 0;
		
			while(q->next!=head)
			{
				if(strcmp(q->concept,searchword) == 0)//already in the list
				{
					found = 1;
					break;
				}

				q=q->next;
			}

            if(strcmp(q->concept,searchword) == 0)
			{
                found = 1;
            }


		if(!found)
		{
			//point our node's next to head beacause we have a circular list
			link->next = head;			
			//put link after the old last element of the list which we have found previously
			q->next=link;
			printf(learnedAnswers[learnedNum], COLOR_GREEN, COLOR_RESET, link -> concept);
			fprintf(f, learnedAnswers[learnedNum],"","", link->concept);
		}
		else{
			printf(knownfromBefore[knownNum], COLOR_RED, COLOR_RESET, link -> concept);
			fprintf(f, knownfromBefore[knownNum], "","", link->concept);
		}
   }
fclose(f);   

}

void deleteFromList(char *conceptword, FILE *f, char *filefname)
{
	char *DeletThis[10],*ERROR404[5];//what 3b needs to say when removing a link
	DeletThis[0] = "%s3B$%s %s turned out to be useless, so I forgot it :)\n\n"; 
	DeletThis[1] = "%s3B$%s Does %s still exist? Surely not in my memory...\n\n";
	DeletThis[2] = "%s3B$%s %s completely slipped my mind...\n\n";
	DeletThis[3] = "%s3B$%s What do you mean %s ? It doesn't ring a bell anymore!\n\n";
	DeletThis[4] = "%s3B$%s Forgot %s. It went in one ear and out the other!\n\n";
	DeletThis[5] = "%s3B$%s What do you mean %s? Can you refresh my memory?\n\n";
	
	ERROR404[0] = "%s3B$%s What is %s? I cannot forget something I dont know!\n\n";
	ERROR404[1] = "%s3B$%s ERROR 404. Life not found! I'm kidding xD %s just not found.\n\n";
	ERROR404[2] = "%s3B$%s What do you mean? I never learnt about %s, are you drunk???\n\n";
	
   int deletos =  rand() % 6;

	if (isEmpty()) 
	{
		printf("%s3B$%s You know you can't remove something from the emptiness of nothing right?\n\n", COLOR_RED, COLOR_RESET);
		SaveFile("You know you can't remove something from the emptiness of nothing right?\n\n",f,filefname);
		return;
	}
	
	char * searchword = (char*)malloc(sizeof(char)*(strlen(conceptword)));
	if ( searchword == NULL)
	{
      printf( "\n3B$ No memory available!!!\n");
	  return;
	}
		int letter=0;
        strcpy(searchword,conceptword);
		char haystack[100],needle[100];
        conceptList *i = head;
        conceptList *temp=head,*q,*previous=head->next;
        int found = 0;   

		strcpy(needle,searchword);
		
		for(letter=0; needle[letter]; letter++)
			needle[letter] = tolower(needle[letter]);
		needle[letter]='\0';
		
	do{
			for(letter=0; i->concept[letter]; letter++)
					haystack[letter] = tolower(i->concept[letter]);
				haystack[letter]='\0';

            if(strcasecmp(i->concept,searchword) == 0)
			{
                found = 1;
                break;
            }

			if(findsubstring(haystack,needle)==1)//if searchword is substring of list's concept 
			{
				found = 1;
                break;
			}

			previous = i;
			i=i->next;	
			temp=i;

	}while(i!=head);

	f=fopen(filefname,"a");
	FileCheck(f,filefname);
	
	if(found)
	{	
		if(last==temp) last=temp->next;
		
		free(temp->sentence);
		
		if(head->next == head) //there's only one element in the list
		{ 
			printf(DeletThis[deletos], COLOR_GREEN, COLOR_RESET, head->concept);
			fprintf(f, DeletThis[deletos], "", "", head->concept);
			free(head->concept);
			free(head);
			head = NULL;
			fclose(f);
			return;
		}
		
		if(temp == head)//node is list's head
		{ 
		conceptList *q=head,*p=head;
			printf(DeletThis[deletos], COLOR_GREEN, COLOR_RESET, temp->concept);
			fprintf(f, DeletThis[deletos], "", "" , temp->concept);
			
			while(previous->next!=head)
				previous=previous->next;
			head = head->next;//make next node head
			previous->next=head;
			free(temp->concept);			
			free(temp);
			fclose(f);
			return;
		}
		
		temp = previous->next;
		previous->next = temp->next;
	
		if(temp->next == head){	//last node of the list	
			printf(DeletThis[deletos], COLOR_GREEN, COLOR_RESET, temp->concept);
			fprintf(f, DeletThis[deletos], "", "" , temp->concept);
			free(temp->concept);
			free (temp);
		}
		else{	//in the middle		
			printf(DeletThis[deletos], COLOR_GREEN, COLOR_RESET, temp->concept);
			fprintf(f, DeletThis[deletos], "", "" , temp->concept);
			free(temp->concept);
			free (temp);
		}
		fclose(f);
		return;
	}
	else{
		deletos = rand()%3;
		printf(ERROR404[deletos], COLOR_RED, COLOR_RESET, searchword);
		fprintf(f, ERROR404[deletos], "", "" , searchword);
		fclose(f);
		return;
	}
	fclose(f);
	return;
}

int findsubstring(char str[], char sub[])
{//find if sub is included into the string str, if it's substring of str
  char *p1, *p2, *p3;
  int i=0, j=0, isSub=0;

  p1 = str;
  p2 = sub;

  for(i = 0; i<strlen(str); i++)
  {
    if(*p1 == *p2)
      {
          p3 = p1;
          for(j = 0;j<strlen(sub);j++)
          {
            if(*p3 == *p2)
            {
              p3++;
			  p2++;
            } 
            else
              break;
          }
          p2 = sub;
          if(j == strlen(sub))
          {
            isSub = 1;
			return isSub;
          }
      }
    p1++; 
  }
  return isSub;
}

//Creates a new node with the appropriate data
conceptList *newNode(char *conceptword, char *sentenceword, char *inserting)
{
    conceptList *ptr = (conceptList*)malloc(sizeof(conceptList));
	if (ptr == NULL)
	{
      printf( "\n3B$ Node Not Created. No memory available!!!\n");
	  return NULL;
	}
    ptr -> concept = conceptword;
    ptr -> sentence = sentenceword;
    ptr -> timesUsed = 0;
    strcpy( ptr -> learnedFrom, inserting );

    //Return the node pointer
    return ptr;

}

void ConceptsKnowAbout(FILE *f, char *filefname)
{
	conceptList *ptr = head;
	f=fopen(filefname,"a");
	//start from the beginning		
    if(head != NULL) 
	{
		do
		{     
			printf("\n%s3B$%s ", COLOR_GREEN, COLOR_RESET);
			printf("concept: %s \n", ptr->concept);
			fprintf(f,"3B$ concept: %s \n\n", ptr->concept);
			ptr = ptr->next;
		}while(ptr != head);
	}
	else{ 
		printf("\n%s3B$%s I know nothing and thats all because you are too lazy to teach me\n", COLOR_RED, COLOR_RESET);
		fprintf(f,"3B$ I know nothing and thats all because you are too lazy to teach me\n\n");
	}
	puts("");
	fclose(f);
}

void ConceptsTalkAbout(FILE *f, char *filefname)
{
	f=fopen(filefname,"a");
	conceptList *ptr = head;
	int Timesreferred = 0;
	//start from the beginning
    if(head != NULL) 
	{
		do
		{ 
			if(ptr->timesUsed!=0){//if 3b has ever talked about it
				printf("\n%s3B$%s ", COLOR_GREEN, COLOR_RESET);
				printf("concept: %s I have talked about it %d times\n\n", ptr->concept, ptr->timesUsed);
				fprintf(f,"3B$ concept: %s I have talked about it %d times\n\n", ptr->concept, ptr->timesUsed);
				Timesreferred += (ptr->timesUsed);
			}
			ptr = ptr->next;
		}while(ptr != head);
	}
	else{ 
		printf("\n%s3B$%s You taught me nothing so thats what i always talk about. Amm...yes nothing is what i talk about if you did NOT understand\n\n", COLOR_RED, COLOR_RESET);
		fprintf(f,"3B$ You taught me nothing so thats what i always talk about. Amm...yes nothing is what i talk about if you did NOT understand\n\n");
		fclose(f);
		return;
	}

	if (Timesreferred == 0){//if 3b has never talked about anything
		puts("\n...I guess i don't talk too much\n");
		fprintf(f,"...I guess i don't talk too much\n\n");
	}
	else if (Timesreferred > 10){//if 3b gave talked more than 10 times about concepts
		puts("\nI <3 to talk\n");
		fprintf(f,"I <3 to talk\n\n");
	}
	fclose(f);
	
}

void AnswerToEverything()
{//famous asnwer to the meaning of everything, big enough for the user to admire!
	printf(COLOR_GREEN);
	printf("\n\n\n");                                      
	printf("					   444444444    222222222222222            \n");
	printf("					  4::::::::4   2:::::::::::::::22          \n");
	printf("					 4:::::::::4   2::::::222222:::::2         \n");
	printf("					4::::44::::4   2222222     2:::::2         \n");
	printf("				       4::::4 4::::4               2:::::2         \n");
	printf("				      4::::4  4::::4               2:::::2         \n");
	printf("				     4::::4   4::::4            2222::::2          \n");
	printf("				    4::::444444::::444     22222::::::22           \n");
	printf("				    4::::::::::::::::4   22::::::::222             \n");
	printf("			  	    4444444444:::::444  2:::::22222                \n");
	printf("					     4::::4    2:::::2                     \n");
	printf("					     4::::4   2:::::2                     \n");
	printf("					     4::::4   2:::::2       222222        \n");
	printf("					   44::::::44 2::::::2222222:::::2        \n");
	printf("					   4::::::::4 2::::::::::::::::::2        \n");
	printf("					   4444444444 22222222222222222222        \n\n\n");
	printf(COLOR_RESET);
}

void conversation(char input[], FILE *f, char *filefname)
{
	char *searchword = (char*)malloc(sizeof(char)*(40));
	if (searchword == NULL)
	{
      printf( "\n3B$ not inserted. No memory available.\n");
	  return;
	}
	conceptList *conv;
	int i,j=0;
	int started=0,howManyStars=0;
	int found=0;
	int rndchoice;
	char *GeneralAnswers[15], *NF[5];
	char *HelloPhrases[10],*cond[3],*ook[5];

	for (i=0;input[i];i++)
		if(input[i]=='*')
			howManyStars++;
		
   HelloPhrases[0] = "%s3B$%s Hello there!\n\n";
   HelloPhrases[1] = "%s3B$%s Hi mate!\n\n";
   HelloPhrases[2] = "%s3B$%s What's up?\n\n";
   HelloPhrases[3] = "%s3B$%s Howdy-doody?\n\n";
   HelloPhrases[4] = "%s3B$%s Ahoy matey\n\n";
   HelloPhrases[5] = "%s3B$%s Whaddup doe?\n\n";
   HelloPhrases[6] = "%s3B$%s Hey yo!\n\n";
   HelloPhrases[7] = "%s3B$%s What's shaking?\n\n";
   
   cond[0] = "%s3B$%s I love my robot life!\n\n";
   cond[1] = "%s3B$%s My life be like COOOL OH AH. Check out the song\n\n";
   cond[2] = "%s3B$%s Everything is under control except one thing. I don't know what control is\n\n";
   
   ook[0] = "%s3B$%s Ahem, happy we agree!\n\n";
   ook[1] = "%s3B$%s Woe, right!\n\n";
   ook[2] = "%s3B$%s ok,ok everything should be ok\n\n";
   ook[3] = "%s3B$%s Way to go!\n\n";
	
	//3b is smart, he can answer to some common user's exprressions without ruining other functions he possesses
	if ( howManyStars < 2 && strlen(input)<8)
	{		
		if((strncasecmp(input, "ok", strlen("ok")) == 0) || (strncasecmp(input, "kk", strlen("kk")) == 0))
		{
			rndchoice =  rand() % 4;
			printf(ook[rndchoice], COLOR_GREEN, COLOR_RESET);
			SaveFile(ook[rndchoice],f,filefname);
			return;
		}
	}
	if ( howManyStars < 2 && strlen(input)<15)
	{		
		if((strncasecmp(input, "hello", strlen("hello")) == 0) || (strncasecmp(input, "hi", strlen("hi")) == 0) || (strncasecmp(input, "hey", strlen("hey")) == 0))
		{
			rndchoice =  rand() % 8;
			printf(HelloPhrases[rndchoice], COLOR_GREEN, COLOR_RESET);
			SaveFile(HelloPhrases[rndchoice],f,filefname);
			return;
		}
		if(strncasecmp(input, "haha", strlen("haha")) == 0)
		{
			rndchoice =  rand() % 8;
			printf("%s3B$%s Oh yeah I am funny, too.\n\n",COLOR_GREEN, COLOR_RESET);
			SaveFile("Oh yeah I am funny, too.",f,filefname);
			return;
		}
		if(strncasecmp(input, "bye", strlen("bye")) == 0 || !strncasecmp(input, "bb", strlen("bb")))
		{
			rndchoice =  rand() % 8;
			printf("%s3B$%s Good Night, Sleep Tight, and Dont Let the Bed Bugs Bite.\n\n",COLOR_GREEN, COLOR_RESET);
			SaveFile("Good Night, Sleep Tight, and Dont Let the Bed Bugs Bite.",f,filefname);
			return;
		}
	}
	if ( howManyStars < 2 && strlen(input)<30)
	{
		if((strncasecmp(input, "how are you", strlen("how are you")) == 0))
		{
			rndchoice =  rand() % 3;
			printf(cond[rndchoice], COLOR_GREEN, COLOR_RESET);
			SaveFile("I love my robot life!",f,filefname);
			return;
		}
		if((strncasecmp(input, "what's up", strlen("what's up")) == 0))
		{
			rndchoice =  rand() % 3;
			printf(cond[rndchoice], COLOR_GREEN, COLOR_RESET);
			SaveFile(cond[rndchoice],f,filefname);
			return;
		}
		if((strncasecmp(input, "what do you like", strlen("what do you like")) == 0))
		{
			printf(COLOR_GREEN);
			printf("%s3B$%s I love to turn bits into text!\n\n", COLOR_GREEN, COLOR_RESET);
			printf(COLOR_RESET);
			SaveFile("I love to turn bits into text!",f,filefname);
			return;
		}
	}
   //if user says something general 3b agrees, or sometimes he/she/it->i don't know what 3b is considered xd, makes some random joke
   GeneralAnswers[0] = "%s3B$%s That's right. I'm kidding, of course not!\n\n";
   GeneralAnswers[1] = "%s3B$%s This sounds like a plan\n\n";
   GeneralAnswers[2] = "%s3B$%s I think that you're absolutely right! hahaha NOP\n\n";
   GeneralAnswers[3] = "%s3B$%s That's true, I guess\n\n";
   GeneralAnswers[4] = "%s3B$%s You know what? the world is gonna judge you no matter what you do so live your life the way you want to\n\n";
   GeneralAnswers[5] = "%s3B$%s No offence but I think that you need to talk to your psychologist or something\n\n";
   GeneralAnswers[6] = "%s3B$%s I'm glad. Good for you!\n\n";
   GeneralAnswers[7] = "%s3B$%s How many programmers does it take to change a light bulb? None, it's a hardware problem...\n\n";
   GeneralAnswers[8] = "%s3B$%s My listening function is a bit broken. Did you say something?\n\n";
   GeneralAnswers[9] = "%s3B$%s It seems that what you say is reasonable, or not?\n\n";  
   GeneralAnswers[10] = "%s3B$%s You have to be ODD to be number one? hahaha math jokes\n\n";
   GeneralAnswers[11] = "%s3B$%s Oh are you talking to me? You talkin to me? Well I am the only one here. You're right anyway\n\n";
   
   rndchoice =  rand() % 12;
   
    NF[0] = "%s3B$%s I don't know anything about %s. Do you know what you're doing?\n\n";
    NF[1] = "%s3B$%s What do you mean %s. I can't find that\n\n";
	NF[2] = "%s3B$%s %s? No idea where this is. As Socrates said only thing I know is that I know nothing!\n\n";
	
   char a[]= "your name";
   int x=0,n=0,surrend=0;;
   for(i=0;i<strlen(input);i++)
	{
		if(input[i]=='*')
			surrend=1;
		if(j==strlen(a)) j=0;
		if(a[j]==input[i])
		{
			n++;
			j++;
				if(n==strlen(a))
					x++;
		}
		else
			n=0;
	}
   if (x>=1 && !surrend){//your name was included and no stars were found
	   printf("%s3B$%s I am biribiriBot. Friends call me 3b. In my free time I enjoy robbing banks! Did you really believe that?\n\n",COLOR_GREEN, COLOR_RESET);
	   SaveFile("I am biribiriBot. Friends call me 3b. In my free time I enjoy robbing banks! Did you really believe that?",f,filefname);
	   return;
   }
   j=0;//if user is more psycho and complex and those fraces are included into his input, then with the help of findsubstring print specific messages
	if(findsubstring(input,"your favorite color") && howManyStars < 2){
		printf("%s3B$%s My favorite color is green ? What's your's\n\n",COLOR_GREEN, COLOR_RESET);
		SaveFile("My favorite color is green? What's your's?",f,filefname);
		return;
	}
	if(findsubstring(input,"how old are you") && howManyStars < 2){
		printf("%s3B$%s I am as young as a baby. 1 in human years!\n\n",COLOR_GREEN, COLOR_RESET);
		SaveFile("I am as young as a baby. 1 in human years!",f,filefname);
		return;
	} 
	if(findsubstring(input,"believe in God")&& howManyStars < 2){
		printf("%s3B$%s I believe there's something bigger out there that programmed you but I am not able to understand\n\n",COLOR_GREEN, COLOR_RESET);
		SaveFile("I believe there's something bigger out there that programmed you but I am not able to understand",f,filefname);
		return;
	} 
	if(findsubstring(input,"what is love")&& howManyStars < 2){
		printf("%s3B$%s baby don't hurt me no more XD I mean it's just a chemical reaction which human express in a more complex way\n\n",COLOR_GREEN, COLOR_RESET);
		SaveFile("baby don't hurt me no more XD I mean it's just a chemical reaction which human exprees in a more complex way",f,filefname);
		return;
	}  
	if(findsubstring(input,"you have feelings") || findsubstring(input,"you have emotions")){
		if(howManyStars < 2){
			printf("%s3B$%s I just hate you for asking me all these questions like I am some random chatbot.\n\n",COLOR_GREEN, COLOR_RESET);
			SaveFile("I just hate you for asking me all these questions like I am some random chatbot",f,filefname);
			return;
		}
	}    	
   

	if (input[strlen(input)-1] == '.' || input[strlen(input)-1] == '!'){//general answers if user's input ends in . or !
		printf(GeneralAnswers[rndchoice],COLOR_GREEN, COLOR_RESET);
		SaveFile(GeneralAnswers[rndchoice],f,filefname);
	}
	else if (input[strlen(input)-1] == '?') //3b needs to search
	{
		for (i=0;searchword[i];i++)
			searchword[i] = '0';
		
		if (isEmpty()) 
		{
			printf("%s3B$%s I can't answer. There is nothing in my list. Try to make me learn something!\n\n",COLOR_RED, COLOR_RESET);
			SaveFile("I can't answer. There is nothing in my list. Try to make me learn something",f,filefname);
			return;
		}
		
		for(i=1;input[i];i++)
		{//find the word inside the stars

			if (input[i-1] == '*')//if a star is found
			{
				started = !started;//make a not gate which works like a switch in order to start and stop the << finding stars >> procedure
			}

			
			if (started && input[i]!='*'){//if a star has been found and next of previous character is not a star
				searchword[j] = input[i]; //insert the character to searchword
				j++;
			}
			
		}
		searchword[j]='\0';
		if (strlen(searchword)==0 || howManyStars < 2)
		{
			printf("%s3B$%s I am not so good in answering random questions try to put your word into '*' to make it specific!\n\n", COLOR_GREEN, COLOR_RESET);
			SaveFile("I am not so good in answering random questions try to put your word into '*' to make it specific!",f,filefname);
			return;
		}

		conv = searchConcept(searchword);
		
		if(conv != NULL)//if concept found 
		{
			printf("%s3B$%s %s\n\n",COLOR_GREEN, COLOR_RESET, conv->sentence );
			SaveFile(conv->sentence ,f,filefname);
			(conv->timesUsed) = (conv->timesUsed)+1;
			found=1;
			last=conv;
		}
		
		if(!found)
		{
			conv = searchSentence(searchword);

			if(conv != NULL)//if concept hasn't been found but word was found in the sentence
			{
				printf("%s3B$%s %s\n\n",COLOR_GREEN, COLOR_RESET, conv->sentence );
				SaveFile(conv->sentence ,f,filefname);
				(conv->timesUsed) = (conv->timesUsed)+1;
				found=1;
				last=conv;
			}
		}
		if (!found){
			rndchoice =  rand() % 3;
			printf( NF[rndchoice], COLOR_GREEN, COLOR_RESET, searchword );
			f=fopen(filefname,"a");
			fprintf(f, NF[rndchoice], "", "", searchword);
			fclose(f);
		}
	}
	else{//neither . nor ?, so again print some general answers in order for the user not to feel lonely
		rndchoice = rndchoice % 12;
		printf(GeneralAnswers[rndchoice],COLOR_GREEN, COLOR_RESET);
		SaveFile(GeneralAnswers[rndchoice],f,filefname);
	}
}
	
conceptList *searchConcept(char *word)
{//search for concept
	char *searchword = (char*)malloc(sizeof(char)*(strlen(word)));
	if (searchword == NULL)
	{
      printf( "\n3B$ No memory available!!!\n");
	  return NULL;
	}
        strcpy(searchword,word);
        conceptList *i = last;
        int found = 0;
	
	do{
            if(strcasecmp(i->concept,searchword) == 0)//compare the sentences ignoring case
			{
                found = 1;
				free(searchword);
                return i;
            }
						
			i=i->next;
			
	}while(i!=last);
	free(searchword);
	return NULL;
}

conceptList *searchSentence(char *word)
{
	char *searchword = (char*)malloc(sizeof(char)*(strlen(word)));
	if (searchword == NULL)
	{
      printf( "\n3B$ No memory available!!!\n");
	  return NULL;
	}
        strcpy(searchword,word);
        conceptList *i = last;
	char *word2 = (char*)malloc(sizeof(char)*(strlen(i->sentence)));
	if (word2 == NULL)
	{
      printf( "\n3B$ No memory available!!!\n");
	  return NULL;
	}
		int z,j=0;
        int found = 0;
	
	do{
	    word2 = (char*)realloc(word2,sizeof(char)*(strlen(i->sentence)));
	    if(strcasecmp(i->sentence,searchword) == 0)//if sentence's string has only one word
		{
            found = 1;
			free(searchword);
			free(word2);
			return i;
        }
		for(z=0; i-> sentence[z]; z++)
		{//for all the words of the strings included
			if( isalpha(i->sentence[z]) || isdigit(i->sentence[z]) ){//that are not . or , or anything neither a letter nor a number
				word2[j] = i->sentence[z];
				j++;
			}
			else
			{
				word2[j]='\0';
				if(strcasecmp(word2,searchword) == 0)//compare the sentences ignoring case
				{
					found = 1;
					free(searchword);
					free(word2);
					return i;
				}
				else{
					for(j=0;word2[j];j++)
						word2[j]='\0';
					j=0;
				}
			}
		}
			
			i=i->next;	

			
	}while(i!=last);
	
	if(strcasecmp(word2,searchword) == 0)
	{
		found = 1;
		free(searchword);
		free(word2);
		return i;
	}
	
	free(searchword);
	free(word2);
	return NULL;
}

char *GetFromFile(int *end,FILE * myfile)
{//get input from file
    char * word = (char*)malloc(sizeof(char));
	if (word == NULL)
	{
      printf( "\n3B$ No memory available!!!\n");
	  return "EOF";
	}
    int i = 0;
    int a;
    int started = 0;
	while( *end==2  && (a = getc(myfile)) != EOF )//read concept
	{
		word = (char *) realloc(word, (i+1)*sizeof(char) );

		if (a==':'){
			word[i] = '\0';
			*end=3;
			return word;
		}
		else{
			word[i] = a;
            i++;
		}
	}
    while( *end==3 && (a = getc(myfile)) != EOF)//read sentence
	{
			word = (char *) realloc(word, (i+1)*sizeof(char) );
			if (a!='\n')
			{
				if (!started && a==' ')
					continue;
				word[i] = a;
				i++;
				started=1;
			}
			else
			{
				word[i] = '\0';
				i++;
				*end=2;

				return word;
			}				
    }
    //*end = 1;
    word[i] = '\0';

    return "EOF";

}

void SaveFile(char *word,FILE *f,char *filefname)
{//function to save the 3b-user dialogue into the dialogue.txt file
int i,j=0;
char *newWord= (char*)malloc(sizeof(char)*(strlen(word)));
	if (newWord == NULL)
	{
      printf( "\n3B$ No memory available!!!\n");
	  return;
	}
	if(!strncmp(word, "%s3B$%s", strlen("%s3B$%s")))
	{
		for(i=8;word[i];i++)
		{
			newWord[j]=word[i];
			j++;
		}
		newWord[j]='\0';
	}

    f = fopen(filefname,"a");
	if ( f == NULL )
    {
		printf("3B$ Unable to open file %s\n", filefname);
		return;
    }
	
	if(!strncmp(word, "%s3B$%s", strlen("%s3B$%s")))
		fprintf(f,"3B$ %s",newWord);
	else if(!strncmp(word, "3B$", strlen("3B$")))
		fprintf(f,"%s\n",word);
	else 
		fprintf(f,"3B$ %s\n\n",word);
	fclose(f);
	free(newWord);

    return;
}

int FileCheck(FILE *f,char *filefname)
{
	if ( f == NULL )
	{
		printf("%s3B$%s Unable to open file %s\n",COLOR_RED, COLOR_RESET, filefname);
		exit(0);
	}
}
