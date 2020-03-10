#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;


struct Date {
	int day;
	int month;
	int year;
	
};

Date getCurrentDate(){
    Date d;
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    d.day   = aTime->tm_mday;
    d.month = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
    d.year  = aTime->tm_year + 1900;

    return d;
}



//write structure definitions here
struct Actor {
	string id;
	string fName;
	string lName;
	char gender;
	int age;
	string bPlace;
	
};

struct Movie {
	int id;
	string name;
	string genre;
	Date releaseDt;
	long long int g2d;
	double starRating;
	
};

struct Cast {
	int mID;
	string aID;
	string role;
	
	
};





//write print functions to print the details of each structure

void printMovieInfo (Movie movies[],int pos) {
	cout << "Movie ID: "<< movies[pos].id<< "\tMovie Name: "<<movies[pos].name<< "\tGenre: "<<movies[pos].genre;
	cout << "\tRelease Date: "<< movies[pos].releaseDt.day<<"/"<<movies[pos].releaseDt.month<<"/"<<movies[pos].releaseDt.year;
	cout << "\tWorld Wide Gross: "<<movies[pos].g2d<<"  "<<"\tStar Rating: "<<movies[pos].starRating;

}


void printActorsInfo(Actor actors[],int pos) {
	cout<<"Actor ID: "<<actors[pos].id<<"\tFirst Name: "<<actors[pos].fName<<"\tLast Name: "<<actors[pos].lName<<"\tGender: "<<actors[pos].gender;
	cout<<"\tPlace of Birth: "<<actors[pos].bPlace<< "\tAge: "<<actors[pos].age;
}



//This function reads the data from the file actors.txt and creates Actor structures and inserts them in an array of Actor structures.
//The function accepts the array of Actor structures and returns the number of elements in the array.
int loadActors(Actor actors[]){
	ifstream fiA ("actors.txt");
		
	if(!fiA.is_open()){
		cout << "File not found"<<endl;
		return 1;
	}
	
	Actor temp;
	int i=0;
	
	fiA>>temp.id;
	while (temp.id!="END"){
		fiA>>temp.fName;
		fiA>>temp.lName;
		fiA>>temp.gender;
		fiA>>temp.age;
		fiA>>temp.bPlace;
		actors[i++]=temp;
		fiA>>temp.id;
	}
	
	fiA.close();
	
	return i;

}


//This function reads the data from the file movies.txt and creates Movie structures and inserts them in an array of Movie structures.
//The function accepts the array of Movie structures and returns the number of elements in the array.
int loadMovies (Movie movies[]){
	ifstream fiM ("movies.txt");
		
	if(!fiM.is_open()){
		cout << "File not found"<<endl;
		return 1;
	}
	
	Movie temp;
	int i=0;
	char slash=' ';
	
	fiM>>temp.id;
	while (temp.id!=0){
		fiM>>temp.name;
		fiM>>temp.genre;
		fiM>>temp.releaseDt.day;
		fiM>>slash;
		fiM>>temp.releaseDt.month;
		fiM>>slash;
		fiM>>temp.releaseDt.year;
		fiM>>temp.g2d;
		fiM>>temp.starRating;
		movies[i++]=temp;
		fiM>>temp.id;
	}
	
	fiM.close();
	
	return i;
}

//This function reads the data from the file cast.txt and creates Cast structures and inserts them in an array of Cast structures.
//The function accepts the array of Cast structures and returns the number of elements in the array.
int loadCast(Cast casts[]){
	ifstream fiC ("cast.txt");
		
	if(!fiC.is_open()){
		cout << "File not found"<<endl;
		return 1;
	}
	
	Cast temp;
	int i=0;

	
	fiC>>temp.mID;
	while (temp.mID!=0){
		fiC>>temp.aID;
		fiC>>temp.role;
		casts[i++]=temp;
		fiC>>temp.mID;
	}
	
	fiC.close();
	
	return i;

}

//This function prints the menu options and prompts the user to enter a choice.
void printMenu(){
	
	cout<<endl<<endl;
	cout<<"\t\t\t\t\t\tMenu"<<endl;
	cout<<"\t\t\t\t\t\t======"<<endl<<endl;
	cout<<"\t\t\t\t\t\t1. Movie Information"<<endl;
	cout<<"\t\t\t\t\t\t2. Movie Cast"<<endl;
	cout<<"\t\t\t\t\t\t3. Actor Information"<<endl;
	cout<<"\t\t\t\t\t\t4. Actor Filmography"<<endl;
	cout<<"\t\t\t\t\t\t5. Latest Release"<<endl;
	cout<<"\t\t\t\t\t\t6. Coming Soon"<<endl;
	cout<<"\t\t\t\t\t\t7. Top-Rated Movies"<<endl;
	cout<<"\t\t\t\t\t\t8. Exit"<<endl;
	
	cout << endl<<endl;
	cout<<"Please enter choice: ";
	
}

//This function searches the array of Actor structures for a given actor id. If the Actor with that actor id is found, the function returns the location in the array
//where the actor was found. If the actor is not found, the function returns -1.
int searchActorById(Actor actors[], int numActors, string actorID){
	for(int i=0;i<numActors;++i){
		if(actors[i].id==actorID)
			return i;
			
	}
	return -1;
	
}

//This function searches the array of Actor structures for a given actor by their name. If the Actor with that name is found, the function returns the location in the array
//where the actor was found. If the actor is not found, the function returns -1.
int searchActorByName(Actor actors[], int numActors, string fName, string lName){
	for(int i=0;i<numActors;++i){
		if(actors[i].fName==fName && actors[i].lName==lName)
			return i;
			
	}
	return -1;
}


//This function searches the array of Movie structures for a given movie by their name. If the Movie with that name is found, the function returns the location in the array
//where the movie was found. If the movie is not found, the function returns -1.
int searchMovieByName(Movie movies[], int numMovies, string movieName){
	for(int i=0;i<numMovies;++i){
		if(movies[i].name==movieName)
			return i;
			
	}
	return -1;
}


//This function searches the array of Movie structures for a given movie id. If the Movie with that movie id is found, the function returns the location in the array
//where the movie was found. If the movie is not found, the function returns -1.
int searchMovieById(Movie movies[], int numMovies, int movieID){
	for(int i=0;i<numMovies;++i){
		if(movies[i].id==movieID)
			return i;
			
	}
	return -1;
	
}


// This functions searches for a movie. If the movie is found all of the information pertaining to the movie is printed.
// If it is not found an appropriate error message is printed.
void option1(Movie movies[], int numMovies, string movieName){
	
	int pos = searchMovieByName(movies, numMovies, movieName);
	if(pos != -1 ){
		printMovieInfo(movies,pos);
		cout<<endl;
	} else {
		cout << "The movie name that you have entered is not valid."<<endl;
	}
	
	
}

//This functions searches for a movie by name and prints the list of all the actors and the roles they played in the movie.
void option2(Movie movies[], int numMovies, string movieName, Actor actors[], int numActors,Cast casts[], int numEntries){
	int pos = searchMovieByName(movies, numMovies, movieName);
	
	bool check=0;
	
	int pos2=0;
	if(pos!=-1){
		for(int i=0;i<numEntries;++i){
			if(movies[pos].id==casts[i].mID){
				pos2=searchActorById(actors, numActors, casts[i].aID);
					if(pos2!=-1){
						cout<<"Actor Name: "<< actors[pos2].fName<<" "<< actors[pos2].lName<< "\t\tRole: "<<casts[i].role;
						cout<<endl;
						check=1;
					}
					
			}
		}
	}
	
	if(pos==-1)
		cout<<"You have entered an invalid movie name."<<endl;
	else if(check==0)
		cout<<"The Movie was not found in the Cast File."<<endl;
	
	
	
}

// This functions searches for an actor by name. If the actor is found all of the information pertaining to the actor is printed.
// If it is not found an appropriate error message is printed.
void option3 (Actor actors[], int numActors, string fName, string lName){
	int pos = searchActorByName(actors, numActors, fName, lName);
	if(pos != -1 ){
		printActorsInfo(actors,pos);
		cout<<endl;
	} else {
		cout << "The actor name that you have entered is not valid."<<endl;
	}
}

//This functions searches for an actor's name and list the name of the movie (s) and roles(s) played in the movie of all the movies the actor has acted
//in if the actor exists. If the actor exists but has not acted in any of the listed movies, display "Actor has not acted in any movie."
//If the actor does not exist, display an appropriate message.
void option4(Movie movies[], int numMovies, Actor actors[], int numActors,Cast casts[], int numEntries, string fName, string lName){
	int posA = searchActorByName(actors, numActors, fName, lName);
	bool check=0;
	if(posA!=-1){
		for(int i=0;i<numEntries;i++){
			if(actors[posA].id==casts[i].aID){
				int posM=searchMovieById(movies, numMovies, casts[i].mID);
				if(posM!=-1){
						cout<<"Name of Movie: "<<movies[posM].name<<"\tRoles played: "<<casts[i].role;
						check=1;
						cout<<endl;
				}
			}
		}		
	}
	
	
	if(posA==-1)
		cout<<fName<<" "<<lName<<" does not exist in the actors file"<<endl;
	else if(check==0)
		cout<<"Actor has not acted in any movie."<<endl;
	
	
}

//For option 5

bool isLeapYear(int year){
	if (((year%4==0)&&(year%100!=0))||(year%400==0))
		return true;
return false;
}

bool isValid(Date d){
	if(d.year>0 && d.month>=1 && d.month<=12 && d.day>=1){
		
		if((d.month==9||d.month==4||d.month==6||d.month==11)&&d.day<=30)	
				return true;
		
		else if((d.month==1||d.month==3||d.month==5||d.month==7||d.month==8||d.month==10||d.month==12) && d.day<=31)
				return true;
					
		else if ((isLeapYear(d.year)&&(d.day<=29))||((!isLeapYear(d.year))&& (d.day<=28)))
				return true;
				
		return false;
		
	}
	return false;
}



Date prevMonth (Date d){
	Date prevD;
	prevD.day=d.day, prevD.month=d.month, prevD.year=d.year;
	// Roll back due to Year
	if(d.month==1){
		prevD.month=12;
		prevD.year-=1;	
	} else {
		prevD.month-=1;
	}
	//Adjust days due to Roll back for February and Days with 30 days.
	
	if(prevD.month==2){
		if(isLeapYear(prevD.year) && prevD.day>29){
			prevD.day=29;
		} 
		else if (prevD.day>28){
			prevD.day=28;
		}
	}
	
	else if ((prevD.month==9 || prevD.month==4 || prevD.month==6 || prevD.month==11) && prevD.day>30)	
		prevD.day=30;
	
	return prevD;
	
}

//This function searches for and prints the names of all movies released within the last month.
void option5(Movie movies[], int numMovies){
	Date d = getCurrentDate();
	Date prevD=prevMonth(d);
		bool check=0;
		for(int i=0;i<numMovies;i++){
			if(isValid(movies[i].releaseDt))
			{
				if((movies[i].releaseDt.year==d.year && movies[i].releaseDt.month==d.month && movies[i].releaseDt.day<=d.day) || (movies[i].releaseDt.year==prevD.year && movies[i].releaseDt.month==prevD.month && movies[i].releaseDt.day>=prevD.day) )
					cout<<"Name of movie: "<<movies[i].name<<"\t\tRelease Date: "<<movies[i].releaseDt.day<<"/"<<movies[i].releaseDt.month<<"/"<<movies[i].releaseDt.year;
					cout<<endl;
					check=1;
			}
			
		}
		if(check==0)
			cout << "No movie was released within the last month."<<endl;

	
	
	
}


//This function searches for and prints the  name(s) of the movies and the release date of all the movies that have not been released yet.
void option6(Movie movies[], int numMovies){
	Date d = getCurrentDate();
	bool check=0;
	for(int i=0;i<numMovies;i++){
		if((movies[i].releaseDt.year>d.year) || (movies[i].releaseDt.year==d.year && movies[i].releaseDt.month>d.month) || (movies[i].releaseDt.year==d.year && movies[i].releaseDt.month==d.month && movies[i].releaseDt.day>d.day) ) {
			cout<<"Name of Movie: "<<movies[i].name <<"\t\tRelease Date: "<<movies[i].releaseDt.day<<"/"<<movies[i].releaseDt.month<<"/"<<movies[i].releaseDt.year;
			cout<<endl;
			check=1;
		}
	}	
	if(check==0)
		cout << "All the movies in the file have already been released."<<endl;
	
}


//This function searches for and prints the names of all movies with a star rating of 8.0 or more that have grossed over 1 billion dollars.
void option7(Movie movies[], int numMovies){
	bool check=0;
	cout<<"\t\t\t\tTop Rated Movies"<<endl;
	cout<<"\t\t\t\t================"<<endl;
	for(int i=0;i<numMovies;++i){
		if (movies[i].starRating>=8.0 && movies[i].g2d>1000000000)
			cout << "Name of Movie: "<< movies[i].name<< "\t\tStar Rating: " <<movies[i].starRating;
			check=1;
			cout<<endl;
		
	}
	
	if(check==0)
	cout << "There is no Top-Rated Movie in the file."<<endl;
	
}

int main(){
	Actor actors[100];
	Movie movies[100];
	Cast casts[10000];
	
	int numActors=0, numMovies=0, numEntries=0;
	
	numActors=loadActors(actors);
	numMovies=loadMovies(movies);
	numEntries=loadCast(casts);
	
	string mName="", fName="", lName="";
	
	int choice=0;
	
	printMenu();
	cin >> choice;
	if(choice==8)
		cout<<endl<< "\t\t\t\t\tProgram Exiting..."<<endl;
	
	while(choice!=8){
		
		// so that menu comes back on the screen
		
		while(choice<1 || choice>8){
			cout<<"Invalid choice.";
			printMenu();
			cin >> choice;
		}
		
		if(choice==1){
			cout << "Please enter Movie Name: ";
			cin >>mName;
			option1(movies, numMovies, mName);
			cout<<endl;
		}
		else if(choice==2) {
			cout << "Please enter Movie Name: ";
			cin >>mName;
			option2(movies, numMovies, mName, actors, numActors, casts, numEntries);
			cout<<endl;
		}
		else if(choice==3) {
			cout << "Please enter Actor's First Name and Last Name: ";
			cin >>fName>>lName;
			option3(actors, numActors, fName, lName);
			cout<<endl;
		}
		else if(choice==4){
			cout << "Please enter Actor's First Name and Last Name: ";
			cin>> fName>>lName;
			option4(movies, numMovies, actors, numActors, casts, numEntries, fName, lName);
			cout<<endl;
		}
		else if(choice==5){
			option5(movies, numMovies);
			cout<<endl;
		}
		else if(choice==6){
			option6(movies, numMovies);
			cout<<endl;
		}
		else if(choice==7){
			option7(movies, numMovies);
			cout<<endl;
			
		}
		else if(choice==8){
			cout<<endl<< "\t\t\t\t\tProgram Exiting..."<<endl;
			break;
		}
			
			
		printMenu();
		cin >> choice;
	
		if(choice==8)
			cout<<endl<< "\t\t\t\t\tProgram Exiting..."<<endl;

		
	}
	
	
	return 0;
}
