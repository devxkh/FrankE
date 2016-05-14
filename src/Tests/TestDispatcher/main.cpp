#include <iostream>
#include <thread>
#include <functional>
#include <vector>
#include <chrono>

#include <queue>

#include "atomicops.h"
#include "readerwriterqueue.h"

//blog: http://blog.csdn.net/pizi0475/article/details/17655915

//another queue http://www.ogre3d.org/addonforums/viewtopic.php?f=19&t=10975



using namespace moodycamel;

class QueueHandler
{
public:
	typedef std::function<void(void)> OnSomethingHandler;

	QueueHandler()
		://ogreTestQ(1000)
		q(1000)  // difference to ogreTestQ .... dynamic size possible!
	{
	}

	void AddOnSomethingHandler(OnSomethingHandler Handler)
	{
		//todo : here use a lockless queue
		//http://moodycamel.com/blog/2013/a-fast-lock-free-queue-for-c++
		//https://github.com/cameron314/readerwriterqueue  1 on 1 thread
		//http://moodycamel.com/blog/2014/a-fast-general-purpose-lock-free-queue-for-c++  n on n Thread
		///	if (mSwitchQueue)
		//	handlers_.push(Handler);
		//	else
		//		handlers_2.push_back(Handler);

		//alternate	bool succeeded = q.try_enqueue(Handler);
			bool succeeded = q.enqueue(Handler);
		//Runs! ----ogreTestQ.push(Handler);

		//q.enqueue(17);                       // Will allocate memory if the queue is full
		//bool succeeded = q.try_enqueue(18);  // Will only succeed if the queue has an empty slot (never allocates)
		//assert(succeeded);

		//int number;
		//succeeded = q.try_dequeue(number);  // Returns false if the queue was empty

		//assert(succeeded && number == 17);

		//// You can also peek at the front item of the queue (consumer only)
		//int* front = q.peek();              // Returns nullptr if the queue was empty
		//assert(front == nullptr);

	}

	void TriggerRenderEvents(void)
	{
		OnSomethingHandler tmp;
		//while (ogreTestQ.pop(tmp))
		//{
		//	tmp();
		//}
		while (q.peek())
			{
				bool succeeded = q.try_dequeue(tmp);
				tmp();
		}

		/*while (!handlers_.empty())
		{
		handlers_.front()();
		handlers_.pop();
		}*/
		//	(*(handlers_.pop()))();
		//	for (auto i = handlers_.begin(); i != handlers_.end(); ++i)
		//	(*i)();
	}


private:
	//Runs! ----LocklessQueue<OnSomethingHandler> ogreTestQ;
	ReaderWriterQueue<OnSomethingHandler> q;       // LFQ Reserve space for at least 100 elements up front
};

class GrapicsManager;

class OgreEntity
{
public:
	void setPosition(int val) //Ogreobject
	{
		t2 = val;
	}
	int t2 = 99;
};

class Entity
{
public:
	Entity(GrapicsManager* gmanager);
	void setEntityPosition(int val);
	void createEntity(int id);
private:
	GrapicsManager* mGraphicsManager;
	
	
	int TestmOgreEntityReference;
	//-------------  Ogre Object only changed in renderthread -------------------------
	OgreEntity* mOgreEntityReference; //just passing around do not modify! only in renderthread //only change with AddOnSomethingHandler in another thread !!!
	//--------------------------------------
};

class GrapicsManager
{
public:
	GrapicsManager();
	void RenderLoop();

	QueueHandler& getQueueHandler() { return my_QueueHandler; }

private:
	std::thread mRenderThread;

	Entity testEntity;  //normaly a list of entities for physics and logical calculations

	QueueHandler my_QueueHandler;
};



Entity::Entity(GrapicsManager* gmanager)
	: mGraphicsManager(gmanager)
	, mOgreEntityReference(nullptr)
{

}

void Entity::createEntity(int id)
{
	//http://scriptionary.com/2011/07/05/c-events-with-lambda-expressions-and-stdfunction/
	mGraphicsManager->getQueueHandler().AddOnSomethingHandler([this](){
		mOgreEntityReference = new OgreEntity();
		std::cout << "RenderThread - create OgreEntityReference " << std::endl;
	});
}

void Entity::setEntityPosition(int val)
{
	//http://scriptionary.com/2011/07/05/c-events-with-lambda-expressions-and-stdfunction/
	
	mGraphicsManager->getQueueHandler().AddOnSomethingHandler([this, val](){
		mOgreEntityReference->setPosition(mOgreEntityReference->t2 += 1);
		std::cout << "RenderThread - OgreEntityReference update: " << mOgreEntityReference->t2 << std::endl;
	});
}

GrapicsManager::GrapicsManager() :
testEntity(this),
mRenderThread(&GrapicsManager::RenderLoop, this)
{
}

//Renderloop executed in Renderthread
void GrapicsManager::RenderLoop()
{
	std::cout << "RenderLoop starting";

	while (true)
	{
		my_QueueHandler.TriggerRenderEvents();
	}
}

class GameThread
{
public:
	GameThread(GrapicsManager* gmanager) :
		m_GameThread(&GameThread::GameLoop, this)
		, mTestGameLogicEntity(gmanager)
	{

	}
private:
	void GameLoop()
	{
		mTestGameLogicEntity.createEntity(1);
		int tmpVal = 0;

		while (true)
		{
		//	std::cout << "GameThread(Loop) - setEntityPosition " << std::endl;
			mTestGameLogicEntity.setEntityPosition(tmpVal); //test call - just adding +1 
			tmpVal++;
			//std::chrono::milliseconds dura(1000);
		//	std::this_thread::sleep_for(dura);
		}
	}

	Entity mTestGameLogicEntity;
	std::thread m_GameThread;
};

int main()
{
	GrapicsManager gm;  //contains render thread

	GameThread mGameThread(&gm);  //game thread
	
	while (true)				//main thread
	{
		std::chrono::milliseconds dura(5000);
		std::this_thread::sleep_for(dura);
	}
}