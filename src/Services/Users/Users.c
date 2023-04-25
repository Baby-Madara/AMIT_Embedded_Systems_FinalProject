#include "Users.h"



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
bool     Users_ReadEntry      (Users_usersList *list, u8 username[],    u8 password[],    u8 *isAdmin){
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


void     Users_GetUsersList   (Users_usersList *list,     u8 *count, u8*  userList[20]){
    *count = (list -> length);

    Users_userNode *currentNode = list->headPtr;
    u8 i =0;
    userList[0] = 0 ;
    while(currentNode != NULL){
        userList[i] = currentNode->data.username ;

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




