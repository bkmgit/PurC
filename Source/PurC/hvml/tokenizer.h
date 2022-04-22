/*
 * @file tokenizer.h
 * @author Xue Shuming
 * @date 2022/02/08
 * @brief The api of hvml tokenizer.
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
 *
 */

#ifndef PURC_HVML_TOKENIZER_H
#define PURC_HVML_TOKENIZER_H

#include "config.h"

#include "private/instance.h"
#include "private/errors.h"
#include "private/debug.h"
#include "private/utils.h"

enum tokenizer_state {
    TKZ_STATE_FIRST = 0,

    TKZ_STATE_DATA = TKZ_STATE_FIRST,
    TKZ_STATE_TAG_OPEN,
    TKZ_STATE_END_TAG_OPEN,
    TKZ_STATE_TAG_CONTENT,
    TKZ_STATE_TAG_NAME,
    TKZ_STATE_BEFORE_ATTRIBUTE_NAME,
    TKZ_STATE_ATTRIBUTE_NAME,
    TKZ_STATE_AFTER_ATTRIBUTE_NAME,
    TKZ_STATE_BEFORE_ATTRIBUTE_VALUE,
    TKZ_STATE_AFTER_ATTRIBUTE_VALUE,
    TKZ_STATE_SELF_CLOSING_START_TAG,
    TKZ_STATE_MARKUP_DECLARATION_OPEN,
    TKZ_STATE_COMMENT_START,
    TKZ_STATE_COMMENT_START_DASH,
    TKZ_STATE_COMMENT,
    TKZ_STATE_COMMENT_LESS_THAN_SIGN,
    TKZ_STATE_COMMENT_LESS_THAN_SIGN_BANG,
    TKZ_STATE_COMMENT_LESS_THAN_SIGN_BANG_DASH,
    TKZ_STATE_COMMENT_LESS_THAN_SIGN_BANG_DASH_DASH,
    TKZ_STATE_COMMENT_END_DASH,
    TKZ_STATE_COMMENT_END,
    TKZ_STATE_COMMENT_END_BANG,
    TKZ_STATE_DOCTYPE,
    TKZ_STATE_BEFORE_DOCTYPE_NAME,
    TKZ_STATE_DOCTYPE_NAME,
    TKZ_STATE_AFTER_DOCTYPE_NAME,
    TKZ_STATE_AFTER_DOCTYPE_PUBLIC_KEYWORD,
    TKZ_STATE_BEFORE_DOCTYPE_PUBLIC_ID,
    TKZ_STATE_DOCTYPE_PUBLIC_ID_DOUBLE_QUOTED,
    TKZ_STATE_DOCTYPE_PUBLIC_ID_SINGLE_QUOTED,
    TKZ_STATE_AFTER_DOCTYPE_PUBLIC_ID,
    TKZ_STATE_BETWEEN_DOCTYPE_PUBLIC_ID_AND_SYSTEM_INFO,
    TKZ_STATE_AFTER_DOCTYPE_SYSTEM_KEYWORD,
    TKZ_STATE_BEFORE_DOCTYPE_SYSTEM,
    TKZ_STATE_DOCTYPE_SYSTEM_DOUBLE_QUOTED,
    TKZ_STATE_DOCTYPE_SYSTEM_SINGLE_QUOTED,
    TKZ_STATE_AFTER_DOCTYPE_SYSTEM,
    TKZ_STATE_BOGUS_DOCTYPE,
    TKZ_STATE_CDATA_SECTION,
    TKZ_STATE_CDATA_SECTION_BRACKET,
    TKZ_STATE_CDATA_SECTION_END,
    TKZ_STATE_CHARACTER_REFERENCE,
    TKZ_STATE_NAMED_CHARACTER_REFERENCE,
    TKZ_STATE_AMBIGUOUS_AMPERSAND,
    TKZ_STATE_NUMERIC_CHARACTER_REFERENCE,
    TKZ_STATE_HEXADECIMAL_CHARACTER_REFERENCE_START,
    TKZ_STATE_DECIMAL_CHARACTER_REFERENCE_START,
    TKZ_STATE_HEXADECIMAL_CHARACTER_REFERENCE,
    TKZ_STATE_DECIMAL_CHARACTER_REFERENCE,
    TKZ_STATE_NUMERIC_CHARACTER_REFERENCE_END,
    TKZ_STATE_SPECIAL_ATTRIBUTE_OPERATOR_IN_ATTRIBUTE_NAME,
    TKZ_STATE_SPECIAL_ATTRIBUTE_OPERATOR_AFTER_ATTRIBUTE_NAME,
    TKZ_STATE_TEXT_CONTENT,
    TKZ_STATE_JSONTEXT_CONTENT,
    TKZ_STATE_JSONEE_ATTRIBUTE_VALUE_DOUBLE_QUOTED,
    TKZ_STATE_JSONEE_ATTRIBUTE_VALUE_SINGLE_QUOTED,
    TKZ_STATE_JSONEE_ATTRIBUTE_VALUE_UNQUOTED,
    TKZ_STATE_EJSON_DATA,
    TKZ_STATE_EJSON_FINISHED,
    TKZ_STATE_EJSON_CONTROL,
    TKZ_STATE_EJSON_LEFT_BRACE,
    TKZ_STATE_EJSON_RIGHT_BRACE,
    TKZ_STATE_EJSON_LEFT_BRACKET,
    TKZ_STATE_EJSON_RIGHT_BRACKET,
    TKZ_STATE_EJSON_LEFT_PARENTHESIS,
    TKZ_STATE_EJSON_RIGHT_PARENTHESIS,
    TKZ_STATE_EJSON_DOLLAR,
    TKZ_STATE_EJSON_AFTER_VALUE,
    TKZ_STATE_EJSON_BEFORE_NAME,
    TKZ_STATE_EJSON_AFTER_NAME,
    TKZ_STATE_EJSON_NAME_UNQUOTED,
    TKZ_STATE_EJSON_NAME_SINGLE_QUOTED,
    TKZ_STATE_EJSON_NAME_DOUBLE_QUOTED,
    TKZ_STATE_EJSON_VALUE_SINGLE_QUOTED,
    TKZ_STATE_EJSON_VALUE_DOUBLE_QUOTED,
    TKZ_STATE_EJSON_AFTER_VALUE_DOUBLE_QUOTED,
    TKZ_STATE_EJSON_VALUE_TWO_DOUBLE_QUOTED,
    TKZ_STATE_EJSON_VALUE_THREE_DOUBLE_QUOTED,
    TKZ_STATE_EJSON_KEYWORD,
    TKZ_STATE_EJSON_AFTER_KEYWORD,
    TKZ_STATE_EJSON_BYTE_SEQUENCE,
    TKZ_STATE_EJSON_AFTER_BYTE_SEQUENCE,
    TKZ_STATE_EJSON_HEX_BYTE_SEQUENCE,
    TKZ_STATE_EJSON_BINARY_BYTE_SEQUENCE,
    TKZ_STATE_EJSON_BASE64_BYTE_SEQUENCE,
    TKZ_STATE_EJSON_VALUE_NUMBER,
    TKZ_STATE_EJSON_AFTER_VALUE_NUMBER,
    TKZ_STATE_EJSON_VALUE_NUMBER_INTEGER,
    TKZ_STATE_EJSON_VALUE_NUMBER_FRACTION,
    TKZ_STATE_EJSON_VALUE_NUMBER_EXPONENT,
    TKZ_STATE_EJSON_VALUE_NUMBER_EXPONENT_INTEGER,
    TKZ_STATE_EJSON_VALUE_NUMBER_SUFFIX_INTEGER,
    TKZ_STATE_EJSON_VALUE_NUMBER_HEX,
    TKZ_STATE_EJSON_VALUE_NUMBER_HEX_SUFFIX,
    TKZ_STATE_EJSON_AFTER_VALUE_NUMBER_HEX,
    TKZ_STATE_EJSON_VALUE_NUMBER_INFINITY,
    TKZ_STATE_EJSON_VALUE_NAN,
    TKZ_STATE_EJSON_STRING_ESCAPE,
    TKZ_STATE_EJSON_STRING_ESCAPE_FOUR_HEXADECIMAL_DIGITS,
    TKZ_STATE_EJSON_JSONEE_VARIABLE,
    TKZ_STATE_EJSON_JSONEE_FULL_STOP_SIGN,
    TKZ_STATE_EJSON_JSONEE_KEYWORD,
    TKZ_STATE_EJSON_JSONEE_STRING,
    TKZ_STATE_EJSON_AFTER_JSONEE_STRING,
    TKZ_STATE_EJSON_TEMPLATE_DATA,
    TKZ_STATE_EJSON_TEMPLATE_DATA_LESS_THAN_SIGN,
    TKZ_STATE_EJSON_TEMPLATE_DATA_END_TAG_OPEN,
    TKZ_STATE_EJSON_TEMPLATE_DATA_END_TAG_NAME,
    TKZ_STATE_EJSON_TEMPLATE_FINISHED,
    TKZ_STATE_EJSON_AMPERSAND,
    TKZ_STATE_EJSON_OR_SIGN,
    TKZ_STATE_EJSON_SEMICOLON,
    TKZ_STATE_EJSON_CJSONEE_FINISHED,

    TKZ_STATE_LAST_STATE = TKZ_STATE_EJSON_CJSONEE_FINISHED,
};


PCA_EXTERN_C_BEGIN

PCA_INLINE bool is_whitespace(uint32_t uc)
{
    return uc == ' ' || uc == '\x0A' || uc == '\x09' || uc == '\x0C';
}

PCA_INLINE uint32_t to_ascii_lower_unchecked(uint32_t uc)
{
    return uc | 0x20;
}

PCA_INLINE bool is_ascii(uint32_t uc)
{
    return !(uc & ~0x7F);
}

PCA_INLINE bool is_ascii_lower(uint32_t uc)
{
    return uc >= 'a' && uc <= 'z';
}

PCA_INLINE bool is_ascii_upper(uint32_t uc)
{
     return uc >= 'A' && uc <= 'Z';
}

PCA_INLINE bool is_ascii_space(uint32_t uc)
{
    return uc <= ' ' && (uc == ' ' || (uc <= 0xD && uc >= 0x9));
}

PCA_INLINE bool is_ascii_digit(uint32_t uc)
{
    return uc >= '0' && uc <= '9';
}

PCA_INLINE bool is_ascii_binary_digit(uint32_t uc)
{
     return uc == '0' || uc == '1';
}

PCA_INLINE bool is_ascii_hex_digit(uint32_t uc)
{
     return is_ascii_digit(uc) || (
             to_ascii_lower_unchecked(uc) >= 'a' &&
             to_ascii_lower_unchecked(uc) <= 'f'
             );
}

PCA_INLINE bool is_ascii_upper_hex_digit(uint32_t uc)
{
     return is_ascii_digit(uc) || (uc >= 'A' && uc <= 'F');
}

PCA_INLINE bool is_ascii_lower_hex_digit(uint32_t uc)
{
     return is_ascii_digit(uc) || (uc >= 'a' && uc <= 'f');
}

PCA_INLINE bool is_ascii_octal_digit(uint32_t uc)
{
     return uc >= '0' && uc <= '7';
}

PCA_INLINE bool is_ascii_alpha(uint32_t uc)
{
    return is_ascii_lower(to_ascii_lower_unchecked(uc));
}

PCA_INLINE bool is_ascii_alpha_numeric(uint32_t uc)
{
    return is_ascii_digit(uc) || is_ascii_alpha(uc);
}

#define PCHVML_END_OF_FILE       0
PCA_INLINE bool is_eof(uint32_t uc)
{
    return uc == PCHVML_END_OF_FILE;
}

PCA_INLINE bool is_separator(uint32_t c)
{
    switch (c) {
        case '{':
        case '}':
        case '[':
        case ']':
        case '<':
        case '>':
        case '(':
        case ')':
        case ',':
        case ':':
            return true;
    }
    return false;
}

PCA_INLINE bool is_attribute_value_operator(uint32_t c)
{
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '~':
        case '^':
        case '$':
            return true;
    }
    return false;
}

PCA_INLINE bool is_context_variable(uint32_t c)
{
    switch (c) {
        case '?':
        case '<':
        case '@':
        case '!':
        case ':':
        case '=':
        case '%':
            return true;
    }
    return false;
}

PCA_EXTERN_C_END

#endif /* PURC_HVML_TOKENIZER_H */
