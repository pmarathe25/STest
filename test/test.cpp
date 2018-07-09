#include "interfaces/STest"

STEST(all, doNothing) {

}

STEST(all, doNothingAgain) {

}

int main() {
    namespace st = Stealth::Test;
    st::runTests();
}
