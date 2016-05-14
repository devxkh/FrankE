#ifndef __QUEUEMANAGER_HPP__
#define __QUEUEMANAGER_HPP__

//#include <sfml/Window/Window.hpp>
//#include <XEGraphics/Gorilla.h>

//#include <queue>
#include <XESystem/atomicops.h>
#include <XESystem/readerwriterqueue.h>

#include <functional>

#include <sfml/Config.hpp>

namespace XE {

	class QueueManager
	{

	public:

		QueueManager();

		typedef std::function<void(void)> OnFunctionHandler;

		void push(OnFunctionHandler Handler);

		void TriggerAllHandler(sf::Uint16 max = 1000);

	private:


		moodycamel::ReaderWriterQueue<OnFunctionHandler> m_rwqueue;
	};


} // ns XE

#endif // __QUEUEMANAGER_HPP__