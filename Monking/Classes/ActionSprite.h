#ifndef ACTION_SPRITE_H
#define ACTION_SPRITE_H
#include "cocos2d.h"

USING_NS_CC;

typedef enum _ActionState
{
	ACTION_NONE,
	ACTION_IDLE,
	ACTION_ATTACK,
	ACTION_HURT,
	ACTION_DEAD,
	ACTION_WALK
}ActionState;

typedef struct 
{
	
	CCRect actual;
	CCRect original;

}BoundBox;


class ActionSprite : public CCSprite
{
public :
	ActionSprite();
	~ActionSprite();

	virtual bool init();


	void idle();
	void attack();
	void hurtWithDanage(float danage);
	void dead();
	void walkWithDirection(CCPoint point);

	void updateDesiredPosition(float dt);

	BoundBox  createBoundBoxWithOrigin(CCPoint origin,CCSize size);
	void tranfromBoxes();
	virtual void setPosition(CCPoint pos);

	CCAction *idleAction;
	CCAction *attackAction;
	CCAction *hurtAction;
	CCAction *deadAction;
	CCAction *walkAction;

	ActionState actionState;

	float walkSpeed;
	float hitPoints;
	float danage;
	CCPoint velocity;
	CCPoint desritePoint;
	float centerToSlide;
	float centerToBottom;

	BoundBox hitBox;
	BoundBox attackBox;

};

#endif