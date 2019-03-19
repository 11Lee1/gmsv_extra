#include "../string_t.h"
#include "../iserverentity.h"
class CBaseEntity : public IServerEntity
{
public:
	virtual ~CBaseEntity();
public:
	int entindex() { return 0; }
public:
	string_t name;
};