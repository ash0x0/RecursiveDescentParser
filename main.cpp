/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ahmed
 *
 * Created on November 2, 2017, 7:22 PM
 */

// This file is build using the EBNF in the report, it is a direct one to one implementation

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

binaryTree<string, string> parseBinaryTree;

void statement();
void expression();
void compoundStmt();

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
        parseBinaryTree.add(s,"");
        scan();  
    } else syntaxError(tokens.top(), s, line);
}

void typeSpecifier(){
    if(tokens.top() =="INTEGER") {
        match("INTEGER");
    } else if(tokens.top() =="FLOAT") {
        match("FLOAT");
    } else if(tokens.top() =="VOID") {
        match("VOID");
    } else {
        syntaxError(tokens.top(), "INTEGER | FLOAT | VOID", line);
    }
}

void param(){
    typeSpecifier();
    match("IDENTIFIER");
    if(tokens.top() == "[") {
        match("[");
        match("]");
    }
}

void paramList(){
    param();
    while(tokens.top() == "COMMA") {
        match("COMMA");
        param();
    }
}

void params(){
    if(tokens.top() == "VOID") match("VOID");
    if(tokens.top() == "INTEGER" || tokens.top() == "FLOAT") paramList();
}

void varDeclarationTail(){
    if(tokens.top() == "SEMI") match("SEMI");
    else if(tokens.top() == "[") {
        match("[");
        match("NUMBER");
        match("]");
        match("SEMI");
    } else syntaxError(tokens.top(), "SEMI | [", line);
}

void varDeclaration(){
    typeSpecifier();
    match("IDENTIFIER");
    varDeclarationTail();
}

void declarationList(){
    if (tokens.top() == "IF") return;
    varDeclaration();
    if(tokens.top() == "INTEGER" || tokens.top() == "FLOAT" || tokens.top() == "VOID") varDeclaration();
}

void args() {
    if(tokens.top() == "INTEGER" || tokens.top() == "FLOAT") paramList();
}

void selectionStmt(){
    if(tokens.top() =="ELSE") {
        match("ELSE");
        statement();
    } else if(tokens.top() == "}" || tokens.top() == "ELSE" ||tokens.top() == "SEMI")
        return;
    else if (tokens.top() == "RETURN") {
        match("RETURN");
        match("IDENTIFIER");
        if (tokens.top() == "SEMI") match("SEMI");
        else if (tokens.top() == "(") {
            match("(");
            match(")");
            match("SEMI");
        }
    }
    else syntaxError(tokens.top(), "ELSE | }", line);
}

void mulOp(){
    if(tokens.top() =="MULOP") {
        match("MULOP");
    } else {
        syntaxError(tokens.top(), "MULOP", line);
    }
}

void varTail(){

    if(tokens.top() =="[") {
        match("[");
        expression();
        match("]");

    } else if(tokens.top() =="ASSIGN" 
            || tokens.top() =="MULOP"
            || tokens.top() =="ADDOP"
            || tokens.top() =="RELOP" 
            || tokens.top() =="SEMI")
        
            return;
    else syntaxError(tokens.top(), "Var Tail", line);
}

void var(){
    match("IDENTIFIER");
    varTail();
}

void factor(){
    if(tokens.top() == "(") {
        match("(");
        expression();
        match(")");
    } else if(tokens.top() == "NUMBER") match("NUMBER");
    else if(tokens.top() == "IDENTIFIER") var();
    else syntaxError(tokens.top(), "( | NUMBER | IDENTIFIER", line);
}

void term(){
    factor();
    while((tokens.top() == "MULOP")) {
        if(tokens.top() == "MULOP") {
            mulOp();
            factor();
        }
    }
}

void addOp(){
    if(tokens.top() == "ADDOP") match("ADDOP");
    else syntaxError(tokens.top(), "ADDOP", line);
}

void additiveExpression(){
    term();
    while((tokens.top().compare("ADDOP") == 0)) {
        if(tokens.top() ==  "ADDOP") {
            addOp();
            term();
        }
    }
}

void relop(){
    if(tokens.top() == "RELOP") match("RELOP");
    else syntaxError(tokens.top(), "RELOP", line);
}

void expression(){
    additiveExpression();
    while(tokens.top() == "RELOP") {
        relop();
        additiveExpression();
    }
}

void selectionSmt(){
    match("IF");
    match("(");
    expression();
    match(")");
    statement();
    if (tokens.top() == "SEMI") match("SEMI");
    else if (tokens.top() == "ELSE") match ("ELSE");
    selectionStmt();
}

void assignmentStmt(){
    var();
    match("ASSIGN");
    expression();
}

void iterationStmt(){
    match("WHILE");
    match("(");
    expression();
    match(")");
    statement();
}

void returnStmt(){
    match("RETURN");
    match("IDENTIFIER");
    match("SEMI");
}

void statement(){
    if(tokens.top() == "IDENTIFIER") assignmentStmt();
    else if(tokens.top() == "{") compoundStmt();
    else if(tokens.top() == "IF") selectionSmt();
    else if(tokens.top() == "WHILE") iterationStmt();
    else if (tokens.top() == "RETURN") returnStmt();
    else syntaxError(tokens.top(), "IDENTIFIER | { | IF | WHILE", line);
}

void statementList(){
    if(tokens.top() == "}") return;
    else statement();
    while(tokens.top() == "SEMI") {
        match("SEMI");
        statementList();
    }
}

void compoundStmt(){
    statementList();
}

void program(){
    typeSpecifier();
    match("IDENTIFIER");
    match("(");
    params();
    match(")");
    match("{");
    declarationList();
    compoundStmt();
    match("}");
}

int main(){
    input.open("output.txt");
    scan();
    program();
    cout << endl;
    parseBinaryTree.preorder();
}