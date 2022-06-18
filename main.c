#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "libft/libft.h"
#include "tmp.h"

t_info	g_info = {};

t_alist	*init_env_values(char **env)
{
	t_alist	*head;
	char	*key;
	char	*eq_pos;

	head = NULL;
	while (*env)
	{
		eq_pos = ft_strchr(*env, '=');
		key = ft_strndup(*env, eq_pos - *env);
		if (key == NULL)
			exit(1);
		if (ft_strcmp(key, "OLDPWD") != 0)
			head = add_new_alist(head, key, eq_pos + 1);
		free(key);
		env++;
	}
	return (head);
}

void	exec_builtin_env(t_alist *env_list)
{
	printf("start env\n");
	while (env_list)
	{
		printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}

void	handle_sigint()
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	set_signal_handler(int signo, void *func)
{
	struct sigaction	action;

	action.sa_handler = func;
	if (sigaction(signo, &action, NULL))
	{
		perror("sigaction");
		exit(1);
	}
}

int	shell_init()
{
	extern char **environ;

	errno = 0;
	// SIGINTとSIGQUITは手当てする
	set_signal_handler(SIGINT, handle_sigint);
	set_signal_handler(SIGQUIT, SIG_IGN);
	// environから環境変数の連想リストを作成
	g_info.env_list = init_env_values(environ);
	getcwd(g_info.pwd, MAX_PATHSIZE);
	if (errno != 0)
		printf("shell-init: error retrieving current directory %s\n", strerror(errno));
	else
		add_new_alist(g_info.env_list, "PWD", g_info.pwd);
	return (errno == 0);
}

int	main(int argc, char** argv) {
	char	*input;

	g_info.last_result = shell_init();
	while (1) {
		// readlineを利用して入力を取得
		input = readline("minishell> ");
		// Ctrl-Dまたは"exit"で終了する
		if (input == NULL || strcmp(input, "exit") == 0)
		{
			printf("exit\n");
			break ;
		}
		// 空行の場合は履歴に加えない
		if (ft_strcmp(input, "") != 0)
			add_history(input);
		// envだったらbuiltinのenvを実行し環境変数を表示(テスト実装)
		if (ft_strcmp(input, "env") == 0)
			exec_builtin_env(g_info.env_list);
		// exportのテスト
		else if (ft_strcmp(input, "export") == 0)
		{
			input = readline("");
			add_new_alist(g_info.env_list, "testval", input);
		}
		// unsetのテスト
		else if (ft_strcmp(input, "unset") == 0)
		{
			input = readline("");
			rm_alist(g_info.env_list, input);
		}
		else if (ft_strcmp(input, "cd") == 0)
		{
			input = readline("");
			builtin_cd(input, g_info.env_list);
		}
		else if (ft_strcmp(input, "pwd") == 0)
			builtin_pwd();
		free(input);
	}
	free(input);
	// 環境変数の連想リストをfreeする
	free_alist(g_info.env_list);
	return (0);
}
