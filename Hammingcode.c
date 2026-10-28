#include <stdio.h>

int main()
{
    int data[20], hamming[20];
    int m, r = 0, i, j, k, pos, error = 0;

    printf("Enter the number of data bits: ");
    scanf("%d", &m);

    printf("Enter the data bits: ");
    for (i = 0; i < m; i++)
        scanf("%d", &data[i]);

    /* Calculate number of parity bits */
    while ((1 << r) < m + r + 1)
        r++;

    int n = m + r;

    /* Initialize Hamming code positions */
    for (i = 1; i <= n; i++)
        hamming[i] = 0;

    /* Place data bits in non-power-of-2 positions */
    j = 0;
    for (i = 1; i <= n; i++)
    {
        if ((i & (i - 1)) != 0)
            hamming[i] = data[j++];
    }

    /* Calculate even parity bits */
    for (i = 1; i <= n; i *= 2)
    {
        int parity = 0;

        for (j = 1; j <= n; j++)
        {
            if ((j & i) != 0)
                parity ^= hamming[j];
        }

        hamming[i] = parity;
    }

    printf("\nHamming Code: ");
    for (i = 1; i <= n; i++)
        printf("%d", hamming[i]);

    /* Receive code from user */
    printf("\n\nEnter received bits (%d bits): ", n);
    for (i = 1; i <= n; i++)
        scanf("%d", &hamming[i]);

    /* Detect error using syndrome */
    for (i = 1; i <= n; i *= 2)
    {
        int parity = 0;

        for (j = 1; j <= n; j++)
        {
            if ((j & i) != 0)
                parity ^= hamming[j];
        }

        if (parity != 0)
            error += i;
    }

    if (error == 0)
    {
        printf("No error detected.\n");
    }
    else if (error <= n)
    {
        printf("Error detected at position: %d\n", error);

        /* Correct the single-bit error */
        hamming[error] ^= 1;

        printf("Corrected Hamming Code: ");
        for (i = 1; i <= n; i++)
            printf("%d", hamming[i]);

        printf("\n");
    }
    else
    {
        printf("Invalid error position.\n");
    }

    return 0;
}
