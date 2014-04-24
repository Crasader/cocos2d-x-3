#ifndef ENEMY_MODEL_H
#define ENEMY_MODEL_H

#include "cocos2d.h"
#include "BaserLayer.h"

USING_NS_CC;

enum Monster
{
	monster1 = 0,
	monster2 = 1,
	monster3 = 2,
	monster4 = 3,
	monster5 = 4,
	monster6 = 5
};

class EnemyModel : public CCNode
{
	public:
		EnemyModel(Monster monster,CCPoint targetPoint);
		~EnemyModel();

		bool init();

		static EnemyModel* getEnemy(Monster monster,CCPoint targetPoint);

		void addBullet(float f);
		void moveBullet(float t);

		CCSpriteBatchNode *enemyBatchNode;
		CCArray *bulletArray;

	private:
		CCAction *mAction;
		CCSprite *mSprite;


};

class EnemyManager : public BaserLayer
{
	public:
		EnemyManager();
		~EnemyManager();

		virtual bool init();

		void setViews();	
		CREATE_FUNC(EnemyManager);

		void addEnemy(float t);

		CCArray *getEnemyArray();
		CCArray *enemyArray;
};

#endif
