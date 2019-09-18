#ifndef THEA_TFI_PARSER_H
#define THEA_TFI_PARSER_H

#include <SdFat.h>

#include "ym2612.h"

/* TFI Patch parser

See http://vgmrips.net/wiki/TFI_File_Format
*/

namespace thea {
namespace tfi {

bool load(SdFile &file, SdFile *folder, thea::ym2612::ChannelPatch *patch);
void save(SdFile &file, thea::ym2612::ChannelPatch &patch);
void serialize(thea::ym2612::ChannelPatch &patch, uint8_t* dest);

} // namespace tfi
} // namespace thea

#endif
