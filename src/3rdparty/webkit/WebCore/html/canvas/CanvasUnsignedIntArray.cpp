/*
 * Copyright (C) 2009 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"

#if ENABLE(3D_CANVAS)

#include "CanvasArrayBuffer.h"
#include "CanvasUnsignedIntArray.h"

namespace WebCore {
    
    PassRefPtr<CanvasUnsignedIntArray> CanvasUnsignedIntArray::create(unsigned length)
    {
        RefPtr<CanvasArrayBuffer> buffer = CanvasArrayBuffer::create(length * sizeof(unsigned int));
        return create(buffer, 0, length);
    }

    PassRefPtr<CanvasUnsignedIntArray> CanvasUnsignedIntArray::create(unsigned int* array, unsigned length)
    {
        RefPtr<CanvasUnsignedIntArray> a = CanvasUnsignedIntArray::create(length);
        for (unsigned i = 0; i < length; ++i)
            a->set(i, array[i]);
        return a;
    }

    PassRefPtr<CanvasUnsignedIntArray> CanvasUnsignedIntArray::create(PassRefPtr<CanvasArrayBuffer> buffer,
                                                                      int offset,
                                                                      unsigned length)
    {
        // Make sure the offset results in valid alignment.
        if ((offset % sizeof(unsigned int)) != 0) {
            return NULL;
        }

        if (buffer) {
            // Check to make sure we are talking about a valid region of
            // the given CanvasArrayBuffer's storage.
            if ((offset + (length * sizeof(unsigned int))) > buffer->byteLength())
                return NULL;
        }

        return adoptRef(new CanvasUnsignedIntArray(buffer, offset, length));
    }
    
    CanvasUnsignedIntArray::CanvasUnsignedIntArray(PassRefPtr<CanvasArrayBuffer> buffer, int offset, unsigned length)
        : CanvasArray(buffer, offset)
        , m_size(length)
    {
    }
    
    unsigned CanvasUnsignedIntArray::length() const {
        return m_size;
    }
        
    unsigned CanvasUnsignedIntArray::sizeInBytes() const {
        return length() * sizeof(unsigned int);
    }
}

#endif // ENABLE(3D_CANVAS)