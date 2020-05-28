#include <stdio.h>
#include <stdlib.h>

typedef struct dot_ { //узел списка точек
    int x;
    int y;
    struct dot_ *next;
} dot;

typedef struct Node_{    //узел списка списков точек
    dot* first_dot;
    dot* last_dot;
    struct Node_ *next;
} Node;

dot* push_dot(dot* head,int x, int y);
Node* push(Node *Head, dot* first_dot, dot* last_dot);
Node* new_elem(Node *head, int x, int y);
void printList(Node *head);

dot* push_dot(dot* head, int x, int y) {
    dot *tmp = (dot*)malloc(sizeof(dot));
    if(!tmp){
        printf("error\n");
        return NULL;
    }
    tmp->x = x;
    tmp->y = y;
    tmp->next = head;
    return tmp;
}

Node* push(Node *Head, dot* first_dot, dot* last_dot) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if(!tmp){
        printf("error\n");
        return NULL;
    }
    tmp->first_dot = first_dot;
    tmp->last_dot = last_dot;
    tmp->next = Head;
    return tmp;
}

Node* new_elem(Node *head,int x, int y) {
    dot *tmp = NULL;
    tmp=push_dot(tmp, x, y);
    if(!tmp){
        printf("error\n");
        return NULL;
    }
    head=push(head, tmp, tmp);
    if(!head){
        printf("error\n");
        return NULL;
    }
    return head;
}


void printList(Node *head) {
    Node *cur_ex=head;
    dot *cur_in=NULL;
    while(cur_ex!=NULL){
        cur_in=cur_ex->first_dot;
        while(cur_in!=NULL){
            printf("(%d, ", cur_in->x);
            printf("%d) ", cur_in->y);
            cur_in=cur_in->next;
        }
        printf("\n");
        cur_ex=cur_ex->next;
    }
    printf("\n");
}




int main(void){
    Node* head = NULL;
    Node* cur_ex = NULL;
    dot* cur_in = NULL;
    Node* Node_tmp = NULL;
    FILE* input;
    Node *temp=NULL;
    Node* prev_ex = NULL;
    dot* prev_in = NULL;
    int x;
    int y;
    int f=0;
    input = fopen("data.txt","r");
    if (!input){
        printf("Error! Cannot open file !\n");
        return -1;
    }
    else{
        if (fscanf(input, "%d", &x) != 1){
            printf("Error! Cannot read from file!\n");
            fclose(input);
            return -1;
        }
        else{
            rewind(input);
            while (fscanf(input, "%d", &x) == 1){
                f=0;
                if (fscanf(input, "%d", &y) != 1){
                    printf("Not enough data!\n");
                    fclose(input);
                    return -1;
                }
                if (head==NULL){
                    head=new_elem(head, x, y);
                    if(!head){
                        printf("error\n");
                        return -1;
                    }
                }
                else{
                    cur_ex=head;
                    while(cur_ex!=NULL){
                        cur_in=cur_ex->first_dot;
                        while(cur_in!=NULL){
                            if((abs(x-(cur_in->x))<=1) && (abs(y-(cur_in->y))<=1) && !((x==(cur_in->x)) && (y==(cur_in->y)))){
                                if (f==0){
                                    Node_tmp=cur_ex;
                                    cur_ex->first_dot=push_dot(cur_ex->first_dot,  x,  y);
                                    f=1;
                                }
                                else{
                                    Node_tmp->last_dot->next=cur_ex->first_dot;
                                    Node_tmp->last_dot=cur_ex->last_dot;
                                    temp = head;
                                    while (temp->next != cur_ex){
                                        temp = temp->next;
                                    }
                                    temp->next = cur_ex->next;
                                    cur_ex=temp;
                                }
                                break;
                            }
                            cur_in=cur_in->next;
                        }
                        cur_ex=cur_ex->next;
                    }
                    if (f==0){
                        head=new_elem(head, x,y);
                    }
                }
                printList(head);
            }
            fclose(input);
             while(head!=NULL){
                prev_ex=head;
                cur_in=head->first_dot;
                prev_in=cur_in;
                while(cur_in!=NULL){
                    cur_in=cur_in->next;
                    free(prev_in);
                    prev_in=cur_in;
                }
                head=head->next;
                free(prev_ex);
            }
            return 0;
        }
    }
}

















