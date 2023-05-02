#include "Users.h"

static volatile u16 Users_freeIndex_EEPROM = 0;

void Users_userNodeInit(Users_userNode *node){
    node ->next = NULL;

    node ->data.isAdmin = FALSE;
    strcpy( node ->data.username   , "");                
    strcpy( node ->data.password   , "");             //means not set yet
    
}


Users_userNode *Users_newNode(){
    Users_userNode *node = (Users_userNode*)malloc(sizeof(Users_userNode));
    Users_userNodeInit(node);
    return node;

}


void Users_initList(Users_usersList *list, u8 maxLength){
    list -> length       = 0;
    list -> maxLength    = maxLength;

    list -> headPtr      = NULL;
}










// ********************** //


// // 1 if full:
bool     Users_IsFull         (Users_usersList *list){
    if             (list -> length >= list -> maxLength)        {return 1;}
    else if        (list -> length <  list -> maxLength)        {return 0;}
    
}


u8       Users_GetUsedSize    (Users_usersList *list){
    return         (list -> length);
}


// 1 if entry is added successfully:
bool     Users_AddEntry       (Users_usersList *list, u8 username[20],    u8 password[20],    bool isAdmin){
    if        ( list -> length == 0 ){
        list -> headPtr = Users_newNode();
        
        strcpy(list->headPtr->data.username, username);
        strcpy(list->headPtr->data.password, password);
        list->headPtr->data.isAdmin = isAdmin;

        (list->length) ++;

        return 1;
    }
    else if ( list -> length < list -> maxLength)
    {
        Users_userNode* newNodePtr = list -> headPtr;                                                             // just as initial value
        while(        newNodePtr->next != NULL        )        {        newNodePtr = newNodePtr->next;    }       // so "newNodePtr" now equals NULL
        newNodePtr ->next = Users_newNode();
        newNodePtr = newNodePtr ->next;

        strcpy(newNodePtr ->data.username , username );
        strcpy(newNodePtr ->data.password , password );
        newNodePtr ->data.isAdmin = isAdmin;

        (list -> length) ++;

        return 1;
    }
    else if ( list -> length >= list -> maxLength)
    {
        LCD_WriteString("Error! ddatabase already reached the maximum limit (%d)\n");
        LCD_WriteInt(list -> maxLength);
        LCD_WriteString(" ");
        return 0;
    }

}


void     Users_DeleteEntry    (Users_usersList *list, u8 username[20])
{
    Users_userNode *nodeToDelete     = list->headPtr,          // it is just needed initialization and the pointer will be changing till it reaches the targetted node
                   *prevNode         = NULL;                    // logically it should be  `*prevNode = list` but it might run the code incorrectly as prevNode and list are different dataTypes, so we will use "delete1stNodeFlag": if the node to be deleted is the first node, it will run a specific line instead

    bool delete1stNodeFlag= TRUE;

    while(    (nodeToDelete -> data.username) != username    ){
        prevNode          = nodeToDelete;
        nodeToDelete      = nodeToDelete->next;
        
        delete1stNodeFlag = FALSE;
    }
    if    (delete1stNodeFlag){
        list->headPtr = nodeToDelete->next;
    }
    else{
        prevNode->next = nodeToDelete->next;
    }
    
    free(nodeToDelete);
    list->length--;


}


// 1 if entry exists:
bool     Users_ReadEntry      (Users_usersList *list, u8 username[],    u8 password[],    bool *isAdmin){
    Users_userNode *nodeToFind = list->headPtr;
    while( nodeToFind != NULL){
        if(!strcmp(username , nodeToFind->data.username)){
            strcpy(password, nodeToFind->data.password);
            *isAdmin = nodeToFind->data.isAdmin;
            
            return 1;                                            // return 1 if entry exists
        }
        nodeToFind = nodeToFind->next;
    }



    return 0;
}


void     Users_GetUsersList   (Users_usersList *list,     u8 *count, u8  userList[][20]){
    *count = (list -> length);

    Users_userNode *currentNode = list->headPtr;
    u8 i =0;
    strcpy(userList[0], "") ;
    while(currentNode != NULL){
        strcpy(userList[i], currentNode->data.username);

        currentNode = currentNode->next;
        i++;
    }

}


// 1 if exists:
bool     Users_IsUserExist    (Users_usersList *list,     u8 user[]){
    Users_userNode *currentNode = list->headPtr;
    
    while(currentNode != NULL){
        if (!strcmp(user, currentNode->data.username))            {            return 1;            }
        currentNode = currentNode->next;
    }

    return 0;
}




bool             Users_EditEntry      (Users_usersList *list,  u8 oldUser[],  u8 newUser[],  u8  newPass[],      bool isAdmin)
{
    if (!Users_IsUserExist(list, oldUser))
    {return 0;}
    else
    {
        Users_userNode *currentNode = list->headPtr;
    
        while(currentNode != NULL){
            if (!strcmp(oldUser, currentNode->data.username))
            {
                strcpy(currentNode->data.username, newUser);
                strcpy(currentNode->data.password, newPass);
                currentNode->data.isAdmin = isAdmin;
            }
            currentNode = currentNode->next;
        }

    }
    return 1;
}


/////////////////////////////// USING EEPROM://////////////////////////////








void   Users_initList_EEPROM(Users_usersList_EEPROM *list,  u8 maxLength, u8 listAddr)
{
    //u8 len     u8 maxLen     u16 headPtr
    EEPROM_writeChar(list->length, listAddr);
    EEPROM_writeChar(list->maxLength, listAddr+1);
    EEPROM_writeChar(list->headPtr, listAddr+1);
    list->maxLength;
    
    
    
}

void Users_SaveNodeInEEPROM(Users_userNode_EEPROM node, u16 addr)
{
    Users_userNode_EEPROM* nodePtr= &node;

    for(int i=0; i< sizeof(Users_userNode_EEPROM); i++)
    {
        EEPROM_writeChar(  (*(u8*)(nodePtr+i))     ,     addr+i);
    }
}

void             Users_userNodeInit_EEPROM   (Users_userNode_EEPROM *node)
{

}

Users_userNode_EEPROM*  Users_newNode_EEPROM        ()
{

}



// **************************  REQUIRED  ************************* //


bool   Users_AddEntry_EEPROM     (Users_usersList_EEPROM *list,  u8 username[20],  u8  password[20],    bool isAdmin)
{

}

bool   Users_ReadEntry_EEPROM    (Users_usersList_EEPROM *list,  u8 username[],    u8  password[],      bool *isAdmin)
{

}

bool   Users_EditEntry_EEPROM    (Users_usersList_EEPROM *list,  u8 oldUser[],     u8 newUser[],  u8 newPass[],      bool isAdmin)
{

}

// 1 if exists
bool   Users_IsUserExist_EEPROM  (Users_usersList_EEPROM *list,  u8 user[])
{

}

void   Users_DeleteEntry_EEPROM  (Users_usersList_EEPROM *list,  u8 username[20])
{

}

bool   Users_IsFull_EEPROM       (Users_usersList_EEPROM *list)
{

}
                                                                  // 1 if full
u8     Users_GetUsedSize_EEPROM  (Users_usersList_EEPROM *list)
{

}

void   Users_GetUsersList_EEPROM (Users_usersList_EEPROM *list,  u8 *count,        u8 userList[][20])
{

}




/*

void Users_userNodeInit(Users_userNode *node){
    node ->next = NULL;

    node ->data.isAdmin = FALSE;
    strcpy( node ->data.username   , "");                
    strcpy( node ->data.password   , "");             //means not set yet
    
}


Users_userNode *Users_newNode(){
    // Users_userNode *node = (Users_userNode*)malloc(sizeof(Users_userNode));
    // Users_userNodeInit(node);
    // return node;

    Users_userNode *node = (Users_userNode*)malloc(sizeof(Users_userNode));
    Users_userNodeInit(node);
    return node;

}


void Users_initList(Users_usersList *list, u8 maxLength){
    list -> length       = 0;
    list -> maxLength    = maxLength;

    list -> headPtr      = NULL;
}










// ********************** //


// // 1 if full:
bool     Users_IsFull         (Users_usersList *list){
    if             (list -> length >= list -> maxLength)        {return 1;}
    else if        (list -> length <  list -> maxLength)        {return 0;}
    
}


u8       Users_GetUsedSize    (Users_usersList *list){
    return         (list -> length);
}


// 1 if entry is added successfully:
bool     Users_AddEntry       (Users_usersList *list, u8 username[20],    u8 password[20],    bool isAdmin){
    if        ( list -> length == 0 ){
        list -> headPtr = Users_newNode();
        
        strcpy(list->headPtr->data.username, username);
        strcpy(list->headPtr->data.password, password);
        list->headPtr->data.isAdmin = isAdmin;

        (list->length) ++;

        return 1;
    }
    else if ( list -> length < list -> maxLength)
    {
        Users_userNode* newNodePtr = list -> headPtr;                                                             // just as initial value
        while(        newNodePtr->next != NULL        )        {        newNodePtr = newNodePtr->next;    }       // so "newNodePtr" now equals NULL
        newNodePtr ->next = Users_newNode();
        newNodePtr = newNodePtr ->next;

        strcpy(newNodePtr ->data.username , username );
        strcpy(newNodePtr ->data.password , password );
        newNodePtr ->data.isAdmin = isAdmin;

        (list -> length) ++;

        return 1;
    }
    else if ( list -> length >= list -> maxLength)
    {
        LCD_WriteString("Error! ddatabase already reached the maximum limit (%d)\n");
        LCD_WriteInt(list -> maxLength);
        LCD_WriteString(" ");
        return 0;
    }

}


void     Users_DeleteEntry    (Users_usersList *list, u8 username[20])
{
    Users_userNode *nodeToDelete     = list->headPtr,          // it is just needed initialization and the pointer will be changing till it reaches the targetted node
                   *prevNode         = NULL;                    // logically it should be  `*prevNode = list` but it might run the code incorrectly as prevNode and list are different dataTypes, so we will use "delete1stNodeFlag": if the node to be deleted is the first node, it will run a specific line instead

    bool delete1stNodeFlag= TRUE;

    while(    (nodeToDelete -> data.username) != username    ){
        prevNode          = nodeToDelete;
        nodeToDelete      = nodeToDelete->next;
        
        delete1stNodeFlag = FALSE;
    }
    if    (delete1stNodeFlag){
        list->headPtr = nodeToDelete->next;
    }
    else{
        prevNode->next = nodeToDelete->next;
    }
    
    free(nodeToDelete);
    list->length--;


}


// 1 if entry exists:
bool     Users_ReadEntry      (Users_usersList *list, u8 username[],    u8 password[],    bool *isAdmin){
    Users_userNode *nodeToFind = list->headPtr;
    while( nodeToFind != NULL){
        if(!strcmp(username , nodeToFind->data.username)){
            strcpy(password, nodeToFind->data.password);
            *isAdmin = nodeToFind->data.isAdmin;
            
            return 1;                                            // return 1 if entry exists
        }
        nodeToFind = nodeToFind->next;
    }



    return 0;
}


void     Users_GetUsersList   (Users_usersList *list,     u8 *count, u8  userList[][20]){
    *count = (list -> length);

    Users_userNode *currentNode = list->headPtr;
    u8 i =0;
    strcpy(userList[0], "") ;
    while(currentNode != NULL){
        strcpy(userList[i], currentNode->data.username);

        currentNode = currentNode->next;
        i++;
    }

}


// 1 if exists:
bool     Users_IsUserExist    (Users_usersList *list,     u8 user[]){
    Users_userNode *currentNode = list->headPtr;
    
    while(currentNode != NULL){
        if (!strcmp(user, currentNode->data.username))            {            return 1;            }
        currentNode = currentNode->next;
    }

    return 0;
}




bool             Users_EditEntry      (Users_usersList *list,  u8 oldUser[],  u8 newUser[],  u8  newPass[],      bool isAdmin)
{
    if (!Users_IsUserExist(list, oldUser))
    {return 0;}
    else
    {
        Users_userNode *currentNode = list->headPtr;
    
        while(currentNode != NULL){
            if (!strcmp(oldUser, currentNode->data.username))
            {
                strcpy(currentNode->data.username, newUser);
                strcpy(currentNode->data.password, newPass);
                currentNode->data.isAdmin = isAdmin;
            }
            currentNode = currentNode->next;
        }

    }
    return 1;
}
*/