/**
 * 
 * @name ITP
 * 
 * @brief Introduction to Programming Assignment
 * 
 * @author https://github.com/cyb3r-b4stard (Lomikovskiy Ivan).
 * 
 * @project Interactive Library Interface
 * 
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#if defined(WIN32) || defined(WIN64)
	#define clearConsole system("cls")
#else
	#define clearConsole system("clear")
#endif

// structure for books
struct booksList {
	struct booksList  *next;
	float              book_rate;
	char              *title;
	char              *author;
	int                year;
};

// function for creating a new book
struct booksList* newBook(char* title, char* author,
							int year, float book_rate) {

	struct booksList *book;                              // creating a pointer for our book
	book = (struct booksList *)malloc(sizeof(*book));     // allocating memory for our book and assigning it's address to pointer

	book -> book_rate = book_rate;
	book -> author    = strdup(author);
	book -> title     = strdup(title);
	book -> year      = year;
	book -> next      = NULL; // pointer to the next element in the list, by the definition of the linked list it is NULL

	return book; // returns pointer to a new book
}

// function for adding new book to a list from the front side
struct booksList* bookAdd(struct booksList *list_head, char *title,
								  char *author, int year, float book_rate) {

	struct booksList *book;
	book = newBook(title, author, year, book_rate); // creating a new book

	//checking if the book was created
	if (book) {
		book -> next = list_head; /* if it was, then our object should have a pointer to the initial
		                           first element of the list, which is now replaced by our new book */
		return book; // returns pointer to the new element of the list
	}

	return list_head; // if the book wasn't created, then we add nothing and return the list
}


// function for searching for a book in a list by it's title
struct booksList* bookSearch(struct booksList *list_head, char *_title) {

	struct booksList* current_book = list_head;
	// iterating through every book in a list
	while (current_book) {
		if(strcmp(current_book -> title, _title) == 0) return current_book;
		current_book = current_book -> next;
	}
	return NULL; // if we didn't find our book, then it is not represented in a list
}


// function for deleting book from list
struct booksList* bookDelete(struct booksList *list_head, char *_title) {

	struct booksList *current_book = list_head, *previous_book = NULL; // ptr - pointer to iterate through list, prev - pointer to the previous element

	// iterating through every book
	while (current_book) {
		if(strcmp(current_book-> title, _title) == 0) {     // Here we are checking if the title of the books coincides with the given one

			if (!previous_book) // if our element is the first one in the list
				list_head = current_book -> next;  // then the pointer to the first element should point to the next one
			else
				previous_book -> next = current_book -> next; // in other case, pointer from the previous element to this should point to the next element

			free(current_book); // freeing memory, allocated for the book we want to delete
			return list_head; // returns pointer to the first element
		}
		previous_book = current_book;
		current_book = current_book -> next;
	}
	return list_head;
}



// function for printing the whole list of books
void showBooks(struct booksList *list_head) {
	int number = 1; // variable for enumerating books
	struct booksList* current_book = list_head;
	clearConsole;
	printf("\t\t\tTHE LIST OF ALL BOOKS IN THE LIBRARY\n");

	//iterating through list and printing values of every book
	while (current_book) {
		printf("\nBook number %d:\nTitle: %s\nAuthor: %s\nYear: %d\nRating: %f\n\n\n", 
				number, 
				current_book -> title,
				current_book -> author,
				current_book -> year,
				current_book -> book_rate);
		++number;
		current_book = current_book -> next;
	}
}

// function for updating the book
struct booksList* bookUpdate(struct booksList *list_head, char *_title,
							   char *new_title, char *new_author, int new_year, float new_book_rate) {
	// iterating throught books in the list
	struct booksList *current_book = list_head;
	while (current_book) {
		if (strcmp(current_book -> title, _title) == 0) { // if the title of the current book coincides with the given one
			current_book -> book_rate = new_book_rate;
			current_book -> author    = new_author;              /* then we update this book's data*/
			current_book -> title     = new_title;
			current_book -> year      = new_year;

			return current_book;
		}
		current_book = current_book -> next;
	}
	return NULL; // returning NULL if we haven't found the book in the list
}

void booksClear(struct booksList *list_head) {
	struct booksList *ptr = NULL;
	while (list_head) {
		free(ptr);
		ptr = list_head;
		list_head = list_head -> next;
	}
	free(ptr);
}


// structure for customers
struct customersList {
	struct customersList  *next;
	float                  customer_rate;
	char                  *name;
	int                    age;
};


// function for creating a new customer
struct customersList* newCustomer(char *name, int age, float customer_rate) {

	struct customersList *customer;                               // creating a pointer for our customer
	customer = (struct customersList *)malloc(sizeof(*customer));      // allocating memory for our customer and assigning it's address to pointer

	customer -> customer_rate = customer_rate;
	customer -> name          = strdup(name);
	customer -> next          = NULL;    // by the definition of the linked list, the pointer to the next element is NULL
	customer -> age           = age;

	return customer; // returns pointer to a customer
}

// function for adding new customer to a list from the front side
struct customersList* customerAdd(struct customersList *list_head, char *name,
								          int age, float customer_rate) {

	struct customersList *customer;
	customer = newCustomer(name, age, customer_rate); // creating a new customer

	//checking if the customer was created
	if (customer) {
		customer -> next = list_head; // if it was, then our object should have a pointer to the initial first element of the list
		return customer; // returns new element of a list
	}

	return list_head; // if the customer wasn't created, then we add nothing
}


// function for searching for a customer in a list
struct customersList* customerSearch(struct customersList *list_head, char *_name) {

	struct customersList *current_customer = list_head;
	// iterating through every customer in a list
	while (current_customer) {
		if(strcmp(current_customer -> name, _name) == 0) return current_customer;
		current_customer = current_customer -> next; // Here we use pointer from the current customer to access the next one
	}
	return NULL; // if we didn't find our customer, then it is not represented in a list
}


// function for deleting customer from list
struct customersList* customerDelete(struct customersList *list_head, char *_name) {

	struct customersList *current_customer = list_head, *previous_customer = NULL; // ptr - pointer to iterate through list, prev - pointer to the previous element

	// iterating through the list
	while (current_customer) {
		if(strcmp(current_customer -> name, _name) == 0) {  // Here we are checking if the name of the customer coincides with the given one
			if (!previous_customer) {   // if our element is the first one in the list
				list_head = current_customer -> next; // then the pointer to the first element should point to the next one
			} else {
				previous_customer -> next = current_customer -> next; // in other case, pointer from the previous element to this should point to the next element
			}
			free(current_customer); // freeing memory, allocated for the customer

			return list_head; // returns pointer to the first customer
		}
		previous_customer = current_customer;
		current_customer = current_customer -> next;
	}
	return list_head;
}

// function for printing the whole list of customers
void showCustomers(struct customersList *list_head) {
	int number = 1; // variable for enumerating customer
	struct customersList *current_customer = list_head;
	clearConsole;
	printf("\t\t   THE LIST OF ALL CUSTOMERS IN THE LIBRARY\n");

	//iterating through list and printing values of every customer
	while (current_customer) {
		printf("\nCustomer number %d:\nName: %s\nAge: %d\nRating: %f\n",
				number,
				current_customer -> name,
				current_customer -> age,
				current_customer -> customer_rate);
		++number;
		current_customer = current_customer -> next;
	}
}

// function for updating the customer
struct customersList* customerUpdate(struct customersList *list_head, char *_name,
							           char *new_name, int new_age, float new_customer_rate) {

	struct customersList *current_customer = list_head;
	while (current_customer) {
		if (strcmp(current_customer -> name, _name) == 0) { // if the name of the current customer coincides with the given one
			current_customer -> customer_rate = new_customer_rate;
			current_customer -> name          = new_name;
			current_customer -> age           = new_age;                           /* then we update the data of this customer*/

			return current_customer; // we return pointer to the first element of the list
		}
		current_customer = current_customer -> next;
	}
	return NULL; // we return NULL, if we haven't found the customer that we want to update
}

void customersClear(struct customersList *list_head) {
	struct customersList *ptr = NULL;
	while (list_head) {
		free(ptr);
		ptr = list_head;
		list_head = list_head -> next;
	}
	free(ptr);
}


int main() {
	int   books = 0, 
		  customers = 0, 
		  active = 1, 
		  option,
		  year,
	      new_year,
		  age,
		  new_age;

	char  c,
		  title[60],
	      author[50],
		  new_title[60],
		  new_author[50],
		  name[50],
		  new_name[50];

	float book_rate,
		  new_book_rate,
		  customer_rate,
		  new_customer_rate;

	struct customersList* customer_head = NULL;    // customers linked list
	struct booksList*     book_head     = NULL;            // books linked list

	clearConsole;
	while (active) {
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

		clearConsole;
		switch (option) {
			case 1:
				if (books > 0) { // checking if we have books in the list
					showBooks(book_head);
				} else {
					printf("\nSorry, the library is empty\n");
				}
				break;
			case 2:
				printf("\n\t\t\t\tADDING THE BOOK\n");
				printf("\nPlease, enter the title of the book: ");
				gets(title);
				printf("\nPlease, enter the author of the book: ");
				gets(author);
				printf("\nPlease, enter the year of the book: ");
				scanf("%d", &year);
				printf("\nPlease, enter the rate of the book: ");
				scanf("%f", &book_rate);

				book_head = bookAdd(book_head, title, author, year, book_rate); // adding book to the list

				if (bookSearch(book_head, title)) { // checking is the new book is in the list now
					printf("\nThe book was succesfully added to the list\n");
					++books; // + 1 book in the library
				} else {
					printf("\nAn error occured, the book wasn't added\n");
				}
				break;
			case 3:
				printf("\t\t\t\tUPDATING THE BOOK\n");

				printf("\nPlease, enter the title of the book: ");
				gets(title);

				if (bookSearch(book_head, title)) { // checking if the book is in the list
					clearConsole;

					printf("\t\t\tUPDATING THE BOOK\n");

					printf("\nPlease, enter the new title of the book: ");
					gets(new_title);
					printf("\nPlease, enter the new author of the book: ");
					gets(new_author);
					printf("\nPlease, enter the new year of the book: ");
					scanf("%d", &new_year);
					printf("\nPlease, enter the new rate of the book: ");
					scanf("%f", &new_book_rate);

					bookUpdate(book_head, title, new_title, new_author, new_year, new_book_rate); // updating the book in the list

					printf("\nThe book was succesfully updated\n");
				} else {
					printf("\nThe book is not in the list\n");
				}
				break;
			case 4:
			    printf("\t\t\t\tDELETING THE BOOK\n");

				printf("\nPlease, enter the title of the book: ");
				gets(title);

				if (bookSearch(book_head, title)) {

					book_head = bookDelete(book_head, title); // deleting the book

					if (!bookSearch(book_head, title)) { // checking if the book is not in the list
						printf("\nThe book was succesfully deleted\n");
						--books; // - 1 book in the library
					} else {
						printf("\nAn error occured, the book wasn't deleted\n");
					}
				} else {
					printf("\nThe book is not in the library.\n");
				}

				break;
			case 5:
				if (customers > 0) { // checking if there are customers in the library
					showCustomers(customer_head);
				} else {
					printf("\nSorry, we don't have customers for now\n");
				}
				break;
			case 6:
				printf("\t\t\t\tADDING THE CUSTOMER\n");

				printf("\nPlease, enter the name of the customer: ");
				gets(name);
				printf("\nPlease, enter the age of the customer: ");
				scanf("%d", &age);
				printf("\nPlease, enter the rate of the customer: ");
				scanf("%f", &customer_rate);

				customer_head = customerAdd(customer_head, name, age, customer_rate);
				if (customerSearch(customer_head, name)) {
					printf("\nThe customer was succesfully added to the list\n");
					++customers; // + 1 customer in the library
				} else {
					printf("\nThe error occured, the customer wasn't added\n");
				}
				break;
			case 7:
				printf("\t\t\t  UPDATING THE CUSTOMER\n");

				printf("\nPlease, enter the name of the customer: ");
				gets(name);

				if (customerSearch(customer_head, name)) { // checking if the customer is in the list
					clearConsole;

					printf("\t\t\t  UPDATING THE CUSTOMER\n");

					printf("\nPlease, enter the new name of the customer: ");
					gets(new_name);
					printf("\nPlease, enter the new age of the customer: ");
					scanf("%d", &new_age);
					printf("\nPlease, enter the new rate of the customer: ");
					scanf("%f", &new_customer_rate);

					customerUpdate(customer_head, name, new_name, new_age, new_customer_rate); // updating the customer

					printf("\nThe customer was succesfully updated\n");
				} else {
					printf("\nThe customer is not in the list\n");
				}
				break;
			case 8:
				printf("\t\t\t  DELETING THE CUSTOMER\n");

				printf("\nPlease, enter the name of the customer: ");
				gets(name);

				if (customerSearch(customer_head, name)) {

					customer_head = customerDelete(customer_head, name); // deleting the customer

					if (!customerSearch(customer_head, name)) { // checking if the customer is not in the list
						printf("\nThe customer was succesfully deleted\n");
						--customers; // - 1 customer in the list
					} else {
						printf("\nThe error occured, the customer wasn't deleted\n");
					}
				} else {
					printf("\nThe customer is not in the library\n");
				}

				break;
			case 9:
				printf("\nGoodbye. Have a nice day\n");
				active = 0;
				break;
			default:
				printf("\t\t\tInvalid input, please use numbers from 1 to 9!\n");
		}
	}
	booksClear(book_head);
	customersClear(customer_head);
	return 0;
}
