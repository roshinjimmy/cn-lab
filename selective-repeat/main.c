#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define TOTAL_PACKETS 10
#define WINDOW_SIZE 4

int simulate_acknowledgement() {
    return rand() % 10 < 7;
}

int main() {
    srand(time(0));
    
    int base = 1;
    int ack[TOTAL_PACKETS + 1] = {0};

    while (base <= TOTAL_PACKETS) {
        printf("\n--- Sending Window ---\n");

        for (int i = base; i < base + WINDOW_SIZE && i <= TOTAL_PACKETS; i++) {
            if (!ack[i]) {
                printf("Sender: Sending packet %d\n", i);
            }
        }

        sleep(2);

        printf("\n--- Receiving ACKs ---\n");
        for (int i = base; i < base + WINDOW_SIZE && i <= TOTAL_PACKETS; i++) {
            if (!ack[i]) {
                if (simulate_acknowledgement()) {
                    printf("ACK for packet %d received\n", i);
                    ack[i] = 1;
                } else {
                    printf("ACK for packet %d lost. Will resend later\n", i);
                }
            }
        }

        while (ack[base] && base <= TOTAL_PACKETS) {
            base++;
        }

        sleep(1);
    }

    printf("\nAll packets received successfully!\n");
    return 0;
}
