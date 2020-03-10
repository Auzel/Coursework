#include<iostream>
#include<fstream>

#define MaxUsers 100

using namespace std;

struct Friend{
	int column;
	Friend* next;
		
};

int main(){
	void mainMenu(int, string[],Friend*[]);
	int readFriendsFile(char fileName[],string users[],Friend* A[]);
	string users[MaxUsers];
	Friend* A[MaxUsers+1];
	int numUsers;
	
	
	char fileName[]="friends.txt";	
	numUsers=readFriendsFile(fileName,users,A);	
	mainMenu(numUsers,users,A);
	
	return 0;
}



void mainMenu(int numUsers, string users[],Friend* A[]){
	void displayFriendsMatrix(string[],Friend*[],int);
	int getUser(string [],string, int);
	int getNumFriends(Friend* [],int, int);
	void displayFriends (Friend* [],string [],int, int);	
	bool isFriend(Friend* A[],int, int, int );
	bool deFriend(Friend* A[], int, int, int);
	bool paradox(Friend* A[],int numUsers, int i);
	
	
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

Friend* createFriend(int column){
	Friend* f=new Friend;
	f->column=column;
	f->next=NULL;
	return f;
}

int getUser(string users[],string user, int numUsers){
	for(int i=1;i<=numUsers;i++)
		if(users[i]==user)
			return i;
			
	return -1;	
	
}

bool isFriend(Friend* A[], int numUsers, int i, int j){
	
	if(i<1 || j<1 || i>numUsers || j>numUsers)
		return false;
	
	Friend* f=A[i];

	while(f){
		if(f->column==j)
			return true;
		f=f->next;
	} 
	return false;	

}

void setFriend(Friend* A[],int i, int j, bool value){
	if(value==true){
		Friend* nf=createFriend(j);
		nf->next=A[i];
		A[i]=nf;
	}
}

int getNumFriends(Friend* A[], int numUsers, int i){
	Friend* f=A[i];
	int count=0;
	while(f){
		count++;
		f=f->next;	
	}
	return count;
}

void displayFriends(Friend* A[], string users[], int numUsers, int i){
	Friend* f=A[i];
	int numFriends=getNumFriends(A,numUsers,i);
	if(numFriends>0){
		if(numFriends>1)
			cout<<"The friends of "<<users[i]<<" are: ";
		else 
			cout<<"The only friend of "<<users[i]<<" is: ";
			
		while(f){
			cout<<users[f->column];
			if(f->next!=NULL)
				cout<<", ";
			f=f->next;
		}
		cout<<"."<<endl;
	} else {
		cout<<i <<" has no friends."<<endl;
	}
	
}

bool paradox(Friend* A[], int numUsers, int i){
	int totFriends=0;
	int avgFriends;
	int myFriends;
	

	for(int j=1;j<=numUsers;j++){
		if (isFriend(A,numUsers,i,j)){
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

int readFriendsFile(char fileName[],string users[],Friend* A[]){
	ifstream fin(fileName);
	if(!fin.is_open()){
		cout<<"File could not be opened."<<endl;
		return -1;
	}
	
	int num;
	fin>>num; 
	
	for(int i=1;i<=num;i++){
		fin>>users[i];
		A[i]=NULL;	
	} 
	
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

void displayFriendsMatrix(string users[], Friend* A[], int numUsers){
	
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

bool deFriend(Friend* A[], int numUsers, int i, int j){
	bool del=false;
	if(isFriend(A,numUsers,i,j)){
		for(int k=1;k<=2;k++){
			Friend* f=A[i];
			Friend* p;
			while(f){
				if(f->column==j){
					if(A[i]==f)
						A[i]=f->next;
					else
						p->next=f->next;
					delete f;
					del=true;
					break;
				}
				p=f;
				f=f->next;
			}
			int temp=i;
			i=j;
			j=temp;
		}
	} 	
	return del;
}
