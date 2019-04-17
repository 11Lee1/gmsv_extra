#ifndef IGMODDATATABLE_H
#define IGMODDATATABLE_H
#ifdef _WIN32
#pragma once
#endif
class CGMODVariant;
class IGMODDataTable
{
public: // finish me
	virtual void GetKey(int) = 0;
	virtual void GetValue(int key) = 0;
	virtual void IncrementIterator(int&) = 0;
	virtual void Get(int) = 0;
	virtual void Set(int, CGMODVariant const &) = 0;
	virtual void HasKey(int) = 0;
	virtual void GetLocal(char const*) = 0;
	virtual void SetLocal(char const*, CGMODVariant const &) = 0;
	virtual void ClearLocal(char const*) = 0;
	virtual void Clear() = 0;
	virtual void Begin() = 0;
	virtual void End() = 0;
};

#endif