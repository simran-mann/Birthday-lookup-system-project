//Simran Mann
//301542808
//sma308@sfu.ca

#include "a4_birthdaylib.hpp"
#include "a4_birthdayBST.hpp"


BirthdayBST::BirthdayBST(){
    root=NULL;
    size= 0; 
}

BirthdayBSTreeNode* BirthdayBST::newNode(Birthday* value){
    node* ret=new BirthdayBSTreeNode; 
    ret->left=NULL;
    ret->right =NULL; 
    ret->parent=NULL; 
    ret->value=value;
    return ret;
}

BirthdayBSTreeNode* BirthdayBST:: insertNode_rec(BirthdayBSTreeNode* node, Birthday* value){ 
    if (node==NULL){ 
        size++;
        return newNode(value); 
    }
    //using helper function to determine where the next node should be placed 
    int res= compareBirthdaysByMD(node->value, value);
    if (res==1){
        node->left=insertNode_rec(node->left, value);
    }else if (res==-1 || res==0 ){
        node->right =insertNode_rec(node->right, value);
    }
    return node;
}

void BirthdayBST::insertNode(Birthday* value){
    root= insertNode_rec(root, value);
}

int BirthdayBST:: getSize(){
    return size; 
}

void BirthdayBST:: inOrderPrint_rec(BirthdayBSTreeNode* node, ostream& os){
    /*inorder traversal goes down each left child, then 
    visits the root of each subtree before visiting the right child*/

    if (node==NULL){
        return;
    }else{ 
        inOrderPrint_rec(node->left, os);
        print_Birthday(node->value, os);
        inOrderPrint_rec(node->right, os);
        return;
    }
}

void BirthdayBST:: inOrderPrint(ostream& os){
    inOrderPrint_rec(root,os); 
}

BirthdayBSTreeNode* BirthdayBST:: findNodeByMD_rec(BirthdayBSTreeNode* node,short month, short day){
    if (node==NULL){
        return NULL;
    }else{
        //if there is a match, return the node  
        if(node->value->day==day && node->value->month ==month){         
            return node;
        //if the given month/day is smaller
        }else if (node->value->month>month|| (node->value->month ==month && node->value->day > day)){
            return findNodeByMD_rec(node->left, month, day);//only search to the left

        }else{//if the given month/day is == to or larger 
            return findNodeByMD_rec(node->right, month, day);//check to the right 
        }
    }
}

 Birthday* BirthdayBST::findNodeByMD(short month, short day){
    BirthdayBSTreeNode* res= findNodeByMD_rec(root, month, day);
    if (res==NULL){
        return NULL;
    }else{
        return res->value;
    }
 }

void BirthdayBST:: printAllNodeWithMatchingMD_rec(BirthdayBSTreeNode* node, ostream& os,short month, short day){

        //find a match starting from the current node
        BirthdayBSTreeNode* res=findNodeByMD_rec(node, month, day);
        if (res==NULL){
            return;
        }else{
            printAllNodeWithMatchingMD_rec(res->right, os, month, day); //check for more matches  
            print_Birthday(res->value, os);//print the current match 
        }
}

void BirthdayBST:: printAllNodeWithMatchingMD(short month, short day, ostream& os){
    printAllNodeWithMatchingMD_rec(root, os, month, day);
}

BirthdayBSTreeNode*  BirthdayBST::findNodeByYMDN_rec(BirthdayBSTreeNode* node,short year, short month, short day,string name){
    if (node==NULL){
        return NULL;
    }else{
        //if there is a match, return the node 
        if (node->value->year==year&&node->value->month==month&&node->value->day==day&&node->value->name==name){
            return node;
        //if given month/day is smaller 
        }else if (node->value->month>month || (node->value->month ==month && node->value->day>day)){
            return findNodeByYMDN_rec(node->left, year, month, day, name);//search to the left 
        }else{//given month/day is larger 
            return findNodeByYMDN_rec(node->right, year, month, day, name);//search to the right 
        }
    }
}

Birthday* BirthdayBST:: findNodeByYMDN(short year, short month, short day,string name){
    BirthdayBSTreeNode* res= findNodeByYMDN_rec(root, year, month, day, name);
    if (res==NULL){
        return NULL; 
    }else{
        return res->value;
    } 
}

void BirthdayBST:: deleteTree_rec(BirthdayBSTreeNode* node){
    if (node==NULL){
        return;
    }else{
        deleteTree_rec(node->left);
        
        delete_Birthday(node->value);//delete memory used by bday struct 
        delete node;//delete memory used by node

        deleteTree_rec(node->right);
    }
}

void BirthdayBST:: reset(){//used to reset the tree when a new file is loaded 
    deleteTree_rec(root);
    size =0;
    root=NULL; 
}

BirthdayBST::~BirthdayBST(){
    deleteTree_rec(root);
}

//the functions below are not used in the main program, as mentioned in the discussion forum 

//helper function for removing a node with 2 children 
BirthdayBSTreeNode* BirthdayBST:: minSuccessor(BirthdayBSTreeNode* node){
    BirthdayBSTreeNode* minNode=node; 
    while (minNode!=NULL && minNode->left !=NULL){
        minNode=minNode->left;
    }
    return minNode; 
}


BirthdayBSTreeNode* BirthdayBST::removeNode_rec(BirthdayBSTreeNode* node,Birthday* value){
    if(node==NULL){
        return node;
    }
    if (node->value>value){
        node->left=removeNode_rec(node->left, value); 
    }else if (node->value <value){
        node->right =removeNode_rec(node->right, value);
    }else{
        if (node->left==NULL &&node->right ==NULL){
            free(node); 
            return NULL; 
        }else if (node->right ==NULL){
            BirthdayBSTreeNode* leftchild=node->left;
            free(node);
            return leftchild; 
        }else if (node->left==NULL){
            BirthdayBSTreeNode* rightchild=node->right; 
            free(node);
            return rightchild;  
        }else{//node has 2 children 
            BirthdayBSTreeNode* minRightNode=minSuccessor(node->right);
            node->value=minRightNode->value; 
            node->right =removeNode_rec(node->right, minRightNode->value);
        }   
    }
    return node; 
}

Birthday* BirthdayBST::removeNode(Birthday* value){
    BirthdayBSTreeNode* res = removeNode_rec(root, value);
    if (res!=NULL){
        return res->value;
    }else{
        return NULL;
    }
}


