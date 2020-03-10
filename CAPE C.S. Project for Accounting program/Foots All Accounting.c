#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <windows.h>
#include <stdlib.h>
#include <dos.h>
#define DIVISOR 100
#define COMPANY	"Foot's All Accounting System"

//				Foot's All Accounting System
/*	A program to accept data pertaining to the business' transactions of three users. 
   The program then calculates and prints out information in the form of journals,
   cashbook and t-accounts which are much easier to analyze.*/

struct login
{
	char username[10];
	char password[10];
};
struct transaction
{
	char	date[30];
	int		type_of_transaction;
	int 	specific_transaction;
	char	item_name[20];
	int		quantity;
	char 	source[20];
	float	unit_price;
	char	credit_or_cash[20];
	float	discount_percent;
	float	price;
};
struct BasicCreditJournalInfo
{
	char	date[30];
	char	source[20];
	float	price;
};
struct GeneralJournalInfo
{
	char	date[30];
	char	credit_particulars[20];
	char	debit_particulars[20];
	float 	price;
};
struct CashBookInfo 
{
	char	date[30];
	char	item_name[20];
	float	discount_value;
	float	price;
	int		credit_or_debit;
};
struct double_entry
{
	char	date[30];
	char	item_name[20];
	char	source[20];
	float	price;
	int		credit_or_debit;	
	int 	type_of_transaction;
};
struct Creditor_Debtor
{
	struct	double_entry Creditor_Debtor_Transactions[100];
	char	name_of_Creditor_Debtor[20];
};
struct Cred_Debt_Computing
{
	int 	Cred_Debt_count_cred;
	int		Cred_Debt_count_deb;
	int		num_of_Cred_Debt_Ac;
	float	sum_of_debit_Cred_Debt;
	float	sum_of_credit_Cred_Debt;
	float	sum_of_Cred_Debt ;
	float	balance_of_Cred_Debt;
	int 	Cred_Debt_highest;	
}; 

//Defines gotoxy() for ANSI C compilers
//Changes cursor to any position on the screen
void gotoxy(short x, short y) 
{
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
} 

//declaration of struct for login details
struct login Users[3], Login;

//declaration of structs 
//declaration of variables with transaction, journal and cashbook datatype	
struct transaction transactions[100];
struct BasicCreditJournalInfo PurchasesJournal[100], SalesJournal[100], ReturnsInwardsJournal[100], ReturnsOutwardsJournal[100];
struct GeneralJournalInfo GeneralJournal[100];
struct CashBookInfo CashBook[100];

//declaration of variables with T_accounts
struct double_entry	Purchases_Ac[100], Sales_Ac[100], Returns_Inwards_Ac[100], Returns_Outwards_Ac[100];
struct Cred_Debt_Computing Creditors_Debtors_Compute[100];
struct Creditor_Debtor Creditors_Debtors_Ac[100];

//Menu
void Main_Menu(); void Load_BusinessAcc_Screen(); void Save_BusinessAcc_Screen(int save_as); void Welcome_Screen();
int Login_Screen(); void rectangle(int x,int y,int l,int b);void rectangle2(int x,int y,int l,int b); void _password(char buffer[]);

//Function for file
void Read_Login(); void Save_Transactions(struct transaction T[],char file_name[]); int Read_Transactions(struct transaction T[],char file_name[]); void fin_statement();

//Elementary functions for program
void Inputting_Transactions(); void Compute_Journals_and_CashBook(); void Compute_t_account ();

//declaration & initialization for the elementary program
int	i_counter,x=0,y = 0, compare_attempt;
float	discount[100]; char attempt[5];

//Calculations functions for Journals
void Add_to_Purchases_Journal (int TransactionIndex); void Add_to_Sales_Journal (int TransactionIndex); void Add_to_Returns_Inwards_Journal (int TransactionIndex);
void Add_to_Returns_Outwards_Journal (int TransactionIndex); void Add_to_General_Journal (int TransactionIndex); void Add_to_CashBook (int TransactionIndex);

//Calculations functions for T-accounts
void Add_To_Basic_T_Acc (int TransactionIndex, int *count_cred, int *count_deb, int *num, struct double_entry T_accounts[],float *sum_of_deb, float *sum_of_Cred_Debt , float *sum_of_account, float *bal, int *max );
void Add_To_Deb_or_Cred_T_Acc (int TransactionIndex, struct Cred_Debt_Computing Creditors_Debtors_Compute[], struct Creditor_Debtor Creditors[]);

//Printing of Journals
void Print_CreditJournal (int num_limit,struct BasicCreditJournalInfo Journal_type[],float total_of_Journal, int Credit_Journal_Type);
void Print_ReturnsInwardsJournal(); void Print_ReturnsOutwardsJournal(); void Print_CashBook(); void Print_PurchasesJournal(); void Print_SalesJournal(); void Print_GeneralJournal();

//Printing of t-accouts
void Print_Basic_T_Acc (int Ac_index, int *highest, struct double_entry T_accounts[],float *sum_of_deb, float *sum_of_Cred_Debt , float *sum_of_account, float *bal, int *num);
void Print_Deb_or_Cred_T_Acc(int *b_counter, struct Cred_Debt_Computing Creditors_Debtors_Compute[], struct Creditor_Debtor Creditors[]);

//declaration & initialization of transactions and Journals				 
int num_of_transactions=0, num_of_login_users=0, num_of_PurchasesJournal=0, num_of_SalesJournal=0, num_of_ReturnsInwardsJournal=0, num_of_ReturnsOutwardsJournal=0, num_of_CashBook=0, num_of_GeneralJournal=0, cash_count_cred=0, cash_count_deb=0, Basic_Journal_Type=0;
float total_of_ReturnsInwardsJournal=0, total_of_ReturnsOutwardsJournal=0, total_of_PurchasesJournal=0, total_of_SalesJournal=0, total_of_GeneralJournal = 0;	

//declaration & initialization of Cashbook
int 	highest=0; 
float	sum_of_debit_CashBook=0, sum_of_credit_CashBook=0, sum_of_CashBook_entries=0, balance_of_CashBook =0;

//declaration & initialization of Purchases T_account
int 	Purchases_count_cred=0, num_of_Purchases_Ac=0, Purchases_count_deb=0, Purchases_highest =0;
float	sum_of_debit_Purchases=0, sum_of_credit_Purchases=0, sum_of_Purchases=0, balance_of_Purchases =0;

//delcaration & initialization of Sales T_account
int 	Sales_count_cred=0, Sales_count_deb=0, num_of_Sales_Ac=0, Sales_highest = 0;
float	sum_of_debit_Sales=0, sum_of_credit_Sales=0, sum_of_Sales=0, balance_of_Sales =0;

//delcaration & initialization of Returns Inwards T_account
int 	Returns_Inwards_count_cred=0, Returns_Inwards_count_deb=0, num_of_Returns_Inwards_Ac=0, Returns_Inwards_highest = 0;
float	sum_of_debit_Returns_Inwards=0, sum_of_credit_Returns_Inwards=0, sum_of_Returns_Inwards=0, balance_of_Returns_Inwards =0;

//delcaration & initialization of Returns Outwards T_account
int 	Returns_Outwards_count_cred=0, Returns_Outwards_count_deb=0,ac_no=0, num_of_Returns_Outwards_Ac=0, sum_of_credit_GJournal=0,sum_of_debit_GJournal=0, Returns_Outwards_highest=0;
float	sum_of_debit_Returns_Outwards, sum_of_credit_Returns_Outwards, sum_of_Returns_Outwards, balance_of_Returns_Outwards =0;
char 	current_file[30], temp[20];

int main()
{	
	int i_counter=0;
	int access_granted = 0;	
	Welcome_Screen();
	
	//Login
	access_granted = Login_Screen();
		
	//if access is granted
	if (access_granted)
	{
		Load_BusinessAcc_Screen();
		Main_Menu();
		fin_statement();
	}else
	{
		system("cls");
		rectangle(0,0,80,23);
		x=10;	y=11;
		gotoxy(x,y);
		printf("You have exhausted your login attempts. Program quitting...\n");
		sleep(3);
		x=10; y=19;
		gotoxy(x,y);
	}
	return 0;	
}

void Inputting_Transactions()
{
	while (num_of_transactions!=-1)
		{
			num_of_transactions+=1;
			x=19;	y=1;
			gotoxy(x,y);		
			printf("Foot's All Accounting System");
			x+=-18;	y+=3;		
			gotoxy(x, y);																			               
			printf("Enter date of the transaction ");
					y+=1;
			gotoxy(x, y);
			scanf(" %[^\t\n]s", transactions[num_of_transactions-1].date);
					y+=3;			
			gotoxy(x, y);
			printf("Enter your transaction type \n 1 - Purchase \t 2 - Sale \t  3 - Returns Inwards \t 4 - Returns Outwards ");
			transactions[num_of_transactions-1].type_of_transaction=-1;
			
			//loop until input is valid
			while (transactions[num_of_transactions-1].type_of_transaction!=(atoi(temp)))
			{
				x= 1; y+=2;
				gotoxy(x, y);				
				scanf("%s",temp);
				//atoi converts string to decimal
				if (((atoi(temp)) ==1) || ((atoi(temp))==2) || ((atoi(temp))==3) || ((atoi(temp))==4))
				{
		 			 transactions[num_of_transactions-1].type_of_transaction=(atoi(temp));
				}
					else 
				{
					y+=2;
					gotoxy(x, y);
		  			printf(" Invalid input !");
		  			y+=1;
		  			gotoxy(x, y);
		  			printf(" Please input a number");
		  			Sleep (2000);
		  			x=1;
		  			gotoxy(x, y);
		  			printf("                                                   ");
		  			x=1;	y-=1;
		  			gotoxy(x, y);
		  			printf("                                                   ");
		  			x=1;	y-=1;
		  			gotoxy(x, y);
		  			printf("                                                   "); 
		  			x=1;	y-=1;
		  			gotoxy(x, y);
		  			printf("                                                   ");
		  			x=1; y-=2;
		  			gotoxy(x, y);
				}
			}		
			x=1;		y+=3;
			gotoxy(x, y);
			
			// If Transaction is Purchases			
			if (transactions[num_of_transactions-1].type_of_transaction == 1)
			{
				printf("1 - Purchase of goods intended for resale \t 2 - Purchase of Fixed Asset \t 3 - Payment of expenses ");
				transactions[num_of_transactions-1].specific_transaction = -1;
				
				//loop until input is valid     //atio converts string to integer
				while (transactions[num_of_transactions-1].specific_transaction!=(atoi(temp)))
				{	
					x= 1; y+=2;
					gotoxy(x, y);				
					scanf("%s",temp);
					//atoi converts string to decimal
					if (((atoi(temp)) ==1) || ((atoi(temp))==2) || ((atoi(temp))==3) || ((atoi(temp))==4))
					{
			 			 transactions[num_of_transactions-1].specific_transaction=(atoi(temp));
					}
						else 
					{
							y+=2;
							gotoxy(x, y);
			  				printf(" Invalid input !");
			  				y+=1;
			  				gotoxy(x, y);
			  				printf(" Please input a number");
			  				Sleep (2000);
			  				x=1;
			  				gotoxy(x, y);
			  				printf("                                                   ");
			  				x=1;	y-=1;
			  				gotoxy(x, y);
			  				printf("                                                   ");
			  				x=1;	y-=1;
			  				gotoxy(x, y);
			  				printf("                                                   "); 
			  				x=1;	y-=1;
			  				gotoxy(x, y);
			  				printf("                                                   ");
			  				x=1; y-=2;
			  				gotoxy(x, y);
					}
				}		
				y+=3;
				gotoxy(x,y);
			}
			
			// If Transaction is Sales
			else if (transactions[num_of_transactions-1].type_of_transaction == 2)	
			{
				printf("1 - Sale of goods that were intended for resale \t 2 - Sale of Fixed Asset 3 - Accounts Received ");
				
				transactions[num_of_transactions-1].specific_transaction = -1;
				//loop until input is valid     //atio converts string to integer
				while (transactions[num_of_transactions-1].specific_transaction!=(atoi(temp)))
				{	
					x= 1; y+=2;
					gotoxy(x, y);				
					scanf("%s",temp);
					//atoi converts string to decimal
					if (((atoi(temp)) ==1) || ((atoi(temp))==2) || ((atoi(temp))==3) || ((atoi(temp))==4))
					{
			 			 transactions[num_of_transactions-1].specific_transaction=(atoi(temp));
					}
						else 
					{
							y+=2;
							gotoxy(x, y);
			  				printf(" Invalid input !");
			  				y+=1;
			  				gotoxy(x, y);
			  				printf(" Please input a number");
			  				Sleep (2000);
			  				x=1;
			  				gotoxy(x, y);
			  				printf("                                                   ");
			  				x=1;	y-=1;
			  				gotoxy(x, y);
			  				printf("                                                   ");
			  				x=1;	y-=1;
			  				gotoxy(x, y);
			  				printf("                                                   "); 
			  				x=1;	y-=1;
			  				gotoxy(x, y);
			  				printf("                                                   ");
			  				x=1; y-=2;
			  				gotoxy(x, y);
					}
				}		
				y+=3;
				gotoxy(x, y);
			}						
			printf("Enter the name of the item ");
				y+=1;
			gotoxy(x, y);				
			scanf(" %[^\t\n]s", transactions[num_of_transactions-1].item_name);
				y+=3;
			gotoxy(x, y);
			
			// If Transaction is Payment of Expenses or Receivables
			if (transactions[num_of_transactions-1].specific_transaction == 3)	
			{	
				printf("Enter the price of the expense ");
					y+=1;
				gotoxy(x, y);
				scanf("%f", &transactions[num_of_transactions-1].price);
					y+=3;
				gotoxy(x, y);
			}	else
			
			// If Transaction is NOT (Payment of Expense or Receivables)
			{
				printf("Enter the quantity of the product ");
					y+=1;
				gotoxy(x, y);
				scanf("%d", &transactions[num_of_transactions-1].quantity);
					y+=3;
				gotoxy(x, y);	
				printf("Enter the unit price of the product  ");
					y+=1;
				gotoxy(x, y);
				scanf("%f", &transactions[num_of_transactions-1].unit_price);
					y+=3;
				gotoxy(x, y);		
		
				switch (transactions[num_of_transactions-1].type_of_transaction)	
				{
					case 3:
							printf("Enter the name of your customer ");
								y+=1;
							gotoxy(x, y);
							scanf(" %[^\t\n]s", transactions[num_of_transactions-1].source);
								y+=3;
							gotoxy(x, y);
							break;
					case 2:
							printf("Enter the name of your customer ");
								y+=1;
							gotoxy(x, y);
							scanf(" %[^\t\n]s", transactions[num_of_transactions-1].source);
								y+=3;
							gotoxy(x, y);
					
							printf("Enter whether the item was sold by credit or cash ");
								y+=1;
							gotoxy(x, y);
							scanf(" %[^\t\n]s", transactions[num_of_transactions-1].credit_or_cash);
								y+=3;
							gotoxy(x, y);					
							break;
					case 4: 
							printf("Enter the name of your supplier ");
								y+=1;
							gotoxy(x, y);
							scanf(" %[^\t\n]s", transactions[num_of_transactions-1].source);
								y+=3;
							gotoxy(x, y);	
							break;
					case 1:	
							printf("Enter the name of your supplier ");
								y+=1;
							gotoxy(x, y);
							scanf(" %[^\t\n]s", transactions[num_of_transactions-1].source);
								y+=3;
							gotoxy(x, y);
										
							printf("Enter whether the item was paid by credit or cash ");
								y+=1;
							gotoxy(x, y);
							scanf(" %[^\t\n]s", transactions[num_of_transactions-1].credit_or_cash);
								y+=3;
							gotoxy(x, y);
							break;
				}														
				printf("Enter any discount as a percentage placed on the product ");
				y+=1;
				gotoxy(x, y);
				scanf("%f", &transactions[num_of_transactions-1].discount_percent);
					y+=3;
				gotoxy(x, y);		
			}
			printf("Would you like to enter another transaction: ");
				y+=1;
			gotoxy(x, y);	
			scanf("%s", attempt);				
			system ( "cls" );
		
			//calculates price if Transaction is NOT (Payment of Wages of Receivables)
			if(transactions[num_of_transactions-1].specific_transaction != 3 )		
			{
				discount[num_of_transactions-1] = (transactions[num_of_transactions-1].discount_percent / DIVISOR ) * (transactions[num_of_transactions-1].unit_price*transactions[num_of_transactions-1].quantity);
				transactions[num_of_transactions-1].price = (( transactions[num_of_transactions-1].unit_price * transactions[num_of_transactions-1].quantity) - discount[num_of_transactions-1]);		
			}	
			compare_attempt = strcmpi(attempt,"no");
			if (compare_attempt == 0)
				break;			
		}
}

void Compute_Journals_and_CashBook()
{
		num_of_PurchasesJournal=0, num_of_SalesJournal = 0,	num_of_ReturnsInwardsJournal = 0; num_of_ReturnsOutwardsJournal = 0; num_of_CashBook = 0;num_of_GeneralJournal =0; 
		Basic_Journal_Type =0; cash_count_cred=0; cash_count_deb=0; total_of_ReturnsInwardsJournal = 0; total_of_ReturnsOutwardsJournal = 0; total_of_PurchasesJournal = 0; 
		total_of_SalesJournal = 0; total_of_GeneralJournal = 0; highest=0; sum_of_debit_CashBook = 0; sum_of_credit_CashBook = 0; sum_of_CashBook_entries = 0; balance_of_CashBook =0;
	
		for (i_counter=0;i_counter<num_of_transactions;i_counter++)
		{
				int compare_credit_or_cash;
				compare_credit_or_cash = strcmpi(transactions[i_counter].credit_or_cash, "cash");
				
				// Checking to see if to use Returns Inwards 
				if (transactions[i_counter].type_of_transaction == 3 ) 
				{					
					 Add_to_Returns_Inwards_Journal (i_counter);					
				}
				// Checking to see if to use Returns Outwards
				else if (transactions[i_counter].type_of_transaction == 4 ) 
				{
					Add_to_Returns_Outwards_Journal (i_counter);
				}	
				//If paid by cash
				else if ((compare_credit_or_cash == 0) || (transactions[i_counter].specific_transaction == 3))
				{						
					Add_to_CashBook (i_counter);
				}
				// Checking to see whether to use Purchases Journal
				else if ((compare_credit_or_cash != 0) && (transactions[i_counter].type_of_transaction == 1) && (transactions[i_counter].specific_transaction ==1 ))
				{
					Add_to_Purchases_Journal (i_counter);
				}
				//Checking to see whether to use General Journal
				else if ((compare_credit_or_cash != 0) && (transactions[i_counter].specific_transaction == 2 ))
				{
					Add_to_General_Journal (i_counter);
				}
				// Checking to see whether to use Sales Journal
				else if ((compare_credit_or_cash != 0) && (transactions[i_counter].type_of_transaction == 2) && (transactions[i_counter].specific_transaction == 1 ))
				{
					Add_to_Sales_Journal (i_counter);
				}		
		}		
		//Printing of Returns Inwards Journal
		if (num_of_ReturnsInwardsJournal !=0)
		{
			Print_ReturnsInwardsJournal () ;
		}
		//Printing of Returns Outwards Journal
		if (num_of_ReturnsOutwardsJournal != 0)
		{
			Print_ReturnsOutwardsJournal () ;	
		}
		// Print of Cashbook
		 if (num_of_CashBook != 0) 
		 {
		 	Print_CashBook ();
		 }
		// Print of Purchases Journal
		if (num_of_PurchasesJournal != 0)
		{
			Print_PurchasesJournal ();
		}	
		// Print of Sales Journal
		if (num_of_SalesJournal != 0)
		{
			Print_SalesJournal ();
		}
		// Print of General Journal
		if (num_of_GeneralJournal != 0)
		{
			Print_GeneralJournal ();
		}
}

void Add_to_Returns_Inwards_Journal (int TransactionIndex)
{
	num_of_ReturnsInwardsJournal+=1;
	strcpy(ReturnsInwardsJournal[num_of_ReturnsInwardsJournal-1].date, transactions[TransactionIndex].date);
	strcpy(ReturnsInwardsJournal[num_of_ReturnsInwardsJournal-1].source, transactions[TransactionIndex].source);
	ReturnsInwardsJournal[num_of_ReturnsInwardsJournal-1].price = transactions[TransactionIndex].price;	
	total_of_ReturnsInwardsJournal+= ReturnsInwardsJournal[num_of_ReturnsInwardsJournal-1].price;
}

void Add_to_Returns_Outwards_Journal (int TransactionIndex)
{
	num_of_ReturnsOutwardsJournal+=1;
	strcpy(ReturnsOutwardsJournal[num_of_ReturnsOutwardsJournal-1].date, transactions[TransactionIndex].date);
	strcpy(ReturnsOutwardsJournal[num_of_ReturnsOutwardsJournal-1].source, transactions[TransactionIndex].source);
	ReturnsOutwardsJournal[num_of_ReturnsOutwardsJournal-1].price = transactions[TransactionIndex].price;
	total_of_ReturnsOutwardsJournal+= ReturnsOutwardsJournal[num_of_ReturnsOutwardsJournal-1].price;		
}

void Add_to_CashBook (int TransactionIndex)
{
	num_of_CashBook+=1;
	strcpy(CashBook[num_of_CashBook-1].date, transactions[TransactionIndex].date);
	strcpy(CashBook[num_of_CashBook-1].item_name, transactions[TransactionIndex].item_name);
	CashBook[num_of_CashBook-1].price = transactions[TransactionIndex].price;
	CashBook[num_of_CashBook-1].discount_value = discount[TransactionIndex];

	//If type of transaction chosen is sales
	if(transactions[i_counter].type_of_transaction == 2)
	{
		//If Cashbook is debit
		cash_count_deb+=1;
		CashBook[num_of_CashBook-1].credit_or_debit = 0;	
		sum_of_debit_CashBook+= transactions[TransactionIndex].price;
	}else
	//If type of transaction chosen is purchases
	if(transactions[i_counter].type_of_transaction == 1)
	{
		//If Cashbook is credit
		cash_count_cred+=1;
		CashBook[num_of_CashBook-1].credit_or_debit = 1;
		sum_of_credit_CashBook+= transactions[TransactionIndex].price;			
	}
	//If the debit side of cashbook is more than the credit side
	if (sum_of_debit_CashBook > sum_of_credit_CashBook)
	{
		sum_of_CashBook_entries = sum_of_debit_CashBook;
		balance_of_CashBook = sum_of_CashBook_entries - sum_of_credit_CashBook;
	}else 
	//if the debit side of cashbook is less than the credit side
	if (sum_of_debit_CashBook < sum_of_credit_CashBook)
	{
		sum_of_CashBook_entries = sum_of_credit_CashBook;	
		balance_of_CashBook = sum_of_CashBook_entries - sum_of_debit_CashBook;
	}else
	// If the debit side of the cashbook is equal to the credit side
	if (sum_of_debit_CashBook == sum_of_credit_CashBook)
	{
		sum_of_CashBook_entries = sum_of_credit_CashBook;	
		balance_of_CashBook = 0;
	}						
	//If the number of credit entries is more than debit entries
	if (cash_count_cred > cash_count_deb)
	{
		highest = cash_count_cred;		
	}else
	{
		highest = cash_count_deb;
	}	
}		   

void Add_to_Sales_Journal (int TransactionIndex)
{
	num_of_SalesJournal+=1;
	strcpy(SalesJournal[num_of_SalesJournal-1].date, transactions[TransactionIndex].date);
	strcpy(SalesJournal[num_of_SalesJournal-1].source, transactions[TransactionIndex].source);
	SalesJournal[num_of_SalesJournal-1].price = transactions[TransactionIndex].price;
	total_of_SalesJournal+= SalesJournal[num_of_SalesJournal-1].price;	
}

void Add_to_Purchases_Journal (int TransactionIndex)
{
	num_of_PurchasesJournal+=1;
	strcpy(PurchasesJournal[num_of_PurchasesJournal-1].date, transactions[TransactionIndex].date);
	strcpy(PurchasesJournal[num_of_PurchasesJournal-1].source, transactions[TransactionIndex].source);
	PurchasesJournal[num_of_PurchasesJournal-1].price = transactions[TransactionIndex].price;
	total_of_PurchasesJournal+= PurchasesJournal[num_of_PurchasesJournal-1].price;	
}

void Add_to_General_Journal (int TransactionIndex)
{
	sum_of_credit_GJournal=0;
	sum_of_debit_GJournal=0;
	num_of_GeneralJournal +=1;
	
	strcpy(GeneralJournal[num_of_GeneralJournal-1].date, transactions[TransactionIndex].date);
	GeneralJournal[num_of_GeneralJournal-1].price = transactions[TransactionIndex].price;
		if(transactions[i_counter].type_of_transaction == 1)
		{
			strcpy(GeneralJournal[num_of_GeneralJournal-1].debit_particulars, transactions[TransactionIndex].item_name);	
			strcpy(GeneralJournal[num_of_GeneralJournal-1].credit_particulars, transactions[TransactionIndex].source);
			sum_of_debit_GJournal = sum_of_credit_GJournal + GeneralJournal[num_of_GeneralJournal-1].price;
		}else
		{
			strcpy(GeneralJournal[num_of_GeneralJournal-1].credit_particulars, transactions[TransactionIndex].item_name);	
			strcpy(GeneralJournal[num_of_GeneralJournal-1].debit_particulars, transactions[TransactionIndex].source);
			sum_of_credit_GJournal = sum_of_credit_GJournal + GeneralJournal[num_of_GeneralJournal-1].price ;
		}
	total_of_GeneralJournal+= GeneralJournal[num_of_GeneralJournal-1].price;
}

void fin_statement()
{
	float sum_of_debit = total_of_ReturnsInwardsJournal + total_of_PurchasesJournal +	sum_of_debit_CashBook + sum_of_debit_GJournal;
	float sum_of_credit = total_of_ReturnsOutwardsJournal  + 	total_of_SalesJournal + sum_of_credit_CashBook + sum_of_credit_GJournal;
	float total_balance = abs (sum_of_credit - sum_of_debit);
	
	FILE *response_pointer;
	response_pointer = fopen("profit_or_loss.txt","w");
	
	//Check whether business made a profit or loss
	if(sum_of_credit> sum_of_debit)
	{
		fprintf(response_pointer," Foot's All made \n A Profit of $%.2f During\n the period\n Under review\n. Hence the\n capital\n has been increased by\n $%.2f",total_balance,total_balance);
	}else
	if(sum_of_debit> sum_of_credit) 
	{
		fprintf(response_pointer," Foot's All made A Loss of $%.2f During the period Under review. Hence the capital has been decreased by $%.2f",total_balance,total_balance);
	}
	else
	if(sum_of_debit == sum_of_credit)
	{
		fprintf(response_pointer," Foot's All made neither a Profit nor a Loss During the period Under review");
	}
	
	fclose(response_pointer);
}

void Print_CreditJournal (int num_limit,struct BasicCreditJournalInfo Journal_type[],float total_of_Journal, int Credit_Journal_Type)
{
	int x=1;
	//horizontal lines
	for (x=1; x<75; x++)
	{
		//Horizontal lines at the top
		gotoxy(x, 10);
		printf("_");
		gotoxy(x, 7);
		printf("_");
		
		//Horizontal line at the bottom (no of entries plus the row starting at and extra rows before close)
		gotoxy(x, num_limit+16);
		printf("_");	
	}
	
	i_counter = 0;
	x=22;	y=1;
	gotoxy(x,y);		
	printf("%s",COMPANY);
			y+=5;
	gotoxy(x+7,y);
	
	if (Credit_Journal_Type == 1)	
	{
		printf("Purchases Journal ");
			
	}else
	if (Credit_Journal_Type == 2)
	{
		printf("Sales Journal ");			
	}else
	if (Credit_Journal_Type == 3)
	{
		printf("Returns Inwards Journal ");
	}else
	if (Credit_Journal_Type == 4)
	{
		printf("Returns Outwards Journal ");	
	}
	
	x= 4; y+=3;
	gotoxy(x,y);
	printf("Date ");
	x+= 25;
	gotoxy(x,y);
	printf("Item");
	x+=25;
	gotoxy(x,y);
	printf("Amount($)");
	x=4; y+=2;
	gotoxy(x,y);
	
	for (i_counter=0; i_counter<num_limit;i_counter++)
	{
		//print entries
		printf("%s",Journal_type[i_counter].date);
		x+=25;
		gotoxy(x,y);
		printf("%s ",Journal_type[i_counter].source);
		x+=25;
		gotoxy(x,y);
		printf("%.2f",Journal_type[i_counter].price);
		x=4;		y+=1;
		gotoxy(x,y);
	}		
		
	if (i_counter==(num_limit))
	{	
		//print total
		x=29; 	y+=2;
		gotoxy(x,y);
		printf("Total");
		x=54;			
		gotoxy(x,y);
		printf("%.2f",total_of_Journal);	
		int y2=y-1; y+=1;	
		
		for (x=50;x<63;x++)
			{
				//bottom line
				gotoxy(x,y);
				printf("_");
				
				//top line
				gotoxy(x,y2);
				printf("_");  
			}
	}
	printf("\n\n\n\n\n\n \t\t\t Press any key to continue");
	getch();
	system ( "cls" );
}

void Print_ReturnsInwardsJournal ()
{
	Basic_Journal_Type = 3;	
	Print_CreditJournal (num_of_ReturnsInwardsJournal,ReturnsInwardsJournal,total_of_ReturnsInwardsJournal, Basic_Journal_Type);
}

void Print_ReturnsOutwardsJournal ()
{
	Basic_Journal_Type = 4;
	Print_CreditJournal (num_of_ReturnsOutwardsJournal,ReturnsOutwardsJournal,total_of_ReturnsOutwardsJournal,Basic_Journal_Type);
}

void Print_CashBook ()
{
	int x=1;
	//horizontal lines
	for (x=0; x<80; x++)
	{
		//Horizontal lines at the top
		gotoxy(x, 10);
		printf("_");
		gotoxy(x, 7);
		printf("_");
		
		//Horizontal line at the bottom (no of entries plus the row starting at and extra rows before close)
		gotoxy(x, highest+20);
		printf("_");
	}
	
	for (y=8; y<=(highest+20);y++)
	{
		//vertical line separation for debit and credit side
		gotoxy(39, y);
		printf("|");
	}
	i_counter = 0;
	x=22;	y=1;
	gotoxy(x,y);		
	printf("%s",COMPANY);
			y+=5;
	gotoxy(x+11,y);	
	printf("Cash Book ");
	x= 0; y+=3;
	gotoxy(x,y);
	printf("Date ");
	x+= 9;
	gotoxy(x,y);
	printf("Item");
	x+= 11;
	gotoxy(x,y);
	printf("Discount");
	x+=10;
	gotoxy(x,y);
	printf("Amount($)");
	x+= 11; 
	gotoxy(x,y);
	printf("Date ");
	x+= 9;
	gotoxy(x,y);
	printf("Item");
	x+= 11;
	gotoxy(x,y);
	printf("Discount");
	x+=10;
	gotoxy(x,y);
	printf("Amount($)");
	
	x=0; y+=2;  int x2 = 41; int y2 = 11;	
	for (i_counter=0; i_counter<num_of_CashBook;i_counter++)
	{
		// print debit entries
		if(CashBook[i_counter].credit_or_debit == 0)
		{	
			gotoxy(x,y);			
			printf("%s",CashBook[i_counter].date);
			x+=9;
			gotoxy(x,y);
			printf("%s ",CashBook[i_counter].item_name);
			x+=11;
			gotoxy(x,y);
			printf("%.2f ",CashBook[i_counter].discount_value);
			x+=10;
			gotoxy(x,y);
			printf("%.2f",CashBook[i_counter].price);
			x=0;		y+=1;
			gotoxy(x,y);
		}else
		if (CashBook[i_counter].credit_or_debit == 1)
		{
			//print credit side of cashbook
			gotoxy(x2,y2);			
			printf("%s",CashBook[i_counter].date);
			x2+=9;
			gotoxy(x2,y2);
			printf("%s ",CashBook[i_counter].item_name);
			x2+=11;
			gotoxy(x2,y2);
			printf("%.2f",CashBook[i_counter].discount_value);
			x2+=10;
			gotoxy(x2,y2);
			printf("%.2f",CashBook[i_counter].price);
			x2=41;		y2+=1;
			gotoxy(x2,y2);				
		}
	}		
	
	//If credit side of Cashbook is more than Debit side
	if (sum_of_credit_CashBook > sum_of_debit_CashBook)	
	{
		y=y2;
		y+=1;
		gotoxy(9, y);
		printf("Balance c/d");
		gotoxy(30, y);
		printf("%.2f",balance_of_CashBook);	
		y2=y;		
	}else
	
	//If credit side of Cashbook is less than Debit side
	if (sum_of_credit_CashBook < sum_of_debit_CashBook)
	{
		y2=y;
		y2+=1;
		gotoxy(41, y2);
		printf("Balance c/d");
		gotoxy(71, y2);
		printf("%.2f",balance_of_CashBook);
		y=y2;		
	}
	y+=2;	y2+=2;
	gotoxy(30,y);
	printf("%.2f", sum_of_CashBook_entries);
	gotoxy(71,y2);
	printf("%.2f", sum_of_CashBook_entries);
	int yy=y-1; y+=1;	
	
	for (x=27;x<38;x++)
	{
		//bottom line
		gotoxy(x,y);
		printf("_");	
		//top line
		gotoxy(x,yy);
		printf("_");  			 
	}	
	int yy2=y2-1; y2+=1;
		
	for (x=68;x<79;x++)
	{
		//bottom line
		gotoxy(x,y2);
		printf("_");	
		//top line
		gotoxy(x,yy2);
		printf("_");  		 
	}	
	y+=2;	y2+=2;	
	
	if (sum_of_credit_CashBook > sum_of_debit_CashBook)
	{
		gotoxy(41, y2);
		printf("Balance b/d");
		gotoxy(71, y2);
		printf("%.2f",balance_of_CashBook);
	}
	else if (sum_of_credit_CashBook < sum_of_debit_CashBook)
	{
		gotoxy(9, y);
		printf("Balance b/d");
		gotoxy(30, y);
		printf("%.2f",balance_of_CashBook);		
	}
	printf("\n\n\n\n\n\n \t\t\t Press any key to continue");
	getch();
	system ( "cls" );  	    
}
	
void Print_PurchasesJournal()
{
	Basic_Journal_Type = 1;	
	Print_CreditJournal (num_of_PurchasesJournal,PurchasesJournal,total_of_PurchasesJournal,Basic_Journal_Type);	
}

void Print_SalesJournal ()
{
	Basic_Journal_Type = 2;	
	Print_CreditJournal (num_of_SalesJournal,SalesJournal,total_of_SalesJournal,Basic_Journal_Type);		
}

void Print_GeneralJournal()
{
	int x=1;
	//horizontal lines
	for (x=1; x<75; x++)
	{
		//Horizontal lines at the top
		gotoxy(x, 10);
		printf("_");
		gotoxy(x, 7);
		printf("_");

		//Horizontal line at the bottom (no of entries plus the row starting at and extra rows before close)
		gotoxy(x, num_of_GeneralJournal+16);
		printf("_");		
	}
	
	i_counter = 0;
	x=22;	y=1;
	gotoxy(x,y);		
	printf("%s",COMPANY);
			y+=5;
	gotoxy(x+7,y);	
	printf("General Journal ");
	x= 4; y+=3;
	gotoxy(x,y);
	printf("Date ");
	x+= 15;
	gotoxy(x,y);
	printf("Item");
	x+=20;
	gotoxy(x,y);
	printf("Debit($)");
	x+=15;
	gotoxy(x,y);
	printf("Credit($)");
	
	for (i_counter=0; i_counter<num_of_GeneralJournal;i_counter++)
	{
		//print entries for purchases
		if(transactions[i_counter].type_of_transaction == 1)
		{			
			x=4; y+=2;
			gotoxy(x,y);
			printf("%s",GeneralJournal[i_counter].date);
			x+=15;
			gotoxy(x,y);
			printf("%s ",GeneralJournal[i_counter].debit_particulars);
			x+=20;
			gotoxy(x,y);
			printf("%.2f",GeneralJournal[i_counter].price);
			x=4; y+=1;
			gotoxy(x,y);
			printf("%s",GeneralJournal[i_counter].date);
			x+=20;
			gotoxy(x,y);
			printf("%s ",GeneralJournal[i_counter].credit_particulars);
			x+=30;
			gotoxy(x,y);
			printf("%.2f",GeneralJournal[i_counter].price);		
		}else
		if (transactions[i_counter].type_of_transaction == 2)
			//Print entries for Sales
		{
			x=4; y+=2;
			gotoxy(x,y);
			printf("%s",GeneralJournal[i_counter].date);
			x+=15;
			gotoxy(x,y);
			printf("%s ",GeneralJournal[i_counter].credit_particulars);	
			x+=35;
			gotoxy(x,y);
			printf("%.2f",GeneralJournal[i_counter].price);	
			x=4; y+=1;
			gotoxy(x,y);
			printf("%s",GeneralJournal[i_counter].date);
			x+=20;
			gotoxy(x,y);
			printf("%s ",GeneralJournal[i_counter].debit_particulars);
			x+=15;
			gotoxy(x,y);
			printf("%.2f",GeneralJournal[i_counter].price);		
		}	
	}		
		
	if (i_counter==(num_of_GeneralJournal))
	{
		//print total
		x=29; 	y+=2;
		gotoxy(x,y);
		printf("Total");
		x=39;			
		gotoxy(x,y);
		printf("%.2f",total_of_GeneralJournal);
		x=54;			
		gotoxy(x,y);
		printf("%.2f",total_of_GeneralJournal);
		int y2=y-1; y+=1;	
		
		for (x=38;x<60;x++)
			{
				//bottom line
				gotoxy(x,y);
				printf("_");
				
				//top line
				gotoxy(x,y2);
				printf("_");  	 
			}		
	}
	printf("\n\n\n\n\n\n \t\t\t Press any key to continue");
	getch();
	system ( "cls" );
}

void Compute_t_account ()
{
	Purchases_count_cred=0, num_of_Purchases_Ac=0, Purchases_count_deb=0, sum_of_debit_Purchases=0, sum_of_credit_Purchases=0, sum_of_Purchases=0, balance_of_Purchases=0, Purchases_highest = 0;
	Sales_count_cred=0, Sales_count_deb=0, num_of_Sales_Ac=0, sum_of_debit_Sales=0, sum_of_credit_Sales=0, sum_of_Sales=0, balance_of_Sales=0, Sales_highest = 0;	
	Returns_Inwards_count_cred=0, Returns_Inwards_count_deb=0, num_of_Returns_Inwards_Ac=0, sum_of_debit_Returns_Inwards=0, sum_of_credit_Returns_Inwards=0, sum_of_Returns_Inwards=0, balance_of_Returns_Inwards=0, Returns_Inwards_highest = 0;
	Returns_Outwards_count_cred=0, Returns_Outwards_count_deb=0, num_of_Returns_Outwards_Ac=0, sum_of_debit_Returns_Outwards=0, sum_of_credit_Returns_Outwards=0, sum_of_Returns_Outwards=0, balance_of_Returns_Outwards=0, Returns_Outwards_highest = 0;
	float   balance_of_Creditors_Ac=0, balance_of_Debtors_Ac=0;
	
	// removed the balance_of_Purchases_Ac and the reset accounts
	int i_counter = 0 ;	
	int b_counter = 0;
	
	//Re-initializes the number of transactions for each creditor to zero
	for (b_counter=0;b_counter<ac_no;b_counter++)
	{	
		Creditors_Debtors_Compute[b_counter].num_of_Cred_Debt_Ac=0;
	}
	ac_no = 0;
	
	while (i_counter<num_of_transactions)	
	{
		//If condition causes it to be Purchases Account
		if((transactions[i_counter].type_of_transaction == 1) && (transactions[i_counter].specific_transaction == 1 ))
		{
			Add_To_Basic_T_Acc (i_counter,&Purchases_count_cred, &Purchases_count_deb, &num_of_Purchases_Ac,Purchases_Ac, &sum_of_debit_Purchases, &sum_of_credit_Purchases,&sum_of_Purchases,&balance_of_Purchases,&Purchases_highest);		
			Add_To_Deb_or_Cred_T_Acc (i_counter,Creditors_Debtors_Compute, Creditors_Debtors_Ac);
		}
		//If condition causes it to be Sales Account
		if((transactions[i_counter].type_of_transaction == 2) && (transactions[i_counter].specific_transaction == 1 )) 
		{
			Add_To_Basic_T_Acc (i_counter,&Sales_count_cred,&Sales_count_deb,&num_of_Sales_Ac,Sales_Ac, &sum_of_debit_Sales, &sum_of_credit_Sales,&sum_of_Sales,&balance_of_Sales,&Sales_highest);
			Add_To_Deb_or_Cred_T_Acc (i_counter,Creditors_Debtors_Compute, Creditors_Debtors_Ac);
		}
		//If condition causes it to be Returns Inwards Account
		if (transactions[i_counter].type_of_transaction == 3)
		{
			Add_To_Basic_T_Acc (i_counter,&Returns_Inwards_count_cred,&Returns_Inwards_count_deb,&num_of_Returns_Inwards_Ac,Returns_Inwards_Ac, &sum_of_debit_Returns_Inwards, &sum_of_credit_Returns_Inwards,&sum_of_Returns_Inwards,&balance_of_Returns_Inwards,&Returns_Inwards_highest);	
			Add_To_Deb_or_Cred_T_Acc (i_counter,Creditors_Debtors_Compute, Creditors_Debtors_Ac);
		}
		//If condition causes it to be Returs Outwards Account
		if (transactions[i_counter].type_of_transaction == 4)
		{
			Add_To_Basic_T_Acc (i_counter,&Returns_Outwards_count_cred,&Returns_Outwards_count_deb,&num_of_Returns_Outwards_Ac,Returns_Outwards_Ac, &sum_of_debit_Returns_Outwards, &sum_of_credit_Returns_Outwards,&sum_of_Returns_Outwards,&balance_of_Returns_Outwards,&Returns_Outwards_highest);	
			Add_To_Deb_or_Cred_T_Acc (i_counter,Creditors_Debtors_Compute, Creditors_Debtors_Ac);
		}
		i_counter++;	
	}
	
	for(i_counter=0;i_counter<ac_no;i_counter++){
		
		if (Creditors_Debtors_Compute[i_counter].balance_of_Cred_Debt<0)
		{
			balance_of_Creditors_Ac+=fabsf(Creditors_Debtors_Compute[i_counter].balance_of_Cred_Debt);
	    	
		} else if (Creditors_Debtors_Compute[i_counter].balance_of_Cred_Debt>0)
		{
			balance_of_Debtors_Ac+=Creditors_Debtors_Compute[i_counter].balance_of_Cred_Debt;
		}			
	}	
	// Printing T- Accounts if it is required by the transactions	
			
	if (num_of_Purchases_Ac > 0)
	{
		Print_Basic_T_Acc (1,&Purchases_highest,Purchases_Ac,&sum_of_debit_Purchases,&sum_of_credit_Purchases,&sum_of_Purchases,&balance_of_Purchases,&num_of_Purchases_Ac);	
	}
	if (num_of_Sales_Ac > 0)		
	{
		Print_Basic_T_Acc (2,&Sales_highest,Sales_Ac,&sum_of_debit_Sales,&sum_of_credit_Sales,&sum_of_Sales,&balance_of_Sales,&num_of_Sales_Ac);
	}	
	if (num_of_Returns_Inwards_Ac > 0)	
	{
		Print_Basic_T_Acc (3,&Returns_Inwards_highest,Returns_Inwards_Ac,&sum_of_debit_Returns_Inwards,&sum_of_credit_Returns_Inwards,&sum_of_Returns_Inwards,&balance_of_Returns_Inwards,&num_of_Returns_Inwards_Ac);
	}	
	if (num_of_Returns_Outwards_Ac > 0)
	{
		Print_Basic_T_Acc (4,&Returns_Outwards_highest,Returns_Outwards_Ac,&sum_of_debit_Returns_Outwards,&sum_of_credit_Returns_Outwards,&sum_of_Returns_Outwards,&balance_of_Returns_Outwards,&num_of_Returns_Outwards_Ac);
	}			 
			
	for (b_counter=0;b_counter<ac_no;b_counter++)
	{	
		if (Creditors_Debtors_Compute[b_counter].num_of_Cred_Debt_Ac>0)
		{
			Print_Deb_or_Cred_T_Acc(&b_counter,Creditors_Debtors_Compute, Creditors_Debtors_Ac);
		}
	} 	
}

void Add_To_Basic_T_Acc (int TransactionIndex, int *count_cred, int *count_deb, int *num, struct double_entry T_accounts[],float *sum_of_deb, float *sum_of_cred, float *sum_of_account, float *bal, int *max )
{
	*num+=1;	
	strcpy(T_accounts[*(num)-1].date, transactions[TransactionIndex].date);
	strcpy(T_accounts[*(num)-1].source, transactions[TransactionIndex].source);
	T_accounts[*(num)-1].price = transactions[TransactionIndex].price;
	
	if(((transactions[TransactionIndex].type_of_transaction == 1) && (transactions[TransactionIndex].specific_transaction == 1 ))  ||  (transactions[TransactionIndex].type_of_transaction == 3))
	{
		//If Purchases a/c is debit
		*count_deb+=1;
		T_accounts[*(num)-1].credit_or_debit = 0;
		*sum_of_deb+= T_accounts[*(num)-1].price;	
	}else 
	if(((transactions[TransactionIndex].type_of_transaction == 2) && (transactions[TransactionIndex].specific_transaction == 1 ))  ||  (transactions[TransactionIndex].type_of_transaction == 4))
	{
		//If Purchases a/c is credit
		*count_cred += 1;
		T_accounts[*(num)-1].credit_or_debit = 1;
		*sum_of_cred+= T_accounts[*(num)-1].price;
	}
	
	//if the debit side of Purchases a/c is more than the credit side
	if(*sum_of_deb > *sum_of_cred)
	{	
		*sum_of_account = *sum_of_deb;
		*bal = *sum_of_account - *sum_of_cred;
	}else
	//if the debit side of Purchases a/c is less than the credit side
	if(*sum_of_deb < *sum_of_cred)
	{
		*sum_of_account = *sum_of_cred;
		*bal = *sum_of_account - *sum_of_deb;
	}else
	//if the debit side of Purchases a/c is equal than the credit side
	if(*sum_of_deb == *sum_of_cred)
	{
		*sum_of_account = *sum_of_cred;
		*bal = 0;
	}
	//If the number of credit entries is more than debit entries
	if (*count_cred >= *count_deb)
	{
		*max = *count_cred;		
	}else 
	if (*count_cred < *count_deb)
	{
		*max = *count_deb;
	}	
}

void	Print_Basic_T_Acc (int Ac_index, int *highest, struct double_entry T_accounts[],float *sum_of_deb, float *sum_of_cred, float *sum_of_account, float *bal, int *num)
{
	int x=1;
	for (x=0; x<80; x++)
	{
		//Horizontal lines at the top
		gotoxy(x, 10);
		printf("_");
		gotoxy(x, 7);
		printf("_");
		
		//Horizontal line at the bottom (no of entries plus the row starting at and extra rows before close)
		gotoxy(x, *(highest)+20);
		printf("_");
	}
	
	for (y=8; y<=(*(highest)+20);y++)
	{
		//vertical line separation for debit and credit side
		gotoxy(39, y);
		printf("|");
	}
	i_counter = 0;
	x=22;	y=1;
	gotoxy(x,y);		
	printf("%s",COMPANY);
			y+=5;
	gotoxy(x+11,y);	
	
	if (Ac_index == 1)
	{
		printf("Purchases a/c ");	
	}else
	if (Ac_index == 2)
	{
		printf("Sales a/c ");
	}else
	if (Ac_index == 3)
	{
		printf("Returns Inwards a/c");
	}else
	if(Ac_index == 4)
	{
		printf("Returns Outwards a/c");
	}

	x= 0; y+=3;
	gotoxy(x,y);
	printf("Date ");
	x+=13;
	gotoxy(x,y);
	printf("Item");
	x+=15;
	gotoxy(x,y);
	printf("Amount($)");
	x+= 13; 
	gotoxy(x,y);
	printf("Date ");
	x+= 13;
	gotoxy(x,y);
	printf("Item");
	x+=15;
	gotoxy(x,y);
	printf("Amount($)");
	x=0; y+=2;  int x2 = 41; int y2 = 11;
		
	for (i_counter=0; i_counter<*num;i_counter++)
	{		
		// print debit entries
		if(T_accounts[i_counter].credit_or_debit == 0)
		{				
			gotoxy(x,y);			
			printf("%s",T_accounts[i_counter].date);
			x+=13;
			gotoxy(x,y);
			printf("%s ",T_accounts[i_counter].source);		
			x+=15;
			gotoxy(x,y);
			printf("%.2f",T_accounts[i_counter].price);
			x=0;		y+=1;
			gotoxy(x,y);
		}else
		if (T_accounts[i_counter].credit_or_debit == 1)
		{
			//print credit side of T_accounts
			gotoxy(x2,y2);			
			printf("%s",T_accounts[i_counter].date);
			x2+=13;
			gotoxy(x2,y2);
			printf("%s ",T_accounts[i_counter].source);
			x2+=15;
			gotoxy(x2,y2);
			printf("%.2f",T_accounts[i_counter].price);
			x2=41;		y2+=1;
			gotoxy(x2,y2);
		}
	}
	//If credit side of T account is more than Debit side
	if (*sum_of_cred > *sum_of_deb)	
	{
		y=y2;
		y+=1;
		gotoxy(13, y);
		printf("Balance c/d");
		gotoxy(28, y);
		printf("%.2f",*bal);	
		y2=y;	
	}else	
	//If credit side of T account is less than Debit side
	if (*sum_of_cred < *sum_of_deb)
	{
		y2=y;
		y2+=1;
		gotoxy(54, y2);
		printf("Balance c/d");
		gotoxy(69, y2);
		printf("%.2f",*bal);
		y=y2;		
	}
	y+=2;	y2+=2;		
	gotoxy(28,y);
	printf("%.2f", *sum_of_account);	
	gotoxy(69,y2);
	printf("%.2f", *sum_of_account);		
	int yy=y-1; y+=1;	
	
	for (x=25;x<39;x++)
	{
		//bottom line
		gotoxy(x,y);
		printf("_");
				
		//top line
		gotoxy(x,yy);
		printf("_");  
					 
	}	
	int yy2=y2-1; y2+=1;	
	for (x=66;x<80;x++)
	{
		//bottom line
		gotoxy(x,y2);
		printf("_");
					
		//top line
		gotoxy(x,yy2);
		printf("_");  			 
	}	
	y+=2;	y2+=2;	
		
	if (*sum_of_cred > *sum_of_deb)
	{
		gotoxy(54, y2);
		printf("Balance b/d");	
		gotoxy(69, y2);
		printf("%.2f",*bal);		
	}
	else if (*sum_of_cred < *sum_of_deb)
	{
		gotoxy(13, y);
		printf("Balance b/d");
		gotoxy(28, y);
		printf("%.2f",*bal);		
	}
	printf("\n\n\n\n\n\n \t\t\t Press any key to continue");
	getch();
	system ( "cls" );		
}

void Add_To_Deb_or_Cred_T_Acc (int TransactionIndex,struct Cred_Debt_Computing Creditors_Debtors_Compute[], struct Creditor_Debtor Creditors[])
{
	int found=0, a_counter=0, ac_no2 = 0;
	
	if (TransactionIndex == 0)
	{
		ac_no++;
		ac_no2 = ac_no;	
		Creditors_Debtors_Compute[ac_no2-1].num_of_Cred_Debt_Ac += 1;	
	} 
	
	if (TransactionIndex > 0)
	{
		for (a_counter=0;a_counter<ac_no;a_counter++)
		{	
			if (strcmpi(Creditors[a_counter].name_of_Creditor_Debtor,transactions[TransactionIndex].source) == 0)
			{
				found = 1;
				ac_no2 = a_counter+1;
				a_counter=ac_no;
				Creditors_Debtors_Compute[ac_no2-1].num_of_Cred_Debt_Ac+=1;
			}
		}	
	}
	
	// a_counter = ac; so loop finishes
	if ((found != 1) && (TransactionIndex > 0))
	{
		ac_no++;
		ac_no2 = ac_no;	
		Creditors_Debtors_Compute[ac_no2-1].num_of_Cred_Debt_Ac += 1;	
	} 
	
	//copies information from transaction array
	strcpy(Creditors[ac_no2-1].Creditor_Debtor_Transactions[(Creditors_Debtors_Compute[ac_no2-1].num_of_Cred_Debt_Ac)-1].date, transactions[TransactionIndex].date);
	strcpy(Creditors[ac_no2-1].name_of_Creditor_Debtor, transactions[TransactionIndex].source);
	Creditors[ac_no2-1].Creditor_Debtor_Transactions[(Creditors_Debtors_Compute[ac_no2-1].num_of_Cred_Debt_Ac)-1].price = transactions[TransactionIndex].price;
	Creditors[ac_no2-1].Creditor_Debtor_Transactions[(Creditors_Debtors_Compute[ac_no2-1].num_of_Cred_Debt_Ac)-1].type_of_transaction = transactions[TransactionIndex].type_of_transaction;
	
	if((transactions[TransactionIndex].type_of_transaction == 1)   ||  (transactions[TransactionIndex].type_of_transaction == 3))
	{
		//Credit Side
		Creditors_Debtors_Compute[ac_no2-1].Cred_Debt_count_cred +=1;
		Creditors[ac_no2-1].Creditor_Debtor_Transactions[(Creditors_Debtors_Compute[ac_no2-1].num_of_Cred_Debt_Ac)-1].credit_or_debit = 1;
		Creditors_Debtors_Compute[ac_no2-1].sum_of_credit_Cred_Debt+= Creditors[ac_no2-1].Creditor_Debtor_Transactions[(Creditors_Debtors_Compute[ac_no2-1].num_of_Cred_Debt_Ac)-1].price;	
	}else 
	
	if((transactions[TransactionIndex].type_of_transaction == 2)  ||  (transactions[TransactionIndex].type_of_transaction == 4))
	{
		//Debit Side
		Creditors_Debtors_Compute[ac_no2-1].Cred_Debt_count_deb +=1;
		Creditors[ac_no2-1].Creditor_Debtor_Transactions[(Creditors_Debtors_Compute[ac_no2-1].num_of_Cred_Debt_Ac)-1].credit_or_debit = 0;
		Creditors_Debtors_Compute[ac_no2-1].sum_of_debit_Cred_Debt += Creditors[ac_no2-1].Creditor_Debtor_Transactions[(Creditors_Debtors_Compute[ac_no2-1].num_of_Cred_Debt_Ac)-1].price;
	}

	//if the debit side of  a/c is more than the credit side
	if(Creditors_Debtors_Compute[ac_no2-1].sum_of_debit_Cred_Debt > Creditors_Debtors_Compute[ac_no2-1].sum_of_credit_Cred_Debt)
	{	
			Creditors_Debtors_Compute[ac_no2-1].sum_of_Cred_Debt  = Creditors_Debtors_Compute[ac_no2-1].sum_of_debit_Cred_Debt;
			Creditors_Debtors_Compute[ac_no2-1].balance_of_Cred_Debt = Creditors_Debtors_Compute[ac_no2-1].sum_of_debit_Cred_Debt  - Creditors_Debtors_Compute[ac_no2-1].sum_of_credit_Cred_Debt;
	}else
	
	//if the debit side of a/c is less than the credit side
	if(Creditors_Debtors_Compute[ac_no2-1].sum_of_debit_Cred_Debt < Creditors_Debtors_Compute[ac_no2-1].sum_of_credit_Cred_Debt)
	{
		Creditors_Debtors_Compute[ac_no2-1].sum_of_Cred_Debt  = Creditors_Debtors_Compute[ac_no2-1].sum_of_credit_Cred_Debt;
		Creditors_Debtors_Compute[ac_no2-1].balance_of_Cred_Debt = Creditors_Debtors_Compute[ac_no2-1].sum_of_debit_Cred_Debt  - Creditors_Debtors_Compute[ac_no2-1].sum_of_credit_Cred_Debt;
	}else
	
	//if the debit side of a/c is equal than the credit side
	if(Creditors_Debtors_Compute[ac_no2-1].sum_of_debit_Cred_Debt == Creditors_Debtors_Compute[ac_no2-1].sum_of_credit_Cred_Debt)
	{
		Creditors_Debtors_Compute[ac_no2-1].sum_of_Cred_Debt  = Creditors_Debtors_Compute[ac_no2-1].sum_of_credit_Cred_Debt;
		Creditors_Debtors_Compute[ac_no2-1].balance_of_Cred_Debt  = 0;
	}
	
	//If the number of credit entries is more than debit entries
	if (Creditors_Debtors_Compute[ac_no2-1].Cred_Debt_count_cred >= Creditors_Debtors_Compute[ac_no2-1].Cred_Debt_count_deb)
	{
		Creditors_Debtors_Compute[ac_no2-1].Cred_Debt_highest = Creditors_Debtors_Compute[ac_no2-1].Cred_Debt_count_cred;		
	}else 
	if (Creditors_Debtors_Compute[ac_no2-1].Cred_Debt_count_cred < Creditors_Debtors_Compute[ac_no2-1].Cred_Debt_count_deb)
	{
		Creditors_Debtors_Compute[ac_no2-1].Cred_Debt_highest = Creditors_Debtors_Compute[ac_no2-1].Cred_Debt_count_deb;
	}	
}

void Print_Deb_or_Cred_T_Acc( int *b_counter, struct Cred_Debt_Computing Creditors_Debtors_Compute[], struct Creditor_Debtor Creditors[])
{
	int x=1;
	int Ac_index=0;

	for (x=0; x<80; x++)
	{
		//Horizontal lines at the top
		gotoxy(x, 10);
		printf("_");
		gotoxy(x, 7);
		printf("_");
		
		//Horizontal line at the bottom (no of entries plus the row starting at and extra rows before close)
		gotoxy(x, (Creditors_Debtors_Compute[*b_counter].Cred_Debt_highest+20));
		printf("_");
	}
	
	for (y=8; y<=((Creditors_Debtors_Compute[*b_counter].Cred_Debt_highest)+20);y++)
	{
		//vertical line separation for debit and credit side
		gotoxy(39, y);
		printf("|");
	}
	
	i_counter = 0;
	x=22;	y=1;
	gotoxy(x,y);		
	printf("%s",COMPANY);
			y+=5;
	gotoxy(x+11,y);	
	printf(" %s  a/c ",Creditors[*b_counter].name_of_Creditor_Debtor);	//increment with b outside
	x= 0; y+=3;
	gotoxy(x,y);
	printf("Date ");
	x+=13;
	gotoxy(x,y);
	printf("Item");
	x+=15;
	gotoxy(x,y);
	printf("Amount($)");
	x+= 13; 
	gotoxy(x,y);
	printf("Date ");
	x+= 13;
	gotoxy(x,y);
	printf("Item");
	x+=15;
	gotoxy(x,y);
	printf("Amount($)");
	x=0; y+=2;  int x2 = 41; int y2 = 11;
	
	for (i_counter=0; i_counter<(Creditors_Debtors_Compute[*b_counter].num_of_Cred_Debt_Ac);i_counter++)
	{	
		Ac_index = Creditors[*b_counter].Creditor_Debtor_Transactions[i_counter].type_of_transaction;	
	
		// print debit entries
		if(Creditors[*b_counter].Creditor_Debtor_Transactions[i_counter].credit_or_debit == 0)
		{				
			gotoxy(x,y);			
			printf("%s",Creditors[*b_counter].Creditor_Debtor_Transactions[i_counter].date);
			x+=13;
			gotoxy(x,y);
			
			if (Ac_index == 2)
			{
				printf("Sales");				
			}else
			if (Ac_index == 4)
			{
				printf("Returns Outwards");
			}				
			x+=15;
			gotoxy(x,y);
			printf("%.2f",Creditors[*b_counter].Creditor_Debtor_Transactions[i_counter].price);
			x=0;		y+=1;
			gotoxy(x,y);
		}	else
		
		if (Creditors[*b_counter].Creditor_Debtor_Transactions[i_counter].credit_or_debit == 1)
		{
			//print credit side of T_accounts
			gotoxy(x2,y2);			
			printf("%s",Creditors[*b_counter].Creditor_Debtor_Transactions[i_counter].date);
			x2+=13;
			gotoxy(x2,y2);
			
			if (Ac_index == 1)
			{
				printf("Purchases");
			}else 
			if (Ac_index == 3)
			{
				printf("Returns Inwards");
			}  
			x2+=15;
			gotoxy(x2,y2);
			printf("%.2f",Creditors[*b_counter].Creditor_Debtor_Transactions[i_counter].price);
			x2=41;		y2+=1;
			gotoxy(x2,y2);
		} 
	} 
	//If credit side of T account is more than Debit side
	if (Creditors_Debtors_Compute[*b_counter].sum_of_credit_Cred_Debt > Creditors_Debtors_Compute[*b_counter].sum_of_debit_Cred_Debt)	
	{
		y=y2;
		y+=1;
		gotoxy(13, y);
		printf("Balance c/d");	
		gotoxy(28, y);
		printf("%.2f",fabsf(Creditors_Debtors_Compute[*b_counter].balance_of_Cred_Debt));		
		y2=y;		
	}else

	//If credit side of T account is less than Debit side
	if (Creditors_Debtors_Compute[*b_counter].sum_of_credit_Cred_Debt < Creditors_Debtors_Compute[*b_counter].sum_of_debit_Cred_Debt)
	{
		y2=y;
		y2+=1;
		gotoxy(54, y2);
		printf("Balance c/d");
		gotoxy(69, y2);
		printf("%.2f",fabsf(Creditors_Debtors_Compute[*b_counter].balance_of_Cred_Debt));
			y=y2;		
	}
	y+=2;	y2+=2;
	gotoxy(28,y);
	printf("%.2f", Creditors_Debtors_Compute[*b_counter].sum_of_Cred_Debt );
	gotoxy(69,y2);
	printf("%.2f", Creditors_Debtors_Compute[*b_counter].sum_of_Cred_Debt );	
	int yy=y-1; y+=1;
		
	for (x=25;x<39;x++)
	{
		//bottom line
		gotoxy(x,y);
		printf("_");
					
		//top line
		gotoxy(x,yy);
		printf("_");  			 
	}
	int yy2=y2-1; y2+=1;
		
	for (x=66;x<80;x++)
	{
		//bottom line
		gotoxy(x,y2);
		printf("_");
					
		//top line
		gotoxy(x,yy2);
		printf("_");  				 
	}		
		y+=2;	y2+=2;	
		
	if (Creditors_Debtors_Compute[*b_counter].sum_of_credit_Cred_Debt > Creditors_Debtors_Compute[*b_counter].sum_of_debit_Cred_Debt)
	{
		gotoxy(54, y2);
		printf("Balance b/d");
		gotoxy(69, y2);
		printf("%.2f",fabsf(Creditors_Debtors_Compute[*b_counter].balance_of_Cred_Debt));
	}
	else if (Creditors_Debtors_Compute[*b_counter].sum_of_credit_Cred_Debt < Creditors_Debtors_Compute[*b_counter].sum_of_debit_Cred_Debt)
	{
		gotoxy(13, y);
		printf("Balance b/d");	
		gotoxy(28, y);
		printf("%.2f",fabsf(Creditors_Debtors_Compute[*b_counter].balance_of_Cred_Debt));		
	}
	printf("\n\n\n\n\n\n \t\t\t Press any key to continue");
	getch();
	system ( "cls" );		
}

void Load_BusinessAcc_Screen()
{
	char file_name[30], load_previous[2]=" ";
	
	system("cls");
	rectangle(0,0,80,23);
	x=21;	y=4;
	gotoxy(x,y); 		
	printf("%s",COMPANY);
	x=29;	y=8;
    gotoxy(x,y); 		
	printf("Load Business Account");
	rectangle2(17,9,64,16);
	rectangle2(17,9,64,12);
	x=19;	y=10;
    gotoxy(x,y); 		
	printf("Would you like to load a previously saved");
	x=19;	y=11;
    gotoxy(x,y); 
	printf("Business Account ? [Y/N]");
	x=20;	y=14;
    gotoxy(x,y); 
	printf("Yes (Y) or No (N):");
	x=39;	y=14;
    gotoxy(x,y); 
	scanf("%s",load_previous);

	while(!(((strcmpi(load_previous,"Y")==0)) || ((strcmpi(load_previous,"N")==0))))
	{
	    x=15;	y=17;
        gotoxy(x,y); 
		printf("You have entered an invalid input! Please try again.");
		Sleep(2000);
		x=15;	y=17;
        gotoxy(x,y); 		
	    printf("                                                      ");
		x=39;	y=14;
        gotoxy(x,y); 
	    printf("      ");	
		x=39;	y=14;
        gotoxy(x,y); 
	    scanf("%s",load_previous);			
	}
		
    if(strcmpi(load_previous,"Y")==0)
	{
		x=19;	y=10;
	    gotoxy(x,y); 		
		printf("                                           ");
		x=19;	y=11;
	    gotoxy(x,y); 		
		printf("                                           ");
		x=20;	y=14;
	    gotoxy(x,y); 		
		printf("                                           ");
		x=19;	y=10;
	    gotoxy(x,y); 		
		printf("Enter file name of previously saved Business");
		x=19;	y=11;
	    gotoxy(x,y); 		
		printf("Account to Load (or Type 'Q' to Quit):");
		x=20;	y=14;
	    gotoxy(x,y); 		
		printf("File Name:");
		x=31;	y=14;
	    gotoxy(x,y); 
		scanf("%s",file_name);
		
		while(!(Read_Transactions(transactions,file_name))&&(strcmpi(file_name,"Q")!=0))
		{			
			x=22;	y=17;
		    gotoxy(x,y); 
			printf("Business Account file does not exists!");
			x=26;	y=18;
		    gotoxy(x,y); 
			printf("Please enter valid file name.");
			Sleep(2000);	
			x=22;	y=17;
		    gotoxy(x,y); 		
			printf("                                         ");
			x=22;	y=18;
		    gotoxy(x,y); 		
			printf("                                         ");
			x=31;	y=14;
		    gotoxy(x,y); 
			printf("                           ");
			x=31;	y=14;
		    gotoxy(x,y); 
			scanf("%s",file_name);		 
		}
    }
}

void Save_BusinessAcc_Screen(int save_as)
{
	char file_name[30], confirm_save[2]=" ";
	
	system("cls");
	rectangle(0,0,80,23);
	x=21;	y=4;
	gotoxy(x,y); 		
	printf("%s",COMPANY);
	x=29;	y=8;
    gotoxy(x,y); 		
	printf("Save Business Account");
	rectangle2(17,9,64,16);
	rectangle2(17,9,64,12);
	x=19;	y=10;
    gotoxy(x,y); 		
	printf("Are you sure would like to save Business");
	x=19;	y=11;
    gotoxy(x,y); 
	printf("Account ? [Y/N]");
	x=20;	y=14;
    gotoxy(x,y); 
	printf("Yes (Y) or No (N):");
	x=39;	y=14;
    gotoxy(x,y); 
	scanf("%s",confirm_save);
	      
	while(!(((strcmpi(confirm_save,"Y")==0)) || ((strcmpi(confirm_save,"N")==0))))
	{
	    x=15;	y=17;
        gotoxy(x,y); 
		printf("You have entered an invalid input! Please try again.");
		Sleep(2000);
		x=15;	y=17;
        gotoxy(x,y); 		
	    printf("                                                      ");
		x=39;	y=14;
        gotoxy(x,y); 
	    printf("      ");	
		x=39;	y=14;
        gotoxy(x,y); 
	    scanf("%s",confirm_save);		
	}
	
    if(strcmpi(confirm_save,"Y")==0)
    
	{
		if (save_as)
		{
			x=19;	y=10;
		    gotoxy(x,y); 		
			printf("                                           ");
			x=19;	y=11;
		    gotoxy(x,y); 		
			printf("                                           ");
			x=20;	y=14;
		    gotoxy(x,y); 		
			printf("                                           ");
			x=19;	y=10;
		    gotoxy(x,y); 		
			printf("Enter file name to save Business");
			x=19;	y=11;
		    gotoxy(x,y); 		
			printf("Account as (or Type 'Q' to Quit):");
			x=20;	y=14;
		    gotoxy(x,y); 		
			printf("File Name:");
			x=31;	y=14;
		    gotoxy(x,y); 
			scanf("%s",file_name);
		    Save_Transactions(transactions,file_name);
		    strcpy(current_file,file_name);
		}else
		{	
			Save_Transactions(transactions,current_file);
		}
    }
}

void Welcome_Screen()
{
	system("cls");
	rectangle(0,0,80,23);
	rectangle(16,7,66,13);
	x=22;	y=10;
    gotoxy(x,y); 
    printf("%s\n",COMPANY);
    x=39;	y=14;
    gotoxy(x,y); 
    printf("Created by Philmon Roberts\n");
	Sleep(3000);
}

int Login_Screen()
{
	int access_granted=0, tries = 0;
	Read_Login();	
	system("cls");
	rectangle(0,0,80,23);
	x=21;	y=4;
	gotoxy(x,y); 		
	printf("%s",COMPANY);
	
	do
	{
        rectangle2(21,8,58,16);
        rectangle2(21,8,58,10);
		i_counter+=1;
		x=37;	y=9;
		gotoxy(x,y); 		
		printf("Login");
		x=23;	y=12;
		gotoxy(x,y);		
		printf("Username: ");
		y+=2;	
		gotoxy(x,y);
		printf("Password: ");
		x=33;	y=12;
		gotoxy(x,y);
		scanf(" %s", Login.username);
		y+=2;
		gotoxy(x,y);
		char passwrd[30]={0};//To nullify the string passwrd
        _password(passwrd);
        strcpy(Login.password,passwrd);
			
		for(i_counter=0;i_counter<3;i_counter++)
		{
			if((strcmp(Users[i_counter].username,Login.username)==0)&&(strcmp(Users[i_counter].password,Login.password)==0))
			{
				access_granted = 1;
			    break;				
			}else
			{
				x=22;	y=17;
			    gotoxy(x,y);		
			    printf("Login Details Entered Incorrectly!");
				Sleep(2000);
				x=22;	y=17;
			    gotoxy(x,y);		
			    printf("                                          ");	
			    x=33;	y=12;
				gotoxy(x,y);
				printf("                      ");				 
				x=33;	y+=2;
				gotoxy(x,y);
				printf("                      ");
				x=0;	y=0;
				gotoxy(x,y);
				break;	
			}
		}
		tries+=1;
	}while ((!access_granted)&&(tries<3));	
	
	return access_granted;
}

void Main_Menu()
{
	int menu_choice=0;
	system("cls");
	rectangle(0,0,80,23);
	x=21;	y=4;
	gotoxy(x,y); 		
	printf("%s",COMPANY);
	rectangle(10,7,38,17);
	x=12;	y=9;
	gotoxy(x,y); 
	printf("1 - Input data");
	x=12;	y=11;
	gotoxy(x,y); 
	printf("2 - Compute Journals");
	x=16;	y=12;
	gotoxy(x,y); 
	printf("and CashBook");
	x=12;	y=14;
	gotoxy(x,y); 
	printf("3 - Compute T-account");
	rectangle(41,7,70,17);
	x=43;	y=9;
	gotoxy(x,y); 
	printf("4 - Load Business Account");
	x=43;	y=11;
	gotoxy(x,y); 
	printf("5 - Save - Business");
	x=54;	y=12;
	gotoxy(x,y); 
	printf("Account");
	x=43;	y=14;
	gotoxy(x,y); 
	printf("6 - Save As - New Business");
	x=57;	y=15;
	gotoxy(x,y); 
	printf("Account");
	x=69;	y=2;
	gotoxy(x,y); 
	printf("Exit (7)");
	x=30;	y=20;
	gotoxy(x,y); 
	printf("Menu Choice:");
	x=43;	y=20;
	gotoxy(x,y); 
	scanf("%d",&menu_choice);
	x=43;	y=20;
	gotoxy(x,y); 
	printf("%d",menu_choice);
	system("cls");
	
	while(menu_choice != 7)
	{
		switch(menu_choice)
		{
			case 1:
			{
				Inputting_Transactions ();
				break;
			}	
			case 2:
			{
				Compute_Journals_and_CashBook ();
				break;
			}
			case 3:
			{
				Compute_t_account ();
				break;
			}
		    case 4:
			{
				Load_BusinessAcc_Screen();
				break;	
			}	
			case 5:
			{
				Save_BusinessAcc_Screen(0);
				break;
			}	
			case 6:
			{
				Save_BusinessAcc_Screen(1);
				break;
			}	
			default : 
			{
				printf("\t\tYou have entered an incorrect menu choice \n \n Please try again");
			}
		}
		system("cls"); 
		if(menu_choice == 7)
		{
			break;	
		}
		system("cls");
		rectangle(0,0,80,23);
		x=21;	y=4;
		gotoxy(x,y); 		
		printf("%s",COMPANY);
		rectangle(10,7,38,17);
		x=12;	y=9;
		gotoxy(x,y); 
		printf("1 - Input data");
		x=12;	y=11;
		gotoxy(x,y); 
		printf("2 - Compute Journals");
		x=16;	y=12;
		gotoxy(x,y); 
		printf("and CashBook");
		x=12;	y=14;
		gotoxy(x,y); 
		printf("3 - Compute T-account");
		rectangle(41,7,70,17);
		x=43;	y=9;
		gotoxy(x,y); 
		printf("4 - Load Business Account");
		x=43;	y=11;
		gotoxy(x,y); 
		printf("5 - Save - Business");
		x=54;	y=12;
		gotoxy(x,y); 
		printf("Account");
		x=43;	y=14;
		gotoxy(x,y); 
		printf("6 - Save As - New Business");
		x=57;	y=15;
		gotoxy(x,y); 
		printf("Account");
		x=69;	y=2;
		gotoxy(x,y); 
		printf("Exit (7)");
		x=30;	y=20;
		gotoxy(x,y); 
		printf("Menu Choice:");
		x=43;	y=20;
		gotoxy(x,y); 
		scanf("%d",&menu_choice);
		x=43;	y=20;
		gotoxy(x,y); 
		printf("%d",menu_choice);
		system("cls");
	}	
}

void Save_Transactions(struct transaction T[],char file_name[])
{
	int a_counter=0;
	
	FILE *file_pointer;
	file_pointer = fopen(file_name,"w");
	
	//print to transaction to file
	for (a_counter=0;a_counter<num_of_transactions;a_counter++)
	{
		fprintf(file_pointer,"T%d %s %d %d %s %d %s %.2f %s %.2f %.2f \n",a_counter, T[a_counter].date,T[a_counter].type_of_transaction,T[a_counter].specific_transaction, T[a_counter].item_name ,T[a_counter].quantity ,T[a_counter].source ,T[a_counter].unit_price ,T[a_counter].credit_or_cash, T[a_counter].discount_percent , T[a_counter].price);
	}	
	fclose(file_pointer);	
}

int Read_Transactions(struct transaction T[],char file_name[])
{
	char *a;
	num_of_transactions=0;
	int success = 0;
	FILE *file_pointer;
	file_pointer = fopen(file_name,"r");
		
	//Read from Transaction file; but first check if file is not empty
	if(file_pointer != NULL)
	{
		while(!feof(file_pointer))
		{
			if (fscanf(file_pointer,"%s %s %d %d %s %d %s %f %s %f %f",&a, T[num_of_transactions].date,&T[num_of_transactions].type_of_transaction,&T[num_of_transactions].specific_transaction, T[num_of_transactions].item_name ,&T[num_of_transactions].quantity ,T[num_of_transactions].source ,&T[num_of_transactions].unit_price ,T[num_of_transactions].credit_or_cash, &T[num_of_transactions].discount_percent ,&T[num_of_transactions].price)!=EOF)
			{
			num_of_transactions+=1;	
			}
		}
		strcpy(current_file,file_name);
		success = 1;
	} 
	fclose(file_pointer);
	return success;
}

void Read_Login()
{
	int z_counter =0;
	num_of_transactions=0;
	char *a;
	FILE *file_pointer;
	file_pointer = fopen("Users.txt","r");
	
	//read from login file
	for(z_counter=0;z_counter<3;z_counter++)
	{
		fscanf(file_pointer,"%s %s %s",&a, Users[z_counter].username,Users[z_counter].password);
	}
	fclose(file_pointer);
}

void rectangle(int x,int y,int l,int b)
{
	//print 1st rectangle
    int i,m;
    gotoxy(x,y); printf("%c",201);
    for(i=x+1;i<l-1;i++)
    {
        gotoxy(i,y);
        printf("%c",205);
    }
    gotoxy(i,y); printf("%c",187);

    for (m=y+1;m<b;m++)
    {
        gotoxy(x,m);
        for(i=x;i<l;i++)
        {
            if(i==x||i==l-1)
            {
                gotoxy(i,m); printf("%c",186);
        	}
        }
    }
    gotoxy(x,m); printf("%c",200);
    
    for(i=x+1;i<l-1;i++)
    {
        gotoxy(i,m);
        printf("%c",205);
    }
    gotoxy(i,m); printf("%c",188);
}

void rectangle2(int x,int y,int l,int b)
{
	//print 2nd rectangle
    int i,m;
    gotoxy(x,y); printf("%c",218);
    for(i=x+1;i<l-1;i++)
    {
        gotoxy(i,y);
        printf("%c",196);
    }
    gotoxy(i,y); printf("%c",191);

    for (m=y+1;m<b;m++)
    {
        gotoxy(x,m);
        for(i=x;i<l;i++)
        {
            if(i==x||i==l-1)
            {
                gotoxy(i,m); printf("%c",179);
            }
        }
    }
    gotoxy(x,m); printf("%c",192);
    
    for(i=x+1;i<l-1;i++)
    {
        gotoxy(i,m);
        printf("%c",196);
    }
    gotoxy(i,m); printf("%c",217);
}

void _password(char buffer[])
{	//store password in a buffer to print it as stars
	char c;
    int pos = 0;
    do
    {
      	c = getch();
        if( isprint(c) )
        {
        	buffer[ pos++ ] = c;
            printf("%c", '*');
        }
        else if( c == 8 && pos )
        {
        	buffer[ pos-- ] = '\0';
            printf("%s", "\b \b");
       	}
    }while( c != 13 );
}
	

