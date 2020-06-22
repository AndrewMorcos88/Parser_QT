#include "expersion.h"


 static int Counter=0;
 static QVector<Token>Tokens;
 static Node* Parent_Sibling=nullptr;
 static bool Flag_Error=false;
 static QString Error_Message="";

Expression::Expression()
{

}

Node *Expression::RunAlgorithm(QVector<Token> tokens )
{
     Tokens = tokens;
     Counter=0;
     Parent_Sibling=nullptr;
     Flag_Error=false;
     return  Statement_Sequence(1);
}

Node* Expression::Statement_Sequence(int a){
    Node* Root =Statement(a);

    while( Counter<Tokens.size() && Tokens[Counter].tokenType=="SEMICOLON" )
    {
        Counter++;
        Statement(a);
    }
    if( Counter<Tokens.size() && Tokens[Counter].tokenType!="SEMICOLON" &&a==1 )
        return ERROR("Error!!,Missing semicolun");


return Root;
}

 Node* Expression:: Statement(int A)
{
     QString Temp_type =Tokens[Counter].tokenType;

    if (Temp_type=="IF")
    {
        Counter++;
             return IF();
    }
     else if(Temp_type=="REPEAT")
    {
        Counter++;
         return REPEAT();
    }
     else if (Temp_type=="READ")
    {
        Counter++;
            return READ();
    }
     else if (Temp_type=="WRITE")
    {
        Counter++;
            return WRITE();
    }
     else if (Temp_type=="IDENTIFIER")
    {
        QString Left_Side_Identifier=Tokens[Counter].tokenValue;
        Counter++;
              return ASSIGMENT(Left_Side_Identifier);
    }
     else if (A==1)
      return ERROR("No Statment is defined");


}
 Node* Expression:: READ()
 {
     if (Counter<Tokens.size() && Tokens[Counter].tokenType== "IDENTIFIER")
     {

         // create node for Read

         Node*New_Node =new Node;
         New_Node->Expression_Expression =true;
         New_Node->token.tokenType="READ";
         New_Node->token.tokenValue= "("+Tokens[Counter].tokenValue+")";
         Counter++;
         if (Parent_Sibling==nullptr)
         {
           Parent_Sibling=New_Node;
         }
         else
         {
             Parent_Sibling->Sibling=New_Node;
             Parent_Sibling=New_Node;
         }

         return New_Node;

     }

    else
      return ERROR("Error !! , must have IDENTIFIER after READ token");

 }



 Node* Expression:: ASSIGMENT( QString Left_Side_Identifier)
 {
     if ( Counter<Tokens.size() && Tokens[Counter].tokenType== "ASSIGN")
     {
         Counter++;

         // create node for ASSIGMENT
         Node*New_Node =new Node;
         New_Node->Expression_Expression =true;
         New_Node->token.tokenType="ASSIGN";
         New_Node->token.tokenValue= "("+ Left_Side_Identifier  +")";
         New_Node->Childrens.push_back(exp().root);

         if (Parent_Sibling==nullptr)
         {
           Parent_Sibling=New_Node;
         }
         else
         {
             Parent_Sibling->Sibling=New_Node;
             Parent_Sibling=New_Node;
         }

         return New_Node;


     }

     else
         return  ERROR("Error !! , should have assign operator after IDENTIFIER");



 }



 Node* Expression:: WRITE()
 {

         // create node for Write
         Node*New_Node =new Node;
         New_Node->Expression_Expression =true;
         New_Node->token.tokenValue="WRITE";
        New_Node->Childrens.push_back(exp().root);

         if (Parent_Sibling==nullptr)
         {
           Parent_Sibling=New_Node;
         }
         else
         {
             Parent_Sibling->Sibling=New_Node;
             Parent_Sibling=New_Node;
         }


         return New_Node;

 }



 Node* Expression:: REPEAT()
 {

     Node*New_Node =new Node;
     New_Node->Expression_Expression =true;
     New_Node->token.tokenValue="REPEAT";

     Node* TeMp=Parent_Sibling;  // temp value to have Parent sibling of Repeat

     Parent_Sibling=nullptr;
     New_Node->Childrens.push_back(Statement_Sequence(0));
     New_Node->Childrens.push_back(UNTIL());
     Parent_Sibling=TeMp;


     if (Parent_Sibling==nullptr)
     {
       Parent_Sibling=New_Node;
     }
     else
     {
         Parent_Sibling->Sibling=New_Node;
         Parent_Sibling=New_Node;
     }



     return New_Node;

 }


 Node* Expression:: IF()
 {

     Node*New_Node =new Node;
     New_Node->Expression_Expression =true;
     New_Node->token.tokenValue="IF";

     Node* TeMp=Parent_Sibling;  // temp value to have Parent sibling of Repeat

     Parent_Sibling=nullptr;
     New_Node->Childrens.push_back(exp().root);
     THEN();
     New_Node->Childrens.push_back(Statement_Sequence(0));

     Parent_Sibling=TeMp;


     if (Parent_Sibling==nullptr)
     {
       Parent_Sibling=New_Node;
     }
     else
     {
         Parent_Sibling->Sibling=New_Node;
         Parent_Sibling=New_Node;
     }


      if (Counter<Tokens.size() && Tokens[Counter].tokenType== "ELSE")
      {
          Counter++;
          Statement_Sequence(0);

          if ( Counter<Tokens.size() && Tokens[Counter].tokenType== "END")
          {
              Counter ++;

          }
         else
          return ERROR (" error!!, must be end token after if condition ");

      }

      else if ( Counter<Tokens.size() &&Tokens[Counter].tokenType== "END")
      {
          Counter++;

      }

      else
       return ERROR (" error!!, must be end token after if condition ");





      return New_Node;




 }



void Expression:: THEN()
 {
     if (Counter<Tokens.size() && Tokens[Counter].tokenType== "THEN")
     {
         Counter ++;
         return;
     }
     else
       ERROR(" error!!,must have then token after if condition ");

 }





 Node* Expression:: UNTIL()
 {
     if (Counter<Tokens.size() && Tokens[Counter].tokenType== "UNTIL")
     {
         Counter++;
         return exp().root;

     }
     else
      return  ERROR("must have until tokrn after repeat");
 }


 Tree Expression:: exp(){
    Tree temp = simpleexp();
         while (Counter<Tokens.size() && iscompop(Tokens[Counter]))
         {
             int opindex = Counter;
             Counter++;
             Tree newtemp = simpleexp();
             Node* opnode = new Node;
             opnode->token.tokenValue = Tokens[opindex].tokenValue;
             opnode->Expression_Expression=false;
             opnode->token.tokenType = "OPERATOR";

             opnode->Childrens.push_back(temp.root);
             opnode->Childrens.push_back(newtemp.root);
             temp.root = opnode;

         }
         return temp;
 }


 Tree Expression:: simpleexp()
 {

     Tree temp = term();
     while (Counter<Tokens.size() && isaddop(Tokens[Counter]))
     {
         int opindex = Counter;
         Counter++;
         Tree newtemp = term();
         Node * opnode = new Node;
         opnode->token.tokenValue = Tokens[opindex].tokenValue;
         opnode->token.tokenType = "OPERATOR";
         opnode->Expression_Expression=false;
         opnode->Childrens.push_back(temp.root);
         opnode->Childrens.push_back(newtemp.root);
         temp.root = opnode;

     }
     return temp;


 }

 Tree Expression:: term()
 {
     Tree temp=factor();
     Node newNode ;
     while ( Counter<Tokens.size() && ismulop(Tokens[Counter]))
     {
      int opindex = Counter;
      Counter++;
      Tree newtemp=  factor();
      Node * opnode = new Node;
      opnode->token.tokenValue = Tokens[opindex].tokenValue;
      opnode->token.tokenType = "OPERATOR";
      opnode->Expression_Expression=false;
      opnode->Childrens.push_back(temp.root);
      opnode->Childrens.push_back(newtemp.root);
      temp.root = opnode;

     }
     return temp;
 }




 Tree Expression:: factor()
 {

     if (Counter<Tokens.size() && Tokens[Counter].tokenValue == "(")
     {
         match("(");
         Tree temp=exp();
         match(")");
         return temp;

     }
     else if ( Counter<Tokens.size() &&Tokens[Counter].tokenType == "NUMBER")
     {
         Tree tmp;
         Node * temp = new Node;
         temp->token.tokenValue = Tokens[Counter].tokenValue;
         temp->token.tokenType = "CONST";
         temp->Expression_Expression=false;
         tmp.root = temp;

         Counter++;
         return tmp;
     }
     else if ( Counter<Tokens.size() &&Tokens[Counter].tokenType == "IDENTIFIER")
     {
         Tree tmp;
         Node * temp = new Node;
         temp->token.tokenValue = Tokens[Counter].tokenValue;
         temp->token.tokenType = "ID";
         temp->Expression_Expression=false;
         tmp.root = temp;
         Counter++;
         return tmp;
     }
     else
      ERROR(" Error!!,not allowed expression");



 }




 bool Expression:: iscompop(Token x)
 {
     if (x.tokenValue == "<" || x.tokenValue == "=")
     {
         return 1;
     }

     return 0;
 }

 bool Expression:: isaddop(Token x)
 {
     if (x.tokenValue == "+" || x.tokenValue == "-")
     {
         return 1;
     }

     return 0;
 }

 bool Expression:: ismulop(Token x)
 {
     if (x.tokenValue == "*" || x.tokenValue == "/")
     {
         return 1;
     }

     return 0;
 }


 void Expression:: match(QString x)
 {
     if (x == Tokens[Counter].tokenValue)
     {
         Counter++;
     }
     else
      ERROR("error!!,not matched expression");
 }



 Node* Expression:: ERROR(QString Error_message)
 {
     Flag_Error =true;
     Error_Message=Error_message;
     return nullptr;
 }



 QString Expression:: Check_Error()
 {
     if (Flag_Error==true)
         return Error_Message;
     else {
         return "";

     }



 }






















