//
//  App.hpp
//  TacWarsIOS
//
//  Created by Lio on 26/05/16.
//  Copyright © 2016 Lio. All rights reserved.
//

#ifndef App_hpp
#define App_hpp

// SFML
//#include <SFML/Main.hpp> // get the main() hook for IOS
//#include <SFML/Audio.hpp>
//#include <memory>
//using std::unique_ptr;

// MVD

// OTHER

namespace mvd // MoVodDesign namespace
{
  // APP: [SINGLETON]
  // top level pseudo static class, instantiated only once
  // call with mvd::App::getInstance()->loop();
  class App
  {
  public:
    //--- METHODS
    
    void loop(); // main loop
    
    // get reference to unique instance and handle clean up gracefully
    static App& getInstance() {
      static App instance;
      return instance;
    };

    // deleted methods to avoid appearance of accidental copies of your singleton
    App(App const&) = delete; // Singleton: Don't Implement
    void operator=(App const&) = delete; // Singleton: Don't Implement

  private:
    //-- METHODS
    App(); // Singleton constructor

    //-- MEMBERS
    //unique_ptr<sf::RenderWindow> m_upWindow;
    bool m_paused;
  };

}//eo-namespace mvd
#endif /* App_hpp */
