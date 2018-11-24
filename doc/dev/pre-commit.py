#!/usr/bin/env python3

import sys
import subprocess


# Set stdin to read user input
sys.stdin = open('/dev/tty')


def cont_check(input_str):
    cont = input(input_str).strip()
    if cont.lower() in 'yes':
        return 0
    return 1


try:
    import cpplint
except ImportError:
    print('\n >cpplint is not installed!\n')
    exit_code = cont_check(' >Have you checked cpplint by hand(y/n)?> ')
    sys.exit(exit_code)

git_command = ["git", "diff", "--cached", "--name-only"]
process = subprocess.Popen(git_command, stdout=subprocess.PIPE)

output, _ = process.communicate()
commiting_files = str(output, 'utf-8').split('\n')

cpplint_include = ('.cpp', '.hpp')
cpplint_files = [f for f in commiting_files if f.endswith(cpplint_include)]

if len(cpplint_files):
    sys.argv = [''] + cpplint_files  # Include empty first string
    try:
        exit_code = cpplint.main()
    except SystemExit:
        print('\n >cpplint failed!\n')
        inp = ' >Are you sure you still want to continue(y/n)?> '
        exit_code = cont_check(inp)

    sys.exit(exit_code)
