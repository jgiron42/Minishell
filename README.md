# Minishell
This project is a basic shell implementation.

It supports:
- quoting
- simple redirections (>[file] <[file] >>[file] <<[END])
- pipelines
- environment (but the only way to set variables is export)
- the special variable $?
- signals
- the following built-in:
  - echo
  - pwd
  - cd
  - export
  - unset
  - env
  - exit

