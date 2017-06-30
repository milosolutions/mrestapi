/*******************************************************************************
  Copyright (C) 2016 Milo Solutions
  Contact: https://www.milosolutions.com

  This file is part of Milo Code Database, which is a collection of useful code
  snippets often reused within Milo Solutions. As such, this code is present in
  many projects done by Milo Solutions and does not constitute a copyright
  infridgement.

  You are entitled to do anything you please with this code, just as with the
  rest of code you bought. Files not containing this notice were written
  specifically for this project and have not been shared with any other party
  within or without Milo.
*******************************************************************************/

#include "logoutrequest.h"

/*!
 * \ingroup Network
 * \ingroup Example
 * @{
 */

/*!
 * \class LogoutRequest
 * \brief Use this class to log out of the web API
 *
 * Anonymous (not logged in) user can still browse the shop.
 */

/*!
 * Default constructor. Uses "login" API and sends out a DELETE HTTP message.
 */
LogoutRequest::LogoutRequest() : MrBabuRequest("login")
{
    mPriority = Priority::High;
    mType = Type::Delete;
}

/*!
 * Does nothing - for now.
 */
void LogoutRequest::parse()
{
    //qDebug() << mReplyDocument.toJson();
}

/*! @} */
