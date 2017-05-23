#include "stdafx.h"
#include "logic_core.h"
#include "logic_def.h"
#include <climits>
#include <algorithm>
#include <string>
#include <cstdlib>

#define CARDS_COUNT 54
logic_core::logic_core(int deskCount)
{
	this->deskCount = deskCount;
}

void logic_core::init()
{
	for (int i = 1; i <= 13; i++)
	{
		m_cards.push_back(i * 100 + 1);
		m_cards.push_back(i * 100 + 2);
		m_cards.push_back(i * 100 + 3);
		m_cards.push_back(i * 100 + 4);
	}
	m_cards.push_back(14 * 100);
	m_cards.push_back(15 * 100);

	assert(m_cards.size()==54);

	srand(time(NULL));
	std::random_shuffle(m_cards.begin(), m_cards.end(), [](int x) { return std::rand() % x; });//洗下牌
}


void logic_core::send_card()
{
	srand(time(NULL));
	std::random_shuffle(m_cards.begin(), m_cards.end(), [](int x) { return std::rand() % x; });//洗下牌

	mOpenCard = m_cards[m_cards.size() - 1];

	int rand_1 = rand(deskCount,m_cards.size()-deskCount);
	std::vector<int> m_cards_1;
	for (int i = rand_1; i < m_cards.size(); i++)
	{
		m_cards_1.push_back(m_cards[i]);
	}
	for (int i = 0; i < rand_1; i++)
	{
		m_cards_1.push_back(m_cards[i]);
	}
	m_cards = m_cards_1;

	int i = 1;
	while (m_cards.size()>3)
	{
		m_cardMap[i].push_back(take_one_card());
		i++;
		if (i > deskCount)
		{
			i = 1;
		}
	}
}

int logic_core::rand(int min, int max)
{
	return min +  std::rand()%(max-min+1);
}

int logic_core::take_one_card()
{
	int card=m_cards[m_cards.size() - 1];
	m_cards.pop_back();
	return card;
}

int logic_core::compare_card(std::vector<int> cards_1, std::vector<int> cards_2)
{
	int point1=getPoint(cards_1);
	int point2 = getPoint(cards_2);	

	return 0;
}

int logic_core::getPoint(std::vector<int> cards)
{
	std::vector<int> sort_cards = cards;
	std::sort(sort_cards.begin(), sort_cards.end(), [](int x, int y) { return x<y; });

	return 0;
}


//双飞
bool logic_core::IS_SHUANGFEI(std::vector<int> cards)
{
	if (cards.size()==2 && (cards[0] / 100 == 14 || cards[0] / 100 == 15) && (cards[1] / 100 == 14 || cards[1] / 100 == 15))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//四张牌
bool logic_core::IS_ZHADAN(std::vector<int> cards)
{
	if (cards.size() == 4 && cards[0]/100==cards[1]/100 && cards[0]/100 == cards[2]/100 && cards[0]/100 == cards[3]/100)
	{	
		return true;
	}
	else
	{
		return false;
	}
}

//四带1
bool logic_core::IS_SIDAIYI(std::vector<int> cards)
{
	if (cards.size() == 5 && cards[0] / 100 == cards[1] / 100 && cards[0] / 100 == cards[2] / 100 && cards[0] / 100 == cards[3] / 100)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//四带二
bool logic_core::IS_SIDAIER(std::vector<int> cards)
{
	if (cards.size() == 6 && cards[0] / 100 == cards[1] / 100 && cards[0] / 100 == cards[2] / 100 && cards[0] / 100 == cards[3] / 100)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//三张牌
bool logic_core::IS_SANPAI(std::vector<int> cards)
{
	if (cards.size() == 3 && cards[0] / 100 == cards[1] / 100 && cards[0] / 100 == cards[2] / 100)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//三带1
bool logic_core::IS_SANDAIYI(std::vector<int> cards)
{
	if (cards.size() == 4 && cards[0] / 100 == cards[1] / 100 && cards[0] / 100 == cards[2] / 100 && cards[0] / 100 == cards[3] / 100)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//两张牌
bool logic_core::IS_DUIPAI(std::vector<int> cards)
{
	if (cards.size() == 2 && cards[0] / 100 == cards[1] / 100)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//四排 顺子
bool logic_core::IS_SIPAISHUN(std::vector<int> cards)
{
	if (cards[0] / 100 == cards[1] / 100)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//三排 顺子
bool logic_core::IS_SANPAISHUN(std::vector<int> cards)
{
	if (cards[0] / 100 == cards[1] / 100)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//二排顺
bool logic_core::IS_ERPAISHUN(std::vector<int> cards)
{
	if (cards[0] / 100 == cards[1] / 100)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//单排顺
bool logic_core::IS_DANPAISHUN(std::vector<int> cards)
{
	if (cards[0] / 100 == cards[1] / 100)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//单张牌
bool logic_core::IS_DANPAI(std::vector<int> cards)
{
	if (cards.size() == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}


