#pragma once

#include <db_base.h>
#include <enable_singleton.h>

static const std::string DB_LANDLORD_PLAYER = "landlord_player";
static const std::string DB_LANDLORD_ROOM = "landlord_room";

//Íæ¼ÒÊý¾Ý¿â
class db_game : public db_base, public enable_singleton<db_game>
{
public:
	db_game();
	virtual ~db_game();
	virtual void init_index();
};