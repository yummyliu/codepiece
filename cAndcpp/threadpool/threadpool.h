/*=============================================================================
#     FileName: threadpool.h
#         Desc: 
#       Author: LiuYangming
#        Email: sdwhlym@gmail.com
#     HomePage: http://yummyliu.github.io
#      Version: 0.0.1
#   LastChange: 2017-09-07 14:25:57
#      History:
=============================================================================*/
#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <pthread.h>

class CThread
{
public:
	CThread();
	virtual ~CThread();

	static void* StartRoutine(void* arg);
	virtual void StartThread(void);
	virtual void OnThreadRun(void) = 0;
protected:
	pthread_t	m_thread_id;
};

class CEventThread : public CThread
{
public:
	CEventThread();
	virtual ~CEventThread();

 	virtual void OnThreadTick(void) = 0;
	virtual void OnThreadRun(void);
	virtual void StartThread();
	virtual void StopThread();
	bool IsRunning() { return m_bRunning; }
private:
	bool 		m_bRunning;
};

class CThreadNotify
{
public:
	CThreadNotify();
	~CThreadNotify();
	void Lock() { pthread_mutex_lock(&m_mutex); }
	void Unlock() { pthread_mutex_unlock(&m_mutex); }
	void Wait() { pthread_cond_wait(&m_cond, &m_mutex); }
	void Signal() { pthread_cond_signal(&m_cond); }
private:
	pthread_mutex_t 	m_mutex;
	pthread_mutexattr_t	m_mutexattr;

	pthread_cond_t 		m_cond;
};

#endif
