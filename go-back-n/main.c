#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TOTAL 10
#define WINDOW 4

int stimulate() {
    return rand() % 10 < 7;
}

int main() {
    srand(time(0));

    int base = 1, nextseq = 1;

    while (base <= TOTAL) {
        printf("\n--- Sending Window ---\n");
        while (nextseq < base + WINDOW && nextseq <= TOTAL) {
            printf("Sender sending packet %d\n", nextseq);
            nextseq++;
        }

        printf("\n--- ACKs ---\n");
        for (int i = base; i < nextseq; i++) {
            if (stimulate()) {
                printf("ACK received for packet %d\n", i);
                base++;
            } else {
                printf("ACK lost for packet %d - Resending from base %d\n", i, base);
                nextseq = base;
                break;
            }
        }

        sleep(1);
    }

    printf("\nAll packets sent and acknowledged!\n");
    return 0;
}
