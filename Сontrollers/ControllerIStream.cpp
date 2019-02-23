/*
 * ControllerIStream.cpp
 *
 *  Created on: 13 ����. 2017 �.
 *      Author: �������
 */

#include "ControllerIStream.h"

string inputString(istream& stream){
	string str;
	cout<<">> ";
	stream>>str;
	return str;
}

string inputLine(istream& stream){
	string str;
	cout<<">> ";
	stream.get();
	getline(stream,str);
	return str;
}

unsigned int inputUnsignedInt(istream& stream){
	return atoi(inputString(stream).c_str());
}

short int inputShortInt(istream& stream){
	return atoi(inputString(stream).c_str());
}
