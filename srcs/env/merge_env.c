
void	merge_env(t_env **a, t_env *b)
{
	t_env	*tmp;

	if (!*a)
		*a = b;
	tmp = *a;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = b;
	return (OK);
}