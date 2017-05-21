#pragma once
#include <enable_smart_ptr.h>
#include <enable_queue.h>
#include <net/peer_handler.h>

namespace google
{
	namespace protobuf
	{
		class Message;
	};
};

struct msgbuf
{
	msgbuf()
		:packet_id(0)
		,msg(nullptr)
		,need_route(false)
	{
	}
	//msgbuf(const msgbuf& in)
	//{
	//	packet_id = in.packet_id;
	//	msg = in.msg;
	//}
	//msgbuf(uint16_t _packet_id, boost::shared_ptr<google::protobuf::Message> _msg)
	//{
	//	packet_id = _packet_id;
	//	msg = _msg;
	//}
	~msgbuf()
	{
		packet_id = 0;
		msg = nullptr;
		msgbuff.clear();
	}

	uint16_t packet_id;
	boost::shared_ptr<google::protobuf::Message> msg;
	bool need_route;
	std::string msgbuff;
};

struct peer_event
{
	uint16_t peer_id;
	e_peer_event ep_event;

	peer_event()
	{
		peer_id = 0;
		ep_event =  e_pe_disconnected;
	}

	peer_event(uint16_t _id, e_peer_event _event)
	{
		peer_id = _id;
		ep_event = _event;
	}
};



