/*
	 Hangman by
	 
	 

*/
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

int randInt(int i);//function for random number generator
void printCharArrS(char arr[]);//print an string array with a space betn the letters 
void HangMan_main(int mode);//main body
void menu();//main menu
char * fileOpen();//to open the 'words.txt' in the singleplayer and retuen a word from the set of words
void restart(int mode);

int main(){
	menu();
}

void menu(){
	int num;
	char choice;
	printf("-------------------MAIN MENU-------------------");
	printf("\nPress :\n");
	printf("\t[1] Single Player\n");
	printf("\t[2] Multiplayer Player\n");
	printf("\t[3] To Exit\n");
	printf("NOTE : You can add or remove words on file 'words.txt' ");
	printf("\n\nEnter your choice : ");
	scanf(" %c",&choice);
	switch(choice){
		case '1':
			HangMan_main(1);
			break;
		
		case '2':
			HangMan_main(2);
			break;
		
		case '3':
			exit(0);
			
		default:
			printf("Invalid Input\n");
			printf("Please Try Again\n\n");
			menu();
	}
}

void HangMan_main(int mode){
	char asd;//note the variable asd is used to capture a fugitive 'enter' and prevent it from taking the array arr[]  
	int i,size,j,k,count=0;
	char arr[20],dup[20],blank[20];
	char clue[20]={'\0'};
	char guess;
	int random;
	int chance;
	
	//mode specifies single player or multiplayer (i.e. 1 or 2)
	//You only need to take input on multiplayer so mode==2
	if(mode==2){
		printf("Enter any Word :"); //take input from player
		scanf("%c",&asd);
		
		//store input
		for(i=0;i<20;i++){
			scanf("%c",&arr[i]);
			if(arr[i]=='\n'){
				arr[i]='\0';
				break;
			}	
		}		
	}
	else{
		//fileOpen returns a string which is copied to arr
		strcpy(arr,fileOpen());
	}
	
	
	size=strlen(arr);			//find length of word
	
	random=randInt(size%10);	//create a random int 
	
	//create a duplicate word
	for(i=0;i<size;i++)			
	{
		dup[i]=arr[i];
	}
	system("cls");
	
	
	//create an array with '_' to replace the letters of the word
	for(i=0;i<size;i++)
	{
		blank[i]='_';
	}
	
	printf("\n");
	
	//use random number and size of array to create the chances of answer (longer the word more chances will be provided and smaller the word the chances will be decreased)
	if(size>6){
		chance=size-3+random;
	}
	else{
		chance=size-random;
	}
	
	
	//use random number to give hints on the '_' blank spaces 
	if(random>=0&&size>6){
		for(i=0;i<random;i++){
			int clue=randInt(size);
			char hint1;
			hint1=arr[clue];
			//printf("\n %c  00    %c  00  %d  asd %d 00\n",hint1,arr[clue],random,clue);
			for(j=0;j<size;j++){
				if(dup[j]==hint1){
					//printf("\n %c         %c    \n",dup[j],hint1);
					blank[j]=hint1;
				}
			}
		}
	}
	printCharArrS(blank);
	
	do
	{
		int check=0;
		for(i=0;i<size;i++){
			if(dup[i]==blank[i])
				{check++;}
		}
		if(check==size){
			printf("\n-----------You Win-----------\n");
			restart(2);
		}
		else{
			printf("\nLetters already guessed :");		
			printCharArrS(clue);
			
			printf("\nChances Remain : %d",chance);
		
			printf("\nGuess the letter : ");	
			scanf(" %c",&guess);
		
			//check the letter is correct or not
			//chance will be decreased for every word but if the guess word is in the array it will increase to prevent it from going down
			for(j=0;j<size;j++){
				//printf("\n%c\t%c\t%c\n",arr[i],blank[i],guess);
				if(guess==arr[j]){
					blank[j]=guess;
					chance++;	
				}	
			}
			
			
			clue[count]=guess;
			count++;
	
			printCharArrS(blank);
			printf("\n");
			chance--;
			
			//when you run out of chances you check if the word is completely guessed
			if(chance==0){
				check=0;
				for(i=0;i<size;i++){
					if(dup[i]==blank[i])
					{check++;}
				}
				if(check==size){
					printf("\n-----------You Win-----------\n");
					restart(mode);
				}
			}		
		}	
	}while(chance!=0);
	//if the letters are not guessed the player loses
	if(chance==0){
		printf("\n-----------You Lose-----------\nThe Word was :");
		printCharArrS(dup);
		restart(mode);
	}
}


void printCharArrS(char arr[]){
	int i;
	for(i=0;i<strlen(arr);i++)
		{	if((arr[i]>64&&arr[i]<91)||(arr[i]>96&&arr[i]<123)||arr[i]==95)
				printf("%c ",arr[i]);
		}

}


//A function for a random number generator
int randInt(int i){
	time_t t;
	srand((unsigned) time(&t));
       int n=rand()%i;    
    return n;
}


//After a game is finished (either in win or lose) the program naturally ends. So a function is created to allow the player to traverse the menu options.
//mode 1 specifies Single Player
//mode 2 specifies Multi Player

void restart(int mode){
	char choice;
	printf("\nPress:\n");
	printf("\t[1] To Play Again\n");
	printf("\t[2] To Go To Main Menu\n");
	printf("\t[3] To Exit\n");
	
	printf("Enter your choice : ");
	scanf(" %c",&choice);
	switch(choice){
		case '1':
			system("cls");
			if (mode == 2){ HangMan_main(mode); }	
			else { HangMan_main(1); }
		case '2':
			system("cls");
			menu();
			
		case '3':
			exit(0);
			
		default:
			printf("\nInvalid Input\n");
			printf("Please Try Again\n\n");
			restart(mode);
	}
}

char * fileOpen(){
	FILE *fptr;
    char ch;
    fptr = fopen("words.txt", "r");
    static char line[25];
	int l = 0;
	int linesCount=0;
    	
    if (fptr == NULL)
    {
 	 	printf("\nThe necessary text file or folder is missing. \n");
     	printf("\nCreate a file named 'words.txt' in the same directory as this exe\n");
   	 	printf("The words u want can be added or removed in this file (NOTE: the words should be connected and each line should have only 1 word)");
    	printf("\n\n\n");
      	menu();
    }
    	
    	//Counts the total number of lines in a file	
//    	while((ch=fgetc(fptr))!=EOF) {
//     		if(ch=='\n')
//        		{ linesCount++; }
//   		}
//   		linesCount++;
//    	
    	l=0;
    	linesCount=1067;
    	
    	//printf("\n\n linecount %d\n\n",linesCount);
    	
    	while (fscanf(fptr, "%s", &line) != EOF ) {
        	if(l == randInt(linesCount) )
        	{
        		break;
        	}
        	else
        		l++;
 		}
    	fclose(fptr);
    	return line;
}

