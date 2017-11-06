/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ahmed
 *
 * Created on November 6, 2017, 7:22 PM
 */

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "BinaryTree.cpp"

using namespace std;

stack<string> tokens;
ifstream input;
int line = 1;

binaryTree<string, string> bst;

void statement();
void expression();
void compoundstmt();

void scan(){
	char ch;
	string token;
	input.get(ch);

	while(((ch == ' ') || (ch == '\n')) && (!input.eof()))
	{
		if(ch == '\n')
			line++;
		input.get(ch);
	}

	while((ch != ' ') && (ch != '\n') && (!input.eof()))
	{
		token += ch;
		input.get(ch);
	}

	if(token!="")
		tokens.push(token);
	if(ch == '\n')
		line++;
}

void error(string token, string exp, int line){
	cout << "\n\nError\n\tLine:\t" << line << "\n\tExpected:\t" << exp << "\n\tFound:\t" << token << "\n"; 
	exit(0);
}

void match(string s){

	if(tokens.top() == s)
	{
		cout << tokens.top() << " ";
		bst.insert(s,"");
		scan();  
	} else
		error(tokens.top(), s, line);
}

void typespecifier(){
	if(tokens.top() =="int")
	{
		match("int");
	}
	else if(tokens.top() =="float")
	{
		match("float");
	}
	else if(tokens.top() =="void")
	{
		match("void");
	}
	else
	{
		error(tokens.top(), "int | float | void", line);
	}
}

void param(){
	typespecifier();
	match("id");
	if(tokens.top() == "[")
	{
		match("[");
		match("]");
	}
}

void paramlist(){
	param();
	while(tokens.top() == ",")
	{
		match(",");
		param();
	}
}

void params(){
	if(tokens.top() == "void")
		match("void");
	if(tokens.top() == "int" || tokens.top() == "float")
		paramlist();
}

void vardeclarationtail(){
	if(tokens.top() == ";")
		match(";");
	else if(tokens.top() == "[")
	{
		match("[");
		match("num");
		match("]");
		match(";");
	} else 
		error(tokens.top(), "; | [", line);
}

void vardeclaration(){
	typespecifier();
	match("id");
	vardeclarationtail();
}

void declarationlist(){
	vardeclaration();
	if(tokens.top() == "int" || tokens.top() == "float" || tokens.top() == "void")
		vardeclaration();
}

void selectionstmttail(){
	if(tokens.top() =="else")
	{
		match("else");
		statement();
	}
	else if(tokens.top() == "}" || tokens.top() == "else" ||tokens.top() == ";" )
	{
		return;
	}
	else
	{
		error(tokens.top(), "else | }", line);
	}
}

void multop(){
	if(tokens.top() =="multop")
	{
		match("multop");
	}
	else if(tokens.top() =="backslashop")
	{
		match("backslashop");
	}
	else
	{
		error(tokens.top(), "multop | backslashop", line);
	}
}

void vartail(){

	if(tokens.top() =="[")
	{
		match("[");
        expression();
		match("]");

	}
	else if(tokens.top() =="assign" || tokens.top() =="multop" || tokens.top() =="backslashop" || tokens.top() =="addop" || tokens.top() =="subop" || tokens.top() =="relop" || tokens.top() ==";")
	{
		return;
	}
	else
	{
		error(tokens.top(), "Var Tail", line);
	}
}

void var(){

	match("id");
	vartail();
}

void factor(){
	if(tokens.top() == "(")
	{
		match("(");
		expression();
		match(")");
	}
	else if(tokens.top() == "num")
	{
		match("num");
	}
	else if(tokens.top() == "id")
	{
		var();

	}
	else
	{
		error(tokens.top(), "( | num | id", line);
	}
}

void term(){
	factor();

	while((tokens.top() == "multop") || (tokens.top() == "backslashop"))
	{
		if(tokens.top() == "multop")
		{
			multop();
			factor();
		}
		else if (tokens.top() == "backslashop")
		{
			multop();
			factor();
		}
	}
}

void addop(){
	if(tokens.top() == "addop")
	{
		match("addop");
	}
	else if(tokens.top() ==  "subop")
	{
		match("subop");
	}
	else
	{
		error(tokens.top(), "addop | subop", line);
	}
}

void additiveexpression(){
	term();
	while((tokens.top().compare("addop") == 0) || (tokens.top().compare("subop") == 0))
	{
		if(tokens.top() ==  "addop")
		{
			addop();
			term();
		}
		else if(tokens.top() ==  "subop")
		{
			addop();
			term();
		}
	}
}

void relop(){
	if(tokens.top() == "relop")
	{
		match("relop");
	}
	else
	{
		error(tokens.top(), "relop", line);
	}
}

void expression(){
	additiveexpression();

	while(tokens.top() == "relop")
	{
		relop();
		additiveexpression();
	}
}

void selectionstmt(){
	match("if");
	match("(");
	expression();
	match(")");
	statement();
	match(";");
	selectionstmttail();
}

void assignmentstmt(){
	var();
	match("assign");
	expression();
}

void iterationstmt(){
	match("while");
	match("(");
	expression();
	match(")");
	statement();
}

void statement(){
	if(tokens.top() == "id")
		assignmentstmt();
	else if(tokens.top() == "{")
		compoundstmt();
	else if(tokens.top() == "if")
		selectionstmt();
	else if(tokens.top() == "while")
		iterationstmt();
	else
		error(tokens.top(), "id | { | if | while", line);
}

void statementlist(){
	if(tokens.top() == "}")
		return;
	else
		statement();
	while(tokens.top() == ";")
	{
		match(";");
		statementlist();
	}
}

void compoundstmt(){
	statementlist();
}

void program(){
	typespecifier();
	match("id");
	match("(");
	params();
	match(")");
	match("{");
	// if(tokens.top() == "int" || tokens.top() == "float" || tokens.top() == "void")
		declarationlist();
	// else
		compoundstmt();
	match("}");
}

int main(){
	input.open("output.txt");
	scan();
	program();
	cout << "\n\n\n\n\n";
	bst.preorder();
}