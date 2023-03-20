#include <stdio.h>
#include <stdlib.h>

// A CREW_PREFIX függvény megvalósítása
void crew_prefix(int n, int *x, int *s, int low, int high)
{
    if (low == high) {
        s[low] = x[low];
        return;
    }

    int mid = (low + high) / 2;

    crew_prefix(n, x, s, low, mid);
    crew_prefix(n, x, s, mid + 1, high);

    int sum = 0;
    for (int i = mid; i >= low; i--) {
        sum += x[i];
        s[i] += sum;
    }

    sum = 0;
    for (int i = mid + 1; i <= high; i++) {
        sum += x[i];
        s[i] += sum;
    }
}

// A hívási fájl készítése
void make_call_graph(int n, int *x)
{
    int *s = (int *) calloc(n, sizeof(int));
    crew_prefix(n, x, s, 0, n-1);

    FILE *fp = fopen("call_graph.dot", "w");
    fprintf(fp, "digraph call_graph {\n");

    for (int i = 0; i < n; i++) {
        fprintf(fp, "node%d [label=\"%d\"];\n", i, x[i]);
        if (i > 0) {
            fprintf(fp, "node%d -> node%d;\n", i-1, i);
        }
    }

    fprintf(fp, "}\n");
    fclose(fp);

    free(s);
}

int main()
{
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int *x = (int *) malloc(n * sizeof(int));
    printf("Enter the array elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }

    make_call_graph(n, x);

    free(x);

    printf("Call graph created in call_graph.dot file.\n");

    return 0;
}
