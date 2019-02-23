/*
 * AdministratorScreen.cpp
 *
 *  Created on: 13 нояб. 2017 г.
 *      Author: Дмитрий
 */

#include "AdministratorScreen.h"

bool AdministratorScreen::created = false;

AdministratorScreen::AdministratorScreen(list<UserAccount> &ListUserAccounts,
		list<Book> &ListBooks) {
	this->ListUserAccounts = &ListUserAccounts;
	this->ListBooks = &ListBooks;
	this->created = true;
	this->ListFreeUserId = readFile(ServiceUserAccounts::PATH_FREE_USERID,
			ListFreeUserId);
	this->ListFreeBookId = readFile(ServiceBooks::PATH_FREE_BOOKID,
			ListFreeBookId);
}

AdministratorScreen::~AdministratorScreen() {
}

AdministratorScreen& AdministratorScreen::instance(
		list<UserAccount> &ListUserAccounts, list<Book> &ListBooks) {
	static AdministratorScreen *inst;
	if (!created)
		inst = new AdministratorScreen(ListUserAccounts, ListBooks);
	return *inst;
}

void AdministratorScreen::showAdministratorScreen() {
	unsigned int variation;
	while (true) {
		system("cls");
		cout << "1.\tУчетные записи пользователей\n"
				<< "2.\tКниги\n" << "3.\tСохранение изменений\n"
				<< "0.\tВыйти" << endl;
		variation = inputUnsignedInt(cin);
		switch (variation) {
		case 1:
			accountManagementMenu();
			break;
		case 2:
			bookManagementMenu();
			break;
		case 3:
			ListUserAccounts->sort(
					ServiceUserAccounts::compUserAccountByUserId);
			ListBooks->sort(ServiceBooks::compBookById);
			writeFile(UserAccount::PATH_USER_ACCOUNTS, *ListUserAccounts);
			writeFile(Book::PATH_BOOKS, *ListBooks);
			writeFile(ServiceUserAccounts::PATH_FREE_USERID, ListFreeUserId);
			writeFile(ServiceBooks::PATH_FREE_BOOKID, ListFreeBookId);
			*ListUserAccounts = readFile(UserAccount::PATH_USER_ACCOUNTS,
					*ListUserAccounts);
			*ListBooks = readFile(Book::PATH_BOOKS, *ListBooks);
			ListFreeUserId = readFile(ServiceUserAccounts::PATH_FREE_USERID,
					ListFreeUserId);
			ListFreeBookId = readFile(ServiceBooks::PATH_FREE_BOOKID,
					ListFreeBookId);
			cout << "Изменения сохранены" << endl;
			fflush(stdin);
			cin.get();
			break;
		case 0:
			ListUserAccounts->sort(
					ServiceUserAccounts::compUserAccountByUserId);
			ListBooks->sort(ServiceBooks::compBookById);
			break;
		default:
			showExceptionScreen();
		}
		if (variation == 0)
			break;
	}
}

void AdministratorScreen::accountManagementMenu() {
	unsigned int variation;
	while (true) {
		system("cls");
		showList(*ListUserAccounts);
		cout << "1.\tДобавить учетную запись пользователя\n"
				<< "2.\tРедактировать учетную запись пользователя\n"
				<< "3.\tУдаление учетной записи пользователя\n"
				<< "4.\tУдаление всех учетных записей пользователей\n"
				<< "5.\tСортировка по возрастанию/А-Я\n"
				<< "6.\tСортировка по убыванию/Я-А\n" << "7.\tПоиск\n"
				<< "0.\tВернуться" << endl;
		variation = inputUnsignedInt(cin);
		switch (variation) {
		case 1:
			ServiceUserAccounts::addUserAccount(*ListUserAccounts, ListFreeUserId);
			break;
		case 2:
			editingUserAccountMenu();
			break;
		case 3:
			ServiceUserAccounts::deleteUserAccount(*ListUserAccounts, ListFreeUserId);
			break;
		case 4:
			ServiceUserAccounts::deleteAllUserAccounts(
					*ListUserAccounts, ListFreeUserId);
			break;
		case 5:
			sortInAscendingOrderUserAccountsMenu();
			break;
		case 6:
			sortInDecreasingOrderUserAccountsMenu();
			break;
		case 7:
			findUserAccountMenu();
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

void AdministratorScreen::bookManagementMenu() {
	unsigned int variation;
	while (true) {
		system("cls");
		showList(*ListBooks);
		cout << "1.\tДобавить книги\n" << "2.\tРедактировать книги\n"
				<< "3.\tУдаление книги\n" << "4.\tУдаление всех книг\n"
				<< "5.\tСортировка по возрастанию/А-Я\n"
				<< "6.\tСортировка по убыванию/Я-А\n" << "7.\tПоиск\n"
				<< "8.\tВывести список книг с фамилиями авторов в алфавитном порядке, изданных после заданного года\n"
				<< "0.\tВернуться" << endl;
		variation = inputUnsignedInt(cin);
		switch (variation) {
		case 1:
			ServiceBooks::addBook(*ListBooks, ListFreeBookId);
			break;
		case 2:
			editingBookMenu();
			break;
		case 3:
			ServiceBooks::deleteBook(*ListBooks, ListFreeBookId);
			break;
		case 4:
			ServiceBooks::deleteAllBook(*ListBooks, ListFreeBookId);
			break;
		case 5:
			sortInAscendingOrderBooksMenu();
			break;
		case 6:
			sortInDecreasingOrderBooksMenu();
			break;
		case 7:
			findBookMenu();
			break;
		case 8:
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

void AdministratorScreen::editingUserAccountMenu() {
	system("cls");
	cout
			<< "Введите индентификатор пользователя, данные которого необходимо изменить"
			<< endl;
	unsigned int inputUserId = inputUnsignedInt(cin);
	ListUserAccounts->sort(ServiceUserAccounts::compUserAccountByUserId);
	list<UserAccount>::iterator findUserAccount =
			ServiceUserAccounts::findUserAccountByUserId(
					ListUserAccounts->begin(), ListUserAccounts->end(),
					inputUserId);
	if (findUserAccount != ListUserAccounts->end()) {
		cout
				<< "Подтвердите редактирование этой учетной записи пользователя (пароль)\n"
				<< (*findUserAccount) << endl;
		string passwordAccount(inputString(cin));
		if (HashPasswordWithSal()(passwordAccount,
				(*findUserAccount).getSurname())
				== (*findUserAccount).getPassword()) {
			unsigned int variation;
			while (true) {
				system("cls");
				cout << (*findUserAccount) << endl;
				cout << "1.\tФамилию Имя Отчество учетной записи пользователя\n"
						<< "2.\tОтдел учетной записи пользователя\n"
						<< "3.\tПароль учетной записи пользователя\n"
						<< "4.\tВсе данные об учетной записи пользователя\n"
						<< "0.\tВернуться" << endl;
				variation = inputUnsignedInt(cin);
				switch (variation) {
				case 1:
					ServiceUserAccounts::editingSNMUserAccount(findUserAccount,
							passwordAccount);
					ListUserAccounts->sort();
					break;
				case 2:
					ServiceUserAccounts::editingDepartmentUserAccount(
							findUserAccount);

					break;
				case 3:
					ServiceUserAccounts::editingPasswordUserAccount(
							findUserAccount, passwordAccount);
					break;
				case 4:
					ServiceUserAccounts::editingAllDataUserAccount(
							findUserAccount);
					ListUserAccounts->sort();
					break;
				case 0:
					break;
				default:
					showExceptionScreen();
				}
				if (variation == 0)
					break;
			}
		} else
			showExceptionScreen();
	} else
		showNotFindData();
}

void AdministratorScreen::editingBookMenu() {
	system("cls");
	cout << "Введите индентификатор книги, данные которого необходимо изменить"
			<< endl;
	unsigned int inputBookId = inputUnsignedInt(cin);
	ListBooks->sort(ServiceBooks::compBookById);
	list<Book>::iterator findBook = ServiceBooks::findBookById(
			ListBooks->begin(), ListBooks->end(), inputBookId);
	list<UserAccount>::iterator activeAccount = (*ListUserAccounts).begin();
	if (findBook != ListBooks->end()) {
		cout << "Подтвердите редактирование этой книги(да/нет)\n"
				<< (*findBook) << endl;
		string confirmation(inputString(cin));
		if (confirmation == "да") {
			unsigned int variation;
			while (true) {
				system("cls");
				cout << (*findBook) << endl;
				cout << "1.\tАвтор\n"
						<< "2.\tНазвание\n"
						<< "3.\tГод издания\n"
						<< "4.\tИздательство\n" << "5.\tЖанр\n"
						<< "6.\tКоличество страниц\n" << "0.\tВернуться"
						<< endl;
				variation = inputUnsignedInt(cin);
				switch (variation) {
				case 1:
					ServiceBooks::editingAuthorBook(findBook);
					break;
				case 2:
					ServiceBooks::editingTitleBook(findBook);
					break;
				case 3:
					ServiceBooks::editingPublishingYearBook(findBook);
					break;
				case 4:
					ServiceBooks::editingPublishingHouseBook(findBook);
					break;
				case 5:
					ServiceBooks::editingGenreBook(findBook);
					break;
				case 6:
					ServiceBooks::editingNumberOfPagesBook(findBook);
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
		if (confirmation != "да" && confirmation != "нет")
			showExceptionScreen();
	} else
		showNotFindData();
}

void AdministratorScreen::sortInAscendingOrderUserAccountsMenu() {
	unsigned int variation;
	system("cls");
	cout << "1.\tПо идентификатору\n" << "2.\tПо фамилии\n" << "3.\tПо имени\n"
			<< "4.\tПо отчеству\n" << "5.\tПо отделам\n" << "0.\tВернуться"
			<< endl;
	variation = inputUnsignedInt(cin);
	switch (variation) {
	case 1:
		ListUserAccounts->sort(ServiceUserAccounts::compUserAccountByUserId);
		break;
	case 2:
		ListUserAccounts->sort();
		break;
	case 3:
		ListUserAccounts->sort(ServiceUserAccounts::compUserAccountByName);
		break;
	case 4:
		ListUserAccounts->sort(ServiceUserAccounts::compUserAccountByMidname);
		break;
	case 5:
		ListUserAccounts->sort(
				ServiceUserAccounts::compUserAccountByDepartment);
		break;
	case 0:
		break;
	default:
		showExceptionScreen();
	}
}

void AdministratorScreen::sortInAscendingOrderBooksMenu() {
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

void AdministratorScreen::sortInDecreasingOrderUserAccountsMenu() {
	unsigned int variation;
	system("cls");
	cout << "1.\tПо идентификатору\n" << "2.\tПо фамилии\n"
			<< "3.\tПо имени\n" << "4.\tПо отчеству\n" << "5.\tПо отделам\n"
			<< "0.\tВернуться" << endl;
	variation = inputUnsignedInt(cin);
	switch (variation) {
	case 1:
		ListUserAccounts->sort(
				ServiceUserAccounts::recompUserAccountByUserId);
		break;
	case 2:
		ListUserAccounts->sort(
				ServiceUserAccounts::recompUserAccountBySurname);
		break;
	case 3:
		ListUserAccounts->sort(
				ServiceUserAccounts::recompUserAccountByName);
		break;
	case 4:
		ListUserAccounts->sort(
				ServiceUserAccounts::recompUserAccountByMidname);
		break;
	case 5:
		ListUserAccounts->sort(
				ServiceUserAccounts::recompUserAccountByDepartment);
		break;
	case 0:
		break;
	default:
		showExceptionScreen();
	}
}

void AdministratorScreen::sortInDecreasingOrderBooksMenu(){
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

void AdministratorScreen::findUserAccountMenu() {
	unsigned int variation;
	while (true) {
		system("cls");
		cout << "1.\tПо идентификатору\n" << "2.\tПо фамилии\n"
				<< "3.\tПо имени\n" << "4.\tПо отчеству\n" << "5.\tПо отделам\n"
				<< "0.\tВернуться" << endl;
		variation = inputUnsignedInt(cin);
		list<UserAccount> findListUserAccounts;
		list<UserAccount>::iterator begin = ListUserAccounts->begin();
		list<UserAccount>::iterator end = ListUserAccounts->end();
		string str;
		switch (variation) {
		case 1:
			system("cls");
			unsigned int userId;
			cout << "Введите идентификатор для поиска нужной записи" << endl;
			userId = inputUnsignedInt(cin);
			while (true) {
				begin = ServiceUserAccounts::findUserAccountByUserId(begin, end,
						userId);
				if (begin == end)
					break;
				findListUserAccounts.push_back(*begin);
				begin++;
			}
			if (findListUserAccounts.size() != 0) {
				showList(findListUserAccounts);
				cin.get();
			} else
				showNotFindData();
			break;
		case 2:
			system("cls");
			cout
					<< "Введите фамилию (начало/конец/часть фамилии) для поиска нужной записи"
					<< endl;
			str = inputString(cin);
			while (true) {
				begin = ServiceUserAccounts::findUserAccountBySurname(begin,
						end, str);
				if (begin == end)
					break;
				findListUserAccounts.push_back(*begin);
				begin++;
			}
			if (findListUserAccounts.size() != 0) {
				showList(findListUserAccounts);
				cin.get();
			} else
				showNotFindData();
			break;
		case 3:
			system("cls");
			cout
					<< "Введите имя (начало/конец/часть имени) для поиска нужной записи"
					<< endl;
			str = inputString(cin);
			while (true) {
				begin = ServiceUserAccounts::findUserAccountByName(begin, end,
						str);
				if (begin == end)
					break;
				findListUserAccounts.push_back(*begin);
				begin++;
			}
			if (findListUserAccounts.size() != 0) {
				showList(findListUserAccounts);
				cin.get();
			} else
				showNotFindData();
			break;
		case 4:
			system("cls");
			cout
					<< "Введите отчество (начало/конец/часть отчества) для поиска нужной записи"
					<< endl;
			str = inputString(cin);
			while (true) {
				begin = ServiceUserAccounts::findUserAccountByMidname(begin,
						end, str);
				if (begin == end)
					break;
				findListUserAccounts.push_back(*begin);
				begin++;
			}
			if (findListUserAccounts.size() != 0) {
				showList(findListUserAccounts);
				cin.get();
			} else
				showNotFindData();
			break;
		case 5:
			system("cls");
			cout
					<< "Введите отдела (начало/конец/часть отдела) для поиска нужной записи"
					<< endl;
			str = inputString(cin);
			while (true) {
				begin = ServiceUserAccounts::findUserAccountByDepartment(begin,
						end, str);
				if (begin == end)
					break;
				findListUserAccounts.push_back(*begin);
				begin++;
			}
			if (findListUserAccounts.size() != 0) {
				showList(findListUserAccounts);
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

void AdministratorScreen::findBookMenu(){
	unsigned int variation;
	while (true) {
		system("cls");
		cout << "1.\tПо идентификатору\n" << "2.\tПо автору\n"
				<< "3.\tПо названию\n"
				<< "4.\tПо издательству\n"
				<< "5.\tПо жанру\n"
				<< "6.\tПо количеству страниц\n"
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
		case 4:
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
		case 5:
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
		case 6:
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
