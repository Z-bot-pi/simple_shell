#include "shell.h"

/**
 * desp_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int desp_history(info_t *info)
{
	list_print(info->history);
	return (0);
}

/**
 * alias_unset - changes alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_unset(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _chastr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = at_index_del_node(&(info->alias),
		fetch_node_index(info->alias, return_node_start(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * s_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int s_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (alias_unset(info, str));

	alias_unset(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * p_alias - prints a string alias
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int p_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 *m_alias - imitates the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int m_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			p_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			s_alias(info, info->argv[i]);
		else
			p_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
