#pragma once
#include <boost/unordered_map.hpp>
#include <vector>
struct Landlord_RoomCFGData
{
	//房间id
	int mRoomID;
	//房间名
	std::string mRoomName;
	//是否开放
	bool mIsOpen;
	//房间图片
	std::string mRoomImage;
	//进场VIP条件
	int mVipCondition;
	//进场金币条件
	int mGoldCondition;
};

class Landlord_RoomCFG
{
public:
private:
	static std::auto_ptr<Landlord_RoomCFG> msSingleton;
public:
	int GetCount();
	const Landlord_RoomCFGData* GetData(int RoomID);
	boost::unordered_map<int, Landlord_RoomCFGData>& GetMapData();
	void Reload();
	void Load();
	static Landlord_RoomCFG* GetSingleton();
private:
	boost::unordered_map<int, Landlord_RoomCFGData> mMapData;
};
