#ifndef ANIMATION_H
#define ANIMATION_H

#include "node.h"
#include "textMarker.h"
enum EAnimType
{
	AT_NONE,
	AT_ADDLONE,
	AT_ADDFRONT,
	AT_ADDREAR,
	AT_ADDITH,
	AT_REMLONE,
	AT_REMFRONT,
	AT_REMREAR,
	AT_REMITH
};

enum EAnimStatus
{
	AS_OFF,
	AS_ON,
	AS_FINISHED

};
class Animation
{
public:
	Animation();
	void initAddLone(Node* pLimbo, TextMarker* pTextFront, TextMarker* pTextRear, TextMarker* pTextNull);
	void initAddFront(Node* pLimbo, Node* pFront, TextMarker* pTextFront);
	void initAddRear(Node* pLimbo, Node* pRear, TextMarker* pTextRear, TextMarker* pTextNull);
	void initRemLone(Node* pLimbo, TextMarker* pTextFront, TextMarker* pTextRear, TextMarker* pTextNull);
	void initRemFront(Node* pLimbo, Node* pNodeAfter, TextMarker* pTextFront);
	void initRemRear(Node* pLimbo, Node* pNodeBefore, Node* pFront, TextMarker* pTextIter, TextMarker* pTextRear, TextMarker* pTextNull);
	void initAddBeforeIth(Node* pLimbo, Node* pNodeBefore, Node* pFront, TextMarker* pTextIter);
	void initRemIth(Node* pLimbo, Node* pNodeBefore, Node* pFront, TextMarker* pTextIter);

	void update(sf::Time dt);
	EAnimStatus getStatus();
	std::string step();
	void endAnim();
private:
	void clearAll();
	void playAddLone();
	void playAddFront();
	void playAddRear();
	void playRemoveLone();
	void playRemoveFront();
	void playRemoveRear();
	void playAddBeforeIth();
	void playRemoveIth();


	//pointers to affected objects
	Node* limbo;
	Node* front;
	Node* rear;
	Node* nodeBefore;
	Node* nodeAfter;
	TextMarker* textIter;
	TextMarker* textFront;
	TextMarker* textRear;
	TextMarker* textNull;

	int animStep;
	float elapsedTime;
	EAnimType type;
	EAnimStatus status;

	std::string procedure;

	float textYoffset;
	float iterOffset;
};
#endif