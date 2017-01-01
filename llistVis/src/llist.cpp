#include "..\include\llist.h"
#include <iostream>

float nodeSpace = 140.0f;
float textYoffset = -60.0f;

LList::LList(AssetManager& pAssets) : assets(&pAssets), textLabel(&pAssets), textFront(&pAssets, true), textRear(&pAssets, true), textNull(&pAssets), textIter(&pAssets, true)
{
	

	textLabel.setString("llist:-");
	textLabel.setCharacterSize(24);
	textLabel.setColor(sf::Color::Black);
	textLabel.setOrigin(sf::Vector2f(textLabel.getLocalBounds().width, textLabel.getLocalBounds().height));
	textLabel.setPosition(-20.0f, 0.0f);

	textNull.setString("NULL");
	textNull.setCharacterSize(16);
	textNull.setColor(sf::Color::Black);
	textNull.setOrigin(sf::Vector2f(textNull.getLocalBounds().width / 2.0f, 0.0f));
	textNull.setPosition(0.0f, 0.0f);

	textFront.setString("FRONT");
	textFront.setCharacterSize(12);
	textFront.setColor(sf::Color::Black);
	textFront.setOrigin(sf::Vector2f(textFront.getLocalBounds().width, textFront.getLocalBounds().height));
	textFront.addConstraint(textNull, sf::Vector2f(0.0f, textYoffset));

	textRear.setString("REAR");
	textRear.setCharacterSize(12);
	textRear.setColor(sf::Color::Black);
	textRear.setOrigin(sf::Vector2f(0.0f, textRear.getLocalBounds().height));
	textRear.addConstraint(textNull, sf::Vector2f(0.0f, textYoffset));

	textIter.setString("ITER");
	textIter.setCharacterSize(12);
	textIter.setColor(sf::Color::Blue);
	textIter.setOrigin(sf::Vector2f(textFront.getLocalBounds().width / 2.0f, textFront.getLocalBounds().height));
	textIter.setVisible(false);

	front = NULL;
	rear = NULL;
	limbo = NULL;
}

void LList::update(sf::Time dt)
{
	anim.update(dt);
	if (anim.getStatus() == AS_FINISHED)
	{
		switch (info.type)
		{
		case InsertInfo::ADD_FRONT:
			addFront();
			break;
		case InsertInfo::ADD_REAR:
			addRear();
			break;
		case InsertInfo::ADD_ITH:
			addBeforeIth();
			break;
		case InsertInfo::REM_FRONT:
			//UPDATE PLACEMENT HERE
			updatePlacement(-1);
			deleteFront();
			break;
		case InsertInfo::REM_REAR:
			updatePlacement(-1);
			deleteRear();
			break;
		case InsertInfo::REM_ITH:
			updatePlacement(-1);
			deleteIth();
			break;
		}
		anim.endAnim();
	}

	textFront.update(dt);
	textRear.update(dt);
	textLabel.update(dt);
	textNull.update(dt);
	textIter.update(dt);

	Node* ptr = front;
	while (ptr != NULL)
	{
		ptr->update(dt);
		ptr = ptr->getNext();
	}

}

//amount is either 1 for increment or -1 for decrement
void LList::updatePlacement(int amount)
{
	dimensions.x = (count + amount) * nodeSpace;
	pos.x = -dimensions.x / 2.0f;
	textLabel.addConstraint(*this, sf::Vector2f(-(dimensions.x / 2.0f), 0.0f));
	textNull.addConstraint(*this, sf::Vector2f((dimensions.x / 2.0f) + (nodeSpace / 2.0f), 0.0f));
	
	Node* node = front;
	while (node != NULL)
	{
		if (node->placement >= limbo->placement)
		{
			if (node != limbo)
				node->placement += amount;
		}
		node = node->getNext();
	}
	updateNodeDest(count + amount);
}

void LList::updateNodeDest(int projectedCount)
{
	if (limbo)//this should always be true since you only call this function when adding limbo
	{
		limbo->updateDest(sf::Vector2f(-(nodeSpace * (projectedCount - 1) / 2.0f) + (nodeSpace * (projectedCount) * ((float)limbo->placement / (float)(projectedCount))), 0.0f));
	}
	Node* ptr = front;
	while (ptr != NULL)
	{
		ptr->updateDest(sf::Vector2f(-(nodeSpace * (projectedCount - 1) / 2.0f) + (nodeSpace * (projectedCount) * ((float)ptr->placement / (float)(projectedCount))), 0.0f));
		ptr = ptr->getNext();

	}
}

bool LList::isEmpty()
{
	return count == 0;
}

void LList::addNode(Node* newNode, InsertInfo pinfo)
{
	info = pinfo;
	switch (info.type)
	{
	case InsertInfo::insertType::ADD_FRONT:
	{
		limbo = newNode;
		limbo->placement = 0;
		limbo->setState(EState::ES_ADDED);
		if (!isEmpty())
		{
			anim.initAddFront(limbo, front, &textFront);
		}
		else
		{
			anim.initAddLone(limbo, &textFront, &textRear, &textNull);
		}
		updatePlacement(1);
	}break;
	case InsertInfo::insertType::ADD_REAR:
	{
		limbo = newNode;
		limbo->placement = count;
		limbo->setState(EState::ES_ADDED);
		if (!isEmpty())
		{
			anim.initAddRear(limbo, rear, &textRear, &textNull);
		}
		else
		{
			anim.initAddLone(limbo, &textFront, &textRear, &textNull);
		}
		updatePlacement(1);
	}break;
	case InsertInfo::insertType::REM_FRONT:
	{
		if (front)
		{
			limbo = front;
			nodeAfter = front->getNext();
			limbo->setState(EState::ES_REMOVED);

			if (front == rear)
			{
				anim.initRemLone(limbo, &textFront, &textRear, &textNull);
			}
			else
			{
				anim.initRemFront(limbo, nodeAfter, &textFront);
			}

		}
		else
		{
			std::cout << "There is no node to delete!" << std::endl;
			return;
		}
	}break;
	case InsertInfo::insertType::REM_REAR:
	{
		nodeBefore = NULL;
		if (rear)
		{
			limbo = rear;
			if (front != rear)
			{
				nodeBefore = front;
				while (nodeBefore->getNext() != rear)
				{
					nodeBefore = nodeBefore->getNext();
				}
				textIter.setVisible(true);
				textIter.setPosition(front->getPosition());

				anim.initRemRear(limbo, nodeBefore, front, &textIter, &textRear, &textNull);
			}
			else
			{
				anim.initRemLone(limbo, &textFront, &textRear, &textNull);
			}
		}
		else
		{
			std::cout << "There is no node to delete!" << std::endl;
			return;
		}
	}break;
	case InsertInfo::insertType::ADD_ITH:
	{
		limbo = newNode;
		limbo->placement = info.ith - 1;
		limbo->setState(EState::ES_ADDED);

		if (isEmpty())
		{
			if (info.ith == 1)
			{
				//anim add lone
				anim.initAddLone(limbo, &textFront, &textRear, &textNull);
			}
			else
			{
				std::cout << "Not a valid index to insert node!" << std::endl;
				delete limbo;
				limbo = NULL;
				return;
			}
		}
		else
		{
			if (info.ith == 1)
			{
				//anim add front
				anim.initAddFront(limbo, front, &textFront);
			}
			else if (info.ith == count + 1)
			{
				//anim add rear
				anim.initAddRear(limbo, rear, &textRear, &textNull);
			}
			else if (info.ith > 1 && info.ith < count + 1)
			{
				//iter is the cursor to node before ith node
				nodeBefore = front;
				int i = 1;
				while (i != info.ith - 1)
				{
					nodeBefore = nodeBefore->getNext();
					i++;
				}
				//anim add before ith
				anim.initAddBeforeIth(limbo, nodeBefore, front, &textIter);
			}
			else
			{
				std::cout << "Not a valid index!" << std::endl;
				delete limbo;
				limbo = NULL;
				return;
			}
		}
		updatePlacement(1);
	}break;
	case InsertInfo::insertType::REM_ITH:
	{
		/*limbo = newNode;
		limbo->placement = info.ith - 1;
		limbo->setState(EState::ES_ADDED);*/

		if (isEmpty())
		{
			std::cout << "List is empty! Cannot delete anything!" << std::endl;
		}
		else
		{
			limbo = front;
			if (info.ith == 1)
			{
				if (front == rear)
				{
					anim.initRemLone(limbo, &textFront, &textRear, &textNull);
				}
				else
				{
					nodeAfter = front->getNext();
					anim.initRemFront(limbo, nodeAfter, &textFront);
				}
			}
			else if (info.ith == count && count != 1)
			{
				limbo = rear;
				nodeBefore = front;
				while (nodeBefore->getNext() != rear)
				{
					nodeBefore = nodeBefore->getNext();
				}
				anim.initRemRear(limbo, nodeBefore, front, &textIter, &textRear, &textNull);
			}
			else if (info.ith > 1 && info.ith < count)
			{
				//iter is the cursor to node before ith node
				nodeBefore = front;
				int i = 1;
				while (i != info.ith - 1)
				{
					nodeBefore = nodeBefore->getNext();
					i++;
				}
				limbo = nodeBefore->getNext();
				//anim add before ith
				anim.initRemIth(limbo, nodeBefore, front, &textIter);
			}
			else
			{
				std::cout << "Not a valid index!" << std::endl;
				return;
			}
		}
	}break;
	}
}

void LList::addBeforeIth()
{
	int i = info.ith;
	
	//CASE: adding before first node
	if (i == 1)
	{
		addFront();
	}
	//CASE: adding "before last's next" which is adding to rear
	else if (i == count + 1)
	{
		addRear();
	}
	//CASE: valid range to insert
	else if (i > 1 && i < count + 1)
	{
		
		limbo->setNext(nodeBefore->getNext());
		nodeBefore->setNext(limbo);
		count++;
	}
	//CASE: not within valid range of the list
	else
	{
		std::cout << "TO DO - GET RID OF THIS BY ADDING FUNCTIONALITY ELSEWHERE!";
	}


	textIter.removeConstraint();
	limbo = NULL;
	nodeBefore = NULL;
}

void LList::addFront()
{
	//CASE: first node in the list
	if (isEmpty())
	{
			front = limbo;
			rear = front;
			rear->setNext(NULL);
		
			count++;
	}
	else //CASE: there is a preexisting list
	{
		//newNode is node to add before front
		limbo->setNext(front);
		front = limbo;

		count++;
	}
	limbo = NULL;
}

void LList::addRear()
{
	//CASE: when first node, must create new node and set rear and front to it
	if (isEmpty())
	{
		front = limbo;
		rear = front;

		rear->setNext(NULL);

		count++;
	}
	else //for adding to preexisting list
	{
		rear->setNext(limbo);
		rear = rear->getNext();
		rear->setNext(NULL);

		count++;
	}
	limbo = NULL;
}

void LList::deleteFront()
{

	//CASE: where front is the last node, if deleted, list is empty so set front and rear NULL
	if (nodeAfter == NULL)
	{
		//delete first before hard-setting back to NULL
		delete front;
		front = NULL;
		rear = NULL;
		count--;
	}
	else // CASE: usual
	{
		//second is node after front
		delete front;
		front = nodeAfter;
		count--;
	}
	limbo = NULL;
	nodeAfter = NULL;
}

void LList::deleteRear()
{
	//CASE: the only node in the list
	if (nodeBefore == NULL)
	{
		//delete first before hard-setting back to NULL
		delete rear;
		front = NULL;
		rear = NULL;
		count--;
	}
	else // CASE: usual
	{
		//iter to node before rear
		delete rear;
		rear = nodeBefore;
		rear->setNext(NULL);
		count--;
	}
	textIter.removeConstraint();
	nodeBefore = NULL;
	limbo = NULL;
}
void LList::deleteIth()
{
	int i = info.ith;
	//CASE: first elem
	if (i == 1)
	{
		deleteFront();
	}
	//CASE: last elem
	else if (i == count)
	{
		deleteRear();
	}
	//CASE: valid i
	else if (i > 1 && i < count)
	{
		nodeBefore->setNext(limbo->getNext());
		delete limbo;
		count--;
	}
	else //CASE: invalid value (outside scope of list)
	{
		//TO DO GET RID OF THIS
	}
	textIter.removeConstraint();
	nodeBefore = NULL;
	limbo = NULL;
}

void LList::draw(sf::RenderWindow& window)
{
	if (limbo)
	{
		limbo->draw(window);
	}
	Node* ptr = front;
	while (ptr != NULL)
	{
		
		ptr->draw(window);
	
		ptr = ptr->getNext();
	}
	textLabel.draw(window);
	textFront.draw(window);
	textRear.draw(window);
	textNull.draw(window);
	textIter.draw(window);

}

sf::FloatRect LList::getBoundingRect()
{
	sf::FloatRect result;
	result.left = pos.x;
	result.top = pos.y;
	result.width = dimensions.x;
	result.height = dimensions.y;
	return result;
}
bool LList::isAnimPlaying()
{
	return anim.getStatus() == AS_ON;
}
std::string LList::stepAnim()
{
	std::string procResult = anim.step();
	std::cout << procResult << std::endl;
	return procResult;
}