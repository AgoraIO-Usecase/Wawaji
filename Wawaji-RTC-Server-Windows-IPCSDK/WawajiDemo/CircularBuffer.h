#pragma once
#include "stdafx.h"

/*
	@brief Circularbuffer DataStruct for constant len
	init(size_t ncount);
	BOOL push(const char *data, size_t bytes);//����.
	BOOL pop(char *data, int &bytes);

	@brief Circularbuffer DataStruct for the change len
	BOOL init(size_t capacity,size_t ncount);
	BOOL pushEx(const char *data,size_t bytes);//������
	BOOL popEx(char *data,int &bytes);
*/

class Locker
{
public:
	Locker();

	virtual ~Locker(void);

public:
	void lock(const char *userDesc = NULL);

	void unlock();

	bool tryLock();

private:
	CRITICAL_SECTION	_lock;
	const char	*_userDesc;
};

class AutoLocker
{
public:
	AutoLocker(Locker *locker, const char *userDesc = NULL);

	~AutoLocker();

private:
	Locker	*_locker;
};

class CircularBuffer
{
public:
	~CircularBuffer();
	static CircularBuffer* getinstance();
	void releaseInstance();
	
	BOOL init(size_t ncount);
	BOOL init(size_t capacity,size_t ncount);
	BOOL uninit();
	size_t size() const { return size_; }
	size_t capacity() const { return capacity_; }
	size_t count(){return ncount_;}
	size_t len(){return nlen_;}
	BOOL push(const char *data, size_t bytes);//����.
	BOOL pop(char *data, int &bytes);
	BOOL pushEx(const char *data,size_t bytes);//������
	BOOL popEx(char *data,int &bytes);
	BOOL empty();
	BOOL isFull();
	BOOL isInit();
	BOOL reInit(size_t capacity);

private:
	CircularBuffer(void);
	static CircularBuffer* pInstance_;

private:
	bool isInit_;
	size_t beg_index_; 
	size_t end_index_; 
	size_t size_;
	size_t capacity_;
	size_t ncount_;
	size_t nlen_;
	char *data_;
	size_t *pushLen_;
	Locker lock_;
};
