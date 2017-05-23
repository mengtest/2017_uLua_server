#include "stdafx.h"
#include "proc_game_landlord_protocol.h"
#include <i_game_player.h>
#include "game_engine.h"
#include "logic_player.h"
using namespace boost;

void init_proc_landlord_protocol()
{
	packetc2l_enter_room_factory::regedit_factory();
	packetl2c_enter_room_result_factory::regedit_factory();

	packetc2l_leave_room_factory::regedit_factory();
	packetl2c_leave_room_result_factory::regedit_factory();

	packetc2l_get_room_scene_info_factory::regedit_factory();
	packetl2c_get_room_scene_info_result_factory::regedit_factory();

	packetc2l_check_state_factory::regedit_factory();
	packetl2c_check_state_result_factory::regedit_factory();

	packetl2c_notice_start_game_factory::regedit_factory();
}

//进入斗地主房间
bool packetc2l_enter_room_factory::packet_process(shared_ptr<peer_tcp> peer, shared_ptr<i_game_player> player,shared_ptr<packetc2l_enter_room> msg)
{	
	__ENTER_FUNCTION_CHECK;
	int ret = game_engine::instance().get_lobby().enter_room(player->get_playerid(), msg->room_id());

	auto sendmsg = PACKET_CREATE(packetl2c_enter_room_result, e_mst_l2c_enter_room);
	sendmsg->set_result((e_server_error_code)ret);
	sendmsg->set_wait_time(30);
	player->send_msg_to_client(sendmsg);

	__LEAVE_FUNCTION_CHECK
		return !EX_CHECK;
}

//离开斗地主房间
bool packetc2l_leave_room_factory::packet_process(shared_ptr<peer_tcp> peer, shared_ptr<i_game_player> player, shared_ptr<packetc2l_leave_room> msg)
{
	__ENTER_FUNCTION_CHECK;

	auto lcplayer = CONVERT_POINT(logic_player, player->get_handler());
	lcplayer->leave_table();

	auto sendmsg = PACKET_CREATE(packetl2c_leave_room_result, e_mst_l2c_leave_room);
	sendmsg->set_result(e_error_code_success);
	player->send_msg_to_client(sendmsg);

	__LEAVE_FUNCTION_CHECK
		return !EX_CHECK;
}

//断线重练 获取场景信息
bool packetc2l_get_room_scene_info_factory::packet_process(shared_ptr<peer_tcp> peer, shared_ptr<i_game_player> player, shared_ptr<packetc2l_get_room_scene_info> msg)
{
	__ENTER_FUNCTION_CHECK;

	auto sendmsg = PACKET_CREATE(packetl2c_get_room_scene_info_result, e_mst_l2c_get_room_scene_info);
	player->send_msg_to_client(sendmsg);

	__LEAVE_FUNCTION_CHECK
		return !EX_CHECK;
}

//检测游戏状态,进入游戏之后判断是否在桌子中
bool packetc2l_check_state_factory::packet_process(shared_ptr<peer_tcp> peer, shared_ptr<i_game_player> player, shared_ptr<packetc2l_check_state> msg)
{
	__ENTER_FUNCTION_CHECK;

	auto sendmsg = PACKET_CREATE(packetl2c_check_state_result, e_mst_l2c_check_state);
	player->send_msg_to_client(sendmsg);

	__LEAVE_FUNCTION_CHECK
		return !EX_CHECK;
}

