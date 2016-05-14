#include <XESystem/QueueManager.hpp>

namespace XE 
{
	QueueManager::QueueManager()
		: m_rwqueue(500)
	{

	}

	void QueueManager::push(OnFunctionHandler Handler)
	{
		bool succeeded = m_rwqueue.enqueue(Handler);
	}

	void QueueManager::TriggerAllHandler(sf::Uint16 max)
	{
		OnFunctionHandler tmp;


		while (m_rwqueue.peek() && max > 0)
		{
			bool succeeded = m_rwqueue.trydequeue(tmp);
			tmp();
			max--;
		}
	}

}