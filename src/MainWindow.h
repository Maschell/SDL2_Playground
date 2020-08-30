#pragma once

#include <iostream>
#include "gui/GuiFrame.h"
#include "gui/GuiButton.h"
#include "logger.h"

class MainWindow : public GuiFrame, public sigslot::has_slots<> {
public:
    void test(GuiButton *, const GuiController *, GuiTrigger *) {
        DEBUG_FUNCTION_LINE("Hello, you have clicked the button");
    }

    ~MainWindow();

    MainWindow(int32_t w, int32_t h);
    void process() override;
private:
    GuiText *label = nullptr;
    GuiTrigger *touchTrigger = nullptr;
    GuiSound *sound = nullptr;
    GuiImage *image = nullptr;
    GuiImage *image2 = nullptr;
    GuiImage *image3 = nullptr;
    GuiImage *image4 = nullptr;
    GuiImage *image5 = nullptr;
    GuiButton *button = nullptr;
    GuiSound *bgMusic = nullptr;
};
