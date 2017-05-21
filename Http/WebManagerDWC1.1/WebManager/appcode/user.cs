using System.Web.Configuration;
using System.Collections.Generic;

// 登陆GM用户相关
public class GMUser : SysMgr
{
    // 登陆帐号名
    public string m_user = "";
    // 帐号权限
    public string m_right = "";
    // 登陆密码
    public string m_pwd = "";
    public string m_type = "";

    // 登陆的帐号IP
    public string m_ip = "";
    // 要操作的数据库IP
    public string m_dbIP="";
    // GM上挂接的DB，每个GM可以操作的db不同
    private int m_dbId = 0;
    // 设置操作结果
    private string m_opResult = "";
    // 之前的URL
    private string m_preURL = "";
    private long m_totalRecord = 0;

    public string preURL
    {
        get { return m_preURL; }
        set
        {
            if (value != "/appaspx/SelectMachine.aspx")
            {
                m_preURL = value;
            }
        }
    }

    // 用户浏览的总记录个数
    public long totalRecord
    {
        get { return m_totalRecord; }
        set { m_totalRecord = value; }
    }

    public GMUser() { }
    public GMUser(AccountInfo info)
    {
        m_user = info.m_user;
        m_right = info.m_right;
        m_pwd = info.m_pwd;
        m_ip = info.m_ip;
        m_type = info.m_type;
    }

    // 返回挂接的操作DB
    public int getDbServerID()
    {
        return m_dbId;
    }

    // 初始化
    public void init()
    {
        m_dbIP = WebConfigurationManager.AppSettings["account"];
        m_dbId = DBMgr.getInstance().getDbId(m_dbIP);

        addSys(new QueryMgr());
        addSys(new DyOpMgr());
        addSys(new StatMgr());
        addSys(new ExportMgr());
        initSys();
    }

    // 更换要操作的游戏数据库
    public bool changeGameDb(string pools)
    {
        int id = DBMgr.getInstance().getDbId(pools);
        if (id == -1)
        {
            return false;
        }
        m_dbId = id;
        m_dbIP = pools;
        return true;
    }

    public string getOpResultString()
    {
        return m_opResult;
    }

    public void setOpResult(OpRes res)
    {
        m_opResult = OpResMgr.getInstance().getResultString(res);
    }
}


