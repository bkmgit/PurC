/**
 * @file purc-errors.h
 * @author Vincent Wei (https://github.com/VincentWei)
 * @date 2021/07/02
 * @brief The error codes of PurC.
 *
 * Copyright (C) 2021 FMSoft <https://www.fmsoft.cn>
 *
 * This file is a part of PurC (short for Purring Cat), an HVML interpreter.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PURC_PURC_ERRORS_H
#define PURC_PURC_ERRORS_H

#include <stdbool.h>
#include <stddef.h>

#include "purc-macros.h"

#define PURC_ERROR_OK                   0
#define PURC_ERROR_BAD_SYSTEM_CALL      1
#define PURC_ERROR_BAD_STDC_CALL        2
#define PURC_ERROR_OUT_OF_MEMORY        3
#define PURC_ERROR_INVALID_VALUE        4
#define PURC_ERROR_DUPLICATED           5
#define PURC_ERROR_NOT_IMPLEMENTED      6
#define PURC_ERROR_NO_INSTANCE          7
#define PURC_ERROR_TOO_LARGE_ENTITY     8
#define PURC_ERROR_BAD_ENCODING         9
#define PURC_ERROR_NOT_SUPPORTED        10
#define PURC_ERROR_OUTPUT               11
#define PURC_ERROR_TOO_SMALL_BUFF       12

// the first error codes for various modules:
#define PURC_ERROR_FIRST_VARIANT        100
#define PURC_ERROR_FIRST_RWSTREAM       200

#define PURC_ERROR_FIRST_EJSON          1100
#define PURC_ERROR_FIRST_HVML           1200
#define PURC_ERROR_FIRST_HTML           1300
#define PURC_ERROR_FIRST_XGML           1400
#define PURC_ERROR_FIRST_XML            1500

#define PURC_ERROR_FIRST_VDOM           2100
#define PURC_ERROR_FIRST_EDOM           2200
#define PURC_ERROR_FIRST_VCM            2300

// TODO: error codes for variant go here
enum pcvariant_error
{
    PCVARIANT_SUCCESS = PURC_ERROR_OK,
    PCVARIANT_INVALID_TYPE = PURC_ERROR_FIRST_VARIANT,
    PCVARIANT_STRING_NOT_UTF8,
    PCVARIANT_ERROR_NOT_FOUND,
};

// TODO: error codes for rwstream go here
enum pcrwstream_error
{
    PCRWSTREAM_SUCCESS = PURC_ERROR_OK,
    PCRWSTREAM_ERROR_FAILED = PURC_ERROR_FIRST_RWSTREAM,
    PCRWSTREAM_ERROR_FILE_TOO_BIG,
    PCRWSTREAM_ERROR_IO,
    PCRWSTREAM_ERROR_IS_DIR,
    PCRWSTREAM_ERROR_NO_SPACE,
    PCRWSTREAM_ERROR_NO_DEVICE_OR_ADDRESS,
    PCRWSTREAM_ERROR_OVERFLOW,
    PCRWSTREAM_ERROR_PIPE,
};

// TODO: error codes for ejson go here
enum pcejson_error
{
    PCEJSON_SUCCESS = PURC_ERROR_OK,
    PCEJSON_UNEXPECTED_CHARACTER_PARSE_ERROR = PURC_ERROR_FIRST_EJSON,
    PCEJSON_UNEXPECTED_NULL_CHARACTER_PARSE_ERROR,
    PCEJSON_UNEXPECTED_JSON_NUMBER_EXPONENT_PARSE_ERROR,
    PCEJSON_UNEXPECTED_JSON_NUMBER_FRACTION_PARSE_ERROR,
    PCEJSON_UNEXPECTED_JSON_NUMBER_INTEGER_PARSE_ERROR,
    PCEJSON_UNEXPECTED_JSON_NUMBER_PARSE_ERROR,
    PCEJSON_UNEXPECTED_RIGHT_BRACE_PARSE_ERROR,
    PCEJSON_UNEXPECTED_RIGHT_BRACKET_PARSE_ERROR,
    PCEJSON_UNEXPECTED_JSON_KEY_NAME_PARSE_ERROR,
    PCEJSON_UNEXPECTED_COMMA_PARSE_ERROR,
    PCEJSON_UNEXPECTED_JSON_KEYWORD_PARSE_ERROR,
    PCEJSON_UNEXPECTED_BASE64_PARSE_ERROR,
    PCEJSON_BAD_JSON_NUMBER_PARSE_ERROR,
    PCEJSON_BAD_JSON_PARSE_ERROR,
    PCEJSON_BAD_JSON_STRING_ESCAPE_ENTITY_PARSE_ERROR,
    PCEJSON_EOF_IN_STRING_PARSE_ERROR,
};

PCA_EXTERN_C_BEGIN

/**
 * purc_get_last_error:
 *
 * Returns: The last error code.
 */
PCA_EXPORT int
purc_get_last_error (void);

/**
 * purc_get_error_message:
 *
 * @errcode: the error code.
 *
 * Returns: The message for the specified error code.
 */
PCA_EXPORT const char*
purc_get_error_message (int errcode);

PCA_EXTERN_C_END

#endif /* not defined PURC_PURC_ERRORS_H */

