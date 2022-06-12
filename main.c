#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <readline/readline.h>
#include <readline/history.h>

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

int	main(int argc, char** argv) {
	char	*input;

	set_signal_handler(SIGINT, handle_sigint);
	set_signal_handler(SIGQUIT, SIG_IGN);
	while (1) {
		// readlineを利用して入力を取得
		input = readline("minishell> ");
		// Ctrl-Dまたは"exit"で終了する
		if (input == NULL || strcmp(input, "exit") == 0)
		{
			printf("exit\n");
			break ;
		}
		if (strcmp(input, "") != 0)
			add_history(input);
		free(input);
	}
	free(input);
	return (0);
}
