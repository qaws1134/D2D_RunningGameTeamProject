#ifndef __Multi_Texture_H_
#define __Multi_Texture_H_




#include "Texture.h"
class CMulti_Texture :
	public CTexture
{
public:
	explicit CMulti_Texture(void);
	virtual ~CMulti_Texture(void);

public:
	virtual const TEXINFO * Get_TexInfo(const wstring & wstrStateKey, const int & iCount) override;
	virtual HRESULT			Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey, const int & iCount) override;
	virtual void			Release() override;





private:
	map<wstring, vector<TEXINFO*>> m_mapMulti;


};

#endif // !__Multi_Texture_H_
