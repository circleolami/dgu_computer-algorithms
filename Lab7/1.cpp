#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX1 1024
#define MAX2 100

void brutesearch(char *p, char *a)
{
    int M = strlen(p);
    int N = strlen(a);
    int count = 0;

    for (int i = 0; i <= N - M; i++)
    {
        int j;
        for (j = 0; j < M; j++)
        {
            count++;
            if (a[i + j] != p[j])
                break;
        }
        if (j == M)
            printf("%d, ", i);
    }
    printf("%d ", count);
}

void computeLPSArray(char *pat, int M, int *lps)
{
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void kmpsearch(char *p, char *a)
{
    int M = strlen(p);
    int N = strlen(a);
    int *lps = (int *)malloc(sizeof(int) * M);
    int j = 0;
    int count = 0;

    computeLPSArray(p, M, lps);

    int i = 0;
    while (i < N)
    {
        if (p[j] == a[i])
        {
            j++;
            i++;
        }
        if (j == M)
        {
            printf("%d, ", i - j);
            j = lps[j - 1];
        }
        else if (i < N && p[j] != a[i])
        {
            count++;
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    free(lps);
    printf("%d ", count);
}

void rksearch(char *p, char *a)
{
    int M = strlen(p);
    int N = strlen(a);
    int i, j;
    int pHash = 0;
    int aHash = 0;
    int h = 1;
    int d = 256;
    int q = 101;
    int count = 0;

    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    for (i = 0; i < M; i++)
    {
        pHash = (d * pHash + p[i]) % q;
        aHash = (d * aHash + a[i]) % q;
    }

    for (i = 0; i <= N - M; i++)
    {
        if (pHash == aHash)
        {
            for (j = 0; j < M; j++)
            {
                count++;
                if (a[i + j] != p[j])
                    break;
            }
            if (j == M)
                printf("%d, ", i);
        }
        if (i < N - M)
        {
            aHash = (d * (aHash - a[i] * h) + a[i + M]) % q;
            if (aHash < 0)
                aHash = (aHash + q);
        }
    }
    printf("%d ", count);
}

int main()
{
    char text[MAX1];
    char pattern[MAX2];

    printf("text string:\n");
    fgets(text, MAX1, stdin);
    text[strcspn(text, "\n")] = 0;

    printf("pattern string:\n");
    fgets(pattern, MAX2, stdin);
    pattern[strcspn(pattern, "\n")] = 0;

    brutesearch(pattern, text);
    printf("(Brute-Force - 문자열의 시작의 IDX1, 문자열의 시작의 IDX2, 문자열 비교 횟수)\n");

    kmpsearch(pattern, text);
    printf("(KMP - 문자열의 시작의 IDX1, 문자열의 시작의 IDX2, 문자열 비교 횟수)\n");

    rksearch(pattern, text);
    printf("(Rabin-Karp - 문자열의 시작의 IDX1, 문자열의 시작의 IDX2, 문자열 비교 횟수)\n");

    return 0;
}
