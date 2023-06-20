#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

typedef struct
{
    char loginNumber[16];
    char title[80];
    char author[80];
    char category[16];
    char publisher[80];
    char publicationDate[24];
    float price;
} Book;

typedef struct
{
    Book books[MAX_BOOKS];
    int count;
} Library;

/* description: 录入图书
 *
 */
void addBook(Library *library)
{
    if (library->count >= MAX_BOOKS)
    {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    Book book;
    printf("Enter login number: ");
    scanf("%s", book.loginNumber);
    printf("Enter title: ");
    scanf(" %[^\n]", book.title); // 读到回车为止
    printf("Enter author: ");
    scanf(" %[^\n]", book.author);
    printf("Enter category: ");
    scanf(" %[^\n]", book.category);
    printf("Enter publisher: ");
    scanf(" %[^\n]", book.publisher);
    printf("Enter publication date: ");
    scanf(" %[^\n]", book.publicationDate);
    printf("Enter price: ");
    scanf("%f", &book.price);

    library->books[library->count++] = book;
    printf("Book added successfully.\n");
}

/* description: 查看图书信息
 *
 */
void displayBook(const Book *book)
{
    printf("Login Number: %s\n", book->loginNumber);
    printf("Title: %s\n", book->title);
    printf("Author: %s\n", book->author);
    printf("Category: %s\n", book->category);
    printf("Publisher: %s\n", book->publisher);
    printf("Publication Date: %s\n", book->publicationDate);
    printf("Price: %.2f\n", book->price);
    printf("--------------------------------\n");
}

/* description: 浏览全部图书
 *
 */
void browseBooks(const Library *library)
{
    if (library->count == 0)
    {
        printf("Library is empty.\n");
        return;
    }

    printf("Books in the library:\n");
    printf("--------------------------------\n");

    for (int i = 0; i < library->count; i++)
    {
        displayBook(&library->books[i]);
    }
}

/* description: 根据书名搜索图书
 *
 */
void searchByTitle(const Library *library, const char *title)
{
    int found = 0;

    for (int i = 0; i < library->count; i++)
    {
        if (strcmp(library->books[i].title, title) == 0)
        {
            displayBook(&library->books[i]);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Book not found.\n");
    }
}

/* description: 根据作者搜索图书
 *
 */
void searchByAuthor(const Library *library, const char *author)
{
    int found = 0;

    for (int i = 0; i < library->count; i++)
    {
        if (strcmp(library->books[i].author, author) == 0)
        {
            displayBook(&library->books[i]);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Book not found.\n");
    }
}

/* description: 按书名排序 a-z
 * 简单点用个冒泡
 */
void sortByTitle(Library *library)
{
    for (int i = 0; i < library->count - 1; i++)
    {
        for (int j = 0; j < library->count - i - 1; j++)
        {
            if (strcmp(library->books[j].title, library->books[j + 1].title) > 0)
            {
                Book temp = library->books[j];
                library->books[j] = library->books[j + 1];
                library->books[j + 1] = temp;
            }
        }
    }

    printf("Books sorted by title.\n");
}

/* description: 删除某本书
 *
 */
void deleteBook(Library *library, const char *loginNumber)
{
    int found = 0;

    for (int i = 0; i < library->count; i++)
    {
        if (strcmp(library->books[i].loginNumber, loginNumber) == 0)
        {
            for (int j = i; j < library->count - 1; j++)
            {
                library->books[j] = library->books[j + 1];
            }
            library->count--;
            printf("Book deleted successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Book not found.\n");
    }
}

/* description: 修改图书信息
 *
 */
void modifyBook(Library *library, const char *loginNumber)
{
    int found = 0;

    for (int i = 0; i < library->count; i++)
    {
        if (strcmp(library->books[i].loginNumber, loginNumber) == 0)
        {
            Book *book = &library->books[i];
            printf("Enter new title (or press Enter to keep current value): ");
            scanf(" %[^\n]", book->title);
            printf("Enter new author (or press Enter to keep current value): ");
            scanf(" %[^\n]", book->author);
            printf("Enter new category (or press Enter to keep current value): ");
            scanf(" %[^\n]", book->category);
            printf("Enter new publisher (or press Enter to keep current value): ");
            scanf(" %[^\n]", book->publisher);
            printf("Enter new publication date (or press Enter to keep current value): ");
            scanf(" %[^\n]", book->publicationDate);
            printf("Enter new price (or press Enter to keep current value): ");
            scanf("%f", &book->price);
            printf("Book modified successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Book not found.\n");
    }
}

/* description: 保存至文件
 *
 */
void saveToFile(const Library *library, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(library, sizeof(Library), 1, file);
    fclose(file);

    printf("Library data saved to file.\n");
}

/* description: 从文件中读取
 *
 */
void loadFromFile(Library *library, const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    fread(library, sizeof(Library), 1, file);
    fclose(file);

    printf("Library data loaded from file.\n");
}

int main()
{
    Library library;
    library.count = 0;

    int choice;
    char searchTitle[80];
    char searchAuthor[80];
    char deleteLoginNumber[16];
    char modifyLoginNumber[16];
    char filename[100];

    while (1)
    {
        printf("********* Library Management System *********\n");
        printf("1. Add Book\n");
        printf("2. Browse Books\n");
        printf("3. Search by Title\n");
        printf("4. Search by Author\n");
        printf("5. Sort by Title\n");
        printf("6. Delete Book\n");
        printf("7. Modify Book\n");
        printf("8. Save to File\n");
        printf("9. Load from File\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBook(&library);
            break;
        case 2:
            browseBooks(&library);
            break;
        case 3:
            printf("Enter title to search: ");
            scanf(" %[^\n]", searchTitle);
            searchByTitle(&library, searchTitle);
            break;
        case 4:
            printf("Enter author to search: ");
            scanf(" %[^\n]", searchAuthor);
            searchByAuthor(&library, searchAuthor);
            break;
        case 5:
            sortByTitle(&library);
            break;
        case 6:
            printf("Enter login number to delete: ");
            scanf("%s", deleteLoginNumber);
            deleteBook(&library, deleteLoginNumber);
            break;
        case 7:
            printf("Enter login number to modify: ");
            scanf("%s", modifyLoginNumber);
            modifyBook(&library, modifyLoginNumber);
            break;
        case 8:
            printf("Enter filename to save: ");
            scanf("%s", filename);
            saveToFile(&library, filename);
            break;
        case 9:
            printf("Enter filename to load: ");
            scanf("%s", filename);
            loadFromFile(&library, filename);
            break;
        case 0:
            printf("Exiting the program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }

        printf("\n");
    }

    return 0;
}
