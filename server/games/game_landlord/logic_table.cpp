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

logic_table::logic_table(logic_room* room, int tableId) :current_deskId(1), playhand_cdTime(0), sendcard_cdTime(0), roblandlord_cdTime(0)
	,m_room(nullptr)
	,robCount(0)
	,createRob_time(0)
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
			bool allPrepare = true;
			for(auto& var: playerMap)
			{
				if (var.second->get_deskId() > 0 && var.second->get_deskId() <= deskCount)
				{
					if (var.second->get_player_game_state() != e_player_game_state::e_player_game_state_matching)
					{
						allPrepare = false;
						break;
					}
				}
				else
				{
					allPrepare = false;
					break;
				}
			}
			if (allPrepare)
			{
				gameState = e_game_state::e_game_state_startgame;
			}
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
			gameState = e_game_state::e_game_state_robLandlore;
			do_protobuf_notice_robLandlord();
			sendcard_cdTime = 0;
		}
		else
		{
			sendcard_cdTime += elapsed;
		}
	}
	else if (gameState == e_game_state::e_game_state_robLandlore)//叫地主
	{
		if (roblandlord_cdTime > 20.0)
		{
			for (auto& var : playerMap)
			{
				if (var.second->get_deskId() == current_robLandlord_Id)
				{
					rob_Landlord(var.second.get(),2);
					break;
				}
			}
			roblandlord_cdTime = 0.0;
		}else
		{
			roblandlord_cdTime += elapsed;
		}	
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
		gameState = e_game_state::e_game_state_none;
		for (auto& var : playerMap)
		{
			var.second->set_player_game_state(e_player_game_state::e_player_game_state_none);
		}
	}

	/*if (robCount < deskCount - 1)
	{
		if (createRob_time > 1.0)
		{
			game_engine::instance().request_robot(m_room->get_room_id()*1000+get_table_id(), global_random::instance().rand_int(10000, 100000), global_random::instance().rand_int(0, 3));
			createRob_time = 0.0;
		}
		createRob_time += elapsed;
	}*/
}

uint16_t logic_table::get_table_id()
{
	return m_tableId;
}

bool logic_table::check_ExistRealPlayer()
{
	for (auto& var : playerMap)
	{
		if (!var.second->is_robot())
		{
			return true;
		}
	}
	return false;
}

e_server_error_code logic_table::enter_table(LPlayerPtr player)
{
	if (get_orFull())
	{
		SLOG_CRITICAL << "桌子满了";
		return e_error_code_failed;
	}
	auto it = playerMap.find(player->get_pid());
	if (it != playerMap.end())
	{
		SLOG_CRITICAL << "玩家已经在桌子里了";
		return e_error_code_success;
	}
	playerMap.insert(make_pair(player->get_pid(),player));
	int deskId=Find_DeskPos();
	if (deskId<=0)
	{
		SLOG_CRITICAL << "没有找到凳子";
		return e_error_code_failed;
	}
	deskList[deskId - 1] = 1;
	player->set_table(this);
	player->set_deskId(deskId);
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
	playerMap.erase(it);
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

bool logic_table::get_orFull()
{
	return playerMap.size() >= deskCount;
}

void logic_table::rob_Landlord(logic_player* player,int orRob)
{
	if (current_robLandlord_Id > deskCount)
	{
		current_robLandlord_Id = 0;
	}

	int landlord_id = m_cardManager->get_Landlord();
	if (landlord_id>1 && current_robLandlord_Id == landlord_id - 1 || landlord_id == 1 && current_robLandlord_Id == deskCount)
	{
		gameState = e_game_state::e_game_state_playhand;
	}
	else
	{
		if (orRob == 2)
		{
			do_protobuf_notice_robLandlord_result(player, orRob);
			do_protobuf_notice_robLandlord();
			current_robLandlord_Id++;
		}
		else if (orRob == 1)
		{
			do_protobuf_notice_robLandlord_result(player, orRob);
			gameState = e_game_state::e_game_state_playhand;
		}
	}
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
		m_cardManager->playhand(cards.deskid(),m_cards);
		if (m_cardManager->get_cards_info(cards.deskid()).size() == 0)
		{
			do_protobuf_notice_winlose(cards.deskid());
			gameState = e_game_state::e_game_state_award;
		}
		return true;
	}
}

void logic_table::do_protobuf_notice_start_game()//开始游戏
{
	SLOG_CRITICAL << "开始游戏" << std::endl;

	m_cardManager->send_card();
	current_robLandlord_Id = m_cardManager->get_Landlord();

	auto sendmsg = PACKET_CREATE(packetl2c_notice_startgame, e_mst_l2c_notice_startgame);
	int openCard=m_cardManager->get_openCard();
	sendmsg->set_opencard(openCard);

	const std::vector<int>& m_remainLandlord_cards = m_cardManager->get_RemainLandlordCards();
	for (auto& var : m_remainLandlord_cards)
	{
		sendmsg->add_cards_1(var);
	}

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

	std::map<int, vector<int>>& m_cards = m_cardManager->get_cards_info();
	for (auto& var : playerMap)
	{
		sendmsg->clear_cards();
		std::vector<int>& m_cards = m_cardManager->get_cards_info(var.second->get_deskId());
		for (auto& var1 : m_cards)
		{
			sendmsg->add_cards(var1);
		}
		var.second->send_msg_to_client(sendmsg);
	}	
}

void logic_table::do_protobuf_notice_playhand(const game_landlord_protocol::card_Info& cards)//通知  出牌信息
{
	auto sendmsg = PACKET_CREATE(packetl2c_notice_playhand, e_mst_l2c_notice_playhand);
	sendmsg->mutable_cards()->CopyFrom(cards);
	broadcast_msg_to_client(sendmsg);

	playhand_cdTime = 0.0;
}
void logic_table::do_protobuf_notice_robLandlord()//通知 某某抢地主
{
	for (auto& var : playerMap)
	{
		if (!var.second->is_robot())
		{
			if (var.second->get_deskId() == current_robLandlord_Id)
			{
				auto sendmsg = PACKET_CREATE(packetl2c_notice_rob_landlord, e_mst_l2c_notice_rob_landlord);
				var.second->send_msg_to_client(sendmsg);
				break;
			}
		}
	}
}

void logic_table::do_protobuf_notice_robLandlord_result(logic_player* player,int orRob)//通知 其他人抢地主的结果
{
	auto sendmsg = PACKET_CREATE(packetl2c_notice_rob_landlord_result, e_mst_l2c_notice_rob_landlord_result);
	sendmsg->set_deskid(player->get_deskId());
	sendmsg->set_or_rob(orRob);
	broadcast_msg_to_client(sendmsg, player->get_pid());
}

void logic_table::do_protobuf_notice_winlose(int deskId)//通知 开奖
{
	auto sendmsg = PACKET_CREATE(packetl2c_notice_winlose, e_mst_l2c_notice_winlose);
	sendmsg->set_win_deskid(deskId);
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







