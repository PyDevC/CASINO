#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define Re_mon(x) scanf("%u", &x)
#define read(x) scanf("%d", &x)

struct user
{
	char username[50];
	unsigned long int accountnum;
	char password[40];
	unsigned long long int balance;
}; //structure user

int spin_roulette(void);
int roulette(unsigned long long int balance);
int Randoms(int low, int high);
int bet(unsigned long long int balance);
int guessTheCard();

int main()
{
	FILE *ptr;
	int open = 1, option, opt, op;
	char save;
	char date[12];
	struct user cust;
	struct user temp;
	char name[50];
	int verify = 0;
	printf("<<<<<<<<<*************** WELCOME  TO  CASINO ***************>>>>>>>>\n\n\n");
	while (open == 1)
	{
	mainmenu:
		printf("\nmain_menu\n\n");
		printf("1. New account\n2. Continue with existing account\n3. Exit\n");
		printf("\nSelect one of the above options.\n");
		read(option);
		fgetc(stdin);
		switch (option)
		{
		case 1:
		user_info:
			system("clear");
			printf("\nEnter the user name:\t");
			fgets(cust.username, 50, stdin);
			cust.username[strlen(cust.username) - 1] = 0;
			strcpy(date, __DATE__); //takes date from the system
			printf("\nWrite an account number:\t");
			scanf("%lu", &cust.accountnum);
			getch();
			printf("\nEnter a secured password of maximum length 40:\t");
			fgets(cust.password, 40, stdin);
			cust.password[strlen(cust.password) - 1] = 0;
			printf("\nAs a new user you are given 1000 itins");
			cust.balance = 1000;

			printf("\nDo you want to save this information[y/n]");
			scanf("%c", &save);
			if (save == 'n')
			{
				goto user_info;
			}
			else if (save == 'y')
			{
			save:
				ptr = fopen("accounts.dat", "a+");
				fwrite(&cust, sizeof(struct user), 1, ptr);
				if (fwrite != 0)
					printf("\nSuccessfully saved");
				else
					printf("\nError saving");
				fclose(ptr);
				goto play;
			}
			break;
		case 2:
			system("clear");
			ptr = fopen("accounts.dat", "r");
			if (ptr == NULL)
			{
				printf("No accounts created");
				goto mainmenu;
			}
			printf("Enter your user name:\t");
			fgets(cust.username, 50, stdin);
			cust.username[strlen(cust.username) - 1] = 0;
			printf("\nEnter your account number\t");
			scanf("%lu", &cust.accountnum);
			getch();
			printf("\nEnter your password:\t");
			fgets(cust.password, 40, stdin);
			cust.password[strlen(cust.password) - 1] = 0;
			printf("verifying.....\n");
			while (fread(&temp, sizeof(struct user), 1, ptr))
			{
				if (!strcmp(cust.username, temp.username))
				{
					if (cust.accountnum == temp.accountnum)
					{
						if (!strcmp(cust.password, temp.password))
						{
							verify = 1;
						}
						else
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			fclose(ptr);
			if (!verify)
			{
				printf("account does not exist");
				goto mainmenu;
			}
			else
			{
				printf("Verified");
				cust.balance = temp.balance;
			}
			cust.balance = temp.balance;
			getch();
		play:
			system("clear");
			printf("please select the option.\n");
			printf("1. Play\n2. Withdraw money\n3. Exit\n");
			read(opt);
			fgetc(stdin);
			if (opt == 1)
			{
				system("clear");
				printf("what will you like to play\n\n\n");
				printf("1. Guess The Card\n2. roulette Spin\n");
				read(op);
				fgetc(stdin);
				if (op == 1)
				{
					system("clear");
					printf("GUESS THE CARD %c\n\n", 6);
					char typ[4] = {3, 4, 5, 6};
					int cardNum, type;
					int mon = bet(cust.balance);
					printf("Enter the number and type of card\n\n");
					printf("1. %c\n2. %c\n3. %c\n4. %c\n\n", typ[0], typ[1], typ[2], typ[3]);
					printf("Enter type of card: ");
					scanf("%d", &type);
					getch();
					printf("\n1. Ace\n2. 2\n3. 3\n4. 4\n5. 5\n6. 6\n7. 7\n8. 8\n9. 9\n10. Jack\n11. Queen\n12. King\n13. JOCKER\n");
					printf("Enter Card Number: ");
					scanf("%d", &cardNum);
					getch();
					int ran_card = Randoms(1, 4);
					int ran_num = Randoms(1, 13);
					if (type == ran_card && cardNum == ran_num)
					{
						printf("YOU WON!!!\nYou guessed it correct\n");
						cust.balance += mon;
					}
					else
					{
						printf("SORRY YOU LOST\n");
						cust.balance += mon;
					}
					getch();
					goto save;
				}
				else if (op == 2)
				{
					cust.balance = roulette(cust.balance);
					goto save;
				}
				else
				{
					printf("Sorry invalid option");
				}
			} //switch prevoius user
			else if (opt == 2)
			{
				system("clear");
				unsigned int withdraw;
				printf("withdraw your money");
				printf("\nYOUR BALANCE\t%llu", cust.balance);
				printf("\nEnter the amount you want to withdraw\t");
				scanf("%u", &withdraw);
				getch();
				if (withdraw > cust.balance)
				{
					if (withdraw > 20000)
						printf("Too high to withdraw once");
					else
						printf("Amount is greater than the balance");
				}
				else if (withdraw > 0 && withdraw < 20000)
				{
					cust.balance -= withdraw;
					goto save;
				}
				else
					printf("invalid amount");
			}
			else if (opt == 3)
			{
				exit(0);
			}
			else
			{
				printf("Sorry invalid option\n");
			}
		case 3:
			exit(0);
			break;
		default:
			printf("Sorry invalid option");
		} //switch main menu
	}	  //while
	return 0;
} //main

int spin_roulette(void)
{
	int number;
	srand(time(NULL));
	number = 1 + (rand() % 36);
	printf("The ball has landed on %d\n", number);
	return number;
}

int roulette(unsigned long long int balance)
{
roulette_play:
	int betmode;
	int straightbet, cashbet, parity;
	int number;
	char colorbet, R = '\0', B = '\0';

	//Arrays
	int red[18] = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};
	int black[18] = {2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35};

	printf("There are 3 types of bets you can make\n\n");
	printf("1) Straight-up bet: Choose a single number. High risk, high payout! (35 to 1)\n\n");
	printf("2) Red or black: Choose a color.(1 to 1)\n Red numbers are  1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36\n Black numbers are 2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35\n\n");
	printf("3) Odd or even: Choose odd or even (1 to 1)\n\n");
	printf("4) To exit game");
	printf("\nPlease select your preferred type of bet. Enter 1, 2, or 3> ");
	scanf("%d", &betmode);
	while (balance > 0)
	{
		if (betmode == 4)
		{
			goto out;
		}
		else if (betmode == 1) //Straight bets
		{
			printf("\nGoing for the big money, eh?\n Enter a number between 1-36 you'd like to bet on> ");
			scanf("%d", &straightbet);
			printf("Now how much money are you willing to risk? Payout is 35 to 1> ");
			scanf("%d", &cashbet);
			printf("\nYou have bet $%d on the number %d", cashbet, straightbet);
			printf("\nPress ENTER to spin the roulette. Keep your fingers crossed!");
			getchar();
			getchar();
			number = spin_roulette();
			if (number == straightbet)
			{
				balance += (cashbet * 35);
				printf("Winner Winner! You now have %llu in your pocket", balance);
				getch();
				goto roulette_play;
			}
			else
				balance -= cashbet;
			printf("Sorry. You've lost %d. Your new balance is %llu", cashbet, balance);
			getch();
			goto roulette_play;
		}
		else if (betmode == 2) //Red or black bets
		{
			printf("\nAlright pick a color. Choose R for RED or B for BLACK> ");
			scanf("&c", &colorbet);
			printf("\nNow how much money are you willing to risk? Payout is 1 to 1> ");
			scanf("%d", &cashbet);
			printf("\nYou have bet %d on the color %c", cashbet, colorbet);
			printf("\nPress ENTER to spin the roulette. Keep your fingers crossed!");
			getchar();
			getchar();
			spin_roulette();
			if (colorbet == R)
			{
				if (number == red[17])
				{
					balance += cashbet;
					printf("Winner Winner! You now have %llu in your pocket", balance);
					getch();
					goto roulette_play;
				}
				else
					balance -= cashbet;
				printf("Sorry. You've lost %d. Your new balance is %llu", cashbet, balance);
				getch();
				goto roulette_play;
			}
			else if (colorbet == B)
			{
				if (number == black[17])
					balance += cashbet;
				printf("Winner Winner! You now have %llu in your pocket", balance);
				getch();
				goto roulette_play;
			}
			else
				balance -= cashbet;
			printf("Sorry. You've lost %d. Your new balance is %llu", cashbet, balance);
			getch();
			goto roulette_play;
		}
		else //Odd or even bets
		{
			printf("Alright enter 1 for odd or 2 for even. Choose wisely!> ");
			scanf("%d", &parity);
			printf("\nNow how much money are you willing to risk? Payout is 1 to 1> ");
			scanf("%d", &cashbet);
			if (parity == 1)
				printf("\nYou have bet %d on odds", cashbet);
			else
				printf("\nYou have bet %d on evens", cashbet);
			printf("\nPress ENTER to spin the roulette. Keep your fingers crossed!");
			getchar();
			getchar();
			spin_roulette();
			if (parity == 1)
			{
				if (number % 2 == 1)
				{
					balance += cashbet;
					printf("Winner Winner! You now have %llu in your pocket", balance);
					getch();
					goto roulette_play;
				}
				else
					balance -= cashbet;
				printf("Sorry. You've lost %d. Your new balance is %llu", cashbet, balance);
				getch();
				goto roulette_play;
			}
			else if (number % 2 == 0)
			{
				balance += cashbet;
				printf("Winner Winner! You now have %llu in your pocket", balance);
				getch();
				goto roulette_play;
			}
			else
				balance -= cashbet;
			printf("Sorry. You've lost %d. Your new balance is %llu", cashbet, balance);
			getch();
			goto roulette_play;
		}
	}
	if (balance == 0)
	{
		return 0;
	}
	getchar();
	getchar();
out:
	return balance;
}

int Randoms(int low, int high)
{ //Generates a random number
	int num = (rand() % (high - low + 1)) + low;
	srand(time(0));
	return num;
} //Randoms

int bet(unsigned long long int balance)
{
	int mon;
	printf("Place a bet\n");
	Re_mon(mon);
	if (mon > balance)
	{
		printf("Too high bet\n");
		return bet(balance);
	}
	return mon;
}