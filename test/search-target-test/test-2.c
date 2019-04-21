#include "klee/klee.h"

void better_with_dfs( int a0, int a1) {
	int k, n = 0;
	if (a0 > 0)
		a0 = 1;
	else
		a0 = -1;
	if (a1 > 0)
		a1 = 1;
	else
		a1 = -1;

	n = (a0 + a1);

	k = k / (n + 2);
}

void better_with_bfs(int a0, int a1) {
	int k, n = 0;
	if (a0 > 0)
		a0 = 1;
	else
		a0 = -1;
	if (a1 > 0)
		a1 = 1;
	else
		a1 = -1;

	n = (a0 + a1);

	k = k / (n - 2);
}

int main()
{
	int a0, a1;

	klee_make_symbolic(&a0, sizeof(a0), "a0");
	klee_make_symbolic(&a1, sizeof(a1), "a1");
	
	better_with_bfs(a0, a1);
	better_with_dfs(a0, a1);
}
