#ifndef TOKEN_H
#define TOKEN_H

#include <QString>

class Token{

public:
    Token();
    Token(QString value,QString type);
    QString tokenValue;
    QString tokenType;
};

#endif // TOKEN_H
