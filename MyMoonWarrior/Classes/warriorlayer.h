#ifndef WARRIOR_LAYER_h
#define WARRIOR_LAYER_h

#include "BaserLayer.h"

class WarriorLayer : public BaserLayer
{
	public:
		WarriorLayer();
		~WarriorLayer();

		virtual bool init();

		CREATE_FUNC(WarriorLayer);

		void setViews();

		virtual bool ccTouchBegan(CCTouch *pTouch,CCEvent *event);
		virtual void registerWithTouchDispatcher(void);

		CCPoint getWarriorPostion();
		CCSize getFlySize();

	private:
		CCSprite *warrior;
};

class BulletLayer : public BaserLayer
{
	public:
		BulletLayer();
		~BulletLayer();

		virtual bool init();

		CREATE_FUNC(BulletLayer);

		void setViews();

		void addBullet(const CCPoint startPoint,CCSize flySize);
//		void addBullet(float t );
		void moveAllBullet(float t);

	private:
		CCSpriteBatchNode *mBulletNode;
		CCArray *bulletArray;
};

#endif
