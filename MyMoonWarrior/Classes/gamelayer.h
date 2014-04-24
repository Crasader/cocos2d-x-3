#ifndef GAME_LAYER_H
#define GAME_LAYER_H

#include "cocos2d.h"
#include "BaserLayer.h"
#include "warriorlayer.h"

class GameLayer : public BaserLayer
{
	public:
		GameLayer();
		~GameLayer();

		virtual bool init();

		static CCScene * scene();

		void setViews();
		CREATE_FUNC(GameLayer);

		void background_scroll(float t);
		void pause_game(CCObject *obj);
		void warrior_add_new_bullet(float t);

	private:
		WarriorLayer *mWarrior;
		BulletLayer *bulletManager ;
};

class ScoreLayer : public BaserLayer
{
	public:
		ScoreLayer();
		~ScoreLayer();

		virtual bool init();
		void setViews();

		CREATE_FUNC(ScoreLayer);
};

class TimeLayer : public BaserLayer
{
	public:
		TimeLayer();
		~TimeLayer();

		virtual bool init();
		
		void setViews();

		CREATE_FUNC(TimeLayer);

		void time_count(float t);

	private :
		int count;
};

class PauseLayer : public CCLayerColor
{
	public:
		PauseLayer();
		~PauseLayer();

		virtual bool init();

		void setViews();

		CREATE_FUNC(PauseLayer);
		void play_stats(CCObject *obj);
};

#endif
