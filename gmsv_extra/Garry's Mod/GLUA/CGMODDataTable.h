#ifndef CGMODDATATABLE_H
#define CGMODDATATABLE_H
#ifdef _WIN32
#pragma once
#endif
#include "IGMODDataTable.h"

class CGMODDataTable : public IGMODDataTable
{
public:
	BYTE pad_unk00[4];
	BYTE pad_unk01[32][2];
};


#endif