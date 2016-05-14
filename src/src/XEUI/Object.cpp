#include <XEUI/Object.hpp>

namespace XE {

Signal& Object::GetSignal( Signal::SignalID& id ) {
	if( !id ) {
		id = Signal::GetGUID();
	}

	return m_signals[id];
}

SignalContainer& Object::GetSignals() {
	return m_signals;
}

}
