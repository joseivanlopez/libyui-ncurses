/*
  Copyright (C) 2000-2012 Novell, Inc
  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2.1 of the
  License, or (at your option) version 3.0 of the License. This library
  is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
  License for more details. You should have received a copy of the GNU
  Lesser General Public License along with this library; if not, write
  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
  Floor, Boston, MA 02110-1301 USA
*/


/*-/

   File:       NCEmpty.h

   Author:     Michael Andres <ma@suse.de>

/-*/

#ifndef NCEmpty_h
#define NCEmpty_h

#include <iosfwd>

#include <yui/YEmpty.h>
#include "NCWidget.h"


class NCEmpty : public YEmpty, public NCWidget
{
private:

    friend std::ostream & operator<<( std::ostream & str, const NCEmpty & obj );

    NCEmpty & operator=( const NCEmpty & );
    NCEmpty( const NCEmpty & );


protected:

    virtual const char * location() const { return "NCEmpty"; }

public:

    NCEmpty( YWidget * parent );

    virtual ~NCEmpty();

    virtual int preferredWidth() { return YEmpty::preferredWidth(); }
    virtual int preferredHeight() { return YEmpty::preferredHeight(); }

    virtual void setSize( int newWidth, int newHeight );

    virtual void setEnabled( bool do_bv );
};


#endif // NCEmpty_h
