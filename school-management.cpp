#include<iostream>
#include<conio.h>
using namespace std;
class Node
{
    public:
    int roll_no;
    string name;
    float marks,per;
    Node *next_add;
};
class Linked_list
{
   public:
   Node * head=NULL;
   void Insert()
   {
    int r;
    string n;
    float m;
    cout<<"\n\nEnter Roll No. : ";
    cin>>r;
    cout<<"\n\nEnter Name : ";
    cin>>n;
    cout<<"\n\nEnter Marks : ";
    cin>>m;
    Node * new_node= new Node;
    new_node->roll_no=r;
    new_node->name=n;
    new_node->marks=m;
    new_node->per=m/100*100;
    new_node->next_add=NULL;
    if(head==NULL)
    {
        head=new_node;
    }
    else{
        Node *ptr=head;
        while(ptr->next_add!=NULL)
        {
            ptr=ptr->next_add;
        }
        ptr->next_add=new_node;
    }
    cout<<"\n\n New Node Inserted Successfully..";
   }

   void Search()
   {
    if(head==NULL)
    {
        cout<<"\n\n Linked list is empty";
    }
    else{
        int r,found=0;
        cout<<"\n\n Enter roll_no for search";
        cin>>r;
        Node *ptr=head;
        while(ptr!=NULL)
        {
            if(ptr->roll_no==r)
            {
                found++;
                cout<<"\n\n Roll_no :"<<ptr->roll_no;
                cout<<"\n Name : "<<ptr->name;
                cout<< "\nMarks :"<<ptr->marks;
                cout<<"\nPercentage %:"<<ptr->per;
            }
            ptr=ptr->next_add;
        }
        if(found==0)
        {
            cout<<"\n\n search Roll_no:"<<r<<" Record not found";
        }
    }
   }

   void Update()
   {
    if(head==NULL)
    {
        cout<<"\n\n Linked list is empty";
    }
    else{
        int r,found=0;
        cout<<"\n\n Enter roll_no for updation";
        cin>>r;
        Node *ptr=head;
        while(ptr!=NULL)
        {
            if(ptr->roll_no==r)
            {
                found++;
                cout<<"\n\nEnter new roll No. : ";
                cin>>ptr->roll_no;
                cout<<"\n\nEnter Name : ";
                cin>>ptr->name;
                cout<<"\n\nEnter Marks : ";
                cin>>ptr->marks;
                ptr->per=ptr->marks/100*100;
                cout<<"\n\n Record Updated Successfully..";
        }
        if(found==0)
        {
            cout<<"\n\n No Past record exist for Roll_no:"<<r;
        }
    }
   }
   }

   void Del()
   {
    if(head==NULL)
    {
        cout<<"\n\n Linked list is empty";
    }
    else{
        int r,found=0;
        cout<<"\n\n Enter roll_no for Deletion";
        cin>>r;
        Node *ptr=head;
        Node* prev=head;
        while(ptr!=NULL)
        {  
            if(ptr->roll_no==r)
            {
                if(head==ptr)
                {
                    head=ptr->next_add;
                }
                found++;
                prev->next_add=ptr->next_add;
                delete ptr;
                cout<<"\n\nRoll_No:"<<r<<"Deleted Successfully";
                break;
            }
            prev=ptr;
            ptr=ptr->next_add;
        }
        if(found==0)
        {
            cout<<"\n\n Roll_no:"<<r<<"did not exist";
        }
    }
   }
   
   void show()
   {
    if(head==NULL)
    {
        cout<<"\n\n Linked list is empty";
    }
    else{
        
        Node *ptr=head;
        while(ptr!=NULL)
        {
                cout<<"\n\n Roll_no :"<<ptr->roll_no;
                cout<<"\n Name : "<<ptr->name;
                cout<< "\nMarks :"<<ptr->marks;
                cout<<"\nPercentage %:"<<ptr->per;
            ptr=ptr->next_add;
        }
    }
   }
};
int main()
{
   Linked_list obj;
   p:
   system("cls");
   int choice;
   cout<<"\n\n 1.Register New Student";
   cout<<"\n\n 2. Search By Roll_number";
   cout<<"\n\n 3. Update Record";
   cout<<"\n\n 4. Delete Record";
   cout<<"\n\n 5. Show All Records";
   cout<<"\n\n 6. Exit";
   cout<<"\n\n\n Your Choice:";
   cin>>choice;
   switch(choice)
   {
    case 1:
    system("cls");
    obj.Insert();
    break;
    case 2:
    system("cls");
    obj.Search();
    break;
    case 3:
    system("cls");
    obj.Update();
    break;
    case 4:
    system("cls");
    obj.Del();
    break;
    case 5:
    system("cls");
    obj.show();
    break;
    case 6:
    exit(0);
    default:
    cout<<"Invalid Choice... Please try again";
   }
   getch();
   goto p;
   return 0;
}
