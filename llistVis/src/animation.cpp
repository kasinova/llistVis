#include "..\include\animation.h"



Animation::Animation()
{
	textYoffset = -60.0f;
	iterOffset = -72.0f;
	clearAll();
}

void Animation::clearAll()
{
	limbo = NULL;
	front = NULL;
	rear = NULL;
	nodeBefore = NULL;
	nodeAfter = NULL;
	textIter = NULL;
	textFront = NULL;
	textRear = NULL;
	textNull = NULL;

	elapsedTime = 0.0f;
	animStep = -1;
	type = AT_NONE;
	status = AS_OFF;

	procedure = "";
}
std::string Animation::step()
{
	//initially set to -1 so step first
	animStep++;
	
	switch (type)
	{
	case AT_ADDLONE:
		playAddLone();
		break;
	case AT_ADDITH:
		playAddBeforeIth();
		break;
	case AT_ADDFRONT:
		playAddFront();
		break;
	case AT_ADDREAR:
		playAddRear();
		break;
	case AT_REMLONE:
		playRemoveLone();
		break;
	case AT_REMFRONT:
		playRemoveFront();
		break;
	case AT_REMREAR:
		playRemoveRear();
		break;
	case AT_REMITH:
		playRemoveIth();
		break;
	}

	return procedure;
}
void Animation::endAnim()
{
	clearAll();
}

void Animation::update(sf::Time dt)
{
	if (status == AS_ON)
	{
		limbo->update(dt);
	}
	else //if the animation is not running, these are the correct positions for updated list
	{
		elapsedTime = 0.0f;
		animStep = -1;
	}
}

EAnimStatus Animation::getStatus()
{
	return status;
}
void Animation::initAddLone(Node* pLimbo, TextMarker* pTextFront, TextMarker* pTextRear, TextMarker* pTextNull)
{
	limbo = pLimbo;
	textFront = pTextFront;
	textRear = pTextRear;
	textNull = pTextNull;

	type = AT_ADDLONE;
	status = AS_ON;
}
void Animation::initAddFront(Node* pLimbo, Node* pFront, TextMarker* pTextFront)
{
	limbo = pLimbo;
	front = pFront; 
	textFront = pTextFront;

	type = AT_ADDFRONT;
	status = AS_ON;
}
void Animation::initAddRear(Node* pLimbo, Node* pRear, TextMarker* pTextRear, TextMarker* pTextNull)
{
	limbo = pLimbo;
	rear = pRear;
	textRear = pTextRear;
	textNull = pTextNull;
	
	type = AT_ADDREAR;
	status = AS_ON;
}
void Animation::initRemLone(Node* pLimbo, TextMarker* pTextFront, TextMarker* pTextRear, TextMarker* pTextNull)
{
	limbo = pLimbo;
	textFront = pTextFront;
	textRear = pTextRear;
	textNull = pTextNull;

	type = AT_REMLONE;
	status = AS_ON;
}
void Animation::initRemFront(Node* pLimbo, Node* pNodeAfter, TextMarker* pTextFront)
{
	limbo = pLimbo;
	nodeAfter = pNodeAfter;
	textFront = pTextFront;

	type = AT_REMFRONT;
	status = AS_ON;
}
void Animation::initRemRear(Node* pLimbo, Node* pNodeBefore, Node* pFront, TextMarker* pTextIter, TextMarker* pTextRear, TextMarker* pTextNull)
{
	limbo = pLimbo;
	nodeBefore = pNodeBefore;
	front = pFront;
	textIter = pTextIter;
	textRear = pTextRear;
	textNull = pTextNull;

	textIter->setVisible(true);
	textIter->setPosition(front->getPosition());
	textIter->addConstraint(*front, sf::Vector2f(0.0f, iterOffset));

	type = AT_REMREAR;
	status = AS_ON;
}

void Animation::initAddBeforeIth(Node* pLimbo, Node* pNodeBefore, Node* pFront, TextMarker* pTextIter)
{
	limbo = pLimbo;
	nodeBefore = pNodeBefore;
	front = pFront;
	textIter = pTextIter;

	textIter->setVisible(true);
	textIter->setPosition(front->getPosition());
	textIter->addConstraint(*front, sf::Vector2f(0.0f, iterOffset));

	type = AT_ADDITH;
	status = AS_ON;
}

void Animation::initRemIth(Node* pLimbo, Node* pNodeBefore, Node* pFront, TextMarker* pTextIter)
{
	limbo = pLimbo;
	nodeBefore = pNodeBefore;
	front = pFront;
	textIter = pTextIter;

	textIter->setVisible(true);
	textIter->setPosition(front->getPosition());
	textIter->addConstraint(*front, sf::Vector2f(0.0f, iterOffset));

	type = AT_REMITH;
	status = AS_ON;
}
void Animation::playAddLone()
{
	switch (animStep)
	{
	case 0:
		textFront->setColor(sf::Color::Green);
		textFront->addConstraint(*limbo, sf::Vector2f(0.0f, textYoffset), LA_CENTERTOP);

		procedure = "front = newNode;";
		break;
	case 1:
		textFront->setColor(sf::Color::Black);
		textRear->setColor(sf::Color::Green);
		textRear->addConstraint(*limbo, sf::Vector2f(0.0f, textYoffset), LA_CENTERTOP);

		procedure = "rear = newNode;";
		break;
	case 2:
		textRear->setColor(sf::Color::Black);
		limbo->createLine(*textNull, sf::Color::Green);
		limbo->setLineVisibility(true);

		procedure = "newNode->setNext(NULL);";
		break;
	case 3:
		limbo->setState(EState::ES_INLIST);
		limbo->setLineColor(sf::Color::Black);
		status = AS_FINISHED;

		procedure = "Procedure Finished.";
		break;
	}

}
void Animation::playAddFront()
{

	switch (animStep)
	{
	case 0:
		limbo->createLine(*front, sf::Color::Green);
		limbo->setLineVisibility(true);

		procedure = "newNode->setNext(front);";
		break;
	case 1:
		limbo->setLineColor(sf::Color::Black);
		textFront->setColor(sf::Color::Green);
		textFront->addConstraint(*limbo, sf::Vector2f(0.0f, textYoffset), LA_CENTERTOP);

		procedure = "front = newNode;";
		break;
	case 2:
		textFront->setColor(sf::Color::Black);
		limbo->setState(EState::ES_INLIST);
		//addFront();
		status = AS_FINISHED;

		procedure = "Procedure Finished.";
		break;
	}

}

void Animation::playAddRear()
{
	switch (animStep)
	{
	case 0:
		rear->setLineColor(sf::Color::Red);

		procedure = "rear->setNext(newNode);";
		break;
	case 1:
		rear->createLine(*limbo, sf::Color::Green);
		rear->setLineVisibility(true);

		procedure = "";
		break;
	case 2:
		rear->setLineColor(sf::Color::Black);
		textRear->setColor(sf::Color::Green);
		textRear->addConstraint(*limbo, sf::Vector2f(0.0f, textYoffset), LA_CENTERTOP);

		procedure = "rear = newNode;";
		break;
	case 3:
		textRear->setColor(sf::Color::Black);
		limbo->createLine(*textNull, sf::Color::Green);
		limbo->setLineVisibility(true);

		procedure = "newNode->setNext(NULL);";
		break;
	case 4:
		limbo->setState(EState::ES_INLIST);
		limbo->setLineColor(sf::Color::Black);
		status = AS_FINISHED;

		procedure = "Procedure Finished.";
		break;
	}

}
void Animation::playRemoveLone()
{
	switch (animStep)
	{
	case 0:
		limbo->setState(EState::ES_REMOVED);
		procedure = "";
		break;
	case 1:
		limbo->markDeleted();

		procedure = "delete front;";
		break;
	case 2:
		textRear->setColor(sf::Color::Green);
		textRear->addConstraint(*textNull, sf::Vector2f(0.0f, textYoffset));

		procedure = "rear = NULL;";
		break;
	case 3:
		textRear->setColor(sf::Color::Black);
		textFront->setColor(sf::Color::Green);
		textFront->addConstraint(*textNull, sf::Vector2f(0.0f, textYoffset));

		procedure = "front = NULL;";
		break;
	case 4:
		textFront->setColor(sf::Color::Black);
		status = AS_FINISHED;

		procedure = "Procedure Finished.";
		break;
	}
}
void Animation::playRemoveFront()
{	
	switch (animStep)
	{
	case 0:
		limbo->setState(EState::ES_REMOVED);
		procedure = "Node* temp = front;";
		break;
	case 1:
		textFront->setColor(sf::Color::Green);
		textFront->addConstraint(*nodeAfter, sf::Vector2f(0.0f, textYoffset));

		procedure = "front = front->getNext();";
		break;
	case 2:
		limbo->markDeleted();

		procedure = "delete temp;";
		break;
	case 3:
		textFront->setColor(sf::Color::Black);
		status = AS_FINISHED;

		procedure = "Procedure Finished.";
		break;
	}
}
void Animation::playRemoveRear()
{

	if (animStep < limbo->placement - 1)
	{
		Node* node = front;
		for (int i = 0; i <= animStep; i++)
		{
			node = node->getNext();
		}
		textIter->addConstraint(*node, sf::Vector2f(0.0f, iterOffset));

		procedure = "while(nodeBefore->getNext() != rear)\n\tnodeBefore = nodeBefore->getNext();";
	}
	else
	{
		switch (animStep - limbo->placement + 1)
		{
		case 0:
			limbo->setState(EState::ES_REMOVED);

			procedure = "";
			break;
		case 1:
			limbo->markDeleted();
			
			procedure = "delete rear;";
			break;
		case 2:
			textRear->setColor(sf::Color::Green);
			textRear->addConstraint(*nodeBefore, sf::Vector2f(0.0f, textYoffset));
			
			procedure = "rear = nodeBefore;";
			break;
		case 3:
			textRear->setColor(sf::Color::Black);
			nodeBefore->createLine(*textNull, sf::Color::Green);

			procedure = "nodeBefore->setNext(NULL);";
			break;
		case 4:
			nodeBefore->setLineColor(sf::Color::Black);
			textIter->setVisible(false);
			status = AS_FINISHED;

			procedure = "Procedure Finished.";
			break;
		}
	}
	
}

void Animation::playAddBeforeIth()
{
	if (animStep < nodeBefore->placement)
	{
		Node* node = front;
		for (int i = 0; i <= animStep; i++)
		{
			node = node->getNext();
		}
		textIter->addConstraint(*node, sf::Vector2f(0.0f, iterOffset));
		procedure = "int pos = 1;\nwhile(pos < i-1)\n"
			"{ iter = iter->getNext();\n"
			"pos++;}";
	}
	else
	{
		switch (animStep - nodeBefore->placement)
		{
		case 0:
			limbo->createLine(*nodeBefore->getNext(), sf::Color::Green);
			limbo->setLineVisibility(true);
			procedure = "Node* newNode = new Node();\nnewNode->setNext(iter->getNext());";
			break;
		case 1:
			limbo->setLineColor(sf::Color::Black);
			nodeBefore->setLineColor(sf::Color::Red);
			break;
		case 2:
			nodeBefore->createLine(*limbo, sf::Color::Green);
			nodeBefore->setLineVisibility(true);
			procedure = "iter->setNext(newNode);";
			break;
		case 3:
			nodeBefore->setLineColor(sf::Color::Black);
			procedure = "";
			break;
		case 4:
			limbo->setState(EState::ES_INLIST);
			textIter->setVisible(false);
			status = AS_FINISHED;
			procedure = "Procedure Finished.";
			break;
		}
	}
}

void Animation::playRemoveIth()
{
	if (animStep < nodeBefore->placement)
	{
		Node* node = front;
		for (int i = 0; i <= animStep; i++)
		{
			node = node->getNext();
		}
		textIter->addConstraint(*node, sf::Vector2f(0.0f, iterOffset));

		procedure = "int pos = 1;\nwhile(pos < i-1)\n"
			"{ iter = iter->getNext();\n"
			"pos++;}";
	}
	else
	{
		switch (animStep - nodeBefore->placement)
		{
		case 0:
			limbo->setState(EState::ES_REMOVED);
			procedure = "Node* IthNode = iter->getNext();";
			break;
		case 1:
			nodeBefore->setLineColor(sf::Color::Red);
			procedure = "iter->setNext(IthNode->getNext());";
			break;
		case 2:
			nodeBefore->createLine(*limbo->getNext(), sf::Color::Green);
			nodeBefore->setLineVisibility(true);
			procedure = "";
			break;
		case 3:
			nodeBefore->setLineColor(sf::Color::Black);
			limbo->markDeleted();
			procedure = "delete IthNode;";
			break;
		case 4:
			textIter->setVisible(false);
			status = AS_FINISHED;
			procedure = "Procedure Finished.";
			break;
		}
	}
}