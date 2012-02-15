/*
 * AbsoluteTimeoutAction.cpp
 *
 *  Created on: Aug 27, 2011
 *      Author: augcampos
 */

#include "asteriskcpp/manager/actions/AbsoluteTimeoutAction.h"

namespace asteriskcpp {

	AbsoluteTimeoutAction::AbsoluteTimeoutAction(const std::string& channel, unsigned int timeout) {
		setChannel(channel);
		setTimeout(timeout);
	}

	AbsoluteTimeoutAction::~AbsoluteTimeoutAction() {
	}

	/**
	 * Returns the name of this action, i.e. "Login".
	 */
	std::string AbsoluteTimeoutAction::getAction() {
		return ("AbsoluteTimeout");
	}

	/**
	 * Returns the name of the channel.
	 */
	std::string AbsoluteTimeoutAction::getChannel() const {
		return (getProperty("Channel"));
	}

	/**
	 * Sets the name of the channel.
	 */
	void AbsoluteTimeoutAction::setChannel(const std::string& channel) {
		setProperty("Channel", channel);
	}

	/**
	 * Returns the the maximum duation of the call (in seconds) to set.
	 */
	int AbsoluteTimeoutAction::getTimeout() const {
		return (getProperty<int>("Timeout"));
	}

	/**
	 * Sets the the maximum duation of the call (in seconds) to set on channel.<p>
	 * Setting the timeout to 0 cancels the timeout.
	 */
	void AbsoluteTimeoutAction::setTimeout(int timeout) {
		setProperty("Timeout", timeout);
	}

} //NS
