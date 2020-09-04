/****************************************************************************
 * Copyright (C) 2015 Dimok
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#pragma once

#include <vector>
#include <mutex>
#include "GuiElement.h"
#include "sigslot.h"
#include "../system/video/Renderer.h"

//!Allows GuiElements to be grouped together into a "window"
class GuiFrame : public GuiElement {
public:
    //!Constructor
    GuiFrame(GuiFrame *parent = 0);

    //!\overload
    //!\param w Width of window
    //!\param h Height of window
    GuiFrame(float w, float h, GuiFrame *parent = 0);

    //!Destructor
    ~GuiFrame() override;

    //!Appends a GuiElement to the GuiFrame
    //!\param e The GuiElement to append. If it is already in the GuiFrame, it is removed first
    void append(GuiElement *e);

    //!Inserts a GuiElement into the GuiFrame at the specified index
    //!\param e The GuiElement to insert. If it is already in the GuiFrame, it is removed first
    //!\param i Index in which to insert the element
    void insert(GuiElement *e, uint32_t i);

    //!Removes the specified GuiElement from the GuiFrame
    //!\param e GuiElement to be removed
    void remove(GuiElement *e);

    //!Removes all GuiElements
    void removeAll();

    //!Bring element to front of the window
    void bringToFront(GuiElement *e) {
        remove(e);
        append(e);
    }

    //!Returns the GuiElement at the specified index
    //!\param index The index of the element
    //!\return A pointer to the element at the index, NULL on error (eg: out of bounds)
    GuiElement *getGuiElementAt(uint32_t index) const;

    //!Returns the size of the list of elements
    //!\return The size of the current element list
    uint32_t getSize();

    //!Sets the visibility of the window
    //!\param v visibility (true = visible)
    void setVisible(bool v) override;

    //!Resets the window's state to STATE_DEFAULT
    void resetState() override;

    //!Sets the window's state
    //!\param s State
    void setState(uint32_t s, int32_t c = -1) override;

    void clearState(uint32_t s, int32_t c = -1) override;

    //!Gets the index of the GuiElement inside the window that is currently selected
    //!\return index of selected GuiElement
    int32_t getSelected() override;

    //!Draws all the elements in this GuiFrame
    void draw(Renderer *v) override;

    //!Updates the window and all elements contains within
    //!Allows the GuiFrame and all elements to respond to the input data specified
    //!\param t Pointer to a GuiTrigger, containing the current input data from PAD/WPAD
    void update(GuiController *t) override;

    //!virtual updateEffects which is called by the main loop
    void updateEffects() override;

    //!virtual process which is called by the main loop
    void process() override;

    //! Signals
    //! On Closing
    sigslot::signal1<GuiFrame *> closing;
protected:
    bool dim;   //! Enable/disable dim of a window only
    GuiFrame *parent; //!< Parent Window
    std::vector<GuiElement *> elements; //!< Contains all elements within the GuiFrame
    std::recursive_mutex mutex;
};
