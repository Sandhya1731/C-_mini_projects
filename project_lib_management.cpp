#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

class Date
{
    private:
    int dd;
    int mm;
    int yy;
    void rectifyDate()
    {
        if(dd>30)
        {
            dd-=30;
            mm++;
        }
        if(mm>12)
        {
            mm-=12;
            yy++;
        }
    }
    public:
    Date()
    {
        dd=1;
        mm=1;
        yy=2022;
    }
    void setDate()
    {
        cout<<"Enter Date: ";
        cin>>dd;
        cout<<"Enter Month: ";
        cin>>mm;
        cout<<"Enter Year: ";
        cin>>yy;
    }
    /* overload* to find return date by passing issued date*/
    void setDate(Date temp)
    {
        dd=temp.dd+15;
        mm=temp.mm;
        yy=temp.yy;
        rectifyDate();
    }
    void showDate()
    {
        cout<<dd<<"/"<<mm<<"/"<<yy;
    }
};

class Menu
{
    public:
    void mainMenu();
    void studentMenu();
    void bookMenu();
    void issueBook();
    void returnBook();
};

void Menu::mainMenu()
{
    cout<<"#################### Main Menu ###################\n\n";
    cout<<"1. Student Menu\n2.Book Menu\n3. Issue Book\n4. Return Menu\n5. Exit"<<endl;
}
void Menu::studentMenu()
{
    cout<<"#################### Student Menu ##################\n\n";
    cout<<"1. New Entry\n2. Modify Entry\n3. Search Entry\n4. Delete Entry\n";
    cout<<"5. View All Student Details\n6. Go to Main Menu\n";
}
void Menu::bookMenu()
{
     cout<<"#################### Book Menu ##################\n\n";
    cout<<"1. New Entry\n2. Modify Entry\n3. Search Entry\n4. Delete Entry\n";
    cout<<"5. View All Books Details\n6. Go to Main Menu\n";
}

class BookData
{
    public:
    char title[30];
    char author[30];
    char publisher[30];
    int status;// can store max copies and available copies and issued Roll no in vector
    float price;
    int issuedRollNo;
    Date issuedDate;// rollno,date data type to store in map which rollno issued when
    Date returnDate;
    BookData()
    {
        status=0;
        issuedRollNo=-9999;
    }

};

class StudentData
{
  public:
  int rollNo;
  char name[30];
  char address[50];
  char branch[5];
  int status;// how many books already having max limit can be issued 
  char bookTitle[30];
  StudentData()
  {
    status=0;
  }

};

class Book
{  
    public:
    void inputDetails();
    void modifyDetails();
    void searchDetails();
    void searchDetails(char []);
    void deleteDetails();
    void viewAllBookDetails();
};

void Book::inputDetails()
{
    fstream fin;
    fin.open("bookDatabase.dat", ios::app | ios::binary |ios::out);
    if(!fin)
    {
        cerr<<"Unable to open the file"<<endl;// show errors on console
        return;
    }
    BookData book;// object created
    cout<<"Enter book title";
    cin>>book.title;
    cout<<"Enter author name";
    cin>>book.author;
    cout<<"enter publisher name";
    cin>>book.publisher;
    cout<<"enter book price";
    cin>>book.price;

    fin.write((char*)&book,sizeof(BookData));
    fin.close();
}

void Book::modifyDetails()
{
    fstream fin;
    fin.open("bookDatabase.dat",ios:: in|ios:: binary| ios::out|ios::ate);
    if(!fin)
    {
        cerr<<"Unable to open the file"<<endl;// show errors on console
        return;
    }
    fin.seekg(0,ios::beg);// point to 0 values after begining
    BookData book;
    char title[30];

    cout<<"enter book title of book you want to modify: ";
    cin>>title;
    while(fin.read((char*)&book,sizeof(BookData)))
    {
       if(strcmp(book.title,title)==0)
       {
        int pos_back=(-1)*sizeof(BookData);
        fin.seekp(pos_back,ios::cur);
        
        cout<<"Enter new book title:";
        cin>>book.title;
        cout<<"Enter new author's name:";
        cin>>book.author;
        cout<<"Enter new publisher:";
        cin>>book.publisher;
        cout<<"Enter new price:";
        cin>>book.price;

        cout<<"Record updated";
        cin.get();
        fin.close();
        return;
       }
    }
    cout<<"Book not found";
    fin.close();
    cin.get();
    return;
}

void Book::searchDetails(char tiitle[])
{
   fstream fout;
        fout.open("bookDatabase.dat",ios::in|ios::binary);
        if(!fout)
        {
        cout<<"Unable to open the file";
        cin.get();
        return;
        }
        BookData book;
    while(fout.read((char*)&book,sizeof(BookData)))
    {
     if(strcmp(book.title,tiitle)==0)
     {
        cout<<"Book Title: "<<book.title<<endl;
        cout<<"Book Author: "<<book.author<<endl;
        cout<<"Book Publisher: "<<book.publisher<<endl;
        cout<<"Book Price: "<<book.price<<endl;
        if(book.status==1)
        {
            cout<<"Issued Date: ";
            book.issuedDate.showDate();
            cout<<endl<<"Return Date: ";
            book.returnDate.showDate();
            cout<<endl;
        }
        else{
            cout<<"Issued Status :None"<<endl;
        }
        cin.get();
        fout.close();
        return;
     }
    }
    fout.close();
    cout<<"Book not found"<<endl;
    cin.get();
    return;
}

void Book::searchDetails()
{
    fstream fin;
    fin.open("bookDatabase.dat",ios::in|ios::binary);
    if(!fin)
    {
        cout<<"Unable to open the file";
        cin.get();
        return;
    }

    BookData book;
    char title[30];
    cin>>title;
    while(fin.read((char*)&book,sizeof(BookData)))
    {
     if(strcmp(book.title,title)==0)
     {
        cout<<"Book Title: "<<book.title<<endl;
        cout<<"Book Author: "<<book.author<<endl;
        cout<<"Book Publisher: "<<book.publisher<<endl;
        cout<<"Book Price: "<<book.price<<endl;
        if(book.status==1)
        {
            cout<<"Issued RollNo: "<<book.issuedRollNo<<endl;
            cout<<"Issued Date: ";
            book.issuedDate.showDate();
            cout<<endl<<"Return Date: ";
            book.returnDate.showDate();
            cout<<endl;
        }
        else{
            cout<<"Issued Status :None"<<endl;
        }
        cin.get();
        fin.close();
        return;
     }
    }
    fin.close();
    cout<<"Book not found"<<endl;
    cin.get();
    return;
}

void Book::deleteDetails()
{
    fstream fin,temp;
    fin.open("bookDatabase.dat",ios::binary|ios::in);
    temp.open("temp.dat",ios::binary|ios::out);

    char title[30];
    cin>>title;
    BookData book;
    int flag=0;
    cout<<"Enter book title to remove:";
    cin>>book.title;
    while(fin.read((char*)&book,sizeof(BookData)))
    {
     if(strcmp(book.title,title)==0)
     {  flag++;
        continue;
     }
     temp.write((char*)&book,sizeof(BookData));
    }
    fin.close();
    temp.close();
    remove("bookDatabase.dat");
    rename("temp.dat","bookDatabase.dat");

    if(flag==1)
    cout<<"Record Delted"<<endl;
    else
    cout<<"Record not found"<<endl;
    cin.get();
    return;
}

void Book::viewAllBookDetails()
{
    fstream fin;
    fin.open("bookDatabase.dat",ios::in|ios::binary);
    if(!fin)
    {
        cout<<"Unable to open the file";
        cin.get();
        return;
    }

    BookData book;
    int choice=1;
    while(fin.read((char*)&book,sizeof(BookData))&&choice)
    {
     
        system("clear");
        cout<<"Book Title: "<<book.title<<endl;
        cout<<"Book Author: "<<book.author<<endl;
        cout<<"Book Publisher: "<<book.publisher<<endl;
        cout<<"Book Price: "<<book.price<<endl;
        if(book.status==1)
        {
            cout<<"Issued RollNo: "<<book.issuedRollNo<<endl;
            cout<<"Issued Date: ";
            book.issuedDate.showDate();
            cout<<endl<<"Return Date: ";
            book.returnDate.showDate();
            cout<<endl;
        }
        else{
            cout<<"Issued Status :None"<<endl;
        }
        
        cout<<"Press 1 to view next book else press 0:";
        cin>>choice;
     }
    fin.close();
    cout<<"Book not found"<<endl;
    cin.get();
    return;
}

class Student
{
    public:
    void inputDetails();
    void modifyDetails();
    void searchDetails();
    void deleteDetails();
    void viewAllStudents();
};
void Student::inputDetails()
{
   fstream fin;
   fin.open("studentDatabase.dat",ios::out| ios::app| ios::binary);

   if(!fin)
   {
    cout<<"Unable to open file"<<endl;
    return;
   } 
    StudentData student;
    cout<<"Enter student's roll no. :";
    cin>>student.rollNo;
    cout<<"Enter student's name :";
    cin>>student.name;
    cout<<"Enter student's address :";
    cin>>student.address;
    cout<<"Enter student's branch :";
    cin>>student.branch;

    cout<<"Record added to database!";
    fin.write((char*)&student,sizeof(StudentData));
    fin.close();
}

void Student::modifyDetails()
{
   fstream fin;
   fin.open("studentDatabase.dat",ios::in| ios::out|ios::ate |ios::binary);

   if(!fin)
   {
    cout<<"Unable to open file"<<endl;
    return;
   } 

    fin.seekg(0,ios::beg);
    int target;
    cout<<"Enter student's roll no. to modify:";
    cin>>target;
    StudentData student;
    while(fin.read((char*)&student,sizeof(student)))// once come and check 
    {
    if(target==student.rollNo)
    {
    int pos=(-1)*sizeof(StudentData);
    fin.seekp(pos,ios::cur);

    cout<<"Enter student's roll no. :";
    cin>>student.rollNo;
    cout<<"Enter student's name :";
    cin>>student.name;
    cout<<"Enter student's address :";
    cin>>student.address;
    cout<<"Enter student's branch :";
    cin>>student.branch;

    fin.write((char*)&student,sizeof(StudentData));
    fin.close();
    cout<<"Record Updated"<<endl;
    return;
    }
    }
    cout<<"Roll no. not found!"<<endl;
    fin.close();
    return;
}

void Student::searchDetails()
  { fstream fin;
   fin.open("studentDatabase.dat",ios::in|ios::binary);

   if(!fin)
   {
    cerr<<"Unable to open file"<<endl;
    return;
   } 
    fin.seekg(0,ios::beg);
    int target;
    cout<<"Enter student's roll no. to search:";
    cin>>target;
    
    StudentData student;
    while(fin.read((char*)&student,sizeof(StudentData)))// once come and check 
    {
    if(target==student.rollNo)
    {
    cout<<"Record Found!"<<endl;
    cout<<"Student's roll no. :"<<student.rollNo<<endl;
    cout<<"Student's name :"<<student.name<<endl;
    cout<<"Student's branch :"<<student.branch<<endl;
    cout<<"Student's address :"<<student.address<<endl;
    if(student.status==1)
    {
        cout<<"Issued Book name is: "<<student.bookTitle<<endl;
        cout<<"Book Details:"<<endl;
        Book b;
        b.searchDetails(student.bookTitle);
    }
    else{
        cout<<"No book is issued for this roll no."<<endl;
    }
    cin.get();
    fin.close();
    return;
    }
    }
    cout<<"Roll no. not found!"<<endl;
    fin.close();
    return;
}

void Student::viewAllStudents()
{
    system("clear");
    fstream fin;
    fin.open("studentDatabase.dat",ios::in|ios::binary);

   if(!fin)
   {
    cout<<"Unable to open file"<<endl;
    return;
   } 

    fin.seekg(0,ios::beg);
    StudentData student;
    int choice=1;
    while(choice && fin.read((char*)&student,sizeof(StudentData)))// once come and check 
    {
    system("clear");
    cout<<"Student's roll no. :"<<student.rollNo<<endl;
    cout<<"Student's name :"<<student.name<<endl;
    cout<<"Student's branch :"<<student.branch<<endl;
    cout<<"Student's address :"<<student.address<<endl;
    if(student.status==1)
    {
        cout<<"Issued Book name is: "<<student.bookTitle<<endl;
    }
    else{
        cout<<"No book is issued for this roll no."<<endl;
    }
    cin.get();
    cout<<"Enter 1 if want to see details of next student else 0";
    cin>>choice;
    }
    fin.close();
    return;
}

void Student::deleteDetails()
{
    fstream fin;
    fin.open("studentDatabase.dat",ios::in|ios::binary);
    fstream temp;
    temp.open("temp.dat",ios::out|ios::binary);
    StudentData student;
    int target;
    int flag=0;

    cout<<"Enter roll no. to be delted:";
    cin>> target;
    while(fin.read((char*)&student,sizeof(StudentData)))// check here something else written
    {
     if(student.rollNo==target)
     {
        if(student.status==1)
        {
            cout<<"Can't delete roll no as issued book is not return yet !";
            fin.close();
            temp.close();
            remove("temp.dat");
            return;
        }
        flag++;
        continue;
     }
     temp.write((char*)&student,sizeof(StudentData));
    }
    fin.close();
    temp.close();
    remove("studentDatabase.dat");
    rename("temp.dat","studentDatabase.dat");

    if(flag==1)
    {
     cout<<"Record Deleted"<<endl;
    }
    else{
        cout<<"Roll no. not found"<<endl;
    }
    cin.get();
    return;
}
 
void Menu::issueBook()
{
    fstream sd,bd;// student database,book database
    sd.open("studentDatabase.dat",ios::in|ios::out|ios::ate|ios::binary);
    bd.open("bookDatabase.dat",ios::in|ios::out|ios::ate|ios::binary);
    bd.seekg(0,ios::beg);
    sd.seekg(0,ios::beg);

    int rollNo,flagS=0,flagB=0,pos;
    char title[30];
    StudentData student;
    BookData book;
    cout<<"Enter Student's roll no to issue book: ";
    cin>>rollNo;
    while(sd.read((char*)&student,sizeof(StudentData)))
    {
     if(student.rollNo==rollNo)
     {
        pos=(-1)*sizeof(StudentData);
        sd.seekp(pos,ios::cur);
        flagS++;
        break;
     }
    }
    if(flagS!=1)
    {
        cout<<"Record not found!"<<endl;
        cin.get();
        sd.close();
        bd.close();
        return;
    }
    cout<<"Enter book title to be issued: ";
    cin>>title;

    while(bd.read((char*)&student,sizeof(BookData)))
    {
        if(strcmp(book.title,title)==0)
        {
            pos=(-1)*sizeof(BookData);
            bd.seekp(pos,ios::cur);//check where seeekg or seekp is required in file
            flagB++;
            break;
        }
    }
    
    if(flagB!=1)
    {
        cout<<"Record not found!"<<endl;
        cin.get();
        sd.close();
        bd.close();
        return;
    }
    if(student.status!=1 && book.status!=1)
    {
        strcpy(student.bookTitle,title);
        student.status=1;
        book.status=1;
        book.issuedRollNo=student.rollNo;
        book.issuedDate.setDate();
        book.returnDate.setDate(book.issuedDate);
        sd.write((char*)&student,sizeof(StudentData));
        bd.write((char*)&book,sizeof(BookData));
        sd.close();
        bd.close();
    }
    else{
        if(student.status==1)
        {
            cout<<"Student's account is already full"<<endl;
            cin.get();
            sd.close();
            bd.close();
            return;
        }
        else{
             cout<<"Book currently unavailable (issued)"<<endl;
            cin.get();
            sd.close();
            bd.close();
            return;
        }
    }
}

void Menu::returnBook()
{
      fstream sd,bd;// student database,book database
    sd.open("studentDatabase.dat",ios::in|ios::out|ios::ate|ios::binary);
    bd.open("bookDatabase.dat",ios::in|ios::out|ios::ate|ios::binary);
    bd.seekg(0,ios::beg);
    sd.seekg(0,ios::beg);

    int rollNo,flagS=0,flagB=0,pos;
    char title[30];
    StudentData student;
    BookData book;
    cout<<"Enter Student's roll no to return book: ";
    cin>>rollNo;
    while(sd.read((char*)&student,sizeof(StudentData)))
    {
     if(student.rollNo==rollNo)
     {
        pos=(-1)*sizeof(StudentData);
        sd.seekp(pos,ios::cur);
        flagS++;
        break;
     }
    }
    if(flagS!=1)
    {
        cout<<"Record not found!"<<endl;
        cin.get();
        sd.close();
        bd.close();
        return;
    }
    strcpy(title,student.bookTitle);

    while(bd.read((char*)&student,sizeof(BookData)))
    {
        if(strcmp(book.title,title)==0)
        {
            pos=(-1)*sizeof(BookData);
            bd.seekp(pos,ios::cur);//check where seeekg or seekp is required in file
            flagB++;
            break;
        }
    }
    
    if(flagB!=1)
    {
        cout<<"Record not found!"<<endl;
        cin.get();
        sd.close();
        bd.close();
        return;
    }
    if(student.status==1 && book.status==1)
    {
        strcpy(student.bookTitle," ");
        student.status=0;
        book.status=0;
        book.issuedRollNo=-9999;
        sd.write((char*)&student,sizeof(StudentData));
        bd.write((char*)&book,sizeof(BookData));
        sd.close();
        bd.close();
    }
    else{
        if(student.status==0)
        {
            cout<<"No book is issued to this roll no."<<endl;
            cin.get();
            sd.close();
            bd.close();
            return;
        }
        else{
             cout<<"Book is available(issued to none)"<<endl;
            cin.get();
            sd.close();
            bd.close();
            return;
        }
    }
}


int main()
{
 Menu menu;
 int quit=0;
 int choice;

 while(!quit)
 {
    system("clear");
    menu.mainMenu();
    cout<<"Please enter your choice:"<<endl;
    cin>>choice;
    switch(choice)
    {
        case 1:{
            system("clear");
            menu.studentMenu();
            cout<<"Please Enter your choice: "<<endl;
            cin>>choice;
            Student s1;
            switch(choice)
            {
                case 1:
                s1.inputDetails();
                break;

                case 2:
                s1.modifyDetails();
                break;

                case 3:
                s1.searchDetails();
                break;
                
                case 4:
                s1.deleteDetails();
                break;

                case 5:
                s1.viewAllStudents();
                break;
               
                default:
                cout<<"Invalid Choice!"<<endl;
                break;
            }
            break;
        }

        case 2:{
            system("clear");
            menu.bookMenu();
            cout<<"Please enter your choice: "<<endl;
            cin>>choice;
            Book b1;
            switch(choice)
            {
                 case 1:
                b1.inputDetails();
                break;

                case 2:
                b1.modifyDetails();
                break;

                case 3:
                b1.searchDetails();
                break;
                
                case 4:
                b1.deleteDetails();
                break;

                case 5:
                b1.viewAllBookDetails();
                break;

                default:
                cout<<"Invalid Choice!"<<endl;
                break;
            }
            break;
        }

        case 3:menu.issueBook();
        break;

        case 4:menu.returnBook();
        break;

        case 5:quit++;
        break;

        default:cerr<<"Please select valid choice!"<<endl;
        cin>>choice;
    }
 }
}

