
#include <stdio.h>
#include <string.h>

int main()
{
    char data[100], divisor[30], temp[130], received[130];
    int i, j, dataLen, divisorLen, totalLen, error = 0;

    printf("Enter data bits: ");
    scanf("%99s", data);

    printf("Enter generator bits: ");
    scanf("%29s", divisor);

    dataLen = strlen(data);
    divisorLen = strlen(divisor);

    if (divisorLen < 2 || dataLen + divisorLen - 1 >= 130)
    {
        printf("Invalid input length.\n");
        return 1;
    }

    for (i = 0; i < dataLen; i++)
    {
        if (data[i] != '0' && data[i] != '1')
        {
            printf("Invalid binary data.\n");
            return 1;
        }
    }

    for (i = 0; i < divisorLen; i++)
    {
        if (divisor[i] != '0' && divisor[i] != '1')
        {
            printf("Invalid generator bits.\n");
            return 1;
        }
    }

    if (divisor[0] != '1')
    {
        printf("Generator must start with 1.\n");
        return 1;
    }

    totalLen = dataLen + divisorLen - 1;

    strcpy(temp, data);

    for (i = dataLen; i < totalLen; i++)
        temp[i] = '0';

    temp[totalLen] = '\0';

    /* CRC generation */
    for (i = 0; i < dataLen; i++)
    {
        if (temp[i] == '1')
        {
            for (j = 0; j < divisorLen; j++)
                temp[i + j] =
                    (temp[i + j] == divisor[j]) ? '0' : '1';
        }
    }

    printf("\nCRC bits: ");
    for (i = dataLen; i < totalLen; i++)
        printf("%c", temp[i]);

    /* Append CRC bits to original data */
    strcpy(received, data);

    for (i = dataLen; i < totalLen; i++)
        received[i] = temp[i];

    received[totalLen] = '\0';

    printf("\nTransmitted data: %s\n", received);

    /* Receiver side */
    printf("\nEnter received data bits (%d bits): ", totalLen);
    scanf("%129s", temp);

    if ((int)strlen(temp) != totalLen)
    {
        printf("Invalid received data length.\n");
        return 1;
    }

    for (i = 0; i < totalLen; i++)
    {
        if (temp[i] != '0' && temp[i] != '1')
        {
            printf("Invalid received binary data.\n");
            return 1;
        }
    }

    /* CRC checking */
    for (i = 0; i <= totalLen - divisorLen; i++)
    {
        if (temp[i] == '1')
        {
            for (j = 0; j < divisorLen; j++)
                temp[i + j] =
                    (temp[i + j] == divisor[j]) ? '0' : '1';
        }
    }

    for (i = totalLen - divisorLen + 1; i < totalLen; i++)
    {
        if (temp[i] == '1')
            error = 1;
    }

    if (error == 0)
        printf("No error detected. Data accepted.\n");
    else
        printf("Error detected. Data rejected.\n");

    return 0;
}
