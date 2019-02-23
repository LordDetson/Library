#include <iostream>
#include <list>
#include "./Screens/LoginAndPasswordScreen.h"
#include "./Screens/AdministratorScreen.h"
#include "./Screens/UserScreen.h"
#include "./Ñontrollers/ControllerIOFStream.h"
#include "./Data_Classes/UserAccount.h"
#include "./Data_Classes/Book.h"
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	list<UserAccount> ListUserAccounts;
	ListUserAccounts = readFile(UserAccount::PATH_USER_ACCOUNTS,
			ListUserAccounts);
	list<Book> ListBooks;
	ListBooks = readFile(Book::PATH_BOOKS, ListBooks);
	list<UserAccount>::iterator activeAccount =
			LoginAndPasswordScreen::instance(ListUserAccounts).showLoginAndPasswordScreen();
	if ((*activeAccount).getUserId() == 0) {
		AdministratorScreen::instance(ListUserAccounts, ListBooks).showAdministratorScreen();
		return 0;
	}
	UserScreen::instance(ListBooks).showUserScreen();
	return 0;
}
