#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "datatype.h"
#define MAX_CATEGORIES 100
#define MAX_PRODUCTS 100
#define MAX_CATEGORY_ID_LENGTH 3
#define MAX_CATEGORY_NAME_LENGTH 10

struct Category categories[MAX_CATEGORIES];
int numCategories = 0;
void displayCategories(struct Category categories[], int numCategories) {
    if (numCategories == 0) {
        printf("Khong co danh muc nao.\n");
        return;
    }

    printf("**** Danh sach Danh muc ****\n"); 

    printf("================================\n");


    printf("| %-5s | %-20s |\n", "ID", "Ten");
    printf("================================\n");

  
    for (int i = 0; i < numCategories; i++) {
        printf("| %-5s | %-20s |\n", categories[i].CategoryId, categories[i].CategoryName);
        printf("================================\n");
    }
}
static bool isCategoryIdExists(const char *categoryId, struct Category categories[], int numCategories) {
    for (int i = 0; i < numCategories; i++) {
        if (strcmp(categories[i].CategoryId, categoryId) == 0) {
            return true;
        }
    }
    return false;
}


bool isCategorytNameExists(const char *categoryName, struct Category categories[], int numCategories){
    for (int i = 0; i < numCategories; i++) {
        if (strcmp(categories[i].CategoryName, categoryName) == 0) {
            return true;
        }
    }
    return false;
}

void addCategory(struct Category categories[], int *numCategories) { 
    if (*numCategories >= MAX_CATEGORIES) {
        printf("Da dat toi so luong danh muc toi da.\n");
        return;
    }

    struct Category newCategory;
    bool isValid = false;

	do {
        printf("Nhap ID danh muc (toi da %d ky tu): ", MAX_CATEGORY_ID_LENGTH - 1);
        scanf(" %[^\n]s", newCategory.CategoryId);
        getchar();
        if (strlen(newCategory.CategoryId) == 0) {
            printf("ID danh muc khong duoc de trong.\n");
        } else if (strlen(newCategory.CategoryId) > MAX_CATEGORY_ID_LENGTH - 1) {
            printf("ID danh muc vuot qua so ky tu cho phep.\n");
        } else if (isCategoryIdExists(newCategory.CategoryId, categories, *numCategories)) {
            printf("ID danh muc da ton tai. Vui long nhap ID khac.\n");
        }else{
            break;
        }
    } while (true);
    
	do {
        printf("Nhap ten danh muc (toi da %d ky tu): ", MAX_CATEGORY_NAME_LENGTH - 1);
        scanf(" %[^\n]s", newCategory.CategoryName);
        getchar();
        if (strlen(newCategory.CategoryName) == 0) {
            printf("Ten danh muc khong duoc de trong.\n");
        } else if (strlen(newCategory.CategoryName) > MAX_CATEGORY_NAME_LENGTH - 1) {
            printf("Ten danh muc vuot qua so ky tu cho phep.\n");
        } else if (isCategorytNameExists(newCategory.CategoryName, categories, *numCategories)) {
            printf("Ten danh muc da ton tai. Vui long nhap ten khac.\n");
        }else{
            break;
        }
    } while (true);
    strcpy(categories[*numCategories].CategoryId, newCategory.CategoryId);
    strcpy(categories[*numCategories].CategoryName, newCategory.CategoryName);
    (*numCategories)++; 
    printf("Da them danh muc thanh cong.\n");
    saveCategoriesToBinaryFile("categories.bin", categories, *numCategories);
}

int findCategoryById(const char *categoryId, struct Category categories[], int numCategories) {
    for (int i = 0; i < numCategories; i++) {
        if (strcmp(categories[i].CategoryId, categoryId) == 0) {
            return i;
        }
    }
    return -1;
}

void editCategory(struct Category categories[], int numCategories) {
    char categoryIdToEdit[MAX_CATEGORY_ID_LENGTH]; 
    printf("\n--- Sua Danh Muc ---\n");
    printf("Nhap ID danh muc muon sua: ");
    scanf(" %[^\n]s", categoryIdToEdit);
    getchar();

    int index = findCategoryById(categoryIdToEdit, categories, numCategories); 
    if (index == -1) {
        printf("Khong tim thay danh muc co ID nay.\n");
        return;
    }

    printf("Ten danh muc hien tai: %s\n", categories[index].CategoryName);
    printf("Nhap ten danh muc moi: ");
    scanf(" %[^\n]s", categories[index].CategoryName); 
    getchar();

    printf("Sua danh muc thanh cong.\n");
}

void deleteCategory(struct Category categories[], int *numCategories) {
    char categoryIdToDelete[MAX_CATEGORY_ID_LENGTH]; 
    printf("\n--- Xoa Danh Muc ---\n");
    printf("Nhap ID danh muc muon xoa: ");
    scanf(" %[^\n]s", categoryIdToDelete);
    getchar();

    int index = findCategoryById(categoryIdToDelete, categories, *numCategories); 
    if (index == -1) {
        printf("Khong tim thay danh muc co ID nay.\n");
        return;
    }
    char confirm;
    printf("Ban co chac chan muon xoa danh muc nay? (y/n): ");
    scanf(" %c", &confirm);
    getchar();

    if (confirm == 'y' || confirm == 'Y') {
        for (int i = index; i < *numCategories - 1; i++) {
            categories[i] = categories[i + 1];
        }
        (*numCategories)--;
        printf("Xoa danh muc thanh cong.\n");
    } else {
        printf("Huy bo xoa danh muc.\n");
    }
}

int compareCategories(const void *a, const void *b, bool ascending) {
    struct Category *catA = (struct Category *)a;
    struct Category *catB = (struct Category *)b;
    int comparison = strcmp(catA->CategoryName, catB->CategoryName);
    return ascending ? comparison : -comparison;
}

int compareCategoriesWrapperAsc(const void *a, const void *b) {
    return compareCategories(a, b, true);
}

int compareCategoriesWrapperDesc(const void *a, const void *b) {
    return compareCategories(a, b, false);
}

int compareCategoriesById(const void *a, const void *b, bool ascending) {
    struct Category *catA = (struct Category *)a;
    struct Category *catB = (struct Category *)b;
    int comparison = atoi(catA->CategoryId) - atoi(catB->CategoryId);
    return ascending ? comparison : -comparison;
}

int compareCategoriesByIdWrapperAsc(const void *a, const void *b) {
    return compareCategoriesById(a, b, true);
}

int compareCategoriesByIdWrapperDesc(const void *a, const void *b) {
    return compareCategoriesById(a, b, false);
}

void sortCategoriesByName(struct Category categories[], int numCategories, bool ascending) {
    if (numCategories == 0) {
        printf("Khong co danh muc nao de sap xep.\n");
        return;
    }

    qsort(categories, numCategories, sizeof(struct Category), ascending ? compareCategoriesWrapperAsc : compareCategoriesWrapperDesc);

    printf("Danh sach danh muc da duoc sap xep theo ten %s.\n", ascending ? "(A-Z)" : "(Z-A)");
    displayCategories(categories, numCategories);
}

void sortCategoriesById(struct Category categories[], int numCategories, bool ascending) {
    if (numCategories == 0) {
        printf("Khong co danh muc nao de sap xep.\n");
        return;
    }

    qsort(categories, numCategories, sizeof(struct Category), ascending ? compareCategoriesByIdWrapperAsc : compareCategoriesByIdWrapperDesc);

    printf("Danh sach danh muc da duoc sap xep theo ID %s.\n", ascending ? "(tang dan)" : "(giam dan)");
    displayCategories(categories, numCategories);
}

void searchCategoryByName(struct Category categories[], int numCategories) {
    char searchName[MAX_CATEGORY_NAME_LENGTH];
    printf("\n--- Tim kiem Danh Muc theo Ten ---\n");
    printf("Nhap ten danh muc muon tim kiem: ");
    scanf(" %[^\n]s", searchName);
    getchar();

    bool found = false;
    printf("Ket qua tim kiem:\n");

    printf("================================\n");
    printf("| %-5s | %-20s |\n", "ID", "Ten");
    printf("================================\n");


    for (int i = 0; i < numCategories; i++) {
        if (strstr(categories[i].CategoryName, searchName) != NULL) {
            printf("| %-5s | %-20s |\n", categories[i].CategoryId, categories[i].CategoryName);
            printf("================================\n");
            found = true;
        }
    }

    if (!found) {
        printf("Khong tim thay danh muc nao co ten chua '%s'.\n", searchName);
    }
}

void saveCategoriesToBinaryFile(const char *filename, struct Category categories[], int numCategories) {
    FILE *fp = fopen(filename, "wb"); 
    if (fp == NULL) {
        printf("Loi mo file de ghi.\n");
        return;
    }

    fwrite(&numCategories, sizeof(int), 1, fp);

    for (int i = 0; i < numCategories; i++) {
        fwrite(&categories[i], sizeof(struct Category), 1, fp);
    }

    fclose(fp);
    printf("Da luu du lieu vao file '%s' thanh cong.\n", filename);
}

bool loadCategoriesFromBinaryFile(const char *filename, struct Category categories[], int *numCategories) {
    FILE *fp = fopen(filename, "rb"); 
    if (fp == NULL) {
        printf("Khong tim thay file '%s'.\n", filename);
        return false;
    }

    if (fread(numCategories, sizeof(int), 1, fp) != 1) {
        printf("Loi doc so luong danh muc tu file.\n");
        fclose(fp);
        return false;
    }

    if (*numCategories > MAX_CATEGORIES){
        printf("So luong danh muc trong file vuot qua gioi han cho phep.\n");
        *numCategories = 0;
        fclose(fp);
        return false;
    }

    for (int i = 0; i < *numCategories; i++) {
        if (fread(&categories[i], sizeof(struct Category), 1, fp) != 1) {
            printf("Loi doc du lieu danh muc tu file.\n");
            *numCategories = 0;
            fclose(fp);
            return false;
        }
    }

    fclose(fp);
    printf("Da doc du lieu tu file '%s' thanh cong.\n", filename);
    return true;
}

void displaySortOrderMenu(){
    printf("\n+* Chon thu tu sap xep *+\n");
    printf("     ========================\n");
    printf("     |        MENU          |\n");
    printf("     ========================\n");
    printf("     | [1] Tang dan         |\n");
    printf("     | [2] Giam dan         |\n");
    printf("     | [0] Quay lai         |\n");
    printf("     ========================\n");
    printf("Nhap lua chon: ");
}

void displaySortMenu(){
    printf("\n");
    printf("     +* Sap xep danh muc *+\n");
    printf("     ========================\n");
    printf("     |        MENU          |\n");
    printf("     ========================\n");
    printf("     | [1] Sap xep theo ten |\n");
    printf("     | [2] Sap xep theo ID  |\n");
    printf("     | [0] Quay lai         |\n");
    printf("     =======================\n");
    printf("     Nhap lua chon: ");	         
}

//San pham
void displayProducts(struct Product products[], int numProducts) {
    if (numProducts == 0) {
        printf("Khong co san pham nao.\n");
        return;
    }
    printf("**** Danh sach San pham ****\n");
    printf("============================================================================\n");
    printf("| %-10s | %-10s | %-20s | %-10s | %-10s |\n", "ID", "Ma DM", "Ten SP", "So luong", "Gia");
    printf("============================================================================\n");

    for (int i = 0; i < numProducts; i++) {
        printf("| %-10s | %-10s | %-20s | %-10d | %-10d |\n", products[i].productId, products[i].categoryId, products[i].productName, products[i].quantity, products[i].price);
        printf("============================================================================\n");
    }
}

bool isProductIdExists(const char *productId, struct Product products[], int numProducts) {
    for (int i = 0; i < numProducts; i++) {
        if (strcmp(products[i].productId, productId) == 0) {
            return true;
        }
    }
    return false;
}

bool isProductNameExists(const char *productName, struct Product products[], int numProducts){
    for (int i = 0; i < numProducts; i++) {
        if (strcmp(products[i].productName, productName) == 0) {
            return true;
        }
    }
    return false;
}

void addProduct(struct Product products[], int *numProducts) {
    if (*numProducts >= MAX_PRODUCTS) {
        printf("Da dat toi so luong san pham toi da.\n");
        return;
    }

    struct Product newProduct;
    bool validInput = false;

    do {
        printf("\n--- Them San Pham ---\n");

        do {
            printf("Nhap ID san pham (toi da 9 ky tu): ");
            scanf("%s", newProduct.productId);
            if (strlen(newProduct.productId) == 0) {
                printf("ID san pham khong duoc de trong.\n");
            } else if (strlen(newProduct.productId) > 9) {
                printf("ID san pham vuot qua so ky tu cho phep.\n");
            } else if (isProductIdExists(newProduct.productId, products, *numProducts)) {
                printf("ID san pham da ton tai. Vui long nhap ID khac.\n");
            }else{
                break;
            }
        } while (true);

        do {
            printf("Nhap ma danh muc san pham (toi da 9 ky tu): ");
            scanf("%s", newProduct.categoryId);
            if (strlen(newProduct.categoryId) == 0) {
                printf("Ma danh muc san pham khong duoc de trong.\n");
            } else if (strlen(newProduct.categoryId) > 9) {
                printf("Ma danh muc san pham vuot qua so ky tu cho phep.\n");
            }else{
                break;
            }
        } while (true);

        do {
            printf("Nhap ten san pham (toi da 9 ky tu): ");
            scanf("%s", newProduct.productName);
            if (strlen(newProduct.productName) == 0) {
                printf("Ten san pham khong duoc de trong.\n");
            } else if (strlen(newProduct.productName) > 9) {
                printf("Ten san pham vuot qua so ky tu cho phep.\n");
            }else if (isProductNameExists(newProduct.productName, products, *numProducts)) {
                printf("Ten san pham da ton tai. Vui long nhap ten khac.\n");
            }else{
                break;
            }
        } while (true);

        do {
            printf("Nhap gia san pham: ");
            if (scanf("%d", &newProduct.price) != 1 || newProduct.price < 0) {
                printf("Gia san pham khong hop le. Vui long nhap so nguyen duong.\n");
                while(getchar() != '\n');
            } else {
                break;
            }
        } while (true);

        do {
            printf("Nhap so luong san pham: ");
            if (scanf("%d", &newProduct.quantity) != 1 || newProduct.quantity < 0) {
                printf("So luong san pham khong hop le. Vui long nhap so nguyen duong.\n");
                while(getchar() != '\n');
            } else {
                break;
            }
        } while (true);

        validInput = true;
    } while (!validInput);

    products[*numProducts] = newProduct;
    (*numProducts)++;
    printf("Them san pham thanh cong.\n");
    saveProductsToFile(products, *numProducts);    
}

bool isProductNameExistsExceptSelf(const char *productName, struct Product products[], int numProducts, int currentIndex) {
    for (int i = 0; i < numProducts; i++) {
        if (i != currentIndex && strcmp(products[i].productName, productName) == 0) {
            return true;
        }
    }
    return false;
}

int findProductById(const char *productId, struct Product products[], int numProducts) {
    for (int i = 0; i < numProducts; i++) {
        if (strcmp(products[i].productId, productId) == 0) {
            return i;
        }
    }
    return -1;
}

void editProduct(struct Product products[], int numProducts) {
    char productIdToEdit[10];
    int index;
    bool validInput = false;

    do {
        printf("\n--- Sua San Pham ---\n");
        printf("Nhap ID san pham muon sua: ");
        scanf("%s", productIdToEdit);

        index = findProductById(productIdToEdit, products, numProducts);
        if (index == -1) {
            printf("Khong tim thay san pham co ID nay. Vui long nhap lai.\n");
            continue;
        } else {
            validInput = true;
        }
    } while (!validInput);

    validInput = false;
    do {
        char newProductName[10];
        int newPrice;
        int newQuantity;

        do {
            printf("Nhap ten san pham moi (toi da 9 ky tu): ");
            scanf("%s", newProductName);
            if (strlen(newProductName) == 0) {
                printf("Ten san pham khong duoc de trong.\n");
            } else if (strlen(newProductName) > 9) {
                printf("Ten san pham vuot qua so ky tu cho phep.\n");
            }else if (isProductNameExistsExceptSelf(newProductName, products, numProducts, index)) {
                printf("Ten san pham da ton tai. Vui long nhap ten khac.\n");
            } else {
                strcpy(products[index].productName, newProductName);
                break;
            }
        } while (true);

        do {
            printf("Nhap gia san pham moi: ");
            if (scanf("%d", &newPrice) != 1 || newPrice < 0) {
                printf("Gia san pham khong hop le. Vui long nhap so nguyen duong.\n");
                while(getchar() != '\n');
            } else {
                products[index].price = newPrice;
                break;
            }
        } while (true);

        do {
            printf("Nhap so luong san pham moi: ");
            if (scanf("%d", &newQuantity) != 1 || newQuantity < 0) {
                printf("So luong san pham khong hop le. Vui long nhap so nguyen duong.\n");
                while(getchar() != '\n');
            } else {
                products[index].quantity = newQuantity;
                break;
            }
        } while (true);
        validInput = true;
    } while (!validInput);

    printf("Sua san pham thanh cong.\n");
}
void deleteProduct(struct Product products[], int *numProducts) {
    char productIdToDelete[10];
    printf("\n--- Xoa San Pham ---\n");
    printf("Nhap ID san pham muon xoa: ");
    scanf("%s", productIdToDelete);

    int index = findProductById(productIdToDelete, products, *numProducts);
    if (index == -1) {
        printf("Khong tim thay san pham co ID nay.\n");
        return;
    }
    char confirm;
    printf("Ban co chac chan muon xoa san pham nay? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        for (int i = index; i < *numProducts - 1; i++) {
            products[i] = products[i + 1];
        }
        (*numProducts)--;
        printf("Xoa san pham thanh cong.\n");
        saveProductsToFile(products, *numProducts);
    } else {
        printf("Huy bo xoa san pham.\n");
    }
}

void searchProductByName(struct Product products[], int numProducts) {
    char productNameToSearch[50];
    printf("Nhap ten san pham muon tim kiem: ");
    scanf("%s", productNameToSearch);
    int found = 0;
    printf("Ket qua tim kiem:\n");
    printf("============================================================================\n");
    printf("| %-10s | %-10s | %-20s | %-10s | %-10s |\n", "ID", "Ma DM", "Ten SP", "So luong", "Gia");
    printf("============================================================================\n");
    for (int i = 0; i < numProducts; i++) {
        if (strstr(products[i].productName, productNameToSearch) != NULL) {
            printf("| %-10s | %-10s | %-20s | %-10d | %-10d |\n", products[i].productId, products[i].categoryId, products[i].productName, products[i].quantity, products[i].price);
            printf("============================================================================\n");
            found = 1;
        }
    }
    if(found == 0){
        printf("Khong tim thay san pham nao!\n");
    }
}

int compareProductsByPrice(const void *a, const void *b) {
    return ((struct Product *)a)->price - ((struct Product *)b)->price;
}

void displayProductSortMenu() {
    printf("\n");
    printf("     +* Sap xep San pham theo gia *+\n");
    printf("     =================================\n");
    printf("     |              MENU             |\n");
    printf("     =================================\n");
    printf("     | [1] Sap xep theo gia tang dan |\n");
    printf("     | [2] Sap xep theo gia giam dan |\n");
    printf("     | [0] Quay lai                  |\n");
    printf("     =================================\n");
    printf("     Nhap lua chon: ");
}

void sortProductsByPrice(struct Product products[], int numProducts) {
    if (numProducts == 0) {
        printf("Khong co san pham nao de sap xep.\n");
        return;
    }
    int choice;
    do{
        displayProductSortMenu();
        scanf("%d", &choice);
        getchar();
        switch(choice){
            case 1:
                qsort(products, numProducts, sizeof(struct Product), compareProductsByPrice);
                printf("Da sap xep san pham theo gia tang dan.\n");
                displayProducts(products, numProducts);
                break;
            case 2:
                qsort(products, numProducts, sizeof(struct Product), compareProductsByPrice);
                for (int i = 0; i < numProducts / 2; i++) {
                    struct Product temp = products[i];
                    products[i] = products[numProducts - i - 1];
                    products[numProducts - i - 1] = temp;
                }
                printf("Da sap xep san pham theo gia giam dan.\n");
                displayProducts(products, numProducts);
                break;
            case 0:
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    }while(choice != 0);

}

void saveProductsToFile(struct Product products[], int numProducts) {
    FILE *fp = fopen("products.bin", "wb");
    if (fp == NULL) {
        perror("Loi mo file de ghi");
        return;
    }

    if (fwrite(products, sizeof(struct Product), numProducts, fp) != (size_t)numProducts) {
        perror("Loi ghi du lieu vao file");
        fclose(fp);
        return;
    }

    fclose(fp);
    printf("Da luu du lieu san pham vao file products.bin\n");
}

int loadProductsFromFile(struct Product products[]) {
    FILE *fp = fopen("products.bin", "rb");
    if (fp == NULL) {
        printf("Khong tim thay file products.bin. Khoi tao danh sach san pham moi.\n");
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    int numProducts = fileSize / sizeof(struct Product);

    if (fileSize % sizeof(struct Product) != 0) {
        fprintf(stderr, "File bi loi, kich thuoc khong hop le.\n");
        fclose(fp);
        return 0;
    }

    if (fread(products, sizeof(struct Product), numProducts, fp) != (size_t)numProducts && !feof(fp)) {
        perror("Loi doc du lieu tu file");
        fclose(fp);
        return 0;
    }

    fclose(fp);
    printf("Da doc du lieu san pham tu file products.bin\n");
    return numProducts;
}
