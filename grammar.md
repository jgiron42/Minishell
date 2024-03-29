
![Tableau](https://github.com/jgiron42/minishell_v2/blob/parsing/includes/Tableau.png)

/* -------------------------------------------------------
   The grammar symbols
   ------------------------------------------------------- */

	%token  WORD
	%token  AND_IF    OR_IF	DLESS DGREAT 	PIPE	LESS	GREAT
	/*      '&&'      '||'	 '<<'   '>>'	'|'		'<'     '>'  '('		')'

/* -------------------------------------------------------
   The Grammar
   ------------------------------------------------------- */

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

cmd_word         : WORD                   /* Apply rule 7b */ not the first word


	[Assignment preceding command name]

		[When the first word]

			If the TOKEN does not contain the character '=', rule 1 is applied. Otherwise, 7b shall be applied.

	[Not the first word]

		If the TOKEN contains an unquoted (as determined while applying rule 4 from Token Recognition) <equals-sign> character that is not part of an embedded parameter expansion, command substitution, or arithmetic expansion construct (as determined while applying rule 5 from Token Recognition):

		If the TOKEN begins with '=', then rule 1 shall be applied.

		If all the characters in the TOKEN preceding the first such <equals-sign> form a valid name (see XBD Name), the token ASSIGNMENT_WORD shall be returned.

		Otherwise, it is unspecified whether rule 1 is applied or ASSIGNMENT_WORD is returned.

		Otherwise, 	the token WORD shall be returned.


cmd_prefix       :            io_redirect
                 | cmd_prefix io_redirect
                 |            ASSIGNMENT_WORD
                 | cmd_prefix ASSIGNMENT_WORD

cmd_suffix       :            io_redirect
                 | cmd_suffix io_redirect
                 |            WORD
                 | cmd_suffix WORD

redirect_list    :               io_redirect
                 | redirect_list io_redirect

io_redirect      :           io_file
                 | IO_NUMBER io_file
                 |           io_here
                 | IO_NUMBER io_here

io_file          : '<'       filename
                 | '>'       filename
                 | DGREAT    filename

filename         : WORD                      /* Apply rule 2 */

				[Redirection to or from filename]
				The expansions specified in Redirection shall occur. As specified there, exactly one field can result (or the result is unspecified),
				and there are additional requirements on pathname expansion.


io_here          : DLESS     here_end

here_end         : WORD                      /* Apply rule 3 */

				[Redirection from here-document]
				Quote removal shall be applied to the word to determine the delimiter
				that is used to find the end of the here-document that begins after the next <newline>.

----------------------------------------------------------------------
Expansion :
Bonus : attention les doubles quote empeches l'expansion des wildcard '*'

$	:
		peut etre suivi par :
		
			A numeric character

			The name of one of the special parameters (see Special Parameters)

			A valid first character of a variable name

			A <left-curly-bracket> ( '{' )

			A <left-parenthesis>

		si suivi de quote n'expand pas et quote remove

ASSIGNEMENT WORD = ne dois pas commencer par un nombre
exemple :
	bash: 1name=ab: command not found
----------------------------------------------------------------------

Heredoc :
	Le heredoc est appelé des que le token DLESS est vu dans le parsing
	Arret quand le delimiter est ecrit ou EOF pour gestion ctr^D
	Ne jamais expand le delimiter

	expansion : 
		si delimiter ne contient pas de quote:
			expand l'integraliter des $quelque chose dans le heredoc 
		si delimiter contient quote:
			expand ne rien expand dans le heredoc
