#ifndef IBASICDATA_H
#define IBASICDATA_H

#include <QMutex>

#include "uv_state.h"

/** \brief Basic interface for accessing data in UV_state class
 *
 */
class IBasicData
{
public:
    IBasicData();

protected:
    /// Static mutex variable
    static QMutex UVMutex;
    /// Static UV_State variable, which we will be accessing
    static UV_State UVState;
};

#endif // IBASICDATA_H
