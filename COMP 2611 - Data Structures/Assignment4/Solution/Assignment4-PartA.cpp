#include<iostream>
#include<fstream>

#define MaxUsers 100

using namespace std;


int main(){
	void mainMenu(int, string[],bool[]);
	int readFriendsFile(char fileName[],string users[],bool A[]);
	string users[MaxUsers];
	bool A[MaxUsers*(MaxUsers-1)/2+1];
	int numUsers;
	
	char fileName[]="friends.txt";	
	numUsers=readFriendsFile(fileName,users,A);	
	mainMenu(numUsers,users,A);
	
	return 0;
}



void mainMenu(int numUsers, string users[],bool A[]){
	void displayFriendsMatrix(string[],bool[],int);
	int getUser(string [],string, int);
	int getNumFriends(bool [],int, int );
	void displayFriends (bool [],string [],int, int);	
	bool isFriend(bool [],int, int, int );
	bool deFriend(bool [], int, int, int);
	bool paradox(bool A[],int numUsers, int i);
	
	char c;
	int option;
	cout<<"Assignment 4: Working with Matrices"<<endl;
	cout<<"-----------------------------------------------"<<endl<<endl;
	cout<<"1. Display the Friends Matrix"<<endl;
	cout<<"2. How Many Friends Does User A Have?"<<endl;
	cout<<"3. List the Friends of User A"<<endl;
	cout<<"4. Is User B a Friend of User A?"<<endl;
	cout<<"5. Defriend User A and User B"<<endl;
	cout<<"6. Does the Friendship Paradox Hold for User A?"<<endl;
	cout<<"7. Quit"<<endl<<endl;
	cout<<"Please enter an option: ";
	cin>>option;
	cout<<endl<<endl;
	
	string userA, userB;
	int indexA, indexB;
	while(option!=7){
		
		if(option==1){
			displayFriendsMatrix(users,A,numUsers);	
		}
		else if(option==2){
			cout<<"Please enter a User: ";
			cin>>userA;
			indexA=getUser(users,userA,numUsers);
			cout<<endl;
			if(indexA>0){
				int n=getNumFriends(A,numUsers,indexA);
				cout<<userA<<" has "<<n<<" friend";
				if(n>1)
					cout<<"s.\n";
				else
					cout<<".\n";
			} else{
				cout<<userA<<" is not a valid user name."<<endl;
			}
		}
		else if(option==3){
			cout<<"Please enter a User: ";
			cin>>userA;
			indexA=getUser(users,userA,numUsers);
			cout<<endl;
			if(indexA>0){
				displayFriends(A,users,numUsers,indexA);
			} else{
				cout<<userA<<" is not a valid user name."<<endl;
			}
		}
		else if(option==4){
			cout<<"Please enter a User B: ";
			cin>>userB;
			cout<<"Please enter a User A: ";
			cin>>userA;
			indexA=getUser(users,userA,numUsers);
			indexB=getUser(users,userB,numUsers);
			cout<<endl;
			if(indexA>0 && indexB>0){
				if(isFriend(A,numUsers,indexA,indexB))
					cout<<"Yes.\n";
				else
					cout<<"No.\n";
			} else {
				cout<<userA<<" and/or "<<userB<<" is not a valid user name."<<endl;
			}
		}
		else if(option==5){
			cout<<"Please enter a User B: ";
			cin>>userB;
			cout<<"Please enter a User A: ";
			cin>>userA;
			indexA=getUser(users,userA,numUsers);
			indexB=getUser(users,userB,numUsers);
			cout<<endl;
			if(indexA>0 && indexB>0){
				if(deFriend(A,numUsers,indexA,indexB))
					cout<<userA<<" and "<< userB<<" are no longer friends.\n";
				else
					cout<<userA<<" and "<<userB<<" are not friends, so can not defriend users.\n";
			} else {
				cout<<userA<<" and/or "<<userB<<" is not a valid user name."<<endl;
			}
		}
		else if(option==6){
			
			cout<<"Please enter a User: ";
			cin>>userA;
			indexA=getUser(users,userA,numUsers);
			cout<<endl;
			if(indexA>0){
				if(paradox(A,numUsers,indexA))
					cout<<"Yes\n";
				else
					cout<<"No\n";
			} else{
				cout<<userA<<" is not a valid user name."<<endl;
			}
		}
		else{
			cout<<"Invalid option chosen."<<endl;
		}
				
		
		cout<<endl<<endl;
		cout<<"Assignment 4: Working with Matrices"<<endl;
		cout<<"-----------------------------------------------"<<endl<<endl;
		cout<<"1. Display the Friends Matrix"<<endl;
		cout<<"2. How Many Friends Does User A Have?"<<endl;
		cout<<"3. List the Friends of User A"<<endl;
		cout<<"4. Is User B a Friend of User A?"<<endl;
		cout<<"5. Defriend User A and User B"<<endl;
		cout<<"6. Does the Friendship Paradox Hold for User A?"<<endl;
		cout<<"7. Quit"<<endl<<endl;
		cout<<"Please enter an option: ";
		cin>>option;
		cout<<endl<<endl;		
	}
	
	
	
}

int getUser(string users[],string user, int numUsers){
	
	for(int i=1;i<=numUsers;i++)
		if(users[i]==user)
			return i;
			
	return -1;	
}

bool isFriend(bool A[],int numUsers, int i, int j){
	
	if(i<1 || j<1 || i>numUsers || j>numUsers)
		return false;

	if(i==j)
		return false;
	else
	if(i>j)
		return A[(i-1)*(i-2)/2+j];
	else
		return A[(j-1)*(j-2)/2+i];
}

void setFriend(bool A[], int i, int j, bool value){
	if(i!=j){
		if(i>j)
			A[(i-1)*(i-2)/2+j]=value;
		else
			A[(j-1)*(j-2)/2+i]=value;
		
	}

}

int getNumFriends(bool A[],int numUsers, int i){
	int count=0;
	for(int j=1;j<=numUsers;j++)
		if(isFriend(A,numUsers,i,j))
			count++;
	
	return count;
	
}

void displayFriends (bool A[],string users[],int numUsers, int i){
	int numFriends=getNumFriends(A,numUsers,i);
	if(numFriends>0){
		if(numFriends>1)
			cout<<"The friends of "<<users[i]<<" are: ";
		else 
			cout<<"The only friend of "<<users[i]<<" is: ";
			
		int count=0;
		for(int j=1;j<=numUsers;j++)
			if(isFriend(A,numUsers,i,j)){
					count++;
					if(count!=1)
						cout<<", ";
					cout<<users[j];
				}

				
		cout<<"."<<endl;
	}else {
		cout<<i<<" has no friends."<<endl;
	}
}

bool paradox(bool A[],int numUsers, int i){
	int totFriends=0;
	int avgFriends;
	int myFriends;
	

	for(int j=1;j<=numUsers;j++){
		if (isFriend(A,numUsers,j,i)){
			totFriends+=getNumFriends(A,numUsers,j);
		}
	}
	
	myFriends=getNumFriends(A,numUsers,i);
	
	if(myFriends==0)     //fail safe function necessary so that avg Friends
		return false;	// does not divide by 0 if 'i' has no friend.
	
	avgFriends=totFriends/myFriends;

	
	if(myFriends<avgFriends)
		return true;
	return false;
}

int readFriendsFile(char fileName[],string users[],bool A[]){
	void displayFriendsMatrix(string[], bool[], int);
	ifstream fin(fileName);
	if(!fin.is_open()){
		cout<<"File could not be opened."<<endl;
		return -1;
	}
	
	int num;
	fin>>num; 

	
	for(int i=1;i<=num;i++) fin>>users[i];
	
	bool val;
	fin>>boolalpha;
	for(int i=1;i<=num;i++){
		for(int j=1;j<=num;j++){
			fin>>val;
			setFriend(A,i,j,val);
		}
	}

	fin.close();
	return num;
}

void displayFriendsMatrix(string users[],bool A[],int numUsers){
	
	for(int i=1;i<=numUsers;i++){
		cout<<"\t"<<users[i];
	}
	cout<<endl;
	cout<<boolalpha;
	for(int i=1;i<=numUsers;i++){
		cout<<users[i]<<"\t";
		for(int j=1;j<=numUsers;j++){
			cout<<isFriend(A,numUsers,i,j)<<"\t";
		}
		cout<<endl;		
	} 
	
	cout<<endl;
}

bool deFriend(bool A[], int numUsers, int i, int j){
	if(isFriend(A,numUsers,i,j)){
		setFriend(A,i,j,false);	
		return true;
	} 	
	return false;
}
