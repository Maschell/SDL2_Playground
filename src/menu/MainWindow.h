#pragma once

#include <iostream>
#include "../gui/GuiFrame.h"
#include "../gui/GuiButton.h"
#include "../utils/logger.h"
#include "../gui/GuiImage.h"

class MainWindow : public GuiFrame, public sigslot::has_slots<> {
public:
    void test(GuiButton *, const GuiController *, GuiTrigger *);

    ~MainWindow() override;

    MainWindow(int32_t w, int32_t h, Renderer* renderer);
    void process() override;
private:
    GuiText *label = nullptr;
    GuiTrigger *touchTrigger = nullptr;
    GuiTrigger *buttonTrigger = nullptr;
    GuiSound *sound = nullptr;
    GuiImage *image = nullptr;
    GuiImage *image2 = nullptr;
    GuiImage *image3 = nullptr;
    GuiImage *image4 = nullptr;
    GuiImage *image5 = nullptr;
    GuiButton *button = nullptr;
    GuiSound *bgMusic = nullptr;
};
