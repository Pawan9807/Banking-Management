#include<bits/stdc++.h>
#include<iostream>
#include<string.h>
#include<fstream>
#include <iostream>
#include <chrono>
#include<thread>
#include<windows.h>
#include <time.h>
#include<conio.h>
using namespace std;
class verify_customer
{
    public:
    int Cus_pin;
    int loan_pin;
   
};
class customer:public verify_customer
{
    public:
    char cname[25];
    int cid;
    double cbalance;
    int ctype;
 
    void CreateNewUser();
    void DisplayAcc()const;
    void C_AccDeposite(double x);
    void C_AccWithdraw(double x);
    void C_Edetail() const;    //return entire all customer accoubt
    int dyid() const;     //return account number
    int dtype() const;    //return account type
    int dybal()const;  //return balance
    int dypin()const;  //return pin
    void C_AccUpdate();
};
void customer:: CreateNewUser()
    {
        int random;
        int tbal=0;
        system("cls");
        cout<<endl<<"\t\t\t\tEnter customer name:";
        cin.ignore();
        cin.getline(cname,25);
        cout<<"\n\t\t\t\tPlease wait while your account number is being generated...";
        srand(time(0));
      
        cid=rand()%1000+1;
        cout<<"\n\t\t\t\tAcc No:"<<cid;
        cout<<"\n\t\t\t\tEnter you pin:";
        cin>>Cus_pin;
        cout<<endl<<"\t\t\t\tEnter customer account type(1 for savings 2 for current):";
        cin>>ctype;
        cout<<endl<<"\t\t\t\tEnter initial balance:";
        cin>>cbalance;
        if(ctype==2&&cbalance<=0)
        {
            cout<<"\t\t\t\tMinimum balnce in current account should be greater than 0, enter new initial balance:";
            cin>>tbal;
            cbalance=tbal;
        }
        
        cout<<endl<<"Account number "<<cid<<" is sucessfully created\n";
    }
    void customer::C_AccUpdate()
  {
	cout<<"\n\tBank_Account No. : "<<cid;
	cout<<"\n\tUpdation Bank_Account Holder Name : ";
	cin.ignore();
	cin.getline(cname,25);
	cout<<"\n\tUpdation Type of Bank_Account : ";
	cin>>ctype;
	ctype=toupper(ctype);
	cout<<"\n\tUpdation Balance Total-Money : ";
	cin>>cbalance;
  }
int customer:: dybal()const
    {
        return cbalance;
    }
int customer:: dypin()const
{
    return Cus_pin;
}

int customer::dyid()const
    {
        return cid;
    }
int customer::dtype()const
    {
        return ctype;
    }
void customer::C_Edetail() const
{
    cout<<cid<<setw(7)<<" "<<cname<<setw(10)<<"\t"<<"  "<<ctype<<setw(10)<<"\t"<<cbalance<<endl;
}
void customer:: DisplayAcc()const
{
    cout<<"\n\t\t\t\tAccount number:"<<cid;
    cout<<"\n\t\t\t\tName on account:"<<cname;
    cout<<"\n\t\t\t\tAccount type:"<<ctype;
    cout<<"\n\t\t\t\tAccount balance:"<<cbalance<<endl;
}
void customer::C_AccWithdraw(double amt)
{
    cbalance-=amt;
}
void customer::C_AccDeposite(double amt)
{
    cbalance+=amt;
}
class operations: public customer
{
    public:
    void ShowBalance(int n,int p)
    {
        operations ac;
        bool flag=false;
        ifstream inFile;
        inFile.open("database.dat",ios::binary);
        if(!inFile)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        cout<<"\n\t\t\t\tBALANCE DETAILS\n";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(customer)))
        {
            if(ac.dyid()==n)
            {   
                if(ac.dypin()==p)
                {
                ac.DisplayAcc();
                flag=true;
                }
                else
                {
                    cout<<"\n\t\t\t\t\tWrong password";
                }
            }
        }
        inFile.close();
        if(flag==false){
            cout<<"\n\n\t\t\tAccount number does not exist";
        }
    }
    void Pushdetails()
    {
        operations ac;
        ofstream outFile;
        outFile.open("database.dat",ios::binary|ios::app);
        ac.CreateNewUser();
        outFile.write(reinterpret_cast<char *> (&ac), sizeof(customer));
        outFile.close();
    }
    void Withdraw(int n,int p)
    {
        double amt;
        bool found=false;
        operations ac;
        fstream File;
        File.open("database.dat", ios::binary|ios::in|ios::out);
        if(!File)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        while(!File.eof() && found==false)
        {
            File.read(reinterpret_cast<char *> (&ac), sizeof(customer));
            if(ac.dyid()==n)
            {
                if(ac.dypin()==p)
                {
                ac.DisplayAcc();
                //cout<<"\n\n\t\t\tTO WITHDRAW AMOUNT";
                cout<<"\n\n\t\t\tEnter The amount to be withdraw: ";
                cin>>amt;
                int bal=ac.dybal()-amt;
                if(bal<0)
                    cout<<"Sorry !! Insufficience balance..";
                else
                    //ac.Withdraw(amt);
                    ac.C_AccWithdraw(amt); 
                int pos=(-1)*static_cast<int>(sizeof(customer));
                File.seekp(pos,ios::cur);
                File.write(reinterpret_cast<char *> (&ac), sizeof(customer));
                cout<<"\n\n\t\t\tSuccess... Record Updated Successfully";
                found=true;
                }
                else{
                    cout<<"\n\t\t\t\tWrong password";
                }
           }
         }
        File.close();
        if(found==false)
        cout<<"\n\n\t\t\tOops! We Couldn't find your record";
    }
    void  Deposite(int n,int p)
    {
        double amt;
        bool found=false;
        operations ac;
        fstream File;
        File.open("database.dat", ios::binary|ios::in|ios::out);
        if(!File)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        while(!File.eof() && found==false)
        {
            File.read(reinterpret_cast<char *> (&ac), sizeof(customer));
            if(ac.dyid()==n)
            {
                if(ac.dypin()==p)
                {
                ac.DisplayAcc();
                //cout<<"\n\n\t\t\tTO DEPOSITSS AMOUNT";
                cout<<"\n\n\t\t\tEnter The amount to be deposited: ";
                cin>>amt;
                ac.C_AccDeposite(amt);
                int pos=(-1)*static_cast<int>(sizeof(customer));
                File.seekp(pos,ios::cur);
                File.write(reinterpret_cast<char *> (&ac), sizeof(customer));
                cout<<"\n\n\t\t\tSuccess... Record Updated Successfully";
                found=true;
                }
                else
                {
                    cout<<"\n\t\t\t\tWrong password";
                }
            }
        }
        File.close();
        if(found==false)
        cout<<"\n\n\t\t\tOops! We Couldn't find your record";
    }
 void Acc_Update(int up) 
   {
	bool found=false;
	operations ac;
	fstream File;
    File.open("database.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(customer));
		if(ac.dyid()==up)
		{
			ac.DisplayAcc();
			cout<<"\n\n\tPlease Enter The New Details of Bank_Account"<<endl;
			ac.C_AccUpdate();
			int pos=(-1)*static_cast<int>(sizeof(customer));
			File.seekp(pos,ios::cur); //fncallat1353
		    File.write(reinterpret_cast<char *> (&ac), sizeof(customer));
		    cout<<"\n\n\tCongrats your Record Updated";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n\t Pardon,details doest not exist";
   }
    

    void ncloseacc(int n,int p)
    {
        operations ac;
        ifstream inFile;
        ofstream outFile;
        bool found=false;
        inFile.open("database.dat",ios::binary);
        if(!inFile)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        outFile.open("Temp.dat",ios::binary);
        inFile.seekg(0,ios::beg);
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(customer)))
        {
            if(ac.dyid()!=n && ac.dypin()!=p)
            {
                outFile.write(reinterpret_cast<char *> (&ac), sizeof(customer));
                found=true;
            }
        }
        inFile.close();
        outFile.close();
        if(found==false)
        cout<<"\n\n\t\t\tOops! We Couldn't find your record";
        else
        {
            remove("database.dat");
            rename("Temp.dat","database.dat");
            cout<<"\n\n\t\tRecord Deleted .."<<endl;
        }
    }
    void ndisplayrecords()
    {
        system("cls");
        int t1;
        cout<<"\t\t\t\tEnter admin password:";
        cin>>t1;
        if(t1==123)
        {
        operations ac;
        ifstream inFile;
        inFile.open("database.dat",ios::binary);
        if(!inFile)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        cout<<"\n\n\t\tACCOUNT HOLDERS DETAILS\n\n";
        cout<<"--------------------------------------------------------\n";
        cout<<"A/c no.      NAME                Type            Balance\n";
        cout<<"--------------------------------------------------------\n";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(customer)))
        {
            ac.C_Edetail();
        }
        inFile.close();
        }
        else
        {
            cout<<"\n\t\t\t\tWrong admin password";
        }
    }
  
  
};
class loancustomer:public verify_customer
{
    public:
    char lname[25];
    int lid;
    double lamount;
    int lyears;
    float lrate;
    void lCreateNewUser();
    void lDisplayAcc()const;
    void ldodeposite(double x);
    void lpriAll()const;
    int ldyid()const;
    int ldybal()const;
    int ldypin()const;
    void lemi()const;
};
int loancustomer:: ldypin()const
{
    return loan_pin;
}
void loancustomer::lCreateNewUser()
{
    int random;
    system("cls");
    cout<<endl<<"\t\t\t\tEnter customer name:";
    cin.ignore();
    cin.getline(lname,25);
    cout<<"\n\t\t\t\tPlease wait while your account number is being generated...";
    srand(time(0));
    for(int i=0;i<6;i++)
    {
        cout<<".";
        Sleep(1000);
    }
    lid=rand()%1000+1;
    cout<<"\n\t\t\t\tAcc No:"<<lid<<endl;
    cout<<endl<<"\t\t\t\tEnter account pin:";
    cin>>loan_pin;
    cout<<endl<<"\t\t\t\tEnter initial remaining balance:";
    cin>>lamount;
    //cout<<endl<<"\t\t\t\tEnter customer pin:";
    //cin>>cpin;
    cout<<endl<<"\t\t\t\tEnter loan duration in years:";
    cin>>lyears;
    cout<<endl<<"\t\t\t\tEnter loan interest rate:";
    cin>>lrate;
    cout<<endl<<"Account number "<<lid<<" is sucessfully created\n";
}
int loancustomer::ldybal()const
{
    return lamount;
}
int loancustomer::ldyid()const
{
    return lid;
}
void loancustomer::lpriAll()const
{
    cout<<lid<<setw(7)<<" "<<lname<<setw(10)<<"\t"<<"  "<<lyears<<setw(10)<<"\t"<<lamount<<endl;
}
void loancustomer::lDisplayAcc()const
{
    cout<<"\n\t\t\t\tAccount number:"<<lid;
    cout<<"\n\t\t\t\tName on account:"<<lname;
    cout<<"\n\t\t\t\tAccount loan duration:"<<lyears;
    cout<<"\n\t\t\t\tAccount loan balance amount:"<<lamount<<endl;
}
void loancustomer::lemi()const
{
    double emi=0;
    double r;
    r=lrate/(12*100);
    cout<<"\n\t\t\t\t"<<r<<" "<<pow(1+r,lyears);
    emi=lamount * r * pow(1+r,lyears*12)/(pow(1+r,lyears*12)-1);
    cout<<"\n\t\t\t\tMonthly EMI will be RS "<<emi<<endl;
}
void loancustomer::ldodeposite(double amt)
{
    lamount-=amt;
}
class loanoperations :public loancustomer
{
    public:
   void lShowBalance(int n,int p)
   {
        loanoperations ac;
        bool flag=false;
        ifstream inFile;
        inFile.open("loanDB.dat",ios::binary);
        if(!inFile)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        cout<<"\n\t\t\tLOAN BALANCE DETAILS\n";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(loancustomer)))
        {
            if(ac.ldyid()==n)
            {
                if(ac.ldypin()==p)
                {
                ac.lDisplayAcc();
                flag=true;
                }
                else
                {
                    cout<<"\n\t\t\t\tWrong password";
                }
            }
        }
        inFile.close();
        if(flag==false){
            cout<<"\n\n\t\t\tLoan Account of such number does not exist";
        }
   }
   void lPushdetails()
   {
        loanoperations ac;
        ofstream outFile;
        outFile.open("loanDB.dat",ios::binary|ios::app);
        ac.lCreateNewUser();
        outFile.write(reinterpret_cast<char *> (&ac), sizeof(loancustomer));
        outFile.close();
   }
   void lDeposite(int n,int p)
   {
        double amt;
        bool found=false;
        loanoperations ac;
        fstream File;
        File.open("loanDB.dat", ios::binary|ios::in|ios::out);
        if(!File)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        while(!File.eof() && found==false)
        {
            File.read(reinterpret_cast<char *> (&ac), sizeof(loancustomer));
            if(ac.ldyid()==n)
            {
                if(ac.ldypin()==p)
                {
                ac.lDisplayAcc();
                //cout<<"\n\n\t\t\tTO DEPOSITSS AMOUNT";
                cout<<"\n\n\t\t\tEnter The amount to be repay: ";
                cin>>amt;
                ac.ldodeposite(amt);
                int pos=(-1)*static_cast<int>(sizeof(loancustomer));
                File.seekp(pos,ios::cur);
                File.write(reinterpret_cast<char *> (&ac), sizeof(loancustomer));
                cout<<"\n\n\t\t\tSuccess... Record Updated Successfully";
                found=true;
                }
                else
                {
                    cout<<"\n\t\t\t\tWrong password";
                }
            }
        }
        File.close();
        if(found==false)
        cout<<"\n\n\t\t\tOops! We Couldn't find your record";
   }
    void lcalcemi(int n,int p)
    {
        loanoperations ac;
        bool flag=false;
        ifstream inFile;
        inFile.open("loanDB.dat",ios::binary);
        if(!inFile)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        cout<<"\n\t\t\tLOAN BALANCE DETAILS\n";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(loancustomer)))
        {
            if(ac.ldyid()==n)
            {
                if(ac.ldypin()==p)
                {
                ac.lemi();
                flag=true;
                }
                else
                {
                    cout<<"\n\t\t\t\tWrong password";
                }
            }
        }
        inFile.close();
        if(flag==false){
            cout<<"\n\n\t\t\tLoan Account of such number does not exist";
        }
    }

   void ldisplayrecords()
   {
        int t1;
        cout<<"\t\t\t\tEnter admin password:";
        cin>>t1;
        if(t1==123)
        {
        system("cls");
        loanoperations ac;
        ifstream inFile;
        inFile.open("loanDB.dat",ios::binary);
        if(!inFile)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        cout<<"\n\n\t\tACCOUNT HOLDERS DETAILS\n\n";
        cout<<"----------------------------------------------------------------\n";
        cout<<"A/c no.      NAME                Years             Remaining Sum\n";
        cout<<"----------------------------------------------------------------\n";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(loancustomer)))
        {
            ac.lpriAll();
        }
        inFile.close();
        }
        else
        {
            cout<<"\n\t\t\t\tWrong admin password";
        }
   }
   


};
class menu :public operations,loanoperations
{
    public:
    void Sav_Cur()
    {
        system("Color 0A");
        int id;
        int ip;
        int choice_menu;
        cout<<endl;
        cout<<endl;
        cout<<"\t\t\t\tchoose any one\n";
        cout<<"\t\t\t\t1--If you are a new user\n";
        cout<<"\t\t\t\t2--To check remaining balance\n";
        cout<<"\t\t\t\t3--To withdraw money in your account\n";
        cout<<"\t\t\t\t4--To deposite money from your account\n";
        cout<<"\t\t\t\t5--To display acc info\n";
        cout<<"\t\t\t\t6--To close your account\n";
        cout<<"\t\t\t\t7--To update account\n";
        cout<<"\t\t\t\t8--To exit\n";
        
        cin>>choice_menu;
        if(choice_menu==1)
        {
            Pushdetails();
             Sav_Cur();
        }
        else if(choice_menu==2)
        {
            cout<<"\n\n\n\t\t\t\tEnter your account number:";
            cin>>id;
            cout<<"\n\t\t\t\tEnter your account pin:";
            cin>>ip;
            ShowBalance(id,ip);
             Sav_Cur();
        }
        else if(choice_menu==3)
        {
            cout<<"\n\n\n\t\t\t\tEnter your account number:";
            cin>>id;
            cout<<"\n\t\t\t\tEnter your account pin:";
            cin>>ip;
            Withdraw(id,ip);
            Sav_Cur();
        }
        else if(choice_menu==4)
        {
            cout<<"\n\n\n\t\t\t\tEnter your account number:";
            cin>>id;
            cout<<"\n\t\t\t\tEnter your account pin:";
            cin>>ip;
             Deposite(id,ip);
       Sav_Cur();
        }
        else if(choice_menu==5)
        {
            cout<<"\n\n\n\t\t\t\tEnter your account number:";
            cin>>id;
            ndisplayrecords();
             Sav_Cur();
        }
        else if(choice_menu==6)
        {
            cout<<"\n\n\n\t\t\t\tEnter your account number:";
            cin>>id;
            cout<<"\n\t\t\t\tEnter your account pin:";
            cin>>ip;
            ncloseacc(id,ip);
             Sav_Cur();
        else if(choice_menu==7)
        {
          cout<<"\n\n\n\t\t\t\tEnter your account number:";
          cin>>id;
          Acc_Update(id);
          cout<<endl;
        Sav_Cur()

        }
        else if(choice_menu==7)
        {
            cout<<"\t\t*****************Bye*******************";
            system("Color 07");
        }
        else
        {
            cout<<"\t\t\t\tInvalid choice returning to main menu........\n";
            menu();
        }
        
    }
    void loan_acc()
    {
        int id;
        int ip;
        int choice_loan;
        system("Color E4");
        cout<<"\t\t\t\tPress\n";
        cout<<"\t\t\t\t1--If you want to open a new loan account\n";
        cout<<"\t\t\t\t2--To display amount of loan remaining to repay\n";
        cout<<"\t\t\t\t3--To repay loan\n";
        cout<<"\t\t\t\t4--To calculate emi on loan\n";
        cout<<"\t\t\t\t5--To display all records\n";
        cout<<"\t\t\t\t6--to exit\n";
        cin>>choice_loan;
        if(choice_loan==1)
        {
            lPushdetails();
            loan_acc();
        }
        else if(choice_loan==2)
        {
            cout<<"\n\n\n\t\t\t\tEnter your account number:";
            cin>>id;
            cout<<"\n\t\t\t\tEnter your account pin:";
            cin>>ip;
            lShowBalance(id,ip);
       loan_acc();
        }
        else if(choice_loan==3)
        {
            cout<<"\n\n\n\t\t\t\tEnter your account number:";
            cin>>id;
            cout<<"\n\t\t\t\tEnter your account pin:";
            cin>>ip;
            lDeposite(id,ip);
          loan_acc();
        }
        else if(choice_loan==4)
        {
            cout<<"\n\n\n\t\t\t\tEnter your account number:";
            cin>>id;
            cout<<"\n\t\t\t\tEnter your account pin:";
            cin>>ip;
            lcalcemi(id,ip);
        loan_acc();
        }
        else if(lchoice_profm==5)
        {
            // cout<<"\n\n\n\t\t\t\tEnter your account number\n";
            // cin>>id;
            ldisplayrecords();
        loan_acc();
        }
        else if(choice_loan==6)
        {
            system("Color 07");
            cout<<"\t\t*****************Bye*******************";
        }
        else
        {
            cout<<"\t\t\t\tInvalid choice returning to main menu........\n";
            menu();
        }
    }
    menu()
     {
        system("CLS");
        cout<<endl<<endl<<endl;
        cout<<"\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        cout<<"\t\t\t       @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@          \n";
        cout<<"\t\t\t          |||||| LANDIS + GYR BANK  ||||||                      \n";
        cout<<"\t\t\t       @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@          \n";
        cout<<"\t\t\t*******Address:-Candor Techspace, sector-62 ,Noida**************\n";
        cout<<"\t\t\t************************             ***************************\n";
        cout<<"\t\t\t****************************      ******************************\n";
        cout<<"\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        cout<<"\n";
        int choice_prof;
        cout<<"Press Enter- key to continue to main menu\n";
        getchar();
        
        cout<<"\t\t\t\tPress\n";
        cout<<"\t\t\t\t1 For savings/current account login\n";
        cout<<"\t\t\t\t2 For loan account login\n";
        cout<<"\t\t\t\t3: Exit                \n";
        cin>>choice_prof;
        if(choice_prof==1)
        {
            Sav_Cur();
        }
        else if(choice_prof==2)
        {
          loan_acc();
        }
        
        else
        {
            cout<<"\t\t\t\tInvalid choice returning to main menu........\n";
            menu();
        }
     }
};

// --------------------- Branch Manager-----------------------!!

class Branch :public operations
{

  public:
    int B_id;    
    string B_Name;
  

 
  
  void CreateBranchManager();
  void B_checkAcc() const;
 // void B_closeacc();
  //int rB_id() const;

};

//int Branch::rB_id() const
//{
 //   return B_id;
//}


void Branch:: CreateBranchManager()
{
    system("cls");
    cout<<endl<<"Enter Branch Name ->";
    cin.ignore();
    cin>>B_Name;
    cout<<"Branch ID ->";
    cin>>B_id;
    
}

// Branch check  
void Branch::B_checkAcc()const
    {   
       string t="Noida";
        system("cls");
        cout<<"\t\t\tEnter Branch Manager id->"<<B_id;
        cout<<endl<<"\t\t\tEnter Branch Name->"<<B_Name;

        if(B_Name==t && B_id==9807)
        {
        operations ac;
        ifstream inFile;
        inFile.open("database.dat",ios::binary);
        if(!inFile)
        {
            cout<<"File cann't open,Try Again\n";
            return;
        }
        cout<<"\n\n\t\tACCOUNT HOLDERS DETAILS\n\n";
        cout<<"--------------------------------------------------------\n";
        cout<<"A/c no.      NAME                Type            Balance\n";
        cout<<"--------------------------------------------------------\n";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(customer)))
        {
            ac.C_Edetail();
            getch();
        }
        inFile.close();
        }
        else
        {
            cout<<"\n\t\t\t\t Pardon, try again to access";
        }
    };
/*
    void Branch:: B_closeacc()
    {   
        if(B_Name=="Noida" && B_id==9807){
        operations ac;
        ifstream inFile;
        ofstream outFile;
        bool found=false;
        inFile.open("database.dat",ios::binary);
        if(!inFile)
        {
            
            cout<<"File could not be open !! Press any Key...";
            return;
         
        }
        outFile.open("Temp.dat",ios::binary);
        inFile.seekg(0,ios::beg);
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(customer)))
        {
           
            
            
                outFile.write(reinterpret_cast<char *> (&ac), sizeof(customer));
                found=true;
            
       }
        inFile.close();
        outFile.close();
        if(found==false)
        cout<<"\n\n\t\t\tOops! We Couldn't find your record";
        else
        {
            remove("database.dat");
            rename("Temp.dat","database.dat");
            cout<<"\n\n\t\tRecord Deleted .."<<endl;
            getch();
        }
    }
}*/
 void Bank()
  {
     Branch b;
      b.CreateBranchManager();
     //int An,Ap;
    cout<<"\t\t\tchoose any one\n";
    cout<<"\t\t\t 1: check All Customer Account List\n";
    //cout<<"\t\t\t 2: Delete Account \n";
    cout<<"\t\t\t 3: Exit           \n";
 
    int ch;
    cin>>ch;
    if(ch==1)
    {  
        b.B_checkAcc();
        Bank();
    }
    else if(ch==2)
    {  /*
        cout<<"\t\t\t Enter Account number:";
        cin>>An;
        cout<<"\t\t\t Enter Accout pin :";
        cin>>Ap;
        */
        //b.CreateBranchManager();
       // b.B_closeacc();
        Bank();

    }
    else
    {
      cout<<"\t\t\t Pardon, try again ";
      Bank();
       
    }
}
/*
class B_operation: public customer 
{
    public:
    void B_checkAcc()const
    {   
      string t="Noida";
        system("cls");
        cout<<"\t\t\tEnter Branch Manager id->"<<B_id;
        cout<<endl<<"\t\t\tEnter Branch Name->"<<B_Name;

        if(B_Name==t && B_id==9807)
        {
        operations ac;
        ifstream inFile;
        inFile.open("database.dat",ios::binary);
        if(!inFile)
        {
            cout<<"File cann't open,Try Again\n";
            return;
        }
        cout<<"\n\n\t\tACCOUNT HOLDERS DETAILS\n\n";
        cout<<"--------------------------------------------------------\n";
        cout<<"A/c no.      NAME                Type            Balance\n";
        cout<<"--------------------------------------------------------\n";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(customer)))
        {
            ac.priAll();
            getch();
        }
        inFile.close();
    
        //else
       // {
         //   cout<<"\n\t\t\t\t Pardon, try again to access";
        //}
    
   void  B_closeacc(int n,int p)
    {   
       // if(B_Name=="Noida" && B_id==9807){
        operations ac;
        ifstream inFile;
        ofstream outFile;
        bool found=false;
        inFile.open("database.dat",ios::binary);
        if(!inFile)
        {
            
            cout<<"File could not be open !! Press any Key...";
            return;
         
        }
        outFile.open("Temp.dat",ios::binary);
        inFile.seekg(0,ios::beg);
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(customer)))
        {
           
            
            if(dyid()!=n && dypin()!=p)
            {
                outFile.write(reinterpret_cast<char *> (&ac), sizeof(customer));
                found=true;
            }
       }
        inFile.close();
        outFile.close();
        if(found==false)
        cout<<"\n\n\t\t\tOops! We Couldn't find your record";
        else
        {
            remove("database.dat");
            rename("Temp.dat","database.dat");
            cout<<"\n\n\t\tRecord Deleted .."<<endl;
            getch();
        }
}
}; 
  
class Bank: public B_operation
 {
   Branch b;
  public:
   
   
   void B()
   {
     int An,Ap;
    cout<<"\t\t\tchoose any one\n";
    cout<<"\t\t\t 1: check All Customer Account List\n";
    cout<<"\t\t\t 2: Delete Account \n";
    cout<<"\t\t\t 3: Exit           \n";
 
    int ch;
    cin>>ch;
    if(ch==1)
    {
        B_checkAcc();
    }
    else if(ch==2)
    {  
        cout<<"\t\t\t Enter Account number:";
        cin>>An;
        cout<<"\t\t\t Enter Accout pin :";
        cin>>Ap;
        B_closeacc(An,Ap);
    }
    else
    {
      cout<<"\t\t\t Pardon, try again ";

    }
};
*/  
/*


  void B_checkAcc()
    {   
        system("cls");
        cout<<"\t\t\tEnter Branch Manager id->"<<B_id;
        cout<<endl<<"\t\t\tEnter Branch Name->"<<B_Name;

        if(B_Name='Noida' && B_id=9807)
        {
operations ac;
        ifstream inFile;
        inFile.open("account.dat",ios::binary);
        if(!inFile)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        cout<<"\n\n\t\tACCOUNT HOLDERS DETAILS\n\n";
        cout<<"--------------------------------------------------------\n";
        cout<<"A/c no.      NAME                Type            Balance\n";
        cout<<"--------------------------------------------------------\n";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(customer)))
        {
            ac.priAll();
        }
        inFile.close();
        }
        else
        {
            cout<<"\n\t\t\t\tWrong admin password";
        }
}
*/

//        USER AND REGISTER
void admin_login();
void login();
void registration();
void forgot();
void Bank();   
int main()
{
    int c;
    system("color  B5");
     cout<<"************************************************************************************\n";
     cout<<"*******               Press 1:  LOGIN                                        *******\n";
     cout<<"******                Press 2:  ADMIN LOGIN                                   ******\n";
     cout<<"*****                 Press 3:  REGISTER                                       *****\n";                  
     cout<<"****                  Press 4:  FORGET PASSWORD                                 ****\n";
     cout<<"***                   Press 5:  EXIT                                             ***\n";
     cout<<"**                    please enter your choice:                                   **\n"; 

     cin>>c;
     cout<<endl;

     switch(c)
     {
        case 1:
             login();
             break;

       case 2:
             admin_login(); 
       case 3:
             registration();
             break;
        case 4:
             forgot();
             break;
        case 5:
             
            cout<<"\t\t\t thank u \n\n";
            //exit();
             break;         
        default:
        system("cls");
        cout<<"\t\t\t  please select from the option given above \n";
        main();
     }
}

void login()
{
    int count;
    string userId,password,id,pass;
    system("cls");
    cout<<"\t\t\t please enter the username and password: "<<endl;
    cout<<"\t\t\t Username ";
    cin>>userId;
    cout<<"\t\t\t Password";
    cin>>password;

    ifstream input("records.txt");

    while(input>>id>>pass)
    {
         if(id==userId && pass==password)
         { 
            count=1;
            system("cls");

         }
    }

    input.close();
   
    if(count==1)
    {
        cout<<userId<<"\n your login is successful \n ";
        menu();

    }
    else{
        cout<<"\n LOGIN ERROR \n please check your username\n";
        
    }

}

void admin_login()
{
    int count;
    string id;
     int password;
    system("cls");
    cout<<"\t\t\t please enter the username and password: "<<endl;
    cout<<"\t\t\t Username ";
    cin>>id;
    cout<<"\t\t\t Password ";
    cin>>password;

       if(id=="Admin" && password==12345)
         { 
          
            system("cls");
            
            cout<<id<<"\n your login is successful \n ";
             Bank();


         }
         else 
          {  cout<<"\t\t Invalid Id or Password \n";
             
          }    
}

void registration()
{

string ruserId,rpassword,rid,rpass;
system("cls");
cout<<"\t\t\t Enter the username: ";
cin>>ruserId;
cout<<"\t\t\t Enter the password: ";
cin>>rpassword;

ofstream f1("records.txt", ios::app);
f1<<ruserId<<' '<<rpassword<<endl;
system("cls");

cout<<"\n\t\t\t Registration is sucessfull \n";
main();
}

void forgot()
{
    int option;
    system("cls");
    cout<<"\t\t\t you forgot the password?";
    cout<<"Press 1 to search your id by username"<<endl;
    cout<<"Press 2 to go back to the main menu"<<endl;
    cout<<"\t\t\t Enter your choice: ";
    cin>>option;

    switch(option)
    {
        case 1:
         {
            int count=0;
            string suserId,sId,spass;
            cout<<"\n\t\t enter the username which you remembered:";
            cin>>suserId;

            ifstream f2("records.txt");
            while(f2>>sId>>spass)
            {
                if(sId==suserId)
                {
                    count=1;
                }
            }
           f2.close();

           if(count==1)
           {
            cout<<"\n\n your account is found! \n";
            cout<<"\n\n Your password is :     "<<spass;
            main();
           }
            else
            {
                cout<<"\n\t sorry! your account is not found! \n";
                main();

            }
           break;
         }
          
          case 2:
          {
            main();

          }
          default:
                 cout<<"\t\t\t Wrong choice ! please try again"<<endl;
                 forgot();
    } 
}

