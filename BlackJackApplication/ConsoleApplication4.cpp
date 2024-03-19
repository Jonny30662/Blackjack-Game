#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <limits>
#include <iomanip>

using namespace std;

struct cards {
	string numbers;
	int values;
};

int getChoice() {
	int bet = 0;
	cout << "PLACE YOUR BET: ";
	cin >> setw(1) >> bet;

	while (!cin.good()) {
		cout << "input invalid" << endl;
		cin.clear();
		cin.ignore(numeric_limits<int>::max(), '\n');

		cout << "PLACE YOUR BET: ";
		cin >> setw(1) >> bet;
	}
	cin.clear();
	cin.ignore(numeric_limits<int>::max(), '\n');
	return bet;
}
int get_choice() {
	int menu_choice = 0;

	cout << "Please select one of the following options" << endl;
	cout << "Option 1: PLAY GAME" << endl;
	cout << "Option 2: HOW TO PLAY" << endl;
	cout << "Option 3: EXIT" << endl;
	cout << "Please enter 1,2 or 3" << endl;

	cin >> setw(1) >> menu_choice;

	while (!cin.good()) {
		cout << "input invalid" << endl;
		cin.clear();
		cin.ignore(numeric_limits<int>::max(), '\n');

		system("CLS");
		cout << "Please select one of the following options" << endl;
		cout << "Option 1: PLAY GAME" << endl;
		cout << "Option 2: HOW TO PLAY" << endl;
		cout << "Option 3: EXIT" << endl;
		cout << "Please enter 1,2 or 3" << endl;
		cin >> setw(1) >> menu_choice;
	}
	cin.clear();
	cin.ignore(numeric_limits<int>::max(), '\n');
	return menu_choice;
}

void shuffle(pair<string, string> cards[], int len) { // FUNCTION TAKES THE VALUES IN THE DECK ARRAY AND THEN REPLACED WITH RANDOM CARD UNTIL THE ARRAY IS COMPLETLY MIXED UP.
	string temp1 = "0";
	string temp2 = "0";
	int random_index = 0;

	for (int i = 0; i < len; i++) {
		int random_index = rand() % len;
		temp1 = cards[i].first;
		temp2 = cards[i].second;

		cards[i].first = cards[random_index].first;
		cards[random_index].first = temp1;

		cards[i].second = cards[random_index].second;
		cards[random_index].second = temp2;


	}

}

int main()
{

	cards cardss[13] = {
	   {"2", 2},
	   {"3", 3},
	   {"4", 4 },
	   {"5", 5},
	   {"6", 6},
	   {"7", 7 },
	   {"8", 8},
	   {"9", 9},
	   {"10", 10},
	   {"J", 10},
	   {"Q", 10},
	   {"K", 10},
	   {"A", 11}

	};

	string suit[4] = { "Spade", "Clubs", "Diamonds", "Hearts" };

	int values_of_cards[52]; //THIS IS AN ARROY SET UP TO STORE ALL THE VALUES OF THE CARDS WHEN THEY ARE PLACED IN IT
	pair<string, string> cards[52]; // A PAIR IS USED TO STORE THE VALUE OF THE CARD IN THE FIRST COLUMN AND THEN THE SUIT OF THE CARD IN THE SECOND
	pair<string, string> Dealer_Hand[5];
	int dealer_values[5] = { 0, 0, 0, 0, 0 }; // THIS MAKES IT EASIER FOR WHEN YOU RESET THE GAME, THESE VALUES WILL BE  OVER WRITTEN THROUGHOUT THE GAME.
	int dealer_total = 0; // DEALER TOTAL STARTS OFF AS 0 
	pair<string, string> Player_Hand[5]; 
	int player_values[5] = { 0, 0, 0, 0, 0 };
	int player_total = 0;
	string choice; // THIS IS FOR "HIT" OR "STAND"
	string choice2; // THIS IS FOR "YES" OR "NO" FOR EXITING THE GAME
	srand(time(NULL)); // RANDOM NUMBER GENERATOR USED TO SHUFFLE CARDS
	int player_total_ = 0;
	bool playing = true;
	bool player_win;
	bool dealer_win;
	int player_account;
	int bet = 0;
	
	int highscore_;
	ifstream infile("Accounts.txt"); // IMPORT THE PLAYER ACCOUNT FROM THE ACCOUNTS TEXT FILE

	infile >> player_account; 
	if (player_account < 500) { //THIS JUST MAKES SURE PEOPLE HAVE MONEY TO PLAY WITH. AS THE VALUE OF THE PLAYERS ACCOUNT WILL BE SAVED TO THE TEXT FILE WHICH COULD RESULT IN 0 MONEY. SO IF THIS IS THE CASE THE GAME GIVE THS PLAYER 500 CHIPS.
		player_account = 500;
	}
	ifstream highscore("Highscore.txt");
	highscore >> highscore_;
	if (player_account > highscore_) {
		highscore_ = player_account;

	}
	ofstream highscore1("Highscore.txt");
	highscore1 << highscore_; //YOUR FILE ACCOUNT VALUE IS PUT BACK INTO THE FILE
	infile.close();
	

	int z = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			cards[z].first = cardss[j].numbers; // THIS CREATES THE CARDS AND STORES THEM IN THE PAIR
			cards[z].second = suit[i];
			z++;
		}

	}
	while (playing == true) { // WHILE LOOP FOR GAME
		shuffle(cards, 52); // SHUFFLES THE CARDS TO A RANDOM ORDER 


		
	

		// attempt to take the array of values, match them up to the cards first value and then make another array which uses the order of the cards to order the values of the cards, 
		//this allows the index value to be used to get the card and the value of the cards.
		for (int j = 0; j < 13; j++) {
			for (int i = 0; i < 52; i++) {
				if (cards[i].first == cardss[j].numbers) {
					values_of_cards[i] = cardss[j].values;;


				}
			}
		}
		
		//Dealer takes top two cards off deck and values of these cards are saved to dealer total
		Dealer_Hand[0].first = cards[0].first;
		Dealer_Hand[0].second = cards[0].second;
		dealer_values[0] = values_of_cards[0];

		Dealer_Hand[1].first = cards[1].first;
		Dealer_Hand[1].second = cards[1].second;
		dealer_values[1] = values_of_cards[1];
		

		//for loop to work out dealer total
		for (int i = 0; i < 5; i++) {
			dealer_total = dealer_values[i] + dealer_total;
		}

		//Player takes next top two cards off deck and values of these cards are saved to player total
		Player_Hand[0].first = cards[2].first;
		Player_Hand[0].second = cards[2].second;
		player_values[0] = values_of_cards[2];

		Player_Hand[1].first = cards[3].first;
		Player_Hand[1].second = cards[3].second;
		player_values[1] = values_of_cards[3];

		//FOR LOOP TO WORK OUT PLAYER TOTAL

		for (int i = 0; i < 5; i++) {
			player_total = player_values[i] + player_total;
		}
		
		
			

			int menu_choice;
			menu_choice = get_choice();

			switch (menu_choice) {
			case 1:
				system("CLS"); // will go straight to game
				break;
			case 2:
				system("CLS"); // explains how the game works, then the user can press any button to play
				cout << "HOW TO PLAY" << endl << endl;
				cout << "- Object of the game is to gain a higher value than the dealer with out going bust" << endl << endl;
				cout << "- Try to avoid going over the value of 21 in order to not go bust" << endl << endl;
				cout << "- When its the player turn, you can choose to 'hit' or 'stand'" << endl << endl;
				cout << "- 'hit' means gives me another card, 'stand' means move to dealer turn" << endl << endl;
				cout << "- An Ace is normally worth 11, but if you or the dealer are about to go bust but have an ace in your hand, then the value of the card will change from from 11 to 1" << endl << endl;
				cout << "- bets are doubled if you win, lost if you lose and returned to the player if you draw" << endl << endl;
				cout << "- A draw can happen in two ways, eithr the player and the dealer end up with the same value, or they both go bust" << endl << endl;



				system("pause");
				system("CLS");
				break;

			case 3:
				system("CLS"); // exits game
				cout << "Thanks for playing" << endl;
				exit(1);
				return 1;
			default: 
				system("CLS"); // if anything else is entered
				cout << "invalid" << endl;
				continue;
				
			
			}
		


		


	
		while (true) { // WHILE LOOP TO MAKE SURE THE GAME KEEPS PROMPTING THE USER TO ENTER A VALUE BELOW OR EQUAL TO ACCOUNT VALUE, OTHERWISE THE USER CANNOT CARRY ON WITH THE PROGRAM
			cout << "Highest account balance achieved: " << highscore_ << endl << endl;
			cout << "PLAYER ACCOUNT: " << player_account << endl << endl;
			bet = getChoice();
			if (bet <= player_account) {
				break;
			}
			else if (bet > player_account) {
				system("CLS");
				cout << "Insufficient Funds In Account" << endl;
			}


		
		}
		
		
		
		
		
		system("CLS"); // USED TO TIDY UP THE SCREEN

		cout << "CURRENT BET: " << bet << endl;
		player_account = player_account - bet;
		cout << "" << endl;


		cout << "DEALER HAND: " << endl << endl;
		
		cout << Dealer_Hand[0].first << " of " << Dealer_Hand[0].second << endl; //ONLY FIRST DEALER CARD IS SHOWN TO THE USER
		cout << "Hidden" << endl;
			
		
		cout << "" << endl;
		cout << "DEALER TOTAL FOR 1ST CARD: " << dealer_values[0] << endl << endl << endl;

		cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl << endl;

		cout << "PLAYER HAND: " << endl << endl;
		for (int i = 0; i < 5; i++) { // PRINTS OUT THE PLAYER HAND
			if (Player_Hand[i].first != "") { // IF THE FIRST PART OF THE PAIR DOESNT HAVE ANYTHING IN IT DON'T PRINT IT
				cout << Player_Hand[i].first << " of " << Player_Hand[i].second << endl; 
			}
		}
		cout << "" << endl;
		cout << "PLAYER TOTAL: " << player_total << endl;







		int P_card_num = 2; //MAKES SURE THAT THE ARRAY SLOT FILLED BY NEXT CARD WILL BE AFTER THE FIRST TWO CARDS
		int D_card_num = 2; //MAKES SURE THAT THE ARRAY SLOT FILLED BY NEXT CARD WILL BE AFTER THE FIRST TWO CARDS
		int deck_num = 4;	//MAKES SURE THAT THE PROGRAM TAKES THE ARRAY SLOT AFTER THE FIRST 4 CARDS. THIS MAKES SURE THAT CARDS ARE NOT REPEATED
		// starting the game
		//PLAYERS TURN
		while ((dealer_total < 21) && (player_total < 21)) {
			cout << "hit or stand" << endl;
			getline(cin, choice);
			if (choice == "hit") {
				system("CLS");
				cout << "CURRENT BET: " << bet << endl;
				cout << "" << endl;
				cout << "DEALER HAND: " << endl << endl;
				
						
				cout << Dealer_Hand[0].first << " of " << Dealer_Hand[0].second << endl;
				cout << "Hidden" << endl;
					
					
				
				cout << "" << endl;
				cout << "DEALER TOTAL FOR 1ST CARD : " << dealer_values[0] << endl << endl << endl;


				cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl << endl;


				Player_Hand[P_card_num].first = cards[deck_num].first; // THIS PORTION OF CODE IS TO MAKE SURE THE RIGHT CARD GOES INTO THE PLAYER HAND AND MAKES SURE THE VALUE ASSOCIATED WITH THE CARD IS PLACED IN THE VALUE ARRAY.
				Player_Hand[P_card_num].second = cards[deck_num].second;
				player_values[P_card_num] = values_of_cards[deck_num];
				cout << "PLAYER HAND: " << endl << endl;
				for (int i = 0; i < 5; i++) {
					if (Player_Hand[i].first != "") {
						cout << Player_Hand[i].first << " of " << Player_Hand[i].second << endl; 
					}

				}
				player_total = 0; // THIS REWRITES THE VALUE EVERYTIME SO IT DOESNT STACK FROM PREVIOUS CALCULATIONS 
				for (int i = 0; i < 5; i++) {
					player_total = player_values[i] + player_total;
				}
				for (int i = 0; i < 5; i++) {
					if ((Player_Hand[i].first == "A") && (player_total > 21)) { // THIS LOOKS FOR AN ACE IN THE PLAYER HAND, WHEN THE PLAYER HAS GONE BUST BUT THE PLAYER HAS AN ACE THE VALUE OF THE CARDS WILL CHANGE TO 1
						player_total = player_total - 10;
					}
				}
				cout << "" << endl;
				cout << "PLAYER TOTAL: " << player_total << endl << endl << endl;
				P_card_num++; // MEANS THE NEXT PART OF THE ARRAY WILL BE SELECTED
				deck_num++; // MEANS THE NEXT CARD IN THE DECK WILL BE SELECTED
			}
			else if (choice == "stand") { // IF STAND GO TO DEALER TURN

				break;
			}
			else {
				cout << "invalid input" << endl;
			}
		}
		//DEALERS TURN 
		while ((dealer_total < 17) && (D_card_num < 5)) {
			system("CLS");
			cout << "CURRENT BET: " << bet << endl;
			cout << "" << endl;


			Dealer_Hand[D_card_num].first = cards[deck_num].first; // SAME THING AS PLAYER HAND
			Dealer_Hand[D_card_num].second = cards[deck_num].second;
			dealer_values[D_card_num] = values_of_cards[deck_num];
			cout << "DEALER HAND: " << endl << endl;
			for (int i = 0; i < 5; i++) {
				if (Dealer_Hand[i].first != "") {
					cout << Dealer_Hand[i].first << " of " << Dealer_Hand[i].second << endl;
				}
			}
			dealer_total = 0;
			for (int i = 0; i < 5; i++) {

				dealer_total = dealer_values[i] + dealer_total;
			}
			for (int i = 0; i < 5; i++) {
				if ((Dealer_Hand[i].first == "A") && (dealer_total > 21)) {
					dealer_total = dealer_total - 10;
				}
			}
			cout << "" << endl;
			cout << "DEALER TOTAL : " << dealer_total << endl << endl << endl;


			cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl << endl;


			cout << "PLAYER HAND: " << endl << endl;
			for (int i = 0; i < 5; i++) {
				if (Player_Hand[i].first != "") {
					cout << Player_Hand[i].first << " of " << Player_Hand[i].second << endl;
				}
			}
			cout << "" << endl;
			cout << "PLAYER TOTAL: " << player_total << endl << endl << endl;


			D_card_num++;
			deck_num++;
		}



		// WIN CONDITIONS
		if (dealer_total > 21) {
			cout << "Dealer has gone bust " << endl;
			player_win = true;
			dealer_win = false;
		}
		if (player_total > 21) {
			cout << "Player has gone bust " << endl;
			dealer_win = true;
			player_win = false;
		}
		if ((player_total > 21) && (dealer_total > 21)) {
			player_win = false;
			dealer_win = false;
		}
		if ((player_total > dealer_total) && (dealer_total <= 21) && (player_total <= 21)) {
			player_win = true;
			dealer_win = false;
		}
		if ((dealer_total > player_total) && (dealer_total <= 21) && (player_total <= 21)) {
			dealer_win = true;
			player_win = false;
		}
		if (player_total == dealer_total) {
			player_win = true;
			dealer_win = true;
		}

		//PRINTING OUT WHO WINS AND STATING WHO GAINS MONEY AND WHO LOSES MONEY
		if ((dealer_win == true) && (player_win == false)) {
			cout << "Dealer Wins" << endl;
			bet = 0;
		}
		if ((dealer_win == false) && (player_win == true)) {
			cout << "Player Wins" << endl;
			bet = bet * 2;
		}
		if ((dealer_win == true) && (player_win == true)) {
			cout << "Draw" << endl;
			bet = bet;
		}
		if ((dealer_win == false) && (player_win == false)) {
			cout << "Draw" << endl;
			bet = bet;
		}
		player_account = player_account + bet;
		ofstream infile("Accounts.txt");
		infile << player_account; //YOUR FILE ACCOUNT VALUE IS PUT BACK INTO THE FILE
		infile.close();
		//PLAY AGAIN
		while (true) {
			cout << "Go back to menu? (type 'yes' or 'no') " << endl;
			getline(cin, choice2);
			if (choice2 == "yes") { //IF THE USER CHOOSES YES THEN ALL THE ARRAYS WILL BE RESET AND THE SCREEN WILL BE CLEARED
				system("CLS");
				for (int i = 0; i < 5; i++) {
					Player_Hand[i].first = "";
					Player_Hand[i].second = "";

					Dealer_Hand[i].first = "";
					Dealer_Hand[i].second = "";
					player_values[i] = 0;
					dealer_values[i] = 0;
				}
				dealer_total = 0;
				player_total = 0;
				break;
			}
			else if (choice2 == "no") { //IF USER CHOOSES NO THEN THE GAME ENDS
				playing = false;
				system("CLS");
				cout << "Thanks for playing" << endl;
				exit(1);
				return 1;
			}
			else {
				system("CLS");
				cout << "Invalid Input" << endl;
			}
		}
	}

}