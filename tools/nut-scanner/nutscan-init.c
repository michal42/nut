/*
 *  Copyright (C) 2011 - EATON
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/*! \file nutscan-init.c
    \brief init functions for nut scanner library
    \author Frederic Bohe <fredericbohe@eaton.com>
*/

#include "common.h"
#include <ltdl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int nutscan_avail_avahi = 0;
int nutscan_avail_ipmi = 0;
int nutscan_avail_nut = 0;
int nutscan_avail_snmp = 0;
int nutscan_avail_usb = 0;
int nutscan_avail_xml_http = 0;

int nutscan_load_usb_library(const char *libname_path);
int nutscan_load_snmp_library(const char *libname_path);
int nutscan_load_neon_library(const char *libname_path);
int nutscan_load_avahi_library(const char *libname_path);
int nutscan_load_ipmi_library(const char *libname_path);
int nutscan_load_upsclient_library(const char *libname_path);

void nutscan_init(void)
{
#ifdef WITH_USB
	nutscan_avail_usb = nutscan_load_usb_library(get_libname("libusb-0.1.so"));
#endif
#ifdef WITH_SNMP
	nutscan_avail_snmp = nutscan_load_snmp_library(get_libname("libnetsnmp.so"));
#endif
#ifdef WITH_NEON
	nutscan_avail_xml_http = nutscan_load_neon_library(get_libname("libneon.so"));
#endif
#ifdef WITH_AVAHI
	nutscan_avail_avahi = nutscan_load_avahi_library(get_libname("libavahi-client.so"));
#endif
#ifdef WITH_FREEIPMI
	nutscan_avail_ipmi = nutscan_load_ipmi_library(get_libname("libfreeipmi.so"));
#endif
	nutscan_avail_nut = nutscan_load_upsclient_library(get_libname("libupsclient.so"));
}

void nutscan_free(void)
{
	if( nutscan_avail_usb ) {
		lt_dlexit();
	}
	if( nutscan_avail_snmp ) {
		lt_dlexit();
	}
	if( nutscan_avail_xml_http ) {
		lt_dlexit();
	}
	if( nutscan_avail_avahi ) {
		lt_dlexit();
	}
	if( nutscan_avail_ipmi ) {
		lt_dlexit();
	}
	if( nutscan_avail_nut ) {
		lt_dlexit();
	}
}
