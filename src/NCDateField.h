/*
  Copyright (C) 2014 Novell, Inc
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

   File:       NCDateField.h

   Author:     Angelo Naselli <anaselli@linux.it>

/-*/

#ifndef NCDateField_h
#define NCDateField_h

#include <iosfwd>

#include <yui/YDateField.h>
#include "NCWidget.h"


class NCDateField : public YDateField, public NCWidget
{

  friend std::ostream & operator<< ( std::ostream & STREAM, const NCDateField & OBJ );

  NCDateField & operator= ( const NCDateField & );
  NCDateField ( const NCDateField & );

private:

  NClabel  label;
  std::wstring   buffer;

  NCursesWindow * lwin;
  NCursesWindow * twin;

  unsigned fldstart;
  unsigned fldlength;
  unsigned curpos;
  static const unsigned maxFldLength;

  NCstring validChars;

  bool     returnOnReturn_b;

  void setDefsze();
  void tUpdate();

  bool     bufferFull() const;
  unsigned maxCursor() const;

protected:

  virtual const char * location() const
  {
    return "NCDateField";
  }

  virtual void wCreate ( const wrect & newrect );
  virtual void wDelete();

  virtual void wRedraw();

  bool validKey ( wint_t key ) const;

public:

  NCDateField ( YWidget * parent,
                const std::string & label
              );
  virtual ~NCDateField();

  virtual int preferredWidth();
  virtual int preferredHeight();

  virtual void setSize ( int newWidth, int newHeight );

  virtual void setLabel ( const std::string & nlabel );

  virtual void setValue ( const std::string & ntext );
  virtual std::string value();

  virtual void setEnabled ( bool do_bv );

  virtual NCursesEvent wHandleInput ( wint_t key );

  virtual bool setKeyboardFocus()
  {
    if ( !grabFocus() )
      return YWidget::setKeyboardFocus();

    return true;
  }

  void setCurPos ( unsigned pos )
  {
    curpos = pos;
  }
};


#endif // NCDateField_h
