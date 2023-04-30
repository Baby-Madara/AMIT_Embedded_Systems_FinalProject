#ifndef Users_H_INCLUDED
#define Users_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../UTILS/STD_Types.h"
#include "../../UTILS/BitMath.h"
#include "../../UTILS/Maths.h"
#include "../../HAL/LCD/LCD.h"


/**
 *  
 * "main" is just a test code
 * "volatile" keyword is added so if something wrong happens, I will be clear it is absloutly from the code algorithm
 * some datatypes and parameters have been modified to work properly (ex. student ID shouldnt be of type u8 is the maximum ID value would be 255 then, and it is not an ID - i had to pass pointer to dataBase entry as an argument for some functions...)
 * WARNINGI:       when passing list of "subjects IDs" you should explicitly cast the list (the array of subject IDs)
 * WARNINGII:      working with VSCode so i needed to add "SDB.c" in terminal,         (    or to addt #include "SDB.c" at the end of "main.c" -_-         ) ...
 *                 cd "d:\Activities - Projects\AMIT Embedded\AMIT_proj_AhmedFarahat_VSCode\" ; if ($?) { gcc -std=c99 main.c SDB.c -o main } ; if ($?) { .\main }
 *  
 */



// typedef struct course{
//     volatile u8     grade;
//     volatile u8     ID[20];                    //assume maximum possible id length is 20 characters
// }course;

typedef struct Users_user{
    volatile u8    username[20];
    volatile u8    password[20];
    volatile bool  isAdmin;

}Users_user;

typedef struct Users_userNode{
    volatile        Users_user         data;
    volatile struct Users_userNode    *next;
}Users_userNode;


typedef struct Users_usersList{
    volatile u8              length;
    volatile u8              maxLength;
    volatile Users_userNode *headPtr;

}Users_usersList;                                        //"dataBase" is just the entry for the linked list node which hold the data, "dataBase" also holds and tracks the database state (length, max length that user will set it to 10 btw, aaaannnd the entry for the first node)


void             Users_initList(Users_usersList *base,  u8 maxLength);




// **************************  REQUIRED  ************************* //

void             Users_userNodeInit   (Users_userNode *node);


bool             Users_AddEntry       (Users_usersList *list,  u8 username[20],  u8  password[20],    bool isAdmin);
bool             Users_ReadEntry      (Users_usersList *list,  u8 username[],    u8  password[],      bool *isAdmin);
bool             Users_IsUserExist    (Users_usersList *list,  u8 user[]);                                                      // 1 if exists
void             Users_DeleteEntry    (Users_usersList *list,  u8 username[20]);
bool             Users_IsFull         (Users_usersList *list);                                                                  // 1 if full
u8               Users_GetUsedSize    (Users_usersList *list);
void             Users_GetUsersList   (Users_usersList *list,  u8 *count,        u8 userList[][20]);


Users_userNode*  Users_newNode        ();

#endif // Users_H_INCLUDED
