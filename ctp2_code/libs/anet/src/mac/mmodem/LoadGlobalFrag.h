/*
Copyright (C) 1995-2001 Activision, Inc.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/


static short	gvRef;
static long		gparID;
#define kTransportNames		11000
#define kTransportPath		12000
#define kTransportType		'shlb'
#define kTransportCreator	'mwNT'
void SetBasePath(void);
OSErr LoadTransport(char *transportName);
void unloadTransport(void);
OSErr GetData(unsigned long* value);
OSErr SetData(unsigned long value);
// MAD ** OSErr SetupData(CFragConnectionID connID);
