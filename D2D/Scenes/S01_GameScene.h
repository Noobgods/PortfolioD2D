#pragma once
#include "Scene.h"

#define BALL_INIT_POS_X -232.0f
#define BALL_INIT_POS_Y -384.0f

#define BALL_LINE_SIZE_X 9
#define BALL_LINE_SIZE_Y 12

#define SCALE_X 4.0f
#define SCALE_Y 4.0f

#define CEILING_Y 330.0f
#define MAX_STAGE 4


enum class State {
	READY = 0, GO, GAME, WIN, LOSE, NEXTSTAGE
};
class S01_GameScene : public Scene {
public:
	S01_GameScene(SceneValues* values);
	~S01_GameScene();

	void Update() override;
	void Render() override;

private:
	UINT RandomSeed();
	void CeilingDown();
	void BubbleStitch(UINT x_, UINT y_);
	void BubbleExplodeCheck(UINT x, UINT y);
	void BubbleExplodeDelete();
	void BubbleAirCheck(UINT x, UINT y);
	void BubbleAirDelete();
	void BubbleDelete();
	void MonsterDelete();

private:
	float fBubbleRotation;		// 버블/발사대 회전각 
	float fRotationSpeed;		// 회전속도
	float fStageTime;
	float fCeilingY;

	Sprite* bubbleBag1;
	Sprite* bubbleBag2;
	Sprite* deadLine;

	class Arrow* arrow;
	class Background* background;
	class LaunchDragon* launchDragon;
	class LaunchingPad* launchingPad;
	class Ceiling* ceiling;

	class Bubble* bubbles[BALL_LINE_SIZE_Y][BALL_LINE_SIZE_X];
	class Bubble* readyBubble;
	class Bubble* waitBubble;
	class Bubble* shootBubble;
	vector<class Bubble*> deleteBubbles;
	vector<class Monster*> deleteMonster;

	Vector2 bubbleLine[BALL_LINE_SIZE_Y][BALL_LINE_SIZE_X];

	bool bCheckBubbles[BALL_LINE_SIZE_Y][BALL_LINE_SIZE_X];
	bool bCheckAirBubbles[BALL_LINE_SIZE_Y][BALL_LINE_SIZE_X];
	State stageState;

	UINT bRemainsColor[9];
	UINT uiStage;
	UINT uiExplodeCount;
	UINT uiOverLine;
	UINT uiCeilingLine;

	float fBubbleShake;
	float fBubbleDistance;
	float fShakeSpeed;
	float temp1 = 0, temp2 = 0;
};