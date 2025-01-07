#include <stdio.h>
#include <string.h>

struct Date {
    int month; 
    int day;   
    int year;  
};

struct Category {
    char CategoryId[10];   
    char CategoryName[10];
};

struct Product {
    char productId[10];  
    char categoryId[10]; 
    char productName[10]; 
    int quantity;        
    int price;           
};

struct Order {
    char orderId[10];   
    char customerId[20]; 
    struct Date date;   
    struct Product product;
};

struct User {
    char email[50];
    char password[10];
};


