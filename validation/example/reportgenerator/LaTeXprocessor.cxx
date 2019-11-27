/*
 * LaTeXprocessor.cxx
 *
 *  Created on: Sep 21, 2010
 *      Author: fraenkle
 */

#include "LaTeXprocessor.h"
#include <fstream>
#include <iostream>

using namespace std;

LaTeXprocessor::LaTeXprocessor(){

	latexstring = "";
	tokenposition = 0;

}

LaTeXprocessor::LaTeXprocessor(string filename){

	ifstream inputfile;
	string s;

	latexstring = "";
	tokenposition = 0;
	inputfile.open(filename.c_str());
	if(inputfile.fail()){
		cout << "(LaTeXprocessor:) ERROR! Can't open file \"" << filename << "\"\n";
	}
	while(getline(inputfile,s)){
		latexstring += s;
		latexstring += "\n";
	}
	inputfile.close();
}

int LaTeXprocessor::ReadTemplate(string filename){

	ifstream inputfile;
	string s;

	latexstring = "";
	inputfile.open(filename.c_str());
	if(inputfile.fail()){
		cout << "(LaTeXprocessor:) ERROR! Can't open file \"" << filename << "\"\n";
		return inputfile.fail();
	}
	while(getline(inputfile,s)){
		latexstring += s;
		latexstring += "\n";
	}
	inputfile.close();

	return 0;
}

void LaTeXprocessor::WriteReport(string filename){

	ofstream outputfile;

	outputfile.open(filename.c_str());
	outputfile << latexstring;
	outputfile.close();
}

int LaTeXprocessor::GetTokenNumber(){

	int tokennumber = 0;
	size_t position = 0;

	// search for tokens
	do{
		position = latexstring.find("XX:",position);
		if(position != string::npos){
			tokennumber++;
			position += 1;
		}
		else
			break;
	}while(1);

	return tokennumber;
}

string LaTeXprocessor::GetToken(){

	string token;
	size_t endposition;

	tokenposition = latexstring.find("XX:",tokenposition);
	if(tokenposition != (int)(string::npos)){
		endposition = latexstring.find(":XX",tokenposition+1);
		token = latexstring.substr(tokenposition,endposition+3-tokenposition);
		return token;
	}
	else
		return "";
}

void LaTeXprocessor::ReplaceToken(string textvalue){

	size_t endposition;

	endposition = latexstring.find(":XX",tokenposition+1);
	endposition += 3;
	latexstring.replace(tokenposition,endposition-tokenposition,textvalue);
}

void LaTeXprocessor::PrintLatexString(){

	cout << latexstring;

}

LaTeXprocessor::~LaTeXprocessor() {

}
