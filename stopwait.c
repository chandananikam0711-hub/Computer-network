#include <stdio.h>

int main()
{
    int frames, i;

    printf("Enter the number of frames to be sent: ");

    if (scanf("%d", &frames) != 1 || frames <= 0)
    {
        printf("Please enter a valid positive number.\n");
        return 1;
    }

    for (i = 1; i <= frames; i++)
    {
        printf("\nSender: Sending frame %d\n", i);
        printf("Receiver: Frame %d received\n", i);
        printf("Receiver: Sending ACK %d\n", i);
        printf("Sender: ACK %d received\n", i);
        printf("Frame %d transmitted successfully\n", i);
    }

    printf("\nAll frames transmitted successfully.\n");

    return 0;
}
