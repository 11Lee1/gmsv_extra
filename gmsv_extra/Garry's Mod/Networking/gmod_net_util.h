#ifndef GMOD_NET_UTIL_H
#define GMOD_NET_UTIL_H

extern int NetworkstringTableID;

void GUTIL_AddNetworkString(char const* name);

#define util_AddNetworkString(name)	\
	GUTIL_AddNetworkString(name);	\

#endif