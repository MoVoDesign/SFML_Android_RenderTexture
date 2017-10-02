#include "App.hpp"

#include <android/native_activity.h>
#include <SFML/System/NativeActivity.hpp>

#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-activity", __VA_ARGS__))


int main(int argc, char *argv[]) {
  LOGI("[START]");

  ANativeActivity* na = sf::getNativeActivity();
  LOGI("[PATH]=[%s]", na->internalDataPath);

  mvd::App::getInstance().loop();
  LOGI("[END]");
  return 0;
}