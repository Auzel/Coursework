#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;


#define NUMROWS 10				// for drawing hangman diagram
#define NUMCOLS 12				// for drawing hangman diagram

int start=0;

struct Word {
	char word [25];
	char category [25];
	bool used;
};

struct User{
	char fname[25];
	char lname[25];
	char category[25];
	char guessL;
	char guessW[25];
	int livesLost;
	int score;
	char choice;
};

int randomNumber (int max) {
	return rand() % max;
}

int readCharacters(char data[]) {        
 
    ifstream fin;     
	char ch;     
	int i;             
	
	fin.open("words.txt");     
	
	if (!fin.is_open()) {         
		cout << "Error -- words.txt could not be opened." << endl;         
		return -1;
	}         
	
	i = 0;
	
	fin >> noskipws;          
	fin >> ch;  
	   
	while (!fin.eof()) {           
		data[i] = ch;          
		i = i + 1;           
		fin >> ch;     
	}          
	
	data[i] = '\0';          
	fin.close();
	                
	return i; 

} 

bool isLetter (char c) {
	if ((c >= 'A' && c <= 'Z') ||
	    (c >= 'a' && c <= 'z'))
		return true;
	else
		return false;
}

char toLowerCase(char c){
	if(isLetter(c)){
		if(c>='A' && c<='Z'){
			return (c+32);
		}
	}
	return c;
}

void stringToLowerCase(char guessW[]){
	int i=0;
	for(i=0;i<strlen(guessW);i++){
		guessW[i]=toLowerCase(guessW[i]);
	}
}

int getWord (char words[], int start, char word[]) { 
 
    int i, j, length;         
	
	length = strlen (words);			// find how many characters in words
	
	i = start;
	while (i < length && !isLetter(words[i]))
		i = i + 1;    
		         
		
	if (i == length)					// there are no more words
		return -1;	
		
	if (i>length)						// start outside the positions of the array
		return 0;				
		
	j = 0;     							// copy characters to word
	while (isLetter(words[i])) {
		//common letters to store in j
		word[j]= toLowerCase(words[i]);
		i = i + 1;
		j = j + 1;     
	}       
 
    word[j]= '\0';          
    
	return i;							// starting position to look for next word
}

//This function obtains all the words and their corresponding categories from the allWords
// array of characters. The Word structs are stored in the words array.
int getWords (char allWords[], Word words[]){
	int i=0;
	char word[25];    
	int wordCount=0;  
	
	int marker=1;
	i = getWord(allWords, i, word);  
	
	
	wordCount = 0;     
	while (i > 0) {   
		if(marker%2==1) {
			strcpy(words[wordCount].word,word);
		}			
		else {
			strcpy(words[wordCount].category,word);
			words[wordCount].used=false;
			wordCount = wordCount + 1; 
		}
		marker++;
		i = getWord(allWords, i, word);            
	}          	
	
	return wordCount;

}
	


void prepareGallows(char drawing[NUMROWS][NUMCOLS]) {
	int i, j;
	
	for (i=0; i<NUMROWS; i++) {
		for (j=0; j<NUMCOLS; j++) {
			drawing[i][j] = ' ';
		}
	}
		
	for (j=3; j<7; j++)
		drawing[0][j] = '_';

	for (i=1; i<7; i++)
		drawing[i][2] = '|';
	
	for (j=5; j<11; j++)
		drawing[7][j] = '_';
			
	for (j=1; j<11; j++)
		drawing[9][j] = '_';
	
	drawing[1][7] = '|';
	
	drawing[6][1] = '_';
	drawing[6][3] = '_';
	
	drawing[7][0] = '|';
	drawing[8][0] = '|';
	drawing[9][0] = '|';

	drawing[7][4] = '|';	

	drawing[8][11] = '|';	
	drawing[9][11] = '|';	
}

// The following is the new version of the drawHangman function.
//  It calls the prepareGallows function above.

void drawHangman (int livesLost) {
	char drawing [NUMROWS][NUMCOLS];
	int i, j;
	int lives;
	
	prepareGallows(drawing);
		
	if (livesLost >= 1)
		drawing[2][7] = 'o';

	if (livesLost >= 2) {
		drawing[3][7] = 'X';
		drawing[4][7] = 'X';				
	}

	if (livesLost >= 3)
		drawing[3][6] = '/';

	if (livesLost >= 4)
		drawing[3][8] = '\\';

	if (livesLost >= 5)
		drawing[5][6] = '/';

	if (livesLost == 6)
		drawing[5][8] = '\\';
	
	for (i=0; i<NUMROWS; i++) {
		for (j=0; j<NUMCOLS; j++) {
			cout << drawing[i][j];
		}
		cout << endl;
	}
	cout << endl;

	if (livesLost == 6)					// sound the alarm if player loses
		cout << "\a" << endl;
		
}

//User Defined Functions
//This function displays the word being guessed by the player where each letter is separated by a space.
void drawWord (char displayWord[]){
	int i=0;
	while(displayWord[i]!='\0'){
		cout<<displayWord[i++];
	}
	cout<<endl<<endl;
	
}

//This function finds wordSelected in the words array and sets its used field to true.
void setWordToUsed (Word words[], int numWords, char wordSelected[]){
	int i=0;
	
	for (i=0;i<numWords;i++){
		if( strcmp(words[i].word,wordSelected)==0  ){
			words[i].used=true;
			break;
		}
		
	}
	
}


//This function finds all the words in the words array that are in the category specified (if not used before) and stores them in an array.
//It then randomly chooses a word from this array and stores it in wordSelected. The randomNumber function can be called to
//generate a random location in the array.
bool findCategoryWord (Word words[], int numWords, char category[], char wordSelected []){
	Word cat[100];
	int i=0, j=0;
	
	for (i=0;i<numWords;i++){
		if( (strcmp(words[i].category,category)==0) && (words[i].used==false)){
			strcpy(cat[j].word,words[i].word);
			j++;
		}
		
	}
	if(j>0){
		int ranNum=randomNumber(j);
		strcpy(wordSelected,cat[ranNum].word);
		setWordToUsed(words,numWords,wordSelected);
	}
	

	return j; //return true or false
}

//This function initializes the word to be displayed based on the word to be guessed. It
//also reveals the letters from “RSTLNE” if they are present.
void initWord (char guessWord[], char displayWord[]){
	int i=0;
	
	for(i=0;i<strlen(guessWord);i++){
		if(guessWord[i]=='r'){
			displayWord[i]='r';
		}		
		else if (guessWord[i]=='s'){
			displayWord[i]='s';
		}
		else if (guessWord[i]=='t'){
			displayWord[i]='t';
		}	
		else if (guessWord[i]=='l'){
			displayWord[i]='l';
		}
		else if (guessWord[i]=='n'){
			displayWord[i]='n';
		}
		else if (guessWord[i]=='e'){
			displayWord[i]='e';
		} 
		else {
			displayWord[i]='_';
		} 
	}
	
	drawWord(displayWord);
	
}

int updateGuessAttempts(char guessLetters[], char letter){
	guessLetters[start]=letter;
	start++;
	return start;
}


bool duplicateLetter(char guessLetters[], char letter){
	int i=0;
	
	if (letter=='r' || letter=='s' || letter=='t' || letter=='l' || letter=='n' || letter=='e'){
		return true;
	} else {
		for(i=0;i<strlen(guessLetters);i++){
			if(guessLetters[i]==letter){
				return true;
			}
		}
	}
		
	return false;		
}


//This function checks the word to be guessed to determine if letter is present. If so, the
//corresponding letters in the displayWord are revealed.
bool checkLetter (char guessWord[], char displayWord[], char guessLetters[], char letter){
	int i=0;
	bool found=false;
	while(duplicateLetter(guessLetters, letter)){
		start = updateGuessAttempts(guessLetters, letter);
		cout<<"Your guess Letter is already present in the displayed word or present in the string 'RSTLNE'.\n\nPlease guess another letter: ";
		cin>>letter;
		while(!isLetter(letter)){
				cout<<endl<<"You have not entered a valid letter.";
				cout<<endl<<"Please guess a letter: ";
				cin>>letter;
				cout<<endl;
		}
		cout<<endl;
		
	}
	
	
	start = updateGuessAttempts(guessLetters, letter);
	for (i=0;i<strlen(guessWord);i++){
		if(guessWord[i]==letter){
			displayWord[i]=letter;
			found=true;
		}
	}
		

	return found;
}



//This function determines how many letters must still be guessed in the displayWord. The
//count includes repeated letters.
int lettersMissing (char displayWord[]){
	int i=0;
	int count=0;
	for(i=0;i<strlen(displayWord);i++){
		if(displayWord[i]=='_'){
			count++;
		}
	}
	return count;
}


void displayCategories(Word words[], int numWords){
	int i=0, j=0, k=0;
	bool flag=0;
	Word cat[100];
	cout<<"Here are the Categories that you can choose from: "<<endl;
	while(i<numWords){
		flag=0;
//		check for duplicates
		for(k=1;k<j;k++){
			if(strcmp(cat[k].category,words[i].category)==0){
				flag=1;
				break;
			}
		}
		if (!flag){
			strcpy(cat[j].category,words[i].category);
			j++;
			cout<<words[i].category<< "   ";
		}
			
		i++;
	}
	
	cout<<endl<<endl;
	cout<<"Enter the category of your choice: ";
}


void displayGuessAttempts(char guessLetters[]){
	int i=0;
	bool check=false;
	cout<<"Your previous guesses are: ";
	for (i=0;i<strlen(guessLetters);i++){
		if(isLetter(guessLetters[i])){
			cout <<guessLetters[i]<<"\t";
			check=true;
		}
	}
	if(!check)
		cout<<"No Letters as yet.";
}

void initGuessLetters(char guessLetters[]){
	int i=0;
	for(i=0;i<strlen(guessLetters);i++){
		guessLetters[i]=' ';
	}
}

//This function plays one game of Hangman with the user. There are three outcomes: the
//user loses, the user wins by guessing letters, and the user wins by guessing a complete word
//(where at least two letters were remaining).
int playGame(User user, Word words[], int numWords){
	user.livesLost=0;
	char wordSelected[25];	
	char displayWord[25];
	char guessLetters[27];
	initGuessLetters(guessLetters);
	
	displayCategories(words, numWords);
	cin>>user.category;
	
	while(!findCategoryWord(words,numWords,user.category,wordSelected)){
		cout <<endl<< "Sorry, You have entered an incorrect category or no more words are left in this category.\nPlease enter a different category: ";
		cin>>user.category;
	}	
		
	displayWord[strlen(wordSelected)]='\0';
	drawHangman(user.livesLost);
	cout<<endl;
	initWord(wordSelected,displayWord);
	
	cout << "You have "<<6-user.livesLost<<" lives remaining."<<endl;
	cout << "Your score is: "<<user.score<<endl<<endl;

	start=0;
	while ((user.livesLost<6) && (lettersMissing(displayWord)>0) && (strcmp(user.guessW,wordSelected)!=0) ) {
		displayGuessAttempts(guessLetters);
		cout<<endl<<endl;
		cout<<"Please guess a letter (Enter # to guess entire word): ";
		cin>>user.guessL;
		while(!(isLetter(user.guessL) || user.guessL=='#')){
			cout<<endl<<"You have not entered a valid letter";
			cout<<endl<<"Please guess a letter (Enter # to guess entire word): ";
			cin>>user.guessL;
		}
		user.guessL=toLowerCase(user.guessL);
		if(user.guessL!='#'){
			if(checkLetter(wordSelected,displayWord,guessLetters,user.guessL)){
				cout<<endl;
				drawHangman(user.livesLost);
				drawWord(displayWord);
			} else {
				user.livesLost++;
				drawHangman(user.livesLost);
				drawWord(displayWord);
				
			}
		} else {
			cout<<endl;
			cout<<"Enter your guess word: ";
			cin>>user.guessW;
			stringToLowerCase(user.guessW);
			if(strcmp(user.guessW,wordSelected)!=0){
				user.livesLost+=2;
				if(user.livesLost>=6){
					drawHangman(6);
				} else {
					drawHangman(user.livesLost);
				}
				drawWord(displayWord);
				cout<<endl;
			} else {
				break;
			}
			
		}
		if (user.livesLost>=6){
				cout << "You have 0 lives remaining"<<endl;
		} else {
				cout << "You have "<<6-user.livesLost<<" lives remaining"<<endl;
		}
	}	
	
	if(lettersMissing(displayWord)==0){
		user.score+=2;
	} 
	else if((lettersMissing(displayWord)>=2)&& (strcmp(user.guessW,wordSelected)==0) ){
		user.score+=4;
	}
	else if (user.livesLost>=6){
		user.score-=2;
	}
	
	cout<<endl;
	if(user.livesLost>=6){
		cout<<endl<<"Game Over."<<endl;
	} else {
		cout<<endl<<"You won! Champ"<<endl;
	}
	cout<<endl;
	
	initGuessLetters(guessLetters); // initialize guess letters for next game
	
 return user.score;	
	
}

//The main function reads all the characters into an array and then creates an array of Word
//structs. It then repeatedly plays a game of Hangman until the user decides to quit.
int main() {
	srand(time(NULL));					// for better random number generation

	User user;
	user.score=0;
	char temp;
	char data[2000];
	Word words[100];
	int dataSize=0, numWords=0; 
	
	cout << "Please enter your first and last name: ";
	cin >> user.fname>>user.lname;
	cout<<endl;
	
	dataSize=readCharacters(data);
	
	if(dataSize>0) {
		
		numWords=getWords(data,words);
	
		user.score=playGame(user,words,numWords);
		cout<<endl;
		cout << "Player Name: "<<user.fname<<user.lname<< "\t\t"<< "Current Score: "<<user.score<<endl<<endl;
		cout<<"Would you like to play again?  Y|N: ";
		cin >> user.choice;
		cout<<endl<<endl;
		while(!(user.choice=='Y'|| user.choice=='N')){
			cout<<"You have chosen an Invalid option choice. Please re-enter your choice to play again.   Y|N"<<endl;
			cin>>user.choice;
		}
		
		while(user.choice=='Y'){
			user.score=playGame(user,words,numWords);
			cout<<endl;
			cout << "Player Name: "<<user.fname<<user.lname<< "\t\t"<< "Current Score: "<<user.score<<endl<<endl;
			cout<<"Would you like to play again?  Y|N: ";
			cin >> user.choice;
			cout<<endl<<endl;
		}
		
		cout<<endl<<"Thank you for playing Hangman!"<<endl;
	} 
	else if(dataSize==0){
		cout<< "No Data is in the file."<<endl;
	}
	
	cout<<endl<<endl <<"Pogram Exiting...";
		
	
	return 0;

		

	
}

