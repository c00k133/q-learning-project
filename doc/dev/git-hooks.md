# Git hooks

### Note to reader

Unfortunately none of the group members are set as maintainers for the repository, so for automating testing and linting before commits each group member has to either do this manually or add git-hooks themselves.


### Pre-commit

In the pre-commit hook we have attached a linter for C++ syntax, which should be according to [Google's C++ style guide](http://google.github.io/styleguide/cppguide.html).

For automating this check we are currently using a fork of Google's own GitHub linter, written in Python: [cpplint](https://github.com/cpplint/cpplint). 

*However*, as the default linter contains checks that the group do not want - such as a needed copyright claim on each document - we are using a [slightly modified version](https://github.com/c00k133/cpplint).

The pre-commit hook should be found in this folder under the same name. 
The guide used for creating the hook can be found [here](https://medium.com/@shettyrahul8june/how-to-run-eslint-using-pre-commit-hook-25984fbce17e).


### Pre-push

The hook for pre-pushing is used to ensure that each member does not accidentally push to the `master` branch.


### General

As a quick guide for setting up hooks:
1. Copy the wanted hook file to `.git/hooks/`
2. Make it executable with the following command: `chmod +x .git/hooks/<hook-name>`
