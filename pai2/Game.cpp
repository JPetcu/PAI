#include "stdafx.h"
#include "Game.h"
#include "SevenEval/src/SevenEval.h"
#include <algorithm>
#include <typeinfo>


Game::Game() : mDeck(new Deck()), cardCounter(52, 0)
{
	mPlayers.emplace_back(new Player());
	mPlayers.emplace_back(new Player());
	mPlayers.emplace_back(new Player());
	mPlayers.emplace_back(new Player());
	mCashier = std::make_shared<Cashier>(mPlayers);
}


void Game::initGame()
{
	mPot = /*smallBlind + bigBlind;*/ 0;
	for (auto player : mPlayers)
	{
		player->receiveCard(mDeck->draw());
		cardCounter[player->getCard1()->toValue()]++;
	}
	for (auto player : mPlayers)
	{
		player->receiveCard(mDeck->draw());
		cardCounter[player->getCard2()->toValue()]++;
	}
}

void Game::dealFlop()
{
	std::shared_ptr<Card> deadCard = mDeck->draw();
	cardCounter[deadCard->toValue()]++;

	mDownCards.emplace_back(mDeck->draw());
	mDownCards.emplace_back(mDeck->draw());
	mDownCards.emplace_back(mDeck->draw());

	sendDownCards();

}

void Game::dealTurn()
{
	std::shared_ptr<Card> deadCard = mDeck->draw();
	cardCounter[deadCard->toValue()]++;
	mDownCards.emplace_back(mDeck->draw());
	sendDownCards();
}

void Game::dealRiver()
{
	std::shared_ptr<Card> deadCard = mDeck->draw();
	cardCounter[deadCard->toValue()]++;
	mDownCards.emplace_back(mDeck->draw());
	for (auto card : mDownCards)
		cardCounter[card->toValue()]++;
	sendDownCards();
}



int Game::decideWinner()
{
	int i = 0;
	std::vector<int> rank = std::vector<int>(4, 0);
	for (auto player : mPlayers)
	{
		rank[player->getNo()-1] = SevenEval::GetRank(player->getCard1()->toValue(), player->getCard2()->toValue(), mDownCards[0]->toValue(), mDownCards[1]->toValue(), mDownCards[2]->toValue(), mDownCards[3]->toValue(), mDownCards[4]->toValue());
	}
	std::vector<int>::iterator it = std::max_element(rank.begin(), rank.end());
	bool draw = false;
	for (auto it2 = rank.begin(); it2 != rank.end(); it2++)
	{
		if (*it == *it2 && mPlayers.size() != 1 && it2 != it)
			draw = true;

	}
	if (draw)
	{
		mCashier->endOfRound(rank, true, mPot);
	}
	else
	{
		mCashier->endOfRound(rank, false, mPot);
	}
	
	return std::distance(rank.begin(), it);

}

void Game::showWinner()
{
	//winner = this->decideWinner();
	if (winner >= 0)
		std::cout << "\nWinner is Player" << winner+1 << "\n";
	else
		std::cout << "\nDRAW\n";
}

void Game::updateChips()
{
	int total = 0;
	int k = 0;
	for (auto player : mPlayers)
	{
		if (player->getChips() >= 1600)
		{
			over = true;
			winner = player->getNo() - 1;
		}
		
		player->throwCards();
		k++;

		std::cout << "Player" << player->getNo() << " has: ";
		player->printBalance();
		
		player->clearBet();
		total += player->getChips();
	}
	std::cout << "Total: " << total << "\n";
	if(total != 1600)
	{
		total = 5;
	}
}
void Game::erasePlayers()
{
	std::vector<std::shared_ptr<Player>>::iterator toBeErased = mPlayers.end();
	for (auto it = mPlayers.begin(); it != mPlayers.end(); it++)
	{
		
			while ((*it)->getChips() <= 0)
			{
				toBeErased = it;
				mPlayers.erase(toBeErased);
				it = mPlayers.begin();
			}

		
	}
	/*if (toBeErased != mPlayers.end())
		mPlayers.erase(toBeErased);*/
	std::cout << "-------------------------------------\n";

}

void Game::clearRound()
{
	mDownCards.clear();
	mDeck->shuffle();
	mPot = /*smallBlind + bigBlind;*/ 0;
	mDownCards = std::vector<std::shared_ptr<Card>>(0, 0);
	playerTurn = 0;
	requiredToPlay = bigBlind;
	mCashier->clearBets();
	for(auto player:mPlayers)
	{
		player->setAllIn(false);
		player->getDownCards(mDownCards);
	}
}

void Game::playRound()
{
	initGame();
	mCashier->startOfRound();
	requestAction();
	dealFlop();
	requestAction();
	dealTurn();
	requestAction();
	dealRiver();
	requestAction();
	winner = decideWinner();
	showGame();
	showWinner();
	updateChips();
	erasePlayers();
	clearRound();
}



void Game::showGame()
{
	int i = 1;
	for(auto player : mPlayers)
	{
		std::cout << "Player" << player->getNo() << ": " << player->showCards() << "\n";
	}
	std::cout << "Cards: ";
	for (auto card : mDownCards)
		std::cout << card->toString() << ", ";
}

bool Game::getOver()
{
	return over;
}

int Game::getWinner()
{
	return winner;
}

std::shared_ptr<Action> Game::requestAction(std::shared_ptr<Player> player, const int bet)
{
	std::shared_ptr<Action> action = player->getAction(bet);
	if(action->getAction() == "BetAction")
	{
		mPot += action->getChips();
		requiredToPlay = player->getBet();
	}
	if (action->getAction() == "CallAction")
	{
		mPot += action->getChips();
		//requiredToPlay += action->getChips();
	}
	return action;
}

void Game::requestAction()
{
	std::vector<std::shared_ptr<Action>> actions;
	int i = 0;
	while(canContinue(actions) != true)
	{
		int bet = requiredToPlay - mPlayers[currentTurn()]->getBet();
		
		if (actions.size() != mPlayers.size())
		{   
			int currTurn = currentTurn();
			actions.emplace_back(requestAction(mPlayers[getTurn()], bet));
			
		}
		else
		{
			int currTurn = currentTurn();
			actions[getTurn()] = requestAction(mPlayers[getTurn()], bet);
			
		}
		i++;
		if (i > 10)
		{
			std::cout << "Blocked";
		}
	}
	
}

void Game::sendDownCards()
{
	for (auto player : mPlayers)
		player->getDownCards(mDownCards);
}

bool Game::canContinue(std::vector<std::shared_ptr<Action>> actions)
{
	if (actions.size() < mPlayers.size())
		return false;

	std::string type = actions[0]->getAction();
	int raise = 0, call = 0, check = 0, fold = 0;

	int k = 0;
	for (auto action : actions)
	{
		if (k > mPlayers.size())
			break;
		if (action->getAction() == "BetAction")
		{
			raise++;
		}
		if (action->getAction() == "CallAction")
		{
			call++;
		}
		if (action->getAction() == "CheckAction")
		{
			check++;
		}
		if (action->getAction() == "FoldAction")
		{
			fold++;
		}
		k++;
	}
	if (raise > 1)
	{
		check = raise - 1;
		raise = 1;
	}
	if(fold + raise == mPlayers.size() || 
		raise + call == mPlayers.size() ||
		raise + fold + call == mPlayers.size() ||
		check == mPlayers.size())
			return true;
	return false;
}

int Game::getTurn()
{
	
		int turn = playerTurn;
		playerTurn++;
		if (playerTurn == mPlayers.size())
			playerTurn = 0;
	
	return turn;
}
int Game::currentTurn()
{
	return playerTurn;
}

Game::~Game()
{
}
