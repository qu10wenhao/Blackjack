#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

const string type[4] = {"Heart", "Spade", "Club", "Diamond"};				//4 colors of the cards.
const string number[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};	//from A to K .
const double card_score[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0.5, 0.5, 0.5};		//the score of each kinds of cards.
bool stack[4][13] = {0}									//the stack of cards, false means this card is in the stack.

char GetChar();										//the function to judge the legalty of the input.
											//return 'y', 'Y', 'n', 'N'.
																					
void Wash(int acards[52][2],int bcards[52][2], int &anum, int &bnum);			//the function to initialise the game.

bool PlayerRound(int cards[52][2], int &num);						//the function for the player's round.
											//return false if player's score is bigger than 21.
																					
bool ComputerRound(int acards[52][2], int bcards[52][2], int &num);			//the function for the computer's round.
											//return false if computer's score is bigger than 21.

void Deal(int n, int cards[52][2], int &num);						//the function to deal cards.
											//n means the number of the cards to deal.

void Show(int cards[52][2], int num);							//the function to show all the cards of player or computer.

double GetScore(int cards[52][2], int num);						//the function to get the score.
											//return the score.

int main(){
	int player_cards[52][2], computer_cards[52][2];					//player_cards[52][2], computer_cards[52][2]: the cards which the player and computer have.
											//cards[i][0] is the color and cards[i][1] is the number "A-K".
	int player_cards_num = 0, computer_cards_num = 0;				//player_cards_num, computer_cards_num: the number of the cards which player and computer have.
	double player_score = 0, computer_score = 0, score_dif = 0;			//player_score, computer_score: the score of the player and computer.
											//score_dif: the difference of player's and computer's score, help to judge the result.
	char judge_play;								//judge_play: judge whether the player want to play the game again.
	do{
		Wash(player_cards, computer_cards, player_cards_num, computer_cards_num);
		if(PlayerRound(player_cards, player_cards_num)){
			if(ComputerRound(computer_cards, player_cards, computer_cards_num)){
				cout << "your score: " << GetScore(player_cards, player_cards_num) << endl;
				cout << "computer's score: " << GetScore(computer_cards, computer_cards_num) << endl;
				score_dif = GetScore(player_cards, player_cards_num) - GetScore(computer_cards, computer_cards_num);
				if(score_dif > 0){
					cout << "You win!" << endl;
				}else if(score_dif < 0){
					cout << "You lost!" << endl;	
				}else{
					if(player_cards_num < computer_cards_num){
						cout << "You win!" << endl;
					}else if(player_cards_num > computer_cards_num){
						cout << "You lost!" << endl;
					}else{
						cout << "It's draw!" << endl;
					}
				}
			}
		}
		cout << "Again(y/n)?";
		judge_play = GetChar();
		cout << endl;
	}while('y' == judge_play || 'Y' == judge_play);
	return 0;
}
char GetChar(){
	string c;									//c: the variable to store user's input.
	while(true){
		try{
			cin >> c;
			if("y" == c || "n" == c || "Y" == c || "N" == c){
				return c[0];
			}
			throw 1;
		}
		catch(int i){
			cout << "Your input is illegal! Pleas try again: ";
		}
	}
}
void Wash(int acards[52][2], int bcards[52][2], int &anum, int &bnum){
	int i, j;
	for(i=0; i<4; i++){
		for(j=0; j<13; j++){
			stack[i][j] = false;
		}
	}
	for(i=0; i<52; i++){
		acards[i][0] = 0;
		acards[i][1] = 0;
		bcards[i][0] = 0;
		bcards[i][1] = 0;
	}
	anum = 0;
	bnum = 0;
}

bool PlayerRound(int cards[52][2], int &num){
	char judge;																		//judge: judge wheather the player want one more card.
	Deal(2, cards, num);
	cout << "Player has: ";
	Show(cards, num);
	cout << "Need one more card?(y/n):";
	judge = GetChar();
	while('y' == judge || 'Y' == judge){
		Deal(1, cards, num);
		cout << "Now you have: ";
		Show(cards, num);
		if(0 > 21.0 - GetScore(cards, num)){
			cout << "You lost!" << endl;;
			return false;
		}
	cout << "Need one more card?(y/n):";
	judge = GetChar();		
	}
	return true;
}

bool ComputerRound(int acards[52][2], int bcards[52][2], int &num){
	Deal(2, acards, num);
	cout << "Computer has: ";
	Show(acards, num);
	while(0 < GetScore(bcards, num) - GetScore(acards, num)){
		Deal(1, acards, num);
		cout << "Computer needs one more card: ";
		Show(acards, num);
		if(0 > 21.0 - GetScore(acards, num)){
			cout << "You win!" << endl;
			return false;
		}
	}
	cout << "Computer doesn't want more cards!" << endl;
	return true;
}

void Deal(int n, int cards[52][2],int &num){
	srand(time(NULL));
	
	int i, j;
	while(n > 0){
		do{
			i = rand()%4;
			j = rand()%13;
		}while(stack[i][j]);
		cards[num][0] = i; 
		cards[num][1] = j;
		num ++;
		stack[i][j] = true;
		n --;
	}
}

void Show(int cards[52][2], int num){
	int i;
	for(i=0; i<num; i++){
		cout << type[cards[i][0]] << " " << number[cards[i][1]] << "  ";
	}
	cout << endl;
}

double GetScore(int cards[52][2], int num){
	double score = 0;								//score: store the score and return it in the end of the function.
	int i;
	for(i=0; i<num; i++){
		score += card_score[cards[i][1]];
	}
	return score;
}
