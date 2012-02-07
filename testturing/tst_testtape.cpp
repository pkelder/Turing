#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../simulation/src/Tape.h"

class TestTape : public QObject
{
    Q_OBJECT

public:
    TestTape();

private Q_SLOTS:
    void TapeConstructor();
    void TapeMove();
    void TapeSetChar();
};

TestTape::TestTape()
{
}

void TestTape::TapeConstructor()
{
    vector<char> content = {'a','2','c'};
    Tape* testtape = new Tape(content);
    QVERIFY(testtape->getChar() == 'a');
    vector<char> actual = testtape->getContent();
    QVERIFY(actual[0] == ' ');
    QVERIFY(actual[1] == 'a');
    QVERIFY(actual[2] == '2');
    QVERIFY(actual[3] == 'c');
    QVERIFY(actual[4] == ' ');
    delete testtape;
}

void TestTape::TapeMove()
{
    vector<char> content = {'a','b','c'};
    Tape* testtape = new Tape(content);
    testtape->move(-1);
    QVERIFY(testtape->getChar() == ' ');
    testtape->move(-1);
    QVERIFY(testtape->getChar() == ' ');
    testtape->move(1);
    QVERIFY(testtape->getChar() == 'a');
    testtape->move(0);
    QVERIFY(testtape->getChar() == 'a');
    testtape->move(1);
    QVERIFY(testtape->getChar() == 'b');
    testtape->move(2);
    QVERIFY(testtape->getChar() == 'b');
    testtape->move(1);
    QVERIFY(testtape->getChar() == 'c');
    testtape->move(1);
    QVERIFY(testtape->getChar() == ' ');
    testtape->move(1);
    QVERIFY(testtape->getChar() == ' ');
    testtape->move(-1);
    QVERIFY(testtape->getChar() == 'c');
    delete testtape;
}

void TestTape::TapeSetChar()
{
    vector<char> content = {'a', 'b'};
    Tape* testtape = new Tape(content);

    //Simple check
    testtape->setChar('z');
    QVERIFY(testtape->getChar() == 'z');

    //Check if setChar extends correctly the Tape
    testtape->move(1);
    testtape->move(1);
    for (int i = 0; i < 10; i++) {
        testtape->setChar(i);
        QVERIFY(testtape->getChar() == i);
        testtape->move(1);
    }
    QVERIFY(testtape->getChar() == ' ');
}

QTEST_APPLESS_MAIN(TestTape);

#include "tst_testtape.moc"
