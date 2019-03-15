#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdio.h>
#include<dos.h>
using namespace std;
class hotel
{
    int room_no;
    char name[30];
    char address[50];
    char phone[10];
    
    public:
    void main_menu();    //to dispay the main menu
    void add();        //to book a room
    void display();    //to display the customer record
    void rooms();    //to display alloted rooms
    void edit();    //to edit the customer record
    int check(int);    //to check room status
    void modify(int);    //to modify the record
    void delete_rec(int);    //to delete the record
	void food();
};
void hotel::main_menu()
{
    int choice;
    
    while(choice!=6)
    {

    	cout<<"\n\t\t\t\t*************";
        cout<<"\n\t\t\t\t* MAIN MENU *";
        cout<<"\n\t\t\t\t*************";
        cout<<"\n\n\n\t\t\t1.Book A Room";
        cout<<"\n\t\t\t2.Customer Record";
        cout<<"\n\t\t\t3.Rooms Allotted";
        cout<<"\n\t\t\t4.Edit Record";
        cout<<"\n\t\t\t5.food";
        cout<<"\n\t\t\t6.Exit";
        cout<<"\n\n\t\t\tEnter Your Choice: ";
        cin>>choice;
        
        switch(choice)
        {
            case 1: add();
                    break;
            case 2: display();
                    break;
            case 3: rooms();
                    break;
            case 4: edit();
                    break;
            case 5: food();
            		break;
            case 6: break;
            default:
                    {
                        cout<<"\n\n\t\t\tWrong choice!!!";
                        cout<<"\n\t\t\tPress any key to continue!!";
                        getch();
              	    }
        }
    }
}
void hotel::add()
{
    int r,flag;
    ofstream fout("Record.dat",ios::app);
    system("cls");
    cout<<"**************************welcome to star hotel room booking portal*******************";
    cout<<"\n Enter Customer Detalis";
    cout<<"\n **********************";
    cout<<"\n\n Room no: ";
    cin>>r;
    flag=check(r);
    
    if(flag)
        cout<<"\n Sorry..!!!Room is already booked";
    else
    {
        room_no=r;
        cout<<" Name: ";
        gets(name);
        gets(address);
        cout<<" Phone No: ";
        gets(phone);
        fout.write((char*)this,sizeof(hotel));
        cout<<"\n Room is booked!!!";
    }
    
    cout<<"\n Press any key to continue!!";
    getch();
    fout.close();
}
void hotel::display()
{
    ifstream fin("Record.dat",ios::in);
    int r,flag;
    system("cls");
    cout<<"*****************************welcome to star hotel room display portal********************";
    cout<<"\n Enter room no: ";
    cin>>r;
    
    while(!fin.eof())
    {
        fin.read((char*)this,sizeof(hotel));
        if(room_no==r)
        {
            cout<<"\n Cusromer Details";
            cout<<"\n ****************";
            cout<<"\n\n Room no: "<<room_no;
            cout<<"\n Name: ";
            cout<<address;
            cout<<"\n Phone no: "<<phone;
            flag=1;
            break;
        }
    }
    
    if(flag==0)
    {
    	cout<<"\n Sorry Room no. not found or vacant!!";
	} 
    cout<<"\n\n Press any key to continue!!";
    getch();
    fin.close();
}
void hotel::rooms()
{
    ifstream fin("Record.dat",ios::in);
    system("cls");
	cout<<"**********************welcome to star hotel list of rooms alloted************************";
    cout<<"\n\t\t\tList Of Rooms Allotted";
    cout<<"\n\t\t\t*********************";
    cout<<"\n\n Room No.\tName\t\tPhone No.\n";
    
    while(!fin.eof())
    {
        fin.read((char*)this,sizeof(hotel));
        cout<<"\n\n "<<room_no<<"\t\t"<<address;
        cout<<"\t\t"<<phone;
    }
    
    cout<<"\n\n\n\t\t\tPress any key to continue!!";
    getch();
    fin.close();
}
void hotel::edit()
{
    
    int choice,r;
    
    cout<<"\n EDIT MENU";
    cout<<"\n *********";
    cout<<"\n\n 1.Modify Customer Record";
    cout<<"\n 2.Delete Customer Record";
    
    cout<<"\n Enter your choice: ";
    cin>>choice;
    
    
    cout<<"\n Enter room no: ";
    cin>>r;
    
    switch(choice)
    {
        case 1: modify(r);
                break;
        case 2: delete_rec(r);
                break;
        default: cout<<"\n Wrong Choice!!";
    }
    
    cout<<"\n Press any key to continue!!!";
    getch();
}
 
int hotel::check(int r)
{
    int flag=0;
    ifstream fin("Record.dat",ios::in);
    while(!fin.eof())
    {
        fin.read((char*)this,sizeof(hotel));
        if(room_no==r)
        {
            flag=1;
                break;
        }
    }
    fin.close();
    return(flag);
}
 
void hotel::modify(int r)
{
    long pos,flag=0;
    fstream file("Record.dat",ios::in|ios::out|ios::binary);
    
    while(!file.eof())
    {
        pos=file.tellg();
        file.read((char*)this,sizeof(hotel));
        if(room_no==r)
        {
            cout<<"\n Enter New Details";
            cout<<"\n *****************";
            cout<<"\n Name: ";
            gets(name);
            gets(address);
            cout<<" Phone no: ";
            gets(phone);
            
            file.seekg(pos);
            file.write((char*)this,sizeof(hotel));
            cout<<"\n Record is modified!!";
            flag=1;
            break;
        }
    }
    
    if(flag==0)
        cout<<"\n Sorry Room no. not found or vacant!!";
        
    file.close();
}
 
void hotel::delete_rec(int r)
{
    int flag=0;
    char ch;
    ifstream fin("Record.dat",ios::in);
    ofstream fout("temp.dat",ios::out);
    
    while(!fin.eof())
    {
        fin.read((char*)this,sizeof(hotel));
        if(room_no==r)
        {
            cout<<"\n Name: ";
            cout<<address;
            cout<<"\n Phone No: "<<phone;
            cout<<"\n\n Do you want to delete this record(y/n): ";
            cin>>ch;   
            if(ch=='n')
            fout.write((char*)this,sizeof(hotel));
            
            flag=1;
        }
        else
            fout.write((char*)this,sizeof(hotel));
    }
    
    fin.close();
    fout.close();
    
    if(flag==0)
        cout<<"\n Sorry room no. not found or vacant!!";
    else
    {
        remove("Record.dat");
        rename("temp.dat","Record.dat");
    }
}
void hotel::food()
{
		int noofitems,itemno,s=0;
		int a[100];
		system("cls");
		cout<<"\t\t\t\t\t*********************************welcome to the portal of food billing****************************";
		cout<<"\n\t\t\t\t\tthe items we have are:\n";
		cout<<"\n\t\t\t\t\t1.idly(2)--20\n\t\t\t\t\t2.dosa--50\n\t\t\t\t\t3.poori--30\n\t\t\t\t\t4.chapathi--40\n\t\t\t\t\t5.veg friedrice--70\n\t\t\t\t\t6.veg biriyani--100\n\t\t\t\t\t7.chicken biriyani--150\n";
		cout<<"\n\t\t\t\t\tenter no of items you have took:";
		cin>>noofitems;
		for(int z=1;z<=noofitems;z++)
		{
			cout<<"\n\t\t\t\t\tenter item numbers giving enter to each";
			cin>>itemno;
			switch(itemno)
			{
				case 1:cout<<"\t\t\t\t\t"<<z<<".	idly--20\n";
				break;
				case 2:cout<<"\t\t\t\t\t"<<z<<".	dosa--50\n";
				break;
				case 3:cout<<"\t\t\t\t\t"<<z<<".	poori--30\n";
				break;
				case 4:cout<<"\t\t\t\t\t"<<z<<".	chapathi--40\n";
				break;
				case 5:cout<<"\t\t\t\t\t"<<z<<".	veg friedrice--70\n";
				break;
				case 6:cout<<"\t\t\t\t\t"<<z<<".	veg biriyani--100\n";
				break;
				case 7:cout<<"\t\t\t\t\t"<<z<<".	chicken biriyani--150\n";
				break;
			}
		}
		cout<<"\n\t\t\t\t\tenter the price of items:";
		for(int i=0;i<noofitems;i++)
		{
			cin>>a[i];
		}
		for(int i=0;i<noofitems;i++)
		{
			s=s+a[i];
		}
		cout<<"\n\t\t\t\t\tthe total bill amount is="<<s;
		cout<<"\n Press any key to continue!!";
    	getch();
}
int main()
{
    hotel h;
    cout<<"\n\t\t\t****************************";
    cout<<"\n\t\t\t* WELCOME TO THE STAR HOTEL *";
    cout<<"\n\t\t\t****************************";
    cout<<"\n\n\n\n\n\t\t\t\tPress any key to continue!!";
    getch();
    h.main_menu();
}
