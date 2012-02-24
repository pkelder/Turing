#include "t_tape.h"

int main() {
    TestTape* test_tape = new TestTape();
    QTest::qExec(test_tape);
}
