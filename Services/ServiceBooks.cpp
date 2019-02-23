/*
 * ServiceBooks.cpp
 *
 *  Created on: 28 нояб. 2017 г.
 *      Author: Дмитрий
 */

#include "ServiceBooks.h"

const string ServiceBooks::PATH_FREE_BOOKID = "./Resources/FreeBookId.txt";

ServiceBooks::ServiceBooks() {

}

ServiceBooks::~ServiceBooks() {
}

bool ServiceBooks::compBookById(Book &first, Book &second) {
	return first.getId() < second.getId();
}
bool ServiceBooks::compBookByAuthor(Book &first, Book &second) {
	return (first.getAuthor().compare(second.getAuthor()) == -1 ? true : false);
}
bool ServiceBooks::compBookByTitle(Book &first, Book &second) {
	return (first.getTitle().compare(second.getTitle()) == -1 ? true : false);
}
bool ServiceBooks::compBookByPublishingYear(Book &first, Book &second) {
	return (first.getPublishingYear().comparisonDate(second.getPublishingYear())
			== -1 ? true : false);
}
bool ServiceBooks::compBookByPublishingHouse(Book &first, Book &second) {
	return (first.getPublishingHouse().compare(second.getPublishingHouse())
			== -1 ? true : false);
}
bool ServiceBooks::compBookByGenre(Book &first, Book &second) {
	return (first.getGenre().compare(second.getGenre()) == -1 ? true : false);
}
bool ServiceBooks::compBookByNumberOfPages(Book &first, Book &second) {
	return first.getNumberOfPages() < second.getNumberOfPages();
}

bool ServiceBooks::recompBookById(Book &first, Book &second) {
	return first.getId() > second.getId();
}
bool ServiceBooks::recompBookByAuthor(Book &first, Book &second) {
	return (first.getAuthor().compare(second.getAuthor()) == 1 ? true : false);
}
bool ServiceBooks::recompBookByTitle(Book &first, Book &second) {
	return (first.getTitle().compare(second.getTitle()) == 1 ? true : false);
}
bool ServiceBooks::recompBookByPublishingYear(Book &first, Book &second) {
	return (first.getPublishingYear().comparisonDate(second.getPublishingYear())
			== 1 ? true : false);
}
bool ServiceBooks::recompBookByPublishingHouse(Book &first, Book &second) {
	return (first.getPublishingHouse().compare(second.getPublishingHouse())
			== 1 ? true : false);
}
bool ServiceBooks::recompBookByGenre(Book &first, Book &second) {
	return (first.getGenre().compare(second.getGenre()) == 1 ? true : false);
}
bool ServiceBooks::recompBookByNumberOfPages(Book &first, Book &second) {
	return first.getNumberOfPages() > second.getNumberOfPages();
}

list<Book>::iterator ServiceBooks::findBookById(list<Book>::iterator begin,
		list<Book>::iterator end, unsigned int id) {
	for (; begin != end; begin++)
		if (to_string((*begin).getId()).find(to_string(id)) != string::npos)
			return begin;
	return end;
}

list<Book>::iterator ServiceBooks::findBookByAuthor(list<Book>::iterator begin,
		list<Book>::iterator end, string author) {
	for (; begin != end; begin++)
		if ((*begin).getAuthor().find(author) != string::npos)
			return begin;
	return end;
}

list<Book>::iterator ServiceBooks::findBookByTitle(list<Book>::iterator begin,
		list<Book>::iterator end, string title) {
	for (; begin != end; begin++)
		if ((*begin).getTitle().find(title) != string::npos)
			return begin;
	return end;
}

list<Book>::iterator ServiceBooks::findBookByPublishingYear(
		list<Book>::iterator begin, list<Book>::iterator end,
		Date publishingYear) {
	for (; begin != end; begin++)
		if ((*begin).getPublishingYear().comparisonDate(publishingYear) == 0)
			return begin;
	return end;
}

list<Book>::iterator ServiceBooks::findBookByPublishingHouse(
		list<Book>::iterator begin, list<Book>::iterator end,
		string publishingHouse) {
	for (; begin != end; begin++)
		if ((*begin).getPublishingHouse().find(publishingHouse) != string::npos)
			return begin;
	return end;
}

list<Book>::iterator ServiceBooks::findBookByGenre(list<Book>::iterator begin,
		list<Book>::iterator end, string genre) {
	for (; begin != end; begin++)
		if ((*begin).getGenre().find(genre) != string::npos)
			return begin;
	return end;
}

list<Book>::iterator ServiceBooks::findBookByNumberOfPages(
		list<Book>::iterator begin, list<Book>::iterator end,
		unsigned int numberOfPages) {
	for (; begin != end; begin++)
		if (to_string((*begin).getNumberOfPages()).find(
				to_string(numberOfPages)) != string::npos)
			return begin;
	return end;
}

void ServiceBooks::addBook(list<Book> &ListBooks,
		list<unsigned int> &ListFreeBookId) {
	system("cls");
	unsigned int maxBookIdInListNow = (*ListBooks.begin()).getId();
	if (ListFreeBookId.size() == 0) {
		for (Book t : ListBooks) {
			if (maxBookIdInListNow < t.getId())
				maxBookIdInListNow = t.getId();
		}
		maxBookIdInListNow++;
	} else {
		maxBookIdInListNow = *ListFreeBookId.begin();
		ListFreeBookId.pop_front();
	}
	Book newBook;
	newBook.setId(maxBookIdInListNow);
	cout << "Введите данные о новой книге c идентификатором " << newBook.getId()
			<< "\n" << endl;
	cin >> newBook;
	cout << "Подтвердите создание новой записи в библиотеке (да/нет)" << endl;
	cout << newBook << endl;
	string confirmation(inputString(cin));
	if (confirmation == "да")
		ListBooks.push_back(newBook);
	if (confirmation != "да" && confirmation != "нет")
		showExceptionScreen();
}

void ServiceBooks::editingAuthorBook(list<Book>::iterator &findBook) {
	cout << "Автор" << endl;
	(*findBook).setAuthor(inputLine(cin));
}

void ServiceBooks::editingTitleBook(list<Book>::iterator &findBook) {
	cout << "Название книги" << endl;
	(*findBook).setAuthor(inputLine(cin));
}

void ServiceBooks::editingPublishingYearBook(list<Book>::iterator &findBook) {
	cout << "Год издания" << endl;
	Date publishingYear;
	cin >> publishingYear;
	(*findBook).setPublishingYear(publishingYear);
}

void ServiceBooks::editingPublishingHouseBook(list<Book>::iterator &findBook) {
	cout << "Издательство" << endl;
	(*findBook).setPublishingHouse(inputLine(cin));
}

void ServiceBooks::editingGenreBook(list<Book>::iterator &findBook) {
	cout << "Жанр" << endl;
	(*findBook).setGenre(inputLine(cin));
}

void ServiceBooks::editingNumberOfPagesBook(list<Book>::iterator &findBook) {
	cout << "Количество страниц" << endl;
	(*findBook).setNumberOfPages(inputUnsignedInt(cin));
}

void ServiceBooks::deleteBookByIterator(list<Book> &ListBooks,
		list<Book>::iterator &findBook, list<unsigned int> &ListFreeBookId) {
	ListFreeBookId.push_back((*findBook).getId());
	ListBooks.remove((*findBook));
}

void ServiceBooks::deleteBook(list<Book> &ListBooks,
		list<unsigned int> &ListFreeBookId) {
	system("cls");
	cout << "ВВедите индентификатор книги, данные которого необходимо удалить"
			<< endl;
	unsigned int inputBookId = inputUnsignedInt(cin);
	ListBooks.sort(ServiceBooks::compBookById);
	list<Book>::iterator findBook = ServiceBooks::findBookById(
			ListBooks.begin(), ListBooks.end(), inputBookId);
	if (findBook != ListBooks.end()) {
		cout
				<< "Подтвердите удаление книги(да/нет)"
				<< endl;
		cout << (*findBook) << endl;
		string confirmation(inputString(cin));
		if (confirmation == "да") {
			ServiceBooks::deleteBookByIterator(ListBooks, findBook,
					ListFreeBookId);
		}
		if (confirmation != "да" && confirmation != "нет")
			showExceptionScreen();
	} else {
		showNotFindData();
	}
}

void ServiceBooks::deleteAllBook(list<Book> &ListBooks,
		list<unsigned int> &ListFreeBookId) {
	cout
			<< "Подтвердите удаление всех книг(да/нет)"
			<< endl;
	string confirmation(inputString(cin));
	if (confirmation == "да") {
		while (true) {
			list<Book>::iterator begin = ListBooks.begin();
			list<Book>::iterator end = ListBooks.end();
			if (begin == end)
				break;
			ServiceBooks::deleteBookByIterator(ListBooks, begin,
					ListFreeBookId);
		}
	}
	if (confirmation != "да" && confirmation != "нет")
		showExceptionScreen();
}

void ServiceBooks::showListBookByPublishingYear(list<Book> &ListBooks) {
	cout
			<< "Введите год, для поиска книг, которые были выпущенны после этого года"
			<< endl;
	short int inputyYear;
	bool findData = false;
	inputyYear = inputShortInt(cin);
	system("cls");
	ListBooks.sort(ServiceBooks::compBookByAuthor);
	for (Book b : ListBooks)
		if (b.getPublishingYear().getYear() >= inputyYear) {
			cout << b << endl;
			findData = true;
		}
	if (!findData)
		showNotFindData();
}
