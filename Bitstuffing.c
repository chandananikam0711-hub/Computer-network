// ```c
#include <stdio.h>
#include <string.h>

int main()
{
    char data[100], stuffed[200];
    int i, j = 0, count = 0;

    printf("Enter the binary data: ");
    scanf("%s", data);

    for (i = 0; i < strlen(data); i++)
    {
        stuffed[j++] = data[i];

        if (data[i] == '1')
        {
            count++;

            if (count == 5)
            {
                stuffed[j++] = '0';
                count = 0;
            }
        }
        else
        {
            count = 0;
        }
    }

    stuffed[j] = '\0';

    printf("Original data: %s\n", data);
    printf("After bit stuffing: %s\n", stuffed);

    return 0;
}
