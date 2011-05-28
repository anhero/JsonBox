/**
 * @file
 * @ingroup Helper
 */

#ifndef RB_UTFCONVERTER_H
#define RB_UTFCONVERTER_H


#include <string>
#include "RBString32.h"


namespace RedBox {
	/**
	 * This class is used to encode/decode/transcode UTF8, 16 and 32
	 * @ingroup Helper
	 */
	class UTFConvert {
	public:
		/**
		 * Encode the given UTF32 string to a 8bit UTF8 one. 
		 */
		static std::string encodeToUTF8(RB_String32 UTF32String);
		/**
		 * Decode the given 8bit UTF8 string to an UTF32 string.
		 */
		static RB_String32 decodeUTF8(std::string UTF8String);
	};
}

#endif
