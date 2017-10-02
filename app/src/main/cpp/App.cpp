//
//  App.cpp
//  TacWarsIOS
//
//  Created by Lio on 26/05/16.
//  Copyright © 2016 Lio. All rights reserved.
//

#include "App.hpp"

//#include <SFML/Config.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-activity", __VA_ARGS__))


namespace mvd
{
  
  //=== CONSTRUCT (private)
  App::App()
  : m_paused(false)
  {

    // random seed f(time)
    srand(static_cast<unsigned int>(time(nullptr)));

  }
  
  

  //--- LOOP
  // Application main loop
  // main loop
  // FPS sync based one VBL, done by openGL through SFML::Window
  void App::loop()
  {
    // FULLSCREEN mode + autoRotate ON
    //sf::RenderWindow window(sf::VideoMode::getFullscreenModes().front(), "TacWars", sf::Style::Fullscreen | sf::Style::Resize);
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes().front(), "TacWars", sf::Style::Fullscreen);
    sf::View view = window.getDefaultView();

    const sf::ContextSettings cs = window.getSettings();
    LOGI("depthBits=0x%x, stencilBits=0x%x, antialiasingLevel=%d, majorVersion=%d, minorVersion=%d, attributeFlags=0x%x, sRgbCapable=%d"
    , cs.depthBits, cs.stencilBits, cs.antialiasingLevel, cs.majorVersion, cs.minorVersion, cs.attributeFlags, cs.sRgbCapable);

    // simple
    sf::RectangleShape rbg(sf::Vector2f(400.f, 400.f));
    rbg.setFillColor(sf::Color(0x808080FF));
    rbg.setPosition(50.f, 50.f);
    sf::RectangleShape rfg(sf::Vector2f(200.f, 200.f));
    rfg.setFillColor(sf::Color(0xFFFF8080));
    rfg.setPosition(25.f, 25.f);

    // create render texture
    sf::RenderTexture rt;
    sf::RenderStates rtst(sf::RenderStates::Default);
    //rtst.blendMode = sf::BlendMode(sf::BlendMode::SrcColor, sf::BlendMode::OneMinusSrcColor);
    /*
    rtst.blendMode = sf::BlendMode(
            sf::BlendMode::OneMinusSrcColor, sf::BlendMode::SrcColor, sf::BlendMode::Add
            , sf::BlendMode::SrcAlpha, sf::BlendMode::OneMinusSrcAlpha, sf::BlendMode::Add
    );
    */
    rt.create(500, 500);
    //rt.clear(sf::Color(0xFFFFFF00));
    rt.clear(sf::Color::Transparent);
    //rt.setSmooth(true);

    rt.draw(rbg, rtst);
    rt.draw(rfg, rtst);

    rt.display();

    sf::Sprite sprRT(rt.getTexture());

    rbg.move(500.f,0.f);
    rfg.move(500.f,0.f);


    while (window.isOpen())
    {
      sf::Event event;

      while (window.pollEvent(event))
      {
        switch (event.type)
        {
          case sf::Event::Closed:
            window.close();
            break;
          case sf::Event::Resized: {
            view.setSize(event.size.width, event.size.height);
            view.setCenter(event.size.width / 2, event.size.height / 2);
            window.setView(view);
          } break;
          default: break;
        }
      }

      window.clear(sf::Color(0x80a0f0ff));
      window.draw(rbg, rtst);
      window.draw(rfg, rtst);
      window.draw(sprRT, rtst);
      window.display();
    }
  }

}//eo-namespace mvd
