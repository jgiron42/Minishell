complete_command : list separator_op
            	| list

list             : list separator_op and_or
                 |                   and_or
separator_op     :  ';'
and_or           :                         pipeline
                 | and_or AND_IF linebreak pipeline
                 | and_or OR_IF  linebreak pipeline
pipeline         :      pipe_sequence
pipe_sequence    :                             command
                 | pipe_sequence '|' linebreak command
command          : simple_command
                 | compound_command
                 | compound_command redirect_list
compound_command : brace_group
                 | subshell
subshell         : '(' compound_list ')'

simple_command   : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
cmd_name         : WORD                   /* Apply rule 7a */ the first word
                 ;
cmd_word         : WORD                   /* Apply rule 7b */ not the first word
cmd_prefix       :            io_redirect
                 | cmd_prefix io_redirect
                 |            ASSIGNMENT_WORD
                 | cmd_prefix ASSIGNMENT_WORD
cmd_suffix       :            io_redirect
                 | cmd_suffix io_redirect
                 |            WORD
                 | cmd_suffix WORD

1name=ab
bash: 1name=ab: command not found
