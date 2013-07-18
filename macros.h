/*
Copyright 2011 Will Stephenson <wstephenson@kde.org>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) version 3, or any
later version accepted by the membership of KDE e.V. (or its
successor approved by the membership of KDE e.V.), which shall
act as a proxy defined in Section 6 of version 3 of the license.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MM_MACROS_H
#define MM_MACROS_H

#include <QAtomicPointer>

# define MM_GLOBAL_STATIC_STRUCT_NAME(NAME)
typedef void (*MmCleanUpFunction)();
class MmCleanUpGlobalStatic
{
    public:
        MmCleanUpFunction func;

        inline ~MmCleanUpGlobalStatic() { func(); }
};

template<typename T>
T* get(const QBasicAtomicPointer<T> &t)
{
#if QT_VERSION > 0x50000
    return t.load();
#else
    return t;
#endif
}

template<typename T>
void store(QBasicAtomicPointer<T> &t, T *val)
{
#if QT_VERSION > 0x50000
    t.store(val);
#else
    t = val;
#endif
}

#define MM_GLOBAL_STATIC(TYPE, NAME) MM_GLOBAL_STATIC_WITH_ARGS(TYPE, NAME, ())
#define MM_GLOBAL_STATIC_WITH_ARGS(TYPE, NAME, ARGS)                            \
static QBasicAtomicPointer<TYPE > _mm_static_##NAME = Q_BASIC_ATOMIC_INITIALIZER(0); \
static bool _mm_static_##NAME##_destroyed;                                      \
static struct MM_GLOBAL_STATIC_STRUCT_NAME(NAME)                                \
{                                                                              \
    inline bool isDestroyed() const                                            \
    {                                                                          \
        return _mm_static_##NAME##_destroyed;                                   \
    }                                                                          \
    inline bool exists() const                                                 \
    {                                                                          \
        return get(_mm_static_##NAME) != 0;                                         \
    }                                                                          \
    inline operator TYPE*()                                                    \
    {                                                                          \
        return operator->();                                                   \
    }                                                                          \
    inline TYPE *operator->()                                                  \
    {                                                                          \
        if (!get(_mm_static_##NAME)) {                                               \
            if (isDestroyed()) {                                               \
                qFatal("Fatal Error: Accessed global static '%s *%s()' after destruction. " \
                       "Defined at %s:%d", #TYPE, #NAME, __FILE__, __LINE__);  \
            }                                                                  \
            TYPE *x = new TYPE ARGS;                                           \
            if (!_mm_static_##NAME.testAndSetOrdered(0, x)                      \
                && get(_mm_static_##NAME) != x ) {                                   \
                delete x;                                                      \
            } else {                                                           \
                static MmCleanUpGlobalStatic cleanUpObject = { destroy };       \
            }                                                                  \
        }                                                                      \
        return get(_mm_static_##NAME);                                               \
    }                                                                          \
    inline TYPE &operator*()                                                   \
    {                                                                          \
        return *operator->();                                                  \
    }                                                                          \
    static void destroy()                                                      \
    {                                                                          \
        _mm_static_##NAME##_destroyed = true;                                   \
        TYPE *x = get(_mm_static_##NAME);                                            \
        store(_mm_static_##NAME,static_cast<TYPE *>(0));                                                  \
        delete x;                                                              \
    }                                                                          \
} NAME;

#endif
