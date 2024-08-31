#include "binary.h"
#include <string>

using namespace std;

Binary::Binary(const int SIZE) 
{
    arr = new string[SIZE]; //allocates memory in the heap for the array
    pos = 0; //starting index of array
}
Binary::~Binary() 
{
    delete arr; //deallocates the memory
    arr = nullptr; //makes arr stop pointing to the previous address in the heap
}
void Binary::push(string binary) 
{
    arr[pos] = binary;
    pos++;
}
string Binary::operator[](int i) {
    return arr[i];
}
bool Binary::isBinary(string& arr)
{
    int check = 0;
    for(int i = 0; i < arr.length(); i++) //if a number in the binary entered is not 1 or 0, it will return false
    {
        if(arr[i] != '0' && arr[i] != '1') check = 1;
    }
    return check==1? false: true;
}
void Binary::addLeadingZeros(const int SIZE)
{
    string zero_str = "";
    int zero = 0;
    string str = "";
    string new_str = "";
    for(int i = 0; i < SIZE-1; i++) //this loop controls how many times it should run based on how
    {                               //many binary numbers were entered
        if(arr[i].length() < arr[i+1].length()) //this checks to see if the first number needs zeros added
        {
            str = arr[i];
            zero = arr[i+1].length() - arr[i].length();
            
            for (int j = 1; j <= zero; j++)
            {
                zero_str += "0";
            }
            new_str = zero_str + str;
            zero_str = "";
            arr[i] = new_str;
        }
        else if(arr[i+1].length() < arr[i].length()) //this checks to see if the second number needs zeros added
        {
            str = arr[i+1];
            zero = arr[i].length() - arr[i+1].length();

            for (int j = 1; j <= zero; j++)
            {
                zero_str += "0";
            }
            new_str = zero_str + str;
            zero_str = "";
            arr[i+1] = new_str;
        }
    }
}
string Binary::addZeros(string binary1, string binary2)
{
    //this function I added to make it easier to add zeros to the product of the later functions 
    //if they are not the same size
    string zero_str = "";
    int zero = 0;
    string str = "";
    string new_str = "";
    str = binary1;
    zero = binary2.length() - binary1.length();
            
    for (int i = 1; i <= zero; i++)
    {
        zero_str += "0";
    }
    new_str = zero_str + str;
    zero_str = "";
    return binary1 = new_str;
}
void Binary::removeZeros(string& binary)
{
    //this function I added to remove leading zeros from the products of the later functions
    //for beautification when displaying them
    for(int i = 0; i < binary.length()-1; i++)
    {
        if(binary[0] == '0') binary.erase(0,1);
        else break;
    }
}
void Binary::swap(int pos1, int pos2) //swaps two binaries if given their positions
{
    string temp = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = temp;
}
void Binary::swap(string& bin1, string& bin2) //swaps two binaries if given them directly
{
    string temp = bin1;
    bin1 = bin2;
    bin2 = temp;
}
string Binary::add(const int SIZE)
{
    return add(arr, SIZE);
}
string Binary::subtract(const int SIZE)
{
    return subtract(arr, SIZE);
}
string Binary::add(string* array, const int SIZE)
{
    string str = "", binary_sum = "";
    for(int i = 0; i < array[0].length(); i++) //this initializes the sum to 0, but to make things
    {                                        //easier, it makes it the same length as the number it
        binary_sum += "0";                   //is going to be added to
    }
    int intbin1 = 0, intbin2 = 0, sum = 0, carry = 0;

    for(int i = 0; i < SIZE; i++) //this loop controls how many times it should run based on how
    {                             //many binary numbers were entered
        string binary1 = array[i];
        string binary2 = binary_sum;
        if(binary1.length() < binary2.length()) binary1 = addZeros(binary1, binary2); //this & the next line adds leading zeros
                                                                                      //if needed to make them the same length
        else if(binary2.length() < binary1.length()) binary2 = addZeros(binary2, binary1);
        
        for(int j = binary1.length()-1; j >= 0; j--) { //this loop starts at the last index of the numbers being added together, and adds them together
            intbin1 = (int)(binary1[j] - '0');
            intbin2 = (int)(binary2[j] - '0');

            sum = carry + intbin1 + intbin2;
            if(sum == 0){
                str = "0" + str;
                carry = 0;
            }else if(sum == 1){
                str = "1" + str;
                carry = 0;
            }else if(sum == 2){
                str = "0" + str;
                carry = 1;
            }else{
                str = "1" + str;
                carry = 1;
            }
        }
        if(carry == 1) str = "1" + str; 
        
        binary_sum = str;
        str = "";
        carry = 0;
    }
    return binary_sum;
}
string Binary::subtract(string* array, const int SIZE)
{
    string str = "", binary_difference = "";
    for(int i = 0; i < array[0].length(); i++) //this initializes the difference to 0, but to make things
    {                                        //easier, it makes it the same length as the number it
        binary_difference += "0";            //is going to be subtracted with
    }
    int intbin1 = 0, intbin2 = 0, difference = 0, k = 1;
    bool done = false;
    for(int i = 0; i < SIZE; i++) //this loop controls how many times it should run based on how
    {                             //many binary numbers were entered
        string binary1 = array[i], binary2 = binary_difference;

        if(binary1 < binary2) swap(binary1, binary2); //this swaps the two numbers if the first one is not bigger than the second one

        for(int j = binary1.length()-1; j >= 0; j--) //this loop starts at the last index of the numbers being subtracted, and subtracts them
        {
            intbin1 = (int)(binary1[j] - '0');
            intbin2 = (int)(binary2[j] - '0');

            if(intbin1 == 0 && intbin2 == 1){
                intbin1 += 2;
                while(done == false){
                    if(binary1[j-k] == '1'){
                        binary1[j-k] = '0';
                        done = true;
                    }else{
                        binary1[j-k] = '1';
                        done = false;
                    }
                    k++;
                } 
            }
            k = 1;
            done = false;
            difference = intbin1 - intbin2;
            str = difference == 0? "0" + str: "1" + str;
        }
        binary_difference = str;
        str = "";
    }
    return binary_difference;
}
string Binary::multiply(const int SIZE)
{
    string binary_product = "1";
    string str = "";
    int intbin1 = 0;
    int intbin2 = 0;
    int product = 0;
    int zeros = 0;
    int temp = 0;
    for (int i = 0; i < SIZE; i++) //this loop controls how many times it should run based on how
    {                              //many binary numbers were entered
        string binary1 = arr[i];   
        string binary2 = binary_product;
        string toAdd[binary2.length()];
        int m = 0;

        for(int j = binary2.length()-1; j >=0; j--) //this loop controls the second binary number
        {
            intbin2 = (int)(binary2[j] - '0');
            while(temp > 0)
            {
                str = "0" + str;
                temp--;
            }
            for(int k = binary1.length()-1; k >=0; k--) //this loop controls the first binary number
            {
                intbin1 = (int)(binary1[k] - '0');
                product = intbin1 * intbin2;
                
                str = product == 0? "0" + str: "1" + str;
            }
            zeros++;
            temp = zeros;
            toAdd[m] = str;

            str = "";
            m++;
        }
        
        binary_product = add(toAdd, binary2.length());
        zeros = 0;
        temp = 0;
        
    }
    removeZeros(binary_product);
    return binary_product;
}
string Binary::divide(const int SIZE)
{
    string binary_product = "1";
    string q = "";
    string r = "";

    for (int i = 0; i < SIZE; i++) //this loop controls how many times it should run based on how
    {                              //many binary numbers were entered
        string binary1 = binary_product;
        string binary2 = arr[i];
        string temp = "";
        string part_binary2 = "";
        string toSubtract[2];
        string part_binary2_zeros = "";
        string binary1_zeros = "";
        int index = 0;

        if(binary1 > binary2) swap(binary1, binary2); //this swaps the numbers if the first number is bigger than the second
        
        part_binary2 += binary2[0];

        for(int j = 0; j < arr[0].length(); j++) //this loop controls the index of which number will be "pulled down" from the second binary number
        {
            toSubtract[2];
            while (j < binary2.length()) //this loop determines whether the quotient will have 0 or 1 added to it
            {
                part_binary2_zeros = part_binary2;
                binary1_zeros = binary1;

                if(part_binary2.length() < binary1.length()) part_binary2_zeros = addZeros(part_binary2, binary1); //these two lines make the two numbers
                else if(part_binary2.length() > binary1.length()) binary1_zeros = addZeros(binary1, part_binary2); //being compared the same length

                if(binary1_zeros <= part_binary2_zeros) //this if else statement determines if q will have 1 or 0 added to it based on which number is larger
                {
                    toSubtract[0] = part_binary2_zeros;
                    toSubtract[1] = binary1_zeros;
                    part_binary2 = (subtract(toSubtract, 2)) + (binary2[j+1]);
                    q+='1';
                    break;
                }
                else 
                {
                    part_binary2 += binary2[j+1];
                    j++;
                    q+='0';
                }
            }            
        }
        r = part_binary2;
        binary_product = q;
        q = "";        
    }
    removeZeros(binary_product); 
    removeZeros(r);
    return "       quotient  = " + binary_product + "\n       remainder = " + r;
}
