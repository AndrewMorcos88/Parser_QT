#ifndef EXPRESSION_H
#define EXPRESSION_H
#include"node.h"
#include"token.h"
#include"tree.h"
#include"mainwindow.h"

class Expression
{
public:
     static Node* Statement(int A);
     static Node* Statement_Sequence(int a);
    static Node* READ();

     static Node* WRITE();
      static Node* REPEAT();
    static Node* UNTIL();
    static Node* IF();
      static Node* ASSIGMENT(QString Left_Side_Identifier);
    Expression();
   static void THEN();
   static void END();




    static Tree exp();
   static Tree simpleexp();
   static Tree term();
   static Tree factor();
    static bool iscompop(Token x);
   static bool isaddop(Token x);
    static bool ismulop(Token x);
   static void error(QString x);
    static void match(QString x);
   static Node* ERROR( QString Error);
   static Node* RunAlgorithm(QVector<Token> tokens);
   static QString Check_Error();



};

#endif// EXPRESSION_H
