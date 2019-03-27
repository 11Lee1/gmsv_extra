//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Random number generator
//
// $Workfile: $
// $NoKeywords: $
//===========================================================================//

#ifndef VSTDLIB_RANDOM_H
#define VSTDLIB_RANDOM_H

#include "../tier0/platform.h"
#include "../tier0/basetypes.h"
#include "../tier0/threadtools.h"
#include "../tier1/interface.h"

#define NTAB 32

#pragma warning(push)
#pragma warning( disable:4251 )

//-----------------------------------------------------------------------------
// A generator of uniformly distributed random numbers
//-----------------------------------------------------------------------------
class IUniformRandomStream
{
public:
	// Sets the seed of the random number generator
	virtual void	SetSeed(int iSeed) = 0;

	// Generates random numbers
	virtual float	RandomFloat(float flMinVal = 0.0f, float flMaxVal = 1.0f) = 0;
	virtual int		RandomInt(int iMinVal, int iMaxVal) = 0;
	virtual float	RandomFloatExp(float flMinVal = 0.0f, float flMaxVal = 1.0f, float flExponent = 1.0f) = 0;
};


//-----------------------------------------------------------------------------
// The standard generator of uniformly distributed random numbers
//-----------------------------------------------------------------------------
class CUniformRandomStream : public IUniformRandomStream
{
public:
	CUniformRandomStream();

	// Sets the seed of the random number generator
	virtual void	SetSeed(int iSeed);

	// Generates random numbers
	virtual float	RandomFloat(float flMinVal = 0.0f, float flMaxVal = 1.0f);
	virtual int		RandomInt(int iMinVal, int iMaxVal);
	virtual float	RandomFloatExp(float flMinVal = 0.0f, float flMaxVal = 1.0f, float flExponent = 1.0f);

private:
	int		GenerateRandomNumber();

	int		m_idum;
	int		m_iy;
	int		m_iv[NTAB];

	CThreadFastMutex m_mutex;
};

#endif // VSTDLIB_RANDOM_H
