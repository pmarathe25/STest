#include "STest/include/STest.hpp"
#include <string>

STEST(StreamablePositiveCase) {
    static_assert(is_streamable_v<std::string, std::ostream>, "Streamable type is not being recognized as streamable");
}

class DefinitelyNotStreamable { };

STEST(StreamableNegativeCase) {
    static_assert(!is_streamable_v<DefinitelyNotStreamable, std::ostream>, "Non-streamable type is being recognized as streamable");
}

STEST_MAIN();
