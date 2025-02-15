/****************************************************************************
 * apps/include/graphics/nxwidgets/cglyphsliderhorizontal.hxx
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 *
 * Portions of this package derive from Woopsi (http://woopsi.org/) and
 * portions are original efforts.  It is difficult to determine at this
 * point what parts are original efforts and which parts derive from Woopsi.
 * However, in any event, the work of  Antony Dzeryn will be acknowledged
 * in most NxWidget files.  Thanks Antony!
 *
 *   Copyright (c) 2007-2011, Antony Dzeryn
 *   All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * * Neither the names "Woopsi", "Simian Zombie" nor the
 *   names of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Antony Dzeryn ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Antony Dzeryn BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef __APPS_INCLUDE_GRAPHICS_NXWIDGETS_CGLYPHSLIDERHORIZONTAL_HXX
#define __APPS_INCLUDE_GRAPHICS_NXWIDGETS_CGLYPHSLIDERHORIZONTAL_HXX

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "graphics/nxwidgets/csliderhorizontal.hxx"
#include "graphics/nxwidgets/cglyphsliderhorizontalgrip.hxx"

/****************************************************************************
 * Pre-Processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Implementation Classes
 ****************************************************************************/

#if defined(__cplusplus)

namespace NXWidgets
{
  /**
   * Widget providing a sliding "grip" that can be moved left and
   * right in the "gutter".  Essentially a scrollbar, but more
   * generic.
   */

  class CGlyphSliderHorizontal : public ISlider, public CNxWidget, public CWidgetEventHandler
  {
  protected:
    CGlyphSliderHorizontalGrip *m_grip; /**< Pointer to the grip. */
    int m_minimumValue;                 /**< Minimum value that the grip can represent. */
    int m_maximumValue;                 /**< Maximum value that the grip can represent. */
    int32_t m_value;                    /**< Current value of the slider. */
    nxgl_coord_t m_minimumGripWidth;    /**< Smallest width that the grip can become */
    nxgl_coord_t m_pageSize;            /**< Value of a page of data, used when clicking
                                             the gutter. */
    int32_t m_gutterWidth;              /**< Width of the gutter, taking into account
                                             any adjustments made to the width of the grip. */
    uint32_t m_contentSize;             /**< Number of values in the min/max range. */
    nxwidget_pixel_t m_fillColor;       /**< Fill color for left side of "fuel gague" */
    bool m_fill;                        /**< Set true if fill is active */
    uint32_t m_barThickness;            /**< Thickness (in pixels) of the bar */

    /**
     * Get the maximum possible value that the slider can represent.  Useful when
     * using the slider as a scrollbar, as the height of the grip prevents the full
     * range of values being accessed (intentionally).
     * The returned value is shifted left 16 places for more accuracy in fixed-point
     * calculations.
     *
     * @return The maximum possible value that the slider can represent.
     */

     int32_t getPhysicalMaximumValueWithBitshift(void) const;

    /**
     * Get the value represented by the top of the grip.
     * return The value represented by the top of the grip.
     */

     const int32_t getGripValue(void) const;

    /**
     * Draw the area of this widget that falls within the clipping region.
     * Called by the redraw() function to draw all visible regions.
     *
     * @param port The CGraphicsPort to draw to.
     * @see redraw()
     */

    virtual void drawContents(CGraphicsPort *port);

    /**
     * Draw the area of this widget that falls within the clipping region.
     * Called by the redraw() function to draw all visible regions.
     *
     * @param port The CGraphicsPort to draw to.
     * @see redraw()
     */

    virtual void drawBorder(CGraphicsPort *port);

    /**
     * Resize the slider to the new dimensions.
     *
     * @param width The new width.
     * @param height The new height.
     */

    virtual void onResize(nxgl_coord_t width, nxgl_coord_t height);

    /**
     * Moves the grip towards the mouse.
     *
     * @param x The x coordinate of the click.
     * @param y The y coordinate of the click.
     */

    virtual void onClick(nxgl_coord_t x, nxgl_coord_t y);

  public:

    /**
     * Constructor.
     *
     * @param control The widget control instance for the window.
     * @param x The x coordinate of the slider, relative to its parent.
     * @param y The y coordinate of the slider, relative to its parent.
     * @param width The width of the slider.
     * @param thickness The thickness of the slider.
     * @param gripBitmap The slider grip image
     * @param fillColor The color to use when filling the grip
     * @param fill True: The grip will be filled with fillColor
     */

    CGlyphSliderHorizontal(CWidgetControl *control,
                           nxgl_coord_t x, nxgl_coord_t y, nxgl_coord_t width,
                           nxgl_coord_t thickness, IBitmap *gripBitmap,
                           nxwidget_pixel_t fillColor, bool fill = true);

    /**
     * Destructor.
     *
     * NOTE: That the contained bitmap image is not destroyed when the image
     * container is destroyed.
     */

    virtual inline ~CGlyphSliderHorizontal(void) { }

    /**
     * Get the smallest value that the slider can represent.
     *
     * @return The smallest value.
     */

     inline const int getMinimumValue(void) const
     {
       return m_minimumValue;
     }

    /**
     * Get the largest value that the slider can represent.
     *
     * @return The largest value.
     */

     inline const int getMaximumValue(void) const
     {
       return m_maximumValue;
     }

    /**
     * Get the current value of the slider.
     *
     * return The current slider value.
     */

    inline const int getValue(void) const
    {
      return (int)(m_value >> 16);
    }

    /**
     * Get the value represented by the height of the grip. For sliders,
     * this would typically be 1 (so each new grip position is worth 1).
     * For scrollbars, this would be the height of the scrolling widget.
     *
     * @return The page size.
     */

    inline const nxgl_coord_t getPageSize(void) const
    {
      return m_pageSize;
    }

    /**
     * Set the smallest value that the slider can represent.
     *
     * @param value The smallest value.
     */

    inline void setMinimumValue(const int value)
    {
      m_minimumValue = value;
      m_contentSize  = m_maximumValue - m_minimumValue + 1;
      //resizeGrip();
    };

    /**
     * Set the largest value that the slider can represent.
     *
     * @param value The largest value.
     */

    inline void setMaximumValue(const int value)
    {
      m_maximumValue = value;
      m_contentSize  = m_maximumValue - m_minimumValue + 1;
      //resizeGrip();
    };

    /**
     * Set the value that of the slider.  This will reposition
     * and redraw the grip.
     *
     * @param value The new value.
     */

    void setValue(const int value);

    /**
     * Set the value that of the slider.  This will reposition and redraw
     * the grip.  The supplied value should be shifted left 16 places.
     * This ensures greater accuracy than the standard setValue() method if
     * the slider is being used as a scrollbar.
     *
     * @param value The new value.
     */

    void setValueWithBitshift(const int32_t value);

    /**
     * Set the page size represented by the grip.
     *
     * @param pageSize The page size.
     * @see getPageSize().
     */

    inline void setPageSize(const nxgl_coord_t pageSize)
    {
      m_pageSize = pageSize;
      //resizeGrip();
    };

    /**
     * Set the thickness of the slider bar
     *
     * @param thickness The slider bar thickness in pixels
     */

    inline void setBarThickness(const nxgl_coord_t thickness)
    {
      m_barThickness = thickness;
      redraw();
    };

    /**
     * Process events fired by the grip.
     *
     * @param e The event details.
     */

    virtual void handleDragEvent(const CWidgetEventArgs &e);

    /**
     * Get the smallest value that the slider can move through when
     * dragged.
     *
     * @return The smallest value that the slider can move through when
     * dragged.
     */

    nxgl_coord_t getMinimumStep(void) const;
  };
}

#endif // __cplusplus

#endif // __APPS_INCLUDE_GRAPHICS_NXWIDGETS_CGLYPHSLIDERHORIZONTAL_HXX
