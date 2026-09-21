#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct book
{
    int id;
    char name[50];
    char author[50];
    int available;
    int studentID;
    int issueDay, issueMonth;
    int returnDay, returnMonth;

    struct book *next;
};

struct bst
{
    int id;
    struct bst *left;
    struct bst *right;
};

struct stack
{
    int id;
    struct stack *next;
};

struct book *head=NULL;
struct bst *root=NULL;
struct stack *top=NULL;

struct bst* insertBST(struct bst* root,int id)
{
    if(root==NULL)
    {
        struct bst *newnode=(struct bst*)malloc(sizeof(struct bst));
        newnode->id=id;
        newnode->left=NULL;
        newnode->right=NULL;
        return newnode;
    }
    if(id<root->id)
    {
        root->left=insertBST(root->left,id);
    }
    else
    {
        root->right=insertBST(root->right,id);
    }
  return root;
}

struct bst* searchBST(struct bst* root,int id)
{
    if(root==NULL || root->id==id)
    {
        return root;
    }
    if(id<root->id)
    {
        return searchBST(root->left,id);
    }
  return searchBST(root->right,id);
}

void push(int id)
{
    struct stack *newnode=(struct stack*)malloc(sizeof(struct stack));
    newnode->id=id;
    newnode->next=top;
    top=newnode;
}

void deleteFromStack(int id)
{
    struct stack *temp=top;
    struct stack *prev=NULL;

    while(temp!=NULL)
    {
        if(temp->id==id)
        {
            if(prev==NULL)
            {
                top=temp->next;
            }
            else
            {
                prev->next=temp->next;
            }

            free(temp);
            return;
        }

        prev=temp;
        temp=temp->next;
    }
}

void displayStack()
{
    struct stack *temp=top;

    if(temp==NULL)
    {
        printf("No issued books\n");
        return;
    }

    printf("Recently Issued Books:\n");
    while(temp!=NULL)
    {
        printf("Book ID: %d\n",temp->id);
        temp=temp->next;
    }
}

void addBook()
{
    struct book *newnode=(struct book*)malloc(sizeof(struct book));

    printf("Enter Book ID: ");
    scanf("%d",&newnode->id);

    if(searchBST(root,newnode->id)!=NULL)
    {
        printf("Book ID already exists!\n");
        free(newnode);
        return;
    }

    printf("Enter Book Name: ");
    scanf(" %[^\n]",newnode->name);

    printf("Enter Author Name: ");
    scanf(" %[^\n]",newnode->author);

    newnode->available=1;
    newnode->studentID=0;
    newnode->issueDay=0;
    newnode->issueMonth=0;
    newnode->returnDay=0;
    newnode->returnMonth=0;
    newnode->next=NULL;

    if(head==NULL)
    {
        head=newnode;
    }
    else
    {
        struct book *temp=head;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next = newnode;
    }

    root=insertBST(root,newnode->id);

    printf("Book Added Successfully\n");
}

void displayBooks()
{
    struct book *temp=head;
    if(temp==NULL)
    {
        printf("Library is empty\n");
        return;
    }
    while(temp!=NULL)
    {
        printf("\nID: %d\nName: %s\nAuthor: %s\n",
               temp->id,temp->name,temp->author);

        if(temp->available)
        {
            printf("Status: Available\n");
        }
        else
        {
            printf("Status: Issued\n");
            printf("Student %d has borrowed this book\n",temp->studentID);
            printf("Issue Date: %d/%d\n",temp->issueDay,temp->issueMonth);
            printf("Return Date: %d/%d\n",temp->returnDay,temp->returnMonth);
        }

        temp=temp->next;
    }
}

void searchBook()
{
    int id;
    printf("Enter Book ID to search: ");
    scanf("%d",&id);

    if(searchBST(root,id)==NULL)
    {
        printf("Book Not Found\n");
        return;
    }

    struct book *temp=head;
    while(temp!=NULL)
    {
        if(temp->id==id)
        {
            printf("\nBook Found:\n");
            printf("Name: %s\nAuthor: %s\n",temp->name,temp->author);

            if(temp->available)
            {
                printf("Status: Available\n");
            }
            else
            {
                printf("Status: Issued\n");
            }
           return;
        }
        temp=temp->next;
    }

    printf("Book not found\n");
}

void issueBook()
{
    int id;
    printf("Enter Book ID to issue: ");
    scanf("%d",&id);

    struct book *temp=head;

    while(temp!=NULL)
    {
        if(temp->id==id)
        {
            if(temp->available==0)
            {
                printf("Book already issued\n");
                return;
            }

            temp->available=0;

            printf("Enter Student ID: ");
            scanf("%d",&temp->studentID);

            printf("Enter issue date (day month): ");
            scanf("%d %d",&temp->issueDay,&temp->issueMonth);

            printf("Enter return date (day month): ");
            scanf("%d %d",&temp->returnDay,&temp->returnMonth);

            push(id);

            printf("Book Issued Successfully\n");
            return;
        }

        temp=temp->next;
    }

    printf("Book not found\n");
}

void returnBook()
{
    int id;
    printf("Enter Book ID to return: ");
    scanf("%d",&id);

    struct book *temp=head;

    while(temp!=NULL)
    {
        if(temp->id==id)
        {
            if(temp->available==1)
            {
                printf("Book was not issued\n");
                return;
            }

            temp->available=1;
            temp->studentID=0;
            temp->issueDay=0;
            temp->issueMonth=0;
            temp->returnDay=0;
            temp->returnMonth=0;

            deleteFromStack(id);

            printf("Book Returned Successfully\n");
            return;
        }

        temp=temp->next;
    }

    printf("Book not found\n");
}

void searchByStudentID()
{
    int Sid;
    printf("Enter Student ID: ");
    scanf("%d",&Sid);

    struct book *temp=head;
    int found=0;

    printf("\nBooks borrowed by Student %d:\n",Sid);

    while(temp!=NULL)
    {
        if(temp->available==0 && temp->studentID==Sid)
        {
            found=1;
            printf("ID: %d | Name: %s | Author: %s\n",
                   temp->id,temp->name,temp->author);

            printf("Issue Date: %d/%d\n",temp->issueDay,temp->issueMonth);
            printf("Return Date: %d/%d\n\n",temp->returnDay,temp->returnMonth);
        }
      temp=temp->next;
    }

    if(found==0)
    {
        printf("No books found for this student\n");
    }
}

void showAvailableBooks()
{
    struct book *temp=head;
    int found=0;

    printf("\nAvailable Books:\n");
    while(temp!=NULL)
    {
        if(temp->available==1)
        {
            found=1;
            printf("ID: %d | Name: %s | Author: %s\n",
                   temp->id,temp->name,temp->author);
        }
      temp=temp->next;
    }

    if(found==0)
    {
        printf("No books are currently available\n");
    }
}

void showIssuedBooks()
{
    struct book *temp=head;
    int found = 0;

    printf("\nIssued Books:\n");
    while(temp != NULL)
    {
        if(temp->available==0)
        {
            found=1;
            printf("ID: %d | Name: %s | Author: %s\n",
                   temp->id,temp->name,temp->author);

            printf("Borrowed by Student ID: %d\n",temp->studentID);
            printf("Issue Date: %d/%d\n",temp->issueDay,temp->issueMonth);
            printf("Return Date: %d/%d\n\n",temp->returnDay,temp->returnMonth);
        }
      temp=temp->next;
    }

    if(found==0)
    {
        printf("No books are currently issued\n");
    }
}

int main()
{
    int choice;

    while(1)
    {
        printf("\nLibrary Management System--\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Show Recently Issued Books\n");
        printf("7. Show Only Available Books\n");
        printf("8. Show Only Issued Books\n");
        printf("9. Search Issued Books by Student ID\n");
        printf("10. Exit\n");

        printf("Enter Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: displayStack(); break;
            case 7: showAvailableBooks(); break;
            case 8: showIssuedBooks(); break;
            case 9: searchByStudentID(); break;
            case 10: exit(0);
            default: printf("Invalid choice\n");
        }
    }
  return 0;
}
