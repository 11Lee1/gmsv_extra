class IMemAlloc;

namespace Interfaces
{
	namespace _I
	{
		IMemAlloc* _memalloc;
	};
	IMemAlloc* MemAlloc() { return _I::_memalloc; }
};