#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Users{
    char name[20];
    int balance;
    char date[30];
}user;

struct Users* sortbydate(struct Users *user, size_t count){
    char tempname[BUFSIZ], tempdate[BUFSIZ];
    int i=0, j=0, tempbal = 0;

    for(i=0; i < count; i++) {
        for(j=0; j < count; j++){
            if(strcmp(user[i].date, user[j].date) < 0){
                // Save the values of user[i] to temp variables.
                strcpy(tempname, user[i].name);
                tempbal = user[i].balance;
                strcpy(tempdate, user[i].date);

                // Swap the values of the member with the lower date with next member of the struct.
                strcpy(user[i].name, user[j].name);
                user[i].balance = user[j].balance;
                strcpy(user[i].date, user[j].date);

                // Save the values of the last member from temp variables, back to the struct for further evaluation.
                strcpy(user[j].name, tempname);
                user[j].balance = tempbal;
                strcpy(user[j].date, tempdate);
            }
        }
    }

    // Return the struct sorted by the date in from oldest to newest.
    return user;
}

void spend(size_t count, struct Users *user, char **argv){
    int val = atoi(argv[1]);
    int i = 0, j = 0;

    // Loop through the array of structs and spend the points according to the conditions.
    for(i=0; i<count; i++){
        // If the user's balance is less than the given amount, subtract their points from their account as well as from the val
        if((val - user[i].balance) > 0 && val > 0){
            val -= user[i].balance;
            user[i].balance = 0;
        }else{ // If the user has more points than are left to spend, subtract the balance from val and set the balance equal to that number.
            user[i].balance = (user[i].balance - val);
            val = 0;
        }
    }

    // Print the output of the program.
    printf("\nOutput:\n");
    for(i=0; i<count; i++){
        for(j=0; i<count; i++){
            // Used to remove the printing of dublicates, if the user has more than one transaction create a sum of total balance and print that.
            if(strcmp(user[i].name, user[j].name) == 0 && user[i].balance == 0){
                user[i].balance += user[j].balance;
            }else{
                // If user does not have more than one transactcion, print the result after spending the points.
                printf("%s, %d, %s\n", user[i].name, user[i].balance, user[i].date);
            }
        }
    }
}

int main(int argc, char **argv){
    size_t rowcount = 0, i = 0;
    // Used to take the first value of the .csv since all three values are string.
    char headern[BUFSIZ], headerb[BUFSIZ], headerd[BUFSIZ];

    // Create struct to hold the users values.
    struct Users user[BUFSIZ];

    // Opens the .csv file
    FILE *data = fopen(argv[2], "r");

    // If the program can't open file, sent error and exit program.
    if(data == NULL){
        perror("Unable to open file.");
        exit(1);
    }

    // Reads the first row in .csv to account for all values being strings
    fscanf(data, "%[^,]%*c %[^,]%*c %s", headern, headerb, headerd);

    // Reads the rest of the lines in the csv while saving the values to the Users struct.
    while(fscanf(data, "%[^,]%*c %d%*c %[^\n]", user[rowcount].name, &user[rowcount].balance, user[rowcount].date) == 3){
        rowcount++;
    }

    // Print the given input.
    printf("\nGiven input:\n");
    for(i=0; i < rowcount; i++){
        printf("%s, %d, %s\n", user[i].name, user[i].balance, user[i].date);
    }
    printf("____________________________________________________________\n");

    struct Users *sorted = sortbydate(user, rowcount);

    spend(rowcount, sorted, argv);
}