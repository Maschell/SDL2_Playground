#include "MainWindow.h"
#include "../resources/Resources.h"

MainWindow::~MainWindow() {
    delete label;
    delete touchTrigger;
    delete buttonTrigger;
    delete sound;
    delete image;
    delete image2;
    delete image3;
    delete image4;
    delete image5;
    delete image;
    delete label;
    delete button;
    delete bgMusic;
}

MainWindow::MainWindow(int32_t w, int32_t h, Renderer* renderer) : GuiFrame(w, h) {
    auto picture_path = "button.png";
    auto font_path = "FreeSans.ttf";
    auto bgMusic_path = "bgMusic.ogg";
    auto music_click = "button_click.mp3";

    TTF_Init();
    TTF_Font *font;

    SDL_RWops *rw = SDL_RWFromMem((void *) Resources::GetFile(font_path), Resources::GetFileSize(font_path));

    DEBUG_FUNCTION_LINE("load font %08X %d", Resources::GetFile(font_path), Resources::GetFileSize(font_path));

    font = TTF_OpenFontRW(rw, 0, 28);
    if(!font){
        DEBUG_FUNCTION_LINE("Failed to load the font");
        return;
    }

    FC_Font* fc_font = FC_CreateFont();
    if(!fc_font){
        DEBUG_FUNCTION_LINE("Failed to create font");
    }

    auto res = FC_LoadFontFromTTF(fc_font, renderer->getRenderer(), font, {255, 255, 255, 255});
    DEBUG_FUNCTION_LINE("FontCache init %d", res);

    label = new GuiText("This is a test.", {255, 255, 0, 255}, fc_font);


    bgMusic = Resources::GetSound(bgMusic_path);
    if(!bgMusic){
        DEBUG_FUNCTION_LINE("Failed to load %s", bgMusic_path);
        return;
    }
    bgMusic->SetLoop(true);
    bgMusic->Play();

    image = new GuiImage(Resources::GetTexture(picture_path));
    image2 = new GuiImage(Resources::GetTexture(picture_path));
    image3 = new GuiImage(Resources::GetTexture(picture_path));
    image4 = new GuiImage(Resources::GetTexture(picture_path));
    image5 = new GuiImage(Resources::GetTexture(picture_path));
    if(!image){
        DEBUG_FUNCTION_LINE("Failed to add image");
        return;
    }
    if(!image2){
        DEBUG_FUNCTION_LINE("Failed to add image");
        return;
    }
    if(!image3){
        DEBUG_FUNCTION_LINE("Failed to add image");
        return;
    }
    if(!image4){
        DEBUG_FUNCTION_LINE("Failed to add image");
        return;
    }

    if(!image5){
        DEBUG_FUNCTION_LINE("Failed to add image");
        return;
    }

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

    sound = Resources::GetSound(music_click);

    touchTrigger = new GuiTrigger(GuiTrigger::CHANNEL_1, GuiTrigger::TOUCHED);
    buttonTrigger = new GuiTrigger(GuiTrigger::CHANNEL_ALL, GuiTrigger::BUTTON_A, true);
    button->setTrigger(touchTrigger);
    button->setTrigger(buttonTrigger);
    button->setEffectGrow();
    label->setAlignment(ALIGN_CENTERED);
    button->setLabel(label);
    label->setMaxWidth(button->getWidth());
    button->setSoundClick(sound);

    button->clicked.connect(this, &MainWindow::test);
}

void MainWindow::process() {
    GuiFrame::process();

    if(!button){
        return;
    }
    // Rotate the button for fun.
    auto res = button->getAngle() + 0.1f;
    if(res > 360){
        res = 0;
    }
    button->setAngle(res);
}

void MainWindow::test(GuiButton *, const GuiController *, GuiTrigger *) {
        DEBUG_FUNCTION_LINE("Hello, you have clicked the button");
}
