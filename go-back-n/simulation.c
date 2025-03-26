#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int total_frames, window_size, total_transmissions = 0, current_frame = 1;

void transmit_frames()
{
    while (current_frame <= total_frames)
    {
        int successfully_transmitted = 0;

        // Sending frames within the window
        for (int frame = current_frame; frame < current_frame + window_size && frame <= total_frames; frame++)
        {
            printf("Sending frame %d...\n", frame);
            total_transmissions++;
        }

        // Receiving acknowledgments
        for (int frame = current_frame; frame < current_frame + window_size && frame <= total_frames; frame++)
        {
            int ack_received = rand() % 2; // Randomly simulate success (1) or failure (0)

            if (ack_received)
            {
                printf("Acknowledgment received for frame %d.\n", frame);
                successfully_transmitted++;
            }
            else
            {
                printf("Timeout! Frame %d not received.\n", frame);
                printf("Retransmitting window...\n");
                break; // Go-Back-N: retransmit from the first unacknowledged frame
            }
        }

        printf("\n");
        current_frame += successfully_transmitted; // Move forward only for acknowledged frames
    }
}

int main()
{
    srand(time(NULL)); // Seed the random number generator

    // Get user input
    printf("Enter the total number of frames: ");
    scanf("%d", &total_frames);

    printf("Enter the window size: ");
    scanf("%d", &window_size);

    // Start transmission
    transmit_frames();

    // Print the total number of frames sent (including retransmissions)
    printf("Total number of frames sent (including retransmissions): %d\n", total_transmissions);

    return 0;
}