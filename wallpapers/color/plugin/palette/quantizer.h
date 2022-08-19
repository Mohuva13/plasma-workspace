/*
    SPDX-FileCopyrightText: 2021 The Android Open Source Project
    SPDX-FileCopyrightText: 2022 Fushan Wen <qydwhotmail@gmail.com>

    SPDX-License-Identifier: Apache-2.0
*/

#ifndef QUANTIZER_H
#define QUANTIZER_H

#include <array>
#include <map>
#include <vector>

#include <QRgb>

/**
 * Definition of an algorithm that receives pixels and outputs a list of colors.
 *
 * @see platform_frameworks_base/base/core/java/com/android/internal/graphics/palette/QuantizerMap.java
 */
class Quantizer
{
public:
    virtual ~Quantizer() = default;

    /**
     * Create colors representative of the colors present in pixels.
     *
     * @param pixels Set of ARGB representation of a color.
     * @param maxColors number of colors to generate
     */
    virtual void quantize(const std::vector<QRgb> &pixels, int maxColors) = 0;

    /**
     * List of colors generated by previous call to quantize.
     */
    const std::vector<QRgb> &getQuantizedColors() const;

    /**
     * Keys are color ints, values are the number of pixels in the image matching that color int
     */
    const std::map<QRgb, unsigned> &inputPixelToCount() const;

protected:
    std::vector<QRgb> m_palette;
    std::map<QRgb, unsigned> m_inputPixelToCount;
};

/**
 * Converts a set of pixels/colors into a map with keys of unique colors, and values of the count
 * of the unique color in the original set of pixels.
 *
 * This allows other quantizers to get a significant speed boost by simply running this quantizer,
 * and then performing operations using the map, rather than for each pixel.
 */
class QuantizerMap : public Quantizer
{
public:
    void quantize(const std::vector<QRgb> &pixels, int) override;
};

#endif // QUANTIZER_H
