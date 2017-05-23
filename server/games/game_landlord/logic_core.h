#pragma once
#include "proc_game_landlord_protocol.h"


class logic_core
{
public:
	logic_core(int);
	void init();
	void send_card();
private:
	int rand(int min, int max);
	int take_one_card();
	int compare_card(std::vector<int> cards_1, std::vector<int> cards_2);
	int getPoint(std::vector<int> cards);

	bool logic_core::IS_SHUANGFEI(std::vector<int> cards);	//双飞
	bool logic_core::IS_ZHADAN(std::vector<int> cards);	//四张牌
	bool logic_core::IS_SIDAIYI(std::vector<int> cards);	//四带1
	bool logic_core::IS_SIDAIER(std::vector<int> cards);	//四带二
	bool logic_core::IS_SANPAI(std::vector<int> cards);	//三张牌
	bool logic_core::IS_SANDAIYI(std::vector<int> cards);	//三带1
	bool logic_core::IS_DUIPAI(std::vector<int> cards);	//两张牌
	bool logic_core::IS_SIPAISHUN(std::vector<int> cards);	//四排 顺子
	bool logic_core::IS_SANPAISHUN(std::vector<int> cards);	//三排 顺子
	bool logic_core::IS_ERPAISHUN(std::vector<int> cards);	//二排顺
	bool logic_core::IS_DANPAISHUN(std::vector<int> cards);	//单排顺
	bool logic_core::IS_DANPAI(std::vector<int> cards);//单张牌
private:
	std::vector<int> m_cards;
	int deskCount;//这个桌子有几个人在打
	int mOpenCard;//取牌前，翻牌确定谁先取牌
	std::map<int, std::vector<int>> m_cardMap;
};
