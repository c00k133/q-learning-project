#!/usr/bin/env python3

import sys
import subprocess

try:
    import cpplint
except ImportError:
    print('cpplint is not installed!')
    cont = input('Have you checked cpplint by hand (y/n)?> ').strip()
    if cont.lower() in 'yes':
        sys.exit(0)
    sys.exit(1)


git_command = ["git", "diff", "--cached", "--name-only"]
process = subprocess.Popen(git_command, stdout=subprocess.PIPE)

output, _ = process.communicate()
commiting_files = str(output, 'utf-8').split('\n')

cpplint_include = ('.cpp', '.hpp')
cpplint_files = [f for f in commiting_files if f.endswith(cpplint_include)]

if len(cpplint_files):
    sys.argv = [''] + cpplint_files  # Include empty first string
    sys.exit(cpplint.main())
