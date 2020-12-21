/*The Introduction to programming assignment*/
       /*Made by Ivan Lomikovskiy*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int condition = 1;

// structure for books
struct books_list {
	char *title;
	char *author;
	int year;
	float book_rate;
	struct books_list *next;
};

// function for creating a new book
struct books_list *new_book(char *title, char *author, 
							int year, float book_rate) {

	struct books_list *ptr;                              // creating a pointer for our book
	ptr = (struct books_list *)malloc(sizeof(*ptr));     // allocating memory for our book and assigning it's address to pointer

	ptr -> title = strdup(title);
	ptr -> author = strdup(author);
	ptr -> year = year;   
	ptr -> book_rate = book_rate;
	ptr -> next = NULL; // pointer to the next element in the list, by the definition of the linked list it is NULL

	return ptr; // returns pointer to a new book
}

// function for adding new book to a list from the front side
struct books_list *book_add_front(struct books_list *books_list, char *title, 
								  char *author, int year, float book_rate) {

	struct books_list *book;
	book = new_book(title, author, year, book_rate); // creating a new book

	//checking if the book was created
	if (book != NULL) {
		book -> next = books_list; /* if it was, then our object should have a pointer to the initial
		                           first element of the list, which is now replaced by our new book */

		return book; // returns pointer to the new element of the list
	}

	return books_list; // if the book wasn't created, then we add nothing and return the list
}


// function for searching for a book in a list by it's title
struct books_list *book_search(struct books_list *books_list, char *title) {

	// iterating through every book in a list
	for (books_list; books_list != NULL; books_list = books_list -> next) {
		if(strcmp(books_list -> title, title) == 0) {  // Here we are checking if the title of the books coincides with the given one

			return books_list; // if our condition is satisfied, we return a pointer to the first element in the list
		}
	}
	return NULL; // if we didn't find our book, then it is not represented in a list
}


// function for deleting book from list
struct books_list *book_delete(struct books_list *books_list, char *title) {

	struct books_list *ptr, *prev = NULL; // ptr - pointer to iterate through list, prev - pointer to the previous element

	// iterating through every book
	for (ptr = books_list; ptr != NULL; ptr = ptr -> next) {
		if(strcmp(ptr -> title, title) == 0) {     // Here we are checking if the title of the books coincides with the given one
			if (prev == NULL) { // if our element is the first one in the list
			books_list = ptr -> next;  // then the pointer to the first element should point to the next one
			} 
			else {
				prev -> next = ptr -> next; // in other case, pointer from the previous element to this should point to the next element
			}
			free(ptr); // freeing memory, allocated for the book we want to delete
			return books_list; // returns pointer to the first element
		}
		prev = ptr;
	}
	return books_list;
}



// function for printing the whole list of books
struct books_list *show_books(struct books_list *books_list) {
	int cnt = 1; // variable for enumerating books

	system("cls"); // clear console on Windows
	//clrscr();  clear console on Linux
	printf("\t\t\tTHE LIST OF ALL BOOKS IN THE LIBRARY\n");

	//iterating through list and printing values of every book
	for (books_list; books_list != NULL; books_list = books_list -> next) {
		printf("\nBook number %d:\n", cnt);
		printf("Title: %s\n", books_list -> title);
		printf("Author: %s\n", books_list -> author);
		printf("Year: %d\n", books_list -> year);
		printf("Rating: %f\n", books_list -> book_rate);
		printf("\n\n");
		cnt++;
	}
	return NULL;
}

// function for updating the book
struct books_list *book_update(struct books_list *books_list, char *book_title, 
							   char *new_title, char *new_author, int new_year, float new_book_rate) {
	// iterating throught books in the list
	for (books_list; books_list != NULL; books_list = books_list -> next) {
		if (strcmp(books_list -> title, book_title) == 0) { // if the title of the current book coincides with the given one
			books_list -> title = new_title;                
			books_list -> author = new_author;              /* then we update this book's data*/
			books_list -> year = new_year;
			books_list -> book_rate = new_book_rate;

			return books_list; // returning pointer to the first element in the list
		}
	}
	return NULL; // returning NULL if we haven't found the book in the list
}

// structure for customers
struct customers_list {
	char *name;
	int age;
	float customer_rate;
	struct customers_list *next;
};


// function for creating a new customer
struct customers_list *new_customer(char *name, int age, float customer_rate) {

	struct customers_list *ptr;                               // creating a pointer for our customer
	ptr = (struct customers_list *)malloc(sizeof(*ptr));      // allocating memory for our customer and assigning it's address to pointer

	ptr -> name = strdup(name);
	ptr -> age = age;   
	ptr -> customer_rate = customer_rate;
	ptr -> next = NULL;    // by the definition of the linked list, the pointer to the next element is NULL

	return ptr; // returns pointer to a customer
}

// function for adding new customer to a list from the front side
struct customers_list *customer_add_front(struct customers_list *customers_list, char *name, 
								          int age, float customer_rate) {

	struct customers_list *customer;
	customer = new_customer(name, age, customer_rate); // creating a new customer

	//checking if the customer was created
	if (customer != NULL) {
		customer -> next = customers_list; // if it was, then our object should have a pointer to the initial first element of the list

		return customer; // returns new element of a list
	}

	return customers_list; // if the customer wasn't created, then we add nothing
}


// function for searching for a customer in a list
struct customers_list *customer_search(struct customers_list *customers_list, char *name) {

	// iterating through every customer in a list
	while (customers_list != NULL) {
		if(strcmp(customers_list -> name, name) == 0) {  // Here we are checking if the name of the customer coincides with the given one

			return customers_list; // if all of our conditions are satisfied, we return a pointer to the first element in the list
		}
		customers_list = customers_list -> next; // Here we use pointer from the current customer to access the next one
	}
	return NULL; // if we didn't find our customer, then it is not represented in a list
}


// function for deleting customer from list
struct customers_list *customer_delete(struct customers_list *customers_list, char *name) {

	struct customers_list *ptr, *prev = NULL; // ptr - pointer to iterate through list, prev - pointer to the previous element

	// iterating through the list
	for (ptr = customers_list; ptr != NULL; ptr = ptr -> next) {
		if(strcmp(ptr -> name, name) == 0) {  // Here we are checking if the name of the customer coincides with the given one
			if (prev == NULL) {   // if our element is the first one in the list
				customers_list = ptr -> next; // then the pointer to the first element should point to the next one
			} else {
				prev -> next = ptr -> next; // in other case, pointer from the previous element to this should point to the next element
			}
			free(ptr); // freeing memory, allocated for the customer

			return customers_list; // returns pointer to the first customer
		}
		prev = ptr;
	}
	return customers_list; 
}

// function for printing the whole list of customers
struct customers_list *show_customers(struct customers_list *customers_list) {
	int cnt = 1; // variable for enumerating customer

	system("cls"); // clear console on Windows
	//clrscr();  clear console on Linux
	printf("\t\t   THE LIST OF ALL CUSTOMERS IN THE LIBRARY\n");

	//iterating through list and printing values of every customer
	for (customers_list; customers_list != NULL; customers_list = customers_list -> next) {
		printf("\nCustomer number %d:\n", cnt);
		printf("Name: %s\n", customers_list -> name);
		printf("Age: %d\n", customers_list -> age);
		printf("Rating: %f\n", customers_list -> customer_rate);
		printf("\n\n");
		cnt++;
	}
	return NULL;
}

// function for updating the customer
struct customers_list *customer_update(struct customers_list *customers_list, char *name, 
							           char *new_name, int new_age, float new_customer_rate) {

	for (customers_list; customers_list != NULL; customers_list = customers_list -> next) {
		if (strcmp(customers_list -> name, name) == 0) { // if the name of the current customer coincides with the given one
			customers_list -> name = new_name;		
			customers_list -> age = new_age;                           /* then we update the data of this customer*/
			customers_list -> customer_rate = new_customer_rate;

			return customers_list; // we return pointer to the first element of the list
		}
	}
	return NULL; // we return NULL, if we haven't found the customer that we want to update
}



int main() {
	auto int option; // variable for choosing the task
	int c;
	static int books = 0, customers = 0; // variables for counting number of books/customers in the list

	char title[60];
	char author[50];
	int year;
	float book_rate;

	char new_title[60];
	char new_author[50];
	int new_year;
	float new_book_rate;

	char name[50];
	int age;
	float customer_rate;

	char new_name[50];
	int new_age;
	float new_customer_rate;

	struct books_list *book_head;            // books linked list
	struct customers_list *customer_head;    // customers linked list

	system("cls"); // clear console on Windows
	//clrscr();  clear console on Linux

	while (condition) {
		printf("\n\t\t    INTERACTIVE LIBRARY CONSOLE APPLICATION\n");
		printf("\n1: Show Books\n"
				"2: Add Book\n"
				"3: Update Book\n"
				"4: Remove Book\n"
				"5: Show Customers\n"
				"6: Add Customer\n"
				"7: Update Customer\n"
				"8: Remove Customer\n"
				"9: Quit\n");

		printf("\nChoose your option: ");
		scanf("%d", &option);

		c = getchar(); // trick, that I have in order to use gets() func properly, without this line it doesn't work

		switch (option) {
			case 1:
				if (books > 0) { // checking if we have books in the list
					show_books(book_head);
				} else {
					printf("\nSorry, the library is empty\n");
				}
				break;
			case 2:
				system("cls"); // clear console on Windows
				//clrscr();  clear console on Linux

				printf("\n\t\t\t\tADDING THE BOOK\n");
				printf("\n%s", "Please, enter the title of the book: ");
				gets(title);
				printf("\n%s", "Please, enter the author of the book: ");
				gets(author);
				printf("\n%s", "Please, enter the year of the book: ");
				scanf("%d", &year);
				printf("\n%s", "Please, enter the rate of the book: ");
				scanf("%f", &book_rate);

				//c = getchar(); // trick, that I used in order to use gets() func properly, without this line it doesn't work

				if (books == 0) { // checking if we have books in the library
					book_head = book_add_front(NULL, title, author, year, book_rate); // adding book to the list

					if (book_search(book_head, title)) { // checking if the new book is in the list now
						printf("\nThe book was succesfully added to the list\n", book_head->title);
						books++; // + 1 book in the library
					} else {
						printf("\nAn error occured, the book wasn't added\n");
					}
				} else {
					book_head = book_add_front(book_head, title, author, year, book_rate); // adding book to the list

					if (book_search(book_head, title)) { // checking is the new book is in the list now
						printf("\nThe book was succesfully added to the list\n");
						books++; // + 1 book in the library
					} else {
						printf("\nAn error occured, the book wasn't added\n");
					}
				}
				break;
			case 3:
				system("cls"); // clear console on Windows
				//clrscr();  clear console on Linux

				printf("\t\t\t\tUPDATING THE BOOK\n");

				printf("\nPlease, enter the title of the book: ");
				gets(title);

				if (book_search(book_head, title)) { // checking if the book is in the list
					system("cls"); // clear console on Windows
				    //clrscr();  clear console on Linux

					printf("\t\t\tUPDATING THE BOOK\n");

					printf("\n%s", "Please, enter the new title of the book: ");
					gets(new_title);
					printf("\n%s", "Please, enter the new author of the book: ");
					gets(new_author);
					printf("\n%s", "Please, enter the new year of the book: ");
					scanf("%d", &new_year);
					printf("\n%s", "Please, enter the new rate of the book: ");
					scanf("%f", &new_book_rate);

					book_update(book_head, title, new_title, new_author, new_year, new_book_rate); // updating the book in the list

					printf("\nThe book was succesfully updated\n");
				} else {
					printf("\nThe book is not in the list\n");
				}
				break;
			case 4:
			    system("cls"); // clear console on Windows
				//clrscr();  clear console on Linux

			    printf("\t\t\t\tDELETING THE BOOK\n");

				printf("\nPlease, enter the title of the book: ");
				gets(title);

				if (book_search(book_head, title)) {

					book_head = book_delete(book_head, title); // deleting the book

					if (books > 0 && !book_search(book_head, title)) { // checking if the book is not in the list
						printf("\nThe book was succesfully deleted\n");
						books--; // - 1 book in the library
					} else {
						printf("\nThe error occured, the book wasn't deleted\n");
					}
				} else {
					printf("\nThe book is not in the library.\n");
				}

				break;
			case 5:
				if (customers > 0) { // checking if there are customers in the library
					show_customers(customer_head);
				} else {
					printf("\nSorry, we don't have customers for now\n");
				}
				break;
			case 6:
				system("cls"); // clear console on Windows
				//clrscr();  clear console on Linux

				printf("\t\t\t\tADDING THE CUSTOMER\n");

				printf("\n%s", "Please, enter the name of the customer: ");
				gets(name);
				printf("\n%s", "Please, enter the age of the customer: ");
				scanf("%d", &age);
				printf("\n%s", "Please, enter the rate of the customer: ");
				scanf("%f", &customer_rate);


				if (customers == 0) { // checking if we have customers in the library

					customer_head = customer_add_front(NULL, name, age, customer_rate); // adding the customer

					if (customer_search(customer_head, name)) { // checking if the new customer is in the list now
						printf("\nThe customer was succesfully added to the list\n", customer_head->name);
						customers++; // + 1 customer in the library
					} else {
						printf("\nThe error occured, the customer wasn't added\n");
					}
				} else {
					customer_head = customer_add_front(customer_head, name, age, customer_rate); // adding the customer

					if (customer_search(customer_head, name)) {
						printf("\nThe customer was succesfully added to the list\n");
						customers++; // + 1 customer in the library
					} else {
						printf("\nThe error occured, the customer wasn't added\n");
					}
				}
				break;
			case 7:
				system("cls"); // clear console on Windows
			    //clrscr();  clear console on Linux

				printf("\t\t\t  UPDATING THE CUSTOMER\n");

				printf("\n%s", "Please, enter the name of the customer: ");
				gets(name);

				if (customer_search(customer_head, name)) { // checking if the customer is in the list
					system("cls"); // clear console on Windows
				    //clrscr();  clear console on Linux

					printf("\t\t\t  UPDATING THE CUSTOMER\n");

					printf("\n%s", "Please, enter the new name of the customer: ");
					gets(new_name);
					printf("\n%s", "Please, enter the new age of the customer: ");
					scanf("%d", &new_age);
					printf("\n%s", "Please, enter the new rate of the customer: ");
					scanf("%f", &new_customer_rate);

					customer_update(customer_head, name, new_name, new_age, new_customer_rate); // updating the customer

					printf("\nThe customer was succesfully updated\n");
				} else {
					printf("\nThe customer is not in the list\n");
				}
				break;
			case 8:
				system("cls"); // clear console on Windows
				//clrscr();  clear console on Linux

				printf("\t\t\t  DELETING THE CUSTOMER\n");

				printf("\n%s", "Please, enter the name of the customer: ");
				gets(name);

				if (customer_search(customer_head, name)) {

					customer_head = customer_delete(customer_head, name); // deleting the customer

					if (!customer_search(customer_head, name)) { // checking if the customer is not in the list
						printf("\nThe customer was succesfully deleted\n");
						customers--; // - 1 customer in the list
					} else {
						printf("\nThe error occured, the customer wasn't deleted\n");
					}
				} else {
					printf("\nThe customer is not in the library\n");
				}

				break;
			case 9:
				printf("\n%s", "Goodbye. Have a nice day\n");
				condition = 0;
				break;
			default:
				system("cls");
				//clrscr();  clear console on Linux
				printf("\t\t\tInvalid input, please use numbers from 1 to 9!\n");
		}
	}
	return 0;
}