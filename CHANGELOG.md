# STest Changelog
Dates are in YYYY-MM-DD format.

## v0.3.3 (2019-09-17)
- Adds a fallback `operator<<` for those types which do not provide one themselves.

## v0.3.2 (2019-09-07)
- Reworks `EXPECT_THROWS` and `EXPECT_THROWS_ANY` so that they no longer trigger compiler warnings.

## v0.3.1 (2019-09-07)
- Test output does not display `PASSED` if no tests passed, or `FAILED` if no tests failed.
- Updates build system.

## v0.3.0 (2019-07-24)
- Leverages `SLog`'s `operator<<` overloads to enable displaying better errors.
- `EXPECT_*` macros now throw a `TestFailedException` to indicate that a failure occurred. This allows them to be used in helper functions as well.
- Adds `STEST_MAIN` macro to save on boiler plate.
- Enables tests with duplicate names (must be in different namespaces).
- Updates `SLog` dependency so no library is required (header-only).

## v0.2.0 (2019-07-15)
- Adds `EXPECT_THROWS` and `EXPECT_THROWS_ANY` to check for exceptions.

## v0.1.1 (2019-07-10)
- Adds header include guard
- Refactors tests into multiple separate tests visible to SBuildr.

## v0.1.0 (2019-07-08)
- Adds support for fixtures with `STEST_F` macro.
- Test names now include source file names.
