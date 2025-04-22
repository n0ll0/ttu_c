# Kodutöö 2
Topic:

	Price watch
		The first file contains smartphones with their technical specifications. 
		The second file contains price quotes from different retailers.
		One phone can be sold by multiple retailers at different prices.
		A retailer might not sell every product in the products file.

- File structure: 
	- Products 
		- Product code (PK) 
		- Name (mark + model) 
		- RAM (MB) 
		- Screen size (inches) 
		- Operating system 
	- Quotes:
		- Quote ID (PK) 
		- Product code (FK) 
		- Retailer 
		- Price 
		- Availability (in stock / order)

Variant: 03-04

Required menu options:
- Display all the data from files.

	Group quotes together by the products. Only display the product once, followed by quotes associated with it.

- edit

	Allow the user to edit the product screen size and quote availability by selecting either the respective product code or quote id. Check that the input matches the required format. Write the changes to the file.

- Search phones

	Search phones based on 2 parameters, which are selected by the user. Only show phones that are in stock for at least one retailer. Display full phone specifications.
