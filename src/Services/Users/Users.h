#ifndef Users_H_INCLUDED
#define Users_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../UTILS/STD_Types.h"
#include "../../UTILS/BitMath.h"
#include "../../UTILS/Maths.h"
#include "../../HAL/LCD/LCD.h"
#include "../../MCAL/EEPROMTrial/EEPROMTrial.h"


/**
 *  
 * some datatypes and parameters have been modified to work properly
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



void             Users_userNodeInit   (Users_userNode *node);
Users_userNode*  Users_newNode        ();


// **************************  REQUIRED  ************************* //


bool             Users_AddEntry       (Users_usersList *list,  u8 username[20],  u8  password[20],    bool isAdmin);
bool             Users_ReadEntry      (Users_usersList *list,  u8 username[],    u8  password[],      bool *isAdmin);
bool             Users_EditEntry      (Users_usersList *list,  u8 oldUser[],     u8 newUser[],  u8 newPass[],      bool isAdmin);
bool             Users_IsUserExist    (Users_usersList *list,  u8 user[]);                                                      // 1 if exists
void             Users_DeleteEntry    (Users_usersList *list,  u8 username[20]);
bool             Users_IsFull         (Users_usersList *list);                                                                  // 1 if full
u8               Users_GetUsedSize    (Users_usersList *list);
void             Users_GetUsersList   (Users_usersList *list,  u8 *count,        u8 userList[][20]);














///         USINGEEPROM:       ///


typedef struct Users_user_EEPROM{
    volatile u8    username[20];
    volatile u8    password[20];
    volatile bool  isAdmin;

}Users_user_EEPROM;

typedef struct Users_userNode_EEPROM{
    volatile        Users_user_EEPROM         data;
    volatile        u16                       next;
}Users_userNode_EEPROM;


typedef struct Users_usersList_EEPROM{
    volatile u8              length;
    volatile u8              maxLength;
    volatile u16             headPtr;

}Users_usersList_EEPROM;                                        //"dataBase" is just the entry for the linked list node which hold the data, "dataBase" also holds and tracks the database state (length, max length that user will set it to 10 btw, aaaannnd the entry for the first node)




// **************************  REQUIRED  ************************* //
void   Users_initList_EEPROM(Users_usersList_EEPROM *list,  u8 maxLength, u8 listAddr);

void             Users_userNodeInit_EEPROM   (Users_userNode_EEPROM *node);
Users_userNode_EEPROM*  Users_newNode_EEPROM        ();


bool   Users_AddEntry_EEPROM     (Users_usersList_EEPROM *list,  u8 username[20],  u8  password[20],    bool isAdmin);
bool   Users_ReadEntry_EEPROM    (Users_usersList_EEPROM *list,  u8 username[],    u8  password[],      bool *isAdmin);
bool   Users_EditEntry_EEPROM    (Users_usersList_EEPROM *list,  u8 oldUser[],     u8 newUser[],  u8 newPass[],      bool isAdmin);
bool   Users_IsUserExist_EEPROM  (Users_usersList_EEPROM *list,  u8 user[]);                                                      // 1 if exists
void   Users_DeleteEntry_EEPROM  (Users_usersList_EEPROM *list,  u8 username[20]);
bool   Users_IsFull_EEPROM       (Users_usersList_EEPROM *list);                                                                  // 1 if full
u8     Users_GetUsedSize_EEPROM  (Users_usersList_EEPROM *list);
void   Users_GetUsersList_EEPROM (Users_usersList_EEPROM *list,  u8 *count,        u8 userList[][20]);

void Users_SaveNodeInEEPROM(Users_userNode_EEPROM node, u16 addr);


#endif // Users_H_INCLUDED
