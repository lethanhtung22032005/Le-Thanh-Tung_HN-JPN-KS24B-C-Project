#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#include "function.h"

void displayMainProgramMenu() {
    printf("\n");
    printf("     +* Quan ly Cua Hang *+\n");
    printf("     ========================\n");
    printf("     |          MENU        |\n");
    printf("     ========================\n");
    printf("     | [1] Quan ly Danh muc |\n");
    printf("     | [2] Quan ly San pham |\n");
    printf("     | [0] Thoat            |\n");
    printf("     ========================\n");
    printf("     Nhap lua chon: ");
}


void displayCategoryManagementMenu() {
	printf("\n");
    printf("     +* Quan ly Danh muc *+\n");
    printf("     =========================\n");
    printf("     |           MENU        |\n");
    printf("     =========================\n");
    printf("     | [1] Hien thi danh sach|\n");
    printf("     | [2] Them danh muc     |\n");
    printf("     | [3] Sua danh muc      |\n");
    printf("     | [4] Xoa danh muc      |\n");
    printf("     | [5] Sap xep danh muc  |\n");
    printf("     | [6] Tim kiem danh muc |\n");
    printf("     | [7] Luu du lieu       |\n");
    printf("     | [0] Thoat             |\n");
    printf("     =========================\n");
    printf("     Nhap lua chon: ");
}

void displayProductManagementMenu() { 
    printf("\n");
    printf("     +* Quan ly San pham *+\n");
    printf("     =========================\n");
    printf("     |         MENU          |\n");
    printf("     =========================\n");
    printf("     | [1] Hien thi danh sach|\n");
    printf("     | [2] Them san pham     |\n");
    printf("     | [3] Sua san pham      |\n");
    printf("     | [4] Xoa san pham      |\n");
    printf("     | [5] Tim kiem SP       |\n");
    printf("     | [6] Sap xep SP        |\n");
    printf("     | [0] Thoat             |\n");
    printf("     =========================\n");
    printf("     Nhap lua chon: ");
}

#define MAX_CATEGORIES 100
#define MAX_PRODUCTS 100
int main() {
    const char *filename = "categories.bin";
    struct Category categories[MAX_CATEGORIES];
    int numCategories = 0;
    
    struct Product products[MAX_PRODUCTS];
    int numProducts = 0;
	numProducts = loadProductsFromFile(products);
    
    
	int productChoice;
    int mainChoice;
    int sortChoice;
    int sortOrderChoice;
    bool ascending;
    
    do {
        displayMainProgramMenu();
        scanf("%d", &mainChoice);
        getchar();

        switch (mainChoice) {
            case 1:
            {
            	if (!loadCategoriesFromBinaryFile(filename, categories, &numCategories)) {
			        printf("Khoi tao danh sach danh muc moi.\n");
			    }
                int categoryChoice;
                do {
                    displayCategoryManagementMenu();
                    if (scanf("%d", &categoryChoice) != 1) {
					    printf("Lua chon khong hop le (khong phai so). Vui long nhap lai.\n");
					    while (getchar() != '\n'); 
					    continue;
					}
					int ch = getchar();
					if (ch != '\n') {
			            printf("Lua chon khong hop le (co ky tu sau so). Vui long nhap lai.\n");
			            while (getchar() != '\n'); 
			            continue;
			        }
//	                scanf("%d", &categoryChoice);
//                    getchar();
//                    do { 
//				        categoryChoice = getchar();
//				        
//				        if (isspace(categoryChoice)) {
//				        	printf("Lua chon khong hop le. Vui long nhap lai.\n");
//				        	while(getchar() != '\n');
//						}
//						else {
//							ungetc(categoryChoice, stdin); 
//							if (scanf("%d", &categoryChoice) != 1) {
//								printf("Lua chon khong hop le. Vui long nhap lai.\n");
//				        		while(getchar() != '\n');
//				        		categoryChoice = -1;
//							}
//						}
//					} while(categoryChoice == -1);
                   
	                    switch (categoryChoice) {
	                        case 1:
	                            displayCategories(categories, numCategories);
	                            break;
	                        case 2:
	                            addCategory(categories, &numCategories);
	                            break;
	                        case 3:
	                            editCategory(categories, numCategories);
	                            break;
	                        case 4:
	                            deleteCategory(categories, &numCategories);
	                            break;
	                        case 5: 
	                        do {
	                            displaySortMenu();
	                            scanf("%d", &sortChoice);
	                            getchar();
	
	                            switch (sortChoice) {
	                                case 1:
	                                    do{
	                                        displaySortOrderMenu();
	                                        scanf("%d", &sortOrderChoice);
	                                        getchar();
	                                        switch (sortOrderChoice)
	                                        {
	                                        case 1:
	                                            ascending = true;
	                                            sortCategoriesByName(categories, numCategories, ascending);
	                                            break;
	                                        case 2:
	                                            ascending = false;
	                                            sortCategoriesByName(categories, numCategories, ascending);
	                                            break;
	                                        case 0:
	                                            break;
	                                        default:
	                                            printf("Lua chon khong hop le. Vui long thu lai.\n");
	                                        }
	                                    } while (sortOrderChoice!=0);
	                                    break;
	                                case 2: 
	                                    do{
	                                        displaySortOrderMenu();
	                                        scanf("%d", &sortOrderChoice);
	                                        getchar();
	                                        switch (sortOrderChoice)
	                                        {
	                                        case 1:
	                                            ascending = true;
	                                            sortCategoriesById(categories, numCategories, ascending);
	                                            break;
	                                        case 2:
	                                            ascending = false;
	                                            sortCategoriesById(categories, numCategories, ascending);
	                                            break;
	                                        case 0:
	                                            break;
	                                        default:
	                                            printf("Lua chon khong hop le. Vui long thu lai.\n");
	                                        }
	                                    } while (sortOrderChoice!=0);
	                                    break;
	                                case 0:
	                                    break;
	                                default:
	                                    printf("Lua chon khong hop le. Vui long thu lai.\n");
	                            }
	                        } while (sortChoice != 0);
	                        break;
	                        case 6: searchCategoryByName(categories, numCategories); break;
	                        case 7: saveCategoriesToBinaryFile(filename, categories, numCategories); break;
	                        case 0:
	                            break;
	                        default:
	                            printf("Lua chon khong hop le. Vui long thu lai.\n");
	                    }
					
                } while (categoryChoice != 0);
                break;
            }
            case 2: 

                do {
                    displayProductManagementMenu();
                    scanf("%d", &productChoice);
                    getchar();
                    switch (productChoice) {
                        case 1:
                            displayProducts(products, numProducts);
                            break;
                        case 2:
                            addProduct(products, &numProducts);
                            break;
                        case 3:
                            editProduct(products, numProducts);
                            break;
                        case 4:
                            deleteProduct(products, &numProducts);
                            break;
                        case 5:
                            searchProductByName(products, numProducts);
                            break;
                        case 6:
                            sortProductsByPrice(products, numProducts);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Lua chon khong hop le. Vui long thu lai.\n");
                    }
                } while (productChoice != 0);
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    } while (mainChoice != 0);
    saveCategoriesToBinaryFile(filename, categories, numCategories);
    saveProductsToFile(products, numProducts);
    return 0;
}
