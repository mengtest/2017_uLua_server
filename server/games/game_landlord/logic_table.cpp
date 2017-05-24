#include "stdafx.h"
#include "logic_table.h"
#include "logic_player.h"
#include "game_db.h"
#include "game_engine.h"
#include "i_game_ehandler.h"
#include <enable_random.h>
#include "game_db_log.h"
#include "msg_type_def.pb.h"
#include <math.h>

using namespace std;

logic_table::logic_table(logic_room* room, int tableId):current_deskId(1), playhand_cdTime(0), sendcard_cdTime(0)
{
	deskCount = 3;
	deskList.resize(deskCount);
	m_room = room;
	gameState = e_game_state::e_game_state_none;
	m_tableId = tableId;
	logic_table_db::init_game_object();
	logic_table_db::m_db_table_id->set_value(m_tableId);
	if (!load_table())
	{
		create_table();
	}
	m_cardManager=new logic_core(deskCount);
}

logic_table::~logic_table(void)
{
	if (m_cardManager != nullptr)
	{
		delete m_cardManager;
		m_cardManager = nullptr;
	}
}

void logic_table::heartbeat(double elapsed)
{
	if (gameState == e_game_state::e_game_state_none)
	{
		if (playerMap.size() > 0)
		{
			gameState = e_game_state::e_game_state_matching;
		}
		return;
	}
	else
	{
		if (playerMap.size() == 0)
		{
			gameState = e_game_state::e_game_state_none;
			return;
		}
	}

	if (gameState == e_game_state::e_game_state_matching)//匹配
	{
		if (playerMap.size() >= deskCount)
		{
			gameState = e_game_state::e_game_state_startgame;
		}	
	}
	else if (gameState == e_game_state::e_game_state_startgame)//开始游戏，发完所有牌
	{
		do_protobuf_notice_start_game();
		gameState = e_game_state::e_game_state_sendcarding;
	}
	else if (gameState == e_game_state::e_game_state_sendcarding)//发牌阶段
	{
		if (sendcard_cdTime > 15.0)
		{
			gameState == e_game_state::e_game_state_robLandlore;
			sendcard_cdTime = 0;
		}
		else
		{
			sendcard_cdTime += elapsed;
		}
	}
	else if (gameState == e_game_state::e_game_state_robLandlore)//叫地主
	{

		
	}
	else if (gameState == e_game_state::e_game_state_playhand)//玩家出牌
	{
		if (playhand_cdTime > 20.0)
		{

			playhand_cdTime = 0.0;
		}
		else
		{
			playhand_cdTime += elapsed;
		}
	}
	else if (gameState == e_game_state::e_game_state_award)//开奖
	{
		do_protobuf_notice_winlose();
		gameState = e_game_state::e_game_state_matching;
	}
}

uint16_t logic_table::get_table_id()
{
	return m_tableId;
}

e_server_error_code logic_table::enter_table(LPlayerPtr player)
{
	if (playerMap.size() >= 3)
	{
		return e_error_code_failed;
	}
	auto it = playerMap.find(player->get_pid());
	if (it != playerMap.end())
	{
		return e_error_code_success;
	}
	playerMap.insert(make_pair(player->get_pid(),player));
	int desk=Find_DeskPos();
	if (desk<=0)
	{
		return e_error_code_failed;
	}
	player->set_deskId(current_deskId);
	SLOG_CRITICAL << "进入桌子成功" << std::endl;
	return e_error_code_success;
}

e_server_error_code logic_table::leave_table(uint32_t playerId)
{
	auto it = playerMap.find(playerId);
	if (it == playerMap.end())
	{
		return e_error_code_success;
	}
	int deskId = it->second->get_deskId();
	if (deskId <= 0)
	{
		return e_error_code_failed;
	}
	deskList[deskId -1] = 0;
	it->second->set_deskId(0);
	playerMap.erase(it);
	m_room->leave_room(playerId);
	return e_error_code_success;
}

int logic_table::Find_DeskPos()
{
	for (size_t i = 0; i <deskList.size(); i++)
	{
		if (deskList[i] == 0)
		{
			return i+1;
		}
	}
	return -1;
}

e_game_state logic_table::get_table_State()
{
	return gameState;
}

bool logic_table::check_playhand(const game_landlord_protocol::card_Info& cards)
{
	if (cards.cards_size() == 0)
	{
		return true;
	}

	std::vector<int> m_cards;
	for (int i = 0; i < cards.cards_size(); i++)
	{
		m_cards.push_back(cards.cards().Get(i));
	}
	int result=m_cardManager->compare_card(m_cards,lastPlayhand);
	if (result <= 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void logic_table::do_protobuf_notice_start_game()//开始游戏
{
	SLOG_CRITICAL << "开始游戏" << std::endl;

	m_cardManager->send_card();
	auto sendmsg = PACKET_CREATE(packetl2c_notice_startgame, e_mst_l2c_notice_startgame);

	std::map<int, vector<int>> m_cards = m_cardManager->get_cards_info();
	for (auto& var : m_cards)
	{
		auto cards=sendmsg->add_cards();
		cards->set_deskid(var.first);
		for (auto& var1 : var.second)
		{
			cards->add_cards(var1);
		}
	}

	int openCard=m_cardManager->get_openCard();
	sendmsg->set_opencard(openCard);

	for (auto& var : playerMap)
	{
		auto player= sendmsg->add_playerlist();
		player->set_deskid(var.second->get_deskId());
		player->set_player_id(var.second->get_pid());
		player->set_player_nickname(var.second->get_nickname());
		player->set_player_head_frame(var.second->get_head_frame_id());
		player->set_player_gold(var.second->get_gold());
		player->set_player_sex(var.second->get_player_sex());
		player->set_player_vip_lv(var.second->get_viplvl());
	}

	int landlord_deskId = m_cardManager->get_Landlord();
	sendmsg->set_landlord_id(landlord_deskId);

	broadcast_msg_to_client(sendmsg);	
}

void logic_table::do_protobuf_notice_playhand(const game_landlord_protocol::card_Info& cards)//通知 出牌信息
{
	auto sendmsg = PACKET_CREATE(packetl2c_notice_playhand, e_mst_l2c_notice_playhand);
	sendmsg->mutable_cards()->CopyFrom(cards);
	broadcast_msg_to_client(sendmsg);

	playhand_cdTime = 0.0;
}
void logic_table::do_protobuf_notice_robLandlord()//通知 某某抢地主
{
	auto sendmsg = PACKET_CREATE(packetl2c_notice_rob_landlord, e_mst_l2c_notice_rob_landlord);
	broadcast_msg_to_client(sendmsg);
}
void logic_table::do_protobuf_notice_winlose()//通知 开奖
{
	auto sendmsg = PACKET_CREATE(packetl2c_notice_winlose, e_mst_l2c_notice_winlose);
	broadcast_msg_to_client(sendmsg);
}






void logic_table_db::create_table()
{

}

//房间数据是要保存到数据库的
bool logic_table_db::load_table()
{
	mongo::BSONObj b = db_game::instance().findone(DB_LANDLORD_TABLE, BSON("table_id" << m_db_table_id->get_value()));
	//如果刚开始数据里没有这个数据
	if (b.isEmpty())
		return false;
	return from_bson(b);
}

void logic_table_db::init_game_object()
{
	m_db_table_id = CONVERT_POINT(Tfield<int16_t>, regedit_tfield(e_got_int16, "table_id"));
}

bool logic_table_db::store_game_object(bool to_all)
{
	if (!has_update())
		return true;

	auto err = db_game::instance().update(DB_LANDLORD_ROOM, BSON("room_id" << m_db_table_id->get_value()), BSON("$set" << to_bson(to_all)));
	if (!err.empty())
	{
		SLOG_ERROR << "logic_room::store_game_object :" << err;
		return false;
	}

	return true;
}







