#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char** argv) {
	char	*input;

	while (1) {
		input = readline("minishell> ");
		if (strcmp("exit", input) == 0)
			break;
		add_history(input);
		free(input);
	}
	free(input);
	return (0);
}
