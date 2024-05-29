#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item{
	int quantity;
	float unit_price;
};

int main(){

	struct item paratha;
	printf("Quantity of Paratha: ");
	scanf("%d",&paratha.quantity);
	printf("Unit Price: ");
	scanf("%f",&paratha.unit_price);
	
	struct item vegetable;
	printf("Quantity of Vegetables: ");
	scanf("%d",&vegetable.quantity);
	printf("Unit Price: ");
	scanf("%f",&vegetable.unit_price);

	struct item mineralwater;
	printf("Quantity of Mineral Water: ");
	scanf("%d",&mineralwater.quantity);
	printf("Unit Price: ");
	scanf("%f",&mineralwater.unit_price);
	
	int people;
	printf("Number of People: ");
	scanf("%d",&people);
	
	float total;
	
	total = ((paratha.quantity*paratha.unit_price)+(vegetable.quantity*vegetable.unit_price)+(mineralwater.quantity*mineralwater.unit_price));
	
	float individual_cost = total / people;
	
	printf("Individual people will pay: %.2f tk\n",individual_cost);

	return 0;
}

