/*---------------------------------------------------------------------\
|                                                                      |
|                      __   __    ____ _____ ____                      |
|                      \ \ / /_ _/ ___|_   _|___ \                     |
|                       \ V / _` \___ \ | |   __) |                    |
|                        | | (_| |___) || |  / __/                     |
|                        |_|\__,_|____/ |_| |_____|                    |
|                                                                      |
|                               core system                            |
|                                                        (C) SuSE GmbH |
\----------------------------------------------------------------------/

   File:       NCurses.h

   Author:     Michael Andres <ma@suse.de>
   Maintainer: Michael Andres <ma@suse.de>

/-*/
#ifndef NCurses_h
#define NCurses_h

#include <iostream>
#include <string>
#include <set>

using namespace std;

#include <YCP.h>
#include "YEvent.h"

#include <curses.h>	/* curses.h: #define  NCURSES_CH_T cchar_t */
#include <wchar.h>

#include "ncursesw.h"
#include "ncursesp.h"
#include "position.h"
#include "NCstyle.h"

class NCWidget;
class NCDialog;

///////////////////////////////////////////////////////////////////

class NCursesError {

  public:

    int    errval_i;
    string errmsg_t;

    NCursesError( char * msg = "unknown error", ... );
    NCursesError( int val, char * msg = "unknown error", ... );

    virtual ~NCursesError() {}

    NCursesError & NCError( char * msg = "unknown error", ... );
    NCursesError & NCError( int val, char * msg = "unknown error", ... );

    virtual const char * location() const { return "NCurses"; }
};

extern std::ostream & operator<<( std::ostream & STREAM, const NCursesError & OBJ );

///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////

class NCursesEvent {

  public:

    enum Type {
      handled = -1,
      none    = 0,
      cancel,
      timeout,
      button,
      menu,
      key
    };

    enum DETAIL {
      NODETAIL   = -1,
      CONTINUE   = -2,
      USERDEF    = -3
    };

    Type       type;
    NCWidget * widget;
    YCPValue   selection;	// used for MenuEvent (the menu selection)

    YCPValue  	result;		// can be used for any result
    
    string	keySymbol;	// used for KeyEvent (symbol pressed key)
    
    int        detail;
    
    YEvent::EventReason reason;

    NCursesEvent( Type t = none, YEvent::EventReason r = YEvent::UnknownReason )
      : type     ( t )
      , widget   ( 0 )
      , selection( YCPNull() )
      , result   ( YCPNull() )
      , detail   ( NODETAIL )
      , reason   ( r )
    {}
    virtual ~NCursesEvent() {}

    // not operator bool() which would be propagated to almost everything ;)
    operator void*() const { return type != none ? (void*)1 : (void*)0; }

    bool operator==( const NCursesEvent & e ) const { return type == e.type; }
    bool operator!=( const NCursesEvent & e ) const { return type != e.type; }

    bool isReturnEvent()   const { return type > none; }
    bool isInternalEvent() const { return type < none; }

    
    // Some predefined events that can be used as return values
    
    static const NCursesEvent Activated;
    static const NCursesEvent SelectionChanged;
    static const NCursesEvent ValueChanged;
};

extern std::ostream & operator<<( std::ostream & STREAM, const NCursesEvent & OBJ );

///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//
//	CLASS NAME : NCurses
//
//	DESCRIPTION :
//
class NCurses {

  friend std::ostream & operator<<( std::ostream & STREAM, const NCurses & OBJ );

  NCurses & operator=( const NCurses & );
  NCurses            ( const NCurses & );

  private:

    static NCurses * myself;

    static WINDOW * ripped_w;
    static int ripinit( WINDOW * , int );

  protected:

    SCREEN * theTerm;
    string   myTerm;
    string   envTerm;
    WINDOW * title_w;
    string   title_t;

    NCstyle *      styleset;
    NCursesPanel * stdpan;

    void init();
    bool initialized() const { return stdpan; }

    virtual bool title_line()   { return true; }
    virtual bool want_colors()  { return true; }
    virtual void setup_screen();
    virtual void init_title();
    virtual void init_screen();

  public:

    NCurses();
    virtual ~NCurses();

    static int cols()  { return ::COLS; }
    static int lines() { return ::LINES; }

    void run();

  public:

    static const NCstyle & style();

    static void Update();
    static void Redraw();
    static void Refresh();
    static void SetTitle( const string & str );
    static void ScreenShot( const string & name = "screen.shot" );

    static void drawTitle();

  public:
    // actually not for public use
    static void ForgetDlg( NCDialog * dlg_r );
    static void RememberDlg( NCDialog * dlg_r );
    static void ResizeEvent();
  private:
    static set<NCDialog*> _knownDlgs;
};

///////////////////////////////////////////////////////////////////

#define CTRL(x)     ((x) & 0x1f)
#define KEY_TAB     011
#define KEY_RETURN  012
#define KEY_ESC     033
#define KEY_SPACE   040
#define KEY_HOTKEY  KEY_MAX+1

///////////////////////////////////////////////////////////////////

#endif // NCurses_h