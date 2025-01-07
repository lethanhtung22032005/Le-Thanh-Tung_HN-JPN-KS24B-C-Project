#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#include "function.h"

void displayLoginMenu() {
	printf("\n");
    printf("     Chon Quyen Dang Nhap\n");
    printf("     =================\n");
    printf("     [1] Admin.\n");
    printf("     [0] Thoat.\n");
    printf("     =================\n");
}

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
#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 10

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int get_int_input(const char *prompt) {
    char input[100]; 
    int value;
    bool valid_input = false;

    do {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%d", &value) == 1) {
                valid_input = true;
            } else {
                printf("Input khong hop le. Vui long nhap mot so.\n");
            }
        } else {
            printf("Loi khi doc input.\n");
            clear_input_buffer();
        }
    } while (!valid_input);

    return value;
}

bool is_valid_email(const char *email) {
    if (email == NULL || strlen(email) == 0 || strlen(email) > MAX_EMAIL_LENGTH) {
        return false;
    }
    return strchr(email, '@') != NULL;
}
#ifndef _WIN32

char *get_password(const char *prompt) {
    char *password = NULL;
    password = getpass(prompt);
    if (password != NULL)
        return strdup(password);
    return NULL;
}
#else
char *get_password(const char *prompt) {
    char password[MAX_PASSWORD_LENGTH + 1] = {0}; 
    int i = 0;
    char ch;
    printf("%s", prompt);
    while ((ch = _getch()) != '\r' && i < MAX_PASSWORD_LENGTH) { 
        if (ch == '\b') { 
            if (i > 0) {
                i--;
                printf("\b \b"); 
            }
        } else {
            password[i++] = ch;
            printf("*"); 
        }
    }
    password[i] = '\0';
    printf("\n");
    return _strdup(password);
}
#endif
int main() {
	int choice;
    char email[MAX_EMAIL_LENGTH];
    char *password;
    
    struct User admin_user;
    strcpy(admin_user.email, "admin@gmail.com");
    strcpy(admin_user.password, "12345");
    
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
		displayLoginMenu();
        choice = get_int_input("     Nhap lua chon: ");

        switch (choice) {
            case 1:
                printf("\n");
                printf("Dang Nhap\n");
                printf("=======\n");

                do {
                    printf("Email: ");
                    if (fgets(email, sizeof(email), stdin) != NULL) {
                        email[strcspn(email, "\n")] = 0;
                        if (!is_valid_email(email)) {
                            printf("Email khong hop le. Vui long nhap lai.\n");
                        }
                        else {
                        	break;
						}
                    } else {
                        printf("Loi khi doc email.\n");
                        clear_input_buffer();
                    }
                } while (true); 
                password = get_password("Password: ");
                if (password == NULL) {
                    printf("Loi khi nhap mat khau.\n");
                    clear_input_buffer(); 
                    continue; 
                }
                if (strcmp(email, admin_user.email) == 0 && strcmp(password, admin_user.password) == 0) {
                    printf("Dang nhap thanh cong!\n");
                    
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

                } 
				else {
                    printf("Email hoac mat khau khong dung.\n");
                }

                free(password);
                break;
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    } while (choice != 0);
    
    saveCategoriesToBinaryFile(filename, categories, numCategories);
    saveProductsToFile(products, numProducts);
    return 0;
}
