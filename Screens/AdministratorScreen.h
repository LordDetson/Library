/*
 * AdministratorScreen.h
 *
 *  Created on: 13 íîÿá. 2017 ã.
 *      Author: Äìèòðèé
 */

#ifndef SCREENS_ADMINISTRATORSCREEN_H_
#define SCREENS_ADMINISTRATORSCREEN_H_

#include <iostream>
#include <string>
#include <list>
#include "../Data_Classes/UserAccount.h"
#include "../Data_Classes/Book.h"
#include "../Services/ServiceData.h"
#include "../Services/ServiceUserAccounts.h"
#include "../Services/ServiceBooks.h"
#include "../Ñontrollers/ControllerIStream.h"
#include "../Ñontrollers/ControllerIOFStream.h"
#include "ExceptionScreen.h"
using namespace std;

class AdministratorScreen {
private:
	list<UserAccount> *ListUserAccounts;
	list<unsigned int> ListFreeUserId;
	list<Book> *ListBooks;
	list<unsigned int> ListFreeBookId;
	static bool created;

	AdministratorScreen(list<UserAccount>&, list<Book>&);
	AdministratorScreen(const AdministratorScreen&);
	~AdministratorScreen();
	AdministratorScreen& operator=(const AdministratorScreen&);

	void accountManagementMenu();
	void bookManagementMenu();
	void editingUserAccountMenu();
	void editingBookMenu();
	void sortInAscendingOrderUserAccountsMenu();
	void sortInAscendingOrderBooksMenu();
	void sortInDecreasingOrderUserAccountsMenu();
	void sortInDecreasingOrderBooksMenu();
	void findUserAccountMenu();
	void findBookMenu();
public:
	static AdministratorScreen& instance(list<UserAccount>&, list<Book>&);
	void showAdministratorScreen();
};

#endif /* SCREENS_ADMINISTRATORSCREEN_H_ */
