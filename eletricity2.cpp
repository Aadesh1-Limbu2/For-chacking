#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class Customer{
    public:
    int id;
    string customername;
    double sr_num;
    string address;
    double contact;

    Customer(int id, string customername, double sr_num, string address, double contact)
    :id(id), customername(customername), sr_num(sr_num), address(address), contact(contact) {}

    void display() const {
        cout << "ID: "<<id<<"\Name: "<< customername<<"/n SR number: "<< sr_num<<"\n Address: "<< address<<"\n contact number: "<< contact<<endl;

    }
};
class Bill{
    public:
    
}
int main(){
    
    return 0;
}