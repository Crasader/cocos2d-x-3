#include "ActionSprite.h"

class Robot : public ActionSprite
{
public:
	Robot(void);
	~Robot(void);

	CREATE_FUNC(Robot);

	virtual bool init();

	float nextDecisionTime;  //��һ������������ѡ���ʱ��
};