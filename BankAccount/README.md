# The Jolly Banker

## Implementation: What does Bank Do?

Bank reads in a .txt file through a command line argument with transactions.

Bank will process the transactions, line by line, opening a new account, withdrawing from an existing account's fund, depositing into an existing account's fund, transferring from one fund to another either from the same account or two different accounts, and printing the transaction history of each fund to an out .txt file.

After processing all transactions -- Bank will print each account with their owner's name, account number, and the balances of every fund.

## Compile and Run

```
./simplecompile.sh
```

### Style Explanation
These options are defined in `.clang-tidy` file.

Perform all check except the following:

- cert-err58-cpp
- cppcoreguidelines-avoid-magic-numbers
- cppcoreguidelines-owning-memory: not using gsl
- cppcoreguidelines-pro-bounds-array-to-pointer-decay: do not give warnings on assert
- cppcoreguidelines-pro-bounds-constant-array-index
- cppcoreguidelines-pro-bounds-pointer-arithmetic
- cppcoreguidelines-special-member-functions: not defining move operator
- fuchsia-* do not need specific checks for "fuchsia" a modular, capability-based operating system
- google-build-using-namespace: for simplicity allow `using namespace std;`
- google-global-names-in-headers: for simplicity allow `using namespace std;`
- google-readability-braces-around-statements: allow compact code without `{`
- hicpp-braces-around-statements: allow compact code without `{` (this option
- hicpp-no-array-decay: need to use assert
- hicpp-special-member-functions: not defining move operator
- llvm-header-guard: not using full directory name
- modernize-pass-by-value
- modernize-use-trailing-return-type: not ready yet for `auto func() -> int` format
- readability-braces-around-statements
- readability-magic-numbers

## Misc

This file is part of a repository located at
https://github.com/jdelliot/banker

