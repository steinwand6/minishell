#include "tmp.h"

extern t_info g_info;

// 引数は1つしか受けとらない(cd呼び出し側の仕事とする)
// 処理の流れ
// 1. 渡されたpathが扱えるものか確認する
// 2. 1の結果、問題あればエラーとして終了
// 3. 現在のpathを取得
// 4. 3の結果、問題あればgetcwdのエラーを表示
// 5. 移動
// 6. OLDPWDに2で取得したものをセット
// 7. PWDに今のものをセット
// ※6, 7はもっと複雑な何かだが、一旦簡易な感じで実装
int	builtin_cd(const char *path, t_alist *env_list)
{
	int		errno;

	errno = 0;
	getcwd(g_info.pwd, MAX_PATHSIZE);
	chdir(path);
	if (errno != 0)
	{
		printf("chdir: %s\n", strerror(errno));
		return (1);
	}
	add_new_alist(env_list, "OLDPWD", g_info.pwd);
	getcwd(g_info.pwd, MAX_PATHSIZE);
	add_new_alist(env_list, "PWD", g_info.pwd);
	return (0);
}

int builtin_pwd()
{
   	char	cwd_name[MAX_PATHSIZE];
	int		errno;

	errno = 0;
	getcwd(cwd_name, MAX_PATHSIZE);
	if (g_info.pwd)
		printf("%s\n", g_info.pwd);
	else if (errno != 0)
		printf("pwd: error retrieving current directory %s\n", strerror(errno));
	else
		printf("%s\n", cwd_name);
	return (errno == 0);
}
