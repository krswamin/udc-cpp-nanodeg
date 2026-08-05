/*
Instructions:

- Declare an integer array arr of size 5 and initialize it with the values 10, 20, 30, 40, 50.
- Declare an integer pointer pArr and make it point to the first element of the array.
- Using pArr and pointer arithmetic (i.e., pArr + offset), print each element of the array. Do not use array indexing (arr[i]) for this part.
- Print the memory address of each element using pointer arithmetic.
- Now, write a loop that iterates through the array using pArr and increments pArr in each iteration. Inside the loop, print the value pointed to by pArr.

*/

# include<iostream>
using namespace std;

int main(){
    
    int arr[5] = {10,20,30,40,50};
    int *ptr = arr;
    int num_arr_elements = sizeof(arr) / sizeof(arr[0]); 
    
    for(int i=0; i< num_arr_elements; i++ ){
       cout<<*(ptr+i)<<", ";
    }
    cout<<endl;
}