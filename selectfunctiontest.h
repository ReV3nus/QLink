#ifndef SELECTFUNCTIONTEST_H
#define SELECTFUNCTIONTEST_H
#include<QtTest/QTest>
#define UNIT_TEST
class SelectFunctionTest : public QObject
{
    Q_OBJECT
private slots:
    void FirstSelection();
    void DuplicateSelection();
    void InvalidSecondSelection_WrongType();
    void InvalidSecondSelection_WrongNum();
    void InvalidSecondSelection_DisConnect();
    void ValidSecondSelection();

public:
    SelectFunctionTest();
};

#endif // SELECTFUNCTIONTEST_H
