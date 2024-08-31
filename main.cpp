//Avery Michaels
//This project has the user enter binary numbers, then it adds, subtracts, multiplies, 
//and divides them (bigger number will be the left operand) and displays the results.

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

#include "binary.h"

using namespace std;

int main()
{
    int size = 0; //CHANGE CONSTANT VALUE IF YOU WANT TO INPUT MORE THAN 2 ARRAYS
    try {
        cout << "Enter the number of binary numbers you have to input: ";
        cin >> size;
        if(cin.fail()) {
            throw "Invalid entry";
        }
    }
    catch (string s) { cout << s << endl; }

    Binary binary_arr(size);

    bool check = true;
    string binary = "";
    for(int i = 0; i < size; i++) //this for loop prompts the user to enter a binary number and checks to see
    {                             //if it is actually a binary number, if it is not, it prompts the user again
        cout << "Enter a binary: ";
        cin >> binary;
        check = binary_arr.isBinary(binary);
        while(check == false)
        {
            cout << "The value entered is not a binary number." << endl;
            cout << "Enter a binary: ";
            cin >> binary;
            check = binary_arr.isBinary(binary);
        }
        binary_arr.push(binary);
    }
    for(int i = 0; i < size-1; i++) //this for loop makes the binary numbers the same size by adding leading zeros
    {
        if(binary_arr[i].length() != binary_arr[i+1].length()) binary_arr.addLeadingZeros(size);
    }
    for(int i = 1; i < size; i++) //this for loop sorts the binary numbers from lowest to highest using bubble sort
    {
        for(int j = 0; j < size - i; j++)
        {
            if(binary_arr[j] < binary_arr[j+1]) binary_arr.swap(j, (j+1));
        }
    }
    cout << "Binary numbers: " << endl;
    for (int i = 0; i < size; i++) //displays the binary numbers
    {
        cout << setw(20) << binary_arr[i] << endl;
    }
    cout << "Result of + : " << endl << setw(20) << binary_arr.add(size) << endl;
    cout << "Result of - : " << endl << setw(20) << binary_arr.subtract(size) << endl;
    cout << "Result of * : " << endl << setw(20) << binary_arr.multiply(size) << endl;
    cout << "Result of / : " << endl << binary_arr.divide(size) << endl;
}