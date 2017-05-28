#pragma once
#include "proc_game_landlord_protocol.h"
#include "logic_player.h"

class logic_core
{
public:
	logic_core(int);
	void init();
	void send_card();
	std::map<int, std::vector<int>>& get_cards_info() { return m_cardMap; }
	std::vector<int>& get_cards_info(int desk) { return m_cardMap[desk]; }

	int get_openCard() { return mOpenCard; }
	int get_Landlord() { return landlord_id; }
	const std::vector<int>& get_RemainLandlordCards() { return m_RemainlandlordCards; }
	int compare_card(std::vector<int>& cards_1, std::vector<int>& cards_2);
	void playhand(int deskid,std::vector<int>& cards);
	game_landlord_protocol::card_Info logic_core::get_rob_playhand(logic_player* player);
private:
	int rand(int min, int max);
	int take_one_card();
	int getPoint(int type, std::vector<int>& cards);
	int GetPaiType(std::vector<int>& cards);

	bool IS_SHUANGFEI(std::vector<int>& cards);	//双飞
	bool IS_SIZHANGPAI(std::vector<int>& cards);	//四张牌
	bool IS_SANPAI(std::vector<int>& cards);	//三张牌
	bool IS_ERPAI(std::vector<int>& cards);	//两张牌
	bool IS_SIPAISHUN(std::vector<int>& cards);	//四排 顺子
	bool IS_SANPAISHUN(std::vector<int>& cards);	//三排 顺子
	bool IS_ERPAISHUN(std::vector<int>& cards);	//二排顺
	bool IS_DANPAISHUN(std::vector<int>& cards);	//单排顺
	bool IS_DANPAI(std::vector<int>& cards);//单张牌

	int FEN_SHUANGFEI(std::vector<int>& cards);	//双飞
	int FEN_ZHADAN(std::vector<int>& cards);	//四张牌
	int FEN_SANPAI(std::vector<int>& cards);	//三张牌
	int FEN_ERPAI(std::vector<int>& cards);	//两张牌
	int FEN_SIPAISHUN(std::vector<int>& cards);	//四排 顺子
    int FEN_SANPAISHUN(std::vector<int>& cards);	//三排 顺子
	int FEN_ERPAISHUN(std::vector<int>& cards);	//二排顺
	int FEN_DANPAISHUN(std::vector<int>& cards);	//单排顺
	int FEN_DANPAI(std::vector<int>& cards);//单张牌

	int IS_Contain_SHUANGFEI(std::vector<int>& cards);	//双飞
	int IS_Contain_SIZHANGPAI(std::vector<int>& cards, int pai);	//四张牌
	int IS_Contain_SANPAI(std::vector<int>& cards, int pai);	//三张牌
	int IS_Contain_ERPAI(std::vector<int>& cards, int pai);	//两张牌
	int IS_Contain_SIPAISHUN(std::vector<int>& cards, int maxpai);	//四排 顺子
	int IS_Contain_SANPAISHUN(std::vector<int>& cards, int maxpai);	//三排 顺子
	int IS_Contain_ERPAISHUN(std::vector<int>& cards, int maxpai);	//二排顺
	int IS_Contain_DANPAISHUN(std::vector<int>& cards, int maxpai);	//单排顺
	int IS_Contain_DANPAI(std::vector<int>& cards, int pai);//单张牌

	std::vector<int> Get_SHUANGFEI(std::vector<int>& cards);	//双飞
	std::vector<int> Get_SIPAI(std::vector<int>& cards, int pai);	//四张牌
	std::vector<int> Get_SANPAI(std::vector<int>& cards, int pai);	//三张牌
	std::vector<int> Get_ERPAI(std::vector<int>& cards, int pai);	//两张牌
	std::vector<int> Get_DANPAI(std::vector<int>& cards, int pai);//单张牌
	std::vector<int> Get_SIPAISHUN(std::vector<int>& cards, int maxpai);	//四排 顺子
	std::vector<int> Get_SANPAISHUN(std::vector<int>& cards, int maxpai);	//三排 顺子
	std::vector<int> Get_ERPAISHUN(std::vector<int>& cards, int maxpai);	//二排顺
	std::vector<int> Get_DANPAISHUN(std::vector<int>& cards, int maxpai);	//单排顺

	void INIT_PAI_TYPE_MAP(int deskId);

	std::vector<int>& get_ZUIXIAO_PAI(std::vector<int> cards_1);//得到自己手里  最小牌，
	std::vector<int>& get_ZUIXIAO_PAI(std::vector<int>& cards_1, std::vector<int>& cards_2);//得到自己手里  最小牌，
private:
	std::vector<int> m_cards;
	int deskCount;//这个桌子有几个人在打
	int mOpenCard;//取牌前，翻牌确定谁先取牌
	std::map<int, std::vector<int>> m_cardMap;
	std::map<int, std::map<int, std::vector<int>>> m_desk_type_map;
	std::vector<int> m_RemainlandlordCards;//剩下的3张牌
	int landlord_id;
};
