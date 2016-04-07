
#include "cBicho.h"
class cHeart :
	public cBicho
{
public:
	cHeart(int id,int pos);
	~cHeart();

	virtual void Draw(cData* dat);
private:
	int id, pos;
};

