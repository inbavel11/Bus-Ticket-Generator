#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PLACES 5
#define MAX_SEATS 40
#define BASE_TICKET_NUMBER 5533101

const char *places[MAX_PLACES] = {"Chennai", "Vellore", "Vilupuram", "Madurai", "Nellai"};
int ticket_counter = BASE_TICKET_NUMBER;

void print_time() {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char date[20];
    strftime(date, 20, "%Y-%m-%d %H:%M:%S", tm_info);
    printf("\tDate and Time: %s\n", date);
}

void print_places() {
    printf("\tMetro Transport Corporation\n");
    for (int i = 0; i < MAX_PLACES; i++) {
        printf("\t%d - %s\n", i + 1, places[i]);
    }
}

void print_seats(int seats[MAX_SEATS]) {
    printf("Available Seats:\n");
    for (int i = 0; i < MAX_SEATS; i++) {
        if (seats[i] == 0) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
}

void generate_ticket(int start, int end, int num_tickets, int seat_numbers[MAX_SEATS]) {
    printf("\tMetro Transport Corporation\n");
    if (num_tickets == 1) {
        printf("\tTicket No: %d\n", ticket_counter);
    } else {
        printf("\tTicket Nos: %d - %d\n", ticket_counter, ticket_counter + num_tickets - 1);
    }

    printf("\t%s to %s\n", places[start - 1], places[end - 1]);
    print_time();
    printf("\tNumber of Passengers: %d\n", num_tickets);
    printf("\tSeat Numbers: ");
    for (int i = 0; i < num_tickets; i++) {
        printf("%d ", seat_numbers[i]);
    }
    printf("\n\tTotal Fare: ₹%d\n", num_tickets * abs(end - start) * 200);
    printf("\t\t     Happy Journey!\n\n");

    ticket_counter += num_tickets;
}

int process_payment(int amount) {
    int payment_success;
    printf("Processing payment of ₹%d...\n", amount);
    // Simulate payment processing
    payment_success = rand() % 2;
    if (payment_success) {
        printf("Payment successful!\n");
    } else {
        printf("Payment failed. Please try again.\n");
    }
    return payment_success;
}

int main() {
    int start, end, num_tickets, seats[MAX_SEATS] = {0}, seat_numbers[MAX_SEATS];

    srand(time(NULL));

    while (1) {
        print_places();
        printf("Enter starting point (0 to exit): ");
        scanf("%d", &start);
        if (start == 0) break;

        if (start < 1 || start > MAX_PLACES) {
            printf("Invalid starting point. Please try again.\n");
            continue;
        }

        printf("Enter destination point (0 to exit): ");
        scanf("%d", &end);
        if (end == 0) break;

        if (end < 1 || end > MAX_PLACES || end == start) {
            printf("Invalid destination point. Please try again.\n");
            continue;
        }

        printf("Enter number of tickets: ");
        scanf("%d", &num_tickets);
        if (num_tickets <= 0 || num_tickets > MAX_SEATS) {
            printf("Invalid number of tickets. Please try again.\n");
            continue;
        }

        print_seats(seats);
        printf("Select your seats: ");
        for (int i = 0; i < num_tickets; i++) {
            int seat;
            scanf("%d", &seat);
            if (seat < 1 || seat > MAX_SEATS || seats[seat - 1] == 1) {
                printf("Invalid seat selection. Please try again.\n");
                i--;
                continue;
            }
            seats[seat - 1] = 1;
            seat_numbers[i] = seat;
        }

        int fare = num_tickets * abs(end - start) * 200;
        if (process_payment(fare)) {
            generate_ticket(start, end, num_tickets, seat_numbers);
        } else {
            // Reset seat selection on payment failure
            for (int i = 0; i < num_tickets; i++) {
                seats[seat_numbers[i] - 1] = 0;
            }
        }
    }

    printf("Exiting...\n");
    return 0;
}
