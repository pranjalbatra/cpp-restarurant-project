


#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<iomanip.h>
#include<ctype.h>
#include<dos.h>

//class containing details of the menu......


class REST
{
 int itemno;
 float price;
 char name[60];
public:
 void Enter()
 {
  cout<<"Enter details\n";
  cout<<"Item number?\n";
  cin>>itemno;
  cout<<"Name?\n";
  gets(name);
  cout<<"Price?\n";
  cin>>price;
 }
 void OUT(int i=5,int j=9)
 {
  gotoxy(i,j);
  cout<<itemno;
  gotoxy(i+10,j);
  cout<<name;
  gotoxy(i+19,j);
  cout<<price;
 }
 int Ritemno()
 {
  return(itemno);
 }
 float Rprice()
 {
  return (price);
 }
 void Change()
 {
  cout<<"Enter New Item No.: "; cin>>itemno;
  cout<<"Enter the New Name of the item :";cin>>name;
  cout<<"Enter the New price of the Item:";cin>>price;
  cout<<endl;
 }
};

//class containing details of the order.......

class Order:public REST
{
 int ono;
 float oprice;
 int oquan;
public:
 void In()
 {
  cout<<"Enter number     ";
  cin>>ono;
  cout<<"Enter Quantity   ";
  cin>>oquan;
 }
 void Out()
 {
  textcolor(WHITE);
  cprintf("Item number :  ");
  textcolor(WHITE);
  cout<<ono;
  cout<<endl;
  cprintf("Quantity    :  ");
  textcolor(WHITE);
  cout<<oquan;
  cout<<endl;
 }
 int Rono()
 {
  return ono;
 }
 int Roquan()
 {
  return oquan;
 }
};


//funtion to write on to the file containing the menu.....

void Write()
{
 fstream fil;
 char choice;
 REST r;
 fil.open("REST.dat",ios::binary|ios::out);
 do
 {
  r.Enter();
  fil.write((char*)&r,sizeof(r));
  cout<<"Enter more? (y/n)\n";
  cin>>choice;
 }
 while(tolower(choice)!='n');
 fil.close();
}

//funtion to sort the menu card a/c to item no......

void Sort()
{
 fstream fil1,fil2;
 REST first,second;
 fil1.open("REST.dat",ios::binary|ios::in|ios::out);
 fil1.seekg(0,ios::end);
 int n=fil1.tellg()/sizeof(first);
 for(int i=0;i<n-1;i++)
 for(int j=0;j<n-1-i;j++)
 {
  fil1.seekg(j*sizeof(first));
  fil1.read((char*)&first,sizeof(first));
  fil1.read((char*)&second,sizeof(second));
  if((first.Ritemno())>(second.Ritemno()))
  {
   fil1.seekg(j*sizeof(first));
   fil1.write((char*)&second,sizeof(second));
   fil1.write((char*)&first,sizeof(first));
  }
 }
 fil1.close();
}

//function to display the menu.....

void Display()
{
 fstream fil;
 REST r;
 int j=11,i=5;
 fil.open("REST.dat",ios::binary|ios::in);
 gotoxy(30,3);
 textcolor(RED);
 cprintf("C++ RESTAURANT");
 cout<<endl;
 textcolor(GREEN+BLINK);
 gotoxy(20,5);
 cprintf("Yummy fast food.....On the GO !!!");
 cout<<endl<<endl;
 cout<<setw(40)<<"MENU : \n";
 gotoxy(5,9);
 cout<<"ITEM NO.";
 gotoxy(15,9);
 cout<<"NAME";
 gotoxy(24,9);
 cout<<"PRICE";
 while(fil.read((char*)&r,sizeof(r)))
 {
  r.OUT(i,j);
  j+=2;
 }
 fil.close();
}

//function to search for the required item.......

void Search()
{
 fstream fil;
 REST r;
 int n;
 cout<<"Enter item number to be searched for\n";
 cin>>n;
 fil.open("REST.dat",ios::binary|ios::in);
 int found=0;
 while(fil.read((char*)&r,sizeof(r)))
 {
  if(r.Ritemno()==n && !found)
  {
   r.OUT();
   cout<<endl<<endl;
   gotoxy(10,10);
   found++;
  }
 }
 if(found==0)
  cout<<"Item not Present\n";
}

//function to create the file contanin details of order......

void Bcreate()
{
 char c;
 Order o;
 fstream fil;
 fil.open("Bill.dat",ios::binary|ios::out);
 do
 {
  o.In();
  fil.write((char*)&o,sizeof(o));
  cout<<"Anything More? (y/n)"<<endl;
  cin>>c;
 }
 while(tolower(c)!='n');
 fil.close();
}

//function to calculate the bill..........

void Bcal(int n,int q,float &p)
{
 fstream fil;
 REST r;
 int found=0;
 fil.open("REST.dat",ios::binary|ios::in);
 while(!found && fil.read((char*)&r,sizeof(r)))
 {
  if(n==r.Ritemno())
  {
   found++;
   p+=(r.Rprice()*q);
  }
 }
 fil.close();
 if(found==0)
  cout<<"               Item not present \n";
}

//function to display the bill.........

void Bdisplay()
{
 fstream fil;
 Order o;
 float total=0,G_total=0;
 fil.open("Bill.dat",ios::binary|ios::in);
 while(fil.read((char*)&o,sizeof(o)))
 {
  o.Out();
  Bcal(o.Rono(),o.Roquan(),total);
  G_total+=total;
 }
 fil.close();
 textcolor(CYAN);
 cprintf("You have to pay : Rs. ") ;
 cout<<total<<endl<<endl;
 textcolor(4);
 gotoxy(30,15);
 cprintf("Thank you !!!");
 cout<<endl;
 gotoxy(30,20);
 cprintf("Visit Again.....!");
 cout<<endl;
 cprintf("\n--------------------------------------------------------------------------------");
 textcolor(WHITE);
 cout<<endl;
}

// function to copy the contents of one file to the other.......

void Copyfile(char F[],char T[])
{
 fstream fil1,fil2;
 fil1.open(F,ios::out|ios::binary);
 fil2.open(T,ios::in|ios::binary);
 REST A;
 while(fil2.read((char*)&A,sizeof(A)))
 {
  fil1.write((char*)&A,sizeof(A));
 }
 fil1.close();
 fil2.close();
}

//function to delete an exixting item..........

void Delete()
{
 fstream fil1,fil2;
 fil1.open("REST.dat",ios::in|ios::binary);
 fil2.open("temp.dat",ios::out|ios::binary);
 REST A;
 int del=0,Code;
 cout<<"Enter the item number to be deleted:\n";
 cin>>Code;
 while(fil1.read((char*)&A,sizeof(A)))
 {
  if(A.Ritemno()==Code)
   del++;
  else
   fil2.write((char*)&A,sizeof(A));
 }
 fil1.close();
 fil2.close();
 if(!del)
  cout<<"Record not found\n";
 else
  Copyfile("REST.dat","temp.dat");
}
//function to edit the menu card........

void Edit()
{
 fstream fil;
 fil.open("REST.dat",ios::in|ios::out|ios::binary);
 REST A;
 int tno, found=0;
 cout<<"Enter the Item Number to be edited: ";
 cin>>tno;
 while(!found && fil.read((char*)&A,sizeof(A)))
 {
  if(A.Ritemno()==tno)
  {
   A.Change();
   cout<<endl<<endl;
   gotoxy(10,10);
   found ++;
  }
 }
 if (found)
 {
  int bytenum=fil.tellg();
  fil.seekp(bytenum-sizeof(A));
  fil.write((char*)&A, sizeof(A));
 }
 else
  cout<<"Record not found : ";
 fil.close();
}

//function to add more items.......

void Add()
{
 REST r;
 fstream fil;
 char choice;
 fil.open("REST.dat",ios::binary|ios::app);
 do
 {
  r.Enter();
  fil.write((char*)&r,sizeof(r));
  cout<<"Enter more items (y/n) ?\n";
  cin>>choice;
 }
 while(tolower(choice)!='n');
 fil.close();
}
// function to change the password...........

int changepassword()
{
 clrscr();
 int i=0;
 char C[20],D[20];
 gotoxy(15,5);cout<<"Enter the new password"<<endl;
 char ch;
 gotoxy(15,6);
 do
 {
  ch=getch();
  if(ch!=13 && ch!=8)
  {
   cout<<"*";
   C[i++]=ch;
  }
  else if (ch==8 && i>0)
  {
   cout<<"\b \b";
   i--;
  }
 }
 while(ch!=13);
 C[i]='\0';  cout<<endl;
 gotoxy(15,7);
 cout<<"Confirm new password"<<endl;
 char c;
 int j=0;gotoxy(15,8);
 do
 {
  c=getch();
  if(c!=13 && c!=8)
  {
   cout<<"*";
   D[j++]=c;
  }
  else if (c==8 && j>0)
  {
   cout<<"\b \b";
   j--;
  }
 }while(c!=13);
 D[j]='\0';
 int k;int h=1;
 k=strcmpi(C,D);
 if (k==0)
 {
  cout<<endl;
  gotoxy(15,9);  textcolor(GREEN);
  char p[30]="PASSWORD CHANGED SUCCESFULLY";
  for (int i=0;i<28;i++)
  {
   delay(100);
   cout<<p[i];
  }
  fstream fil;
  fil.open("password.txt", ios::out);
  fil<<C;textcolor(WHITE);
  h--;
  getch();
 }
 else
 {
  cout<<endl<<"Try again";
 }
 clrscr();
 return h;
}
// function to check password........


int password()
{
 clrscr(); int l=0;
 int i=0;
 char A[20],B[20];
 fstream fil;textcolor(RED);
 fil.open("password.txt", ios::in);
 gotoxy(25,10);cout<<"Enter the password: ";
 char ch;
 do
 {
  ch=getch();
  if(ch!=13 && ch!=8)
  {
   textcolor(RED);
   cout<<"*";
   A[i++]=ch;
  }
  else if (ch==8 && i>0)
  {
   cout<<"\b \b";
   i--;
  }
 }while(ch!=13);
 A[i]='\0';
 fil.getline(B,20);
 if (strcmpi(A,B)==0)
 {
  clrscr();gotoxy(32,10);
  char q[20]="ACCESS PROVIDED";
  for (int i=0;i<21;i++)
  {
   delay(70);
   cout<<q[i];
  }
  l+=1;
  char choice;clrscr();
  gotoxy(20,7);cout<<"Do you want to change the password?"<<endl;
  gotoxy(34,10);textcolor(WHITE);cprintf("Yes");cout<<endl;
  gotoxy(35,11);textcolor(RED);cprintf("No");cout<<endl;
  int w;int k=0;int p;
  do
  {
   w=getch();
   if(w==72)
   {
    gotoxy(34,10);textcolor(WHITE);cprintf("Yes");cout<<endl;
    gotoxy(35,11);textcolor(RED);cprintf("No");cout<<endl;
    k*=0;
   }
   if(w==80)
   {
    gotoxy(34,10);textcolor(RED);cprintf("Yes");cout<<endl;
    gotoxy(35,11);textcolor(WHITE);cprintf("No");cout<<endl;
    k+=1;
   }
  }while(w!=13);
  if(k==0)
  {
   do
   {
    p=changepassword();
   } while(p!=0);
  }
 }
 else
 {
  {
   clrscr();
   char p[20]="ACCESS DENIED";
   gotoxy(32,10);
   for (int i=0;i<15;i++)
   {
    delay(100);
    cout<<p[i];
   }
   cout<<endl;
   gotoxy(34,11);
   textcolor(CYAN+BLINK);
   cprintf("TRY AGAIN");
   textcolor(WHITE);
   getch();
  }
 }
 fil.close();
 return (l);
}


void main()
{
 clrscr();
 _setcursortype(_NOCURSOR);
 char reply,pass[40],c;
 int choice;
 textcolor(6);
 gotoxy(20,3);
 cprintf("WELCOME TO THE C++ RESTAURANT !!!\n");
 textcolor(4);
 gotoxy(20,15);
 cprintf("Presented By:");cout<<endl;
 gotoxy(20,17);
 cprintf("PRANJAL BATRA");cout<<endl;
 gotoxy(20,21);
 cprintf("XII-A");cout<<endl;
 textcolor(WHITE);
 getch();
 clrscr();
 int flag=0;
 do
 {
  clrscr();
  flag=password();
  if(flag!=1)
   clrscr();
  getch();
 }while(flag!=1);
 do
 {
  clrscr();
  textcolor(6);
  gotoxy(30,2);
  cprintf("Welcome manager");
  cout<<endl<<endl;
  cout<<"What would you like to do ?\n";
  cout<<"1::Create a new menu";cout<<endl<<endl;
  cout<<"2::Search for an item\n";
  cout<<endl;
  cout<<"3::Delete an item from the menu\n";
  cout<<endl;
  cout<<"4::Edit details for an item\n";
  cout<<endl;
  cout<<"5::Add on to the menu\n";
  cout<<endl;
  cout<<"0::Quit and Display menu\n";
  cout<<endl;
  cout<<endl<<endl<<endl;
  cin>>choice;
  clrscr();
  switch(choice)
  {
   case 1:Write();
	  cout<<"DETAILS ENTERED\n";
	  break;
   case 2:Search();
	  break;
   case 3:Delete();
	  break;
   case 4:Edit();
	  break;
   case 5:Add();
	  break;
   case 0:clrscr();
	  char p[35]="DISPLAYING THE MENU...........";
	  gotoxy(25,11);
	  for (int i=0;i<31;i++)
	  {
	   delay(100);
	   cout<<p[i];
	  };
	  break;
  default:cout<<"Wrong choice\n";
 }
 if(choice!=0)
 {
  cout<<"Anything else? (y/n) \n";
  cin>>c;}
 }
 while (toupper(c)=='Y' && choice!=0);
 clrscr();
 Sort();
 if (choice!=0);
  clrscr();
 char p[35]="DISPLAYING THE MENU...........";
 gotoxy(25,11);
 for (int i=0;i<31;i++)
 {
  delay(100);
  cout<<p[i];
 };
 clrscr();
 Display();
 cout<<endl<<endl;
 cout<<"Place the Order \n";
 cout<<endl;
 Bcreate();
 clrscr();
 cout<<setw(50)<<"C++ RESTAURANT\n";
 cout<<endl<<endl;
 textcolor(WHITE);
 gotoxy(35,4);
 cprintf("Your Bill");
 cout<<endl<<endl;
 Bdisplay();
 getch();
}





