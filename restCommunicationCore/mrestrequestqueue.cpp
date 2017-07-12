/*******************************************************************************
Copyright (C) 2016 Milo Solutions
Contact: https://www.milosolutions.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/


#include "mrestrequestqueue.h"
#include "mrestrequest.h"

/*!
 * \addtogroup Network
 * @{
 */

/*!
 * \class RequestQueue
 * \brief specialized queue with priority support
 */

void MRestRequestQueue::enqueue(MRestRequestPtr request)
{
    int index = count(); //start from tail
    bool higherPriority = true;
    //find first item that has no lower priority
    while (higherPriority && index > 0) {
        higherPriority = request->isHigherPriority(*at(--index));
    }
    //insert after first item with priority no lower than request
    insert(index + (higherPriority ? 0 : 1), request);
}

/*! @} */