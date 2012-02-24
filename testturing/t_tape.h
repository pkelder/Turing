#ifndef TST_TESTTAPE_H
#define TST_TESTTAPE_H

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

#endif // TST_TESTTAPE_H
