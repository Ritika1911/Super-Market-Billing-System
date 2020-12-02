#include <iostream>
#include <process.h>
#include <conio.h>
#include <fstream>
using namespace std;
class product 
    {
        int pno;
        char name[50];
        float price,qty,dis,tax;
        public:
            void create_product()
                {
                    cout<< "\n Enter the Product Name "<<endl;
                    cin>>gets(name);
                    cout<< "\n Enter the Product NO."<< endl;
                    cin>>pno;
                    cout<<"\n Enter the Price  of the Product"<<endl;
                    cin>>price;
                    cout<<"Enter the Discount(%)"<<endl;
                    cin >>dis;
                }
            void show_product()
                {
                    cout<< "\n  Product No.:"<<pno;
                    cout << "\n The  Name of the Product: ";
                    puts(name);
                    cout<<"\nPrice:" << price;
                    cout<< "n\discount" << dis;
                }
            int retpno()
                {
                    return pno;
                } 
            float retprice()
                {
                    return price;
                }
            char * retname()
                {
                    return name;
                }
            int retdis()
                {
                    return dis;
                }
    };
fstream fp;
product pr;
void write_product()
    {
    fp.open("Shop.dat",ios::out | ios::app);
    pr.create_product();
    fp.write((char *)&pr,sizeof(product));
    fp.close();
    cout<<"\n \n The product has been Created";
    getch();
    }
void display_all()
    {
        cout<<"\n\n\n\t\t DISPLAY ALL RECORD \n\n";
        fp.open("Shop.dat",ios::in);
        while(fp.read((char *)&pr,sizeof(product)))
            {
                pr.show_product();
                cout<<"\n\n==========================\n";
                getch();
            }
        fp.close();
        getch();    
    }    
void display_sp(int n)
    {
        int flag=0;
        fp.open("Shop.dat",ios:: in);
        while(fp.read((char *)&pr,sizeof(product)))
            {
                if(pr.retpno()==n)
                    {
                        pr.show_product();
                        flag=1;
                    }        
            }
        fp.close();
        if (flag==0)
            cout<<"\n\nrecord doesn't exist";
        getch();        
    }    
void modify_product()
    {
        int no,found=0;
        cout<<"\n\n\tTo Modify ";
        cout << "\n\n\tPlease Enter The Product No. of The Product";
        cin>>no;
        fp.open("Shop.dat",ios::in | ios::out);
        while(fp.read((char * ) & pr, sizeof(product) && found==0))
            {
                if(pr.retpno()==no)
                    {
                        pr.show_product();
                        cout<<"\nPlease Enter New Details Of The Product"<<endl;
                        pr.create_product();
                        int pos=-1*sizeof(pr);
                        fp.seekp(pos,ios::cur);
                        fp.write((char *)&pr, sizeof(product));
                        cout<<"\n\n\t Record Updated";
                        found=1;
                    }
            } 
        fp.close();
        if (found==0)
            cout<<"\n\n\t Record Not Found";    
        getch();
    }
void delete_product()
    {
        int no;
        cout<< "\n\n\n\tDelete Record";
        cout<< "\n\nPlease Enter The product no. of The Product You Want To Delete";
        cin>>no;
        fp.open("Shop.dat",ios::in | ios::out);
        fstream fp2;
        fp2.open("Temp.dat",ios::out);
        fp.seekg(0,ios::beg);
        while(fp.read((char *)&pr,sizeof(product)))
        {
            if(pr.retpno()!=no)
                {
                    fp2.write((char *)&pr,sizeof(product));
                }
        }
        fp2.close();
        fp.close();
        remove("Shop.dat");
        rename("Temp.dat","Shop.dat");
        cout<<"\n\nRecord Deleted...";
        getch();
    }
void Product_list()
    {

        fp.open("Shop.dat", ios:: in );
        if (!fp)
        {
            cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File ";

        }

        cout << "\n\n\t\tProduct MENU\n\n";
        cout << "====================================================\n";
        cout << "P.NO.\t\tNAME\t\tPRICE\n";
        cout << "====================================================\n";

        while (fp.read((char * ) & pr, sizeof(product)))
        {
            cout << pr.retpno() << "\t\t" << pr.retname() << "\t\t" << pr.retprice() << endl;
        }
        fp.close();
    }
void Customer()
    {
        int order_arr[50], quan[50], c = 0;
        float amt, damt, total = 0;
        char ch = 'Y';
        Product_list();
        cout << "\n============================";
        cout << "\n PLACE YOUR ORDER";
        cout << "\n============================\n";
        do
            {
                cout << "\n\nEnter The Product No. Of The Product : ";
                cin >> order_arr[c];
                cout << "\nQuantity in number : ";
                cin >> quan[c];
                c++;
                cout << "\nDo You Want To Order Another Product ? (y/n)";
                cin >> ch;
            } while (ch == 'y' || ch == 'Y');
        cout << "\n\nThank You For Placing The Order";
        getch();

        cout << "\n\n******************************** INVOICE ************************\n";
        cout << "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n ";

        for (int x = 0; x <= c; x++)
            {
                fp.open("Shop.dat", ios:: in );
                fp.read((char * ) & pr, sizeof(product));
                while (!fp.eof())
                {
                    if (pr.retpno() == order_arr[x])
                    {
                        amt = pr.retprice() * quan[x];
                        damt = amt - (amt * pr.retdis() / 100);
                        cout << "\n" << order_arr[x] << "\t" << pr.retname() <<
                            "\t" << quan[x] << "\t\t" << pr.retprice() << "\t" << amt << "\t\t" << damt;
                        total += damt;
                    }
                    fp.read((char * ) & pr, sizeof(product));
                }

                fp.close();
            }
        cout << "\n\n\t\t\t\t\tTOTAL = " << total;
        getch();
    }
void Admin()
    {
        int ch;
        cout << "\n\n\n\tADMIN MENU";
        cout << "\n\n\t1.Create Product";
        cout << "\n\n\t2.Display Product";
        cout << "\n\n\t3.Query";
        cout << "\n\n\t4.Modify Product";
        cout << "\n\n\t5.Delete Product";
        cout << "\n\n\t6.View Product ";
        cout << "\n\n\t7.BACK TO MAIN MENU";
        cout << "\n\n\tPlease Enter Your Choice (1-7) ";
        cin>>ch;
        switch(ch)
            {
                case 1:
                    {
                        write_product();
                        break;
                    }
                case 2:
                    {
                        display_all();
                        break;
                    }
                case 3:
                    {
                        int num;
                        cout<<" \n\n\t Enter the Produt No.";
                        cin>>num;
                        display_sp(num);
                        break;
                    }
                case 4:
                    {
                        modify_product();
                        break;
                    }
                case 5:
                    {
                        delete_product();
                        break;
                    }
                case 6:
                    {
                        Product_list();
                        getch(); // this fucntion pauses the output console until a key is pressed 
                    }
                default:
                    cout<< "\a";
                    Admin();
            }
    }
void menu()
        {    int menuselect;
                 

        }

void intro()
{
    cout<<"\tWELCOME " << endl;
    cout << "\t\tTO" << endl;
    cout << "\t\t\tCBIT" << endl;
    cout << " \t\t\t\tSUPERMARKET" <<endl;
    getch();
};
int  main()
    {   char menuselect;
        intro();
        do{ 
            cout<<"1.Customer"<<endl;
            cout<<"2.Admin"<<endl;
            cout<<"3.Exit"<<endl;
            menuselect=getche();
            switch (menuselect)
                {
                    case '1':
                        {
                            Customer();
                            getch();
                            break;
                        }
                        case '2':
                            {
                                Admin();
                                break;
                            }
                        case '3':
                            {
                            cout<<"THANK YOUT FOR USING CBIT SUPER MARKET"<<endl;
                            return 0;
                            }
                        default:
                            {
                                cout<< "Choose a valid no."<<endl;
                                break;
                            }
                }
        }while (menuselect!='3');
    }


        
