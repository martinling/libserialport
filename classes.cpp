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

#include "libserialportcxx.hpp"

namespace serial
{

using namespace std;

static size_t check(enum sp_return result, string function)
{
	switch (result)
	{
		case SP_ERR_ARG:
			throw InvalidArgument(function);
		case SP_ERR_FAIL:
			throw Failure(function);
		case SP_ERR_MEM:
			throw AllocationFailure(function);
		case SP_ERR_SUPP:
			throw NotSupported(function);
		default:
			return result;
	}
}

#define CHECK(call) check(call, __func__)

Config::Config(struct sp_port_config *config)
{
	_structure = config;
}

Config::~Config()
{
	sp_free_config(_structure);
}

shared_ptr<Config> Config::create()
{
	struct sp_port_config *config;
	CHECK(sp_new_config(&config));
	return shared_ptr<Config>(new Config(config), Config::Deleter());
}

int Config::baudrate()
{
	int baudrate;
	CHECK(sp_get_config_baudrate(_structure, &baudrate));
	return baudrate;
}

void Config::set_baudrate(int baudrate)
{
	CHECK(sp_set_config_baudrate(_structure, baudrate));
}

int Config::bits()
{
	int bits;
	CHECK(sp_get_config_bits(_structure, &bits));
	return bits;
}

void Config::set_bits(int bits)
{
	CHECK(sp_set_config_bits(_structure, bits));
}

Parity Config::parity()
{
	enum sp_parity parity;
	CHECK(sp_get_config_parity(_structure, &parity));
	return (Parity) parity;
}

void Config::set_parity(Parity parity)
{
	CHECK(sp_set_config_parity(_structure, (enum sp_parity) parity));
}

int Config::stopbits()
{
	int stopbits;
	CHECK(sp_get_config_stopbits(_structure, &stopbits));
	return stopbits;
}

void Config::set_stopbits(int stopbits)
{
	CHECK(sp_set_config_stopbits(_structure, stopbits));
}

RTS Config::rts()
{
	enum sp_rts rts;
	CHECK(sp_get_config_rts(_structure, &rts));
	return (RTS) rts;
}

void Config::set_rts(RTS rts)
{
	CHECK(sp_set_config_rts(_structure, (enum sp_rts) rts));
}

CTS Config::cts()
{
	enum sp_cts cts;
	CHECK(sp_get_config_cts(_structure, &cts));
	return (CTS) cts;
}

void Config::set_cts(CTS cts)
{
	CHECK(sp_set_config_cts(_structure, (enum sp_cts) cts));
}

DTR Config::dtr()
{
	enum sp_dtr dtr;
	CHECK(sp_get_config_dtr(_structure, &dtr));
	return (DTR) dtr;
}

void Config::set_dtr(DTR dtr)
{
	CHECK(sp_set_config_dtr(_structure, (enum sp_dtr) dtr));
}

DSR Config::dsr()
{
	enum sp_dsr dsr;
	CHECK(sp_get_config_dsr(_structure, &dsr));
	return (DSR) dsr;
}

void Config::set_dsr(DSR dsr)
{
	CHECK(sp_set_config_dsr(_structure, (enum sp_dsr) dsr));
}

XonXoff Config::xon_xoff()
{
	enum sp_xonxoff xon_xoff;
	CHECK(sp_get_config_xon_xoff(_structure, &xon_xoff));
	return (XonXoff) xon_xoff;
}

void Config::set_xon_xoff(XonXoff xon_xoff)
{
	CHECK(sp_set_config_xon_xoff(_structure, (enum sp_xonxoff) xon_xoff));
}

void Config::set_flowcontrol(FlowControl flowcontrol)
{
	CHECK(sp_set_config_flowcontrol(_structure,
			(enum sp_flowcontrol) flowcontrol));
}

Port::Port(struct sp_port *port)
{
	_structure = port;
}

Port::~Port()
{
	sp_free_port(_structure);
}

vector<shared_ptr<Port>> Port::list()
{
	struct sp_port **port_list;
	struct sp_port **port;
	struct sp_port *port_copy;
	vector<shared_ptr<Port>> result;

	CHECK(sp_list_ports(&port_list));

	for (port = port_list; *port; port++)
	{
		try {
			CHECK(sp_copy_port(*port, &port_copy));
		} catch (Error e) {
			sp_free_port_list(port_list);
			throw e;
		}
		result.push_back(
			shared_ptr<Port>(new Port(port_copy), Port::Deleter()));
	}

	sp_free_port_list(port_list);

	return result;
}

shared_ptr<Port> Port::by_name(string name)
{
	struct sp_port *port;
	CHECK(sp_get_port_by_name(name.c_str(), &port));
	return shared_ptr<Port>(new Port(port), Port::Deleter());
}

string Port::name()
{
	return sp_get_port_name(_structure);
}

string Port::description()
{
	return sp_get_port_description(_structure);
}

Transport Port::transport()
{
	return (Transport) sp_get_port_transport(_structure);
}

int Port::usb_bus()
{
	int bus, address;
	CHECK(sp_get_port_usb_bus_address(_structure, &bus, &address));
	return bus;
}

int Port::usb_address()
{
	int bus, address;
	CHECK(sp_get_port_usb_bus_address(_structure, &bus, &address));
	return address;
}

int Port::usb_vid()
{
	int vid, pid;
	CHECK(sp_get_port_usb_vid_pid(_structure, &vid, &pid));
	return vid;
}

int Port::usb_pid()
{
	int vid, pid;
	CHECK(sp_get_port_usb_vid_pid(_structure, &vid, &pid));
	return pid;
}

string Port::usb_manufacturer()
{
	return sp_get_port_usb_manufacturer(_structure);
}

string Port::usb_product()
{
	return sp_get_port_usb_product(_structure);
}

string Port::bluetooth_address()
{
	return sp_get_port_bluetooth_address(_structure);
}

void *Port::get_handle()
{
	void *result = NULL;
	CHECK(sp_get_port_handle(_structure, result));
	return result;
}

void Port::open(Mode mode)
{
	CHECK(sp_open(_structure, (enum sp_mode) mode));
}

void Port::close()
{
	CHECK(sp_close(_structure));
}

shared_ptr<Config> Port::config()
{
	struct sp_port_config *config;
	CHECK(sp_new_config(&config));
	try {
		CHECK(sp_get_config(_structure, config));
	} catch (Error e) {
		sp_free_config(config);
	}
	return shared_ptr<Config>(new Config(config), Config::Deleter());
}

void Port::set_config(shared_ptr<Config> config)
{
	CHECK(sp_set_config(_structure, config->_structure));
}

void Port::set_baudrate(int baudrate)
{
	CHECK(sp_set_baudrate(_structure, baudrate));
}

void Port::set_bits(int bits)
{
	CHECK(sp_set_bits(_structure, bits));
}

void Port::set_parity(Parity parity)
{
	CHECK(sp_set_parity(_structure, (enum sp_parity) parity));
}

void Port::set_stopbits(int stopbits)
{
	CHECK(sp_set_stopbits(_structure, stopbits));
}

void Port::set_rts(RTS rts)
{
	CHECK(sp_set_rts(_structure, (enum sp_rts) rts));
}

void Port::set_cts(CTS cts)
{
	CHECK(sp_set_cts(_structure, (enum sp_cts) cts));
}

void Port::set_dtr(DTR dtr)
{
	CHECK(sp_set_dtr(_structure, (enum sp_dtr) dtr));
}

void Port::set_dsr(DSR dsr)
{
	CHECK(sp_set_dsr(_structure, (enum sp_dsr) dsr));
}

void Port::set_xon_xoff(XonXoff xon_xoff)
{
	CHECK(sp_set_xon_xoff(_structure, (enum sp_xonxoff) xon_xoff));
}

void Port::set_flowcontrol(FlowControl flowcontrol)
{
	CHECK(sp_set_flowcontrol(_structure,
			(enum sp_flowcontrol) flowcontrol));
}

size_t Port::blocking_read(void *buf, size_t count, unsigned int timeout)
{
	return CHECK(sp_blocking_read(_structure, buf, count, timeout));
}

size_t Port::nonblocking_read(void *buf, size_t count)
{
	return CHECK(sp_nonblocking_read(_structure, buf, count));
}

size_t Port::blocking_write(void *buf, size_t count, unsigned int timeout)
{
	return CHECK(sp_blocking_write(_structure, buf, count, timeout));
}

size_t Port::nonblocking_write(void *buf, size_t count)
{
	return CHECK(sp_nonblocking_write(_structure, buf, count));
}

size_t Port::input_waiting()
{
	return CHECK(sp_input_waiting(_structure));
}

size_t Port::output_waiting()
{
	return CHECK(sp_input_waiting(_structure));
}

void Port::flush(Buffer buffer)
{
	CHECK(sp_flush(_structure, (enum sp_buffer) buffer));
}

void Port::drain()
{
	CHECK(sp_drain(_structure));
}

Signal Port::signals()
{
	enum sp_signal signals;
	CHECK(sp_get_signals(_structure, &signals));
	return (Signal) signals;
}

void Port::start_break()
{
	CHECK(sp_start_break(_structure));
}

void Port::end_break()
{
	CHECK(sp_end_break(_structure));
}

EventSet::EventSet(struct sp_event_set *set)
{
	_structure = set;
}

EventSet::~EventSet()
{
	sp_free_event_set(_structure);
}

shared_ptr<EventSet> EventSet::create()
{
	struct sp_event_set *set;
	CHECK(sp_new_event_set(&set));
	return shared_ptr<EventSet>(new EventSet(set), EventSet::Deleter());
}

void EventSet::add_events(shared_ptr<Port> port, Event events)
{
	CHECK(sp_add_port_events(_structure, port->_structure,
		(enum sp_event) events));
}

void EventSet::wait(unsigned int timeout)
{
	CHECK(sp_wait(_structure, timeout));
}

Error::Error(string what)
{
	_what = what;
}

Error::~Error()
{
}

const char *Error::what() const throw()
{
	return _what.c_str();
}

InvalidArgument::InvalidArgument(string function) :
	Error(string("Invalid argument passed to ") + function),
	invalid_argument(string("Invalid argument passed to ") + function)
{
}

Failure::Failure(string function) :
	Error(function + " failed: " + sp_last_error_message()),
	system_error(sp_last_error_code(), system_category(),
		function + " failed: " + sp_last_error_message())
{
}

NotSupported::NotSupported(string function) :
	Error(function + " not possible: requested operation unsupported")
{
}

AllocationFailure::AllocationFailure(string function) :
	Error(function + " failed: memory allocation failed"),
	bad_alloc()
{
}

}
