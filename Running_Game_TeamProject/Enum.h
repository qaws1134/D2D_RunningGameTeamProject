#ifndef _Enum_H_
#define _Enum_H_

namespace TEXID
{
	enum ID
	{
		TEX_SINGLE, TEX_MULTI, TEX_END
	};
}


namespace OBJID
{
	enum ID
	{
		PLAYER, OBSTACLE, ITEM, UI, END
	};
}
namespace ITEMID
{
	enum ID
	{
		HEALTH, GIANT, SPEED,COIN, JELLY, END
	};

}

namespace HURDLEID
{
	enum ID
	{
		FLOOR, FLOOR2F, LOWHILL, HIGHHILL, BULLET,BULLET_CRASH, CELLING,END
	};
}

#endif // !_Enum_H_
