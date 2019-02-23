/*
 * Book.cpp
 *
 *  Created on: 28 нояб. 2017 г.
 *      Author: Дмитрий
 */

#include "Book.h"

const string Book::PATH_BOOKS = "./Resources/Books.txt";

Book::Book() :
		id(0), author(""), title(""), publishingYear(), publishingHouse(""), genre(
				""), numberOfPages(0) {
}

Book::Book(unsigned int id, string author, string title, Date publishingYear,
		string publishingHouse, string genre, unsigned int numberOfPages) :
		id(id), author(author), title(title), publishingYear(publishingYear), publishingHouse(
				publishingHouse), genre(genre), numberOfPages(numberOfPages) {
}

Book::Book(const Book& obj) :
		id(obj.id), author(obj.author), title(obj.title), publishingYear(
				obj.publishingYear), publishingHouse(obj.publishingHouse), genre(
				obj.genre), numberOfPages(obj.numberOfPages) {
}

Book::~Book() {
}

const string& Book::getAuthor() const {
	return author;
}

void Book::setAuthor(const string& author) {
	this->author = author;
}

const string& Book::getGenre() const {
	return genre;
}

void Book::setGenre(const string& genre) {
	this->genre = genre;
}

unsigned int Book::getId() const {
	return id;
}

void Book::setId(unsigned int id) {
	this->id = id;
}

unsigned int Book::getNumberOfPages() const {
	return numberOfPages;
}

void Book::setNumberOfPages(unsigned int numberOfPages) {
	this->numberOfPages = numberOfPages;
}

const string& Book::getPublishingHouse() const {
	return publishingHouse;
}

void Book::setPublishingHouse(const string& publishingHouse) {
	this->publishingHouse = publishingHouse;
}

Date& Book::getPublishingYear(){
	return publishingYear;
}

void Book::setPublishingYear(const Date& publishingYear) {
	this->publishingYear = publishingYear;
}

const string& Book::getTitle() const {
	return title;
}

void Book::setTitle(const string& title) {
	this->title = title;
}
Book& Book::operator=(const Book& obj) {
	this->author = obj.author;
	this->genre = obj.genre;
	this->title = obj.title;
	this->id = obj.id;
	this->numberOfPages = obj.numberOfPages;
	this->publishingHouse = obj.publishingHouse;
	this->publishingYear = obj.publishingYear;
	return *this;
}

bool operator<(const Book& first, const Book& second) {
	return first.id < second.id;
}

bool operator==(const Book& first, const Book& second) {
	return first.id == second.id;
}

ostream& operator<<(ostream& stream, Book& obj) {
	stream << "Регистрационный номер книги: " << obj.id << "\n" << "Автор: "
			<< obj.author << "\n" << "Название: " << obj.title << "\n"
			<< "Год издания: " << obj.publishingYear << "\n" << "Издательство: "
			<< obj.publishingHouse << "\n" << "Жанр: " << obj.genre << "\n"
			<< "Количество страниц: " << obj.numberOfPages << "\n";
	return stream;
}

istream& operator>>(istream& stream, Book& obj) {
	cout << "Автор: \n";
	obj.author = inputLine(stream);
	cout << "Название: \n";
	obj.title = inputLine(stream);
	cout << "Год издания: \n";
	stream >> obj.publishingYear;
	cout << "Издательство: \n";
	obj.publishingHouse = inputLine(stream);
	cout << "Жанр: \n";
	obj.genre = inputLine(stream);
	cout << "Количество страниц: \n";
	obj.numberOfPages = inputUnsignedInt(stream);
	return stream;
}

ofstream& operator<<(ofstream& stream, Book& obj) {
	stream << obj.id << " " << obj.author.length() << " " << obj.author << " "
			<< obj.title.length() << " " << obj.title << " "
			<< obj.publishingYear << " " << obj.publishingHouse.length() << " "
			<< obj.publishingHouse << " " << obj.genre.length() << " "
			<< obj.genre << " " << obj.numberOfPages;
	return stream;
}

ifstream& operator>>(ifstream& stream, Book& obj) {
	size_t length;
	stream >> obj.id >> length;
	stream.get();
	obj.author.clear();
	for (size_t i = 0; i < length; i++) {
		obj.author += stream.get();
	}
	stream >> length;
	stream.get();
	obj.title.clear();
	for (size_t i = 0; i < length; i++) {
		obj.title += stream.get();
	}
	stream >> obj.publishingYear;
	stream >> length;
	stream.get();
	obj.publishingHouse.clear();
	for (size_t i = 0; i < length; i++) {
		obj.publishingHouse += stream.get();
	}
	stream >> length;
	stream.get();
	obj.genre.clear();
	for (size_t i = 0; i < length; i++) {
		obj.genre += stream.get();
	}
	obj.numberOfPages = inputUnsignedInt(stream);
	return stream;
}
