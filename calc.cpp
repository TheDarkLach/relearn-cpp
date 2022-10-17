using namespace std;
#include<iostream>  
#include<stdio.h>


void add();  
void sub();  
void mult();  
void div();   
void exit();  

int main()
{
    int sign;
    float num1,num2;

    cout << "What would you like to do?" 
    "\n1. Addition"
    "\n2. Subtraction"
    "\n3. Multiplication"
    "\n4. Division"
    "\n5. Exit\n";
    cin >> sign;

    switch(sign)
    {
        case 1:
            add();
            break;
        case 2:
            sub();
            break;
        case 3:
            mult();
            break;
        case 4:
            div();
            break;
        case 5:
            exit(0);
    }
    cout << "----------------------------------------------"
    

}
void add()
{
    int i,n,total=0,num;
    cout << "How many numbers would you like to add?\n";
    cin >> n;
    cout << "List numbers one at a time\n";
    for (i = 0; i < n; i++)
    {
        cin >> num;
        total = total + num;
    }
    cout << "\nThe answer is: " << total;
}
void sub()
{
    int i,n1,n2,total=0;
    cout << "What is the first number?\n";
    cin >> n1;
    cout << "What is the second number?\n";
    cin >> n2;
    total = n1 - n2;
    cout << "\nThe answer is: " << total;
}
void mult()
{
    int i,n,total=1,num;
    cout << "How many numbers would you like to multiply?\n";
    cin >> n;
    cout << "List numbers one at a time\n";
    for (i = 0; i < n; i++)
    {
        cin >> num;
        total = total * num;
    }
    cout << "\nThe answer is: " << total;
}
void div()
{
    int i,n1,n2,total=0;
    cout << "What is the first number?\n";
    cin >> n1;
    cout << "What is the second number?\n";
    cin >> n2;
    total = n1 / n2;
    cout << "\nThe answer is: " << total;
}

