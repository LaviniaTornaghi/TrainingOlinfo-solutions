#include <stdio.h>
#include <stdlib.h>

static FILE *in, *out;
static int N, Q, *T, i;
static long long *risp;

void inizia(int N, int T[]);
long long passaggio(int L, int R);

int main() {
  scanf("%d%d", &N, &Q);

  T = (int *)malloc(N * sizeof(int));

  for (i = 0; i < N; i++) {
    scanf("%d", T + i);
  }

  inizia(N, T);
  for (i = 0; i < Q; i++) {
    int L, R;
    scanf( "%d%d", &L, &R);
    printf("%lld\n", passaggio(L,R));
  }

  free(T);
  return 0;
}
