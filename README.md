# 42cursus-minishell ([Subject](https://cdn.intra.42.fr/pdf/pdf/65718/en.subject.pdf))

## Description

The objective of this project is for you to create a simple shell.

[![GitHub](https://img.shields.io/github/license/BrunoCostaGH/42cursus-minishell?style=for-the-badge)]()
[![GitHub contributors](https://img.shields.io/github/contributors/BrunoCostaGH/42cursus-minishell?style=for-the-badge)]()
[![GitHub issues](https://img.shields.io/github/issues/BrunoCostaGH/42cursus-minishell?style=for-the-badge)](https://github.com/BrunoCostaGH/42cursus-minishell/issues)
[![GitHub Release Date](https://img.shields.io/github/release-date/BrunoCostaGH/42cursus-minishell?style=for-the-badge)](https://github.com/BrunoCostaGH/42cursus-minishell/releases/latest)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/BrunoCostaGH/42cursus-minishell?style=for-the-badge)](https://github.com/BrunoCostaGH/42cursus-minishell/releases/latest)

## Features

- Working history.
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
- Implemented redirections:
  - \< redirect input.
  - \> redirect output.
  - \<< should be given a delimiter, then reads the input until a line containing the delimiter is seen. However, it doesn't update the history!
  - \>> redirect output in append mode.
- Implemented pipes (| character).
- Handles environment variables.
- Handles $? which expands to the exit status of the most recently executed foreground pipeline.
- Handles ctrl-C, ctrl-D and ctrl-\.
- In interactive mode:
  - ctrl-C displays a new prompt on a new line.
  - ctrl-D exits the shell.
  - ctrl-\ does nothing.
- echo with option -n
- cd with only a relative or absolute path
- pwd with no options
- export with no options
- unset with no options
- env with no options or arguments
- exit with no options
