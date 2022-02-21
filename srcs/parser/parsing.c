#include "parsing.h"
#include "minishell.h"


//jo voie une fonction avec t_tokenlist list et valeur qui demande a retourner a parse
//

// 	fonction par struct: t_grouping / t_list / t_pipeline / t_simple / t_redir
// 	fonction redir
//	fonction here doc
// prototype possible t_command *parsing(t_token_list *list,char *deliniter)
t_command *parsing(t_token_list **list)
{
	t_command	*tree;

	if (list->type == OR_IF || list->type == AND_IF || list->type == RPARENTHESIS || list->type == RPARENTHESIS)
	{
		printf("Wrong syntax token");
		exit(1);
	}
	else if (list->type >= 1 && list->type <= 5)
	{

	}
}
