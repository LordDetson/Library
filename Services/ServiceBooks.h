/*
 * ServiceBooks.h
 *
 *  Created on: 28 íîÿá. 2017 ã.
 *      Author: Äìèòðèé
 */

#ifndef SERVICES_SERVICEBOOKS_H_
#define SERVICES_SERVICEBOOKS_H_
#include <iostream>
#include <list>
#include "../Data_Classes/Book.h"
#include "../Ñontrollers/ControllerIOFStream.h"
#include "../Ñontrollers/ControllerIOFStream.h"
#include "../Screens/ExceptionScreen.h"
using namespace std;

class ServiceBooks {
	ServiceBooks();
	ServiceBooks(const ServiceBooks&);
	~ServiceBooks();
	ServiceBooks& operator=(const ServiceBooks&);
public:
	static const string PATH_FREE_BOOKID;

	static bool compBookById(Book&, Book&);
	static bool compBookByAuthor(Book&, Book&);
	static bool compBookByTitle(Book&, Book&);
	static bool compBookByPublishingYear(Book&, Book&);
	static bool compBookByPublishingHouse(Book&, Book&);
	static bool compBookByGenre(Book&, Book&);
	static bool compBookByNumberOfPages(Book&, Book&);

	static bool recompBookById(Book&, Book&);
	static bool recompBookByAuthor(Book&, Book&);
	static bool recompBookByTitle(Book&, Book&);
	static bool recompBookByPublishingYear(Book&, Book&);
	static bool recompBookByPublishingHouse(Book&, Book&);
	static bool recompBookByGenre(Book&, Book&);
	static bool recompBookByNumberOfPages(Book&, Book&);

	static list<Book>::iterator findBookById(list<Book>::iterator begin,
			list<Book>::iterator end, unsigned int id);
	static list<Book>::iterator findBookByAuthor(list<Book>::iterator begin,
			list<Book>::iterator end, string author);
	static list<Book>::iterator findBookByTitle(list<Book>::iterator begin,
			list<Book>::iterator end, string title);
	static list<Book>::iterator findBookByPublishingYear(
			list<Book>::iterator begin, list<Book>::iterator end,
			Date publishingYear);
	static list<Book>::iterator findBookByPublishingHouse(
			list<Book>::iterator begin, list<Book>::iterator end,
			string publishingHouse);
	static list<Book>::iterator findBookByGenre(list<Book>::iterator begin,
			list<Book>::iterator end, string genre);
	static list<Book>::iterator findBookByNumberOfPages(
			list<Book>::iterator begin, list<Book>::iterator end,
			unsigned int numberOfPages);

	static void addBook(list<Book>&, list<unsigned int>&);
	static void editingAuthorBook(list<Book>::iterator&);
	static void editingTitleBook(list<Book>::iterator&);
	static void editingPublishingYearBook(list<Book>::iterator&);
	static void editingPublishingHouseBook(list<Book>::iterator&);
	static void editingGenreBook(list<Book>::iterator&);
	static void editingNumberOfPagesBook(list<Book>::iterator&);

	static void deleteBookByIterator(list<Book>&, list<Book>::iterator&,
			list<unsigned int>&);
	static void deleteBook(list<Book>&, list<unsigned int>&);
	static void deleteAllBook(list<Book>&, list<unsigned int>&);

	static void showListBookByPublishingYear(list<Book>&);

};

#endif /* SERVICES_SERVICEBOOKS_H_ */
