/*
 * UserScreen.cpp
 *
 *  Created on: 13 ����. 2017 �.
 *      Author: �������
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
		cout<<"1.\t���������� �� �����������/�-�\n"
				<<"2.\t���������� �� ��������/�-�\n"
				<<"3.\t�����\n"
				<<"4.\t������� ������ ���� � ��������� ������� � ���������� �������, �������� ����� ��������� ���� \n"
				<<"0.\t�����"
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
	cout << "1.\t�� ��������������\n" << "2.\t�� ������\n"
			<< "3.\t�� ��������\n"
			<< "4.\t�� ���� �������\n"
			<< "5.\t�� ������������\n"
			<< "6.\t�� �����\n"
			<< "7.\t�� ���������� �������\n"
			<< "0.\t���������" << endl;
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
	cout << "1.\t�� ��������������\n" << "2.\t�� ������\n"
			<< "3.\t�� ��������\n"
			<< "4.\t�� ���� �������\n"
			<< "5.\t�� ������������\n"
			<< "6.\t�� �����\n"
			<< "7.\t�� ���������� �������\n"
			<< "0.\t���������" << endl;
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
		cout << "1.\t�� ��������������\n" << "2.\t�� ������\n"
				<< "3.\t�� ��������\n"
				<< "4.\t�� ���� �������\n"
				<< "5.\t�� ������������\n"
				<< "6.\t�� �����\n"
				<< "7.\t�� ���������� �������\n"
				<< "0.\t���������" << endl;
		variation = inputUnsignedInt(cin);
		list<Book> findListBooks;
		list<Book>::iterator begin = ListBooks->begin();
		list<Book>::iterator end = ListBooks->end();
		string str;
		switch (variation) {
		case 1:
			system("cls");
			unsigned int BookId;
			cout << "������� ������������� ��� ������ ������ ������" << endl;
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
					<< "������� ������ (������/�����/����� ������) ��� ������ ������ ������"
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
					<< "������� �������� (������/�����/����� ��������) ��� ������ ������ ������"
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
					<< "������� ������������ (������/�����/����� ������������) ��� ������ ������ ������"
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
					<< "������� ���� (������/�����/����� �����) ��� ������ ������ ������"
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
					<< "������� ���������� ������� ��� ������ ������ ������"
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
