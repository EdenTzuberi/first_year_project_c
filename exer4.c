#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define ROWS 2
#define COLS 6
#define SIZE1 6
#define SIZE2 7

typedef struct
{
	char name[11];
	float unit_price;
}Product;

typedef struct
{
	int day;
	int month;
	int year;
}Date_of_purchase;

typedef struct
{
	int purchase_num; 
	Date_of_purchase date;
	char product_name[11];
	int product_amount;
}Purchase;

void ReadOneProduct(Product *p)
{
	printf("insert product name\n");
	gets(p->name);
	printf("insert pruduct price\n");
	scanf_s("%d", &p->unit_price);
	getchar();
}

void ReadOnePurchase(Purchase *b)
{
	printf("insert num of purchase\n");
	scanf_s("%d", &b->purchase_num);
	printf("insert date of purchase\n");
	printf("insert day\n");
	scanf_s("%d", &b->date.day);
	printf("insert month\n");
	scanf_s("%d", &b->date.month);
	printf("insert year\n");
	scanf_s("%d", &b->date.year);
	printf("insert name product\n");
	gets(b->product_name);
	printf("insert product amount\n");
	scanf_s("%d", &b->product_amount);

}

void ReadProducts(Product arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		ReadOneProduct(&arr[i]); 
	}
}

void ReadPurchase(Product arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		ReadOnePurchase(&arr[i]);
	}
}

float CalculateBuying(Product product[], int np, Purchase purchase[], int nb, int num_of_purchase)
{
	int i, j, flag, sum = 0;
	for (i = 0; i < nb; i++)
	{
		if (num_of_purchase == purchase[i].purchase_num)
		{
			for (j = 0, flag = 0 ;j < np && flag == 0 ; j++)
			{
				if (purchase[i].product_name == product[j].name)
				{
					sum = purchase[i].product_amount * product[j].unit_price;
					flag = 1;
				}
			}
		}
	}

	return sum;
}

void PrintCost(int num_of_purchase, int sum)
{
	printf("the cost for purchase number %d is %d", num_of_purchase, sum);
}

int CountLetters(char* string1, int* index_max)
{
	int i, counter = 0, max = 0;

	for (i = 0; *(string1 + i) != '\0'; i++)
	{
		if (*(string1 + i) != ' ' && *(string1 + i) != '.' && *(string1 + i) != ':' && *(string1 + i) != '!' && *(string1 + i) != '?' && *(string1 + i) != ',')
		{
			counter++;
			if (max < counter)
			{
				max = counter;
				*index_max = i;
			}
		}
		else
			counter = 0;
	}

	*index_max = (*index_max) - max + 1;

	return max;
}

char* CopyWord(char* string1, int length, int counter, int* index_max)
{
	int i, j;
	char* string2 = NULL;

	string2 = (char*)malloc(counter + 1);

	for (i = *index_max, j = 0; *(string1 + i) != ' ' && *(string1 + i) != '.' && *(string1 + i) != '!' && *(string1 + i) != '?'; i++)
	{
		*(string2 + j) = *(string1 + i);
		j++;
	}

	*(string2 + j) = '\0';

	return string2;
}


char* DeleteWord(char* string1, int length, int deleted_word)
{
	int i, j=0, count_spaces = 0, count_letters = 0, index=0, flag = 0;
	char *string3 = NULL;

	for (i = 0;  *(string1+i)!='\0' && flag==0; i++)
	{
		
		if (*(string1 + i) != ' ' && *(string1 + i) != '.' && *(string1 + i) != ':' && *(string1 + i) != '!' && *(string1 + i) != '?' && *(string1 + i) != ',')
		{
			count_letters++;
		}

		if (*(string1 + i) == ' ' || *(string1 + i) == '.' || *(string1 + i) == '!' || *(string1 + i) == '?')
		{
			count_spaces++;
			if (*(string1 + i) == ' ' && *(string1 + i - 1) == '.' || *(string1 + i - 1) == '!' || *(string1 + i - 1) == '?')
			{
				count_spaces--;
			}
			if (count_spaces == deleted_word)
			{
				index = i;
				if (*(string1 + i - 1) == '!' || *(string1 + i - 1) == '?' || *(string1 + i - 1) == ':' || *(string1 + i - 1) == '.' || *(string1 + i - 1) == ',')
				{
					index = i - 2;
					flag = 1;
				}
				else
					flag = 1;
			}
			else
			{
				count_letters = 0;
			}
		}
	}
	
	j = strlen(string1) - count_letters;
	string3 = (char*)malloc(j+1);
	for (i = 0, j = 0; i < index-count_letters; i++)
	{
		*(string3 + j) = *(string1 + i);
		j++;
	}
	for (i; i <= index; i++);
	for (i = index + 1; *(string1 + i) != '\0'; i++)
	{
			*(string3 + j) = *(string1 + i);
		j++;
	}

	*(string3 + j) = '\0';

	return string3;
}

void ReadMat(float mat[][COLS], int n)
{
	int i, j;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("fill mat[%d][%d]\n", i, j);
			scanf_s("%f", &mat[i][j]);
		}
	}
}

void PrintArr(float* arr, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%f\t", *(arr + i));
	}
	putchar('\n');
}

float* CreateSides(float mat[][COLS], int n, float *x_max, float *y_max)
{
	int i, j, k;
	float x1, x2, y1, y2, x, y, d, sum;
	float* sideslength = NULL;

	sideslength = (float*)malloc(n * sizeof(float));


	for (k = 0, i = 0, j = 0; j < n; j++)
	{

		x1 = mat[i][j];
		*x_max = x1;
		y1 = mat[i + 1][j];
		*y_max = y1;
		if (j == n - 1)
		{
			x2 = mat[0][0];
			y2 = mat[1][0];
			if (x2 > *x_max)
			{
				*x_max = x2;
				*y_max = y2;
			}
		}
		else
		{
			x2 = mat[i][j + 1];
			y2 = mat[i + 1][j + 1];
			if (x2 > *x_max)
			{
				*x_max = x2;
				*y_max = y2;
			}
		}
		x = x2 - x1;
		y = y2 - y1;
		x = x * x;
		y = y * y;
		sum = x + y;
		d = sqrt(sum);
		*(sideslength + k) = d;
		k++;
	}

	return sideslength;
}

float CalculatePerimeter(float* arr, int n)
{
	int i;
	float perimeter = 0;

	for (i = 0; i < n; i++)
	{
		perimeter = perimeter + *(arr + i);
	}

	return perimeter;
}

float ForeignCurrencyExchange(float shekels, float euro_rate, float dollar_rate, float pound_rate, float* euro_amount, float* dollar_amount, float* pound_amount)
{
	*euro_amount = shekels / euro_rate;
	*dollar_amount = shekels / dollar_rate;
	*pound_amount = shekels / pound_rate;

	return shekels;
}

void main()
{
	int length, counter, index_max, choice, deleted_word, n, num_of_purchase;
	float shekels, euro_rate, dollar_rate, pound_rate, euro_amount, dollar_amount, pound_amount, mat[ROWS][COLS], perimeter = 0, x_max, y_max, sum=0;
	char* string1, *string2, *string3;
	float* sideslength;
	Purchase purchase;
	Product product;

	do
	{
		printf("1.print the longest word in string and delete word by it's serial number.\n");
		printf("2.Calculate perimeter of a geometric shape (Between a triangle and a hexagon).\n");
		printf("3.Calculate foreign currency.\n");
		scanf_s("%d", &choice);
		switch (choice)
		{
		default:
			printf("bad choice\n");
			break;

		case 1:
			printf("insert an amount of letters\n");
			scanf_s("%d", &length);
			string1 = (char*)malloc(length + 1);
			printf("insert a sentence\n");
			getchar();
			gets(string1);
			counter = CountLetters(string1, &index_max); //returns max number of letters
			string2 = CopyWord(string1, length, counter, &index_max);
			printf("the longest word is '%s'\n", string2);
			printf("insert serial number of word to delete it.\n");
			scanf_s("%d", &deleted_word);
			string3 = DeleteWord(string1, length, deleted_word);
			printf("%s\n", string3);
			free(string1);
			free(string2);
			free(string3);
			break;

		case 2:
			printf("insert amount of vertex.\n");
			scanf_s("%d", &n);
			printf("insert coordinates of the geometric shape into a matrix (X first, Y after in the same order.\n");
			ReadMat(mat, n);
			sideslength = CreateSides(mat, n, &x_max, &y_max);
			PrintArr(sideslength, n);
			perimeter = CalculatePerimeter(sideslength, n);
			printf("the perimeter is %f\n", perimeter);
			printf("X max is %f and it's coordinate is %f\n", x_max, y_max);
			break;

		case 3:
			printf("insert amount in shekels\n");
			scanf_s("%f", &shekels);
			printf("insert rate in dollars\n");
			scanf_s("%f", &dollar_rate);
			printf("insert rate in euro\n");
			scanf_s("%f", &euro_rate);
			printf("insert rate in pound\n");
			scanf_s("%f", &pound_rate);
			ForeignCurrencyExchange(shekels, euro_rate, dollar_rate, pound_rate, &euro_amount, &dollar_amount, &pound_amount);
			printf("%f of shekles is:\n", shekels);
			printf("%f in dollars.\n", dollar_amount);
			printf("%f in euro.\n", euro_amount);
			printf("%f in pound.\n", pound_amount);
			break;

		case 4:
			printf("insert details of all products\n");
			ReadProducts(&product, SIZE1);
			ReadPurchase(&purchase, SIZE2);
			printf("insert num of purchase\n");
			scanf_s("%d", &num_of_purchase);
			sum = CalculateBuying(&product, SIZE1, &purchase, SIZE2, num_of_purchase);
			PrintCost(num_of_purchase, sum);
			break;
		
		}
	} while (choice=!4);


}


 


