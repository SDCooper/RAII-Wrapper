#ifndef RFILESTREAM_H
#define RFILESTREAM_H

#include "raii/raii.h"
#include "legacy/FileStream.h"

using RFileStream = Template_Wrapper<FileStream, CREATOR(OpenStream), DESTROYER(Close)>;

#endif // RFILESTREAM_H
