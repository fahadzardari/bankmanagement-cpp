#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <time.h>
#include <math.h>


using namespace std;
string setw(int i );
string setw(int i , char c);
int count = 0;

class Bank {
	private:
		string name , pin , acc_no ,dir = "users/" , pin_confirm;
		int  balance  ;

	public:
		void reset(){
			name = ' ';
			acc_no =  ' ';
			pin = ' ';
			pin_confirm = ' ';
			balance = ' ';
			dir = "users/";
		}
		void setName(){
			cout << setw(12) << "Enter Your Name : ";
			cin.ignore();
			getline(cin, name);
		}
		void setAccount(){
			cout << setw(12) << "Enter Your Account No  (length = 5 ) : ";
			cin >> acc_no;
		}
		void setBalance(){
			cout << setw(12) << "Enter Your Balance : ";
			cin >> balance;
		}
		void setPin(){
			cout << setw(12) << "Enter Your Pin (length = 4) : ";
			cin >> pin;
		}
		string getName(){
			return name;
		}
		string getAccount(){
			return acc_no;
		}
		string getPin(){
			return pin;
		}
		int getBalance(){
			return balance;
		}
		void display(){
			cout << "\n\n";
			cout << setw(39) << "Account Number : " << acc_no << endl;
			cout << setw(39) << "Account Holder : " << name << endl;
			cout << setw(39) << "Account Balance : " << balance << endl;
			cout << "\n\n";
		}
		void resetCount();
		void header();
		void checkSize(string& prop , int size , string prop_name);
		void accountCheck();
		bool checkLog(string a);
		void pinConfirm();
		void saveAccount();
		void addAccountToLog();
		void getAccountData();
		void deleteFromLog();
	
		void mainMenu(){
		system("cls");
		int check;
		Bank::header();
		cout << "\n\n\n\n\n\n";
		cout << setw(45) << "1. Create New Account\n";
		cout << setw(45) << "2. Login\n";
		cout << setw(45) << "Any other key to Exit\n";
		cout << setw(45) << "Your choice: ";
		cin >> check;
					switch(check){
						case 1:
							Bank::createAccount();
							break;
						case 2:
							login();
							break;

						default:
							exit(1);
				}

		} // end main menu




		void menu(){

			system("cls");
			header();
			display();
			int check;
			cout << setw(12) << "1. Withdraw\n";
			cout << setw(12) << "2. Deposit\n";
			cout << setw(12) << "3. Change account pin\n";
			cout << setw(12) << "4. Delete Account\n";
			cout << setw(12) << "5. Logout\n";
			cout << setw(12) << "Any other key to Exit\n";
			cout << setw(12) << "Your choice = ";
			cin >> check;
					switch(check){
						case 1:
							withdraw();
							break;
						case 2:
							deposit();
							break;
						case 3:
							changePin();
							break;
						case 4:
							deleteAccount();
							break;
						case 5:
							reset();
							mainMenu();
							break;
						default:
							exit(1);


				}

				} // end menu

			//Start Of Create Account method
		void createAccount(){
			ofstream user;
			system("cls");
			cout << setw(30) << setw(20 , '-') << "Create Account Menu"<< setw(20 , '-') << endl;
			setName();
			setAccount();
			accountCheck();
			checkSize(acc_no , 5 , "Account No");
			setPin();
			checkSize(pin , 4 , "Pin");
			cout << setw(12) <<"Confirm Your Pin : ";
			cin >> pin_confirm;
			pinConfirm();
			setBalance();
			while(balance < 0 ){
				if(count == 3){
					cout << setw(12) << "No tries left Press any key to retun back";
					getch();
					resetCount();
					menu();
				}
				cout << setw(12) << "Invalid amount try again : ";
				cin >> balance;
				count++;
			}
			dir += acc_no + ".txt";
			addAccountToLog();
			saveAccount();

			cout << setw(12)
				 << "Congratulations " << name
				 << " your account has been created successfully\n" 
				 << setw(12) << "Your Account No is = " << acc_no << endl
		 		<< setw(12) <<" your first deposit is = " << balance <<endl;
			cout << setw(12) << "Press any key to return back......";
			reset();
			getch();
			mainMenu();
		}
		void login(){
			//Start Of Login method

			ifstream user;

			system("cls");
			cout << setw(30) << setw(20 , '-') << "Login Menu"<< setw(20 , '-') << endl;


			setAccount();
			checkSize(acc_no, 5 , "Account No");
			if(checkLog(acc_no) != 1){
				cout << "Account Doesn't exist\nPress any key to return back.........";
				getch();
				reset();
				mainMenu();
			}
			getAccountData();
			cout << setw(12) << "Enter your pin (length = 4): ";
			cin >> pin_confirm;
			checkSize(pin_confirm , 4 , "Pin");

			pinConfirm();

			menu();

		} //end of Login method

		/************ Start of Withdraw function **********/
		void withdraw(){
			int withdraw;
			resetCount();
			system("cls");
			header();
			display();
			cout << setw(12) << "Enter the amount you want to withdraw : ";
			cin >> withdraw;
			while(withdraw < 0 || withdraw > balance){
				if(count == 3){
					cout << setw(12) << "No tries left Press any key to retun back";
					getch();
					resetCount();
					menu();
				}
				cout << setw(12) << "Invalid amount try again : ";
				cin >> withdraw;
				count++;
			}
			balance -= withdraw;
			saveAccount();
			cout << setw(12) << "Successfully withdrawn\n" <<  setw(12) << "Press any key to return back";
			getch();
			menu();
		}
		/************ End of Withdraw function **********/

		/************ Start of Deposit function **********/

		void deposit(){
			resetCount();
			int deposit;
			system("cls");
			header();
			display();

			cout << setw(12) << "Enter the amount you want to deposit : ";
			cin >> deposit;
			while(deposit <= 0 ){
				if(count == 3){
					cout << setw(12) << "No tries left Press any key to retun back";
					getch();
					resetCount();
					menu();
				}
				cout << setw(12) << "Invalid amount try again : ";
				cin >> deposit;
				count++;
			}
			
			balance += deposit;
			saveAccount();
			cout << setw(12) << "Successfully Deposited\n"<< endl << setw(12) <<"Press any key to return back";
			getch();
			menu();
		}

		/************ End Of Deposit function **********/

		/************ Start of edit function **********/
		void changePin(){
			string pin_confirm_local;
			system("cls");
			header();
			display();
			
			cout << setw(12) << "Enter your current pin: ";
			cin >> pin_confirm;
			pinConfirm();
			cout << setw(12) << "Enter your new pin (length = 4) : ";
			cin >> pin_confirm;
			cout << setw(12) << "Confirm your new pin : ";
			cin >> pin_confirm_local;
			if(pin_confirm_local != pin_confirm){
				cout << setw(12) << "Pin doesn't match\n" << setw(12) << "Press any key to return back.......";
				getch();
				menu();
			}
			pin = pin_confirm;
			saveAccount();
			cout << setw(12) << "Pin successfully changed\n" << setw(12) << "Press any key to login page...... ";
				getch();
				login();
		}
		void deleteAccount(){
			system("cls");
			header();
			display();
			char check;
			cout << setw(12) << "Enter your pin: ";
			cin >> pin_confirm;
			pinConfirm();
						
			cout << setw(12) << "Do you really want to delete your account permenantely\n"
				 << setw(12) << "Press y to proceed, any other key to return back : ";
			cin >> check;
			if(check == 'y' || check == 'Y'){
				char d[20];
				for (int i = 0 ; i < dir.length() ; i++){
					d[i] = dir[i];
				}
				
				
				int stat = remove(d);
				cout << setw(12) << "We are sorry to see you go\n" << setw(12) << "Press any key to exit....";
				deleteFromLog();
				getch();
				exit(1);
			}
			menu();
			
		}

};

/************* Main **********/

int main(){

	Bank b;
	b.mainMenu();
	return 0;
}
/********** End of Main ***********/


		void Bank::resetCount(){
			count = 0;
		}
		void Bank::header(){
						cout << setw(30) << setw(20 , '-') << "Welcome to XYZ Bank"<< setw(20 , '-') << endl;
		}
		void Bank::checkSize(string& prop , int size , string prop_name){

			if(prop.length()  != size ){
				resetCount();
				while(prop.length() != size){
					if(count == 3){
						cout << setw(12) << "No tries left\n "<< setw(12 )<< "Press any key to return to Main Menu";
						getch();
						mainMenu();
					}
					count++;
					cout << setw(12) << "Invalid length of " << prop_name << " (" << count << " of 3 tries): ";
					cin >> prop;

				}

			}


		}

		void Bank::accountCheck(){
			ifstream account;
			string line;
			account.open("accounts.txt" );

			while(getline(account , line)){
				if(line == acc_no){
					cout << setw(12) << acc_no << " Account no already exists \n"
					<< setw(12) <<" Press any key to return to main menu..........";
					getch();
					mainMenu();
				}

			}
			account.close();
		} //end of accountCheck
		void Bank::addAccountToLog(){
			/********** Adding Account no to Log *************/
			ofstream acc ;
			acc.open("accounts.txt" ,ios::app);
			acc  <<acc_no <<endl ;
			acc.close();
			/********** Added Account to Log    *************/

		}
		bool Bank::checkLog(string a){
			ifstream account;
			string line;
			account.open("accounts.txt" );

			while(getline(account , line)){
				if(line == a){
					account.close();
					return 1;
				}

			}

			account.close();
			return 0;

		}
		void Bank::saveAccount(){

			/********** Creating and updating account file ********/
			ofstream userRecord;


			userRecord.open(dir.c_str());

			userRecord << acc_no << endl << name << endl << pin << endl << balance;
			userRecord.close();
			/********** Creating and updating account file ********/

		} // end of save account

		void Bank::pinConfirm(){
			resetCount();
			while(pin_confirm != pin){
				if(count == 3){
						cout << setw(12) << "No tries left\n"<<setw(12)<<"Press any key to return to Main Menu";
						getch();
						mainMenu();
					}
					count++;
					cout << setw(12) << "Pin doesn't match (" << count << " of 3 tries): ";
					cin >> pin_confirm;

			}
		}

		void Bank::getAccountData(){
		    ifstream user;
			dir += acc_no + ".txt";
			user.open(dir.c_str());
			cin.ignore();
			getline(user , acc_no);
			getline(user , name);
			user >> pin;
			user >> balance;

		}
		void Bank::deleteFromLog(){
			ifstream log("accounts.txt");
			string line , whole;
			while(getline(log , line)){
				if(line != acc_no){
					whole += line + "\n";
				}
			}
			log.close();
			ofstream logWrite("accounts.txt");
			logWrite << whole;
			logWrite.close();
		}
	
string setw(int i){
	string r;
	 for (int j = 0 ; j < i ; j++){
	 	r += " ";
	 }
	 return r;
}
string setw(int i , char c){
	string r;
	 for (int j = 0 ; j < i ; j++){
	 	r += c;
	 }
	 return r;
}

