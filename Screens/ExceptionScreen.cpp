/*
 * ExceptionScreen.cpp
 *
 *  Created on: 13 МНЪА. 2017 Ц.
 *      Author: дЛХРПХИ
 */

#include "ExceptionScreen.h"

void showExceptionScreen(){
	system("cls");
	cout<<"ньхайю ббндю дюммшу! онопнасире еые пюг!"<<endl;
	fflush(stdin);
	cin.get();
}

void showNotFindData(){
	system("cls");
	cout<<"он бюьелс гюопняс дюммшу ме ясыеярбсер! онопнасире еые пюг!"<<endl;
	fflush(stdin);
	cin.get();
}

void showNotData(){
	system("cls");
	cout<<"дюммшу мер б аюге дюммшу! мер бнглнфмнярх люмхоскъжхи!"<<endl;
	fflush(stdin);
	cin.get();
}

void showNotFindUserId(unsigned int UserId){
	system("cls");
	cout<<"онкэгнбюрекъ я рюйхл ID = " << UserId << " мер б аюге дюммшу!"<<endl;
	fflush(stdin);
	cin.get();
}
