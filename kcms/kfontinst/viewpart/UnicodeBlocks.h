/* UnicodeBlocks.h */
/* THIS IS A GENERATED FILE. CHANGES WILL BE OVERWRITTEN. */
/* Generated by generate-unicode-tables.pl */
/* Generated from UCD version 5.0 */

#ifndef __UNICODE_BLOCKS_H__
#define __UNICODE_BLOCKS_H__

#include <KLocalizedString>
#include <qglobal.h>

struct TUnicodeBlock {
    quint32 start, end;
    const char *blockName;
};

static const struct TUnicodeBlock constUnicodeBlocks[] = {{0x0000, 0x007F, I18N_NOOP("Basic Latin")},
    {0x0080, 0x00FF, I18N_NOOP("Latin-1 Supplement")},
    {0x0100, 0x017F, I18N_NOOP("Latin Extended-A")},
    {0x0180, 0x024F, I18N_NOOP("Latin Extended-B")},
    {0x0250, 0x02AF, I18N_NOOP("IPA Extensions")},
    {0x02B0, 0x02FF, I18N_NOOP("Spacing Modifier Letters")},
    {0x0300, 0x036F, I18N_NOOP("Combining Diacritical Marks")},
    {0x0370, 0x03FF, I18N_NOOP("Greek and Coptic")},
    {0x0400, 0x04FF, I18N_NOOP("Cyrillic")},
    {0x0500, 0x052F, I18N_NOOP("Cyrillic Supplement")},
    {0x0530, 0x058F, I18N_NOOP("Armenian")},
    {0x0590, 0x05FF, I18N_NOOP("Hebrew")},
    {0x0600, 0x06FF, I18N_NOOP("Arabic")},
    {0x0700, 0x074F, I18N_NOOP("Syriac")},
    {0x0750, 0x077F, I18N_NOOP("Arabic Supplement")},
    {0x0780, 0x07BF, I18N_NOOP("Thaana")},
    {0x07C0, 0x07FF, I18N_NOOP("NKo")},
    {0x0900, 0x097F, I18N_NOOP("Devanagari")},
    {0x0980, 0x09FF, I18N_NOOP("Bengali")},
    {0x0A00, 0x0A7F, I18N_NOOP("Gurmukhi")},
    {0x0A80, 0x0AFF, I18N_NOOP("Gujarati")},
    {0x0B00, 0x0B7F, I18N_NOOP("Oriya")},
    {0x0B80, 0x0BFF, I18N_NOOP("Tamil")},
    {0x0C00, 0x0C7F, I18N_NOOP("Telugu")},
    {0x0C80, 0x0CFF, I18N_NOOP("Kannada")},
    {0x0D00, 0x0D7F, I18N_NOOP("Malayalam")},
    {0x0D80, 0x0DFF, I18N_NOOP("Sinhala")},
    {0x0E00, 0x0E7F, I18N_NOOP("Thai")},
    {0x0E80, 0x0EFF, I18N_NOOP("Lao")},
    {0x0F00, 0x0FFF, I18N_NOOP("Tibetan")},
    {0x1000, 0x109F, I18N_NOOP("Myanmar")},
    {0x10A0, 0x10FF, I18N_NOOP("Georgian")},
    {0x1100, 0x11FF, I18N_NOOP("Hangul Jamo")},
    {0x1200, 0x137F, I18N_NOOP("Ethiopic")},
    {0x1380, 0x139F, I18N_NOOP("Ethiopic Supplement")},
    {0x13A0, 0x13FF, I18N_NOOP("Cherokee")},
    {0x1400, 0x167F, I18N_NOOP("Unified Canadian Aboriginal Syllabics")},
    {0x1680, 0x169F, I18N_NOOP("Ogham")},
    {0x16A0, 0x16FF, I18N_NOOP("Runic")},
    {0x1700, 0x171F, I18N_NOOP("Tagalog")},
    {0x1720, 0x173F, I18N_NOOP("Hanunoo")},
    {0x1740, 0x175F, I18N_NOOP("Buhid")},
    {0x1760, 0x177F, I18N_NOOP("Tagbanwa")},
    {0x1780, 0x17FF, I18N_NOOP("Khmer")},
    {0x1800, 0x18AF, I18N_NOOP("Mongolian")},
    {0x1900, 0x194F, I18N_NOOP("Limbu")},
    {0x1950, 0x197F, I18N_NOOP("Tai Le")},
    {0x1980, 0x19DF, I18N_NOOP("New Tai Lue")},
    {0x19E0, 0x19FF, I18N_NOOP("Khmer Symbols")},
    {0x1A00, 0x1A1F, I18N_NOOP("Buginese")},
    {0x1B00, 0x1B7F, I18N_NOOP("Balinese")},
    {0x1D00, 0x1D7F, I18N_NOOP("Phonetic Extensions")},
    {0x1D80, 0x1DBF, I18N_NOOP("Phonetic Extensions Supplement")},
    {0x1DC0, 0x1DFF, I18N_NOOP("Combining Diacritical Marks Supplement")},
    {0x1E00, 0x1EFF, I18N_NOOP("Latin Extended Additional")},
    {0x1F00, 0x1FFF, I18N_NOOP("Greek Extended")},
    {0x2000, 0x206F, I18N_NOOP("General Punctuation")},
    {0x2070, 0x209F, I18N_NOOP("Superscripts and Subscripts")},
    {0x20A0, 0x20CF, I18N_NOOP("Currency Symbols")},
    {0x20D0, 0x20FF, I18N_NOOP("Combining Diacritical Marks for Symbols")},
    {0x2100, 0x214F, I18N_NOOP("Letter-Like Symbols")},
    {0x2150, 0x218F, I18N_NOOP("Number Forms")},
    {0x2190, 0x21FF, I18N_NOOP("Arrows")},
    {0x2200, 0x22FF, I18N_NOOP("Mathematical Operators")},
    {0x2300, 0x23FF, I18N_NOOP("Miscellaneous Technical")},
    {0x2400, 0x243F, I18N_NOOP("Control Pictures")},
    {0x2440, 0x245F, I18N_NOOP("Optical Character Recognition")},
    {0x2460, 0x24FF, I18N_NOOP("Enclosed Alphanumerics")},
    {0x2500, 0x257F, I18N_NOOP("Box Drawing")},
    {0x2580, 0x259F, I18N_NOOP("Block Elements")},
    {0x25A0, 0x25FF, I18N_NOOP("Geometric Shapes")},
    {0x2600, 0x26FF, I18N_NOOP("Miscellaneous Symbols")},
    {0x2700, 0x27BF, I18N_NOOP("Dingbats")},
    {0x27C0, 0x27EF, I18N_NOOP("Miscellaneous Mathematical Symbols-A")},
    {0x27F0, 0x27FF, I18N_NOOP("Supplemental Arrows-A")},
    {0x2800, 0x28FF, I18N_NOOP("Braille Patterns")},
    {0x2900, 0x297F, I18N_NOOP("Supplemental Arrows-B")},
    {0x2980, 0x29FF, I18N_NOOP("Miscellaneous Mathematical Symbols-B")},
    {0x2A00, 0x2AFF, I18N_NOOP("Supplemental Mathematical Operators")},
    {0x2B00, 0x2BFF, I18N_NOOP("Miscellaneous Symbols and Arrows")},
    {0x2C00, 0x2C5F, I18N_NOOP("Glagolitic")},
    {0x2C60, 0x2C7F, I18N_NOOP("Latin Extended-C")},
    {0x2C80, 0x2CFF, I18N_NOOP("Coptic")},
    {0x2D00, 0x2D2F, I18N_NOOP("Georgian Supplement")},
    {0x2D30, 0x2D7F, I18N_NOOP("Tifinagh")},
    {0x2D80, 0x2DDF, I18N_NOOP("Ethiopic Extended")},
    {0x2E00, 0x2E7F, I18N_NOOP("Supplemental Punctuation")},
    {0x2E80, 0x2EFF, I18N_NOOP("CJK Radicals Supplement")},
    {0x2F00, 0x2FDF, I18N_NOOP("Kangxi Radicals")},
    {0x2FF0, 0x2FFF, I18N_NOOP("Ideographic Description Characters")},
    {0x3000, 0x303F, I18N_NOOP("CJK Symbols and Punctuation")},
    {0x3040, 0x309F, I18N_NOOP("Hiragana")},
    {0x30A0, 0x30FF, I18N_NOOP("Katakana")},
    {0x3100, 0x312F, I18N_NOOP("Bopomofo")},
    {0x3130, 0x318F, I18N_NOOP("Hangul Compatibility Jamo")},
    {0x3190, 0x319F, I18N_NOOP("Kanbun")},
    {0x31A0, 0x31BF, I18N_NOOP("Bopomofo Extended")},
    {0x31C0, 0x31EF, I18N_NOOP("CJK Strokes")},
    {0x31F0, 0x31FF, I18N_NOOP("Katakana Phonetic Extensions")},
    {0x3200, 0x32FF, I18N_NOOP("Enclosed CJK Letters and Months")},
    {0x3300, 0x33FF, I18N_NOOP("CJK Compatibility")},
    {0x3400, 0x4DBF, I18N_NOOP("CJK Unified Ideographs Extension A")},
    {0x4DC0, 0x4DFF, I18N_NOOP("Yijing Hexagram Symbols")},
    {0x4E00, 0x9FFF, I18N_NOOP("CJK Unified Ideographs")},
    {0xA000, 0xA48F, I18N_NOOP("Yi Syllables")},
    {0xA490, 0xA4CF, I18N_NOOP("Yi Radicals")},
    {0xA700, 0xA71F, I18N_NOOP("Modifier Tone Letters")},
    {0xA720, 0xA7FF, I18N_NOOP("Latin Extended-D")},
    {0xA800, 0xA82F, I18N_NOOP("Syloti Nagri")},
    {0xA840, 0xA87F, I18N_NOOP("Phags-pa")},
    {0xAC00, 0xD7AF, I18N_NOOP("Hangul Syllables")},
    {0xD800, 0xDB7F, I18N_NOOP("High Surrogates")},
    {0xDB80, 0xDBFF, I18N_NOOP("High Private Use Surrogates")},
    {0xDC00, 0xDFFF, I18N_NOOP("Low Surrogates")},
    {0xE000, 0xF8FF, I18N_NOOP("Private Use Area")},
    {0xF900, 0xFAFF, I18N_NOOP("CJK Compatibility Ideographs")},
    {0xFB00, 0xFB4F, I18N_NOOP("Alphabetic Presentation Forms")},
    {0xFB50, 0xFDFF, I18N_NOOP("Arabic Presentation Forms-A")},
    {0xFE00, 0xFE0F, I18N_NOOP("Variation Selectors")},
    {0xFE10, 0xFE1F, I18N_NOOP("Vertical Forms")},
    {0xFE20, 0xFE2F, I18N_NOOP("Combining Half Marks")},
    {0xFE30, 0xFE4F, I18N_NOOP("CJK Compatibility Forms")},
    {0xFE50, 0xFE6F, I18N_NOOP("Small Form Variants")},
    {0xFE70, 0xFEFF, I18N_NOOP("Arabic Presentation Forms-B")},
    {0xFF00, 0xFFEF, I18N_NOOP("Half-Width and Full-Width Forms")},
    {0xFFF0, 0xFFFF, I18N_NOOP("Specials")},
    {0x10000, 0x1007F, I18N_NOOP("Linear B Syllabary")},
    {0x10080, 0x100FF, I18N_NOOP("Linear B Ideograms")},
    {0x10100, 0x1013F, I18N_NOOP("Aegean Numbers")},
    {0x10140, 0x1018F, I18N_NOOP("Ancient Greek Numbers")},
    {0x10300, 0x1032F, I18N_NOOP("Old Italic")},
    {0x10330, 0x1034F, I18N_NOOP("Gothic")},
    {0x10380, 0x1039F, I18N_NOOP("Ugaritic")},
    {0x103A0, 0x103DF, I18N_NOOP("Old Persian")},
    {0x10400, 0x1044F, I18N_NOOP("Deseret")},
    {0x10450, 0x1047F, I18N_NOOP("Shavian")},
    {0x10480, 0x104AF, I18N_NOOP("Osmanya")},
    {0x10800, 0x1083F, I18N_NOOP("Cypriot Syllabary")},
    {0x10900, 0x1091F, I18N_NOOP("Phoenician")},
    {0x10A00, 0x10A5F, I18N_NOOP("Kharoshthi")},
    {0x12000, 0x123FF, I18N_NOOP("Cuneiform")},
    {0x12400, 0x1247F, I18N_NOOP("Cuneiform Numbers and Punctuation")},
    {0x1D000, 0x1D0FF, I18N_NOOP("Byzantine Musical Symbols")},
    {0x1D100, 0x1D1FF, I18N_NOOP("Musical Symbols")},
    {0x1D200, 0x1D24F, I18N_NOOP("Ancient Greek Musical Notation")},
    {0x1D300, 0x1D35F, I18N_NOOP("Tai Xuan Jing Symbols")},
    {0x1D360, 0x1D37F, I18N_NOOP("Counting Rod Numerals")},
    {0x1D400, 0x1D7FF, I18N_NOOP("Mathematical Alphanumeric Symbols")},
    {0x20000, 0x2A6DF, I18N_NOOP("CJK Unified Ideographs Extension B")},
    {0x2F800, 0x2FA1F, I18N_NOOP("CJK Compatibility Ideographs Supplement")},
    {0xE0000, 0xE007F, I18N_NOOP("Tags")},
    {0xE0100, 0xE01EF, I18N_NOOP("Variation Selectors Supplement")},
    {0xF0000, 0xFFFFF, I18N_NOOP("Supplementary Private Use Area-A")},
    {0x100000, 0x10FFFF, I18N_NOOP("Supplementary Private Use Area-B")},
    {0x0, 0x0, nullptr}};

#endif
