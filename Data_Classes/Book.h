/*
 * Book.h
 *
 *  Created on: 28 íîÿá. 2017 ã.
 *      Author: Äìèòðèé
 */

#ifndef DATA_CLASSES_BOOK_H_
#define DATA_CLASSES_BOOK_H_
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <Windows.h>
#include "Date.h"
#include "../Ñontrollers/ControllerIStream.h"
using namespace std;

class Book {
private:
	unsigned int id;
	string author;
	string title;
	Date publishingYear;
	string publishingHouse;
	string genre;
	unsigned int numberOfPages;
public:
	static const string PATH_BOOKS;
	Book();
	Book(unsigned int, string, string, Date, string, string, unsigned int);
	Book(const Book&);
	~Book();
	const string& getAuthor() const;
	void setAuthor(const string& author);
	const string& getGenre() const;
	void setGenre(const string& genre);
	unsigned int getId() const;
	void setId(unsigned int id);
	unsigned int getNumberOfPages() const;
	void setNumberOfPages(unsigned int numberOfPages);
	const string& getPublishingHouse() const;
	void setPublishingHouse(const string& publishingHouse);
	Date& getPublishingYear();
	void setPublishingYear(const Date& publishingYear);
	const string& getTitle() const;
	void setTitle(const string& title);
	Book& operator=(const Book&);
	friend bool operator<(const Book&, const Book&);
	friend bool operator==(const Book&, const Book&);
	friend ostream& operator<<(ostream&, Book&);
	friend istream& operator>>(istream&, Book&);
	friend ofstream& operator<<(ofstream&, Book&);
	friend ifstream& operator>>(ifstream&, Book&);
};

#endif /* DATA_CLASSES_BOOK_H_ */
