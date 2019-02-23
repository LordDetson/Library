/*
 * UserScreen.h
 *
 *  Created on: 13 но€б. 2017 г.
 *      Author: ƒмитрий
 */

#ifndef SCREENS_USERSCREEN_H_
#define SCREENS_USERSCREEN_H_
#include <iostream>
#include <string>
#include <list>
#include "../Data_Classes/Book.h"
#include "../Services/ServiceData.h"
#include "../Services/ServiceBooks.h"
using namespace std;

class UserScreen {
private:
	list<Book> *ListBooks;
	static bool created;

	UserScreen(list<Book>&);
	~UserScreen();
	UserScreen(const UserScreen&);
	UserScreen& operator=(const UserScreen&);
	void sortInAscendingOrderBooksMenu();
	void sortInDecreasingOrderBooksMenu();
	void findBookMenu();
public:
	static UserScreen& instance(list<Book>&);
	void showUserScreen();
};

#endif /* SCREENS_USERSCREEN_H_ */
