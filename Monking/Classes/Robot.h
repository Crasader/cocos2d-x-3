#include "ActionSprite.h"

class Robot : public ActionSprite
{
public:
	Robot(void);
	~Robot(void);

	CREATE_FUNC(Robot);

	virtual bool init();

	float nextDecisionTime;  //下一个机器人做出选择的时间
};