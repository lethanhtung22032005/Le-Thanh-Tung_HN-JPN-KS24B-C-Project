#ifndef FUNCTION_H
#define FUNCTION_H
#include "datatype.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_CATEGORY_ID_LENGTH 3
#define MAX_CATEGORY_NAME_LENGTH 10
#define MAX_CATEGORIES 100

void displayCategories(struct Category categories[], int numCategories);

void displaySortMenu();

void displaySortOrderMenu();

void displayCategoryMenu();

void addCategory(struct Category categories[], int *numCategories);

void editCategory(struct Category categories[], int numCategories);

void deleteCategory(struct Category categories[], int *numCategories);

int findCategoryByIdAdd(const char *categoryId, struct Category categories[], int numCategories);

int findCategoryById(const char *categoryId);

void searchCategoryByName(struct Category categories[], int numCategories);

void sortCategoriesByName(struct Category categories[], int numCategories, bool ascending);

void sortCategoriesById(struct Category categories[], int numCategories, bool ascending);

int compareCategories(const void *a, const void *b, bool ascending);

int compareCategoriesById(const void *a, const void *b, bool ascending);

void saveCategoriesToBinaryFile(const char *filename, struct Category categories[], int numCategories);

bool loadCategoriesFromBinaryFile(const char *filename, struct Category categories[], int *numCategories);


// San pham
void displayProducts(struct Product products[], int numProducts);
void addProduct(struct Product products[], int *numProducts);
void editProduct(struct Product products[], int numProducts);
void deleteProduct(struct Product products[], int *numProducts);
int findProductById(const char *productId, struct Product products[], int numProducts);
void searchProductByName(struct Product products[], int numProducts);
int compareProductsByPrice(const void *a, const void *b);
void sortProductsByPrice(struct Product products[], int numProducts);
void displayProductMenu();
void displayProductSortMenu();
void saveProductsToFile(struct Product products[], int numProducts);
int loadProductsFromFile(struct Product products[]);
#endif



