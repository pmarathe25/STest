# STest Changelog
Dates are in YYYY-MM-DD format.

## vNext ()
- Leverages `SLog`'s `operator<<` overloads to enable displaying better errors.
- `EXPECT_*` macros now throw a `TestFailedException` to indicate that a failure occurred. This allows them to be used in helper functions as well. 

## v0.2.0 (2019-07-15)
- Adds `EXPECT_THROWS` and `EXPECT_THROWS_ANY` to check for exceptions.

## v0.1.1 (2019-07-10)
- Adds header include guard
- Refactors tests into multiple separate tests visible to SBuildr.

## v0.1.0 (2019-07-08)
- Adds support for fixtures with `STEST_F` macro.
- Test names now include source file names.
