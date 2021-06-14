#ifndef __Single_Texture_H_
#define __Single_Texture_H_



#include "Texture.h"
class CSingle_Texture :
	public CTexture
{
public:
	explicit CSingle_Texture(void);
	virtual ~CSingle_Texture(void);


public:
	virtual const TEXINFO* Get_TexInfo(const wstring& wstrStateKey = L"", const int& iCount = 0);

public:
	virtual					HRESULT Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey = L"", const int & iCount = 0) override;
	virtual void			Release() override;





private:
	TEXINFO* m_pTexInfo = nullptr;


};

#endif // !__Single_Texture_H_
