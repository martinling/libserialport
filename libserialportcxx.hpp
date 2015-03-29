/*
 * This file is part of the libserialport project.
 *
 * Copyright (C) 2015 Martin Ling <martin-sigrok@earth.li>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**

@mainpage API Reference

Introduction
------------

The libserialport++ API provides an object-oriented C++ interface to 
libserialport, including automatic resource management.

It is built on top of the public libserialport C API, and is designed to be
used both as a standalone C++ API and as a basis for other language bindings.

Memory management
-----------------

All dynamically allocated objects created through the C++ API are passed and
accessed via shared pointers, using the C++11 std::shared_ptr implementation.
This means that a reference count is kept for each object.

Shared pointers can be copied and assigned in a user's program, automatically
updating their reference count and deleting objects when they are no longer in
use. This means that management of libserialport++ objects can be treated as
fully automatic. As long as all shared pointers to objects are deleted or
reassigned when no longer in use, underlying resources will be released at the
right time.

Error handling
--------------

When any libserialport C API call returns an error, a serial::Error exception
is raised. Exceptions thrown conform to the C++11 std::exception hierarchy.

*/

#ifndef LIBSERIALPORTCXX_HPP
#define LIBSERIALPORTCXX_HPP

#include <libserialport.h>
#include <system_error>
#include <stdexcept>
#include <utility>
#include <memory>
#include <vector>

namespace serial {

using namespace std;

enum class Mode {
	READ = SP_MODE_READ,
	WRITE = SP_MODE_WRITE,
	READ_WRITE = SP_MODE_READ_WRITE
};

enum class Event {
	RX_READY = SP_EVENT_RX_READY,
	TX_READY = SP_EVENT_TX_READY,
};

enum class Buffer {
	INPUT = SP_BUF_INPUT,
	OUTPUT = SP_BUF_OUTPUT,
	BOTH = SP_BUF_BOTH
};

enum class Parity {
	INVALID = SP_PARITY_INVALID,
	NONE = SP_PARITY_NONE,
	ODD = SP_PARITY_ODD,
	EVEN = SP_PARITY_EVEN
};

enum class RTS {
	INVALID = SP_RTS_INVALID,
	OFF = SP_RTS_OFF,
	ON = SP_RTS_ON,
	FLOW_CONTROL = SP_RTS_FLOW_CONTROL
};

enum class CTS {
	INVALID = SP_CTS_INVALID,
	IGNORE = SP_CTS_IGNORE,
	FLOW_CONTROL = SP_CTS_FLOW_CONTROL
};

enum class DTR {
	INVALID = SP_DTR_INVALID,
	OFF = SP_DTR_OFF,
	ON = SP_DTR_ON,
	FLOW_CONTROL = SP_DTR_FLOW_CONTROL
};

enum class DSR {
	INVALID = SP_DSR_INVALID,
	IGNORE = SP_DSR_IGNORE,
	FLOW_CONTROL = SP_DSR_FLOW_CONTROL
};

enum class XonXoff {
	INVALID = SP_XONXOFF_INVALID,
	DISABLED = SP_XONXOFF_DISABLED,
	IN = SP_XONXOFF_IN,
	OUT = SP_XONXOFF_OUT,
	INOUT = SP_XONXOFF_INOUT
};

enum class FlowControl {
	NONE = SP_FLOWCONTROL_NONE,
	XONXOFF = SP_FLOWCONTROL_XONXOFF,
	RTSCTS = SP_FLOWCONTROL_RTSCTS,
	DTRDSR = SP_FLOWCONTROL_DTRDSR
};

enum class Signal {
	CTS = SP_SIG_CTS,
	DSR = SP_SIG_DSR,
	DCD = SP_SIG_DCD,
	DRI = SP_SIG_RI
};

enum class Transport {
	NATIVE = SP_TRANSPORT_NATIVE,
	USB = SP_TRANSPORT_USB,
	BLUETOOTH = SP_TRANSPORT_BLUETOOTH
};

/** Base class for dynamically allocated objects. */
template<class Class, typename Struct>
class Base
{
protected:
	Struct *_structure;
	class Deleter
	{
	public:
		void operator()(Class *object)
		{
			delete object;
		}
	};
};

class Port;
class Config;
class EventSet;

/** A serial port configuration. */
class Config : Base<Config, struct sp_port_config>
{
public:
	/** Create a new configuration. */
	static shared_ptr<Config> create();
	/** Baud rate. */
	int baudrate();
	/** Set baud rate. */
	void set_baudrate(int baudrate);
	/** Data bits. */
	int bits();
	/** Set data bits. */
	void set_bits(int bits);
	/** Parity. */
	Parity parity();
	/** Set parity. */
	void set_parity(Parity parity);
	/** Stop bits. */
	int stopbits();
	/** Set stop bits. */
	void set_stopbits(int bits);
	/** RTS pin behaviour. */
	RTS rts();
	/** Set RTS pin behaviour. */
	void set_rts(RTS rts);
	/** CTS pin behaviour. */
	CTS cts();
	/** Set CTS pin behaviour. */
	void set_cts(CTS cts);
	/** DTR pin behaviour. */
	DTR dtr();
	/** Set DTR pin behaviour. */
	void set_dtr(DTR dtr);
	/** DSR pin behaviour. */
	DSR dsr();
	/** Set DSR pin behaviour. */
	void set_dsr(DSR dsr);
	/** Xon/Xoff configuration. */
	XonXoff xon_xoff();
	/** Set Xon/Xoff configuration. */
	void set_xon_xoff(XonXoff xon_xoff);
	/** Set flow control mode. */
	void set_flowcontrol(FlowControl flowcontrol);
protected:
	Config(struct sp_port_config *config);
	~Config();
	friend class Deleter;
	friend class Port;
};

/** A serial port. */
class Port : Base<Port, struct sp_port>
{
public:
	/** List available ports. */
	static vector<shared_ptr<Port> > list();
	/** Get port by name. */
	static shared_ptr<Port> by_name(string name);
	/** Name. */
	string name();
	/** Description. */
	string description();
	/** Transport type. */
	Transport transport();
	/** USB bus. */
	int usb_bus();
	/** USB address. */
	int usb_address();
	/** USB vendor ID. */
	int usb_vid();
	/** USB product ID. */
	int usb_pid();
	/** USB manufacturer name. */
	string usb_manufacturer();
	/** USB product name. */
	string usb_product();
	/** Bluetooth MAC address. */
	string bluetooth_address();
	/** Get OS port handle. */
	void *get_handle();
	/** Open port. */
	void open(Mode mode);
	/** Close port. */
	void close();
	/** Current configuration. */
	shared_ptr<Config> config();
	/** Set configuration. */
	void set_config(shared_ptr<Config> config);
	/** Set baudrate. */
	void set_baudrate(int baudrate);
	/** Set data bits. */
	void set_bits(int bits);
	/** Set parity. */
	void set_parity(Parity parity);
	/** Set stop bits. */
	void set_stopbits(int bits);
	/** Set RTS pin behaviour. */
	void set_rts(RTS rts);
	/** Set CTS pin behaviour. */
	void set_cts(CTS cts);
	/** Set DTR pin behaviour. */
	void set_dtr(DTR dtr);
	/** Set DSR pin behaviour. */
	void set_dsr(DSR dsr);
	/** Set Xon/Xoff configuration. */
	void set_xon_xoff(XonXoff xon_xoff);
	/** Set flow control mode. */
	void set_flowcontrol(FlowControl flowcontrol);
	/** Read bytes, blocking until complete. */
	size_t blocking_read(void *buf, size_t count, unsigned int timeout);
	/** Read bytes, without blocking. */
	size_t nonblocking_read(void *buf, size_t count);
	/** Write bytes, blocking until complete. */
	size_t blocking_write(void *buf, size_t count, unsigned int timeout);
	/** Write bytes, without blocking. */
	size_t nonblocking_write(void *buf, size_t count);
	/** Number of bytes waiting in input buffer. */
	size_t input_waiting();
	/** Number of bytes waiting in output buffer. */
	size_t output_waiting();
	/** Flush buffers. */
	void flush(Buffer buffer);
	/** Wait for buffered data to be transmitted. */
	void drain();
	/** Get status of signals. */
	Signal signals();
	/** Start break. */
	void start_break();
	/** End break. */
	void end_break();
protected:
	Port(struct sp_port *port);
	~Port();
	friend class Deleter;
	friend class EventSet;
};

/** A set of port events to wait on. */
class EventSet : Base<EventSet, struct sp_event_set>
{
public:
	/** Create a new event set. */
	static shared_ptr<EventSet> create();
	/** Add port events. */
	void add_events(shared_ptr<Port> port, Event events);
	/** Wait for events. */
	void wait(unsigned int timeout);
protected:
	EventSet(struct sp_event_set *set);
	~EventSet();
	friend class Deleter;
};

/** Base exception class. */
class Error: public exception
{
public:
	Error(string what);
	~Error() throw();
	const char *what() const throw();
protected:
	string _what;
};

/** Invalid argument passed. */
class InvalidArgument: Error, invalid_argument
{
public:
	InvalidArgument(string function);
};

/** Operation failed. */
class Failure : Error, system_error
{
public:
	Failure(string function);
};

/** Operation not supported. */
class NotSupported : Error
{
public:
	NotSupported(string function);
};

/** Memory allocation failed. */
class AllocationFailure : Error, bad_alloc
{
public:
	AllocationFailure(string function);
};

/** Type of debug message handler */
typedef function<void(string message)> DebugHandlerFunction;

/** Set debug message handler. */
void set_debug_handler(DebugHandlerFunction function);

}

#endif
