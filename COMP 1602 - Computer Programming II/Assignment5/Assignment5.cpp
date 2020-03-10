#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

struct Word{
	char word[50];
};

bool isLetter(char ch) {
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
	 	return true;
	return false;
}	

bool isUpperCaseLetter (char c) {
 	if (c >= 'A' && c <= 'Z')
 		return true;
	 return false;
} 

char upperToLower(char ch ){
 	if (isUpperCaseLetter(ch))
 		ch = ch + 32;
 	return ch;
}

void cstrLower(char word[]){
	int i=0;
	
	while(word[i]!='\0'){
		if(isUpperCaseLetter(word[i])){
			word[i]=upperToLower(word[i]);
		}
		i++;
	}
}



int getWord (char data[], int start, char word[]) {
	 int i, j;
	 
	 int size = strlen (data); 
	
	 i = start;
	
	while (i < size && (!isLetter(data[i])))
 		i = i + 1; 
 	
 	if (i >= size)
 		return 0; 
	
	 j = 0;
	 while (isLetter(data[i])) {
	 word[j]= data[i];
	 i = i + 1;
	 j = j + 1;
	 }
	 word[j]= '\0';
	
	 return i;
}
/*
int getWords (char data[], Word words[]){
	
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
*/

int readFile(Word words[][100]){
	ifstream fin("synonyms.txt");
	
	if(!fin.is_open()){		
		return -1;
	}		
	
	char word[50];	
	int m;	
	int j=0,i=0;
	char data[1001];
	
	fin>>noskipws;
	
		
	while(!fin.eof()){
		fin.getline(data,1000);		
		m=0;
		m=getWord(data,m,word);
		while(m>0){
			cstrLower(word);
			strcpy(words[i][j].word,word);
			j++;
			m=getWord(data,m,word);
		}
		strcpy(words[i][j].word,"end");
		i++;  j=0;				
	}
	
	fin.close();
	
	return i;
}

void swap(Word arr[], int i, int j){
	Word temp;
	strcpy(temp.word,arr[i].word);
	strcpy(arr[i].word,arr[j].word);
	strcpy(arr[j].word,temp.word);
	
}
void bubbleSort(Word arr[], int n){
	bool swapped=true;
	int j=0;
	
	while(swapped){
		swapped=false;
		j++;
		for(int i=0;i<n-j;i++){
			if(strcmp(arr[i].word,arr[i+1].word)>0 ){
				swap(arr,i,i+1);
				swapped=true;
			}
		}
	}
}
	
int readDict(Word dict[500]){
	ifstream fin("dictionary.txt");
	
	if(!fin.is_open()){
		return -1;
	}
	int i=0;

	while(!fin.eof()){
		fin>>dict[i].word;
		i++;
	}
	fin.close();
	
	for(int j=0;j<i;j++){
		cstrLower(dict[j].word);
	}
	
	bubbleSort(dict,i);

	fin.close();

	
	return i;
}



void displayWordsSyn (Word words[][100],int val){
	
	cout<<endl<<"Words"<<"\t\t\t"<<"Synonyms"<<endl;
	cout<<"============================================================================"<<endl;
	for(int i=0;i<val;i++){
		int j=0;
		while(strcmp(words[i][j].word,"end")!=0){
			if(j==0){
				if(strlen(words[i][j].word)>7)
					cout<<words[i][j].word<<"\t\t";
				else {
					cout<<words[i][j].word<<"\t\t\t";
				}
			} else{
				cout<<words[i][j].word<<"  ";
			}				
			j++;
		}
		cout<<endl;
	}		
	
}
	

void searchSynonyms(Word words[][100],int val){
	int i=0, j=0;
	if(val==-2){
		cout<<"You have not loaded the synonyms via Option 1."<<endl;
	} else {
		
		char word[50];
		int pos=-1;
		cout<<"Enter a word to find a synonym for: ";
		cin>>word;
		cstrLower(word);		
		for(i=0;i<val;i++){
			j=0;			
			while(strcmp(words[i][j].word,"end")!=0){								
				if(strcmp(words[i][j].word,word)==0){
					pos=i;
					break;
				}	
				j++;
			}
		}
		if(pos!=-1){
			cout<<"Synonyms for "<<word<<" is/are: ";
			int j=0;
			while(strcmp(words[pos][j].word,"end")!=0){
				if(strcmp(words[pos][j].word,word)!=0){
					cout<<words[pos][j].word<<"  ";
				}
				j++;
			}
		} else{
			cout<<"No synonyms are found for "<<word;
		}			
		
	}	
	
	
}

bool checkDictionary(Word dict[],char word[],int lo, int hi){
	int mid;
	
	while(lo<=hi){
		mid=(lo+hi)/2;
		if(strcmp(word,dict[mid].word)==0)
			return mid;
		else if (strcmp(word,dict[mid].word)<0)
			hi=mid-1;
		else 
			lo=mid+1;
	}
	
	return false;	
	
}

bool checkSynonym(Word words[][100],char word[], int val, int val2, Word dict[]){
	int i=0, j=0;
	int row=-1;
	for(i=0;i<val;i++){
		j=0;		
		while(strcmp(words[i][j].word,"end")!=0){								
			if(strcmp(words[i][j].word,word)==0){
				row=i;			
			}			
			j++;
		}
	}	
	
	if(row!=-1){
		j=0;
		while(strcmp(words[row][j].word,"end")!=0){
			if(checkDictionary(dict,words[row][j].word,0,val2))
						return true;
				j++;
		}	
	}
	
	
	return false;
	
}

void parseSent(Word words[][100],Word dict[],int val, int val2){
	char data[501];
	char word[50];
	int i=0;	
	bool correct=true;
	
	cin.ignore();
	
	
	cout<<"Enter a sentence: ";
	cin.getline(data,500);
	

	i=getWord(data,i,word);

	
	while(i>0){
		cstrLower(word);
		if(!checkDictionary(dict,word,0,val2)){
		
			if(!checkSynonym(words,word,val,val2, dict)){
				correct=false;
				cout<<word<<" was not found in the dictionary nor were its synonyms."<<endl;
			} 
		}	
		i=getWord(data,i,word);
	}
	
	if (correct){
		cout<<"All of the words in the sentence, or their synonyms, were found in the dictionary."<<endl;
	} 
}


int main(){
	Word words[100][100];
	Word dict[500];
	int val=-2;
	int val2=-2;
	int option;
	cout<<"Synonym Checker"<<endl;
	cout<<"----------------------------------------"<<endl;
	cout<<"1. Load Synonyms"<<endl;
	cout<<"2. Search Synonyms"<<endl;
	cout<<"3. Display Words and Synonyms"<<endl;
	cout<<"4. Parse Sentence"<<endl;
	cout<<"5. Quit"<<endl;
	
	cout<<endl<<"Please enter an option: ";
	cin>>option;
	
	
	while(option!=5){
		if(option==1){
			val=readFile(words);
			if(val==-1){
				cout<<"synonyms.txt not found."<<endl;;
			}
			val2=readDict(dict);
			if(val2==-1){
				cout<<"dictionary.txt not found."<<endl;
			}
		} 
		else if (option==2){
			searchSynonyms(words,val);
		}
		else if(option==3){
			displayWordsSyn(words,val);
		}
		else if (option==4){
			parseSent(words,dict,val,val2);
			
		}
		else if(option!=5){
			cout<<"You have enterred an invalid menu choice."<<endl;
		}
		
		cout<<endl<<endl<<"Synonym Checker"<<endl;
		cout<<"----------------------------------------"<<endl;
		cout<<"1. Load Synonyms"<<endl;
		cout<<"2. Search Synonyms"<<endl;
		cout<<"3. Display Words and Synonyms"<<endl;
		cout<<"4. Parse Sentence"<<endl;
		cout<<"5. Quit"<<endl;
		
		cout<<endl<<"Please enter an option: ";
		cin>>option;		
	}
	
	
	return 0;
}
