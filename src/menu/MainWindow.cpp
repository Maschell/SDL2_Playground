#include "MainWindow.h"

MainWindow::~MainWindow() {
    delete label;;
    delete touchTrigger;;
    delete sound;;
    delete image;;
    delete image2;;
    delete image3;;
    delete image4;;
    delete image5;;
    delete image;;
    delete label;;
    delete button;;
    delete bgMusic;;
}

MainWindow::MainWindow(int32_t w, int32_t h, Renderer* renderer) : GuiFrame(w, h) {
#if defined _WIN32
    auto picture_path = "test.png";
    auto font_path = "FreeSans.ttf";
    auto bgMusic_path = "bgMusic.ogg";
    auto music_click = "button_click.mp3";
#else
    auto picture_path = "fs:/vol/external01/test.png";
    auto font_path = "fs:/vol/external01/FreeSans.ttf";
    auto bgMusic_path = "fs:/vol/external01/bgMusic.ogg";
    auto music_click = "fs:/vol/external01/button_click.mp3";
#endif

    TTF_Init();
    TTF_Font *font;

    font = TTF_OpenFont(font_path, 28);

    FC_Font* fc_font = FC_CreateFont();
    if(!fc_font){
        DEBUG_FUNCTION_LINE("Failed to create font");
    }

    FC_LoadFontFromTTF(fc_font, renderer->getRenderer(), font, {255, 255, 255, 255});

    label = new GuiText("This is a test.This is a test. This is a test.This is a test.This is a test.This is a test.", {255, 255, 0, 255}, fc_font);

    bgMusic = new GuiSound(bgMusic_path);
    bgMusic->SetLoop(true);
    bgMusic->Play();

    image = new GuiImage(picture_path);
    image2 = new GuiImage(picture_path);
    image3 = new GuiImage(picture_path);
    image4 = new GuiImage(picture_path);
    image5 = new GuiImage(picture_path);

    button = new GuiButton(image5->getWidth(), image5->getHeight());

    this->setAlignment(ALIGN_TOP_LEFT);
    this->append(button);
    this->append(image);
    this->append(image2);
    this->append(image3);
    this->append(image4);

    image->setAlignment(ALIGN_TOP_LEFT);
    image2->setAlignment(ALIGN_TOP_RIGHT);
    image3->setAlignment(ALIGN_BOTTOM | ALIGN_LEFT);
    image4->setAlignment(ALIGN_BOTTOM | ALIGN_RIGHT);

    button->setAlignment(ALIGN_CENTERED);
    button->setImage(image5);

    sound = new GuiSound(music_click);

    touchTrigger = new GuiTrigger(GuiTrigger::CHANNEL_1, GuiTrigger::TOUCHED);
    touchTrigger = new GuiTrigger(GuiTrigger::CHANNEL_ALL, GuiTrigger::TOUCHED);
    button->setTrigger(touchTrigger);
    button->setEffectGrow();
    label->setAlignment(ALIGN_CENTERED);
    button->setLabel(label);
    label->setMaxWidth(button->getWidth());
    button->setSoundClick(sound);

    button->clicked.connect(this, &MainWindow::test);
}

void MainWindow::process() {
    GuiFrame::process();

    // Rotate the button for fun.
    auto res = button->getAngle() + 1;
    if(res > 360){
        res = 0;
    }
    button->setAngle(res);
}

void MainWindow::test(GuiButton *, const GuiController *, GuiTrigger *) {
        DEBUG_FUNCTION_LINE("Hello, you have clicked the button");
}
