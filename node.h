#ifndef NODE_H
#define NODE_H

#include"token.h"
#include<QVector>

class Node
{

public:
    bool Expression_Expression;
    Node*Sibling;
    QVector<Node*> Childrens;
    Token token;

    Node();
};

#endif // NODE_H
