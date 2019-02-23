/*
 * UserScreen.cpp
 *
 *  Created on: 13 нояб. 2017 г.
 *      Author: Дмитрий
 */

#include "UserScreen.h"

bool UserScreen::created = false;

UserScreen::UserScreen(list<Book> &ListBooks) {
	this->ListBooks = &ListBooks;
	this->created = true;
}

UserScreen::~UserScreen() {
}

UserScreen& UserScreen::instance(list<Book> &ListBooks) {
	static UserScreen *inst;
	if (!created)
		inst = new UserScreen(ListBooks);
	return *inst;
}

void UserScreen::showUserScreen() {
	unsigned int variation;
	while (true) {
		system("cls");
		showList(*ListBooks);
		cout<<"1.\tСортировка по возрастанию/А-Я\n"
				<<"2.\tСортировка по убыванию/Я-А\n"
				<<"3.\tПоиск\n"
				<<"4.\tВывести список книг с фамилиями авторов в алфавитном порядке, изданных после заданного года \n"
				<<"0.\tВыйти"
				<<endl;
		variation = inputUnsignedInt(cin);
		switch(variation){
		case 1:
			sortInAscendingOrderBooksMenu();
			break;
		case 2:
			sortInDecreasingOrderBooksMenu();
			break;
		case 3:
			findBookMenu();
			break;
		case 4:
			ServiceBooks::showListBookByPublishingYear(*ListBooks);
			break;
		case 0:
			break;
		default:
			showExceptionScreen();
		}
		if (variation == 0)
			break;
	}
}

void UserScreen::sortInAscendingOrderBooksMenu(){
	unsigned int variation;
	system("cls");
	cout << "1.\tПо идентификатору\n" << "2.\tПо автору\n"
			<< "3.\tПо названию\n"
			<< "4.\tПо году издания\n"
			<< "5.\tПо издательству\n"
			<< "6.\tПо жанру\n"
			<< "7.\tПо количеству страниц\n"
			<< "0.\tВернуться" << endl;
	variation = inputUnsignedInt(cin);
	switch (variation) {
	case 1:
		ListBooks->sort(ServiceBooks::compBookById);
		break;
	case 2:
		ListBooks->sort(ServiceBooks::compBookByAuthor);
		break;
	case 3:
		ListBooks->sort(ServiceBooks::compBookByTitle);
		break;
	case 4:
		ListBooks->sort(ServiceBooks::compBookByPublishingYear);
		break;
	case 5:
		ListBooks->sort(ServiceBooks::compBookByPublishingHouse);
		break;
	case 6:
		ListBooks->sort(ServiceBooks::compBookByGenre);
		break;
	case 7:
		ListBooks->sort(ServiceBooks::compBookByNumberOfPages);
		break;
	case 0:
		break;
	default:
		showExceptionScreen();
	}
}

void UserScreen::sortInDecreasingOrderBooksMenu(){
	unsigned int variation;
	system("cls");
	cout << "1.\tПо идентификатору\n" << "2.\tПо автору\n"
			<< "3.\tПо названию\n"
			<< "4.\tПо году издания\n"
			<< "5.\tПо издательству\n"
			<< "6.\tПо жанру\n"
			<< "7.\tПо количеству страниц\n"
			<< "0.\tВернуться" << endl;
	variation = inputUnsignedInt(cin);
	switch (variation) {
	case 1:
		ListBooks->sort(ServiceBooks::recompBookById);
		break;
	case 2:
		ListBooks->sort(ServiceBooks::recompBookByAuthor);
		break;
	case 3:
		ListBooks->sort(ServiceBooks::recompBookByTitle);
		break;
	case 4:
		ListBooks->sort(ServiceBooks::recompBookByPublishingYear);
		break;
	case 5:
		ListBooks->sort(ServiceBooks::recompBookByPublishingHouse);
		break;
	case 6:
		ListBooks->sort(ServiceBooks::recompBookByGenre);
		break;
	case 7:
		ListBooks->sort(ServiceBooks::compBookByNumberOfPages);
		break;
	case 0:
		break;
	default:
		showExceptionScreen();
	}
}

void UserScreen::findBookMenu(){
	unsigned int variation;
	while (true) {
		system("cls");
		cout << "1.\tПо идентификатору\n" << "2.\tПо автору\n"
				<< "3.\tПо названию\n"
				<< "4.\tПо году издания\n"
				<< "5.\tПо издательству\n"
				<< "6.\tПо жанру\n"
				<< "7.\tПо количеству страниц\n"
				<< "0.\tВернуться" << endl;
		variation = inputUnsignedInt(cin);
		list<Book> findListBooks;
		list<Book>::iterator begin = ListBooks->begin();
		list<Book>::iterator end = ListBooks->end();
		string str;
		switch (variation) {
		case 1:
			system("cls");
			unsigned int BookId;
			cout << "Введите идентификатор для поиска нужной записи" << endl;
			BookId = inputUnsignedInt(cin);
			while (true) {
				begin = ServiceBooks::findBookById(begin,end,BookId);
				if (begin == end)
					break;
				findListBooks.push_back(*begin);
				begin++;
			}
			if (findListBooks.size() != 0) {
				showList(findListBooks);
				cin.get();
			} else
				showNotFindData();
			break;
		case 2:
			system("cls");
			cout
					<< "Введите автора (начало/конец/часть автора) для поиска нужной записи"
					<< endl;
			str = inputString(cin);
			while (true) {
				begin = ServiceBooks::findBookByAuthor(begin,end,str);
				if (begin == end)
					break;
				findListBooks.push_back(*begin);
				begin++;
			}
			if (findListBooks.size() != 0) {
				showList(findListBooks);
				cin.get();
			} else
				showNotFindData();
			break;
		case 3:
			system("cls");
			cout
					<< "Введите название (начало/конец/часть названия) для поиска нужной записи"
					<< endl;
			str = inputString(cin);
			while (true) {
				begin = ServiceBooks::findBookByTitle(begin,end,str);
				if (begin == end)
					break;
				findListBooks.push_back(*begin);
				begin++;
			}
			if (findListBooks.size() != 0) {
				showList(findListBooks);
				cin.get();
			} else
				showNotFindData();
			break;
		case 5:
			system("cls");
			cout
					<< "Введите издательство (начало/конец/часть издательства) для поиска нужной записи"
					<< endl;
			str = inputString(cin);
			while (true) {
				begin = ServiceBooks::findBookByPublishingHouse(begin,end,str);
				if (begin == end)
					break;
				findListBooks.push_back(*begin);
				begin++;
			}
			if (findListBooks.size() != 0) {
				showList(findListBooks);
				cin.get();
			} else
				showNotFindData();
			break;
		case 6:
			system("cls");
			cout
					<< "Введите жанр (начало/конец/часть жанра) для поиска нужной записи"
					<< endl;
			str = inputString(cin);
			while (true) {
				begin = ServiceBooks::findBookByGenre(begin,end,str);
				if (begin == end)
					break;
				findListBooks.push_back(*begin);
				begin++;
			}
			if (findListBooks.size() != 0) {
				showList(findListBooks);
				cin.get();
			} else
				showNotFindData();
			break;
		case 7:
			system("cls");
			unsigned int numberOfPages;
			cout
					<< "Введите количество страниц для поиска нужной записи"
					<< endl;
			numberOfPages = inputUnsignedInt(cin);
			while (true) {
				begin = ServiceBooks::findBookByNumberOfPages(begin,end,numberOfPages);
				if (begin == end)
					break;
				findListBooks.push_back(*begin);
				begin++;
			}
			if (findListBooks.size() != 0) {
				showList(findListBooks);
				cin.get();
			} else
				showNotFindData();
			break;
		case 0:
			break;
		default:
			showExceptionScreen();
		}
		if (variation == 0)
			break;
		cin.get();
	}
}
