class IMemAlloc
{
public:
	virtual void *Alloc(size_t nSize, const char *pFileName, int nLine) = 0;
	virtual void *Realloc(void *pMem, size_t nSize, const char *pFileName, int nLine) = 0;
	virtual void  Free(void *pMem, const char *pFileName, int nLine) = 0;
	virtual void *Expand_NoLongerSupported(void *pMem, size_t nSize, const char *pFileName, int nLine) = 0;
};