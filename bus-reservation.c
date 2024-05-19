#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

typedef struct Reservation {
    int PassnNo; // busNo0SeatNo.
    char name[10];
} tkt;

tkt reservations[100]; // Array to store reservations
int reservationCount = 0; // Count of reservations

int cost(int PassnNo);                // calculates costs
void status();                        // shows bus and seats status
void busLists();                      // shows buslist and do booking seat and return customer ID
void DisplaySeat(int bus[33]);        // Display the seats of buses
void cancel(int x);                   // cancel the booking
void reservationInfo(int custID);     // Display Reservation Info
void insert(int custID);              // inserting a reservation

int busSeat[32][9] = {0};

void redColor() // Print the message in red color
{
    printf("\033[1;31m");
}

void resetColor() // reset the old color of console
{
    printf("\033[0m");
}

void reservationInfo(int custID) // find function
{
    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].PassnNo == custID) {
            redColor();
            printf("\n-----------------------------------------------------------------\n");
            printf("||              NAME: %-10s                            ||\n", reservations[i].name);
            printf("||              CUSTOMER ID: %d                          ||\n", reservations[i].PassnNo);
            printf("||              BUS NUMBER: %d                           ||\n", reservations[i].PassnNo / 1000);
            printf("||              SEAT NUMBER: %d                          ||\n", reservations[i].PassnNo % 100);
            printf("||              TICKET COST: Rs.%d                       ||\n", cost(reservations[i].PassnNo));
            printf("-----------------------------------------------------------------\n");
            resetColor();
            getch();
            return;
        }
    }
    redColor();
    printf("\nRESERVATION NOT FOUND\n");
    resetColor();
}

void insert(int custID)
{
    if (reservationCount < 100) {
        reservations[reservationCount].PassnNo = custID;
        printf("\n   ENTER THE PERSON NAME: ");
        scanf("%s", reservations[reservationCount].name);
        printf("   YOUR RESERVATION NUMBER IS: %d\n", custID); // Display the reservation number
        reservationCount++;
    } else {
        printf("No memory…");
    }
}

void DisplaySeat(int bus[33])
{
    for (int i = 1; i <= 32; i++) {
        redColor();
        if (i < 10 && i > 0) {
            printf("0%d .", i);
        } else {
            printf("%d .", i);
        }

        resetColor();
        if (bus[i] == 0)
            printf("EMPTY ");
        else
            printf("BOOKED");
        printf("         ");
        if (i % 4 == 0)
            printf("\n");
    }
}

void login()
{
    char userName[20] = "user";
    char passWord[10] = "team18";
    char matchPass[10];
    char matchUser[10];
    int value;

    redColor();
    printf("\n\n=========================================================================================\n");
    printf("\n\t\t\tWELCOME TO ONLINE BUS RESERVATION");
    printf("\n\n=========================================================================================\n\n");
    resetColor();

login:
    printf("\n\nUserName: ");
    gets(matchUser);

    printf("\nPassWord: ");
    gets(matchPass);

    value = strcmp(passWord, matchPass);
    if (value != 0) {
        redColor();
        printf("\nINVALID DETAILS TRY AGAIN...\n");
        resetColor();
        goto login;
    } else {
        printf("\nLOGGED IN SUCCESSFULLY...\n");
    }
}

int cost(int PassnNo)
{
    int buscost = PassnNo / 1000;
    switch (buscost % 3) {
    case 1:
        return 70;
    case 2:
        return 55;
    case 0:
        return 40;
    default:
        return 0;
    }
}

void status()
{
    int busNum;
    busLists();
busInput:
    printf("\n\nENTER YOUR BUS NUMBER: ");
    scanf("%d", &busNum);
    if (busNum <= 0 || busNum >= 10) {
        redColor();
        printf("\n  PLEASE ENTER CORRECT BUS NUMBER !!\n");
        resetColor();
        goto busInput;
    }
    printf("\n");
    DisplaySeat(busSeat[busNum]);
    getch();
}

void busLists()
{
    redColor();
    printf("-----------------------------------------------------------------------------------------");
    printf("\nBus.No\tName\t\t\tDestinations  \t\tCharges  \t\tTime\n");
    printf("-----------------------------------------------------------------------------------------");
    resetColor();
    printf("\n1\tGangaTravels         \tPune to Mumbai       \tRs.70   \t\t07:00  AM");
    printf("\n2\tMSRTC Travels     \tMumbai To Pune       \tRs.55    \t\t01:30  PM");
    printf("\n3\tShiv Ganga Travels   \tMumbai To Goa\tRs.40    \t\t03:50  PM");
    printf("\n4\tSuper Deluxe         \tPune To Aurangabad    \tRs.70    \t\t01:00  AM");
    printf("\n5\tSai Baba Travels     \tMumbai To Nashik \tRs.55    \t\t12:05  AM");
    printf("\n6\tShine On Travels     \tPune to Nagpur    \tRs.40    \t\t09:30  AM");
    printf("\n7\tMayur Travels        \tPatna To Gaya         \tRs.70   \t\t11:00  PM");
    printf("\n8\tSai Travels       \tPune To Kolhapur     \tRs.55    \t\t08:15  AM");
    printf("\n9\tShree Travels        \tMumbai  To Solapur      \tRs.40    \t\t04:00  PM");
    printf("\n");
    printf("\n   PRESS 'ENTER' KEY TO CONTINUE ");
    getch();
}

void cancel(int randomNum)
{
    int reservationNo;
    int seatNumber;
    int choice;
    char c;
    int seatCancel;

aa:
    printf("\nENTER YOUR RESERVATION NUMBER: ");
    scanf("%d", &reservationNo);
    if (reservationNo == randomNum) {
        printf("\nRESERVATION NUMBER IS IT CORRECT? %d \nENTER (Y/N): ", reservationNo);
        scanf(" %c", &c);
        if (c == 'y' || c == 'Y') {
            printf("\n\n============================================\n\n");
            printf("   ENTER THE BUS NUMBER: ");
            scanf("%d", &choice);

            printf("\n HOW MANY SEATS DO YOU WANT TO CANCEL: ");
            scanf("%d", &seatCancel);
            for (int i = 0; i < seatCancel; i++) {
                printf("   \nENTER THE SEAT NUMBER: ");
                scanf("%d", &seatNumber);

                busSeat[choice][seatNumber] = 0;
            }
            printf("\n\nYOUR RESERVATION HAS BEEN CANCELLED !!\n\n");
            printf("\n  PRESS 'ENTER' KEY TO CONTINUE \n");
            getch();
            DisplaySeat(busSeat[choice]);
        } else if (c == 'n' || c == 'N') {
            printf("\nYOUR RESERVATION CANCELLATION HAS BEEN DENIED\n");
        }
    } else {
        printf("\nNOT FOUND!! ENTER THE CORRECT RESERVATION NUMBER\n");
        goto aa;
    }
}

int main()
{
    srand(time(0));
    int randomNum = rand();
    int num, i, custID, reservationNo;
    login();

main:
    do {
        printf("\n\n====================================================================\n\n");
        printf("\t\t\t\033[1;31mBUS RESERVATION\033[0m\t\t");
        printf("\n\n=====================================================================\n");
        printf("\n====================");
        redColor();
        printf("  MAIN MENU ");
        resetColor();
        printf("=====================\n\n");
        printf("   \033[1;31m[1]\033[0m VIEW BUS LIST \n\n");
        printf("   \033[1;31m[2]\033[0m BOOK TICKETS\n\n");
        printf("   \033[1;31m[3]\033[0m CANCEL BOOKING\n\n");
        printf("   \033[1;31m[4]\033[0m BUSES SEATS INFO\n\n");
        printf("   \033[1;31m[5]\033[0m RESERVATION INFO\n\n");
        printf("   \033[1;31m[6]\033[0m EXIT\n");
        printf("\n=====================================================\n");
        printf("\n   ENTER YOUR CHOICE: ");
        scanf("%d", &num);

        switch (num) {
            case 1:
                busLists();
                break;
            case 2:
bb:
                printf("\n\n   ENTER THE BUS NUMBER: ");
                scanf("%d", &custID);
                if (custID <= 0 || custID >= 10) {
                    redColor();
                    printf("\n  PLEASE ENTER CORRECT BUS NUMBER !!\n");
                    resetColor();
                    goto bb;
                }
                DisplaySeat(busSeat[custID]);
                printf("\n\n   HOW MANY SEATS YOU WANT TO BOOK: ");
                scanf("%d", &i);
                for (int k = 0; k < i; k++) {
                    printf("   ENTER THE SEAT NUMBER: ");
                    scanf("%d", &reservationNo);
                    busSeat[custID][reservationNo] = 1;
                    insert((custID * 1000) + reservationNo);
                }
                printf("\n\nYOUR RESERVATION DONE SUCCESSFULLY!!\n");
                break;
            case 3:
                cancel(randomNum); // for cancelling the seats
                break;
            case 4:
                status(); // for bus status if booked or not
                break;
            case 5:
                printf("   ENTER YOUR RESERVATION NUMBER: ");
                scanf("%d", &custID);
                reservationInfo(custID); // for printing customer details
                break;
            case 6:
                exit(0); // for exiting from the program
                break;
            default:
                printf("\n  ENTER THE CORRECT OPTION: ");
                break;
        }
    } while (num != 6);
    return 0;
}
