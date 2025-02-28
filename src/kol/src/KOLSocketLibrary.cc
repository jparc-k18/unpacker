// -*- C++ -*-

//  @file   kolsocket.cc
//  @brief  
//  @author Hirofumi Fujii <hirofumi.fujii@kek.jp>
//  @date   Mon Nov 27 05:54:48 2006 UTC
// 
//  $Id: kolsocket.h,v 1.1.1.1 2007/03/28 07:50:17 cvs Exp $
//  $Log: kolsocket.h,v $
//  Revision 1.1.1.1  2007/03/28 07:50:17  cvs
//  prototype-1.2
// 
//  Revision 1.1.1.1  2007/01/31 13:37:53  kensh
//  Initial version.

#include "KOLSocketLibrary.hh"

namespace kol
{

//______________________________________________________________________________
SocketLibrary::SocketLibrary()
  : m_libloaded()
{
  m_libloaded = true;
}

//______________________________________________________________________________
SocketLibrary::~SocketLibrary()
{
}

//______________________________________________________________________________
bool 
SocketLibrary::isloaded() const throw()
{
  return m_libloaded;
}

}
