#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>      ///used for tolower() function


typedef struct{          ///structure for date of birth of members.
    int year;
    int month;
    int day;
}date;


typedef struct {            ///structure to save the members data
    char * nick_name;
    char * family_name;
    char * given_name;
    char * place;
    char ** group;
    int group_total;
    date birth;
} member;


typedef struct{           ///this structure will store the all the members of facebook and the total number of members.
    int total;
    member * users;
}statistics;


member* add_new(statistics * data); ///job of this is to create the member that we will add to users list and put the the name arrays in the structure.

char* add_name();  ///job of this is to create the dynamically allocated memory for the name strings.

date add_date();                      ///function to read date from user check validity and store it.

void print_all_members(statistics data);         ///the following function prints all the members data in the console.

void print_single_user(member profile);          ///the following function prints the data of a particular member.

statistics delete_member(statistics data);       ///deletes a member from the data

void search_member(statistics data);        ///searches a member in the data

statistics add_in_list(member * to_add, statistics old);        ///adds the new member in the data

int improper_name(char * check);             ///checks if the name is improper

void add_group(int *total,char*** group);         ///adds a member in group when a new member data is stored

void print_group_members(statistics data);       ///prints all the member of a particular group

void adding_in_group(char * group_to_add, char*** group_array, int * total);

void add_member_in_group(statistics * data);

void read_from_file(statistics * data);       ///loads the data from the file into the memory

void print_in_file(statistics *data);        /// saves the updated/new data in the file

void deleting_in_group(int index, char*** group_array, int * total);

void delete_member_in_group(statistics * data);

int main(){


    int choice = 0;           ///declaring choice variable for switch case
    statistics data;         /// the structure will store the data of all members and their count
    data.total = 0;
    data.users = NULL;
    member * add;


    read_from_file(&data);        ///fetching the data from file


    printf("\tApplication started succesfully\n");

    do
    {
        printf("\tWelcome to Facebook database\n\n");   ///printing the menu
        printf("\tplease select the task:\n\n");

        printf("\t1. Enter a new member in the data.\n");
        printf("\t2. search a member in the data.\n");
        printf("\t3. delete a member in the data.\n");
        printf("\t4. add a member in a group\n");
        printf("\t5. remove a group member.\n");
        printf("\t6. list all group members.\n");
        printf("\t7. list all the members in the data.\n");
        printf("\t8. Exit the program\n\t");


        scanf("%d" , &choice);
        fflush(stdin);             ///flushing the buffer incase of a non number character

        switch(choice){
            case 1:
                add = add_new(&data);          ///creates new member
                data = add_in_list(add,data);   ///adding the new member in the group

                printf("\n\tData registry succesful\n\n");

                break;

            case 2:
                if(data.total > 0)
                   search_member(data);                  ///searching a member by nickname or family name
                else
                    printf("\tThere are no members to search\n");


                break;
            case 3:
                if(data.total > 0){          //if we have a record of atleast one user then we will run the function.

                   data = delete_member(data);
                    //run the delete function

                }
                else{
                    printf("\tthere are no members to delete.\n");
                }

                break;
            case 4:
                if(data.total > 0)
                   add_member_in_group(&data);
                else
                    printf("No members in the data");
                break;
            case 5:
                delete_member_in_group(&data);
                break;
            case 6:
                if(data.total > 0)
                    print_group_members(data);
                else
                   printf("\tthere are no members to print");
                break;

            case 7:
                //printing all the members in the data;
                if(data.total > 0){
                   print_all_members(data);
                }
                else {
                    printf("\tthere are no members to print");
                }

                break;
            case 8:
                print_in_file(&data);                  ///saving all the data in the file.
                for(int i = 0; i < data.total; i++){               ///freeing all the memory after we are done
                    free(data.users[i].nick_name);
                    free(data.users[i].family_name);
                    free(data.users[i].given_name);
                    free(data.users[i].place);

                    for(int j = 0; j < data.users[i].group_total; j++)
                        free(data.users[i].group[j]);

                    free(data.users[i].group);
                }

                free(data.users);

                printf("\n\n\tGood Bye!");

                break;
            default:
                printf("\n\n\tPlease enter a number among 1 and 8\n\n");

        }
    }while(choice != 8);

    return 0;
}

void print_all_members(statistics data){

    for(int i = 0; i < data.total; i++){
        printf("\n\n\tNickName: %s\n" , data.users[i].nick_name);
        printf("\tfamilyName: %s\n"   , data.users[i].family_name);
        printf("\tgivenName: %s\n"    , data.users[i].given_name);
        printf("\tBirth Place: %s\n"  , data.users[i].place);
        printf("\tDate of Birth(yy/mm/dd): %d/%d/%d\n", data.users[i].birth.year, data.users[i].birth.month, data.users[i].birth.day);
        printf("\tThe user joined %d group(s)\n" , data.users[i].group_total);
        for(int j = 0; j < data.users[i].group_total; j++)
            printf("\tgroup%d: %s\n" , j+1 , data.users[i].group[j]);

        printf("\t-------------------------------------\n\n");
    }


}


void print_single_user(member profile){

    printf("\n\n\tNickName: %s\n" , profile.nick_name);
    printf("\tfamilyName: %s\n"   , profile.family_name);
    printf("\tgivenName: %s\n"    , profile.given_name);
    printf("\tBirth Place: %s\n"  , profile.place);
    printf("\tDate of Birth(yy/mm/dd): %d/%d/%d\n", profile.birth.year, profile.birth.month, profile.birth.day);
    printf("\tThe user joined %d group(s)\n" , profile.group_total);
       for(int j = 0; j < profile.group_total; j++)
          printf("\tgroup%d: %s\n" , j+1 , profile.group[j]);
    printf("\t-------------------------------------\n");


}


void search_member(statistics data){


    printf("\tPlease select among the following options:\n");
    printf("\t1. Search by family name.\n");
    printf("\t2. Search by nick name.\n\t");
    int choice;
    scanf("%d" , &choice);

    int match = 0;

    switch(choice){
           case 1:
               printf("\tEnter family name: ");
               char* family_name = add_name();      ///asking for family name from the user
               for(int i = 0; i < data.total; i++){
                   if(strcmp(data.users[i].family_name,family_name) == 0){
                        match++;
                        print_single_user(data.users[i]);
                   }
               }
               free(family_name);          ///freeing the memory after comparision
               break;
           case 2:
               printf("\tEnter Nick name: ");
               char* nick_name = add_name();      ///asking for nickname from the user
               for(int i = 0; i < data.total; i++){
                   if(strcmp(data.users[i].nick_name,nick_name) == 0){
                        match++;
                        print_single_user(data.users[i]);
                   }
               }
               free(nick_name);            ///freeing the memory afte comparision
               break;
           default:
               printf("\tPlease enter among the selected number!\n");
               break;

    }
    if (match==0)
        printf("\n\tNo match found\n\n");

}



char* add_name(){
    int cnt = 0;
    fflush(stdin);

    char * line = (char *)malloc(sizeof(char));            ///intializing an empty dynamic array
    line[0] = '\0';
    char newchar;
    while(scanf( "%c", &newchar) == 1 && newchar != '\n'){    ///reads the string input character by character until newline
        char * tmp = (char*)malloc((cnt+1+ 1) * sizeof(char));   ///allocates a new array to store the new character
        for(int i = 0; i < cnt ; i++)
            tmp[i] = line[i];                    ///copies all the previous characters from the current array in the new array
        tmp[cnt] = newchar;                     ///stores the new character
        tmp[cnt + 1] = '\0';                   ///adding the terminating 0
        free(line);                            ///freeing the current array
        line = tmp;                            ///new array is now the current array
        cnt++;
    }
    return line;
};



int leap_year(int year){                       // this is to check whether the the given year is a leap year or not.
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
       return 1;
    return 0;
}


int invalid_date(date tmp){      // this function is for checking the validity of the date.

    return tmp.year < 1 || tmp.year > 2023 || tmp.month< 1 || tmp.month> 12 || tmp.day < 1 || tmp.day > 31 ||
    (tmp.month==2 && tmp.day > 29)||
    (!leap_year(tmp.year) && tmp.month == 2 && tmp.day > 28);
}


date add_date(){                  ///creates the date of the new member

    date tmp;
    printf("\tEnter date of birth(yy/mm/dd): ");
    scanf("%d %d %d", &tmp.year,&tmp.month, &tmp.day);
    fflush(stdin);
    while(invalid_date(tmp)){
        printf("\tInvalid date, please enter the date again : ");
        scanf("%d %d %d", &tmp.year, &tmp.month, &tmp.day);
        fflush(stdin);
    }
    return tmp;
};


int improper_name(char * check){

    for(int i = 0; check[i] != '\0' ; i++)
        if(!(check[i] >= 'A' && check[i] <= 'Z') && !(check[i] >= 'a' && check[i] <= 'z')){   ///checks if it is in range (A-Z) and range (a-z) or not
            free(check);             ///if not in the range then we discard it and free the array
            return 1;
        }

    return 0;
}


void add_group(int *total,char*** group){

    printf("\tHow many groups to add?:");
    scanf("%d" , total);

    *group = (char**)malloc((*total) * sizeof(char*));

    for(int i = 0;i < *total; i++){
        printf("\tEnter group%d: " , i+1);
        (*group)[i] = add_name();
    }
    return;

}


int nickname_exists(statistics* data,char * nickname){
    for(int i = 0;i < data->total;i++)
        if(strcmp(data->users[i].nick_name,nickname)==0){
            free(nickname);
            return 1;
        }

    return 0;
}


member * add_new(statistics * data){

    member *tmp = (member*)malloc(sizeof(member));   ///allocating a member structure to store the data of new member.
    char choice;

    printf("\tEnter nickname:");
    tmp->nick_name = add_name();
    while(improper_name(tmp->nick_name) || nickname_exists(data,tmp->nick_name)){   ///handling exception of user giving the same nicknames
        printf("\tNick name is incorrect or already exists: ");
        tmp->nick_name = add_name();
    }

    printf("\tEnter familyname:");
    tmp->family_name = add_name();
     while(improper_name(tmp->family_name)){
        printf("\tPlease enter family name with only letters:");
        tmp->family_name = add_name();
    }

    printf("\tEnter givenname:");
    tmp->given_name = add_name();
     while(improper_name(tmp->given_name)){
        printf("\tPlease enter given name with only letters:");
        tmp->given_name = add_name();
    }

    printf("\tEnter birthplace:");
    tmp->place = add_name();
     while(improper_name(tmp->place)){
        printf("\tPlease enter birthplace with only letters:");
        tmp->place= add_name();
    }
    tmp->group_total = 0;              ///in case the user doesnt add any group while creating a new member
    tmp->group = NULL;                 ///we avoid having dangling pointers


    tmp->birth = add_date();

    printf("\tDo you want to enter group?(Y/N):");
    scanf("%c" , &choice);
    while(tolower(choice) != 'y' && tolower(choice) != 'n'){   ///exception handling
        printf("\tInput Error\n");
        fflush(stdin);
        printf("\tDo you want to enter group?(Y/N):");
        scanf("%c" , &choice);
    }


    if(tolower(choice) == 'y')
       add_group(&(tmp->group_total),&tmp->group);


    return tmp;
}

statistics add_in_list(member * to_add, statistics old){

    int size = old.total;                                          //fetching the the total users already listed
    member * new = (member*)malloc((size+1) * sizeof(member));
    for(int i = 0; i < size; i++){

        new[i].nick_name   = old.users[i].nick_name;               //copying all the old members in the array(database)
        new[i].family_name = old.users[i].family_name;
        new[i].given_name  = old.users[i].given_name;
        new[i].place       = old.users[i].place;
        new[i].birth.year  = old.users[i].birth.year;
        new[i].birth.month = old.users[i].birth.month;
        new[i].birth.day   = old.users[i].birth.day;
        new[i].group_total = old.users[i].group_total;
        new[i].group       = old.users[i].group;

    }

    new[size].nick_name   = to_add->nick_name;                    //copying the new member in the database
    new[size].family_name = to_add->family_name;
    new[size].given_name  = to_add->given_name;
    new[size].place       = to_add->place;
    new[size].birth.year  = to_add->birth.year;
    new[size].birth.month = to_add->birth.month;
    new[size].birth.day   = to_add->birth.day;
    new[size].group_total = to_add->group_total;
    new[size].group       = to_add->group;


    free(old.users);                        ///freeing the old array

    old.users = new;                        ///the new array is stored in the old array
    old.total = old.total + 1;             ///incrementing count by 1

    free(to_add);                       ///freeing the structure memory that we have added in the array

    return old;
}


statistics delete_member(statistics data){

    printf("\tEnter the nickname of the user to be deleted: ");
    char * nick_name = add_name();
    int size = 0;
    member* new;
    for(int i = 0;i < data.total;i++){
        if(strcmp(data.users[i].nick_name,nick_name) == 0){             ///if we get a match we are creating a new dynamic array with one less size and put all the
                                                                        ///data in it except the one to be deleted
            free(data.users[i].nick_name);                 ///freeing the deleted member strings.
            free(data.users[i].family_name);
            free(data.users[i].given_name);
            free(data.users[i].place);

            for(int j = 0; j < data.users[i].group_total; j++){
                free(data.users[i].group[j]);
            }
            free(data.users[i].group);

            size = data.total;
            new = NULL;
            new = (member*)malloc((size-1) * sizeof(member));

            for(int j = 0,k = 0; j < size -1 ;j++,k++){
                if( j == i){                                /// i is the index which has to be deleted.
                    k++;
                }

                new[j].nick_name   = data.users[k].nick_name;
                new[j].family_name = data.users[k].family_name;
                new[j].given_name  = data.users[k].given_name;
                new[j].place       = data.users[k].place;
                new[j].birth.year  = data.users[k].birth.year;
                new[j].birth.month = data.users[k].birth.month;
                new[j].birth.day   = data.users[k].birth.day;
                new[j].group_total = data.users[k].group_total;
                new[j].group       = data.users[k].group;

            }


            free(data.users);

            data.users = new;
            data.total = data.total - 1;
            printf("\tUser deleted");
            break;

        }


    }

    free(nick_name);


    return data;

}


void print_group_members(statistics data){

    printf("\tEnter a group name: ");
    char * group_name = add_name();

    for(int i = 0; i < data.total;i++)
        for(int j = 0; j < data.users[i].group_total; j++){
             if(strcmp(data.users[i].group[j],group_name) == 0){
                print_single_user(data.users[i]);
                break;                    ///since every member have unique group names we dont need to further iterate the loop if we find the groupname
             }
        }
    free(group_name);
}


void add_member_in_group(statistics * data){

    printf("\tEnter user nick name: ");
    char * nick_name = add_name();

    printf("\tEnter the group name: ");
    char * group = add_name();
    while(improper_name(group)){
        printf("Enter apropiate_name: ");
        group = add_name();
    }

    for(int i = 0;i < data->total; i++){
        if(strcmp(data->users[i].nick_name,nick_name) == 0){
            for(int j = 0; j < data->users[i].group_total;j++)
               if(strcmp(data->users[i].group[j],group) == 0){
                  free(group);
                  free(nick_name);
                  printf("\tThe member is already in the group\n");
                  return;
               }
            adding_in_group(group , &data->users[i].group , &data->users[i].group_total);
            printf("\tmember added in the group :)\n\n");
            free(nick_name);
            return;
        }
    }

    printf("\tNo member with this nick name exists\n\n");
    free(group);

    free(nick_name);

    return;
}


void adding_in_group(char * group_to_add, char*** group_array, int * total){

    int size = *total;
    char ** new = (char**)malloc((size+1) * sizeof(char *));

    for(int i = 0;i < size; i++){
        new[i] = (*group_array)[i];
    }
    new[size] = group_to_add;

    free(*group_array);

    *group_array = new;
    *total = size + 1;

    return;
}


void read_from_file(statistics * data){

    FILE *fptr;
    char buffer[200];            ///reads the data from the file line by line
    fptr = fopen("Facebook.txt" , "r");
    if (fptr != NULL)
    {
        while(fgets(buffer , sizeof(buffer) , fptr) != NULL){      ///while we are getting data
            member * adding = (member*)malloc(sizeof(member));
            adding->nick_name    = strdup(strtok(buffer, " "));  ///using string tokenization to get the nickname and strdup to get a dynamic string
            adding->family_name  = strdup(strtok(NULL , " "));
            adding->given_name   = strdup(strtok(NULL , " "));
            adding->place        = strdup(strtok(NULL , " "));
            adding->birth.year   = (int)strtol(strtok(NULL , " "),NULL,10);      ///fetching int from file strtol function converts string to long int.
            adding->birth.month  = (int)strtol(strtok(NULL , " "),NULL,10);
            adding->birth.day    = (int)strtol(strtok(NULL , " "),NULL,10);
            adding->group_total  = (int)strtol(strtok(NULL , " "),NULL,10);
            adding->group = NULL;
            if(adding->group_total != 0){                   ///since we saved how many groups the user is in we can read the data accordingly
                char * portion;
                char ** group_array = (char**)malloc(sizeof(char*) * (adding->group_total));
                int  i;
                for(i = 0; i < (adding->group_total)-1;i++){         ///running a loop till the second last group name
                    portion = strdup(strtok(NULL, " "));
                    group_array[i] = portion;

                }
                portion = strdup(strtok(NULL,"\n"));                   ///the last one ends with a newline.
                group_array[i] = portion;                              ///the last one is loaded.

                adding->group = group_array;

            }
            *data = add_in_list(adding,*data);             ///adds the member in the structure
        }
        fclose(fptr);
    }
    return;

}


void print_in_file(statistics *data){
     FILE * fptr;
     fptr = fopen("Facebook.txt" , "w");          ///opens the file in write mode, if there is no file then creates new one
     if(fptr == NULL){
        printf("Error opening file");
        return;
     }
     for(int i = 0; i < data->total ; i++){
        if(data->users[i].group_total == 0){                   ///if the user is in no group then simply save till group total
            fprintf(fptr,"%s %s %s %s %d %d %d %d \n",data->users[i].nick_name
                                                ,data->users[i].family_name
                                                ,data->users[i].given_name
                                                ,data->users[i].place
                                                ,data->users[i].birth.year
                                                ,data->users[i].birth.month
                                                ,data->users[i].birth.day
                                                ,data->users[i].group_total);
        }
        else                                    ///we also the save the groups the user is in
            {
              fprintf(fptr,"%s %s %s %s %d %d %d %d",data->users[i].nick_name
                                                ,data->users[i].family_name
                                                ,data->users[i].given_name
                                                ,data->users[i].place
                                                ,data->users[i].birth.year
                                                ,data->users[i].birth.month
                                                ,data->users[i].birth.day
                                                ,data->users[i].group_total);
              for(int j = 0; j < data->users[i].group_total;j++){
                fprintf(fptr," %s",data->users[i].group[j]);
              }
              fprintf(fptr,"\n",NULL);
            }
     }
     fclose(fptr);
}

void delete_member_in_group(statistics * data){

    printf("\tEnter user nick name: ");
    char * nick_name = add_name();

    printf("\tEnter the group name to delete: ");
    char * group = add_name();
    while(improper_name(group)){
        printf("Enter apropiate_name: ");
        group = add_name();
    }

    for(int i = 0;i < data->total; i++){
        if(strcmp(data->users[i].nick_name,nick_name) == 0){
            for(int j = 0; j < data->users[i].group_total;j++)
               if(strcmp(data->users[i].group[j],group) == 0){
                  free(data->users[i].group[j]);
                  deleting_in_group( j, &data->users[i].group ,&data->users[i].group_total);

                  free(group);
                  free(nick_name);



                  printf("\tThe member is deleted from the group:) \n\n");
                  return;
               }
            printf("\tmember is not in the group :)\n\n");
            free(group);
            free(nick_name);
            return;
        }
    }

    printf("\tNo member with this nick name exists\n\n");
    free(group);

    free(nick_name);

    return;
}

void deleting_in_group(int index, char*** group_array, int * total){

    int size = *total;
    char ** new = (char**)malloc((size-1) * sizeof(char *));

    for(int i = 0,j=0;i < size-1; i++,j++){
        if(i == index) j++;
        new[i] = (*group_array)[j];
    }


    free(*group_array);

    *group_array = new;
    *total = size - 1;

    return;
}

