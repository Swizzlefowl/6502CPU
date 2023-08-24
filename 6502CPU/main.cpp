#include "CPU.h"
#include "UnitTests.h"
int main() {
    cpu cpu{};

    testOpAdc();
    testOpAnd();
}