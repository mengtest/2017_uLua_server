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
	init();
}

void logic_core::init()
{
	m_cards.clear();
	for (int i = 3; i <= 15; i++)
	{
		m_cards.push_back(i * 100 + 1);
		m_cards.push_back(i * 100 + 2);
		m_cards.push_back(i * 100 + 3);
		m_cards.push_back(i * 100 + 4);
	}
	m_cards.push_back(16 * 100);
	m_cards.push_back(17 * 100);

	assert(m_cards.size()==54);

	srand(time(NULL));
	std::random_shuffle(m_cards.begin(), m_cards.end(), [](int x) { return std::rand() % x; });//洗下牌
}


void logic_core::send_card()
{
	init();

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
		int card= take_one_card();
		if (mOpenCard == card)
		{
			landlord_id = i;
		}
		m_cardMap[i].push_back(card);
		i++;
		if (i > deskCount)
		{
			i = 1;
		}
	}

	m_RemainlandlordCards = m_cards;
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

void logic_core::playhand(int deskid,std::vector<int>& cards)
{
	std::vector<int>& m_desk_cards=m_cardMap[deskid];

	auto var1 = cards.begin();
	for (auto var : cards)
	{
		for (; var1 != cards.end();)
		{
			if (*var1 = var)
			{
				var1=m_desk_cards.erase(var1);
				break;
			}
			else
			{
				var1++;
			}
		}
	}
}

int logic_core::compare_card(std::vector<int> cards_1, std::vector<int> cards_2)
{
	std::vector<int> sort_cards_1 = cards_1;
	std::sort(sort_cards_1.begin(), sort_cards_1.end(), [](int x, int y) { return x<y; });

	std::vector<int> sort_cards_2 = cards_2;
	std::sort(sort_cards_2.begin(), sort_cards_2.end(), [](int x, int y) { return x<y; });

	int type1 = GetPaiType(sort_cards_1);
	int type2 = GetPaiType(sort_cards_2);
	if (type1!=type2)
	{
		if (type1 != 1 && type1 != 2)
		{
			return -1;
		}
	}
	else if(cards_1.size() != cards_2.size())
	{
		return -1;
	}

	int point1=getPoint(type1,cards_1);
	int point2 = getPoint(type2,cards_2);	

	if (point1 > point2)
	{
		return 1;
	}
	else
	{
		return -1;
	}
	return 0;
}

int logic_core::getPoint(int type,std::vector<int> cards)
{
	if (type == 1)
	{
		return FEN_SHUANGFEI(cards);
	}	
	else if (type == 2)
	{
		return FEN_ZHADAN(cards);
	}
	else if (type == 3)
	{
		return FEN_SANPAI(cards);
	}
	else if (type == 4)
	{
		return FEN_ERPAI(cards);
	}
	else if (type == 5)
	{
		return FEN_SIPAISHUN(cards);
	}
	else if (type == 6)
	{
		return FEN_SANPAISHUN(cards);
	}
	else if (type == 7)
	{
		return FEN_ERPAISHUN(cards);
	}
	else if (type == 8)
	{
		return FEN_DANPAISHUN(cards);
	}
	else if (type == 9)
	{
		return FEN_DANPAI(cards);
	}
	return 0;
}


int logic_core::GetPaiType(std::vector<int> sort_cards)
{

	if (IS_SHUANGFEI(sort_cards))
	{
		return 1;
	}
	else if (IS_ZHADAN(sort_cards))
	{
		return 2;
	}
	else if (IS_SANPAI(sort_cards))
	{
		return 3;
	}
	else if (IS_ERPAI(sort_cards))
	{
		return 4;
	}
	else if (IS_SIPAISHUN(sort_cards))
	{
		return 5;
	}
	else if (IS_SANPAISHUN(sort_cards))
	{
		return 6;
	}
	else if (IS_ERPAISHUN(sort_cards))
	{
		return 7;
	}
	else if (IS_DANPAISHUN(sort_cards))
	{
		return 8;
	}
	else if (IS_DANPAI(sort_cards))
	{
		return 9;
	}
	else
	{
		return -1;
	}
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
	if (cards.size() >= 4 && cards.size()<=6)
	{
		for (size_t i = 0; i < cards.size(); i++)
		{
			if (cards[i] / 100 == cards[i+1] / 100 && cards[i] / 100 == cards[i+2] / 100 && cards[i] / 100 == cards[i+3] / 100)
			{
				return true;
			}
		}
	}
	return false;
}

//三张牌
bool logic_core::IS_SANPAI(std::vector<int> cards)
{
	if (cards.size() >= 3 && cards.size()<=4)
	{
		for (size_t i = 0; i < cards.size(); i++)
		{
			if (cards[i] / 100 == cards[i + 1] / 100 && cards[i] / 100 == cards[i + 2] / 100)
			{
				return true;
			}
		}
	}
	return false;
}

//两张牌
bool logic_core::IS_ERPAI(std::vector<int> cards)
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
	if (cards.size() >= 8)
	{
		for (size_t i = 0; i < cards.size(); i++)
		{
			int count = 0;
			if (cards[i] / 100 <= 14 && cards[i] / 100 == cards[i + 1] / 100 && cards[i] / 100 == cards[i + 2] / 100 && cards[i] / 100 == cards[i + 3] / 100)
			{
				count = 1;
				for (int j = 1; j < 100; j++)
				{
					if ((i + 4 * j + 3) < cards.size() && cards[i] / 100 + 1 * j == cards[i + 4 * j] / 100)
					{
						if (cards[i + 4 * j] / 100 <= 14 && cards[i + 4 * j] / 100 == cards[i + 4 * j + 1] / 100 && cards[i + 4 * j] / 100 == cards[i + 4 * j + 2] / 100 && cards[i + 4 * j] / 100 == cards[i + 4 * j + 3] / 100)
						{
							count++;
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
				if (count >= 2 && cards.size() <= (count * 4 + count * 2))
				{
					return true;
				}
				break;
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}

//三排 顺子
bool logic_core::IS_SANPAISHUN(std::vector<int> cards)
{
	if (cards.size() >= 6)
	{
		for (size_t i = 0; i < cards.size(); i++)
		{
			int count = 0;
			if (cards[i] / 100 <= 14 && cards[i] / 100 == cards[i + 1] / 100 && cards[i] / 100 == cards[i + 2] / 100)
			{
				count = 1;
				for (int j = 1; j < 100; j++)
				{
					if ((i + 3 * j + 2) < cards.size() && cards[i] / 100 + 1 * j == cards[i + 3 * j] / 100)
					{
						if (cards[i + 3 * j]/100<=14 && cards[i + 3 * j] / 100 == cards[i + 3 * j + 1] / 100 && cards[i + 3 * j] / 100 == cards[i + 3 * j + 2] / 100)
						{
							count++;
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
				if (count >= 2 && cards.size() <= (count * 3 + count * 1))
				{
					return true;
				}
				break;
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}

//二排顺
bool logic_core::IS_ERPAISHUN(std::vector<int> cards)
{
	if (cards.size() >= 6 && cards.size()%2==0)
	{
		if (cards[cards.size() - 1] >= 15)
		{
			return false;
		}
		for (size_t i = 0; i < cards.size() - 2; i+=2)
		{
			if (cards[i] / 100 != cards[i + 1] / 100  || cards[i]/100+1!=cards[i+2]/100)
			{
				return false;
			}
		}
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
	if (cards.size()>=5)
	{
		if (cards[cards.size() - 1]>=15)
		{
			return false;
		}
		for (size_t i = 0; i < cards.size()-1; i++)
		{
			if (cards[i] / 100 + 1 != cards[i + 1] / 100)
			{
				return false;
			}
		}
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

int logic_core::FEN_SHUANGFEI(std::vector<int> cards)	//双飞
{
	return INT_MAX;
}
int logic_core::FEN_ZHADAN(std::vector<int> cards)	//四张牌
{
	return cards[cards.size()-3];
}

int logic_core::FEN_SANPAI(std::vector<int> cards)	//三张牌
{
	return cards[cards.size() - 2];
}

int logic_core::FEN_ERPAI(std::vector<int> cards)	//两张牌
{
	return cards[0];
}
int logic_core::FEN_SIPAISHUN(std::vector<int> cards)	//四排 顺子
{
	for (size_t i = cards.size() - 1; i >= 0; i--)
	{
		if (cards[i] / 100 == cards[i-1] / 100 && cards[i] / 100 == cards[i - 2] / 100 && cards[i] / 100 == cards[i - 3] / 100)
		{
			return cards[i];
		}
	}
	return 0;
}

int logic_core::FEN_SANPAISHUN(std::vector<int> cards)	//三排 顺子
{
	for (size_t i = cards.size() - 1; i >= 0; i--)
	{
		if (cards[i] / 100 == cards[i - 1] / 100 && cards[i] / 100 == cards[i - 2] / 100)
		{
			return cards[i];
		}
	}
	return 0;
}
int logic_core::FEN_ERPAISHUN(std::vector<int> cards)	//二排顺
{
	return cards[cards.size() - 1]/100;
}
int logic_core::FEN_DANPAISHUN(std::vector<int> cards)	//单排顺
{
	return cards[cards.size()-1]/100;
}
int logic_core::FEN_DANPAI(std::vector<int> cards)//单张牌
{
	return cards[0];
}


