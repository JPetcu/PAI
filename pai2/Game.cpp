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
}


void Game::initGame()
{
	mPot = smallBlind + bigBlind;
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
	std::vector<int> rank = { 0, 0, 0, 0, 0 };
	for (auto player : mPlayers)
	{
		rank[i++] = SevenEval::GetRank(player->getCard1()->toValue(), player->getCard2()->toValue(), mDownCards[0]->toValue(), mDownCards[1]->toValue(), mDownCards[2]->toValue(), mDownCards[3]->toValue(), mDownCards[4]->toValue());
	}
	std::vector<int>::iterator it = std::max_element(rank.begin(), rank.end());
	bool draw = false;
	for (auto it2 = rank.begin(); it2 != rank.end(); it2++)
	{
		if (*it == *it2 && mPlayers.size() != 1 && it2 != it)
			draw = true;

	}
	if (draw)
		return -1;
	return std::distance(rank.begin(), it);

}

void Game::showWinner()
{
	winner = this->decideWinner();
	if (winner >= 0)
		std::cout << "\nWinner is Player" << mPlayers[this->decideWinner()]->getNo() << "\n";
	else
		std::cout << "\nDRAW\n";
}

void Game::updateChips()
{
	int k = 0;
	for (auto player : mPlayers)
	{
		if (player->getChips() >= 1600)
		{
			over = true;
			winner = player->getNo() - 1;
		}
		if (winner != -1)
		{
			if (k == winner)
				player->updateChips((mPlayers.size() - 1) * 20);
			else
				player->updateChips(-20);
		}
		player->throwCards();
		k++;

		std::cout << "Player" << player->getNo() << " has: ";
		player->printBalance();

	}
}
void Game::erasePlayers()
{
	std::vector<std::shared_ptr<Player>>::iterator toBeErased = mPlayers.end();
	for (auto it = mPlayers.begin(); it != mPlayers.end(); it++)
	{
		if ((*it)->getChips() <= 0)
			toBeErased = it;
	}
	if (toBeErased != mPlayers.end())
		mPlayers.erase(toBeErased);
	std::cout << "-------------------------------------\n";
}

void Game::clearRound()
{
	mDownCards.clear();
	mDeck->shuffle();
	mPot = smallBlind + bigBlind;
}

void Game::playRound()
{
	initGame();
	requestAction();
	dealFlop();
	requestAction();
	dealTurn();
	requestAction();
	dealRiver();
	requestAction();
	decideWinner();
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

std::shared_ptr<Action> Game::requestAction(std::shared_ptr<Player> player)
{
	return player->getAction();
}

void Game::requestAction()
{
	std::vector<std::shared_ptr<Action>> actions;
	while(canContinue(actions) != true)
	{
		if (actions.size() < currentTurn())
			actions.emplace_back(requestAction(mPlayers[getTurn()]));
		else
			actions[getTurn()] = requestAction(mPlayers[getTurn()]);
	}
}

void Game::sendDownCards()
{
	for (auto player : mPlayers)
		player->getDownCards(mDownCards);
}

bool Game::canContinue(std::vector<std::shared_ptr<Action>> actions)
{
	if (actions.size() != mPlayers.size())
		return false;

	std::string type = actions[0]->getAction();
	int raise = 0, call = 0, check = 0, fold = 0;

	int k = 0;
	for (auto action : actions)
	{
		if (action->getAction() == "RaiseAction")
		{
			raise++;
			mPot += action->getChips();
			mPlayers[k]->updateChips(action->getChips()*-1);
		}
		if (action->getAction() == "CallAction")
		{
			call++;
			mPot += action->getChips();
			mPlayers[k]->updateChips(action->getChips()*-1);
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
