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
void compoundStatement();

void scan(){
    char ch;
    string token;
    input.get(ch);

    while(((ch == ' ') || (ch == '\n')) && (!input.eof())) {
        if(ch == '\n') line++;
        input.get(ch);
    }

    while((ch != ' ') && (ch != '\n') && (!input.eof())) {
        token += ch;
        input.get(ch);
    }

    if(token!="") tokens.push(token);
    if(ch == '\n') line++;
}

void syntaxError(string token, string exp, int line) {
    cout << "\nError on line: " << line << "\nExpected: \"" << exp << "\", got: " << token << "\n"; 
    exit(0);
}

void match(string s){

    if(tokens.top() == s) {
        cout << tokens.top() << " ";
        bst.add(s,"");
        scan();  
    } else syntaxError(tokens.top(), s, line);
}

void valueType(){
    if(tokens.top() =="int") {
        match("int");
    } else if(tokens.top() =="float") {
        match("float");
    } else if(tokens.top() =="void") {
        match("void");
    } else {
        syntaxError(tokens.top(), "int | float | void", line);
    }
}

void parameter(){
    valueType();
    match("id");
    if(tokens.top() == "[") {
        match("[");
        match("]");
    }
}

void parameterListing(){
    parameter();
    while(tokens.top() == ",") {
        match(",");
        parameter();
    }
}

void listParameter(){
    if(tokens.top() == "void") match("void");
    if(tokens.top() == "int" || tokens.top() == "float") parameterListing();
}

void variableDeclarationEnd(){
    if(tokens.top() == ";") match(";");
    else if(tokens.top() == "[") {
        match("[");
        match("num");
        match("]");
        match(";");
    } else syntaxError(tokens.top(), "; | [", line);
}

void variableDeclaration(){
    valueType();
    match("id");
    variableDeclarationEnd();
}

void variableLising(){
    variableDeclaration();
    if(tokens.top() == "int" || tokens.top() == "float" || tokens.top() == "void") variableDeclaration();
}

void ifEnd(){
    if(tokens.top() =="else") {
        match("else");
        statement();
    } else if(tokens.top() == "}" || tokens.top() == "else" ||tokens.top() == ";" )
        return;
    else syntaxError(tokens.top(), "else | }", line);
}

void multiplication(){
    if(tokens.top() =="multop") {
        match("multop");
    } else if(tokens.top() =="backslashop") {
        match("backslashop");
    } else {
        syntaxError(tokens.top(), "multop | backslashop", line);
    }
}

void variableEnd(){

    if(tokens.top() =="[") {
        match("[");
        expression();
        match("]");

    } else if(tokens.top() =="assign" 
            || tokens.top() =="multop" 
            || tokens.top() =="backslashop" 
            || tokens.top() =="addop" 
            || tokens.top() =="subop" 
            || tokens.top() =="relop" 
            || tokens.top() ==";")
        
            return;
    else syntaxError(tokens.top(), "Var Tail", line);
}

void variable(){
    match("id");
    variableEnd();
}

void factor(){
    if(tokens.top() == "(") {
        match("(");
        expression();
        match(")");
    } else if(tokens.top() == "num") match("num");
    else if(tokens.top() == "id") variable();
    else syntaxError(tokens.top(), "( | num | id", line);
}

void term(){
    factor();
    while((tokens.top() == "multop") || (tokens.top() == "backslashop")) {
        if(tokens.top() == "multop") {
            multiplication();
            factor();
        } else if (tokens.top() == "backslashop") {
            multiplication();
            factor();
        }
    }
}

void additionSubtraction(){
    if(tokens.top() == "addop") match("addop");
    else if(tokens.top() ==  "subop") match("subop");
    else syntaxError(tokens.top(), "addop | subop", line);
}

void additionSubtractionSyntax(){
    term();
    while((tokens.top().compare("addop") == 0) || (tokens.top().compare("subop") == 0)) {
        if(tokens.top() ==  "addop") {
            additionSubtraction();
            term();
        } else if(tokens.top() ==  "subop") {
            additionSubtraction();
            term();
        }
    }
}

void relational(){
    if(tokens.top() == "relop") match("relop");
    else syntaxError(tokens.top(), "relop", line);
}

void expression(){
    additionSubtractionSyntax();
    while(tokens.top() == "relop") {
        relational();
        additionSubtractionSyntax();
    }
}

void ifStatement(){
    match("if");
    match("(");
    expression();
    match(")");
    statement();
    match(";");
    ifEnd();
}

void assignment(){
    variable();
    match("assign");
    expression();
}

void whileStatement(){
    match("while");
    match("(");
    expression();
    match(")");
    statement();
}

void statement(){
    if(tokens.top() == "id") assignment();
    else if(tokens.top() == "{") compoundStatement();
    else if(tokens.top() == "if") ifStatement();
    else if(tokens.top() == "while") whileStatement();
    else syntaxError(tokens.top(), "id | { | if | while", line);
}

void statementListing(){
    if(tokens.top() == "}") return;
    else statement();
    while(tokens.top() == ";") {
        match(";");
        statementListing();
    }
}

void compoundStatement(){
    statementListing();
}

void program(){
    valueType();
    match("id");
    match("(");
    listParameter();
    match(")");
    match("{");
    variableLising();
    compoundStatement();
    match("}");
}

int main(){
    input.open("output.txt");
    scan();
    program();
    cout << "\n\n\n\n\n";
    bst.preorder();
}