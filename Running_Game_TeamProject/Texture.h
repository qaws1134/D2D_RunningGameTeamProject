#ifndef __Texture_H_
#define __Texture_H_




class CTexture
{
public:
	explicit CTexture(void);
	virtual ~CTexture(void);


public:
	virtual const TEXINFO* Get_TexInfo(const wstring& wstrStateKey = L"", const int& iCount = 0)PURE;
public:
	virtual HRESULT Insert_Texture(const wstring& wstrFilePath,
									// MultiTexture
									const wstring& wstrStateKey = L"",
									const int& iCount = 0)PURE;
									virtual void Release() PURE;

};

#endif // !__Texture_H_
