#ifndef DBPOOL_H_
#define DBPOOL_H_

#include <mysql.h>

#define MAX_ESCAPE_STRING_LEN	10240
#define CONNECT_TIMEOUT         15000  // 15s

class CResultSet {
public:
	CResultSet(MYSQL_RES* res);
	virtual ~CResultSet();
	bool Next();
	int GetInt(const char* key);
	char* GetString(const char* key);

private:
	int _GetIndex(const char* key);
    uint64_t            m_count;      // field num for Select, affect num for update
	MYSQL_RES* 			m_res;        // NULL if Update
	MYSQL_ROW			m_curent_row; // typedef char** MYSQL_ROW
	map<string, int>	m_key_map;    // key -> index in row
};

class CPrepareStatement {
public:
	CPrepareStatement();
	virtual ~CPrepareStatement();

	bool Init(MYSQL* mysql, string& sql);

	void SetParam(uint32_t index, int& value);
	void SetParam(uint32_t index, uint32_t& value);
    void SetParam(uint32_t index, string& value);
    void SetParam(uint32_t index, const string& value);

	bool ExecuteUpdate();
	uint32_t GetInsertId();
private:
	MYSQL_STMT*	m_stmt;
	MYSQL_BIND*	m_param_bind;
	uint32_t	m_param_cnt;
};

class CDBPool;

class CDBConn {
public:
	CDBConn(CDBPool* pDBPool);
	virtual ~CDBConn();
	int Init();
	CResultSet* ExecuteQuery(const char* sql_query);
	bool ExecuteUpdate(const char* sql_query);
	// CResultSet* PrepareExecuteQuery(const char* sql_query);
	bool PrepareExecuteUpdate(const char* sql_query);
    /*
     * Based charset of thie conn, get the escape string of $content
     * if one SQL has one str, it maybe need to convert, send set in SQL
     * see this for help: https://codereview.stackexchange.com/questions/71932/my-method-of-escaping-mysql-strings-in-c
     */
	char* EscapeString(const char* content, uint32_t content_len);

	uint32_t GetInsertId();
	const char* GetPoolName();
	MYSQL* GetMysql() { return m_mysql; }

private:
	CDBPool* 	m_pDBPool;
	MYSQL* 		m_mysql;
	char		m_escape_string[MAX_ESCAPE_STRING_LEN + 1];

    uint64_t    m_last_query_time;
};

class CDBPool {
public:
	CDBPool(const char* pool_name,
            const char* db_server_ip,
            uint16_t    db_server_port,
			const char* username,
            const char* password,
            const char* db_name,
            int max_conn_cnt);
	virtual ~CDBPool();

	int Init();
	CDBConn* GetDBConn();
	void RelDBConn(CDBConn* pConn);

	const char* GetPoolName() { return m_pool_name.c_str(); }
	const char* GetDBServerIP() { return m_db_server_ip.c_str(); }
	uint16_t    GetDBServerPort() { return m_db_server_port; }
	const char* GetUsername() { return m_username.c_str(); }
	const char* GetPasswrod() { return m_password.c_str(); }
	const char* GetDBName() { return m_db_name.c_str(); }
private:
	string 		m_pool_name;
	string 		m_db_server_ip;
	uint16_t	m_db_server_port;
	string 		m_username;
	string 		m_password;
	string 		m_db_name;
	int			m_db_cur_conn_cnt;
	int 		m_db_max_conn_cnt;

    list<CDBConn*>  m_busy_list;
	list<CDBConn*>	m_free_list;
    // a lock for multi-thread
	ThreadNotify	m_free_notify;
};

typedef struct {
    string name;
    string host;
    uint32_t port;
    string dbname;
    string username;
    string password;
    uint32_t maxconncnt;
}DbConfig;

/*
 * manage db pool
 * user can use this manager different db for different use
 * ex. (master for write and slave for read)
 */
class CDBManager {
public:
	virtual ~CDBManager();
	static CDBManager* getInstance();

	CDBConn* GetDBConn(const char* dbpool_name);
	void RelDBConn(CDBConn* pConn);

private:
	CDBManager();
	int _init(DbConfig* DBs, uint32_t count);

private:
    // key: dbpool_name
	map<string, CDBPool*>	m_dbpool_map;
};
