#pragma once
#include <boost/unordered_map.hpp>
#include <vector>
struct M_GameCFGData
{
	//key
	int mID;
	//游戏名字
	std::string mGameName;
	//游戏路径
	std::string mGamePrefix;
	//更新地址
	std::string mUpdateUrl;
	//是否开放
	bool mIsOpen;
	//游戏大小
	std::string mGameSize;
	//zip版本
	std::string mZipVersion;
	//动画名称
	std::string mAnimationName;
	//图片名称
	std::string mPictureName;
	//是否显示
	bool mIsShow;
	//显示序号
	int mShowIndex;
	//进入金币要求
	int mEnterGold;
	//进入VIP
	int mEnterVIP;
};

class M_GameCFG
{
public:
private:
	static std::auto_ptr<M_GameCFG> msSingleton;
public:
	int GetCount();
	const M_GameCFGData* GetData(int ID);
	boost::unordered_map<int, M_GameCFGData>& GetMapData();
	void Reload();
	void Reload(const std::string& path);
	void Load(const std::string& path);
	void Load();
	static M_GameCFG* GetSingleton();
private:
	boost::unordered_map<int, M_GameCFGData> mMapData;
};
