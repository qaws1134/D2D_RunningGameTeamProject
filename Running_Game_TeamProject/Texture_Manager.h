#ifndef __Texture_Manager_H_
#define __Texture_Manager_H_


class CTexture;
class CTexture_Manager
{
	DECLARE_SINGLETON(CTexture_Manager)
private:
	explicit CTexture_Manager(void);
	virtual ~CTexture_Manager(void);
public:
	HRESULT	Insert_Texture(const wstring& wstrObjKey,
								const TEXID::ID& eID,
								const wstring& wstrFilePath,
								const wstring& wstrStateKey = L"",
								const int& iCount = 0);

	const TEXINFO*Get_TexInfo(const wstring& wstrObjKey,
								const wstring& wstrStateKey = L"",
								const int& iCount = 0);
	void Release(void);
private:
	map<wstring, CTexture*>	m_mapTexture;

};

#endif // !__Texture_Manager_H_
