#pragma once
#include "logic_def.h"
#include "logic_core.h"
#include "proc_game_landlord_protocol.h"

class logic_table_db :public game_object
{
protected:
	void create_table();
	bool load_table();
public:
	virtual void init_game_object() override;//注册属性
	virtual bool store_game_object(bool to_all = false) override;//非数组对象必须实现此接口
	Tfield<int16_t>::TFieldPtr		m_db_table_id;			//房间id
};

enum TableState
{
	TableState_None = 0,
	TableState_Prepare= 1,
	TableState_Gameing = 2,
};

class logic_table :public logic_table_db
{
public:
	logic_table(logic_room*,int);
	~logic_table(void);

	void heartbeat(double elapsed);
	uint16_t get_table_id();			//房间ID

	e_server_error_code enter_table(LPlayerPtr player);		//进入房间
	e_server_error_code leave_table(uint32_t playerid);			//离开房间

	TableState get_table_state();
private:
	void do_protobuf_notice_start_game();//通知开始玉溪
public:
	template<class T>
	int broadcast_msg_to_client(T msg, uint32_t except_id = 0)
	{
		std::vector<uint32_t> pids;
		for (auto it=playerMap.begin(); it != m_room_players.end(); it++)
		{
			if (!it->second->is_inTable() && it->second->get_pid() != except_id && !it->second->is_robot())
			{
				pids.push_back(it->second->get_pid());
			}
		}
		game_engine::instance().get_handler()->broadcast_msg_to_client(pids, msg->packet_id(), msg);
	}
private:
	std::map<int, LPlayerPtr> playerMap;		//凳子是key,所有玩家字典
	int32_t m_tableId;
	e_game_state gameState;
	int32_t current_deskId;
	logic_room* m_room;
	logic_core* m_cardManager;
	int deskCount;
};