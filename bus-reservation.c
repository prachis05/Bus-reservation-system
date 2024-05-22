#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Reservation {
    int PassnNo; // busNo0SeatNo.
    char name[10];
} tkt;

tkt reservations[100]; // Array to store reservations
int reservationCount = 0; // Count of reservations

int cost(int PassnNo);                //calculates costs
void status();                        // shows bus and seats status
void busLists();                      // shows buslist and do booking seat and return customer ID
void DisplaySeat(int bus[33]);        // Display the seats of buses
void cancel(int custID);              // cancel the booking
void reservationInfo(int custID);     // Display Reservation Info
void insert(int custID);              // inserting a reservation
void loadReservations();              // load reservations from file
void saveReservations();              // save reservations to file
void loadBusData();                   // load bus data from file
void loadUserCredentials();           // load user credentials from file
void login();                         // login function

int busSeat[32][33] = {0};
char userName[20];
char passWord[10];
char busDataFile[] = "busData.txt";
char userCredentialsFile[] = "userCredentials.txt";

void redColor() // Print the message in red color
{
    printf("\033[1;31m");
}

void resetColor() // reset the old color of console
{
    printf("\033[0m");
}

void loadUserCredentials()
{
    FILE *file = fopen(userCredentialsFile, "r");
    if (file == NULL) {
        perror("Error opening user credentials file");
        exit(EXIT_FAILURE);
    }


    fscanf(file, "%s %s", userName, passWord);

    fclose(file);
}

void loadBusData()
{
    FILE *file = fopen(busDataFile, "r");
    if (file == NULL) {
        perror("Error opening bus data file");
        exit(EXIT_FAILURE);
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
            int busNo,charges;
            char busName[20],destination[30],time[30];
            sscanf(line, "%d,%19[^,],%29[^,],%d,%9[^\n]", &busNo,busName,destination,&charges,time);

    }

    fclose(file);
}

void login()
{

    char matchPass[10];
    char matchUser[20];
    int value;

    redColor();
    printf("\n\n=========================================================================================\n");
    printf("\n\t\t\tWELCOME TO ONLINE BUS RESERVATION");
    printf("\n\n=========================================================================================\n\n");
    resetColor();

login:
    printf("\n\nUserName: ");
    fgets(matchUser, 20, stdin);
    matchUser[strcspn(matchUser, "\n")] = 0; // remove newline

    printf("\nPassWord: ");
    fgets(matchPass, 10, stdin);
    matchPass[strcspn(matchPass, "\n")] = 0; // remove newline

    value = strcmp(passWord, matchPass);
    if (value != 0 || strcmp(userName, matchUser)!= 0) {
        redColor();
        printf("\nINVALID DETAILS TRY AGAIN...\n");
        resetColor();
        goto login;
    } else {
        printf("\nLOGGED IN SUCCESSFULLY...\n");
    }
}

void reservationInfo(int custID) // find function
{
    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].PassnNo == custID) {
            int busNum = reservations[i].PassnNo / 1000;
            char *busRoute;

            // Determine the bus route based on the bus number
            switch (busNum) {
                case 1:
                    busRoute = "Pune to Mumbai";
                    break;
                case 2:
                    busRoute = "Mumbai to Pune";
                    break;
                case 3:
                    busRoute = "Mumbai to Goa";
                    break;
                case 4:
                    busRoute = "Pune to Aurangabad";
                    break;
                case 5:
                    busRoute = "Mumbai to Nashik";
                    break;
                case 6:
                    busRoute = "Pune to Nagpur";
                    break;
                case 7:
                    busRoute = "Pune to Amravati";
                    break;
                case 8:
                    busRoute = "Pune to Kolhapur";
                    break;
                case 9:
                    busRoute = "Mumbai to Solapur";
                    break;
                default:
                    busRoute = "Unknown Route";
                    break;
            }

            redColor();
            printf("\n-----------------------------------------------------------------\n");
            printf("||              NAME: %-10s                            ||\n", reservations[i].name);
            printf("||              CUSTOMER ID: %d                          ||\n", reservations[i].PassnNo);
            printf("||              BUS NUMBER: %d                           ||\n", busNum);
            printf("||              SEAT NUMBER: %d                          ||\n", reservations[i].PassnNo % 100);
            printf("||              TICKET COST: Rs.%d                       ||\n", cost(reservations[i].PassnNo));
            printf("||              ROUTE: %s                     ||\n", busRoute);
            printf("-----------------------------------------------------------------\n");
            resetColor();
            getchar();
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
        saveReservations(); // Save to file after inserting
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
    getchar(); // consume newline
    getchar();
}

void busLists()
{
    FILE *file = fopen(busDataFile, "r");
    if (file == NULL) {
        perror("Error opening bus data file");
        exit(EXIT_FAILURE);
    }

    char line[100];
    redColor();
    printf("-----------------------------------------------------------------------------------------");
    printf("\nBus.No\tName                \tDestinations          \tCharges\t   \t\tTime\n");
    printf("-----------------------------------------------------------------------------------------");
    resetColor();
    while (fgets(line, sizeof(line), file)) {
        char busName[40], destination[40], time[40];
        int busNo, charges;
        sscanf(line, "%d,%19[^,],%29[^,],%d,%9[^\n]" , &busNo, busName, destination, &charges, time);
        printf("\n%d\t%-20s\t%-20s\tRs.%-6d\t\t%-8s\n", busNo, busName, destination, charges, time);
    }
    fclose(file);
    printf("\n");
    printf("\n   PRESS 'ENTER' KEY TO CONTINUE ");
    getchar();
    getchar();
}

void cancel(int custID)
{
    int reservationNo;
    int seatNumber;
    int choice;
    char c;
    int seatCancel;

    reservationNo = custID;
    if (reservationNo == custID) {
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
                printf("\n\n   SEAT CANCELLED SUCCESSFULLY!!\n");
            }
        } else {
            printf("\n\nPLEASE ENTER THE CORRECT RESERVATION NUMBER.\n");
        }
    }
}

void saveReservations()
{
    FILE *file = fopen("reservations.txt", "w");
    if (file == NULL) {
        perror("Error opening reservations file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < reservationCount; i++) {
        fprintf(file, "%d %s\n", reservations[i].PassnNo, reservations[i].name);
    }

    fclose(file);
}

void loadReservations()
{
    FILE *file = fopen("reservations.txt", "r");
    if (file == NULL) {
        perror("Error opening reservations file");
        exit(EXIT_FAILURE);
    }

    reservationCount = 0;
    while (fscanf(file, "%d %s", &reservations[reservationCount].PassnNo, reservations[reservationCount].name) != EOF) {
        reservationCount++;
    }

    fclose(file);
}

int main()
{
    int num, i, custID, reservationNo;
    loadUserCredentials();
    loadBusData();
    loadReservations();
    login();

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
                busLists();
                printf("\n\n   ENTER THE BUS NUMBER: ");
                scanf("%d", &custID);
                if (custID <= 0 || custID >= 10) {
                    redColor();
                    printf("\n  PLEASE ENTER CORRECT BUS NUMBER !!\n");
                    resetColor();
                    break;
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
                printf("ENTER YOUR RESERVATION NUMBER: ");
                scanf("%d", &custID);
                cancel(custID);
                break;
            case 4:
                status();
                break;
            case 5:
                printf("   ENTER YOUR RESERVATION NUMBER: ");
                scanf("%d", &custID);
                reservationInfo(custID);
                break;
            case 6:
                saveReservations();
                exit(0);
                break;
            default:
                printf("\n  ENTER THE CORRECT OPTION: ");
                break;
        }
    } while (num != 6);
    return 0;
}
