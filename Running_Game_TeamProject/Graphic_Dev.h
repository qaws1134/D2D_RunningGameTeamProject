#ifndef __Graphic_Dev_H_
#define __Graphic_Dev_H_


class CGraphic_Dev
{
	DECLARE_SINGLETON(CGraphic_Dev)
private:
	explicit CGraphic_Dev(void);
	explicit CGraphic_Dev(const CGraphic_Dev& rhs) {};
	virtual ~CGraphic_Dev(void);
	void operator=(const CGraphic_Dev& rhs) {};

public:
	HRESULT		Ready_GraphicDev(void);
	void		Release_GraphicDev(void);

public:
	void		Render_Begin(void);
	void		Render_End(HWND hWnd = nullptr);

public:
	LPD3DXSPRITE		Get_Sprite(void) { return m_pSprite; }
	LPDIRECT3DDEVICE9	Get_Device(void) { return m_pGraphicDev; }
	LPD3DXFONT			Get_Font(void) { return m_pFont; }


private:
	LPDIRECT3D9			m_pSDK;
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	LPD3DXSPRITE		m_pSprite;
	LPD3DXFONT			m_pFont;

};

#endif // !__Graphic_Dev_H_
